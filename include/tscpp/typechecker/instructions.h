#ifndef TSCPP_TYPECHECKER_INSTRUCTIONS_H
#define TSCPP_TYPECHECKER_INSTRUCTIONS_H

#include <fmt/core.h>

#include "tscpp/utils/enum.h"

namespace tscpp::instructions {
enum OP {
  Noop,
  Jump,  // arbitrary jump, used at the beginning to jump over storage-data
         // (storage-data's addresses are constant)
  Halt,
  SourceMap,  // one parameter (size uint32). all subsequent bytes withing the
              // given size is a map op:pos:end, each uint32
  Main,  // marks end of meta-data section (subroutine metadata + storage data).
         // after this the body section with all subroutine ops follow.

  Never,
  Any,
  Unknown,
  Void,  // void is reserved word
  Object,

  String,
  Number,
  Boolean,
  BigInt,

  Symbol,
  Null,
  Undefined,

  StringLiteral,
  NumberLiteral,
  BigIntLiteral,
  True,
  False,

  Function,
  FunctionRef,  // one parameter, the index of the subroutine of the function
                // that needs to be instantiated
  ClassRef,

  Method,
  MethodSignature,

  Parameter,
  Initializer,

  Property,
  PropertySignature,

  Class,
  ObjectLiteral,
  IndexSignature,
  PropertyAccess,

  Array,
  Tuple,
  TupleMember,
  TupleNamedMember,  // has one parameter, the name in the storage

  Optional,
  Readonly,
  Static,
  Rest,
  RestReuse,  // in expressions like [...T, x] indicates that T can be stolen
              // instead of copied

  Union,
  Intersection,

  Extends,        // expected 2 entries on the stack
  Condition,      // expected 3 entries on the stack
  JumpCondition,  // expected 1 entry on the stack + two uint16 parameters

  CallExpression,  // JS call expression, with 1 parameter (amount of
                   // parameters)
  Instantiate,  // instantiates a type on the stack (FunctionRef for example),
                // ExpressionWithTypeArguments
  StartInferTypeArguments,  // calling generic function/class with only value
                            // arguments, infer type arguments from it
  InferTypeArguments,
  New,

  /**
   * Reserved new stack entries to be used as type variables.
   *
   * 1 parameter indicating how many stack entries will be reserved.
   */
  Slots,

  /**
   * Self checks an expression, like variable, class, interface, type, etc.
   * TypeScript checks types even if they are never used. This SelfCheck makes
   * sure all expression are visited at least once in main.
   */
  SelfCheck,

  ///**
  // * Stack parameter. For each JS variable, JS function, as well as type
  // variables (mapped-type variable for example).
  // *
  // * Parameters:
  // *  1. address on initial stack frame, which should contain its name as a
  // string.
  // *  3. modifier: const
  // *  2. position in source code. necessary to determine if a reference is
  // made to a const symbol before it was defined.
  // */
  // Var,

  /**
   * Makes sure that in the current variable slot is a type placed if nothing
   * was provided as parameter.
   *
   * For each type argument like here `T` a TypeArgument OP is generated.
   * Different to Var OP since Var does reserve an entry on the stack,
   * whereas TypeArgument ensures there is a stack entry if not already provided
   * via call parameters..
   * ```typescript
   * type A<T> = T;
   * ```
   */
  TypeArgument,
  TypeArgumentDefault,  // one parameter with the address of the subroutine of
                        // the default value

  TypeArgumentConstraint,  // expects an entry (the constraint) on the stack

  TemplateLiteral,

  IndexAccess,
  Length,
  KeyOf,
  Infer,
  TypeOf,
  Widen,  // literal to widened type, true -> boolean, '' => string, 32 =>
          // number, etc

  /**
   * Reserves a type variable on the stack, which contains a type object.
   * Unknown as default.
   *
   * The address of it is known in the program and referenced directly.
   */
  TypeVar,
  Loads,  // LOAD from stack. pushes to the stack a referenced type in the
          // stack. has 2 parameters: <frame> <index>, frame is a negative
          // offset to the frame, and index the index of the stack entry withing
          // the referenced frame
  Assign,
  Dup,         // Duplicates the current stack end
  Set,         // narrows/Sets a new value for a subroutine (variables)
  SetAndPush,  // narrows/Sets a new value for a subroutine (variables)
  Error,
  Pop,
  Inline,  // Execute a subroutine on the same active frame

  // Frame, //creates a new stack frame
  // FrameEnd,
  Return,           // end of a subroutine
  ReturnStatement,  // used in inferring return types of functions

  Subroutine,
  Distribute,  // calls a subroutine for each union member. one parameter
               // (address to subroutine)
  Call,        // call a subroutine and push the result on the stack
  TailCall,
  CheckBody,
  InferBody,
  UnwrapInferBody,
};

enum class ErrorCode {
  CannotFind,  // e.g. Cannot find name 'abc'
};

// Max 8 bits, used in the bytecode
enum SubroutineFlag : unsigned int {};
}  // namespace tscpp::instructions

template <>
struct fmt::formatter<tscpp::instructions::OP> : formatter<std::string_view> {
  template <typename FormatContext>
  auto format(tscpp::instructions::OP p, FormatContext& ctx) {
    return formatter<std::string_view>::format(
        magic_enum::enum_name<tscpp::instructions::OP>(p), ctx);
  }
};

template <>
struct fmt::formatter<tscpp::instructions::ErrorCode>
    : formatter<std::string_view> {
  template <typename FormatContext>
  auto format(tscpp::instructions::ErrorCode p, FormatContext& ctx) {
    return formatter<std::string_view>::format(
        magic_enum::enum_name<tscpp::instructions::ErrorCode>(p), ctx);
  }
};

#endif  // TSCPP_TYPECHECKER_INSTRUCTIONS_H