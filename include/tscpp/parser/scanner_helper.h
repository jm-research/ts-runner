#ifndef TSCPP_PARSER_SCANNER_HELPER_H
#define TSCPP_PARSER_SCANNER_HELPER_H

#include <optional>
#include <string>
#include <vector>

#include "tscpp/base/core.h"
#include "tscpp/base/types.h"
#include "tscpp/diagnostic/diagnostic_message.h"
#include "tscpp/parser/node_helper.h"
#include "tscpp/parser/scanner.h"
#include "tscpp/utils/hash.h"
#include "tscpp/utils/utf.h"

namespace tscpp {
using namespace tscpp::types;
using std::optional;
using std::string;
using std::vector;
using tscpp::types::Extension;
using tscpp::types::LanguageVariant;
using tscpp::types::ScriptKind;
using tscpp::types::SyntaxKind;
using tscpp::utf::CharacterCodes;
using tscpp::utf::CharCode;
using tscpp::utf::charCodeAt;
using types::DiagnosticCategory;
using types::DiagnosticMessage;
using types::DiagnosticWithDetachedLocation;

inline vector<const char*> supportedDeclarationExtensions{
    Extension::Dts, Extension::Dcts, Extension::Dmts};

extern LanguageVariant getLanguageVariant(ScriptKind scriptKind);

/* @internal */
template <typename T>
T setTextRangePosEnd(T range, int pos, int end) {
  range->pos = pos;
  range->end = end;
  return range;
}

template <typename T, typename T2>
T setTextRange(T range, T2 location) {
  return location ? setTextRangePosEnd<T>(range, location->pos, location->end)
                  : range;
}

optionalNode<Node> lastOrUndefined(optionalNode<NodeArray> array);

node<NodeArray> setTextRangePosEnd(node<NodeArray> range, int pos, int end);

node<NodeArray> setArrayTextRange(node<NodeArray> range,
                                  optional<NodeArray> location);

/**
 * Gets a custom text range to use when emitting source maps.
 */
node<SourceMapRange> getSourceMapRange(node<Node> node);

/**
 * Gets a custom text range to use when emitting comments.
 */
node<TextRange> getCommentRange(node<Node> node);

optional<vector<SynthesizedComment>> getSyntheticLeadingComments(
    node<Node> node);

optional<vector<SynthesizedComment>> getSyntheticTrailingComments(
    node<Node> node);

bool positionIsSynthesized(int pos);

bool nodeIsSynthesized(node<TextRange> range);

NodeArray setTextRange(NodeArray range, optional<NodeArray> location);

string parsePseudoBigInt(string& stringValue);

/** Add an extra underscore to identifiers that start with two underscores to
 * avoid issues with magic names like '__proto__' */
string escapeLeadingUnderscores(string identifier);

/* @internal */
bool isParameterPropertyModifier(SyntaxKind kind);

/* @internal */
bool isClassMemberModifier(SyntaxKind idToken);

/* @internal */
bool isModifierKind(SyntaxKind token);

bool isCommaSequence(node<Expression> node);

bool isLiteralKind(SyntaxKind kind);

string pseudoBigIntToString(PseudoBigInt bigint);
// Pseudo-literals

/* @internal */
bool isTemplateLiteralKind(SyntaxKind kind);

bool isTemplateLiteralToken(node<Node>& node);

bool isTemplateMiddleOrTemplateTail(node<Node>& node);

bool isImportOrExportSpecifier(node<Node>& node);

enum class OperatorPrecedence {
  // Expression:
  //     AssignmentExpression
  //     Expression `,` AssignmentExpression
  Comma,

  // NOTE: `Spread` is higher than `Comma` due to how it is parsed in
  // |ElementList|
  // SpreadElement:
  //     `...` AssignmentExpression
  Spread,

  // AssignmentExpression:
  //     ConditionalExpression
  //     YieldExpression
  //     ArrowFunction
  //     AsyncArrowFunction
  //     LeftHandSideExpression `=` AssignmentExpression
  //     LeftHandSideExpression AssignmentOperator AssignmentExpression
  //
  // NOTE: AssignmentExpression is broken down into several precedences due to
  // the requirements
  //       of the parenthesizer rules.

  // AssignmentExpression: YieldExpression
  // YieldExpression:
  //     `yield`
  //     `yield` AssignmentExpression
  //     `yield` `*` AssignmentExpression
  Yield,

  // AssignmentExpression: LeftHandSideExpression `=` AssignmentExpression
  // AssignmentExpression: LeftHandSideExpression AssignmentOperator
  // AssignmentExpression
  // AssignmentOperator: one of
  //     `*=` `/=` `%=` `+=` `-=` `<<=` `>>=` `>>>=` `&=` `^=` `|=` `**=`
  Assignment,

  // NOTE: `Conditional` is considered higher than `Assignment` here, but in
  // reality they have
  //       the same precedence.
  // AssignmentExpression: ConditionalExpression
  // ConditionalExpression:
  //     ShortCircuitExpression
  //     ShortCircuitExpression `?` AssignmentExpression `:`
  //     AssignmentExpression
  // ShortCircuitExpression:
  //     LogicalORExpression
  //     CoalesceExpression
  Conditional,

  // CoalesceExpression:
  //     CoalesceExpressionHead `??` BitwiseORExpression
  // CoalesceExpressionHead:
  //     CoalesceExpression
  //     BitwiseORExpression
  Coalesce = Conditional,  // NOTE: This is wrong

  // LogicalORExpression:
  //     LogicalANDExpression
  //     LogicalORExpression `||` LogicalANDExpression
  LogicalOR,

  // LogicalANDExpression:
  //     BitwiseORExpression
  //     LogicalANDExprerssion `&&` BitwiseORExpression
  LogicalAND,

  // BitwiseORExpression:
  //     BitwiseXORExpression
  //     BitwiseORExpression `^` BitwiseXORExpression
  BitwiseOR,

  // BitwiseXORExpression:
  //     BitwiseANDExpression
  //     BitwiseXORExpression `^` BitwiseANDExpression
  BitwiseXOR,

  // BitwiseANDExpression:
  //     EqualityExpression
  //     BitwiseANDExpression `^` EqualityExpression
  BitwiseAND,

  // EqualityExpression:
  //     RelationalExpression
  //     EqualityExpression `==` RelationalExpression
  //     EqualityExpression `!=` RelationalExpression
  //     EqualityExpression `===` RelationalExpression
  //     EqualityExpression `!==` RelationalExpression
  Equality,

  // RelationalExpression:
  //     ShiftExpression
  //     RelationalExpression `<` ShiftExpression
  //     RelationalExpression `>` ShiftExpression
  //     RelationalExpression `<=` ShiftExpression
  //     RelationalExpression `>=` ShiftExpression
  //     RelationalExpression `instanceof` ShiftExpression
  //     RelationalExpression `in` ShiftExpression
  //     [+TypeScript] RelationalExpression `as` Type
  Relational,

  // ShiftExpression:
  //     AdditiveExpression
  //     ShiftExpression `<<` AdditiveExpression
  //     ShiftExpression `>>` AdditiveExpression
  //     ShiftExpression `>>>` AdditiveExpression
  Shift,

  // AdditiveExpression:
  //     MultiplicativeExpression
  //     AdditiveExpression `+` MultiplicativeExpression
  //     AdditiveExpression `-` MultiplicativeExpression
  Additive,

  // MultiplicativeExpression:
  //     ExponentiationExpression
  //     MultiplicativeExpression MultiplicativeOperator
  //     ExponentiationExpression
  // MultiplicativeOperator: one of `*`, `/`, `%`
  Multiplicative,

  // ExponentiationExpression:
  //     UnaryExpression
  //     UpdateExpression `**` ExponentiationExpression
  Exponentiation,

  // UnaryExpression:
  //     UpdateExpression
  //     `delete` UnaryExpression
  //     `void` UnaryExpression
  //     `typeof` UnaryExpression
  //     `+` UnaryExpression
  //     `-` UnaryExpression
  //     `~` UnaryExpression
  //     `!` UnaryExpression
  //     AwaitExpression
  // UpdateExpression:            // TODO: Do we need to investigate the
  // precedence here?
  //     `++` UnaryExpression
  //     `--` UnaryExpression
  Unary,

  // UpdateExpression:
  //     LeftHandSideExpression
  //     LeftHandSideExpression `++`
  //     LeftHandSideExpression `--`
  Update,

  // LeftHandSideExpression:
  //     NewExpression
  //     CallExpression
  // NewExpression:
  //     MemberExpression
  //     `new` NewExpression
  LeftHandSide,

  // CallExpression:
  //     CoverCallExpressionAndAsyncArrowHead
  //     SuperCall
  //     ImportCall
  //     CallExpression Arguments
  //     CallExpression `[` Expression `]`
  //     CallExpression `.` IdentifierName
  //     CallExpression TemplateLiteral
  // MemberExpression:
  //     PrimaryExpression
  //     MemberExpression `[` Expression `]`
  //     MemberExpression `.` IdentifierName
  //     MemberExpression TemplateLiteral
  //     SuperProperty
  //     MetaProperty
  //     `new` MemberExpression Arguments
  Member,

  // TODO: JSXElement?
  // PrimaryExpression:
  //     `this`
  //     IdentifierReference
  //     Literal
  //     ArrayLiteral
  //     ObjectLiteral
  //     FunctionExpression
  //     ClassExpression
  //     GeneratorExpression
  //     AsyncFunctionExpression
  //     AsyncGeneratorExpression
  //     RegularExpressionLiteral
  //     TemplateLiteral
  //     CoverParenthesizedExpressionAndArrowParameterList
  Primary,

  Highest = Primary,
  Lowest = Comma,
  // -1 is lower than all other precedences. Returning it will cause binary
  // expression
  // parsing to stop.
  Invalid = -1,
};

int getBinaryOperatorPrecedence(SyntaxKind kind);

bool isKeyword(types::SyntaxKind token);

bool isContextualKeyword(types::SyntaxKind token);

// unordered_map<string, string> localizedDiagnosticMessages{};

string_view getLocaleSpecificMessage(const node<DiagnosticMessage>& message);

using DiagnosticArg = string;

string formatStringFromArg(string& text, int i, string& v);

string DiagnosticArgToString(DiagnosticArg& v);

DiagnosticWithDetachedLocation createDetachedDiagnostic(
    string fileName, int start, int length,
    const shared_ptr<DiagnosticMessage>& message,
    vector<DiagnosticArg> textArg = {});

DiagnosticWithDetachedLocation& addRelatedInfo(
    DiagnosticWithDetachedLocation& diagnostic,
    vector<DiagnosticRelatedInformation> relatedInformation);

ScriptKind ensureScriptKind(string fileName, optional<ScriptKind> scriptKind);

/** @internal */
bool hasInvalidEscape(node<NodeUnion(TemplateLiteralTypes)> templateLiteral);

string fileExt(const string& filename);

ScriptKind getScriptKindFromFileName(const string& fileName);

bool isOuterExpression(optionalNode<Node> node,
                       int kinds = (int)OuterExpressionKinds::All);

optionalNode<Expression> getExpression(optionalNode<Node> node);

node<Node> skipOuterExpressions(node<Node> node,
                                int kinds = (int)OuterExpressionKinds::All);

node<Node> skipPartiallyEmittedExpressions(node<Node> node);

bool isLeftHandSideExpressionKind(SyntaxKind kind);

bool isUnaryExpressionKind(SyntaxKind kind);

/* @internal */
bool isUnaryExpression(node<Node> node);

int getOperatorPrecedence(SyntaxKind nodeKind, SyntaxKind operatorKind,
                          optional<bool> hasArguments = {});

SyntaxKind getOperator(node<Node> expression);

/* @internal */
bool isGeneratedIdentifier(node<Node> node);

int getExpressionPrecedence(node<Node> expression);

bool isLeftHandSideExpression(node<Node> node);

// Returns true if this node is missing from the actual source code. A 'missing'
// node is different from 'undefined/defined'. When a node is undefined (which
// can happen for optional nodes in the tree), it is definitely missing.
// However, a node may be defined, but still be missing.  This happens whenever
// the parser knows it needs to parse something, but can't get anything in the
// source code that it expects at that location. For example:
//
//          let a: ;
//
// Here, the Type in the Type-Annotation is not-optional (as there is a colon in
// the source code). So the parser will attempt to parse out a type, and will
// create an actual node. However, this node will be 'missing' in the sense that
// no actual source-code/tokens are contained within it.
bool nodeIsMissing(optionalNode<Node> node);

bool nodeIsPresent(optionalNode<Node> node);

string getTextOfNodeFromSourceText(string& sourceText, node<Node> node,
                                   bool includeTrivia = false);

int getFullWidth(node<Node> node);

/**
 * Remove extra underscore from escaped identifier text content.
 *
 * @param identifier The escaped identifier text.
 * @returns The unescaped identifier text.
 */
string unescapeLeadingUnderscores(__String id);

string idText(
    node<NodeUnion(Identifier | PrivateIdentifier)> identifierOrPrivateName);

node<Expression> getLeftmostExpression(node<Expression> node,
                                       bool stopAtCallExpressions);

Comparison compareComparableValues(optional<double> a, optional<double> b);

Comparison compareComparableValues(optional<string> a, optional<string> b);

/**
 * Compare two numeric values for their order relative to each other.
 * To compare strings, use any of the `compareStrings` functions.
 */
Comparison compareValues(optional<double> a, optional<double> b);

/**
 * Gets the actual offset into an array for a relative offset. Negative offsets
 * indicate a position offset from the end of the array.
 */
template <typename T>
int toOffset(vector<T> array, int offset) {
  return offset < 0 ? array.size() + offset : offset;
}

/**
 * Appends a range of value to an array, returning the array.
 *
 * @param to The array to which `value` is to be appended. If `to` is
 * `undefined`, a new array is created if `value` was appended.
 * @param from The values to append to the array. If `from` is `undefined`,
 * nothing is appended. If an element of `from` is `undefined`, that element is
 * not appended.
 * @param start The offset in `from` at which to start copying values.
 * @param end The offset in `from` at which to stop copying values
 * (non-inclusive).
 */
//    export function addRange<T>(to: T[], from: readonly T[] | undefined,
//    start?: number, end?: number): T[]; export function addRange<T>(to: T[] |
//    undefined, from: readonly T[] | undefined, start?: number, end?: number):
//    T[] | undefined;
template <typename T>
optional<vector<T>> addRange(optional<vector<T>> to, optional<vector<T>> from,
                             int start = 0, int end = 0) {
  if (!from || from->empty())
    return to;
  if (!to)
    return slice(from, start, end);
  start = start == 0 ? 0 : toOffset(*from, start);
  end = end == 0 ? from->size() : toOffset(*from, end);
  for (int i = start; i < end && i < from->size(); i++) {
    //            if (!(bool) (*from)[i]) {
    to->push_back((*from)[i]);
    //            }
  }
  return to;
}

enum class Associativity { Left, Right };

Associativity getOperatorAssociativity(SyntaxKind kind, SyntaxKind operatorKind,
                                       bool hasArguments = false);

Associativity getExpressionAssociativity(node<Expression> expression);

node<NodeArray> getElementsOfBindingOrAssignmentPattern(node<Node> name);

bool isLogicalOrCoalescingAssignmentOperator(
    SyntaxKind token);  //: token is LogicalOrCoalescingAssignmentOperator

/**
 * Determines whether the BindingOrAssignmentElement is a BindingElement-like
 * declaration
 */
/* @internal */
inline bool isDeclarationBindingElement(
    node<Node> bindingElement) {  //: bindingElement is VariableDeclaration |
                                  //: ParameterDeclaration | BindingElement {
  switch (bindingElement->kind) {
    case SyntaxKind::VariableDeclaration:
    case SyntaxKind::Parameter:
    case SyntaxKind::BindingElement:
      return true;
  }

  return false;
}

inline bool isObjectLiteralElementLike(
    node<Node> node) {  //: node is ObjectLiteralElementLike {
  auto kind = node->kind;
  return kind == SyntaxKind::PropertyAssignment ||
         kind == SyntaxKind::ShorthandPropertyAssignment ||
         kind == SyntaxKind::SpreadAssignment ||
         kind == SyntaxKind::MethodDeclaration ||
         kind == SyntaxKind::GetAccessor || kind == SyntaxKind::SetAccessor;
}

inline bool isAssignmentExpression(
    node<Node> node,
    bool excludeCompoundAssignment =
        false) {  //: node is AssignmentExpression<AssignmentOperatorToken> {
  return isBinaryExpression(node) &&
         (excludeCompoundAssignment
              ? to<BinaryExpression>(node)->operatorToken->kind ==
                    SyntaxKind::EqualsToken
              : isAssignmentOperator(
                    to<BinaryExpression>(node)->operatorToken->kind)) &&
         isLeftHandSideExpression(to<BinaryExpression>(node)->left);
}

/* @internal */
inline bool isAssignmentPattern(
    node<Node> node) {  //: node is AssignmentPattern {
  auto kind = node->kind;
  return kind == SyntaxKind::ArrayLiteralExpression ||
         kind == SyntaxKind::ObjectLiteralExpression;
}

/**
 * Gets the name of an BindingOrAssignmentElement.
 */
inline optionalNode<Node> getTargetOfBindingOrAssignmentElement(
    node<Node> bindingElement) {
  if (isDeclarationBindingElement(bindingElement)) {
    // `a` in `let { a } = ...`
    // `a` in `let { a = 1 } = ...`
    // `b` in `let { a: b } = ...`
    // `b` in `let { a: b = 1 } = ...`
    // `a` in `let { ...a } = ...`
    // `{b}` in `let { a: {b} } = ...`
    // `{b}` in `let { a: {b} = 1 } = ...`
    // `[b]` in `let { a: [b] } = ...`
    // `[b]` in `let { a: [b] = 1 } = ...`
    // `a` in `let [a] = ...`
    // `a` in `let [a = 1] = ...`
    // `a` in `let [...a] = ...`
    // `{a}` in `let [{a}] = ...`
    // `{a}` in `let [{a} = 1] = ...`
    // `[a]` in `let [[a]] = ...`
    // `[a]` in `let [[a] = 1] = ...`
    return getName(bindingElement);
  }

  if (isObjectLiteralElementLike(bindingElement)) {
    switch (bindingElement->kind) {
      case SyntaxKind::PropertyAssignment:
        // `b` in `({ a: b } = ...)`
        // `b` in `({ a: b = 1 } = ...)`
        // `{b}` in `({ a: {b} } = ...)`
        // `{b}` in `({ a: {b} = 1 } = ...)`
        // `[b]` in `({ a: [b] } = ...)`
        // `[b]` in `({ a: [b] = 1 } = ...)`
        // `b.c` in `({ a: b.c } = ...)`
        // `b.c` in `({ a: b.c = 1 } = ...)`
        // `b[0]` in `({ a: b[0] } = ...)`
        // `b[0]` in `({ a: b[0] = 1 } = ...)`
        return getTargetOfBindingOrAssignmentElement(
            to<PropertyAssignment>(bindingElement)->initializer);

      case SyntaxKind::ShorthandPropertyAssignment:
        // `a` in `({ a } = ...)`
        // `a` in `({ a = 1 } = ...)`
        return getName(bindingElement);

      case SyntaxKind::SpreadAssignment:
        // `a` in `({ ...a } = ...)`
        return getTargetOfBindingOrAssignmentElement(
            to<SpreadAssignment>(bindingElement)->expression);
    }

    // no target
    return nullptr;
  }

  if (isAssignmentExpression(bindingElement,
                             /*excludeCompoundAssignment*/ true)) {
    // `a` in `[a = 1] = ...`
    // `{a}` in `[{a} = 1] = ...`
    // `[a]` in `[[a] = 1] = ...`
    // `a.b` in `[a.b = 1] = ...`
    // `a[0]` in `[a[0] = 1] = ...`
    return getTargetOfBindingOrAssignmentElement(
        to<AssignmentExpression>(bindingElement)->left);
  }

  if (isSpreadElement(bindingElement)) {
    // `a` in `[...a] = ...`
    return getTargetOfBindingOrAssignmentElement(
        to<SpreadElement>(bindingElement)->expression);
  }

  // `a` in `[a] = ...`
  // `{a}` in `[{a}] = ...`
  // `[a]` in `[[a]] = ...`
  // `a.b` in `[a.b] = ...`
  // `a[0]` in `[a[0]] = ...`
  return bindingElement;
}
}  // namespace tscpp

#endif  // TSCPP_PARSER_SCANNER_HELPER_H