#ifndef TSCPP_TYPECHECKER_MODULE_H
#define TSCPP_TYPECHECKER_MODULE_H

#pragma once

#include <string>

#include "tscpp/base/core.h"
#include "tscpp/typechecker/instructions.h"
#include "tscpp/typechecker/io_helper.h"
#include "tscpp/typechecker/types.h"
#include "tscpp/utils/utf.h"

namespace tscpp::vm {
using std::string;
using std::string_view;
using tscpp::instructions::OP;
using tscpp::utf::eatWhitespace;

struct ModuleSubroutine {
  string_view name;
  bool main = false;
  unsigned int address;
  unsigned int flags;
  bool exported = false;
  Type* result = nullptr;
  Type* narrowed = nullptr;  // when control flow analysis sets a new value
  ModuleSubroutine(string_view name, unsigned int address, unsigned int flags,
                   bool main)
      : name(name), address(address), flags(flags), main(main) {}
};

struct FoundSourceMap {
  unsigned int pos;
  unsigned int end;

  bool found() { return pos != 0 && end != 0; }
};

/**
 * const     v2: a<number> = "as"
 *      ^-----^ this is the identifier source map.
 *
 * This function makes sure map.pos starts at `v`, basically eating whitespace.
 */
inline void omitWhitespace(const string& code, FoundSourceMap& map) {
  map.pos = eatWhitespace(code, map.pos);
}

struct Module;

struct DiagnosticMessage {
  string message;
  unsigned int ip;  // ip of the node/OP
  Module* module = nullptr;
  DiagnosticMessage() {}
  explicit DiagnosticMessage(const string& message, int ip)
      : message(message), ip(ip) {}
};

struct FoundSourceLineCharacter {
  unsigned int line;
  unsigned int pos;
  unsigned int end;
};

struct Module {
  const string bin;
  string fileName = "index.ts";
  const string code = "";  // for diagnostic messages only

  vector<ModuleSubroutine> subroutines;
  unsigned int sourceMapAddress;
  unsigned int sourceMapAddressEnd;

  vector<DiagnosticMessage> errors;
  Module() {}

  Module(const string_view& bin, const string& fileName, const string& code)
      : bin(bin), fileName(fileName), code(code) {}

  void clear() {
    errors.clear();
    subroutines.clear();
  }

  ModuleSubroutine* getSubroutine(unsigned int index) {
    return &subroutines[index];
  }

  ModuleSubroutine* getMain() { return &subroutines.back(); }

  string findIdentifier(unsigned int ip) {
    auto map = findNormalizedMap(ip);
    if (!map.found())
      return "";
    return code.substr(map.pos, map.end - map.pos);
  }

  FoundSourceMap findMap(unsigned int ip) {
    unsigned int found = 0;
    for (unsigned int i = sourceMapAddress; i < sourceMapAddressEnd;
         i += 3 * 4) {
      auto mapIp = vm::readUint32(bin, i);
      if (mapIp == ip) {
        found = i;
        break;
      }
      //                if (mapIp > ip) break;
      //                found = i;
    }

    if (found) {
      return {vm::readUint32(bin, found + 4), vm::readUint32(bin, found + 8)};
    }
    return {0, 0};
  }

  FoundSourceMap findNormalizedMap(unsigned int ip) {
    auto map = findMap(ip);
    if (map.found())
      omitWhitespace(code, map);
    return map;
  }

  /**
   * Converts FindSourceMap{x,y} to
   */
  FoundSourceLineCharacter mapToLineCharacter(FoundSourceMap map) {
    unsigned int pos = 0;
    unsigned int line = 0;
    while (pos < map.pos) {
      std::size_t lineStart = code.find('\n', pos);
      if (lineStart == std::string::npos) {
        return {.line = line, .pos = map.pos - pos, .end = map.end - pos};
      } else if (lineStart > map.pos) {
        // dont overshot
        break;
      }
      pos = lineStart + 1;
      line++;
    }
    return {.line = line, .pos = map.pos - pos, .end = map.end - pos};
  }

  void printErrors() {
    for (auto&& e : errors) {
      if (e.ip) {
        auto map = findNormalizedMap(e.ip);

        if (map.found()) {
          auto lineStart = code.rfind('\n', map.pos);
          lineStart = lineStart == std::string::npos ? 0 : lineStart + 1;

          auto lineEnd = code.find('\n', map.end);
          if (lineEnd == std::string::npos)
            lineEnd = code.size();
          std::cout << cyan << fileName << ":" << yellow << map.pos << ":"
                    << map.end << reset << " - " << red << "error" << reset
                    << " TS0000: " << e.message << "\n\n";
          std::cout << "»" << code.substr(lineStart, lineEnd - lineStart - 1)
                    << "\n";
          auto space = map.pos - lineStart;
          std::cout << "»" << std::string(space, ' ') << red
                    << std::string(map.end - map.pos, '~') << reset << "\n\n";
          continue;
        }
      }
      std::cout << "  " << e.message << "\n";
    }
    std::cout << "Found " << errors.size() << " errors in " << fileName << "\n";
  }
};

inline void parseHeader(shared_ptr<Module>& module) {
  auto& bin = module->bin;
  auto end = bin.size();
  bool main = true;
  for (unsigned int i = 0; i < end; i++) {
    const auto op = (OP)bin[i];
    switch (op) {
      case OP::Jump: {
        i = vm::readUint32(bin, i + 1) - 1;  // minus 1 because for's i++
        break;
      }
      case OP::SourceMap: {
        unsigned int size = vm::readUint32(bin, i + 1);
        module->sourceMapAddress = i + 1 + 4;
        i += 4 + size;
        module->sourceMapAddressEnd = i;
        break;
      }
      case OP::Subroutine: {
        unsigned int nameAddress = vm::readUint32(bin, i + 1);
        auto name = nameAddress ? vm::readStorage(bin, nameAddress + 8) : "";
        unsigned int address = vm::readUint32(bin, i + 5);
        unsigned int flags = vm::readUint32(bin, i + 5 + 4);
        vm::eatParams(op, &i);
        module->subroutines.push_back(
            ModuleSubroutine(name, address, flags, main));
        main = false;
        break;
      }
      case OP::Main: {
        return;
      }
    }
  }

  throw std::runtime_error("No OP::Main found");
}
}  // namespace tscpp::vm

#endif  // TSCPP_TYPECHECKER_MODULE_H