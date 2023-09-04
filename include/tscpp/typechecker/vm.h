#ifndef TSCPP_TYPECHECKER_VM_H
#define TSCPP_TYPECHECKER_VM_H

#include <stdio.h>

#include <array>
#include <memory>
#include <span>
#include <string>

#include "tscpp/base/core.h"
#include "tscpp/typechecker/instructions.h"
#include "tscpp/typechecker/module.h"
#include "tscpp/typechecker/types.h"
#include "tscpp/typechecker/io_helper.h"
#include "tscpp/utils/pool_array.h"
#include "tscpp/utils/pool_single.h"

namespace tscpp::vm {
using instructions::OP;
using std::string_view;

//    constexpr auto memoryDefault = 4096 * 10;

//    struct TypeMemoryPool2 {
//        MemoryPool<Type, memoryDefault> unknown;
//        MemoryPool<TypeNever, memoryDefault> never;
//        MemoryPool<TypeAny, memoryDefault> any;
//        MemoryPool<TypeLiteral, memoryDefault> literal;
//        MemoryPool<TypeObjectLiteral, memoryDefault> objectLiteral;
//        MemoryPool<TypeUnion, memoryDefault> unions;
//        MemoryPool<TypeTuple, memoryDefault> tuple;
//        MemoryPool<TypeTupleMember, memoryDefault> tupleMember;
//        MemoryPool<TypePropertySignature, memoryDefault> propertySignature;
//    };

constexpr auto poolSize = 10000;
inline PoolSingle<Type, poolSize> pool;
inline PoolSingle<TypeRef, poolSize> poolRef;
inline PoolArray<TypeRef, poolSize> poolRefs;

// The stack does not own Type
inline std::array<Type*, 4069 * 10> stack;
inline unsigned int sp = 0;

struct LoopHelper {
  TypeRef* current = nullptr;
  unsigned int ip = 0;
  unsigned int startSP = 0;
  unsigned int var1 = 0;
  LoopHelper* previous = nullptr;

  void set(unsigned int var1, TypeRef* typeRef) {
    this->var1 = var1;
    current = typeRef;
  }

  bool next() {
    if (!current)
      return false;
    stack[var1] = current->type;
    current = current->next;
    return true;
  }
};

enum SubroutineFlag : uint16_t {
  InferBody = 1 << 0,
};

/**
 * For each active subroutine this object is created.
 */
struct ActiveSubroutine {
  Module* module;
  ModuleSubroutine* subroutine;
  unsigned int ip = 0;  // current instruction pointer
  unsigned int depth = 0;

  unsigned int initialSp = 0;  // initial stack pointer
  // the amount of registered variable slots on the stack. will be subtracted
  // when doing popFrame() type arguments of type functions and variables like
  // for mapped types
  unsigned int variables = 0;
  vector<unsigned int> variableIPs;  // only used when stepper is active
  uint16_t typeArguments = 0;

  /** @see SubroutineFlag */
  uint16_t flags = 0;
  LoopHelper* loop = nullptr;

  LoopHelper* createLoop(unsigned int var1, TypeRef* type);
  LoopHelper* createEmptyLoop();

  void popLoop();

  unsigned int size() { return sp - initialSp; }

  OP op() { return (OP)module->bin[ip]; }

  std::span<Type*> pop(unsigned int size) {
    sp -= size;
    return {stack.data() + sp, size};
  }
  uint32_t parseUint32() {
    auto val = vm::readUint32(module->bin, ip + 1);
    ip += 4;
    return val;
  }

  bool isMain() { return subroutine->main; }

  int32_t parseInt32() {
    auto val = vm::readInt32(module->bin, ip + 1);
    ip += 4;
    return val;
  }

  uint16_t parseUint16() {
    auto val = vm::readUint16(module->bin, ip + 1);
    ip += 2;
    return val;
  }
};

template <class T, int Size>
class StackPool {
 private:
  std::array<T, Size> values;
  unsigned int i;

 public:
  T* at(unsigned int pos) { return &values[pos]; }

  T* front() { return &values[i]; }

  unsigned int index() { return i; }

  unsigned int size() { return i + 1; }

  T* reset() {
    i = 0;
    return &values[0];
  }

  T* push() {
    if (i >= Size) {
      throw std::runtime_error("Stack overflow");
    }
    return &values[++i];
  }

  T* pop() {
    if (i == 0) {
      throw std::runtime_error("Popped out of stack");
    }
    return &values[--i];
  }
};

constexpr auto stackSize = 1024;
// aka frames
inline StackPool<ActiveSubroutine, stackSize> activeSubroutines;
inline StackPool<LoopHelper, stackSize> loops;

inline bool stepper = false;
inline ActiveSubroutine* subroutine = nullptr;

void process();

void clear(shared_ptr<tscpp::vm::Module>& module);
void prepare(shared_ptr<tscpp::vm::Module>& module);
void drop(Type* type);
void drop(std::span<TypeRef>* types);
void gc(std::span<TypeRef>* types);
void gc(Type* type);
void gcFlush();
// Garbage collect whatever is left on the stack
void gcStack();
void gcStackAndFlush();

Type* allocate(TypeKind kind, uint64_t hash = 0);
std::span<TypeRef> allocateRefs(unsigned int size);

void addHashChild(Type* type, Type* child, unsigned int size);

std::span<Type*> popFrame();

static void run(shared_ptr<Module> module) {
  //        profiler.clear();
  //        pool = MemoryPool<Type, poolSize>();
  //        poolRef = MemoryPool<TypeRef, poolSize>();
  pool.clear();
  poolRef.clear();
  poolRefs.clear();

  sp = 0;
  loops.reset();

  prepare(module);
  process();
}

void call(shared_ptr<Module>& module, unsigned int index = 0,
          unsigned int arguments = 0);

struct CStack {
  vector<Type*> iterator;
  unsigned int i;
  unsigned int round;
};

class CartesianProduct {
  vector<CStack> stack;

 public:
  Type* current(CStack& s) { return s.iterator[s.i]; }

  bool next(CStack& s) {
    return (++s.i == s.iterator.size()) ? (s.i = 0, false) : true;
  }

  vector<Type*> toGroup(Type* type) {
    if (type->kind == TypeKind::Boolean) {
      return {allocate(TypeKind::Literal)->setFlag(TypeFlag::True),
              allocate(TypeKind::Literal)->setFlag(TypeFlag::False)};
    } else if (type->kind == TypeKind::Null) {
      return {allocate(TypeKind::Literal)
                  ->setLiteral(TypeFlag::StringLiteral, "null")};
    } else if (type->kind == TypeKind::Undefined) {
      return {allocate(TypeKind::Literal)
                  ->setLiteral(TypeFlag::StringLiteral, "undefined")};
      // } else if (type->kind == TypeKind::templateLiteral) {
      // //     //todo: this is wrong
      // //     return type.types;
      //     const result: Type[] = [];
      //     for (const s of type.types) {
      //         const g = this.toGroup(s);
      //         result.push(...g);
      //     }
      //
      //     return result;
    } else if (type->kind == TypeKind::Union) {
      vector<Type*> result;
      auto current = (TypeRef*)type->type;
      while (current) {
        auto g = toGroup(current->type);
        for (auto&& s : g)
          result.push_back(s);
        current = current->next;
      }

      return result;
    } else {
      return {type};
    }
  }

  void add(Type* item) {
    stack.push_back({.iterator = toGroup(item), .i = 0, .round = 0});
  }

  vector<vector<Type*>> calculate() {
    vector<vector<Type*>> result;

  outer:
    while (true) {
      vector<Type*> row;
      for (auto&& s : stack) {
        auto item = current(s);
        if (item->kind == TypeKind::TemplateLiteral) {
          auto current = (TypeRef*)item->type;
          while (current) {
            row.push_back(current->type);
            current = current->next;
          }
        } else {
          row.push_back(item);
        }
      }
      result.push_back(row);

      for (unsigned int i = stack.size() - 1; i >= 0; i--) {
        auto active = next(stack[i]);
        // when that i stack is active, continue in main loop
        if (active)
          goto outer;

        // i stack was rewinded. If it's the first, it means we are done
        if (i == 0) {
          goto done;
        }
      }
      break;
    }

  done:
    return result;
  }
};

}  // namespace tscpp::vm

#endif  // TSCPP_TYPECHECKER_VM_H