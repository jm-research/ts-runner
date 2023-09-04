#ifndef TSCPP_TYPECHECKER_DEBUG_H
#define TSCPP_TYPECHECKER_DEBUG_H

#include <string>

#include "tscpp/base/core.h"
#include "tscpp/typechecker/instructions.h"
#include "tscpp/typechecker/io_helper.h"

namespace tscpp::checker {
using std::string_view;
using tscpp::instructions::OP;

struct PrintSubroutineOp {
  string text;
  unsigned int address;
};

struct PrintSubroutine {
  string name;
  unsigned int address;
  vector<PrintSubroutineOp> operations;
};

struct DebugSourceMapEntry {
  OP op;
  unsigned int bytecodePos;
  unsigned int sourcePos;
  unsigned int sourceEnd;
};

struct DebugBinResult {
  vector<string> operations;
  vector<string> storages;
  vector<PrintSubroutine> subroutines;
  vector<DebugSourceMapEntry> sourceMap;
  PrintSubroutine* activeSubroutine = nullptr;
};

inline DebugBinResult parseBin(string_view bin, bool print = false) {
  const auto end = bin.size();
  unsigned int storageEnd = 0;
  bool newSubRoutine = false;
  bool firstJump = false;
  bool newLine = false;
  DebugBinResult result;
  if (print)
    std::cout << fmt::format("Bin {} bytes: ", bin.size());

  for (unsigned int i = 0; i < end; i++) {
    if (storageEnd) {
      while (i < storageEnd) {
        auto size = vm::readUint16(bin, i + 8);
        auto data = bin.substr(i + 8 + 2, size);
        if (print)
          std::cout << fmt::format("(Storage ({})\"{}\") ", size, data);
        result.storages.push_back(string(data));
        i += 8 + 2 + size;
      }
      debug("");
      storageEnd = 0;
    }

    if (newSubRoutine) {
      auto found = false;
      unsigned int j = 0;
      for (auto&& r : result.subroutines) {
        if (r.address == i) {
          if (print)
            std::cout << fmt::format("\n&{} {}(): ", j, r.name);
          result.activeSubroutine = &r;
          found = true;
          break;
        }
        j++;
      }
      if (!found) {
        if (print)
          std::cout << fmt::format("\nunknown!(): ");
      }
      newSubRoutine = false;
    }
    std::string params = "";
    auto startI = i;
    auto op = (OP)bin[i];

    switch (op) {
      case OP::TailCall:
      case OP::Call: {
        params += fmt::format(" &{}[{}]", vm::readUint32(bin, i + 1),
                              vm::readUint16(bin, i + 5));
        vm::eatParams(op, &i);
        break;
      }
      case OP::SourceMap: {
        auto size = vm::readUint32(bin, i + 1);
        auto start = i + 1;
        i += 4 + size;
        params +=
            fmt::format(" {}->{} ({})", start, i,
                        size / (4 * 3));  // each entry has 3x 4bytes (uint32)

        for (unsigned int j = start + 4; j < i; j += 4 * 3) {
          DebugSourceMapEntry sourceMapEntry{
              .op = (OP)(bin[vm::readUint32(bin, j)]),
              .bytecodePos = vm::readUint32(bin, j),
              .sourcePos = vm::readUint32(bin, j + 4),
              .sourceEnd = vm::readUint32(bin, j + 8),
          };
          result.sourceMap.push_back(sourceMapEntry);
          if (print)
            debug("Map [{}]{} to {}:{}", sourceMapEntry.bytecodePos,
                  sourceMapEntry.op, sourceMapEntry.sourcePos,
                  sourceMapEntry.sourceEnd);
        }
        break;
      }
      case OP::Subroutine: {
        auto nameAddress = vm::readUint32(bin, i + 1);
        auto address = vm::readUint32(bin, i + 5);
        string name =
            nameAddress ? string(vm::readStorage(bin, nameAddress + 8)) : "";
        params += fmt::format(" {}[{}]", name, address);
        vm::eatParams(op, &i);
        result.subroutines.push_back({.name = name, .address = address});
        break;
      }
      case OP::Jump: {
        auto address = vm::readInt32(bin, i + 1);
        params += fmt::format(" [{}, +{}]", startI + address, address);
        vm::eatParams(op, &i);
        if (!firstJump)
          storageEnd = address;
        if (firstJump)
          newLine = true;
        firstJump = true;
        break;
      }
      case OP::Main: {
        newSubRoutine = true;
        break;
      }
      case OP::Return: {
        newSubRoutine = true;
        break;
      }
      case OP::Distribute: {
        params += fmt::format(" &{} [{}, +{}]", vm::readUint16(bin, i + 1),
                              startI + vm::readUint32(bin, i + 3),
                              vm::readUint32(bin, i + 3));
        vm::eatParams(op, &i);
        newLine = true;
        break;
      }
      case OP::JumpCondition: {
        params += fmt::format(" [{}]", startI + vm::readUint32(bin, i + 1));
        vm::eatParams(op, &i);
        newLine = true;
        break;
      }
      case OP::CheckBody:
      case OP::InferBody:
      case OP::SelfCheck:
      case OP::Inline:
      case OP::Set:
      case OP::TypeArgumentDefault: {
        params += fmt::format(" &{}", vm::readUint32(bin, i + 1));
        vm::eatParams(op, &i);
        break;
      }
      case OP::ClassRef:
      case OP::FunctionRef: {
        params += fmt::format(" &{} &{}", vm::readUint32(bin, i + 1),
                              vm::readUint32(bin, i + 5));
        vm::eatParams(op, &i);
        break;
      }
      case OP::New:
      case OP::Instantiate:
      case OP::InferTypeArguments: {
        params += fmt::format(" {}", vm::readUint16(bin, i + 1));
        vm::eatParams(op, &i);
        break;
      }
      case OP::Error: {
        params += fmt::format(
            " {}", (instructions::ErrorCode)vm::readUint16(bin, i + 1));
        vm::eatParams(op, &i);
        break;
      }
      case OP::CallExpression: {
        params += fmt::format(" {}", vm::readUint16(bin, i + 1));
        vm::eatParams(op, &i);
        break;
      }
      case OP::Method:
      case OP::Function:
      case OP::Union:
      case OP::Tuple:
      case OP::TemplateLiteral:
      case OP::Class:
      case OP::ObjectLiteral:
      case OP::Slots: {
        params += fmt::format(" {}", vm::readUint16(bin, i + 1));
        vm::eatParams(op, &i);
        break;
      }
      case OP::Loads: {
        params += fmt::format(" {} {}", vm::readUint16(bin, i + 1),
                              vm::readUint16(bin, i + 3));
        vm::eatParams(op, &i);
        break;
      }
      case OP::Parameter:
      case OP::NumberLiteral:
      case OP::BigIntLiteral:
      case OP::StringLiteral: {
        auto address = vm::readUint32(bin, i + 1);
        params += fmt::format(" \"{}\"", vm::readStorage(bin, address + 8));
        vm::eatParams(op, &i);
        break;
      }
    }

    string text;
    if (params.empty()) {
      text = fmt::format("{}", op);
    } else {
      text = fmt::format("{}{}", op, params);
    }
    if (result.activeSubroutine) {
      result.activeSubroutine->operations.push_back(
          {.text = text, .address = startI});
    } else {
      result.operations.push_back(text);
    }
    if (print) {
      std::cout << "[" << startI << "](" << text << ") ";
      if (newLine)
        std::cout << "\n";
      newLine = false;
    }
  }
  if (print)
    std::cout << "\n";
  return result;
}

inline void printBin(string_view bin) { parseBin(bin, true); }
}  // namespace tscpp::checker

#endif  // TSCPP_TYPECHECKER_DEBUG_H