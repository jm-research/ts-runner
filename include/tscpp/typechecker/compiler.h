#ifndef TSCPP_TYPECHECKER_COMPILER_H
#define TSCPP_TYPECHECKER_COMPILER_H

#pragma once

#include <functional>
#include <string>
#include <utility>

#include "tscpp/parser/node_helper.h"
#include "tscpp/typechecker/instructions.h"
#include "tscpp/typechecker/io_helper.h"

namespace tscpp::checker {

using instructions::ErrorCode;
using instructions::OP;
using std::function;
using std::string;

enum class SymbolType {
  Variable,      // const x = true;
  Function,      // function x() {}
  Class,         // class X {}
  Inline,        // subroutines of type argument defaults
  Type,          // type alias, e.g. `foo` in `type foo = string;`
  TypeArgument,  // template variable, e.g. T in function <T>foo(bar: T);
  TypeVariable,  // type variables in distributive conditional types, mapped
                 // types, reserve a stack entry
};

struct SourceMapEntry {
  unsigned int bytecodePos;
  unsigned int sourcePos;
  unsigned int sourceEnd;
};

struct SourceMap {
  vector<SourceMapEntry> map;

  void push(unsigned int bytecodePos, unsigned int sourcePos,
            unsigned int sourceEnd) {
    map.push_back({bytecodePos, sourcePos, sourceEnd});
  }
};

struct ArgumentUsage {
  unsigned int lastIp{};
  unsigned int lastSubroutineIndex{};
  unsigned int argumentIndex{};

  explicit ArgumentUsage(unsigned int argumentIndex)
      : argumentIndex(argumentIndex) {}
};

struct TypeArgumentUsage {
  unsigned int symbolIndex;
  unsigned int ip;

  explicit TypeArgumentUsage(unsigned int symbolIndex, unsigned int ip)
      : symbolIndex(symbolIndex), ip(ip) {}
};

struct Subroutine;

struct Symbol {
  string name;
  bool active = true;  // will be switched to false when it goes out of scope
  SymbolType type = SymbolType::Type;
  unsigned int index{};  // symbol index of the current frame
  unsigned int pos{};
  unsigned int end{};
  unsigned int declarations = 1;
  shared_ptr<Subroutine> routine = nullptr;
};

struct FoundSymbol {
  Symbol* symbol = nullptr;
  unsigned int offset;

  explicit FoundSymbol() : symbol(nullptr), offset(0) {}
  explicit FoundSymbol(Symbol* symbol, unsigned int offset)
      : symbol(symbol), offset(offset) {}
};

// aka Branch
struct Section {
  // instruction pointer start and end
  unsigned int start = 0;
  unsigned int end = 0;
  OP lastOp = OP::Noop;
  unsigned int ops = 0;
  bool isBlockTailCall{};

  bool hasChild = false;
  vector<TypeArgumentUsage> typeArgumentUsages;

  // next and up section
  int next = -1;
  int up = -1;

  explicit Section(unsigned int start, unsigned int up = -1)
      : start(start), up(up) {}

  void registerTypeArgumentUsage(Symbol* symbol, unsigned int ip) {
    for (auto&& usage : typeArgumentUsages) {
      if (usage.symbolIndex == symbol->index) {
        usage.symbolIndex = ip;
        return;
      }
    }
    typeArgumentUsages.emplace_back(symbol->index, ip);
  }
};

// A subroutine is a sub program that can be executed by knowing its address.
// They are used for example for type alias, mapped type, conditional type (for
// false and true side)
struct Subroutine {
  vector<unsigned char> ops;  // OPs, and its parameters
  unsigned int lastOpIp;
  SourceMap sourceMap;
  string_view identifier{};
  unsigned int index{};
  unsigned int slots{};
  unsigned int slotIP{};
  unsigned int nameAddress{};
  SymbolType type = SymbolType::Type;
  vector<Symbol> symbols{};

  vector<Section> sections;
  unsigned int activeSection = 0;

  void registerTypeArgumentUsage(Symbol* symbol) {
    sections[activeSection].registerTypeArgumentUsage(symbol, ip());
  }

  explicit Subroutine() {
    identifier = "";
    sections.emplace_back(ip());
  }

  explicit Subroutine(string_view& identifier) : identifier(identifier) {
    sections.emplace_back(ip());
  }

  bool isIgnoreNextSectionOP = false;
  void ignoreNextSectionOP() { isIgnoreNextSectionOP = true; }

  void blockTailCall() { sections[activeSection].isBlockTailCall = true; }

  void pushOp(OP op) {
    lastOpIp = ops.size();
    ops.push_back(op);

    if (!isIgnoreNextSectionOP) {
      sections[activeSection].lastOp = op;
      sections[activeSection].ops++;
    }

    isIgnoreNextSectionOP = false;
  }

  unsigned int ip() { return ops.size(); }

  void pushSection() {
    sections[activeSection].hasChild = true;
    auto section = sections.emplace_back(ip(), activeSection);
    activeSection = sections.size() - 1;
  }

  void end() { sections[activeSection].end = ip(); }

  void popSection() {
    sections.back().end = ip();
    activeSection = sections.back().up;

    if (sections[activeSection].next == -1) {
      auto& next = sections.emplace_back(ip());
      sections[activeSection].next = sections.size() - 1;
      next.up = sections[activeSection].up;
      activeSection = sections.size() - 1;
    }
  }

  bool ended(Section& section) {
    return section.next >= 0 ? ended(sections[section.next]) : section.ops == 0;
  }

  void optimise() {
    // find all tail sections (sections that end the subroutine when executed)
    for (auto&& section : sections) {
      if (section.hasChild || section.isBlockTailCall) {
        continue;
      }
      if (section.next >= 0 && !ended(section)) {
        continue;
      }

      Section* current = section.up >= 0 ? &sections[section.up] : nullptr;
      bool tail = true;
      while (current) {
        if (current->isBlockTailCall) {
          tail = false;
          break;
        }
        // go upwards and check if some parent has ->next, if so, it is not a
        // tail section
        if (!ended(*current)) {
          tail = false;
          break;
        }
        if (current->up >= 0) {
          current = &sections[current->up];
        } else {
          break;
        }
      }

      // debug("Tail {} lastOp={} ops={}", tail, section.lastOp, section.ops);

      if (tail) {
        // this section is a tail section, which means it returns the subroutine
        if (section.lastOp == OP::Call) {
          ops[section.end - 1 - 4 - 2] = OP::TailCall;
          // debug("tail call optimised");
        }

        for (auto&& usage : section.typeArgumentUsages) {
          auto op = ops[usage.ip];
          if (op == OP::Rest) {
            ops[usage.ip] = OP::RestReuse;
          }
        }
      }
    }
  }

  void pushSourceMap(unsigned int sourcePos, unsigned int sourceEnd) {
    sourceMap.push(ops.size(), sourcePos, sourceEnd);
  }

  // void registerArgumentUsage() {
  //     argumentUsages.emplace_back(argumentUsages.size());
  // }
  //
  // ArgumentUsage &getArgumentUsage(unsigned int argumentIndex) {
  //     if (argumentUsages.size()<=argumentIndex) {
  //         throw std::runtime_error("Unknown argument");
  //     }
  //     return argumentUsages[argumentIndex];
  // }

  unsigned int getFlags() {
    unsigned int flags = 0;
    return flags;
  }
};

struct StorageItem {
  string_view value;
  unsigned int address{};

  explicit StorageItem(const string_view& value) : value(value) {}
};

struct FrameOffset {
  uint32_t frame;   // how many frames up
  uint32_t symbol;  // the index of the symbol in referenced frame, refers
                    // directly to x stack entry of that stack frame.
};

struct Visit {
  bool active = true;
  unsigned int index;  // subroutine index
  unsigned int ip;     // subroutine ip
  unsigned int frameDepth;
  OP op;
};

inline void visitOps2(vector<shared_ptr<Subroutine>>& subroutines, Visit& visit,
                      const function<void(Visit&)>& callback) {
  const auto ops = subroutines[visit.index]->ops;
  for (unsigned int i = 0; visit.active && i < ops.size(); i++) {
    visit.op = (OP)ops[i];
    switch (visit.op) {
      // case OP::Frame: {
      //     visit.frameDepth++;
      //     break;
      // }
      case OP::Tuple:
      case OP::Union:
      case OP::Intersection:
      case OP::Class:
      case OP::ObjectLiteral:
      case OP::Return: {
        visit.frameDepth--;
        break;
      }
        // todo: Go deeper for inline functions for distributive and mapped
        // types, too.
      case OP::JumpCondition: {
        // go deeper
        const auto leftProgram = vm::readUint16(ops, i + 1);
        const auto rightProgram = vm::readUint16(ops, i + 3);
        visit.frameDepth++;
        visit.index = leftProgram;
        visitOps2(subroutines, visit, callback);
        visit.index = rightProgram;
        visitOps2(subroutines, visit, callback);
        visit.frameDepth--;
        break;
      }
      default: {
        visit.ip = i;
        callback(visit);
      }
    }
    vm::eatParams(visit.op, &i);
  }
}

inline void visitOps(vector<shared_ptr<Subroutine>>& subroutines,
                     unsigned int index,
                     const function<void(Visit&)>& callback) {
  auto current = subroutines[index];
  Visit visit;
  visit.index = index;
  visitOps2(subroutines, visit, callback);
}

// shared_ptr<Subroutine> findOuterTypeFunction(vector<shared_ptr<Subroutine>>
// &subroutines, shared_ptr<Subroutine> &subroutine) {
//     shared_ptr<Subroutine> typeFunction = subroutine;
//
//     while (typeFunction->type == SymbolType::Inline) {
//         if (typeFunction->index == 0) {
//             debug("No type function found for subroutine");
//             return subroutines[0];
//         }
//         //the actual function is always before the Inline
//         typeFunction = subroutines[typeFunction->index - 1];
//     }
//
//     return typeFunction;
// }

//    inline void optimiseRestReuse(vector<shared_ptr<Subroutine>> &subroutines,
//    shared_ptr<Subroutine> &subroutine) {
//        for (auto &&variable: subroutine->argumentUsages) {
//            if (!variable.lastIp) continue;
//
//            //check if it was used in ...T, and mark it as RestReuse
//            auto &lastUseSubroutine =
//            subroutines[variable.lastSubroutineIndex]; auto variableUserOp =
//            (OP) lastUseSubroutine->ops[variable.lastIp + 1 + 2 + 2]; if
//            (variableUserOp == OP::Rest) {
//                lastUseSubroutine->ops[variable.lastIp + 1 + 2 + 2] =
//                OP::RestReuse;
//            }
//        }
//
////        std::set<Subroutine *> visited;
////
////        LastRest lastRest = subroutine->lastRest;
////
////        //we support for the moment only
////        bool startPositionFound = false;
////        bool startIndex = typeFunction->index;
////        bool usedAfterRest = false;
////
////        //note: if we have a second optimisation that needs a OP
///forward-pass, we should generalise it and do it only once. /
///visitOps(subroutines, typeFunction->index, [&lastRest, &startPositionFound,
///&subroutines, &usedAfterRest, &startIndex](Visit visit) { /            if
///(!startPositionFound && visit.index == startIndex && visit.op == lastRest.ip)
///{ /                startPositionFound = true; /            }
////
////            if (startPositionFound) {
////                //detect now usage of the lastRest.typeArgument
////                if (visit.op == OP::Loads) {
////                    //check if it actually references the right typeArgument
////                    unsigned int frameOffset =
///vm::readUint16(subroutines[visit.index]->ops, visit.op + 1); / unsigned int
///varIndex = vm::readUint16(subroutines[visit.index]->ops, visit.op + 3); / if
///(varIndex == lastRest.typeArgument && frameOffset == visit.frameDepth) { /
///usedAfterRest = true; /                        visit.active = false; / } / }
////            }
////        });
////
////        if (!usedAfterRest) {
////            //it's safe to mark it as RestReuse
////            debug("safe to RestReuse!");
////        }
//    }

//    struct Optimiser {
//        vector<shared_ptr<Subroutine>> *subroutines;
//
//        explicit Optimiser(vector<shared_ptr<Subroutine>> *subroutines):
//        subroutines(subroutines) {}
//
//        void optimise(unsigned int index) {
//            auto current = (*subroutines)[index];
//            if (current->optimised) return;
//
//            current->optimised = true;
//
//            for (unsigned int i = 0; i<current->ops.size(); i++) {
//                auto op = (OP) current->ops[i];
////                debug("[{}] optimise OP {}", current->index, op);
//
//                switch (op) {
//                    case OP::Rest: {
//                        debug("optimise Rest");
//                        //todo: check if previous is ::Loads
//                        // determine the identity of the Loads variable
//                        // and
//                        break;
//                    }
//                    case OP::Call: {
//                        //go deeper
//                        auto address = vm::readUint32(current->ops, i + 1);
//                        optimise(address);
//                        break;
//                    }
//                    case OP::JumpCondition: {
//                        //go deeper
//                        const auto leftProgram = vm::readUint16(current->ops,
//                        i + 1); const auto rightProgram =
//                        vm::readUint16(current->ops, i + 3);
//                        optimise(leftProgram);
//                        optimise(rightProgram);
//                        break;
//                    }
//                }
//                vm::eatParams(op, &i);
//            }
//        }
//    };

class Program {
 public:
  vector<string_view> storage;  // all kind of literals, as strings
  unordered_map<uint64_t, reference_wrapper<StorageItem>>
      storageMap;  // used to deduplicated storage entries

  unsigned int storageIndex{};

  // tracks which subroutine is active (end() is), so that pushOp calls are
  // correctly assigned.
  vector<shared_ptr<Subroutine>> activeSubroutines;
  vector<shared_ptr<Subroutine>> subroutines;

  Program() {
    pushSubroutineNameLess();  // main
  }

  /**
   * Creates a new nameless subroutine, used for example in mapped-type,
   * conditional type
   * @return
   */
  unsigned int pushSubroutineNameLess() {
    auto routine = make_shared<Subroutine>();
    routine->type = SymbolType::Inline;
    routine->index = subroutines.size();

    subroutines.push_back(routine);
    activeSubroutines.push_back(subroutines.back());
    return routine->index;
  }

  // shared_ptr<Subroutine> getOuterTypeFunction() {
  //     return findOuterTypeFunction(subroutines, activeSubroutines.empty() ?
  //     subroutines[0] : activeSubroutines.back());
  // }

  void registerTypeArgumentUsage(Symbol* symbol) {
    if (activeSubroutines.empty())
      return;
    activeSubroutines.back()->registerTypeArgumentUsage(symbol);
  }

  /**
   * Push the subroutine from the symbol as active. This means it will now be
   * populated with OPs.
   */
  unsigned int pushSubroutine(Symbol& symbol) {
    // find subroutine
    if (!symbol.routine)
      throw runtime_error(fmt::format("symbol has no routine {}", symbol.name));
    activeSubroutines.push_back(symbol.routine);
    return symbol.routine->index;
  }

  shared_ptr<Subroutine> popSubroutine() {
    if (activeSubroutines.empty())
      throw runtime_error("No active subroutine found");
    auto subroutine = activeSubroutines.back();
    if (subroutine->ops.empty()) {
      throw runtime_error("Routine is empty");
    }

    for (auto&& symbol : subroutine->symbols) {
      if (symbol.type == SymbolType::TypeVariable) {
      }
    }
    subroutine->end();
    subroutine->optimise();
    subroutine->ops.push_back(OP::Return);

    activeSubroutines.pop_back();
    return subroutine;
  }

  shared_ptr<Subroutine>& currentSubroutine() {
    return activeSubroutines.back();
  }

  FoundSymbol findSymbol(const string_view& identifier) {
    unsigned int offset = 0;
    for (auto subroutine = activeSubroutines.rbegin();
         subroutine != activeSubroutines.rend(); ++subroutine) {
      auto& symbols = (*subroutine)->symbols;
      // we go in reverse to fetch the closest
      for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
        if (it->active && it->name == identifier) {
          return FoundSymbol(&(*it), offset);
        }
      }
      offset++;
    }

    return FoundSymbol();
  }

  /**
   * The address is always written using 4 bytes.
   *
   * It sometimes is defined in Program as index to the storage or subroutine
   * and thus is a immediate representation of the address. In this case it will
   * be replaced in build with the real address in the binary (hence why we need
   * 4 bytes, so space stays constant).
   */
  void pushAddress(unsigned int address, unsigned int offset = 0) {
    auto& ops = activeSubroutines.back()->ops;
    vm::writeUint32(ops, offset == 0 ? ops.size() : offset, address);
  }

  void pushInt32Address(int32_t address, unsigned int offset = 0) {
    auto& ops = activeSubroutines.back()->ops;
    vm::writeInt32(ops, offset == 0 ? ops.size() : offset, address);
  }

  void pushUint32(unsigned int v) {
    auto& ops = activeSubroutines.back()->ops;
    vm::writeUint32(ops, ops.size(), v);
  }

  void pushUint16(unsigned int v, unsigned int offset = 0) {
    auto& ops = activeSubroutines.back()->ops;
    vm::writeUint16(ops, offset == 0 ? ops.size() : offset, v);
  }

  shared_ptr<Subroutine> mainSubroutine() { return subroutines[0]; }

  void pushError(ErrorCode code, const node<Node>& node) {
    auto main = mainSubroutine();
    // errors need to be part of main
    main->sourceMap.push(0, node->pos, node->end);
    main->ops.push_back(OP::Error);
    vm::writeUint16(main->ops, main->ops.size(), (unsigned int)code);
  }

  void pushSymbolAddress(FoundSymbol& foundSymbol) {
    if (!foundSymbol.symbol)
      throw std::runtime_error("FoundSymbol without symbol");
    pushUint16(foundSymbol.offset);
    pushUint16(foundSymbol.symbol->index);
  }

  void pushSourceMap(const node<Node>& node) {
    activeSubroutines.back()->pushSourceMap(node->pos, node->end);
  }

  void ignoreNextSectionOP() {
    activeSubroutines.back()->ignoreNextSectionOP();
  }

  void pushSection() { activeSubroutines.back()->pushSection(); }

  void blockTailCall() { activeSubroutines.back()->blockTailCall(); }

  void popSection() { activeSubroutines.back()->popSection(); }

  // if > 0 expression statements keep the return value on the stack, otherwise
  // they are removed.
  //  e.g. `doIt()` removes its return type of `doIt()` while `doIt().deep()`
  //  keeps it (so that deep can be resolved).
  unsigned int expressionResult = 0;
  void pushKeepExpressionResult() { expressionResult++; }
  void popKeepExpressionResult() { expressionResult--; }
  void pushSlots() {
    currentSubroutine()->slotIP = ip();
    pushOp(OP::Slots);
    pushUint16(0);  // will be changed in program build
  }

  void pushOp(OP op) { activeSubroutines.back()->pushOp(op); }

  unsigned int subroutineIndex() { return activeSubroutines.back()->index; }

  unsigned int lastOpIp() { return activeSubroutines.back()->lastOpIp; }

  unsigned int ip() { return activeSubroutines.back()->ops.size(); }

  void pushOp(OP op, const optionalNode<Node>& node) {
    if (node)
      pushSourceMap(node);
    pushOp(op);
  }

  // needed for variables
  //        void pushOpAtFrameInHead(shared_ptr<Frame> frame, OP op,
  //        std::vector<unsigned int> params = {}) {
  //            auto &ops = getOPs();
  //
  //            //an earlier known frame could be referenced, in which case we
  //            have to put ops between others. ops.insert(ops.begin() +
  //            frame->headOffset, op); if (params.size()) {
  //                ops.insert(ops.begin() + frame->headOffset + 1,
  //                params.begin(), params.end());
  //            }
  //        }

  unsigned int createSymbolCheckout() {
    return currentSubroutine()->symbols.size();
  }

  void restoreSymbolCheckout(unsigned int checkpoint) {
    auto symbols = currentSubroutine()->symbols;
    for (; checkpoint < symbols.size(); checkpoint++) {
      symbols[checkpoint].active = false;
    }
  }

  /**
   * A symbol could be type alias, function expression, var type declaration.
   * Each represents a type expression and gets its own subroutine. The
   * subroutine is directly created and an index assign. Later when
   * pushSubroutine() is called, this subroutine is returned and with OPs
   * populated.
   *
   * Symbols will be created first before a body is extracted. This makes sure
   * all symbols are known before their reference is used.
   */
  Symbol& pushSymbol(string_view name, SymbolType type,
                     const node<Node>& node) {
    auto subroutine = currentSubroutine();
    for (auto&& v : subroutine->symbols) {
      if (type != SymbolType::TypeVariable && v.name == name) {
        v.declarations++;
        return v;
      }
    }

    Symbol symbol;
    symbol.name = string(name);
    symbol.type = type;
    symbol.index = currentSubroutine()->symbols.size();
    symbol.pos = node->pos;
    symbol.end = node->end;
    if (type == SymbolType::TypeVariable)
      subroutine->slots++;
    subroutine->symbols.push_back(symbol);
    return subroutine->symbols.back();
  }

  Symbol& pushSymbolForRoutine(string_view name, SymbolType type,
                               const node<Node>& node) {
    auto& symbol = pushSymbol(name, type, node);
    if (symbol.routine)
      return symbol;

    auto routine = make_shared<Subroutine>(name);
    routine->type = type;
    routine->nameAddress = registerStorage(routine->identifier);
    routine->index = subroutines.size();
    subroutines.push_back(routine);
    symbol.routine = routine;

    return symbol;
  }

  // note: make sure the same name is not added twice. needs hashmap
  unsigned int registerStorage(const string_view& s) {
    if (!storageIndex)
      storageIndex = 1 + 4;  // jump+address

    const auto address = storageIndex;
    storage.push_back(s);
    storageIndex += 8 + 2 + s.size();  // hash + size + data
    return address;
  }

  /**
   * Pushes a Uint32 and stores the text into the storage.
   * @param s
   */
  void pushStorage(string_view s) { pushAddress(registerStorage(s)); }

  void pushStringLiteral(string_view s, const node<Node>& node) {
    pushOp(OP::StringLiteral, node);
    pushStorage(s);
  }

  string build() {
    vector<unsigned char> bin;
    unsigned int address = 0;

    address = 5;  // we add JUMP + index when building the program to jump over
                  // all subroutines&storages
    bin.push_back(OP::Jump);
    vm::writeUint32(bin, bin.size(), 0);  // set after storage handling

    for (auto&& item : storage) {
      address += 8 + 2 + item.size();  // hash+size+data
    }

    // set initial jump position to right after the storage data
    vm::writeUint32(bin, 1, address);
    // push all storage data to the binary
    for (auto&& item : storage) {
      vm::writeUint64(bin, bin.size(), hash::runtime_hash(item));
      vm::writeUint16(bin, bin.size(), item.size());
      bin.insert(bin.end(), item.begin(), item.end());
    }

    // collect sourcemap data
    unsigned int sourceMapSize = 0;
    for (auto&& routine : subroutines) {
      sourceMapSize += routine->sourceMap.map.size() * (4 * 3);
    }

    // write sourcemap
    bin.push_back(OP::SourceMap);
    vm::writeUint32(bin, bin.size(), sourceMapSize);
    address += 1 + 4 + sourceMapSize;  // OP::SourceMap + uint32 size

    unsigned int bytecodePosOffset = address;
    bytecodePosOffset +=
        subroutines.size() *
        (1 + 4 + 4 + 1);  // OP::Subroutine + uint32 name address + uint32
                          // routine address + flags
    bytecodePosOffset += 1;  // OP::Main

    for (auto&& routine : subroutines) {
      for (auto&& map : routine->sourceMap.map) {
        vm::writeUint32(bin, bin.size(), bytecodePosOffset + map.bytecodePos);
        vm::writeUint32(bin, bin.size(), map.sourcePos);
        vm::writeUint32(bin, bin.size(), map.sourceEnd);
      }
      bytecodePosOffset += routine->ops.size();
    }

    address += 1;  // OP::Main
    address += subroutines.size() *
               (1 + 4 + 4 + 1);  // OP::Subroutine + uint32 name address +
                                 // uint32 routine address + flags

    // after the storage data follows the subroutine meta-data.
    for (auto&& routine : subroutines) {
      bin.push_back(OP::Subroutine);
      vm::writeUint32(bin, bin.size(), routine->nameAddress);
      vm::writeUint32(bin, bin.size(), address);
      bin.push_back(routine->getFlags());
      address += routine->ops.size();
    }

    // after subroutine meta-data follows the actual subroutine code, which we
    // jump over. this marks the end of the header.
    bin.push_back(OP::Main);

    for (auto&& routine : subroutines) {
      if (routine->slots) {
        vm::writeUint16(routine->ops, routine->slotIP + 1, routine->slots);
      }
      bin.insert(bin.end(), routine->ops.begin(), routine->ops.end());
    }

    return string(bin.begin(), bin.end());
  }
};

class Compiler {
 public:
  Program compileSourceFile(const shared_ptr<SourceFile>& file) {
    Program program;

    handle(file.get(), program);

    program.popSubroutine();  // main

    return program;
  }

  void pushName(optionalNode<Node> name, Program& program) {
    if (!name) {
      program.pushOp(OP::Never);
      return;
    }

    if (name->kind == SyntaxKind::Identifier) {
      program.pushStringLiteral(to<Identifier>(name)->escapedText, name);
    } else {
      // computed type name like `[a]: string`
      handle(name, program);
    }
  }

  void pushFunction(OP op, optionalNode<Node> node, Program& program,
                    optionalNode<Node> withName) {
    optionalNode<Node> body = nullptr;
    optionalNode<Node> type = nullptr;
    optionalNode<NodeArray> typeParameters = nullptr;
    optionalNode<NodeArray> parameters = nullptr;
    if (auto a = to<FunctionDeclaration>(node)) {
      body = a->body;
      type = a->type;
      parameters = a->parameters;
      typeParameters = a->typeParameters;
    } else if (auto a = to<FunctionTypeNode>(node)) {
      type = a->type;
      parameters = a->parameters;
      typeParameters = a->typeParameters;
    } else if (auto a = to<MethodDeclaration>(node)) {
      body = a->body;
      type = a->type;
      parameters = a->parameters;
      typeParameters = a->typeParameters;
    } else {
      throw std::runtime_error("function type not supported");
    }

    auto pushBodyType = [&] {
      unsigned int bodyAddress;
      if (body) {
        bodyAddress = program.pushSubroutineNameLess();
        program.pushOp(OP::TypeArgument);
        handle(body, program);
        program.pushOp(OP::Loads);
        program.pushUint16(0);
        program.pushUint16(0);
        program.pushOp(OP::UnwrapInferBody);
        program.popSubroutine();
      }

      if (type) {
        handle(type, program);

        if (bodyAddress) {
          // type and body given, so we check if all `return` are valid.
          // it is moved in its own subroutine, so that the return type is
          // cached and only run once. auto checkBodyAddress =
          // program.pushSubroutineNameLess(); program.pushOp(OP::CheckBody);
          // program.pushAddress(bodyAddress);
          // program.popSubroutine();

          program.pushOp(OP::CheckBody);
          program.pushAddress(bodyAddress);
        }
      } else {
        if (bodyAddress) {
          // no type given, so we infer from body
          program.pushOp(OP::InferBody);
          program.pushAddress(bodyAddress);
        } else {
          program.pushOp(OP::Unknown);
        }
      }
    };

    if (typeParameters) {
      // when there are type parameters, FunctionDeclaration returns a
      // FunctionRef which indicates the VM that the function needs to be
      // instantiated first.

      auto functionDef = program.pushSubroutineNameLess();
      {
        unsigned int size = 0;
        for (auto param : *typeParameters) {
          handle(param, program);
        }
        program.pushSlots();

        // first comes the return type
        size++;

        pushBodyType();

        for (auto param : *parameters) {
          size++;
          handle(param, program);
        }

        pushName(withName, program);
        program.pushOp(op, reinterpret_node<Node>(node));
        program.pushUint16(size);
        program.popSubroutine();
      }

      auto inferTypes = program.pushSubroutineNameLess();
      {
        // todo implement inferring type arguments from parameters
        // https://www.typescriptlang.org/play?#code/PTAEBMFMGMBsEMBOlQDMCuA7aAXAlgPaYQECSOAPACoB8AFPAFyhUA0oARs1QJTcDcAKEEhQsSDlAFQAXlABvAF7MARCoC+QkWGhEAzpPiyS5OvKagAzOvZLVGnkNG7MBzsfBkcZi9fYFHbVAXN2gPLzoCW191QKDnfUkOcNNLaOZrONEE10kwuU9Tc2YAFhsFRFLYrVEoOCQUDGx8IjRMalBIAA8cSExwPQULAGly4foLNk5mYtBRvhYnHUTQIzlUTB8M8tnLMqywOoRkNCxcQmINgEYO7t7+wdnR9mHOnr6B0Ex0AFsOSEQE247C4Q2Y8wEQRChiuxmuWysO18+xqhxgx0aZxal0wACZbu8HmC5mM3vdPt8-gCgSwQdwFlQlsEVvBcXC8Qi-MS9tVhEcGqdmhc2pZqDSpqDeJDoatLAAGdmWOhpUBqQIy+Dy2HrTBK3Y7UFqXka+VsnVKgDalgAuuwLWprXF+ScmudWhtLDdaHQAHR+iwWqZUR3SlmexVXZXsNVCE1XbUiyP69KqhyxsNXM2JuhW22ge0qR1aZ2YoXu3X470B4N0-PBhnp3KyrMe3E5m12h3qsO4hOtnP6vMW2ZGouCE24lsVnO5ocF61jwQlwVunGWUXev0+gOBofBkOLcdhyyKy0d-NdxtuTXh82Wwd2kcaMcmyxT9czm1zh2L5eu7FtCUXpkh8jwjGM4q1lKh4akB7JAZySL2Ly2g4AAngADpABCoKsIFEnQABCBBdBQeCYKgAIsPhnxPOoNA8KhmHYbhyR3KBoB0ORlGINR7FEnRjEgOhWE4cENGDFxFFUcMjHaHo6AcIgBDoPgmAoNxVEAGKYCUuLMBapDSYgiDkQA5lQzEAIKIGZvx9JIABkwb5kZPGmZgFnWbZ9mYE5wzWq5xmWVhNl2T8Dl6Na8mKcpqnkSgVAGQAwvAsCwHMgUWgACspWGIOhqrwIW+YAPIcAAVjAOAADJ4L0iBpdFIAKUpKlqSgwwGVZmBoc1wCtXFHWrAZ2VIPAPxXFlblUc5WWpeloDEV0oBTUFPEAKKEgM0XaBaADKOBIDgM2ICFkBhb5OCBcgODoIgridEgsBoaAADuAAWfSgDgX0sN54UOe98CDKgeBdJA4AxW18XqSN+ZjY1k1ZYdx2nedl0RX581pRlAUI3lAKFSoxVZeVVW4HVDVNetALJYkjXkU5LkWgtGXLat03GVt5JRdDQ0JdMCPjcj+aowV6MA1dOOLfjOWEwVr0kyVFrk9VVMAjThnGfTuSM35oBzbTiA86B-WDe1gvQvrOCjSLa0HUdEvBVLWPXcbhty6dpsPP1RjW-ATNiHgADWKAAAavPxFK-P8iDh6ABgEBhgyvKgyk-JwkDme9eBQJg6ngGgGdWLINBfLHVF0Ho0j1YnR1oYM8CSJYQlgCJKDLWKxhUBJxIGB5Zm1pScfsNAzCabxhHqKAAD8CgAG7cIbCjj0tfc4Ig6AoPPsLMHK6gz8wWBQGDheoh3S0kd3ci99HgyT3Mc9P-f-eb+Zw+V4gY-MBwBAEOIeAmAZ7z3kEvFgR9QAn0gGfSGoBj79BgQlcAF9mJXy6JWdgAA1cut8+6P1eKA8BUwQ7MCwZA6BsCobCTQctTBoAcHGHkBaTAE1IDMAHuZa03B1DCFEDIcupAfofXIiHd6X1LjkXADnaAQDpHgGbpAUGBAp7X1oOwKg+1E5vXqtAL6gwXDSOxGleuii3aDBwNIBS+UAC0GECB6HqhcPQ7Aa7CObkEOut17qPT-r9TgjVsD6NAORVYxAsAXFcdIN6KAPrwAXigXGoB7F6EcRwcQwQ5F50UXoH0S1VJSEwC9cR31e54CbrgdAuNXroD0HA0J-sCA-AwkgcpRAfRBFILhXub0QZQLqUXOgMSviQDgUYdSb00AIDMmgFR7jJAdx4CE4guhmmtJrpgdgddHFmVYbACxf1DFOKICYy+ljQDeIepwAg-ilJAL0UojpNCsLoPocMSAjc+6cM8rg4kVAZ6v1mN8syICFAsLYcsuYHyoo8PgWgNKdT+CgGEqZMyZkASDH2tlTi1iAR2IccczAbdL50OoC8aFXz34-OMOpBJvFAWTFBcw1hEVIXvMbtwiBcLUAIsgEikAn1XqeCUcI8pP1UXot4rixA+LHHYlnkxF5pKpjssGK-YFvygGvQZbC0B4LWWhNVZy-53LeX8uAIKkgIrfpivfmiqi0rZWEoVSSkibyKXqqpWZX5WAQ6YAIG9YgOquV6pZRpYgRrYXMB5fsvlyLgD+tAFixVnc3VkqhZ8z1g9fkEEqtVPuswTWhohYa6FxrIExsRfGxNybnmpowem1VlLs1MIsMCgF20wK6rBWGtlZao3wtjea2twBXUNpVR6zt9cW1yHkKCdtBbGXP2ZSWiN-auXRrNdW6QI6x3uszVOjVPd8HGRflOkeVFi0GrXRygdla+V8LAAACQ2gAJQ2gAQg-doGQv7y42seOA0YATIDwBDgclAyAEDYj0CIjCWccAxNKWEouRh7H3HwCY2R-Rsm9CiaKh+gwPoBpCZIN6KjwN5J+B9D6Kb0E3z4lOghz8o5TqBV6z+VJv7BF-v-QBwDl3EIoYgqhcLKHIKWABi5EgfGDBUP6rCKgs6yNqRHVjvNQBdATpcx6aVemfPvTYu5QTlPwFU0-OJgxE2OpSYSqZ8Ah7CNqW8DCyBUnCj0-AAzvKghyNAOHO+THT3DATnayVgwbMEuxOwHTOc-EfQCfc-RIICn+rhj8ZuDym7ECQIDA2Oj-HhzAcwLc6gE5uLrhhPA0BwPCMgEEMGiA3ARNaA5RAr06DyeTpAFQSy-OqYOc3DpY6GOBY08x+e6mOLscHpx0ePHrkANAwJoh4JIFdcU3C5V7AADkC8ds0FRKgOZ4cLBd1oAnMpgxfX+sDSlyQ9UDEM0DgbMVfqA2bMTtILudFy5itkelSGQQbHl39Qsm51SLl4DMh9HA7A+k9LwItf4yz3JwPTk0-zkpw55M+t9ZIYqEXSHDqCc7NAE5EGKb9RKO2nt6xew967Azgeg5ueK7erjyLQA0pIKAWEiRiWWrTiASDMCEtxxI6ioSOaWa+NII5AFWj1XYBsPSO3e7YazqjgEyBqFgBB3LhZW8UDZ2p1KrnKBqezPSgGnO5HEC1ZrhFYjb08lUBEYMe3tX-gqbqfR2goBZf+yyQo3oi9YWfWqwl21kvVPgCeWANxwz1JjMTrFS2cMxKgb0T9NB-5hSwFDvW+Z0m7oPSbotFJaSMnYfkTkhVf4sTClV5WRda2Xg0jJ7WLvC3ZKhibPAPS8E2zFeJGoWsABWFUa9N7b0PrYcBT5J8lB-oOup8-UxOnRAKfP5YSgbjbySF4BbJT0QYMCIWUw1595giyff8E9QxBTEaaMvXUTMgH3sPsuoSiIWf2mKEMMIfc0X-XMO0ecRcWobfF0JvPfMUc-P5coUEQtWISEHIa8EoeCP-MfNMIAA
        // for functions with type arguments <T>fn(a: T)
        // we need a subroutine to infer them from passed arguments.
        for (auto param : *typeParameters) {
          // put TypeArgument for each type parameter on the stack
          // handle(param, program);
          // const auto p = to<TypeParameterDeclaration>(param);
          // p->constraint
          // auto &symbol = program.pushSymbol(->name->escapedText,
          // SymbolType::TypeArgument, n);
        }
        program.pushOp(OP::InferTypeArguments);
        program.popSubroutine();
      }

      program.pushOp(OP::FunctionRef, reinterpret_node<Node>(node));
      program.pushAddress(functionDef);
      program.pushAddress(inferTypes);
    } else {
      unsigned int size = 0;
      // first comes the return type
      size++;

      pushBodyType();

      for (auto param : *parameters) {
        size++;
        handle(param, program);
      }

      pushName(withName, program);
      program.pushOp(op, reinterpret_node<Node>(node));
      program.pushUint16(size);
    }
  }

  void handle(const node<Node>& node, Program& program) {
    switch (node->kind) {
      case SyntaxKind::SourceFile: {
        for (auto statement : *to<SourceFile>(node)->statements) {
          handle(statement, program);
        }
        break;
      }
      case SyntaxKind::AnyKeyword:
        program.pushOp(OP::Any, node);
        break;
      case SyntaxKind::NullKeyword:
        program.pushOp(OP::Null, node);
        break;
      case SyntaxKind::UndefinedKeyword:
        program.pushOp(OP::Undefined, node);
        break;
      case SyntaxKind::NeverKeyword:
        program.pushOp(OP::Never, node);
        break;
      case SyntaxKind::BooleanKeyword:
        program.pushOp(OP::Boolean, node);
        break;
      case SyntaxKind::StringKeyword:
        program.pushOp(OP::String, node);
        break;
      case SyntaxKind::NumberKeyword:
        program.pushOp(OP::Number, node);
        break;
      case SyntaxKind::BigIntLiteral:
        program.pushOp(OP::BigIntLiteral, node);
        program.pushStorage(to<BigIntLiteral>(node)->text);
        break;
      case SyntaxKind::NumericLiteral:
        program.pushOp(OP::NumberLiteral, node);
        program.pushStorage(to<NumericLiteral>(node)->text);
        break;
      case SyntaxKind::StringLiteral:
        program.pushOp(OP::StringLiteral, node);
        program.pushStorage(to<StringLiteral>(node)->text);
        break;
      case SyntaxKind::TrueKeyword:
        program.pushOp(OP::True, node);
        break;
      case SyntaxKind::FalseKeyword:
        program.pushOp(OP::False, node);
        break;
      case SyntaxKind::IndexedAccessType: {
        const auto n = to<IndexedAccessTypeNode>(node);
        auto literal = to<LiteralTypeNode>(n->indexType);

        if (literal) {
          auto stringLiteral = to<StringLiteral>(literal->literal);
          if (stringLiteral && stringLiteral->text == "length") {
            handle(n->objectType, program);
            program.pushOp(OP::Length, node);
            break;
          }
        }

        handle(n->objectType, program);
        handle(n->indexType, program);
        program.pushOp(OP::IndexAccess, node);
        break;
      }
      case SyntaxKind::LiteralType: {
        const auto n = to<LiteralTypeNode>(node);
        handle(n->literal, program);
        break;
      }
      case SyntaxKind::TemplateLiteralType: {
        auto t = to<TemplateLiteralTypeNode>(node);

        unsigned int size = 0;
        if (t->head->rawText && !t->head->rawText->empty()) {
          size++;
          program.pushOp(OP::StringLiteral, t->head);
          program.pushStorage(*t->head->rawText);
        }

        for (auto sub : *t->templateSpans) {
          auto span = to<TemplateLiteralTypeSpan>(sub);
          size++;
          handle(to<TemplateLiteralTypeSpan>(span)->type, program);

          if (auto a = to<TemplateMiddle>(span->literal)) {
            if (a->rawText && !a->rawText->empty()) {
              size++;
              program.pushOp(OP::StringLiteral, sub);
              program.pushStorage(a->rawText ? *a->rawText : "");
            }
          } else if (auto a = to<TemplateTail>(span->literal)) {
            if (a->rawText && !a->rawText->empty()) {
              size++;
              program.pushOp(OP::StringLiteral, a);
              program.pushStorage(a->rawText ? *a->rawText : "");
            }
          }
        }

        program.pushOp(OP::TemplateLiteral, node);
        program.pushUint16(size);

        break;
      }
      case SyntaxKind::UnionType: {
        const auto n = to<UnionTypeNode>(node);
        unsigned int size = 0;
        for (auto s : *n->types) {
          size++;
          handle(s, program);
        }

        program.pushOp(OP::Union, node);
        program.pushUint16(size);
        break;
      }
      case SyntaxKind::TypeReference: {
        // todo: search in symbol table and get address
        //                    debug("type reference {}",
        //                    to<TypeReferenceNode>(node)->typeName->to<Identifier>().escapedText);
        //                    program.pushOp(OP::Number);
        const auto n = to<TypeReferenceNode>(node);
        const auto name = to<Identifier>(n->typeName)->escapedText;
        auto foundSymbol = program.findSymbol(name);
        if (!foundSymbol.symbol) {
          program.pushOp(OP::Never, n->typeName);
          program.pushError(ErrorCode::CannotFind, n->typeName);
        } else {
          if (foundSymbol.symbol->type == SymbolType::TypeArgument ||
              foundSymbol.symbol->type == SymbolType::TypeVariable) {
            program.pushOp(OP::Loads, n->typeName);
            program.pushSymbolAddress(foundSymbol);
            if (foundSymbol.symbol->type == SymbolType::TypeArgument) {
              program.registerTypeArgumentUsage(foundSymbol.symbol);
            }
          } else {
            if (n->typeArguments) {
              for (auto p : *n->typeArguments) {
                handle(p, program);
              }
            }
            program.pushOp(OP::Call, n->typeName);
            if (!foundSymbol.symbol->routine) {
              throw runtime_error(
                  "Reference is not a reference to a existing routine.");
            }
            program.pushAddress(foundSymbol.symbol->routine->index);
            if (n->typeArguments) {
              program.pushUint16(n->typeArguments->length());
            } else {
              program.pushUint16(0);
            }
          }
        }
        break;
      }
      case SyntaxKind::TypeAliasDeclaration: {
        const auto n = to<TypeAliasDeclaration>(node);

        auto& symbol = program.pushSymbolForRoutine(
            n->name->escapedText, SymbolType::Type,
            n);  // move this to earlier symbol-scan round
        if (symbol.declarations > 1) {
          // todo: for functions/variable embed an error that symbol was
          // declared twice in the same scope
        } else {
          // populate routine
          program.pushSubroutine(symbol);
          // in symbol subroutines we block TailCalls because want to store the
          // result on the routine but only if it has no typeParameters
          if (!n->typeParameters || n->typeParameters->length() == 0) {
            program.blockTailCall();
          }

          if (n->typeParameters) {
            for (auto p : *n->typeParameters) {
              handle(p, program);
            }
          }
          program.pushSlots();

          handle(n->type, program);
          program.popSubroutine();
        }
        break;
      }
      case SyntaxKind::Parameter: {
        const auto n = to<ParameterDeclaration>(node);
        if (n->type) {
          handle(n->type, program);
        } else {
          program.pushOp(OP::Unknown, node);
        }
        program.pushOp(OP::Parameter, node);
        if (auto id = to<Identifier>(n->name)) {
          program.pushStorage(id->escapedText);
        } else {
          program.pushStorage("");
        }
        if (n->questionToken)
          program.pushOp(OP::Optional, n->questionToken);
        if (n->initializer) {
          handle(n->initializer, program);
          program.pushOp(OP::Initializer, n->initializer);
        }
        break;
      }
      case SyntaxKind::TypeParameter: {
        const auto n = to<TypeParameterDeclaration>(node);
        auto& symbol = program.pushSymbol(n->name->escapedText,
                                          SymbolType::TypeArgument, n);
        auto subroutine = program.currentSubroutine();
        if (n->defaultType) {
          program.pushSubroutineNameLess();
          program.pushSlots();
          handle(n->defaultType, program);
          auto routine = program.popSubroutine();
          program.pushOp(OP::TypeArgumentDefault, n->name);
          program.pushAddress(routine->index);
        } else {
          program.pushOp(OP::TypeArgument, n->name);
        }
        if (n->constraint) {
          handle(n->constraint, program);
          program.pushOp(OP::TypeArgumentConstraint);
        }
        break;
      }
      case SyntaxKind::FunctionDeclaration: {
        const auto n = to<FunctionDeclaration>(node);
        if (const auto id = to<Identifier>(n->name)) {
          auto& symbol = program.pushSymbolForRoutine(
              id->escapedText, SymbolType::Function,
              id);  // move this to earlier symbol-scan round
          if (symbol.declarations > 1) {
            // todo: embed error since function is declared twice
          } else {
            program.pushSubroutine(symbol);
            program.pushSlots();
            pushFunction(OP::Function, n, program, n->name);
            program.popSubroutine();
          }
        } else {
          debug("No identifier in name");
        }

        break;
      }
      case SyntaxKind::FunctionType: {
        const auto n = to<FunctionTypeNode>(node);
        pushFunction(OP::Function, n, program, n->name);
        break;
      }
      case SyntaxKind::Identifier: {
        const auto n = to<Identifier>(node);
        auto foundSymbol = program.findSymbol(n->escapedText);
        if (!foundSymbol.symbol) {
          program.pushOp(OP::Never, n);
          program.pushError(ErrorCode::CannotFind, n);
        } else {
          if (foundSymbol.symbol->type == SymbolType::TypeArgument ||
              foundSymbol.symbol->type == SymbolType::TypeVariable) {
            program.pushOp(OP::Loads, node);
            program.pushSymbolAddress(foundSymbol);
          } else {
            if (n->typeArguments) {
              for (auto p : *n->typeArguments) {
                handle(p, program);
              }
            }
            program.pushOp(OP::Call, node);
            if (!foundSymbol.symbol->routine) {
              throw runtime_error(
                  "Reference is not a reference to a existing routine.");
            }
            program.pushAddress(foundSymbol.symbol->routine->index);
            if (n->typeArguments) {
              program.pushUint16(n->typeArguments->length());
            } else {
              program.pushUint16(0);
            }
          }
        }
        break;
      }
      case SyntaxKind::PropertyAssignment: {
        const auto n = to<PropertyAssignment>(node);
        if (n->initializer) {
          handle(n->initializer, program);
        } else {
          program.pushOp(OP::Any, n);
        }
        pushName(n->name, program);
        program.pushOp(OP::PropertySignature, n->name);
        if (n->questionToken)
          program.pushOp(OP::Optional);
        if (hasModifier(n, SyntaxKind::ReadonlyKeyword))
          program.pushOp(OP::Readonly);
        if (hasModifier(n, SyntaxKind::StaticKeyword))
          program.pushOp(OP::Static);
        break;
      }
      case SyntaxKind::PropertySignature: {
        const auto n = to<PropertySignature>(node);
        if (n->type) {
          handle(n->type, program);
        } else {
          program.pushOp(OP::Any);
        }
        pushName(n->name, program);
        program.pushOp(OP::PropertySignature, node);
        if (n->questionToken)
          program.pushOp(OP::Optional);
        if (hasModifier(n, SyntaxKind::ReadonlyKeyword))
          program.pushOp(OP::Readonly);
        break;
      }
      case SyntaxKind::InterfaceDeclaration: {
        const auto n = to<InterfaceDeclaration>(node);
        unsigned int size = 0;

        // first all extend expressions
        if (n->heritageClauses) {
          for (auto node : *n->heritageClauses) {
            auto heritage = to<HeritageClause>(node);
            if (heritage->token == SyntaxKind::ExtendsKeyword) {
              for (auto extendType : *heritage->types) {
                size++;
                handle(extendType, program);
              }
            }
          }
        }

        for (auto member : *n->members) {
          size++;
          handle(member, program);
        }

        program.pushOp(OP::ObjectLiteral, n->name);
        program.pushUint16(size);
        break;
      }
      case SyntaxKind::TypeLiteral: {
        const auto n = to<TypeLiteralNode>(node);
        unsigned int size = 0;

        for (auto member : *n->members) {
          size++;
          handle(member, program);
        }

        program.pushOp(OP::ObjectLiteral, node);
        program.pushUint16(size);
        break;
      }
      case SyntaxKind::IfStatement: {
        const auto n = to<IfStatement>(node);
        // todo handle n->expression, necessary for type narrowing
        handle(n->thenStatement, program);
        if (n->elseStatement) {
          handle(n->elseStatement, program);
        }
        break;
      }
      case SyntaxKind::ParenthesizedExpression: {
        const auto n = to<ParenthesizedExpression>(node);
        handle(n->expression, program);
        break;
      }
      case SyntaxKind::ExpressionWithTypeArguments: {
        const auto n = to<ExpressionWithTypeArguments>(node);
        auto typeArgumentsCount =
            n->typeArguments ? n->typeArguments->length() : 0;
        if (n->typeArguments) {
          for (auto sub : *n->typeArguments)
            handle(sub, program);
        }

        handle(n->expression, program);

        if (n->typeArguments) {
          program.pushOp(OP::Instantiate, node);
          program.pushUint16(typeArgumentsCount);
        }
        break;
      }
      case SyntaxKind::ObjectLiteralExpression: {
        const auto n = to<ObjectLiteralExpression>(node);
        unsigned int size = 0;
        for (auto sub : *n->properties) {
          size++;
          handle(sub, program);
        }
        program.pushOp(OP::ObjectLiteral, node);
        program.pushUint16(size);
        break;
      }
      case SyntaxKind::NewExpression: {
        const auto n = to<NewExpression>(node);

        auto argumentsCount = n->arguments ? n->arguments->length() : 0;
        if (n->arguments)
          for (auto sub : *n->arguments)
            handle(sub, program);

        auto typeArgumentsCount =
            n->typeArguments ? n->typeArguments->length() : 0;
        if (n->typeArguments) {
          for (auto sub : *n->typeArguments)
            handle(sub, program);
        }
        handle(n->expression, program);

        if (n->typeArguments) {
          program.pushOp(OP::Instantiate, node);
          program.pushUint16(typeArgumentsCount);
        } else if (argumentsCount) {
          program.pushOp(OP::StartInferTypeArguments, node);
          program.pushUint16(argumentsCount);
        }

        program.pushOp(OP::New, node);
        program.pushUint16(argumentsCount);
        break;
      }
      case SyntaxKind::CallExpression: {
        const auto n = to<CallExpression>(node);
        auto argumentsCount = n->arguments->length();
        for (auto sub : *n->arguments)
          handle(sub, program);

        auto typeArgumentsCount =
            n->typeArguments ? n->typeArguments->length() : 0;
        if (n->typeArguments) {
          for (auto sub : *n->typeArguments)
            handle(sub, program);
        }

        handle(n->expression, program);

        if (n->typeArguments) {
          program.pushOp(OP::Instantiate, node);
          program.pushUint16(typeArgumentsCount);
        } else {
          program.pushOp(OP::StartInferTypeArguments, node);
          program.pushUint16(argumentsCount);
        }

        program.pushOp(OP::CallExpression, node);
        program.pushUint16(argumentsCount);

        break;
      }
      case SyntaxKind::ReturnStatement: {
        const auto n = to<ReturnStatement>(node);
        handle(n->expression, program);
        program.pushOp(OP::ReturnStatement);
        break;
      }
      case SyntaxKind::Block: {
        const auto n = to<Block>(node);
        for (auto statement : *n->statements) {
          handle(statement, program);
        }
        break;
      }
      case SyntaxKind::ExpressionStatement: {
        const auto n = to<ExpressionStatement>(node);
        handle(n->expression, program);

        auto expressionPutsTypeOnStack = true;
        switch (n->expression->kind) {
          case SyntaxKind::VariableDeclarationList: {
            expressionPutsTypeOnStack = false;
            break;
          }
        }
        if (expressionPutsTypeOnStack && !program.expressionResult) {
          // expression statements that are not used need to be removed from the
          // stack. .e.g `true;` or `doIt();`
          program.pushOp(OP::Pop);
        }
        break;
      }
      case SyntaxKind::ConditionalExpression: {
        const auto n = to<ConditionalExpression>(node);
        // it seems TS does not care about the condition. the result is always a
        // union of false/true branch. we could improve that though to make sure
        // that const-expressions are handled
        handle(n->whenFalse, program);
        handle(n->whenTrue, program);
        program.pushOp(OP::Union, node);
        program.pushUint16(2);
        break;
      }
      case SyntaxKind::ConditionalType: {
        const auto n = to<ConditionalTypeNode>(node);
        // Depending on whether this a distributive conditional type or not, the
        // whole conditional type has to be moved to its own function, so it can
        // be executed for each union member.
        //  - the `checkType` is a simple identifier (just `T`, no `[T]`, no `T
        //  | x`, no `{a: T}`, etc)
        //                    let distributiveOverIdentifier: Identifier |
        //                    undefined =
        //                    isTypeReferenceNode(narrowed.checkType) &&
        //                    isIdentifier(narrowed.checkType.typeName) ?
        //                    narrowed.checkType.typeName : undefined;
        optionalNode<Identifier> distributiveOverIdentifier =
            isTypeReferenceNode(n->checkType) &&
                    isIdentifier(to<TypeReferenceNode>(n->checkType)->typeName)
                ? to<Identifier>(to<TypeReferenceNode>(n->checkType)->typeName)
                : nullptr;

        program.pushSection();
        auto symbolCheckpoint = program.createSymbolCheckout();

        unsigned int distributeJumpIp = 0;
        if (distributiveOverIdentifier) {
          // program.pushOp(OP::TypeVariable, distributiveOverIdentifier);
          handle(n->checkType, program);  // LOADS the input type onto the
                                          // stack. Distribute pops it.

          // in Distribute we block tail calls as the section is called multiple
          // times
          program.blockTailCall();

          // Distribute creates implicit TypeVariable on the stack and populates
          // it todo: we have to move it to the beginning of the subroutine
          auto symbol = program.pushSymbol(
              distributiveOverIdentifier->escapedText, SymbolType::TypeVariable,
              distributiveOverIdentifier);

          program.pushOp(OP::Distribute);
          distributeJumpIp = program.ip();
          program.pushUint16(symbol.index);
          program.pushAddress(0);
        }

        auto symbolInferCheckpoint = program.createSymbolCheckout();
        // checkType and trueType share symbols (from infer)
        handle(n->checkType, program);
        handle(n->extendsType, program);
        program.pushOp(OP::Extends, n);

        program.pushOp(OP::JumpCondition);
        auto relativeTo = program.ip();
        auto falseJumpAddressIp = program.ip();
        program.pushAddress(0);  // trueProgram is directly behind it

        program.pushSection();
        handle(n->trueType, program);
        program.restoreSymbolCheckout(symbolInferCheckpoint);
        program.popSection();

        program.ignoreNextSectionOP();
        program.pushOp(OP::Jump);
        auto trueJumpAddressIp = program.ip();
        program.pushAddress(0);

        auto falseProgram = program.ip() + 1;
        program.pushSection();
        handle(n->falseType, program);
        program.popSection();
        auto falseEndIp = program.ip();

        program.pushInt32Address(falseProgram - relativeTo, falseJumpAddressIp);
        program.pushInt32Address(falseEndIp - trueJumpAddressIp + 1,
                                 trueJumpAddressIp);

        if (distributiveOverIdentifier) {
          // change the address from OP::Distribute to jump to the end of all
          // its expressions
          program.pushAddress(falseEndIp - distributeJumpIp + 6,
                              distributeJumpIp + 2);

          program.ignoreNextSectionOP();
          program.pushOp(OP::Jump);
          program.pushInt32Address(-(program.ip() - distributeJumpIp));
        } else {
          program.ignoreNextSectionOP();
        }

        program.popSection();
        program.restoreSymbolCheckout(symbolCheckpoint);

        //                    debug("ConditionalType {}",
        //                    !!distributiveOverIdentifier);
        break;
      }
      case SyntaxKind::ParenthesizedType: {
        handle(to<ParenthesizedTypeNode>(node)->type, program);
        break;
      }
      case SyntaxKind::RestType: {
        auto n = to<RestTypeNode>(node);
        handle(n->type, program);
        if (n->type->kind == SyntaxKind::TypeReference) {
          // we need to know which symbol is referenced
        }
        program.pushOp(OP::Rest, node);
        break;
      }
        //                case SyntaxKind::OptionalType: {
        //
        //                    break;
        //                }
        // value inference
      case SyntaxKind::ArrayLiteralExpression: {
        unsigned int size = 0;
        for (auto v : *to<ArrayLiteralExpression>(node)->elements) {
          size++;
          handle(v, program);
          program.pushOp(OP::TupleMember, v);
        }
        program.pushOp(OP::Tuple, node);
        program.pushUint16(size);
        // todo: handle `as const`, widen if not const
        break;
      }
      case SyntaxKind::PropertyAccessExpression: {
        // e.g. object.method
        program.pushKeepExpressionResult();
        auto n = to<PropertyAccessExpression>(node);
        handle(n->expression, program);
        // to avoid resolving Identifier to a symbol, we handle it manually
        pushName(n->name, program);
        program.pushOp(OP::PropertyAccess, node);
        program.popKeepExpressionResult();
        break;
      }
      case SyntaxKind::ClassExpression: {
        // todo: class expression, e.g. `const a = class {}`
        throw std::runtime_error("class expression not supported");
        break;
      }
      case SyntaxKind::ClassDeclaration: {
        auto n = to<ClassDeclaration>(node);

        if (!n->name) {
          throw std::runtime_error("class without name not supported");
        }

        auto& symbol = program.pushSymbolForRoutine(
            n->name->escapedText, SymbolType::Class,
            n);  // move this to earlier symbol-scan round
        if (symbol.declarations > 1) {
          // todo: for functions/variable embed an error that symbol was
          // declared twice in the same scope
          throw std::runtime_error("Nope");
        } else {
          // populate routine
          program.pushSubroutine(symbol);
          program.blockTailCall();

          if (n->typeParameters) {
            auto subroutineIndex = program.pushSubroutineNameLess();
            program.blockTailCall();
            for (auto p : *n->typeParameters) {
              handle(p, program);
            }

            program.pushSlots();

            unsigned int size = 0;
            for (auto member : *n->members) {
              size++;
              handle(member, program);
            }
            program.pushOp(OP::Class, node);
            program.pushUint16(size);
            program.popSubroutine();

            // unsigned int constructorInfer = 0;
            // for (auto member: *n->members) {
            //     //could be multiple constructors with constructor signature
            //     if (member->kind == SyntaxKind::Constructor) {
            //         //todo: How do we encode it?
            //     }
            // }
            auto inferTypes = program.pushSubroutineNameLess();
            {
              // for functions with type arguments <T>fn(a: T)
              // we need a subroutine to infer them from passed arguments.
              for (auto param : *n->typeParameters) {
                // put TypeArgument for each type parameter on the stack
                handle(param, program);
                // const auto p = to<TypeParameterDeclaration>(param);
                // p->constraint
                // auto &symbol = program.pushSymbol(->name->escapedText,
                // SymbolType::TypeArgument, n);
              }
              program.pushOp(OP::InferTypeArguments);
              program.popSubroutine();
            }

            program.pushOp(OP::ClassRef, reinterpret_node<Node>(node));
            program.pushAddress(subroutineIndex);
            program.pushAddress(inferTypes);
          } else {
            program.pushSlots();

            unsigned int size = 0;
            for (auto member : *n->members) {
              size++;
              handle(member, program);
            }
            program.pushOp(OP::Class, node);
            program.pushUint16(size);
          }
          program.popSubroutine();
        }
        break;
      }
      case SyntaxKind::MethodDeclaration: {
        auto n = to<MethodDeclaration>(node);

        pushFunction(OP::Method, n, program, n->name);

        if (n->questionToken)
          program.pushOp(OP::Optional);
        if (hasModifier(n, SyntaxKind::ReadonlyKeyword))
          program.pushOp(OP::Readonly);
        if (hasModifier(n, SyntaxKind::StaticKeyword))
          program.pushOp(OP::Static);
        break;
      }
      case SyntaxKind::ArrayType: {
        auto n = to<ArrayTypeNode>(node);
        handle(n->elementType, program);
        program.pushOp(OP::Array, node);
        break;
      }
      case SyntaxKind::TupleType: {
        unsigned int size = 0;
        auto n = to<TupleTypeNode>(node);
        for (auto e : *n->elements) {
          if (auto tm = to<NamedTupleMember>(e)) {
            size++;
            handle(tm->type, program);
            if (tm->dotDotDotToken) {
              program.pushOp(OP::Rest);
            }
            program.pushOp(OP::TupleMember, tm);
            if (tm->questionToken)
              program.pushOp(OP::Optional);
          } else if (auto ot = to<OptionalTypeNode>(e)) {
            size++;
            handle(ot->type, program);
            program.pushOp(OP::TupleMember, ot);
            program.pushOp(OP::Optional);
          } else {
            size++;
            handle(e, program);
            program.pushOp(OP::TupleMember, e);
          }
        }
        program.pushOp(OP::Tuple, node);
        program.pushUint16(size);
        break;
      }
      case SyntaxKind::BinaryExpression: {
        // e.g. `var = ''`, `foo.bar = 1`
        auto n = to<BinaryExpression>(node);
        switch (n->operatorToken->kind) {
          case SyntaxKind::EqualsToken: {
            if (n->left->kind == SyntaxKind::Identifier) {
              const auto name = to<Identifier>(n->left)->escapedText;
              auto foundSymbol = program.findSymbol(name);
              if (!foundSymbol.symbol) {
                program.pushOp(OP::Never, n->left);
                program.pushError(ErrorCode::CannotFind, n->left);
              } else {
                if (!foundSymbol.symbol->routine)
                  throw runtime_error("Symbol has no routine");

                handle(n->right, program);
                program.pushOp(OP::Set, n->operatorToken);
                program.pushAddress(foundSymbol.symbol->routine->index);
              }
            } else {
              throw runtime_error(
                  "BinaryExpression left only Identifier implemented");
            }

            break;
          }
          default:
            throw runtime_error(
                fmt::format("BinaryExpression Operator token {} not handled",
                            n->operatorToken->kind));
        }
        break;
      }
      case SyntaxKind::VariableStatement: {
        for (auto s :
             *to<VariableStatement>(node)->declarationList->declarations) {
          handle(s, program);
        }
        break;
      }
      case SyntaxKind::VariableDeclaration: {
        const auto n = to<VariableDeclaration>(node);
        if (const auto id = to<Identifier>(n->name)) {
          auto& symbol = program.pushSymbolForRoutine(
              id->escapedText, SymbolType::Variable,
              id);  // move this to earlier symbol-scan round
          if (symbol.declarations > 1) {
            // todo: embed error since variable is declared twice
          } else {
            if (n->type) {
              const auto subroutineIndex = program.pushSubroutine(symbol);
              // in symbol subroutines we block TailCalls because want to store
              // the result on the routine
              program.blockTailCall();
              program.pushSlots();

              //                                program.pushSourceMap(id);
              handle(n->type, program);
              program.popSubroutine();
              if (n->initializer) {
                handle(n->initializer, program);
                program.pushOp(OP::Call);
                program.pushAddress(subroutineIndex);
                program.pushUint16(0);
                program.pushOp(OP::Assign, n->name);
              }
            } else {
              auto subroutineIndex = program.pushSubroutine(symbol);
              program.pushSlots();

              if (n->initializer) {
                handle(n->initializer, program);
                // let var1 = true; //boolean
                // const var1 = true; //true
                if (!n->isConst()) {
                  program.pushOp(OP::Widen);
                }
                program.popSubroutine();

                if (!n->isConst()) {
                  // set current narrowed to initializer
                  handle(n->initializer, program);
                  program.pushOp(OP::Set);
                  program.pushAddress(subroutineIndex);
                }
              } else {
                program.pushOp(OP::Any);
                program.popSubroutine();
              }
            }
            if (symbol.routine) {
              program.pushOp(OP::SelfCheck);
              program.pushAddress(symbol.routine->index);
            }
          }
        } else {
          debug("No identifier in name");
        }
        break;
      }
      default: {
        debug("Node {} not handled", node->kind);
      }
    }
  }
};
}  // namespace tscpp::checker

#endif  // TSCPP_TYPECHECKER_COMPILER_H