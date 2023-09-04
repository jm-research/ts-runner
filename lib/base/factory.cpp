#include "tscpp/base/factory.h"

#include <fmt/core.h>

namespace tscpp {
int Factory::propagatePropertyNameFlagsOfChild(node<tscpp::Node>& node,
                                               int transformFlags) {
  return transformFlags | (node->transformFlags &
                           (int)TransformFlags::PropertyNamePropagatingFlags);
}

int Factory::propagateChildFlags(optionalNode<Node> child) {
  if (!child)
    return (int)TransformFlags::None;
  auto childFlags = child->transformFlags &
                    ~(int)getTransformFlagsSubtreeExclusions(child->kind);

  auto name = getName(child);
  return name ? propagatePropertyNameFlagsOfChild(name, childFlags)
              : childFlags;
}

int Factory::propagateIdentifierNameFlags(node<Node> node) {
  // An IdentifierName is allowed to be `await`
  return propagateChildFlags(std::move(node)) &
         ~(int)TransformFlags::ContainsPossibleTopLevelAwait;
}

int Factory::propagateChildrenFlags(const optionalNode<NodeArray>& children) {
  return children ? children->transformFlags : (int)TransformFlags::None;
}

void Factory::aggregateChildrenFlags(const node<NodeArray>& children) {
  int subtreeFlags = (int)TransformFlags::None;
  for (auto child : *children) {
    subtreeFlags |= propagateChildFlags(child);
  }
  children->transformFlags = subtreeFlags;
}

node<NodeArray> Factory::createNodeArray(
    const optionalNode<NodeArray>& elements, bool hasTrailingComma) {
  ZoneScoped;
  if (elements && elements->hasTrailingComma == hasTrailingComma) {
    // Ensure the transform flags have been aggregated for this NodeArray
    if (elements->transformFlags == (int)types::TransformFlags::None) {
      aggregateChildrenFlags(elements);
    }
    //                Debug.attachNodeArrayDebugInfo(elements);
    return elements;
  }
  elements->hasTrailingComma = hasTrailingComma;
  return elements;
  // This *was* a `NodeArray`, but the `hasTrailingComma` option differs.
  // Recreate the array with the same elements, text range, and transform flags
  // but with the updated value for `hasTrailingComma`
  //        auto array = make_shared<NodeArray>();
  //        if (elements) array = elements;
  //        array->pos = elements->pos;
  //        array->end = elements->end;
  //        array->hasTrailingComma = *hasTrailingComma;
  //        array->transformFlags = elements->transformFlags;
  ////            Debug.attachNodeArrayDebugInfo(array);
  //        return array;
}

optionalNode<NodeArray> Factory::asNodeArray(optionalNode<NodeArray> elements) {
  return elements;
}

// @api
node<NumericLiteral> Factory::createNumericLiteral(string value,
                                                   int numericLiteralFlags) {
  auto node = createBaseLiteral<NumericLiteral>(SyntaxKind::NumericLiteral,
                                                std::move(value));
  node->numericLiteralFlags = numericLiteralFlags;
  if (numericLiteralFlags & TokenFlags::BinaryOrOctalSpecifier)
    node->transformFlags |= (int)TransformFlags::ContainsES2015;
  return node;
}

node<NumericLiteral> Factory::createNumericLiteral(
    double value, types::TokenFlags numericLiteralFlags) {
  return createNumericLiteral(std::to_string(value), numericLiteralFlags);
}

// @api
node<BigIntLiteral> Factory::createBigIntLiteral(
    variant<string, PseudoBigInt> value) {
  string v = holds_alternative<string>(value)
                 ? get<string>(value)
                 : pseudoBigIntToString(get<PseudoBigInt>(value)) + "n";
  auto node = createBaseLiteral<BigIntLiteral>(SyntaxKind::BigIntLiteral, v);
  node->transformFlags |= (int)TransformFlags::ContainsESNext;
  return node;
}

node<StringLiteral> Factory::createBaseStringLiteral(
    string text, optional<bool> isSingleQuote) {
  auto node = createBaseLiteral<StringLiteral>(SyntaxKind::StringLiteral,
                                               std::move(text));
  node->singleQuote = isSingleQuote;
  return node;
}
// @api
node<StringLiteral> Factory::createStringLiteral(
    string text, optional<bool> isSingleQuote,
    optional<bool> hasExtendedUnicodeEscape) {
  auto node = createBaseStringLiteral(std::move(text), isSingleQuote);
  node->hasExtendedUnicodeEscape = hasExtendedUnicodeEscape;
  if (hasExtendedUnicodeEscape)
    node->transformFlags |= (int)TransformFlags::ContainsES2015;
  return node;
}

//
// Reserved words
//

// @api
node<SuperExpression> Factory::createSuper() {
  return createToken<SuperExpression>(SyntaxKind::SuperKeyword);
}

// @api
node<ThisExpression> Factory::createThis() {
  return createToken<ThisExpression>(SyntaxKind::ThisKeyword);
}

// @api
node<NullLiteral> Factory::createNull() {
  return createToken<NullLiteral>(SyntaxKind::NullKeyword);
}

// @api
node<TrueLiteral> Factory::createTrue() {
  return createToken<TrueLiteral>(SyntaxKind::TrueKeyword);
}

// @api
node<FalseLiteral> Factory::createFalse() {
  return createToken<FalseLiteral>(SyntaxKind::FalseKeyword);
}

node<Expression> Factory::createBooleanLiteral(bool v) {
  if (v)
    return createTrue();
  return createFalse();
}

using NameType = variant<string, tscpp::node<Node>>;

node<Node> Factory::asName(NameType name) {
  if (holds_alternative<string>(name))
    return createIdentifier(get<string>(name));
  return get<node<Node>>(name);
}

optionalNode<Node> Factory::asName(optional<NameType> name) {
  if (!name)
    return nullptr;
  return asName(*name);
}

using ExpressionType = variant<string, int, bool, optionalNode<Expression>>;

optionalNode<Expression> Factory::asExpression(ExpressionType value) {
  if (holds_alternative<optionalNode<Expression>>(value))
    return get<optionalNode<Expression>>(value);
  if (holds_alternative<string>(value))
    return createStringLiteral(get<string>(value));
  if (holds_alternative<int>(value))
    return createNumericLiteral(get<int>(value));
  if (holds_alternative<bool>(value))
    return createBooleanLiteral(get<bool>(value));

  throw runtime_error("Invalid type given");
}

//        function createBaseNode<T extends Node>(kind: T["kind"]) {
//            return basefactory::createBaseNode(kind) as Mutable<T>;
//        }

void Factory::setName(node<Identifier>& lName, tscpp::node<Node> rName) {
  lName = reinterpret_node<Identifier>(rName);
}

void Factory::setName(node<PrivateIdentifier>& lName, tscpp::node<Node> rName) {
  lName = reinterpret_node<PrivateIdentifier>(rName);
}

void Factory::setName(node<Node>& lName, tscpp::node<Node> rName) {
  lName = rName;
}

//        // @api
//        function createStringLiteralFromNode(sourceNode: PropertyNameLiteral):
//        StringLiteral {
//            auto node =
//            createBaseStringLiteral(getTextOfIdentifierOrLiteral(sourceNode),
//            /*isSingleQuote*/ undefined); node->textSourceNode = sourceNode;
//            return node;
//        }
//
// @api
node<RegularExpressionLiteral> Factory::createRegularExpressionLiteral(
    string text) {
  auto node = createBaseLiteral<RegularExpressionLiteral>(
      SyntaxKind::RegularExpressionLiteral, text);
  return node;
}

// @api
node<JsxText> Factory::createJsxText(
    string text, optional<bool> containsOnlyTriviaWhiteSpaces) {
  auto node = createBaseNode<JsxText>(SyntaxKind::JsxText);
  node->text = text;
  node->containsOnlyTriviaWhiteSpaces =
      containsOnlyTriviaWhiteSpaces ? *containsOnlyTriviaWhiteSpaces : false;
  node->transformFlags |= (int)TransformFlags::ContainsJsx;
  return node;
}

// @api
node<TemplateLiteralLike> Factory::createTemplateLiteralLikeNode(
    SyntaxKind kind, string text, optional<string> rawText,
    optional<int> templateFlags) {
  auto node = createBaseToken<TemplateLiteralLike>(kind);
  node->text = std::move(text);
  node->rawText = std::move(rawText);
  node->templateFlags = (templateFlags ? *templateFlags : 0) &
                        (int)TokenFlags::TemplateLiteralLikeFlags;
  node->transformFlags |= (int)TransformFlags::ContainsES2015;
  if (node->templateFlags) {
    node->transformFlags |= (int)TransformFlags::ContainsES2018;
  }
  return node;
}

// @api
node<LiteralLike> Factory::createLiteralLikeNode(SyntaxKind kind, string text) {
  switch (kind) {
    case SyntaxKind::NumericLiteral:
      return createNumericLiteral(text, /*numericLiteralFlags*/ 0);
    case SyntaxKind::BigIntLiteral:
      return createBigIntLiteral(text);
    case SyntaxKind::StringLiteral:
      return createStringLiteral(text, /*isSingleQuote*/ {});
    case SyntaxKind::JsxText:
      return createJsxText(text, /*containsOnlyTriviaWhiteSpaces*/ false);
    case SyntaxKind::JsxTextAllWhiteSpaces:
      return createJsxText(text, /*containsOnlyTriviaWhiteSpaces*/ true);
    case SyntaxKind::RegularExpressionLiteral:
      return createRegularExpressionLiteral(text);
    case SyntaxKind::NoSubstitutionTemplateLiteral:
      return createTemplateLiteralLikeNode(kind, text, /*rawText*/ {},
                                           /*templateFlags*/ 0);
  }
  throw std::runtime_error("createLiteralLikeNode invalid kind");
}

//        //
//        // Identifiers
//        //

node<Identifier> Factory::createBaseIdentifier(
    string text, optional<SyntaxKind> originalKeywordKind) {
  if (!originalKeywordKind && !text.empty()) {
    originalKeywordKind = stringToToken(text);
  }
  if (originalKeywordKind == SyntaxKind::Identifier) {
    originalKeywordKind.reset();
  }
  auto node = createBaseNode<Identifier>();
  node->originalKeywordKind = originalKeywordKind;
  node->escapedText = escapeLeadingUnderscores(text);
  return node;
}

node<Identifier> Factory::createBaseGeneratedIdentifier(
    string text, GeneratedIdentifierFlags autoGenerateFlags) {
  auto node = createBaseIdentifier(text, /*originalKeywordKind*/ {});
  node->autoGenerateFlags = (int)autoGenerateFlags;
  node->autoGenerateId = nextAutoGenerateId;
  nextAutoGenerateId++;
  return node;
}

// @api
node<Identifier> Factory::createIdentifier(
    string text, optionalNode<NodeArray> typeArguments,
    optional<SyntaxKind> originalKeywordKind) {
  ZoneScoped;
  auto node = createBaseIdentifier(std::move(text), originalKeywordKind);
  if (typeArguments) {
    // NOTE: we do not use `setChildren` here because typeArguments in an
    // identifier do not contribute to transformations
    node->typeArguments = createNodeArray(typeArguments);
  }
  if (node->originalKeywordKind == SyntaxKind::AwaitKeyword) {
    node->transformFlags |= (int)TransformFlags::ContainsPossibleTopLevelAwait;
  }
  return node;
}
//
//        // @api
//        function updateIdentifier(node: Identifier, typeArguments?:
//        NodeArray<TypeNode | TypeParameterDeclaration> | undefined):
//        Identifier {
//            return node->typeArguments != typeArguments
//                ? update(createIdentifier(idText(node), typeArguments), node)
//                : node;
//        }
//
//        // @api
//        function createTempVariable(recordTempVariable: ((node: Identifier) =>
//        void) | undefined, reservedInNestedScopes?: boolean):
//        GeneratedIdentifier {
//            let flags = GeneratedIdentifierFlags.Auto;
//            if (reservedInNestedScopes) flags |=
//            GeneratedIdentifierFlags.ReservedInNestedScopes; auto name =
//            createBaseGeneratedIdentifier("", flags); if (recordTempVariable)
//            {
//                recordTempVariable(name);
//            }
//            return name;
//        }
//
//        /** Create a unique temporary variable for use in a loop. */
//        // @api
//        function createLoopVariable(reservedInNestedScopes?: boolean):
//        Identifier {
//            let flags = GeneratedIdentifierFlags.Loop;
//            if (reservedInNestedScopes) flags |=
//            GeneratedIdentifierFlags.ReservedInNestedScopes; return
//            createBaseGeneratedIdentifier("", flags);
//        }
//
//        /** Create a unique name based on the supplied text. */
//        // @api
//        function createUniqueName(text: string, flags:
//        GeneratedIdentifierFlags = GeneratedIdentifierFlags.None): Identifier
//        {
//            Debug::asserts(!(flags & GeneratedIdentifierFlags.KindMask),
//            "Argument out of range: flags"); Debug::asserts((flags &
//            (GeneratedIdentifierFlags.Optimistic |
//            GeneratedIdentifierFlags.FileLevel)) !=
//            GeneratedIdentifierFlags.FileLevel,
//            "GeneratedIdentifierFlags.FileLevel cannot be set without also
//            setting GeneratedIdentifierFlags.Optimistic"); return
//            createBaseGeneratedIdentifier(text,
//            GeneratedIdentifierFlags.Unique | flags);
//        }
//
//        /** Create a unique name generated for a node-> */
//        // @api
//        function getGeneratedNameForNode(node: Node | undefined, flags:
//        GeneratedIdentifierFlags = 0): Identifier {
//            Debug::asserts(!(flags & GeneratedIdentifierFlags.KindMask),
//            "Argument out of range: flags"); auto name =
//            createBaseGeneratedIdentifier(node && isIdentifier(node) ?
//            idText(node) : "", GeneratedIdentifierFlags.Node | flags);
//            name.original = node;
//            return name;
//        }
//
// @api
node<PrivateIdentifier> Factory::createPrivateIdentifier(string text) {
  if (!startsWith(text, "#"))
    throw runtime_error("First character of private identifier must be #: " +
                        text);
  auto node = createBaseNode<PrivateIdentifier>(SyntaxKind::PrivateIdentifier);
  node->escapedText = escapeLeadingUnderscores(text);
  node->transformFlags |= (int)TransformFlags::ContainsClassFields;
  return node;
}

//        //
//        // Punctuation
//        //

//
//        //
//        // Modifiers
//        //
//
//        // @api
//        function createModifier<T extends ModifierSyntaxKind>(kind: T) {
//            return createToken(kind);
//        }
//
//        // @api
//        function createModifiersFromModifierFlags(flags: ModifierFlags) {
//            auto result: Modifier[] = [];
//            if (flags & ModifierFlags::Export)
//            result.push(createModifier(SyntaxKind::ExportKeyword)); if (flags
//            & ModifierFlags::Ambient)
//            result.push(createModifier(SyntaxKind::DeclareKeyword)); if (flags
//            & ModifierFlags::Default)
//            result.push(createModifier(SyntaxKind::DefaultKeyword)); if (flags
//            & ModifierFlags::Const)
//            result.push(createModifier(SyntaxKind::ConstKeyword)); if (flags &
//            ModifierFlags::Public)
//            result.push(createModifier(SyntaxKind::PublicKeyword)); if (flags
//            & ModifierFlags::Private)
//            result.push(createModifier(SyntaxKind::PrivateKeyword)); if (flags
//            & ModifierFlags::Protected)
//            result.push(createModifier(SyntaxKind::ProtectedKeyword)); if
//            (flags & ModifierFlags::Abstract)
//            result.push(createModifier(SyntaxKind::AbstractKeyword)); if
//            (flags & ModifierFlags::Static)
//            result.push(createModifier(SyntaxKind::StaticKeyword)); if (flags
//            & ModifierFlags::Override)
//            result.push(createModifier(SyntaxKind::OverrideKeyword)); if
//            (flags & ModifierFlags::Readonly)
//            result.push(createModifier(SyntaxKind::ReadonlyKeyword)); if
//            (flags & ModifierFlags::Async)
//            result.push(createModifier(SyntaxKind::AsyncKeyword)); if (flags &
//            ModifierFlags::In)
//            result.push(createModifier(SyntaxKind::InKeyword)); if (flags &
//            ModifierFlags::Out)
//            result.push(createModifier(SyntaxKind::OutKeyword)); return
//            result.length ? result : undefined;
//        }
//
//        //
//        // Names
//        //
//
// @api
node<QualifiedName> Factory::createQualifiedName(node<Node> left,
                                                 NameType right) {
  auto node = createBaseNode<QualifiedName>(SyntaxKind::QualifiedName);
  node->left = left;
  node->right = reinterpret_node<Identifier>(asName(right));
  node->transformFlags |= propagateChildFlags(node->left) |
                          propagateIdentifierNameFlags(node->right);
  return node;
}

//        // @api
//        function updateQualifiedName(node: QualifiedName, left: EntityName,
//        right: Identifier) {
//            return node->left != left
//                || node->right != right
//                ? update(createQualifiedName(left, right), node)
//                : node;
//        }
//
// @api
node<ComputedPropertyName> Factory::createComputedPropertyName(
    node<Expression> expression) {
  auto node =
      createBaseNode<ComputedPropertyName>(SyntaxKind::ComputedPropertyName);
  node->expression =
      parenthesizer.parenthesizeExpressionOfComputedPropertyName(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsES2015 |
                          (int)TransformFlags::ContainsComputedPropertyName;
  return node;
}

//        // @api
//        function updateComputedPropertyName(node: ComputedPropertyName,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createComputedPropertyName(expression), node)
//                : node;
//        }
//
//        //
//        // Signature elements
//        //
//
//        // @api
//        function createTypeParameterDeclaration(optionalNode<NodeArray>
//        modifiers, name: string | Identifier, constraint?: TypeNode,
//        defaultType?: TypeNode): TypeParameterDeclaration;
//        /** @deprecated */
//        function createTypeParameterDeclaration(name: string | Identifier,
//        constraint?: TypeNode, defaultType?: TypeNode):
//        TypeParameterDeclaration;
node<TypeParameterDeclaration> Factory::createTypeParameterDeclaration(
    optional<variant<node<NodeArray>, tscpp::node<Node>, string>> modifiersOrName,
    optional<variant<node<TypeNode>, tscpp::node<Identifier>, string>>
        nameOrConstraint,
    optionalNode<TypeNode> constraintOrDefault,
    optionalNode<TypeNode> defaultType) {
  NameType name = "";
  optionalNode<NodeArray> modifiers;
  optionalNode<TypeNode> constraint = constraintOrDefault;

  if (modifiersOrName) {
    if (holds_alternative<node<NodeArray>>(*modifiersOrName)) {
      modifiers = get<node<NodeArray>>(*modifiersOrName);
    } else if (holds_alternative<string>(*modifiersOrName)) {
      name = get<string>(*modifiersOrName);
    } else if (holds_alternative<node<Node>>(*modifiersOrName)) {
      name = get<node<Node>>(*modifiersOrName);
    }
  }

  if (nameOrConstraint) {
    if (holds_alternative<node<TypeNode>>(*nameOrConstraint)) {
      constraint = get<node<TypeNode>>(*nameOrConstraint);
    } else if (holds_alternative<node<Identifier>>(*nameOrConstraint)) {
      name = get<node<Identifier>>(*nameOrConstraint);
    } else if (holds_alternative<string>(*nameOrConstraint)) {
      name = get<string>(*nameOrConstraint);
    }
  }

  //            if (!modifiersOrName || isArray(modifiersOrName)) {
  //                modifiers = modifiersOrName;
  //                name = nameOrConstraint as string | Identifier;
  //                constraint = constraintOrDefault;
  //            }
  //            else {
  //                modifiers = undefined;
  //                name = modifiersOrName;
  //                constraint = nameOrConstraint as TypeNode | undefined;
  //            }
  auto node = createBaseNamedDeclaration<TypeParameterDeclaration>(
      SyntaxKind::TypeParameter,
      /*decorators*/ nullptr, modifiers, name);
  node->constraint = constraint;
  node->defaultType = defaultType;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTypeParameterDeclaration(node:
//        TypeParameterDeclaration, optionalNode<NodeArray> modifiers, name:
//        Identifier, constraint: TypeNode | undefined,
//        defaultsharedOpt<TypeNode> type): TypeParameterDeclaration;
//        /** @deprecated */
//        function updateTypeParameterDeclaration(node:
//        TypeParameterDeclaration, name: Identifier, constraint: TypeNode |
//        undefined, defaultsharedOpt<TypeNode> type): TypeParameterDeclaration;
//        function updateTypeParameterDeclaration(node:
//        TypeParameterDeclaration, modifiersOrName: readonly Modifier[] |
//        Identifier | undefined, nameOrConstraint: Identifier | TypeNode |
//        undefined, constraintOrDefault: TypeNode | undefined, defaultType?:
//        TypeNode | undefined) {
//            let name;
//            let modifiers;
//            let constraint;
//            if (modifiersOrName == undefined || isArray(modifiersOrName)) {
//                modifiers = modifiersOrName;
//                name = nameOrConstraint as Identifier;
//                constraint = constraintOrDefault;
//            }
//            else {
//                modifiers = undefined;
//                name = modifiersOrName;
//                constraint = nameOrConstraint as TypeNode | undefined;
//            }
//            return node->modifiers != modifiers
//                || node->name != name
//                || node->constraint != constraint
//                || node->default != defaultType
//                ? update(createTypeParameterDeclaration(modifiers, name,
//                constraint, defaultType), node) : node;
//        }

// @api
node<ParameterDeclaration> Factory::createParameterDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    optionalNode<DotDotDotToken> dotDotDotToken, NameType name,
    optionalNode<QuestionToken> questionToken, optionalNode<TypeNode> type,
    optionalNode<Expression> initializer) {
  auto node = createBaseVariableLikeDeclaration<ParameterDeclaration>(
      SyntaxKind::Parameter, decorators, modifiers, name, type,
      initializer
          ? parenthesizer.parenthesizeExpressionForDisallowedComma(initializer)
          : nullptr);
  node->dotDotDotToken = dotDotDotToken;
  node->questionToken = questionToken;
  if (isThisIdentifier(node->name)) {
    node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  } else {
    node->transformFlags |= propagateChildFlags(node->dotDotDotToken) |
                            propagateChildFlags(node->questionToken);
    if (questionToken)
      node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
    if (modifiersToFlags(node->modifiers) &
        (int)ModifierFlags::ParameterPropertyModifier)
      node->transformFlags |=
          (int)TransformFlags::ContainsTypeScriptClassSyntax;
    if (!!initializer || !!dotDotDotToken)
      node->transformFlags |= (int)TransformFlags::ContainsES2015;
  }
  return node;
}

//        // @api
//        function updateParameterDeclaration(
//            node: ParameterDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            dotDotDotToken: DotDotDotToken | undefined,
//            name: string | BindingName,
//            optionalNode<QuestionToken> questionToken,
//            optionalNode<TypeNode> type,
//            optionalNode<Expression> initializer
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->dotDotDotToken != dotDotDotToken
//                || node->name != name
//                || node->questionToken != questionToken
//                || node->type != type
//                || node->initializer != initializer
//                ? update(createParameterDeclaration(decorators, modifiers,
//                dotDotDotToken, name, questionToken, type, initializer), node)
//                : node;
//        }
//
// @api
node<Decorator> Factory::createDecorator(node<Expression> expression) {
  auto node = createBaseNode<Decorator>(SyntaxKind::Decorator);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsTypeScript |
                          (int)TransformFlags::ContainsTypeScriptClassSyntax;
  return node;
}

//        // @api
//        function updateDecorator(node: Decorator, tscpp::node<Expression>
//        expression) {
//            return node->expression != expression
//                ? update(createDecorator(expression), node)
//                : node;
//        }
//
//        //
//        // Type Elements
//        //

// @api
node<PropertySignature> Factory::createPropertySignature(
    optionalNode<NodeArray> modifiers, NameType name,
    optionalNode<QuestionToken> questionToken, optionalNode<TypeNode> type) {
  auto node = createBaseNamedDeclaration<PropertySignature>(
      SyntaxKind::PropertySignature,
      /*decorators*/ nullptr, modifiers, name);
  node->type = type;
  node->questionToken = questionToken;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updatePropertySignature(
//            node: PropertySignature,
//            optionalNode<NodeArray> modifiers,
//            name: PropertyName,
//            optionalNode<QuestionToken> questionToken,
//            optionalNode<TypeNode> type
//        ) {
//            return node->modifiers != modifiers
//                || node->name != name
//                || node->questionToken != questionToken
//                || node->type != type
//                ? update(createPropertySignature(modifiers, name,
//                questionToken, type), node) : node;
//        }

// @api
node<PropertyDeclaration> Factory::createPropertyDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    NameType name, optionalNode<Node> questionOrExclamationToken,
    optionalNode<TypeNode> type, optionalNode<Expression> initializer) {
  auto node = createBaseVariableLikeDeclaration<PropertyDeclaration>(
      SyntaxKind::PropertyDeclaration, decorators, modifiers, name, type,
      initializer);
  node->questionToken =
      questionOrExclamationToken && isQuestionToken(questionOrExclamationToken)
          ? reinterpret_node<QuestionToken>(questionOrExclamationToken)
          : nullptr;
  node->exclamationToken =
      questionOrExclamationToken &&
              isExclamationToken(questionOrExclamationToken)
          ? reinterpret_node<ExclamationToken>(questionOrExclamationToken)
          : nullptr;
  node->transformFlags |= propagateChildFlags(node->questionToken) |
                          propagateChildFlags(node->exclamationToken) |
                          (int)TransformFlags::ContainsClassFields;
  if (isComputedPropertyName(node->name) ||
      (hasStaticModifier(node) && node->initializer)) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScriptClassSyntax;
  }
  if (questionOrExclamationToken ||
      modifiersToFlags(node->modifiers) & (int)ModifierFlags::Ambient) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}

//        // @api
//        function updatePropertyDeclaration(
//            node: PropertyDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            NameType name,
//            questionOrExclamationToken: QuestionToken | ExclamationToken |
//            undefined, optionalNode<TypeNode> type, optionalNode<Expression>
//            initializer
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->questionToken != (questionOrExclamationToken !=
//                undefined && isQuestionToken(questionOrExclamationToken) ?
//                questionOrExclamationToken : undefined)
//                || node->exclamationToken != (questionOrExclamationToken !=
//                undefined && isExclamationToken(questionOrExclamationToken) ?
//                questionOrExclamationToken : undefined)
//                || node->type != type
//                || node->initializer != initializer
//                ? update(createPropertyDeclaration(decorators, modifiers,
//                name, questionOrExclamationToken, type, initializer), node) :
//                node;
//        }
//
// @api
node<MethodSignature> Factory::createMethodSignature(
    optionalNode<NodeArray> modifiers, NameType name,
    optionalNode<QuestionToken> questionToken,
    optionalNode<NodeArray> typeParameters, node<NodeArray> parameters,
    optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<MethodSignature>(
      SyntaxKind::MethodSignature,
      /*decorators*/ nullptr, modifiers, name, typeParameters, parameters,
      type);
  node->questionToken = questionToken;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateMethodSignature(
//            node: MethodSignature,
//            optionalNode<NodeArray> modifiers,
//            name: PropertyName,
//            optionalNode<QuestionToken> questionToken,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return node->modifiers != modifiers
//                || node->name != name
//                || node->questionToken != questionToken
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ?
//                updateBaseSignatureDeclaration(createMethodSignature(modifiers,
//                name, questionToken, typeParameters, parameters, type), node)
//                : node;
//        }
//
// @api
node<MethodDeclaration> Factory::createMethodDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    optionalNode<AsteriskToken> asteriskToken, NameType name,
    optionalNode<QuestionToken> questionToken,
    optionalNode<NodeArray> typeParameters, node<NodeArray> parameters,
    optionalNode<TypeNode> type, optionalNode<Block> body) {
  auto node = createBaseFunctionLikeDeclaration<MethodDeclaration>(
      SyntaxKind::MethodDeclaration, decorators, modifiers, name,
      typeParameters, parameters, type, body);
  node->asteriskToken = asteriskToken;
  node->questionToken = questionToken;
  node->transformFlags |= propagateChildFlags(node->asteriskToken) |
                          propagateChildFlags(node->questionToken) |
                          (int)TransformFlags::ContainsES2015;
  if (questionToken) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Async) {
    if (asteriskToken) {
      node->transformFlags |= (int)TransformFlags::ContainsES2018;
    } else {
      node->transformFlags |= (int)TransformFlags::ContainsES2017;
    }
  } else if (asteriskToken) {
    node->transformFlags |= (int)TransformFlags::ContainsGenerator;
  }
  return node;
}

//        // @api
//        function updateMethodDeclaration(
//            node: MethodDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            optionalNode<AsteriskToken> asteriskToken,
//            name: PropertyName,
//            optionalNode<QuestionToken> questionToken,
//            optionalNode<NodeArray> typeParameters,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type,
//           optionalNode<Block> body
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->asteriskToken != asteriskToken
//                || node->name != name
//                || node->questionToken != questionToken
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createMethodDeclaration(decorators,
//                modifiers, asteriskToken, name, questionToken, typeParameters,
//                parameters, type, body), node) : node;
//        }
//
// @api
node<ClassStaticBlockDeclaration> Factory::createClassStaticBlockDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    node<Block> body) {
  auto node = createBaseNamedDeclaration<ClassStaticBlockDeclaration>(
      SyntaxKind::ClassStaticBlockDeclaration, decorators, modifiers,
      /*name*/ {});
  node->body = body;
  node->transformFlags =
      propagateChildFlags(body) | (int)TransformFlags::ContainsClassFields;
  return node;
}
//
//        // @api
//        function updateClassStaticBlockDeclaration(
//            node: ClassStaticBlockDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            node<Block> block
//        ): ClassStaticBlockDeclaration {
//            return node->decorators != decorators
//                || node->modifier != modifiers
//                || node->body != body
//                ? update(createClassStaticBlockDeclaration(decorators,
//                modifiers, body), node) : node;
//        }

// @api
node<ConstructorDeclaration> Factory::createConstructorDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    node<NodeArray> parameters, optionalNode<Block> body) {
  auto node = createBaseFunctionLikeDeclaration<ConstructorDeclaration>(
      SyntaxKind::Constructor, decorators, modifiers,
      /*name*/ {},
      /*typeParameters*/ {}, parameters,
      /*type*/ {}, body);
  node->transformFlags |= (int)TransformFlags::ContainsES2015;
  return node;
}

//        // @api
//        function updateConstructorDeclaration(
//            node: ConstructorDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            node<NodeArray> parameters,
//           optionalNode<Block> body
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->parameters != parameters
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createConstructorDeclaration(decorators,
//                modifiers, parameters, body), node) : node;
//        }
//
// @api
node<GetAccessorDeclaration> Factory::createGetAccessorDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    NameType name, node<NodeArray> parameters, optionalNode<TypeNode> type,
    optionalNode<Block> body) {
  return createBaseFunctionLikeDeclaration<GetAccessorDeclaration>(
      SyntaxKind::GetAccessor, decorators, modifiers, name,
      /*typeParameters*/ {}, parameters, type, body);
}

//        // @api
//        function updateGetAccessorDeclaration(
//            node: GetAccessorDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: PropertyName,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type,
//           optionalNode<Block> body
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->parameters != parameters
//                || node->type != type
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createGetAccessorDeclaration(decorators,
//                modifiers, name, parameters, type, body), node) : node;
//        }

// @api
node<SetAccessorDeclaration> Factory::createSetAccessorDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    NameType name, node<NodeArray> parameters, optionalNode<Block> body) {
  return createBaseFunctionLikeDeclaration<SetAccessorDeclaration>(
      SyntaxKind::SetAccessor, decorators, modifiers, name,
      /*typeParameters*/ {}, parameters,
      /*type*/ {}, body);
}

//        // @api
//        function updateSetAccessorDeclaration(
//            node: SetAccessorDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: PropertyName,
//            node<NodeArray> parameters,
//           optionalNode<Block> body
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->parameters != parameters
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createSetAccessorDeclaration(decorators,
//                modifiers, name, parameters, body), node) : node;
//        }
//
// @api
node<CallSignatureDeclaration> Factory::createCallSignature(
    optionalNode<NodeTypeArray(TypeParameterDeclaration)> typeParameters,
    node<NodeTypeArray(ParameterDeclaration)> parameters,
    optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<CallSignatureDeclaration>(
      SyntaxKind::CallSignature,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr,
      /*name*/ {}, typeParameters, parameters, type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateCallSignature(
//            node: CallSignatureDeclaration,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ?
//                updateBaseSignatureDeclaration(createCallSignature(typeParameters,
//                parameters, type), node) : node;
//        }
//
// @api
node<ConstructSignatureDeclaration> Factory::createConstructSignature(
    optionalNode<NodeArray> typeParameters, node<NodeArray> parameters,
    optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<ConstructSignatureDeclaration>(
      SyntaxKind::ConstructSignature,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr,
      /*name*/ {}, typeParameters, parameters, type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}
//
//        // @api
//        function updateConstructSignature(
//            node: ConstructSignatureDeclaration,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ?
//                updateBaseSignatureDeclaration(createConstructSignature(typeParameters,
//                parameters, type), node) : node;
//        }
//
// @api
node<IndexSignatureDeclaration> Factory::createIndexSignature(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    node<NodeArray> parameters, optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<IndexSignatureDeclaration>(
      SyntaxKind::IndexSignature, decorators, modifiers,
      /*name*/ {},
      /*typeParameters*/ {}, parameters, type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateIndexSignature(
//            node: IndexSignatureDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            node<NodeArray> parameters,
//            node<TypeNode> type
//        ) {
//            return node->parameters != parameters
//                || node->type != type
//                || node->decorators != decorators
//                || node->modifiers != modifiers
//                ?
//                updateBaseSignatureDeclaration(createIndexSignature(decorators,
//                modifiers, parameters, type), node) : node;
//        }

// @api
node<TemplateLiteralTypeSpan> Factory::createTemplateLiteralTypeSpan(
    node<TypeNode> type,
    tscpp::node<NodeUnion(TemplateMiddle, TemplateTail)> literal) {
  auto node = createBaseNode<TemplateLiteralTypeSpan>(
      SyntaxKind::TemplateLiteralTypeSpan);
  node->type = type;
  node->literal = literal;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTemplateLiteralTypeSpan(node: TemplateLiteralTypeSpan,
//        tscpp::node<TypeNode> type, literal: TemplateMiddle | TemplateTail) {
//            return node->type != type
//                || node->literal != literal
//                ? update(createTemplateLiteralTypeSpan(type, literal), node)
//                : node;
//        }
//
//        //
//        // Types
//        //
//
//        // @api
//        function createKeywordTypeNode<TKind extends
//        KeywordTypeSyntaxKind>(kind: TKind) {
//            return createToken(kind);
//        }
//
// @api
node<TypePredicateNode> Factory::createTypePredicateNode(
    optionalNode<AssertsKeyword> assertsModifier, NameType parameterName,
    optionalNode<TypeNode> type) {
  auto node = createBaseNode<TypePredicateNode>(SyntaxKind::TypePredicate);
  node->assertsModifier = assertsModifier;
  node->parameterName = asName(parameterName);
  node->type = type;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTypePredicateNode(node: TypePredicateNode,
//        assertsModifier: AssertsKeyword | undefined, parameterName: Identifier
//        | ThisTypeNode, optionalNode<TypeNode> type) {
//            return node->assertsModifier != assertsModifier
//                || node->parameterName != parameterName
//                || node->type != type
//                ? update(createTypePredicateNode(assertsModifier,
//                parameterName, type), node) : node;
//        }

// @api
node<TypeReferenceNode> Factory::createTypeReferenceNode(
    NameType typeName, optionalNode<NodeArray> typeArguments) {
  auto node = createBaseNode<TypeReferenceNode>(SyntaxKind::TypeReference);
  node->typeName = asName(typeName);
  if (typeArguments)
    node->typeArguments =
        parenthesizer.parenthesizeTypeArguments(createNodeArray(typeArguments));
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTypeReferenceNode(node: TypeReferenceNode, typeName:
//        EntityName, typeArguments: NodeArray<TypeNode> | undefined) {
//            return node->typeName != typeName
//                || node->typeArguments != typeArguments
//                ? update(createTypeReferenceNode(typeName, typeArguments),
//                node) : node;
//        }

// @api
node<FunctionTypeNode> Factory::createFunctionTypeNode(
    optionalNode<NodeArray> typeParameters, node<NodeArray> parameters,
    optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<FunctionTypeNode>(
      SyntaxKind::FunctionType,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr,
      /*name*/ {}, typeParameters, parameters, type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateFunctionTypeNode(
//            node: FunctionTypeNode,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ?
//                updateBaseSignatureDeclaration(createFunctionTypeNode(typeParameters,
//                parameters, type), node) : node;
//        }
//
//        // @api
//        function createConstructorTypeNode(...args: Parameters<typeof
//        createConstructorTypeNode1 | typeof createConstructorTypeNode2>) {
//            return args.length == 4 ? createConstructorTypeNode1(...args) :
//                args.length == 3 ? createConstructorTypeNode2(...args) :
//                Debug.fail("Incorrect number of arguments specified.");
//        }

node<ConstructorTypeNode> Factory::createConstructorTypeNode1(
    optionalNode<NodeArray> modifiers, optionalNode<NodeArray> typeParameters,
    node<NodeArray> parameters, optionalNode<TypeNode> type) {
  auto node = createBaseSignatureDeclaration<ConstructorTypeNode>(
      SyntaxKind::ConstructorType,
      /*decorators*/ nullptr, modifiers,
      /*name*/ {}, typeParameters, parameters, type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        /** @deprecated */
//        function createConstructorTypeNode2(
//            optionalNode<NodeArray> typeParameters,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type
//        ): ConstructorTypeNode {
//            return createConstructorTypeNode1(/*modifiers*/ nullptr,
//            typeParameters, parameters, type);
//        }
//
//        // @api
//        function updateConstructorTypeNode(...args: Parameters<typeof
//        updateConstructorTypeNode1 | typeof updateConstructorTypeNode2>) {
//            return args.length == 5 ? updateConstructorTypeNode1(...args) :
//                args.length == 4 ? updateConstructorTypeNode2(...args) :
//                Debug.fail("Incorrect number of arguments specified.");
//        }
//
//        function updateConstructorTypeNode1(
//            node: ConstructorTypeNode,
//            optionalNode<NodeArray> modifiers,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return node->modifiers != modifiers
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ?
//                updateBaseSignatureDeclaration(createConstructorTypeNode(modifiers,
//                typeParameters, parameters, type), node) : node;
//        }
//
//        /** @deprecated */
//        function updateConstructorTypeNode2(
//            node: ConstructorTypeNode,
//            typeParameters: NodeArray<TypeParameterDeclaration> | undefined,
//            parameters: NodeArray<ParameterDeclaration>,
//            optionalNode<TypeNode> type
//        ) {
//            return updateConstructorTypeNode1(node, node->modifiers,
//            typeParameters, parameters, type);
//        }
//
// @api
node<TypeQueryNode> Factory::createTypeQueryNode(
    node<NodeUnion(EntityName)> exprName,
    optionalNode<NodeArray> typeArguments) {
  auto node = createBaseNode<TypeQueryNode>(SyntaxKind::TypeQuery);
  node->exprName = exprName;
  if (typeArguments)
    node->typeArguments =
        parenthesizer.parenthesizeTypeArguments(typeArguments);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTypeQueryNode(node: TypeQueryNode, exprName:
//        EntityName, typeArguments?: readonly TypeNode[]) {
//            return node->exprName != exprName
//                || node->typeArguments != typeArguments
//                ? update(createTypeQueryNode(exprName, typeArguments), node)
//                : node;
//        }
//
// @api
node<TypeLiteralNode> Factory::createTypeLiteralNode(
    optionalNode<NodeArray> members) {
  auto node = createBaseNode<TypeLiteralNode>(SyntaxKind::TypeLiteral);
  node->members = createNodeArray(members);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}
//
//        // @api
//        function updateTypeLiteralNode(node: TypeLiteralNode, members:
//        NodeArray<TypeElement>) {
//            return node->members != members
//                ? update(createTypeLiteralNode(members), node)
//                : node;
//        }

// @api
node<ArrayTypeNode> Factory::createArrayTypeNode(node<TypeNode> elementType) {
  auto node = createBaseNode<ArrayTypeNode>(SyntaxKind::ArrayType);
  node->elementType =
      parenthesizer.parenthesizeNonArrayTypeOfPostfixType(elementType);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateArrayTypeNode(node: ArrayTypeNode, tscpp::node<TypeNode>
//        elementType): ArrayTypeNode {
//            return node->elementType != elementType
//                ? update(createArrayTypeNode(elementType), node)
//                : node;
//        }
//
// @api
node<TupleTypeNode> Factory::createTupleTypeNode(node<NodeArray> elements) {
  auto node = createBaseNode<TupleTypeNode>(SyntaxKind::TupleType);
  node->elements = createNodeArray(
      parenthesizer.parenthesizeElementTypesOfTupleType(elements));
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTupleTypeNode(node: TupleTypeNode, elements: readonly
//        (TypeNode | NamedTupleMember)[]) {
//            return node->elements != elements
//                ? update(createTupleTypeNode(elements), node)
//                : node;
//        }
//
// @api
node<NamedTupleMember> Factory::createNamedTupleMember(
    optionalNode<DotDotDotToken> dotDotDotToken, tscpp::node<Identifier> name,
    optionalNode<QuestionToken> questionToken, tscpp::node<TypeNode> type) {
  auto node = createBaseNode<NamedTupleMember>(SyntaxKind::NamedTupleMember);
  node->dotDotDotToken = dotDotDotToken;
  node->name = name;
  node->questionToken = questionToken;
  node->type = type;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateNamedTupleMember(node: NamedTupleMember,
//        dotDotDotToken: DotDotDotToken | undefined, name: Identifier,
//        optionalNode<QuestionToken> questionToken, tscpp::node<TypeNode> type) {
//            return node->dotDotDotToken != dotDotDotToken
//                || node->name != name
//                || node->questionToken != questionToken
//                || node->type != type
//                ? update(createNamedTupleMember(dotDotDotToken, name,
//                questionToken, type), node) : node;
//        }
//
//        // @api
//        function createOptionalTypeNode(node<TypeNode> type) {
//            auto node =
//            createBaseNode<OptionalTypeNode>(SyntaxKind::OptionalType);
//            node->type = parenthesizer.parenthesizeTypeOfOptionalType(type);
//            node->transformFlags = (int)TransformFlags::ContainsTypeScript;
//            return node;
//        }
//
//        // @api
//        function updateOptionalTypeNode(node: OptionalTypeNode,
//        tscpp::node<TypeNode> type): OptionalTypeNode {
//            return node->type != type
//                ? update(createOptionalTypeNode(type), node)
//                : node;
//        }
//
// @api
node<RestTypeNode> Factory::createRestTypeNode(node<TypeNode> type) {
  auto node = createBaseNode<RestTypeNode>(SyntaxKind::RestType);
  node->type = type;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateRestTypeNode(node: RestTypeNode, tscpp::node<TypeNode>
//        type): RestTypeNode {
//            return node->type != type
//                ? update(createRestTypeNode(type), node)
//                : node;
//        }

//        function updateUnionOrIntersectionTypeNode<T extends
//        UnionOrIntersectionTypeNode>(node: T, types: NodeArray<TypeNode>,
//        parenthesize: (nodes: readonly TypeNode[]) => readonly TypeNode[]): T
//        {
//            return node->types != types
//                ? update(createUnionOrIntersectionTypeNode(node->kind, types,
//                parenthesize) as T, node) : node;
//        }

// @api
node<UnionTypeNode> Factory::createUnionTypeNode(node<NodeArray> types) {
  return createUnionOrIntersectionTypeNode<UnionTypeNode>(
      SyntaxKind::UnionType, types,
      CALLBACK(parenthesizer.parenthesizeConstituentTypesOfUnionType));
}

//        // @api
//        function updateUnionTypeNode(node: UnionTypeNode, types:
//        NodeArray<TypeNode>) {
//            return updateUnionOrIntersectionTypeNode(node, types,
//            parenthesizer.parenthesizeConstituentTypesOfUnionType);
//        }

// @api
node<IntersectionTypeNode> Factory::createIntersectionTypeNode(
    node<NodeArray> types) {
  return createUnionOrIntersectionTypeNode<IntersectionTypeNode>(
      SyntaxKind::IntersectionType, types,
      CALLBACK(parenthesizer.parenthesizeConstituentTypesOfIntersectionType));
}

//        // @api
//        function updateIntersectionTypeNode(node: IntersectionTypeNode, types:
//        NodeArray<TypeNode>) {
//            return updateUnionOrIntersectionTypeNode(node, types,
//            parenthesizer.parenthesizeConstituentTypesOfIntersectionType);
//        }

// @api
node<ConditionalTypeNode> Factory::createConditionalTypeNode(
    node<TypeNode> checkType, tscpp::node<TypeNode> extendsType,
    tscpp::node<TypeNode> trueType, tscpp::node<TypeNode> falseType) {
  auto node = createBaseNode<ConditionalTypeNode>(SyntaxKind::ConditionalType);
  node->checkType =
      parenthesizer.parenthesizeCheckTypeOfConditionalType(checkType);
  node->extendsType =
      parenthesizer.parenthesizeExtendsTypeOfConditionalType(extendsType);
  node->trueType = trueType;
  node->falseType = falseType;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateConditionalTypeNode(node: ConditionalTypeNode,
//        checkType: TypeNode, extendsType: TypeNode, trueType: TypeNode,
//        falseType: TypeNode) {
//            return node->checkType != checkType
//                || node->extendsType != extendsType
//                || node->trueType != trueType
//                || node->falseType != falseType
//                ? update(createConditionalTypeNode(checkType, extendsType,
//                trueType, falseType), node) : node;
//        }
//
// @api
node<InferTypeNode> Factory::createInferTypeNode(
    node<TypeParameterDeclaration> typeParameter) {
  auto node = createBaseNode<InferTypeNode>(SyntaxKind::InferType);
  node->typeParameter = typeParameter;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateInferTypeNode(node: InferTypeNode, typeParameter:
//        TypeParameterDeclaration) {
//            return node->typeParameter != typeParameter
//                ? update(createInferTypeNode(typeParameter), node)
//                : node;
//        }

// @api
node<TemplateLiteralTypeNode> Factory::createTemplateLiteralType(
    node<TemplateHead> head, tscpp::node<NodeArray> templateSpans) {
  auto node =
      createBaseNode<TemplateLiteralTypeNode>(SyntaxKind::TemplateLiteralType);
  node->head = head;
  node->templateSpans = createNodeArray(templateSpans);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTemplateLiteralType(node: TemplateLiteralTypeNode,
//        head: TemplateHead, templateSpans: readonly TemplateLiteralTypeSpan[])
//        {
//            return node->head != head
//                || node->templateSpans != templateSpans
//                ? update(createTemplateLiteralType(head, templateSpans), node)
//                : node;
//        }
//
//        // @api
//        function createImportTypeNode(argument: TypeNode, qualifier?:
//        EntityName, typeArguments?: readonly TypeNode[], isTypeOf?: boolean):
//        ImportTypeNode; function createImportTypeNode(argument: TypeNode,
//        assertions?: ImportTypeAssertionContainer, qualifier?: EntityName,
//        typeArguments?: readonly TypeNode[], isTypeOf?: boolean):
//        ImportTypeNode;
node<ImportTypeNode> Factory::createImportTypeNode(
    node<TypeNode> argument,
    optional<variant<node<NodeUnion(EntityName)>,
                     tscpp::node<ImportTypeAssertionContainer>>>
        qualifierOrAssertions,
    optional<variant<node<NodeUnion(EntityName)>, tscpp::node<NodeArray>>>
        typeArgumentsOrQualifier,
    optional<variant<bool, tscpp::node<NodeArray>>> isTypeOfOrTypeArguments,
    optional<bool> isTypeOf) {
  optionalNode<ImportTypeAssertionContainer> assertion;
  optionalNode<NodeUnion(EntityName)> qualifier;
  optionalNode<NodeArray> typeArguments;
  if (qualifierOrAssertions) {
    if (holds_alternative<node<ImportTypeAssertionContainer>>(
            *qualifierOrAssertions)) {
      assertion =
          get<node<ImportTypeAssertionContainer>>(*qualifierOrAssertions);
    } else if (holds_alternative<node<NodeUnion(EntityName)>>(
                   *qualifierOrAssertions)) {
      qualifier = get<node<NodeUnion(EntityName)>>(*qualifierOrAssertions);
    }
  }

  if (typeArgumentsOrQualifier) {
    if (holds_alternative<node<NodeArray>>(*typeArgumentsOrQualifier)) {
      typeArguments = get<node<NodeArray>>(*typeArgumentsOrQualifier);
    } else if (holds_alternative<node<NodeUnion(EntityName)>>(
                   *typeArgumentsOrQualifier)) {
      qualifier = get<node<NodeUnion(EntityName)>>(*typeArgumentsOrQualifier);
    }
  }

  if (isTypeOfOrTypeArguments) {
    if (holds_alternative<node<NodeArray>>(*isTypeOfOrTypeArguments)) {
      typeArguments = get<node<NodeArray>>(*isTypeOfOrTypeArguments);
    } else if (holds_alternative<bool>(*isTypeOfOrTypeArguments)) {
      isTypeOf = get<bool>(*isTypeOfOrTypeArguments);
    }
  }

  //            auto assertion = qualifierOrAssertions &&
  //            qualifierOrAssertions.kind ==
  //            SyntaxKind::ImportTypeAssertionContainer ? qualifierOrAssertions
  //            : undefined; auto qualifier = qualifierOrAssertions &&
  //            isEntityName(qualifierOrAssertions) ? qualifierOrAssertions
  //                : typeArgumentsOrQualifier &&
  //                !isArray(typeArgumentsOrQualifier) ?
  //                typeArgumentsOrQualifier : undefined;
  //            auto typeArguments = isArray(typeArgumentsOrQualifier) ?
  //            typeArgumentsOrQualifier : isArray(isTypeOfOrTypeArguments) ?
  //            isTypeOfOrTypeArguments : undefined; isTypeOf = typeof
  //            isTypeOfOrTypeArguments == "boolean" ? isTypeOfOrTypeArguments :
  //            typeof isTypeOf == "boolean" ? isTypeOf : false;

  auto node = createBaseNode<ImportTypeNode>(SyntaxKind::ImportType);
  node->argument = argument;
  node->assertions = assertion;
  node->qualifier = qualifier;
  if (typeArguments)
    node->typeArguments =
        parenthesizer.parenthesizeTypeArguments(typeArguments);
  node->isTypeOf = isTrue(isTypeOf);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateImportTypeNode(node: ImportTypeNode, argument:
//        TypeNode, qualifier: EntityName | undefined, optionalNode<NodeArray>
//        typeArguments, isTypeOf?: boolean | undefined): ImportTypeNode;
//        function updateImportTypeNode(node: ImportTypeNode, argument:
//        TypeNode, assertions: ImportTypeAssertionContainer | undefined,
//        qualifier: EntityName | undefined, optionalNode<NodeArray>
//        typeArguments, isTypeOf?: boolean | undefined): ImportTypeNode;
//        function updateImportTypeNode(
//            node: ImportTypeNode,
//            argument: TypeNode,
//            qualifierOrAssertions: EntityName | ImportTypeAssertionContainer |
//            undefined, typeArgumentsOrQualifier: readonly TypeNode[] |
//            EntityName | undefined, isTypeOfOrTypeArguments: boolean |
//            readonly TypeNode[] | undefined, isTypeOf?: boolean | undefined
//        ) {
//            auto assertion = qualifierOrAssertions &&
//            qualifierOrAssertions.kind ==
//            SyntaxKind::ImportTypeAssertionContainer ? qualifierOrAssertions :
//            undefined; auto qualifier = qualifierOrAssertions &&
//            isEntityName(qualifierOrAssertions) ? qualifierOrAssertions
//                : typeArgumentsOrQualifier &&
//                !isArray(typeArgumentsOrQualifier) ? typeArgumentsOrQualifier
//                : undefined;
//            auto typeArguments = isArray(typeArgumentsOrQualifier) ?
//            typeArgumentsOrQualifier : isArray(isTypeOfOrTypeArguments) ?
//            isTypeOfOrTypeArguments : undefined; isTypeOf = typeof
//            isTypeOfOrTypeArguments == "boolean" ? isTypeOfOrTypeArguments :
//            typeof isTypeOf == "boolean" ? isTypeOf : node->isTypeOf;
//
//            return node->argument != argument
//                || node->assertions != assertion
//                || node->qualifier != qualifier
//                || node->typeArguments != typeArguments
//                || node->isTypeOf != isTypeOf
//                ? update(createImportTypeNode(argument, assertion, qualifier,
//                typeArguments, isTypeOf), node) : node;
//        }

// @api
node<ParenthesizedTypeNode> Factory::createParenthesizedType(
    node<TypeNode> type) {
  auto node =
      createBaseNode<ParenthesizedTypeNode>(SyntaxKind::ParenthesizedType);
  node->type = type;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateParenthesizedType(node: ParenthesizedTypeNode,
//        tscpp::node<TypeNode> type) {
//            return node->type != type
//                ? update(createParenthesizedType(type), node)
//                : node;
//        }

// @api
node<ThisTypeNode> Factory::createThisTypeNode() {
  auto node = createBaseNode<ThisTypeNode>(SyntaxKind::ThisType);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

// @api
node<TypeOperatorNode> Factory::createTypeOperatorNode(
    SyntaxKind operatorKind, tscpp::node<TypeNode> type) {
  auto node = createBaseNode<TypeOperatorNode>(SyntaxKind::TypeOperator);
  node->operatorKind = operatorKind;
  node->type =
      operatorKind == SyntaxKind::ReadonlyKeyword
          ? parenthesizer.parenthesizeOperandOfReadonlyTypeOperator(type)
          : parenthesizer.parenthesizeOperandOfTypeOperator(type);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateTypeOperatorNode(node: TypeOperatorNode,
//        tscpp::node<TypeNode> type) {
//            return node->type != type
//                ? update(createTypeOperatorNode(node->operator, type), node)
//                : node;
//        }

// @api
node<IndexedAccessTypeNode> Factory::createIndexedAccessTypeNode(
    node<TypeNode> objectType, tscpp::node<TypeNode> indexType) {
  auto node =
      createBaseNode<IndexedAccessTypeNode>(SyntaxKind::IndexedAccessType);
  node->objectType =
      parenthesizer.parenthesizeNonArrayTypeOfPostfixType(objectType);
  node->indexType = indexType;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateIndexedAccessTypeNode(node: IndexedAccessTypeNode,
//        objectType: TypeNode, indexType: TypeNode) {
//            return node->objectType != objectType
//                || node->indexType != indexType
//                ? update(createIndexedAccessTypeNode(objectType, indexType),
//                node) : node;
//        }

// @api
node<MappedTypeNode> Factory::createMappedTypeNode(
    optionalNode<Node> readonlyToken,  //: ReadonlyKeyword | PlusToken |
                                       //: MinusToken | undefined,
    node<TypeParameterDeclaration> typeParameter,
    optionalNode<TypeNode> nameType,
    optionalNode<Node>
        questionToken,  //: QuestionToken | PlusToken | MinusToken | undefined,
    optionalNode<TypeNode> type, optionalNode<NodeArray> members) {
  auto node = createBaseNode<MappedTypeNode>(SyntaxKind::MappedType);
  node->readonlyToken = readonlyToken;
  node->typeParameter = typeParameter;
  node->nameType = nameType;
  node->questionToken = questionToken;
  node->type = type;
  if (members)
    node->members = createNodeArray(members);
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateMappedTypeNode(node: MappedTypeNode, readonlyToken:
//        ReadonlyKeyword | PlusToken | MinusToken | undefined, typeParameter:
//        TypeParameterDeclaration, namesharedOpt<TypeNode> type, questionToken:
//        QuestionToken | PlusToken | MinusToken | undefined,
//        optionalNode<TypeNode> type, optionalNode<NodeArray> members):
//        MappedTypeNode {
//            return node->readonlyToken != readonlyToken
//                || node->typeParameter != typeParameter
//                || node->nameType != nameType
//                || node->questionToken != questionToken
//                || node->type != type
//                || node->members != members
//                ? update(createMappedTypeNode(readonlyToken, typeParameter,
//                nameType, questionToken, type, members), node) : node;
//        }
//
// @api
node<LiteralTypeNode> Factory::createLiteralTypeNode(node<Expression> literal) {
  auto node = createBaseNode<LiteralTypeNode>(SyntaxKind::LiteralType);
  node->literal = literal;
  node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  return node;
}

//        // @api
//        function updateLiteralTypeNode(node: LiteralTypeNode, literal:
//        LiteralTypeNode["literal"]) {
//            return node->literal != literal
//                ? update(createLiteralTypeNode(literal), node)
//                : node;
//        }
//
//        //
//        // Binding Patterns
//        //
//
// @api
node<ObjectBindingPattern> Factory::createObjectBindingPattern(
    node<NodeArray> elements) {
  auto node =
      createBaseNode<ObjectBindingPattern>(SyntaxKind::ObjectBindingPattern);
  node->elements = createNodeArray(elements);
  node->transformFlags |= propagateChildrenFlags(node->elements) |
                          (int)TransformFlags::ContainsES2015 |
                          (int)TransformFlags::ContainsBindingPattern;
  if (node->transformFlags & (int)TransformFlags::ContainsRestOrSpread) {
    node->transformFlags |= (int)TransformFlags::ContainsES2018 |
                            (int)TransformFlags::ContainsObjectRestOrSpread;
  }
  return node;
}
//
//        // @api
//        function updateObjectBindingPattern(node: ObjectBindingPattern,
//        elements: readonly BindingElement[]) {
//            return node->elements != elements
//                ? update(createObjectBindingPattern(elements), node)
//                : node;
//        }
//
// @api
node<ArrayBindingPattern> Factory::createArrayBindingPattern(
    node<NodeArray> elements) {
  auto node =
      createBaseNode<ArrayBindingPattern>(SyntaxKind::ArrayBindingPattern);
  node->elements = createNodeArray(elements);
  node->transformFlags |= propagateChildrenFlags(node->elements) |
                          (int)TransformFlags::ContainsES2015 |
                          (int)TransformFlags::ContainsBindingPattern;
  return node;
}

//        // @api
//        function updateArrayBindingPattern(node: ArrayBindingPattern,
//        elements: readonly ArrayBindingElement[]) {
//            return node->elements != elements
//                ? update(createArrayBindingPattern(elements), node)
//                : node;
//        }
//
// @api
node<BindingElement> Factory::createBindingElement(
    optionalNode<DotDotDotToken> dotDotDotToken,
    optional<variant<string, tscpp::node<NodeUnion(PropertyName)>>> propertyName,
    variant<string, tscpp::node<NodeUnion(BindingName)>> name,
    optionalNode<Expression> initializer) {
  auto node = createBaseBindingLikeDeclaration<BindingElement>(
      SyntaxKind::BindingElement,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr, name,
      initializer
          ? parenthesizer.parenthesizeExpressionForDisallowedComma(initializer)
          : nullptr);
  node->propertyName = asName(*propertyName);
  node->dotDotDotToken = dotDotDotToken;
  node->transformFlags |= propagateChildFlags(node->dotDotDotToken) |
                          (int)TransformFlags::ContainsES2015;
  if (node->propertyName) {
    node->transformFlags |=
        isIdentifier(node->propertyName)
            ? propagateIdentifierNameFlags(node->propertyName)
            : propagateChildFlags(node->propertyName);
  }
  if (dotDotDotToken)
    node->transformFlags |= (int)TransformFlags::ContainsRestOrSpread;
  return node;
}

//        // @api
//        function updateBindingElement(node: BindingElement, dotDotDotToken:
//        DotDotDotToken | undefined, propertyName: PropertyName | undefined,
//        name: BindingName, optionalNode<Expression> initializer) {
//            return node->propertyName != propertyName
//                || node->dotDotDotToken != dotDotDotToken
//                || node->name != name
//                || node->initializer != initializer
//                ? update(createBindingElement(dotDotDotToken, propertyName,
//                name, initializer), node) : node;
//        }
//
//        //
//        // Expression
//        //

// @api
node<ArrayLiteralExpression> Factory::createArrayLiteralExpression(
    optionalNode<NodeArray> elements, bool multiLine) {
  auto node = createBaseExpression<ArrayLiteralExpression>(
      SyntaxKind::ArrayLiteralExpression);
  // Ensure we add a trailing comma for something like `[NumericLiteral(1),
  // NumericLiteral(2), OmittedExpresion]` so that we end up with `[1, 2, ,]`
  // instead of `[1, 2, ]` otherwise the `OmittedExpression` will just end up
  // being treated like a trailing comma.
  optionalNode<Node> lastElement =
      elements ? lastOrUndefined(elements) : nullptr;
  auto elementsArray = createNodeArray(
      elements, lastElement && isOmittedExpression(lastElement) ? true : false);
  node->elements =
      parenthesizer.parenthesizeExpressionsOfCommaDelimitedList(elementsArray);
  node->multiLine = multiLine;
  node->transformFlags |= propagateChildrenFlags(node->elements);
  return node;
}

//        // @api
//        function updateArrayLiteralExpression(node: ArrayLiteralExpression,
//        elements: readonly Expression[]) {
//            return node->elements != elements
//                ? update(createArrayLiteralExpression(elements,
//                node->multiLine), node) : node;
//        }

// @api
node<ObjectLiteralExpression> Factory::createObjectLiteralExpression(
    optionalNode<NodeArray> properties, bool multiLine) {
  auto node = createBaseExpression<ObjectLiteralExpression>(
      SyntaxKind::ObjectLiteralExpression);
  node->properties = createNodeArray(properties);
  node->multiLine = multiLine;
  node->transformFlags |= propagateChildrenFlags(node->properties);
  return node;
}

//        // @api
//        function updateObjectLiteralExpression(node: ObjectLiteralExpression,
//        properties: readonly ObjectLiteralElementLike[]) {
//            return node->properties != properties
//                ? update(createObjectLiteralExpression(properties,
//                node->multiLine), node) : node;
//        }
//
// @api
node<PropertyAccessExpression> Factory::createPropertyAccessExpression(
    node<Expression> expression, NameType _name) {
  auto node = createBaseExpression<PropertyAccessExpression>(
      SyntaxKind::PropertyAccessExpression);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->name = asName(_name);
  node->transformFlags =
      propagateChildFlags(node->expression) |
      (isIdentifier(node->name) ? propagateIdentifierNameFlags(node->name)
                                : propagateChildFlags(node->name));
  if (isSuperKeyword(expression)) {
    // super method calls require a lexical 'this'
    // super method calls require 'super' hoisting in ES2017 and ES2018 async
    // functions and async generators
    node->transformFlags |= (int)TransformFlags::ContainsES2017 |
                            (int)TransformFlags::ContainsES2018;
  }
  return node;
}

// @api
node<PropertyAccessExpression> Factory::createPropertyAccessChain(
    node<Expression> expression,
    optionalNode<QuestionDotToken> questionDotToken, NameType name) {
  auto node = createBaseExpression<PropertyAccessExpression>(
      SyntaxKind::PropertyAccessExpression);
  node->flags |= (int)NodeFlags::OptionalChain;
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->questionDotToken = questionDotToken;
  node->name = asName(name);
  node->transformFlags |=
      (int)TransformFlags::ContainsES2020 |
      propagateChildFlags(node->expression) |
      propagateChildFlags(node->questionDotToken) |
      (isIdentifier(node->name) ? propagateIdentifierNameFlags(node->name)
                                : propagateChildFlags(node->name));
  return node;
}

//        // @api
//        function updatePropertyAccessExpression(node:
//        PropertyAccessExpression, tscpp::node<Expression> expression, name:
//        Identifier | PrivateIdentifier) {
//            if (isPropertyAccessChain(node)) {
//                return updatePropertyAccessChain(node, expression,
//                node->questionDotToken, cast(name, isIdentifier));
//            }
//            return node->expression != expression
//                || node->name != name
//                ? update(createPropertyAccessExpression(expression, name),
//                node) : node;
//        }
//
//
//        // @api
//        function updatePropertyAccessChain(node: PropertyAccessChain,
//        tscpp::node<Expression> expression, optionalNode<QuestionDotToken>
//        questionDotToken, name: Identifier | PrivateIdentifier) {
//            Debug::asserts(!!(node->flags & NodeFlags::OptionalChain), "Cannot
//            update a PropertyAccessExpression using updatePropertyAccessChain.
//            Use updatePropertyAccess instead.");
//            // Because we are updating an existing PropertyAccessChain we want
//            to inherit its emitFlags
//            // instead of using the default from createPropertyAccess
//            return node->expression != expression
//                || node->questionDotToken != questionDotToken
//                || node->name != name
//                ? update(createPropertyAccessChain(expression,
//                questionDotToken, name), node) : node;
//        }
//
// @api
node<ElementAccessExpression> Factory::createElementAccessExpression(
    node<Expression> expression, ExpressionType index) {
  auto node = createBaseExpression<ElementAccessExpression>(
      SyntaxKind::ElementAccessExpression);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->argumentExpression = asExpression(index);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->argumentExpression);
  if (isSuperKeyword(expression)) {
    // super method calls require a lexical 'this'
    // super method calls require 'super' hoisting in ES2017 and ES2018 async
    // functions and async generators
    node->transformFlags |= (int)TransformFlags::ContainsES2017 |
                            (int)TransformFlags::ContainsES2018;
  }
  return node;
}
//
//        // @api
//        function updateElementAccessExpression(node: ElementAccessExpression,
//        tscpp::node<Expression> expression, argumentExpression: Expression) {
//            if (isElementAccessChain(node)) {
//                return updateElementAccessChain(node, expression,
//                node->questionDotToken, argumentExpression);
//            }
//            return node->expression != expression
//                || node->argumentExpression != argumentExpression
//                ? update(createElementAccessExpression(expression,
//                argumentExpression), node) : node;
//        }
//
// @api
node<ElementAccessExpression> Factory::createElementAccessChain(
    node<Expression> expression,
    optionalNode<QuestionDotToken> questionDotToken, ExpressionType index) {
  auto node = createBaseExpression<ElementAccessExpression>(
      SyntaxKind::ElementAccessExpression);
  node->flags |= (int)NodeFlags::OptionalChain;
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->questionDotToken = questionDotToken;
  node->argumentExpression = asExpression(index);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->questionDotToken) |
                          propagateChildFlags(node->argumentExpression) |
                          (int)TransformFlags::ContainsES2020;
  return node;
}

//        // @api
//        function updateElementAccessChain(node: ElementAccessChain,
//        tscpp::node<Expression> expression, optionalNode<QuestionDotToken>
//        questionDotToken, argumentExpression: Expression) {
//            Debug::asserts(!!(node->flags & NodeFlags::OptionalChain), "Cannot
//            update a ElementAccessExpression using updateElementAccessChain.
//            Use updateElementAccess instead.");
//            // Because we are updating an existing ElementAccessChain we want
//            to inherit its emitFlags
//            // instead of using the default from createElementAccess
//            return node->expression != expression
//                || node->questionDotToken != questionDotToken
//                || node->argumentExpression != argumentExpression
//                ? update(createElementAccessChain(expression,
//                questionDotToken, argumentExpression), node) : node;
//        }
//
// @api
node<CallExpression> Factory::createCallExpression(
    node<Expression> expression, optionalNode<NodeArray> typeArguments,
    optionalNode<NodeArray> argumentsArray) {
  auto node = createBaseExpression<CallExpression>(SyntaxKind::CallExpression);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->typeArguments = asNodeArray(typeArguments);
  node->arguments = parenthesizer.parenthesizeExpressionsOfCommaDelimitedList(
      createNodeArray(argumentsArray));
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildrenFlags(node->arguments);
  if (node->typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  if (isImportKeyword(node->expression)) {
    node->transformFlags |= (int)TransformFlags::ContainsDynamicImport;
  } else if (isSuperProperty(node->expression)) {
    node->transformFlags |= (int)TransformFlags::ContainsLexicalThis;
  }
  return node;
}

// @api
node<CallChain> Factory::createCallChain(
    node<Expression> expression,
    optionalNode<QuestionDotToken> questionDotToken,
    optionalNode<NodeArray> typeArguments,
    optionalNode<NodeArray> argumentsArray) {
  auto node = createBaseExpression<CallChain>(SyntaxKind::CallExpression);
  node->flags |= (int)NodeFlags::OptionalChain;
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->questionDotToken = questionDotToken;
  node->typeArguments = asNodeArray(typeArguments);
  node->arguments = parenthesizer.parenthesizeExpressionsOfCommaDelimitedList(
      createNodeArray(argumentsArray));
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->questionDotToken) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildrenFlags(node->arguments) |
                          (int)TransformFlags::ContainsES2020;
  if (node->typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  if (isSuperProperty(node->expression)) {
    node->transformFlags |= (int)TransformFlags::ContainsLexicalThis;
  }
  return node;
}

// @api
node<CallChain> Factory::updateCallChain(
    node<CallChain> node, tscpp::node<Expression> expression,
    optionalNode<QuestionDotToken> questionDotToken,
    optionalNode<NodeArray> typeArguments, tscpp::node<NodeArray> argumentsArray) {
  Debug::asserts(!!(node->flags & (int)NodeFlags::OptionalChain),
                 "Cannot update a CallExpression using updateCallChain. Use "
                 "updateCall instead.");
  return node->expression != expression ||
                 node->questionDotToken != questionDotToken ||
                 node->typeArguments != typeArguments ||
                 node->arguments != argumentsArray
             ? update(createCallChain(expression, questionDotToken,
                                      typeArguments, argumentsArray),
                      node)
             : node;
}

// @api
node<CallExpression> Factory::updateCallExpression(
    node<CallExpression> node, tscpp::node<Expression> expression,
    optionalNode<NodeArray> typeArguments, tscpp::node<NodeArray> argumentsArray) {
  if (isCallChain(node)) {
    return updateCallChain(node, expression, node->questionDotToken,
                           typeArguments, argumentsArray);
  }
  return node->expression != expression ||
                 node->typeArguments != typeArguments ||
                 node->arguments != argumentsArray
             ? update(createCallExpression(expression, typeArguments,
                                           argumentsArray),
                      node)
             : node;
}

// @api
node<NewExpression> Factory::createNewExpression(
    node<Expression> expression, optionalNode<NodeArray> typeArguments,
    optionalNode<NodeArray> argumentsArray) {
  auto node = createBaseExpression<NewExpression>(SyntaxKind::NewExpression);
  node->expression = parenthesizer.parenthesizeExpressionOfNew(expression);
  node->typeArguments = asNodeArray(typeArguments);
  if (argumentsArray)
    node->arguments = parenthesizer.parenthesizeExpressionsOfCommaDelimitedList(
        argumentsArray);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildrenFlags(node->arguments) |
                          (int)TransformFlags::ContainsES2020;
  if (node->typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}

//        // @api
//        function updateNewExpression(node: NewExpression, tscpp::node<Expression>
//        expression, optionalNode<NodeArray> typeArguments,
//        optionalNode<NodeArray> argumentsArray) {
//            return node->expression != expression
//                || node->typeArguments != typeArguments
//                || node->arguments != argumentsArray
//                ? update(createNewExpression(expression, typeArguments,
//                argumentsArray), node) : node;
//        }

// @api
node<TaggedTemplateExpression> Factory::createTaggedTemplateExpression(
    node<Expression> tag, optionalNode<NodeArray> typeArguments,
    tscpp::node<NodeUnion(TemplateLiteralTypes)> templateLiteral) {
  auto node = createBaseExpression<TaggedTemplateExpression>(
      SyntaxKind::TaggedTemplateExpression);
  node->tag = parenthesizer.parenthesizeLeftSideOfAccess(tag);
  node->typeArguments = asNodeArray(typeArguments);
  node->templateLiteral = templateLiteral;
  node->transformFlags |= propagateChildFlags(node->tag) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildFlags(node->templateLiteral) |
                          (int)TransformFlags::ContainsES2015;
  if (node->typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  if (hasInvalidEscape(node->templateLiteral)) {
    node->transformFlags |= (int)TransformFlags::ContainsES2018;
  }
  return node;
}
//
//        // @api
//        function updateTaggedTemplateExpression(node:
//        TaggedTemplateExpression, tag: Expression, optionalNode<NodeArray>
//        typeArguments, template: TemplateLiteral) {
//            return node->tag != tag
//                || node->typeArguments != typeArguments
//                || node->template != template
//                ? update(createTaggedTemplateExpression(tag, typeArguments,
//                template), node) : node;
//        }

// @api
node<TypeAssertion> Factory::createTypeAssertion(
    node<TypeNode> type, tscpp::node<Expression> expression) {
  auto node =
      createBaseExpression<TypeAssertion>(SyntaxKind::TypeAssertionExpression);
  node->expression = parenthesizer.parenthesizeOperandOfPrefixUnary(expression);
  node->type = type;
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->type) |
                          (int)TransformFlags::ContainsTypeScript;
  return node;
}

// @api
node<TypeAssertion> Factory::updateTypeAssertion(
    node<TypeAssertion> node, tscpp::node<TypeNode> type,
    tscpp::node<Expression> expression) {
  return node->type != type || node->expression != expression
             ? update(createTypeAssertion(type, expression), node)
             : node;
}

// @api
node<ParenthesizedExpression> Factory::createParenthesizedExpression(
    node<Expression> expression) {
  auto node = createBaseExpression<ParenthesizedExpression>(
      SyntaxKind::ParenthesizedExpression);
  node->expression = expression;
  node->transformFlags = propagateChildFlags(node->expression);
  return node;
}

// @api
node<ParenthesizedExpression> Factory::updateParenthesizedExpression(
    node<ParenthesizedExpression> node, tscpp::node<Expression> expression) {
  return node->expression != expression
             ? update(createParenthesizedExpression(expression), node)
             : node;
}

// @api
node<FunctionExpression> Factory::createFunctionExpression(
    optionalNode<NodeArray> modifiers,
    optionalNode<AsteriskToken> asteriskToken, NameType name,
    optionalNode<NodeArray> typeParameters, optionalNode<NodeArray> parameters,
    optionalNode<TypeNode> type, node<Block> body) {
  auto node = createBaseFunctionLikeDeclaration<FunctionExpression>(
      SyntaxKind::FunctionExpression,
      /*decorators*/ nullptr, modifiers, name, typeParameters, parameters, type,
      body);
  node->asteriskToken = asteriskToken;
  node->transformFlags |= propagateChildFlags(node->asteriskToken);
  if (node->typeParameters) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Async) {
    if (node->asteriskToken) {
      node->transformFlags |= (int)TransformFlags::ContainsES2018;
    } else {
      node->transformFlags |= (int)TransformFlags::ContainsES2017;
    }
  } else if (node->asteriskToken) {
    node->transformFlags |= (int)TransformFlags::ContainsGenerator;
  }
  return node;
}

//        // @api
//        function updateFunctionExpression(
//            node: FunctionExpression,
//            optionalNode<NodeArray> modifiers,
//            optionalNode<AsteriskToken> asteriskToken,
//            name: Identifier | undefined,
//            optionalNode<NodeArray> typeParameters,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type,
//            node<Block> block
//        ) {
//            return node->name != name
//                || node->modifiers != modifiers
//                || node->asteriskToken != asteriskToken
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createFunctionExpression(modifiers,
//                asteriskToken, name, typeParameters, parameters, type, body),
//                node) : node;
//        }
// @api
node<ArrowFunction> Factory::createArrowFunction(
    optionalNode<NodeArray> modifiers, optionalNode<NodeArray> typeParameters,
    node<NodeArray> parameters, optionalNode<TypeNode> type,
    optionalNode<EqualsGreaterThanToken> equalsGreaterThanToken,
    node<NodeUnion(ConciseBody)> body) {
  auto node = createBaseFunctionLikeDeclaration<ArrowFunction>(
      SyntaxKind::ArrowFunction,
      /*decorators*/ nullptr, modifiers,
      /*name*/ {}, typeParameters, parameters, type,
      parenthesizer.parenthesizeConciseBodyOfArrowFunction(body));
  node->equalsGreaterThanToken = equalsGreaterThanToken
                                     ? equalsGreaterThanToken
                                     : createToken<EqualsGreaterThanToken>(
                                           SyntaxKind::EqualsGreaterThanToken);
  node->transformFlags |= propagateChildFlags(node->equalsGreaterThanToken) |
                          (int)TransformFlags::ContainsES2015;
  if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Async) {
    node->transformFlags |= (int)TransformFlags::ContainsES2017 |
                            (int)TransformFlags::ContainsLexicalThis;
  }
  return node;
}

//        // @api
//        function updateArrowFunction(
//            node: ArrowFunction,
//            optionalNode<NodeArray> modifiers,
//            optionalNode<NodeArray> typeParameters,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type,
//            equalsGreaterThanToken: EqualsGreaterThanToken,
//            body: ConciseBody
//        ): ArrowFunction {
//            return node->modifiers != modifiers
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                || node->equalsGreaterThanToken != equalsGreaterThanToken
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createArrowFunction(modifiers,
//                typeParameters, parameters, type, equalsGreaterThanToken,
//                body), node) : node;
//        }
//
// @api
node<DeleteExpression> Factory::createDeleteExpression(
    node<Expression> expression) {
  auto node =
      createBaseExpression<DeleteExpression>(SyntaxKind::DeleteExpression);
  node->expression = parenthesizer.parenthesizeOperandOfPrefixUnary(expression);
  node->transformFlags |= propagateChildFlags(node->expression);
  return node;
}

//        // @api
//        function updateDeleteExpression(node: DeleteExpression,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createDeleteExpression(expression), node)
//                : node;
//        }

// @api
node<TypeOfExpression> Factory::createTypeOfExpression(
    node<Expression> expression) {
  auto node =
      createBaseExpression<TypeOfExpression>(SyntaxKind::TypeOfExpression);
  node->expression = parenthesizer.parenthesizeOperandOfPrefixUnary(expression);
  node->transformFlags |= propagateChildFlags(node->expression);
  return node;
}

//        // @api
//        function updateTypeOfExpression(node: TypeOfExpression,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createTypeOfExpression(expression), node)
//                : node;
//        }

// @api
node<VoidExpression> Factory::createVoidExpression(
    node<Expression> expression) {
  auto node = createBaseExpression<VoidExpression>(SyntaxKind::VoidExpression);
  node->expression = parenthesizer.parenthesizeOperandOfPrefixUnary(expression);
  node->transformFlags |= propagateChildFlags(node->expression);
  return node;
}

//        // @api
//        function updateVoidExpression(node: VoidExpression,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createVoidExpression(expression), node)
//                : node;
//        }

// @api
node<AwaitExpression> Factory::createAwaitExpression(
    node<Expression> expression) {
  auto node =
      createBaseExpression<AwaitExpression>(SyntaxKind::AwaitExpression);
  node->expression = parenthesizer.parenthesizeOperandOfPrefixUnary(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsES2017 |
                          (int)TransformFlags::ContainsES2018 |
                          (int)TransformFlags::ContainsAwait;
  return node;
}

//        // @api
//        function updateAwaitExpression(node: AwaitExpression,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createAwaitExpression(expression), node)
//                : node;
//        }
//
// @api
node<PrefixUnaryExpression> Factory::createPrefixUnaryExpression(
    SyntaxKind operatorKind, tscpp::node<Expression> operand) {
  auto node = createBaseExpression<PrefixUnaryExpression>(
      SyntaxKind::PrefixUnaryExpression);
  node->operatorKind = operatorKind;
  node->operand = parenthesizer.parenthesizeOperandOfPrefixUnary(operand);
  node->transformFlags |= propagateChildFlags(node->operand);
  // Only set this flag for non-generated identifiers and non-"local" names. See
  // the comment in `visitPreOrPostfixUnaryExpression` in module.ts
  if ((operatorKind == SyntaxKind::PlusPlusToken ||
       operatorKind == SyntaxKind::MinusMinusToken) &&
      isIdentifier(node->operand) && !isGeneratedIdentifier(node->operand)) {
    //! isLocalName(node->operand)) { //<- this is always false as its set by
    //! transformer/emit stuff
    node->transformFlags |=
        (int)TransformFlags::ContainsUpdateExpressionForIdentifier;
  }
  return node;
}

//        // @api
//        function updatePrefixUnaryExpression(node: PrefixUnaryExpression,
//        operand: Expression) {
//            return node->operand != operand
//                ? update(createPrefixUnaryExpression(node->operator, operand),
//                node) : node;
//        }

// @api
node<PostfixUnaryExpression> Factory::createPostfixUnaryExpression(
    node<Expression> operand, SyntaxKind operatorKind) {
  auto node = createBaseExpression<PostfixUnaryExpression>(
      SyntaxKind::PostfixUnaryExpression);
  node->operatorKind = operatorKind;
  node->operand = parenthesizer.parenthesizeOperandOfPostfixUnary(operand);
  node->transformFlags |= propagateChildFlags(node->operand);
  // Only set this flag for non-generated identifiers and non-"local" names. See
  // the comment in `visitPreOrPostfixUnaryExpression` in module.ts
  if (isIdentifier(node->operand) && !isGeneratedIdentifier(node->operand) &&
      !isLocalName(node->operand)) {
    node->transformFlags |=
        (int)TransformFlags::ContainsUpdateExpressionForIdentifier;
  }
  return node;
}

//        // @api
//        function updatePostfixUnaryExpression(node: PostfixUnaryExpression,
//        operand: Expression) {
//            return node->operand != operand
//                ? update(createPostfixUnaryExpression(operand,
//                node->operator), node) : node;
//        }

// @api
node<BinaryExpression> Factory::createBinaryExpression(
    node<Expression> left, tscpp::node<Node> operatorNode,
    tscpp::node<Expression> right) {
  auto node =
      createBaseExpression<BinaryExpression>(SyntaxKind::BinaryExpression);
  auto operatorKind = operatorNode->kind;
  node->left = parenthesizer.parenthesizeLeftSideOfBinary(operatorKind, left);
  node->operatorToken = operatorNode;
  node->right = parenthesizer.parenthesizeRightSideOfBinary(operatorKind,
                                                            node->left, right);
  node->transformFlags |= propagateChildFlags(node->left) |
                          propagateChildFlags(node->operatorToken) |
                          propagateChildFlags(node->right);
  if (operatorKind == SyntaxKind::QuestionQuestionToken) {
    node->transformFlags |= (int)TransformFlags::ContainsES2020;
  } else if (operatorKind == SyntaxKind::EqualsToken) {
    if (isObjectLiteralExpression(node->left)) {
      node->transformFlags |=
          (int)TransformFlags::ContainsES2015 |
          (int)TransformFlags::ContainsES2018 |
          (int)TransformFlags::ContainsDestructuringAssignment |
          (int)propagateAssignmentPatternFlags(node->left);
    } else if (isArrayLiteralExpression(node->left)) {
      node->transformFlags |=
          (int)TransformFlags::ContainsES2015 |
          (int)TransformFlags::ContainsDestructuringAssignment |
          (int)propagateAssignmentPatternFlags(node->left);
    }
  } else if (operatorKind == SyntaxKind::AsteriskAsteriskToken ||
             operatorKind == SyntaxKind::AsteriskAsteriskEqualsToken) {
    node->transformFlags |= (int)TransformFlags::ContainsES2016;
  } else if (isLogicalOrCoalescingAssignmentOperator(operatorKind)) {
    node->transformFlags |= (int)TransformFlags::ContainsES2021;
  }
  return node;
}

TransformFlags Factory::propagateAssignmentPatternFlags(node<Node> node) {
  if (node->transformFlags & (int)TransformFlags::ContainsObjectRestOrSpread)
    return TransformFlags::ContainsObjectRestOrSpread;
  if (node->transformFlags & (int)TransformFlags::ContainsES2018) {
    // check for nested spread assignments, otherwise '{ x: { a, ...b } = foo }
    // = c' will not be correctly interpreted by the ES2018 transformer
    for (auto element : *getElementsOfBindingOrAssignmentPattern(node)) {
      auto target = getTargetOfBindingOrAssignmentElement(element);
      if (target && isAssignmentPattern(target)) {
        if (target->transformFlags &
            (int)TransformFlags::ContainsObjectRestOrSpread) {
          return TransformFlags::ContainsObjectRestOrSpread;
        }
        if (target->transformFlags & (int)TransformFlags::ContainsES2018) {
          auto flags = propagateAssignmentPatternFlags(target);
          if ((int)flags)
            return flags;
        }
      }
    }
  }
  return TransformFlags::None;
}

//        // @api
//        function updateBinaryExpression(node: BinaryExpression, left:
//        Expression, operator: BinaryOperatorToken, right: Expression) {
//            return node->left != left
//                || node->operatorToken != operator
//                || node->right != right
//                ? update(createBinaryExpression(left, operator, right), node)
//                : node;
//        }

// @api
node<ConditionalExpression> Factory::createConditionalExpression(
    node<Expression> condition, optionalNode<QuestionToken> questionToken,
    tscpp::node<Expression> whenTrue, optionalNode<ColonToken> colonToken,
    tscpp::node<Expression> whenFalse) {
  auto node = createBaseExpression<ConditionalExpression>(
      SyntaxKind::ConditionalExpression);
  node->condition =
      parenthesizer.parenthesizeConditionOfConditionalExpression(condition);
  node->questionToken =
      questionToken ? questionToken
                    : createToken<QuestionToken>(SyntaxKind::QuestionToken);
  node->whenTrue =
      parenthesizer.parenthesizeBranchOfConditionalExpression(whenTrue);
  node->colonToken =
      colonToken ? colonToken : createToken<ColonToken>(SyntaxKind::ColonToken);
  node->whenFalse =
      parenthesizer.parenthesizeBranchOfConditionalExpression(whenFalse);
  node->transformFlags |= propagateChildFlags(node->condition) |
                          propagateChildFlags(node->questionToken) |
                          propagateChildFlags(node->whenTrue) |
                          propagateChildFlags(node->colonToken) |
                          propagateChildFlags(node->whenFalse);
  return node;
}

//        // @api
//        function updateConditionalExpression(
//            node: ConditionalExpression,
//            condition: Expression,
//            questionToken: Token<SyntaxKind::QuestionToken>,
//            whenTrue: Expression,
//            colonToken: Token<SyntaxKind::ColonToken>,
//            whenFalse: Expression
//        ): ConditionalExpression {
//            return node->condition != condition
//                || node->questionToken != questionToken
//                || node->whenTrue != whenTrue
//                || node->colonToken != colonToken
//                || node->whenFalse != whenFalse
//                ? update(createConditionalExpression(condition, questionToken,
//                whenTrue, colonToken, whenFalse), node) : node;
//        }

// @api
node<TemplateExpression> Factory::createTemplateExpression(
    node<TemplateHead> head, tscpp::node<NodeArray> templateSpans) {
  auto node =
      createBaseExpression<TemplateExpression>(SyntaxKind::TemplateExpression);
  node->head = head;
  node->templateSpans = createNodeArray(templateSpans);
  node->transformFlags |= propagateChildFlags(node->head) |
                          propagateChildrenFlags(node->templateSpans) |
                          (int)TransformFlags::ContainsES2015;
  return node;
}

//        // @api
//        function updateTemplateExpression(node: TemplateExpression, head:
//        TemplateHead, templateSpans: readonly TemplateSpan[]) {
//            return node->head != head
//                || node->templateSpans != templateSpans
//                ? update(createTemplateExpression(head, templateSpans), node)
//                : node;
//        }
//
//        function createTemplateLiteralLikeNodeChecked(kind:
//        TemplateLiteralToken["kind"], text: string | undefined, rawText:
//        string | undefined, templateFlags = TokenFlags::None) {
//            Debug::asserts(!(templateFlags &
//            ~TokenFlags::TemplateLiteralLikeFlags), "Unsupported template
//            flags.");
//            // NOTE: without the assignment to `undefined`, we don't narrow
//            the initial type of `cooked`.
//            // eslint-disable-next-line no-undef-init
//            let cooked: string | object | undefined = undefined;
//            if (rawText != undefined && rawText != text) {
//                cooked = getCookedText(kind, rawText);
//                if (typeof cooked == "object") {
//                    return Debug.fail("Invalid raw text");
//                }
//            }
//            if (text == undefined) {
//                if (cooked == undefined) {
//                    return Debug.fail("Arguments 'text' and 'rawText' may not
//                    both be undefined.");
//                }
//                text = cooked;
//            }
//            else if (cooked != undefined) {
//                Debug::asserts(text == cooked, "Expected argument 'text' to be
//                the normalized (i.e. 'cooked') version of argument
//                'rawText'.");
//            }
//            return createTemplateLiteralLikeNode(kind, text, rawText,
//            templateFlags);
//        }
//
//        // @api
//        function createTemplateHead(text: string | undefined, rawText?:
//        string, templateFlags?: TokenFlags) {
//            return
//            createTemplateLiteralLikeNodeChecked(SyntaxKind::TemplateHead,
//            text, rawText, templateFlags) as TemplateHead;
//        }
//
//        // @api
//        function createTemplateMiddle(text: string | undefined, rawText?:
//        string, templateFlags?: TokenFlags) {
//            return
//            createTemplateLiteralLikeNodeChecked(SyntaxKind::TemplateMiddle,
//            text, rawText, templateFlags) as TemplateMiddle;
//        }
//
//        // @api
//        function createTemplateTail(text: string | undefined, rawText?:
//        string, templateFlags?: TokenFlags) {
//            return
//            createTemplateLiteralLikeNodeChecked(SyntaxKind::TemplateTail,
//            text, rawText, templateFlags) as TemplateTail;
//        }
//
//        // @api
//        function createNoSubstitutionTemplateLiteral(text: string | undefined,
//        rawText?: string, templateFlags?: TokenFlags) {
//            return
//            createTemplateLiteralLikeNodeChecked(SyntaxKind::NoSubstitutionTemplateLiteral,
//            text, rawText, templateFlags) as NoSubstitutionTemplateLiteral;
//        }

// @api
node<YieldExpression> Factory::createYieldExpression(
    optionalNode<AsteriskToken> asteriskToken,
    optionalNode<Expression> expression) {
  Debug::asserts(
      !asteriskToken || !!expression,
      "A `YieldExpression` with an asteriskToken must have an expression.");
  auto node =
      createBaseExpression<YieldExpression>(SyntaxKind::YieldExpression);
  if (expression)
    node->expression =
        parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
  node->asteriskToken = asteriskToken;
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->asteriskToken) |
                          (int)TransformFlags::ContainsES2015 |
                          (int)TransformFlags::ContainsES2018 |
                          (int)TransformFlags::ContainsYield;
  return node;
}

//        // @api
//        function updateYieldExpression(node: YieldExpression,
//        optionalNode<AsteriskToken> asteriskToken, tscpp::node<Expression>
//        expression) {
//            return node->expression != expression
//                || node->asteriskToken != asteriskToken
//                ? update(createYieldExpression(asteriskToken, expression),
//                node) : node;
//        }

// @api
node<SpreadElement> Factory::createSpreadElement(node<Expression> expression) {
  auto node = createBaseExpression<SpreadElement>(SyntaxKind::SpreadElement);
  node->expression =
      parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsES2015 |
                          (int)TransformFlags::ContainsRestOrSpread;
  return node;
}

//        // @api
//        function updateSpreadElement(node: SpreadElement, tscpp::node<Expression>
//        expression) {
//            return node->expression != expression
//                ? update(createSpreadElement(expression), node)
//                : node;
//        }

// @api
node<ClassExpression> Factory::createClassExpression(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    NameType name, optionalNode<NodeArray> typeParameters,
    optionalNode<NodeArray> heritageClauses, node<NodeArray> members) {
  auto node = createBaseClassLikeDeclaration<ClassExpression>(
      SyntaxKind::ClassExpression, decorators, modifiers, name, typeParameters,
      heritageClauses, members);
  node->transformFlags |= (int)TransformFlags::ContainsES2015;
  return node;
}

//        // @api
//        function updateClassExpression(
//            node: ClassExpression,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: Identifier | undefined,
//            optionalNode<NodeArray> typeParameters,
//            optionalNode<NodeArray> heritageClauses,
//            node<NodeArray> members
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->typeParameters != typeParameters
//                || node->heritageClauses != heritageClauses
//                || node->members != members
//                ? update(createClassExpression(decorators, modifiers, name,
//                typeParameters, heritageClauses, members), node) : node;
//        }

// @api
node<OmittedExpression> Factory::createOmittedExpression() {
  return createBaseExpression<OmittedExpression>(SyntaxKind::OmittedExpression);
}

// @api
node<ExpressionWithTypeArguments> Factory::createExpressionWithTypeArguments(
    node<Expression> expression, optionalNode<NodeArray> typeArguments) {
  auto node = createBaseNode<ExpressionWithTypeArguments>(
      SyntaxKind::ExpressionWithTypeArguments);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  if (typeArguments)
    node->typeArguments =
        parenthesizer.parenthesizeTypeArguments(typeArguments);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildrenFlags(node->typeArguments) |
                          (int)TransformFlags::ContainsES2015;
  return node;
}

//        // @api
//        function updateExpressionWithTypeArguments(node:
//        ExpressionWithTypeArguments, tscpp::node<Expression> expression,
//        optionalNode<NodeArray> typeArguments) {
//            return node->expression != expression
//                || node->typeArguments != typeArguments
//                ? update(createExpressionWithTypeArguments(expression,
//                typeArguments), node) : node;
//        }

// @api
node<AsExpression> Factory::createAsExpression(node<Expression> expression,
                                               tscpp::node<TypeNode> type) {
  auto node = createBaseExpression<AsExpression>(SyntaxKind::AsExpression);
  node->expression = expression;
  node->type = type;
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->type) |
                          (int)TransformFlags::ContainsTypeScript;
  return node;
}

// @api
auto Factory::updateAsExpression(node<AsExpression> node,
                                 tscpp::node<Expression> expression,
                                 tscpp::node<TypeNode> type) {
  return node->expression != expression || node->type != type
             ? update(createAsExpression(expression, type), node)
             : node;
}

// @api
node<NonNullExpression> Factory::createNonNullExpression(
    node<Expression> expression) {
  auto node =
      createBaseExpression<NonNullExpression>(SyntaxKind::NonNullExpression);
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsTypeScript;
  return node;
}

// @api
node<NonNullChain> Factory::createNonNullChain(node<Expression> expression) {
  auto node = createBaseExpression<NonNullChain>(SyntaxKind::NonNullExpression);
  node->flags |= (int)NodeFlags::OptionalChain;
  node->expression = parenthesizer.parenthesizeLeftSideOfAccess(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsTypeScript;
  return node;
}

// @api
auto Factory::updateNonNullChain(node<NonNullChain> node,
                                 tscpp::node<Expression> expression) {
  Debug::asserts(!!(node->flags & (int)NodeFlags::OptionalChain),
                 "Cannot update a NonNullExpression using updateNonNullChain. "
                 "Use updateNonNullExpression instead.");
  return node->expression != expression
             ? update(createNonNullChain(expression), node)
             : node;
}

// @api
auto Factory::updateNonNullExpression(node<NonNullExpression> node,
                                      tscpp::node<Expression> expression) {
  if (isNonNullChain(node)) {
    return updateNonNullChain(node, expression);
  }
  return node->expression != expression
             ? update(createNonNullExpression(expression), node)
             : node;
}

// @api
node<MetaProperty> Factory::createMetaProperty(SyntaxKind keywordToken,
                                               tscpp::node<Identifier> name) {
  auto node = createBaseExpression<MetaProperty>(SyntaxKind::MetaProperty);
  node->keywordToken = keywordToken;
  node->name = name;
  node->transformFlags |= propagateChildFlags(node->name);
  switch (keywordToken) {
    case SyntaxKind::NewKeyword:
      node->transformFlags |= (int)TransformFlags::ContainsES2015;
      break;
    case SyntaxKind::ImportKeyword:
      node->transformFlags |= (int)TransformFlags::ContainsESNext;
      break;
    default:
      throw runtime_error(
          fmt::format("invalid keyword token {}", keywordToken));
  }
  return node;
}

//        // @api
//        function updateMetaProperty(node: MetaProperty, name: Identifier) {
//            return node->name != name
//                ? update(createMetaProperty(node->keywordToken, name), node)
//                : node;
//        }
//
//        //
//        // Misc
//        //

// @api
node<TemplateSpan> Factory::createTemplateSpan(
    node<Expression> expression,
    tscpp::node<NodeUnion(TemplateMiddle, TemplateTail)> literal) {
  auto node = createBaseNode<TemplateSpan>(SyntaxKind::TemplateSpan);
  node->expression = expression;
  node->literal = literal;
  node->transformFlags |= propagateChildFlags(node->expression) |
                          propagateChildFlags(node->literal) |
                          (int)TransformFlags::ContainsES2015;
  return node;
}

//        // @api
//        function updateTemplateSpan(node: TemplateSpan, tscpp::node<Expression>
//        expression, literal: TemplateMiddle | TemplateTail) {
//            return node->expression != expression
//                || node->literal != literal
//                ? update(createTemplateSpan(expression, literal), node)
//                : node;
//        }
//
// @api
node<SemicolonClassElement> Factory::createSemicolonClassElement() {
  auto node =
      createBaseNode<SemicolonClassElement>(SyntaxKind::SemicolonClassElement);
  node->transformFlags |= (int)TransformFlags::ContainsES2015;
  return node;
}

//
// Element
//

// @api
node<Block> Factory::createBlock(node<NodeArray> statements, bool multiLine) {
  auto node = createBaseNode<Block>(SyntaxKind::Block);
  node->statements = createNodeArray(statements);
  node->multiLine = multiLine;
  node->transformFlags |= propagateChildrenFlags(node->statements);
  return node;
}

// @api
node<VariableDeclarationList> Factory::createVariableDeclarationList(
    node<NodeArray> declarations, int flags) {
  auto node = createBaseNode<VariableDeclarationList>(
      SyntaxKind::VariableDeclarationList);
  node->flags |= flags & (int)NodeFlags::BlockScoped;
  node->declarations = declarations;
  for (auto d : *declarations)
    d->setParent(node);
  node->transformFlags |=
      propagateChildrenFlags(node->declarations) |
      (int)TransformFlags::ContainsHoistedDeclarationOrCompletion;
  if (flags & (int)NodeFlags::BlockScoped) {
    node->transformFlags |= (int)TransformFlags::ContainsES2015 |
                            (int)TransformFlags::ContainsBlockScopedBinding;
  }
  return node;
}

//        // @api
//        function updateBlock(node: Block, statements: readonly Statement[]) {
//            return node->statements != statements
//                ? update(createBlock(statements, node->multiLine), node)
//                : node;
//        }

// @api
node<VariableStatement> Factory::createVariableStatement(
    optionalNode<NodeArray> modifiers,
    tscpp::node<VariableDeclarationList> declarationList) {
  auto node = createBaseDeclaration<VariableStatement>(
      SyntaxKind::VariableStatement, /*decorators*/ nullptr, modifiers);
  node->declarationList = declarationList;
  node->transformFlags |= propagateChildFlags(node->declarationList);
  if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Ambient) {
    node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}

//    // @api
//   node<VariableStatement>
//   Factory::createVariableStatement(optionalNode<NodeArray> modifiers,
//   variant<node<VariableDeclarationList>, vector<node<VariableDeclaration>>>
//   declarationList) {
//        auto node =
//        createBaseDeclaration<VariableStatement>(SyntaxKind::VariableStatement,
//        /*decorators*/ nullptr, modifiers);
//
//        if (holds_alternative<node<VariableDeclarationList>>(declarationList))
//        {
//            node->declarationList =
//            get<node<VariableDeclarationList>>(declarationList);
//        } else {
//            node->declarationList =
//            createVariableDeclarationList(get<vector<node<VariableDeclaration>>>(declarationList));
//        }
//        node->transformFlags |=
//                propagateChildFlags(node->declarationList);
//        if (modifiersToFlags(node->modifiers) & (int) ModifierFlags::Ambient)
//        {
//            node->transformFlags = (int) TransformFlags::ContainsTypeScript;
//        }
//        return node;
//    }

//        // @api
//        function updateVariableStatement(node: VariableStatement,
//        optionalNode<NodeArray> modifiers, declarationList:
//        VariableDeclarationList) {
//            return node->modifiers != modifiers
//                || node->declarationList != declarationList
//                ? update(createVariableStatement(modifiers, declarationList),
//                node) : node;
//        }

// @api
node<EmptyStatement> Factory::createEmptyStatement() {
  return createBaseNode<EmptyStatement>(SyntaxKind::EmptyStatement);
}

node<EmitNode> Factory::mergeEmitNode(node<EmitNode> sourceEmitNode,
                                      optionalNode<EmitNode> destEmitNode) {
  if (!destEmitNode)
    destEmitNode = pool->construct<EmitNode>();
  // We are using `.slice()` here in case `destEmitNode.leadingComments` is
  // pushed to later.
  if (sourceEmitNode->leadingComments)
    destEmitNode->leadingComments = addRange<SynthesizedComment>(
        slice(sourceEmitNode->leadingComments), destEmitNode->leadingComments);
  if (sourceEmitNode->trailingComments)
    destEmitNode->trailingComments =
        addRange<SynthesizedComment>(slice(sourceEmitNode->trailingComments),
                                     destEmitNode->trailingComments);
  if (sourceEmitNode->flags)
    destEmitNode->flags = sourceEmitNode->flags & ~(int)EmitFlags::Immutable;
  if (sourceEmitNode->commentRange)
    destEmitNode->commentRange = sourceEmitNode->commentRange;
  if (sourceEmitNode->sourceMapRange)
    destEmitNode->sourceMapRange = sourceEmitNode->sourceMapRange;
  //        if (sourceEmitNode->tokenSourceMapRanges)
  //        destEmitNode->tokenSourceMapRanges =
  //        mergeTokenSourceMapRanges(sourceEmitNode->tokenSourceMapRanges,
  //        destEmitNode->tokenSourceMapRanges!); if
  //        (sourceEmitNode->constantValue != false) destEmitNode->constantValue
  //        = constantValue; if (sourceEmitNode->helpers) {
  //            for (auto helper of helpers) {
  //                destEmitNode.helpers = appendIfUnique(destEmitNode.helpers,
  //                helper);
  //            }
  //        }
  //        if (startsOnNewLine != undefined) destEmitNode.startsOnNewLine =
  //        startsOnNewLine;
  return destEmitNode;
}

// @api
node<ExpressionStatement> Factory::createExpressionStatement(
    node<Expression> expression) {
  auto node =
      createBaseNode<ExpressionStatement>(SyntaxKind::ExpressionStatement);
  node->expression =
      parenthesizer.parenthesizeExpressionOfExpressionStatement(expression);
  node->transformFlags |= propagateChildFlags(node->expression);
  return node;
}

//        // @api
//        function updateExpressionStatement(node: ExpressionStatement,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createExpressionStatement(expression), node)
//                : node;
//        }
//
//        // @api
//        function createIfStatement(node<Expression> expression, thenStatement:
//        Statement, elseStatement?: Statement) {
//            auto node = createBaseNode<IfStatement>(SyntaxKind::IfStatement);
//            node->expression = expression;
//            node->thenStatement = asEmbeddedStatement(thenStatement);
//            node->elseStatement = asEmbeddedStatement(elseStatement);
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->thenStatement) |
//                propagateChildFlags(node->elseStatement);
//            return node;
//        }
//
//        // @api
//        function updateIfStatement(node: IfStatement, tscpp::node<Expression>
//        expression, thenStatement: Statement, elseStatement: Statement |
//        undefined) {
//            return node->expression != expression
//                || node->thenStatement != thenStatement
//                || node->elseStatement != elseStatement
//                ? update(createIfStatement(expression, thenStatement,
//                elseStatement), node) : node;
//        }
//
//        // @api
//        function createDoStatement(statement: Statement, tscpp::node<Expression>
//        expression) {
//            auto node = createBaseNode<DoStatement>(SyntaxKind::DoStatement);
//            node->statement = asEmbeddedStatement(statement);
//            node->expression = expression;
//            node->transformFlags |=
//                propagateChildFlags(node->statement) |
//                propagateChildFlags(node->expression);
//            return node;
//        }
//
//        // @api
//        function updateDoStatement(node: DoStatement, statement: Statement,
//        tscpp::node<Expression> expression) {
//            return node->statement != statement
//                || node->expression != expression
//                ? update(createDoStatement(statement, expression), node)
//                : node;
//        }
//
//        // @api
//        function createWhileStatement(node<Expression> expression, statement:
//        Statement) {
//            auto node =
//            createBaseNode<WhileStatement>(SyntaxKind::WhileStatement);
//            node->expression = expression;
//            node->statement = asEmbeddedStatement(statement);
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->statement);
//            return node;
//        }
//
//        // @api
//        function updateWhileStatement(node: WhileStatement,
//        tscpp::node<Expression> expression, statement: Statement) {
//            return node->expression != expression
//                || node->statement != statement
//                ? update(createWhileStatement(expression, statement), node)
//                : node;
//        }
//
//        // @api
//        function createForStatement(initializer: ForInitializer | undefined,
//        condition: Expression | undefined, incrementor: Expression |
//        undefined, statement: Statement) {
//            auto node =
//            createBaseNode<ForStatement>(SyntaxKind::ForStatement);
//            node->initializer = initializer;
//            node->condition = condition;
//            node->incrementor = incrementor;
//            node->statement = asEmbeddedStatement(statement);
//            node->transformFlags |=
//                propagateChildFlags(node->initializer) |
//                propagateChildFlags(node->condition) |
//                propagateChildFlags(node->incrementor) |
//                propagateChildFlags(node->statement);
//            return node;
//        }
//
//        // @api
//        function updateForStatement(node: ForStatement, initializer:
//        ForInitializer | undefined, condition: Expression | undefined,
//        incrementor: Expression | undefined, statement: Statement) {
//            return node->initializer != initializer
//                || node->condition != condition
//                || node->incrementor != incrementor
//                || node->statement != statement
//                ? update(createForStatement(initializer, condition,
//                incrementor, statement), node) : node;
//        }
//
//        // @api
//        function createForInStatement(initializer: ForInitializer,
//        tscpp::node<Expression> expression, statement: Statement) {
//            auto node =
//            createBaseNode<ForInStatement>(SyntaxKind::ForInStatement);
//            node->initializer = initializer;
//            node->expression = expression;
//            node->statement = asEmbeddedStatement(statement);
//            node->transformFlags |=
//                propagateChildFlags(node->initializer) |
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->statement);
//            return node;
//        }
//
//        // @api
//        function updateForInStatement(node: ForInStatement, initializer:
//        ForInitializer, tscpp::node<Expression> expression, statement: Statement)
//        {
//            return node->initializer != initializer
//                || node->expression != expression
//                || node->statement != statement
//                ? update(createForInStatement(initializer, expression,
//                statement), node) : node;
//        }
//
//        // @api
//        function createForOfStatement(awaitModifier: AwaitKeyword | undefined,
//        initializer: ForInitializer, tscpp::node<Expression> expression,
//        statement: Statement) {
//            auto node =
//            createBaseNode<ForOfStatement>(SyntaxKind::ForOfStatement);
//            node->awaitModifier = awaitModifier;
//            node->initializer = initializer;
//            node->expression =
//            parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
//            node->statement = asEmbeddedStatement(statement);
//            node->transformFlags |=
//                propagateChildFlags(node->awaitModifier) |
//                propagateChildFlags(node->initializer) |
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->statement) |
//                (int)TransformFlags::ContainsES2015;
//            if (awaitModifier) node->transformFlags |=
//            (int)TransformFlags::ContainsES2018; return node;
//        }
//
//        // @api
//        function updateForOfStatement(node: ForOfStatement, awaitModifier:
//        AwaitKeyword | undefined, initializer: ForInitializer,
//        tscpp::node<Expression> expression, statement: Statement) {
//            return node->awaitModifier != awaitModifier
//                || node->initializer != initializer
//                || node->expression != expression
//                || node->statement != statement
//                ? update(createForOfStatement(awaitModifier, initializer,
//                expression, statement), node) : node;
//        }
//
//        // @api
//        function createContinueStatement(label?: string | Identifier):
//        ContinueStatement {
//            auto node =
//            createBaseNode<ContinueStatement>(SyntaxKind::ContinueStatement);
//            node->label = asName(label);
//            node->transformFlags |=
//                propagateChildFlags(node->label) |
//                (int)TransformFlags::ContainsHoistedDeclarationOrCompletion;
//            return node;
//        }
//
//        // @api
//        function updateContinueStatement(node: ContinueStatement, label:
//        Identifier | undefined) {
//            return node->label != label
//                ? update(createContinueStatement(label), node)
//                : node;
//        }
//
//        // @api
//        function createBreakStatement(label?: string | Identifier):
//        BreakStatement {
//            auto node =
//            createBaseNode<BreakStatement>(SyntaxKind::BreakStatement);
//            node->label = asName(label);
//            node->transformFlags |=
//                propagateChildFlags(node->label) |
//                (int)TransformFlags::ContainsHoistedDeclarationOrCompletion;
//            return node;
//        }
//
//        // @api
//        function updateBreakStatement(node: BreakStatement, label: Identifier
//        | undefined) {
//            return node->label != label
//                ? update(createBreakStatement(label), node)
//                : node;
//        }
//
//        // @api
//        function createReturnStatement(expression?: Expression):
//        ReturnStatement {
//            auto node =
//            createBaseNode<ReturnStatement>(SyntaxKind::ReturnStatement);
//            node->expression = expression;
//            // return in an ES2018 async generator must be awaited
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                (int)TransformFlags::ContainsES2018 |
//                (int)TransformFlags::ContainsHoistedDeclarationOrCompletion;
//            return node;
//        }
//
//        // @api
//        function updateReturnStatement(node: ReturnStatement,
//        optionalNode<Expression> expression) {
//            return node->expression != expression
//                ? update(createReturnStatement(expression), node)
//                : node;
//        }
//
//        // @api
//        function createWithStatement(node<Expression> expression, statement:
//        Statement) {
//            auto node =
//            createBaseNode<WithStatement>(SyntaxKind::WithStatement);
//            node->expression = expression;
//            node->statement = asEmbeddedStatement(statement);
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->statement);
//            return node;
//        }
//
//        // @api
//        function updateWithStatement(node: WithStatement, tscpp::node<Expression>
//        expression, statement: Statement) {
//            return node->expression != expression
//                || node->statement != statement
//                ? update(createWithStatement(expression, statement), node)
//                : node;
//        }
//
//        // @api
//        function createSwitchStatement(node<Expression> expression, caseBlock:
//        CaseBlock): SwitchStatement {
//            auto node =
//            createBaseNode<SwitchStatement>(SyntaxKind::SwitchStatement);
//            node->expression =
//            parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
//            node->caseBlock = caseBlock;
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->caseBlock);
//            return node;
//        }
//
//        // @api
//        function updateSwitchStatement(node: SwitchStatement,
//        tscpp::node<Expression> expression, caseBlock: CaseBlock) {
//            return node->expression != expression
//                || node->caseBlock != caseBlock
//                ? update(createSwitchStatement(expression, caseBlock), node)
//                : node;
//        }
//
// @api
node<LabeledStatement> Factory::createLabeledStatement(
    NameType label, tscpp::node<Statement> statement) {
  auto node = createBaseNode<LabeledStatement>(SyntaxKind::LabeledStatement);
  node->label = to<Identifier>(asName(label));
  node->statement = asEmbeddedStatement(statement);
  node->transformFlags |=
      propagateChildFlags(node->label) | propagateChildFlags(node->statement);
  return node;
}

//        // @api
//        function updateLabeledStatement(node: LabeledStatement, label:
//        Identifier, statement: Statement) {
//            return node->label != label
//                || node->statement != statement
//                ? update(createLabeledStatement(label, statement), node)
//                : node;
//        }
//
//        // @api
//        function createThrowStatement(node<Expression> expression) {
//            auto node =
//            createBaseNode<ThrowStatement>(SyntaxKind::ThrowStatement);
//            node->expression = expression;
//            node->transformFlags |= propagateChildFlags(node->expression);
//            return node;
//        }
//
//        // @api
//        function updateThrowStatement(node: ThrowStatement,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createThrowStatement(expression), node)
//                : node;
//        }
//
//        // @api
//        function createTryStatement(tryBlock: Block, catchClause: CatchClause
//        | undefined, finallyBlock: Block | undefined) {
//            auto node =
//            createBaseNode<TryStatement>(SyntaxKind::TryStatement);
//            node->tryBlock = tryBlock;
//            node->catchClause = catchClause;
//            node->finallyBlock = finallyBlock;
//            node->transformFlags |=
//                propagateChildFlags(node->tryBlock) |
//                propagateChildFlags(node->catchClause) |
//                propagateChildFlags(node->finallyBlock);
//            return node;
//        }
//
//        // @api
//        function updateTryStatement(node: TryStatement, tryBlock: Block,
//        catchClause: CatchClause | undefined, finallyBlock: Block | undefined)
//        {
//            return node->tryBlock != tryBlock
//                || node->catchClause != catchClause
//                || node->finallyBlock != finallyBlock
//                ? update(createTryStatement(tryBlock, catchClause,
//                finallyBlock), node) : node;
//        }
//
//        // @api
//        function createDebuggerStatement() {
//            return
//            createBaseNode<DebuggerStatement>(SyntaxKind::DebuggerStatement);
//        }
//
// @api
node<VariableDeclaration> Factory::createVariableDeclaration(
    NameType name, optionalNode<ExclamationToken> exclamationToken,
    optionalNode<TypeNode> type, optionalNode<Expression> initializer) {
  ZoneScoped;
  auto node = createBaseVariableLikeDeclaration<VariableDeclaration>(
      SyntaxKind::VariableDeclaration,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr, name, type,
      initializer
          ? parenthesizer.parenthesizeExpressionForDisallowedComma(initializer)
          : nullptr);
  node->exclamationToken = exclamationToken;
  node->transformFlags |= propagateChildFlags(node->exclamationToken);
  if (exclamationToken) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}

//        // @api
//        function updateVariableDeclaration(node: VariableDeclaration, name:
//        BindingName, exclamationToken: ExclamationToken | undefined,
//        optionalNode<TypeNode> type, optionalNode<Expression> initializer) {
//            return node->name != name
//                || node->type != type
//                || node->exclamationToken != exclamationToken
//                || node->initializer != initializer
//                ? update(createVariableDeclaration(name, exclamationToken,
//                type, initializer), node) : node;
//        }
//
//
//        // @api
//        function updateVariableDeclarationList(node: VariableDeclarationList,
//        declarations: readonly VariableDeclaration[]) {
//            return node->declarations != declarations
//                ? update(createVariableDeclarationList(declarations,
//                node->flags), node) : node;
//        }

// @api
node<FunctionDeclaration> Factory::createFunctionDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    optionalNode<AsteriskToken> asteriskToken, NameType name,
    optionalNode<NodeArray> typeParameters, node<NodeArray> parameters,
    optionalNode<TypeNode> type, optionalNode<Block> body) {
  auto node = createBaseFunctionLikeDeclaration<FunctionDeclaration>(
      SyntaxKind::FunctionDeclaration, decorators, modifiers, name,
      typeParameters, parameters, type, body);
  node->asteriskToken = asteriskToken;
  if (!node->body ||
      modifiersToFlags(node->modifiers) & (int)ModifierFlags::Ambient) {
    node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  } else {
    node->transformFlags |=
        propagateChildFlags(node->asteriskToken) |
        (int)TransformFlags::ContainsHoistedDeclarationOrCompletion;
    if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Async) {
      if (node->asteriskToken) {
        node->transformFlags |= (int)TransformFlags::ContainsES2018;
      } else {
        node->transformFlags |= (int)TransformFlags::ContainsES2017;
      }
    } else if (node->asteriskToken) {
      node->transformFlags |= (int)TransformFlags::ContainsGenerator;
    }
  }
  return node;
}

//        // @api
//        function updateFunctionDeclaration(
//            node: FunctionDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            optionalNode<AsteriskToken> asteriskToken,
//            name: Identifier | undefined,
//            optionalNode<NodeArray> typeParameters,
//            node<NodeArray> parameters,
//            optionalNode<TypeNode> type,
//           optionalNode<Block> body
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->asteriskToken != asteriskToken
//                || node->name != name
//                || node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                || node->body != body
//                ?
//                updateBaseFunctionLikeDeclaration(createFunctionDeclaration(decorators,
//                modifiers, asteriskToken, name, typeParameters, parameters,
//                type, body), node) : node;
//        }
//
// @api
node<ClassDeclaration> Factory::createClassDeclaration(
    optionalNode<NodeArray> decorators, optionalNode<NodeArray> modifiers,
    NameType name, optionalNode<NodeArray> typeParameters,
    optionalNode<NodeArray> heritageClauses, node<NodeArray> members) {
  auto node = createBaseClassLikeDeclaration<ClassDeclaration>(
      SyntaxKind::ClassDeclaration, decorators, modifiers, name, typeParameters,
      heritageClauses, members);
  if (modifiersToFlags(node->modifiers) & (int)ModifierFlags::Ambient) {
    node->transformFlags = (int)TransformFlags::ContainsTypeScript;
  } else {
    node->transformFlags |= (int)TransformFlags::ContainsES2015;
    if (node->transformFlags &
        (int)TransformFlags::ContainsTypeScriptClassSyntax) {
      node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
    }
  }
  return node;
}

//        // @api
//        function updateClassDeclaration(
//            node: ClassDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: Identifier | undefined,
//            optionalNode<NodeArray> typeParameters,
//            optionalNode<NodeArray> heritageClauses,
//            node<NodeArray> members
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->typeParameters != typeParameters
//                || node->heritageClauses != heritageClauses
//                || node->members != members
//                ? update(createClassDeclaration(decorators, modifiers, name,
//                typeParameters, heritageClauses, members), node) : node;
//        }
//
//        // @api
//        function createInterfaceDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: string | Identifier,
//            optionalNode<NodeArray> typeParameters,
//            optionalNode<NodeArray> heritageClauses,
//            members: readonly TypeElement[]
//        ) {
//            auto node =
//            createBaseInterfaceOrClassLikeDeclaration<InterfaceDeclaration>(
//                SyntaxKind::InterfaceDeclaration,
//                decorators,
//                modifiers,
//                name,
//                typeParameters,
//                heritageClauses
//            );
//            node->members = createNodeArray(members);
//            node->transformFlags = (int)TransformFlags::ContainsTypeScript;
//            return node;
//        }
//
//        // @api
//        function updateInterfaceDeclaration(
//            node: InterfaceDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: Identifier,
//            optionalNode<NodeArray> typeParameters,
//            optionalNode<NodeArray> heritageClauses,
//            members: readonly TypeElement[]
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->typeParameters != typeParameters
//                || node->heritageClauses != heritageClauses
//                || node->members != members
//                ? update(createInterfaceDeclaration(decorators, modifiers,
//                name, typeParameters, heritageClauses, members), node) : node;
//        }
//
//        // @api
//        function createTypeAliasDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: string | Identifier,
//            optionalNode<NodeArray> typeParameters,
//            node<TypeNode> type
//        ) {
//            auto node =
//            createBaseGenericNamedDeclaration<TypeAliasDeclaration>(
//                SyntaxKind::TypeAliasDeclaration,
//                decorators,
//                modifiers,
//                name,
//                typeParameters
//            );
//            node->type = type;
//            node->transformFlags = (int)TransformFlags::ContainsTypeScript;
//            return node;
//        }
//
//        // @api
//        function updateTypeAliasDeclaration(
//            node: TypeAliasDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: Identifier,
//            optionalNode<NodeArray> typeParameters,
//            node<TypeNode> type
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->typeParameters != typeParameters
//                || node->type != type
//                ? update(createTypeAliasDeclaration(decorators, modifiers,
//                name, typeParameters, type), node) : node;
//        }
//
//        // @api
//        function createEnumDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: string | Identifier,
//            members: readonly EnumMember[]
//        ) {
//            auto node = createBaseNamedDeclaration<EnumDeclaration>(
//                SyntaxKind::EnumDeclaration,
//                decorators,
//                modifiers,
//                name
//            );
//            node->members = createNodeArray(members);
//            node->transformFlags |=
//                propagateChildrenFlags(node->members) |
//                (int)TransformFlags::ContainsTypeScript;
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // Enum
//            declarations cannot contain `await` return node;
//        }
//
//        // @api
//        function updateEnumDeclaration(
//            node: EnumDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: Identifier,
//            members: readonly EnumMember[]) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->members != members
//                ? update(createEnumDeclaration(decorators, modifiers, name,
//                members), node) : node;
//        }
//
//        // @api
//        function createModuleDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: ModuleName,
//            body: ModuleBody | undefined,
//            flags = NodeFlags::None
//        ) {
//            auto node = createBaseDeclaration<ModuleDeclaration>(
//                SyntaxKind::ModuleDeclaration,
//                decorators,
//                modifiers
//            );
//            node->flags |= flags & (NodeFlags::Namespace |
//            NodeFlags::NestedNamespace | NodeFlags::GlobalAugmentation);
//            node->name = name;
//            node->body = body;
//            if (modifiersToFlags(node->modifiers) & ModifierFlags::Ambient) {
//                node->transformFlags =
//                (int)TransformFlags::ContainsTypeScript;
//            }
//            else {
//                node->transformFlags |=
//                    propagateChildFlags(node->name) |
//                    propagateChildFlags(node->body) |
//                    (int)TransformFlags::ContainsTypeScript;
//            }
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // Module
//            declarations cannot contain `await`. return node;
//        }
//
//        // @api
//        function updateModuleDeclaration(
//            node: ModuleDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            name: ModuleName,
//            body: ModuleBody | undefined
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->name != name
//                || node->body != body
//                ? update(createModuleDeclaration(decorators, modifiers, name,
//                body, node->flags), node) : node;
//        }
//
//        // @api
//        function createModuleBlock(statements: readonly Statement[]) {
//            auto node = createBaseNode<ModuleBlock>(SyntaxKind::ModuleBlock);
//            node->statements = createNodeArray(statements);
//            node->transformFlags |= propagateChildrenFlags(node->statements);
//            return node;
//        }
//
//        // @api
//        function updateModuleBlock(node: ModuleBlock, statements: readonly
//        Statement[]) {
//            return node->statements != statements
//                ? update(createModuleBlock(statements), node)
//                : node;
//        }
//
//        // @api
//        function createCaseBlock(clauses: readonly CaseOrDefaultClause[]):
//        CaseBlock {
//            auto node = createBaseNode<CaseBlock>(SyntaxKind::CaseBlock);
//            node->clauses = createNodeArray(clauses);
//            node->transformFlags |= propagateChildrenFlags(node->clauses);
//            return node;
//        }
//
//        // @api
//        function updateCaseBlock(node: CaseBlock, clauses: readonly
//        CaseOrDefaultClause[]) {
//            return node->clauses != clauses
//                ? update(createCaseBlock(clauses), node)
//                : node;
//        }
//
//        // @api
//        function createNamespaceExportDeclaration(name: string | Identifier) {
//            auto node =
//            createBaseNamedDeclaration<NamespaceExportDeclaration>(
//                SyntaxKind::NamespaceExportDeclaration,
//                /*decorators*/ nullptr,
//                /*modifiers*/ nullptr,
//                name
//            );
//            node->transformFlags = (int)TransformFlags::ContainsTypeScript;
//            return node;
//        }
//
//        // @api
//        function updateNamespaceExportDeclaration(node:
//        NamespaceExportDeclaration, name: Identifier) {
//            return node->name != name
//                ? update(createNamespaceExportDeclaration(name), node)
//                : node;
//        }
//
//        // @api
//        function createImportEqualsDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            isTypeOnly: boolean,
//            name: string | Identifier,
//            moduleReference: ModuleReference
//        ) {
//            auto node = createBaseNamedDeclaration<ImportEqualsDeclaration>(
//                SyntaxKind::ImportEqualsDeclaration,
//                decorators,
//                modifiers,
//                name
//            );
//            node->isTypeOnly = isTypeOnly;
//            node->moduleReference = moduleReference;
//            node->transformFlags |=
//            propagateChildFlags(node->moduleReference); if
//            (!isExternalModuleReference(node->moduleReference))
//            node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // Import=
//            declaration is always parsed in an Await context return node;
//        }
//
//        // @api
//        function updateImportEqualsDeclaration(
//            node: ImportEqualsDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            isTypeOnly: boolean,
//            name: Identifier,
//            moduleReference: ModuleReference
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->isTypeOnly != isTypeOnly
//                || node->name != name
//                || node->moduleReference != moduleReference
//                ? update(createImportEqualsDeclaration(decorators, modifiers,
//                isTypeOnly, name, moduleReference), node) : node;
//        }
//
//        // @api
//        function createImportDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            importClause: ImportClause | undefined,
//            moduleSpecifier: Expression,
//            assertClause: AssertClause | undefined
//        ): ImportDeclaration {
//            auto node = createBaseDeclaration<ImportDeclaration>(
//                SyntaxKind::ImportDeclaration,
//                decorators,
//                modifiers
//            );
//            node->importClause = importClause;
//            node->moduleSpecifier = moduleSpecifier;
//            node->assertClause = assertClause;
//            node->transformFlags |=
//                propagateChildFlags(node->importClause) |
//                propagateChildFlags(node->moduleSpecifier);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateImportDeclaration(
//            node: ImportDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            importClause: ImportClause | undefined,
//            moduleSpecifier: Expression,
//            assertClause: AssertClause | undefined
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->importClause != importClause
//                || node->moduleSpecifier != moduleSpecifier
//                || node->assertClause != assertClause
//                ? update(createImportDeclaration(decorators, modifiers,
//                importClause, moduleSpecifier, assertClause), node) : node;
//        }
//
//        // @api
//        function createImportClause(isTypeOnly: boolean, name: Identifier |
//        undefined, namedBindings: NamedImportBindings | undefined):
//        ImportClause {
//            auto node =
//            createBaseNode<ImportClause>(SyntaxKind::ImportClause);
//            node->isTypeOnly = isTypeOnly;
//            node->name = name;
//            node->namedBindings = namedBindings;
//            node->transformFlags |=
//                propagateChildFlags(node->name) |
//                propagateChildFlags(node->namedBindings);
//            if (isTypeOnly) {
//                node->transformFlags |=
//                (int)TransformFlags::ContainsTypeScript;
//            }
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateImportClause(node: ImportClause, isTypeOnly: boolean,
//        name: Identifier | undefined, namedBindings: NamedImportBindings |
//        undefined) {
//            return node->isTypeOnly != isTypeOnly
//                || node->name != name
//                || node->namedBindings != namedBindings
//                ? update(createImportClause(isTypeOnly, name, namedBindings),
//                node) : node;
//        }
//
// @api
node<AssertClause> Factory::createAssertClause(node<NodeArray> elements,
                                               bool multiLine) {
  auto node = createBaseNode<AssertClause>(SyntaxKind::AssertClause);
  node->elements = createNodeArray(elements);
  node->multiLine = multiLine;
  node->transformFlags |= (int)TransformFlags::ContainsESNext;
  return node;
}

//        // @api
//        function updateAssertClause(node: AssertClause, elements: readonly
//        AssertEntry[], multiLine?: boolean): AssertClause {
//            return node->elements != elements
//                || node->multiLine != multiLine
//                ? update(createAssertClause(elements, multiLine), node)
//                : node;
//        }
//
// @api
node<AssertEntry> Factory::createAssertEntry(node<NodeUnion(AssertionKey)> name,
                                             tscpp::node<Expression> value) {
  auto node = createBaseNode<AssertEntry>(SyntaxKind::AssertEntry);
  node->name = name;
  node->value = value;
  node->transformFlags |= (int)TransformFlags::ContainsESNext;
  return node;
}

//        // @api
//        function updateAssertEntry(node: AssertEntry, name: AssertionKey,
//        value: Expression): AssertEntry {
//            return node->name != name
//                || node->value != value
//                ? update(createAssertEntry(name, value), node)
//                : node;
//        }

// @api
node<ImportTypeAssertionContainer> Factory::createImportTypeAssertionContainer(
    node<AssertClause> clause, bool multiLine) {
  auto node = createBaseNode<ImportTypeAssertionContainer>(
      SyntaxKind::ImportTypeAssertionContainer);
  node->assertClause = clause;
  node->multiLine = multiLine;
  return node;
}

//        // @api
//        function updateImportTypeAssertionContainer(node:
//        ImportTypeAssertionContainer, clause: AssertClause, multiLine?:
//        boolean): ImportTypeAssertionContainer {
//            return node->assertClause != clause
//                || node->multiLine != multiLine
//                ? update(createImportTypeAssertionContainer(clause,
//                multiLine), node) : node;
//        }
//
//        // @api
//        function createNamespaceImport(name: Identifier): NamespaceImport {
//            auto node =
//            createBaseNode<NamespaceImport>(SyntaxKind::NamespaceImport);
//            node->name = name;
//            node->transformFlags |= propagateChildFlags(node->name);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateNamespaceImport(node: NamespaceImport, name:
//        Identifier) {
//            return node->name != name
//                ? update(createNamespaceImport(name), node)
//                : node;
//        }
//
//        // @api
//        function createNamespaceExport(name: Identifier): NamespaceExport {
//            auto node =
//            createBaseNode<NamespaceExport>(SyntaxKind::NamespaceExport);
//            node->name = name;
//            node->transformFlags |=
//                propagateChildFlags(node->name) |
//                (int)TransformFlags::ContainsESNext;
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateNamespaceExport(node: NamespaceExport, name:
//        Identifier) {
//            return node->name != name
//                ? update(createNamespaceExport(name), node)
//                : node;
//        }
//
//        // @api
//        function createNamedImports(elements: readonly ImportSpecifier[]):
//        NamedImports {
//            auto node =
//            createBaseNode<NamedImports>(SyntaxKind::NamedImports);
//            node->elements = createNodeArray(elements);
//            node->transformFlags |= propagateChildrenFlags(node->elements);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateNamedImports(node: NamedImports, elements: readonly
//        ImportSpecifier[]) {
//            return node->elements != elements
//                ? update(createNamedImports(elements), node)
//                : node;
//        }
//
//        // @api
//        function createImportSpecifier(isTypeOnly: boolean, propertyName:
//        Identifier | undefined, name: Identifier) {
//            auto node =
//            createBaseNode<ImportSpecifier>(SyntaxKind::ImportSpecifier);
//            node->isTypeOnly = isTypeOnly;
//            node->propertyName = propertyName;
//            node->name = name;
//            node->transformFlags |=
//                propagateChildFlags(node->propertyName) |
//                propagateChildFlags(node->name);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateImportSpecifier(node: ImportSpecifier, isTypeOnly:
//        boolean, propertyName: Identifier | undefined, name: Identifier) {
//            return node->isTypeOnly != isTypeOnly
//                || node->propertyName != propertyName
//                || node->name != name
//                ? update(createImportSpecifier(isTypeOnly, propertyName,
//                name), node) : node;
//        }
//
//        // @api
//        function createExportAssignment(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            isExportEquals: boolean | undefined,
//            node<Expression> expression
//        ) {
//            auto node = createBaseDeclaration<ExportAssignment>(
//                SyntaxKind::ExportAssignment,
//                decorators,
//                modifiers
//            );
//            node->isExportEquals = isExportEquals;
//            node->expression = isExportEquals
//                ?
//                parenthesizer.parenthesizeRightSideOfBinary(SyntaxKind::EqualsToken,
//                /*leftSide*/ {}, expression) :
//                parenthesizer.parenthesizeExpressionOfExportDefault(expression);
//            node->transformFlags |= propagateChildFlags(node->expression);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateExportAssignment(
//            node: ExportAssignment,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            node<Expression> expression
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->expression != expression
//                ? update(createExportAssignment(decorators, modifiers,
//                node->isExportEquals, expression), node) : node;
//        }
//
//        // @api
//        function createExportDeclaration(
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            isTypeOnly: boolean,
//            exportClause: NamedExportBindings | undefined,
//            moduleSpecifier?: Expression,
//            assertClause?: AssertClause
//        ) {
//            auto node = createBaseDeclaration<ExportDeclaration>(
//                SyntaxKind::ExportDeclaration,
//                decorators,
//                modifiers
//            );
//            node->isTypeOnly = isTypeOnly;
//            node->exportClause = exportClause;
//            node->moduleSpecifier = moduleSpecifier;
//            node->assertClause = assertClause;
//            node->transformFlags |=
//                propagateChildFlags(node->exportClause) |
//                propagateChildFlags(node->moduleSpecifier);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateExportDeclaration(
//            node: ExportDeclaration,
//            optionalNode<NodeArray> decorators,
//            optionalNode<NodeArray> modifiers,
//            isTypeOnly: boolean,
//            exportClause: NamedExportBindings | undefined,
//            moduleSpecifier: Expression | undefined,
//            assertClause: AssertClause | undefined
//        ) {
//            return node->decorators != decorators
//                || node->modifiers != modifiers
//                || node->isTypeOnly != isTypeOnly
//                || node->exportClause != exportClause
//                || node->moduleSpecifier != moduleSpecifier
//                || node->assertClause != assertClause
//                ? update(createExportDeclaration(decorators, modifiers,
//                isTypeOnly, exportClause, moduleSpecifier, assertClause),
//                node) : node;
//        }
//
//        // @api
//        function createNamedExports(elements: readonly ExportSpecifier[]) {
//            auto node =
//            createBaseNode<NamedExports>(SyntaxKind::NamedExports);
//            node->elements = createNodeArray(elements);
//            node->transformFlags |= propagateChildrenFlags(node->elements);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateNamedExports(node: NamedExports, elements: readonly
//        ExportSpecifier[]) {
//            return node->elements != elements
//                ? update(createNamedExports(elements), node)
//                : node;
//        }
//
//        // @api
//        function createExportSpecifier(isTypeOnly: boolean, propertyName:
//        string | Identifier | undefined, name: string | Identifier) {
//            auto node =
//            createBaseNode<ExportSpecifier>(SyntaxKind::ExportSpecifier);
//            node->isTypeOnly = isTypeOnly;
//            node->propertyName = asName(propertyName);
//            node->name = asName(name);
//            node->transformFlags |=
//                propagateChildFlags(node->propertyName) |
//                propagateChildFlags(node->name);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateExportSpecifier(node: ExportSpecifier, isTypeOnly:
//        boolean, propertyName: Identifier | undefined, name: Identifier) {
//            return node->isTypeOnly != isTypeOnly
//                || node->propertyName != propertyName
//                || node->name != name
//                ? update(createExportSpecifier(isTypeOnly, propertyName,
//                name), node) : node;
//        }
//
// @api
node<MissingDeclaration> Factory::createMissingDeclaration() {
  auto node =
      createBaseDeclaration<MissingDeclaration>(SyntaxKind::MissingDeclaration,
                                                /*decorators*/ nullptr,
                                                /*modifiers*/ {});
  return node;
}

//        //
//        // Module references
//        //
//
//        // @api
//        function createExternalModuleReference(node<Expression> expression) {
//            auto node =
//            createBaseNode<ExternalModuleReference>(SyntaxKind::ExternalModuleReference);
//            node->expression = expression;
//            node->transformFlags |= propagateChildFlags(node->expression);
//            node->transformFlags &=
//            ~TransformFlags::ContainsPossibleTopLevelAwait; // always parsed
//            in an Await context return node;
//        }
//
//        // @api
//        function updateExternalModuleReference(node: ExternalModuleReference,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createExternalModuleReference(expression), node)
//                : node;
//        }
//
//        //
//        // JSDoc
//        //
//
//        // @api
//        // createJSDocAllType
//        // createJSDocUnknownType
//        function createJSDocPrimaryTypeWorker<T extends JSDocType>(kind:
//        T["kind"]) {
//            return createBaseNode(kind);
//        }
//
//        // @api
//        // createJSDocNullableType
//        // createJSDocNonNullableType
//        function createJSDocPrePostfixUnaryTypeWorker<T extends JSDocType & {
//        readonly optionalNode<TypeNode> type; readonly postfix: boolean
//        }>(SyntaxKind kind, type: T["type"], postfix = false): T {
//            auto node = createJSDocUnaryTypeWorker(
//                kind,
//                postfix ? type &&
//                parenthesizer.parenthesizeNonArrayTypeOfPostfixType(type) :
//                type
//            ) as Mutable<T>;
//            node->postfix = postfix;
//            return node;
//        }
//
//        // @api
//        // createJSDocOptionalType
//        // createJSDocVariadicType
//        // createJSDocNamepathType
//        function createJSDocUnaryTypeWorker<T extends JSDocType & { readonly
//        optionalNode<TypeNode> type; }>(SyntaxKind kind, type: T["type"]): T {
//            auto node = createBaseNode<T>(kind);
//            node->type = type;
//            return node;
//        }
//
//        // @api
//        // updateJSDocNonNullableType
//        // updateJSDocNullableType
//        function updateJSDocPrePostfixUnaryTypeWorker<T extends JSDocType & {
//        readonly optionalNode<TypeNode> type; readonly postfix: boolean;
//        }>(SyntaxKind kind, node: T, type: T["type"]): T {
//            return node->type != type
//            ? update(createJSDocPrePostfixUnaryTypeWorker(kind, type,
//            node->postfix), node) : node;
//        }
//
//        // @api
//        // updateJSDocOptionalType
//        // updateJSDocVariadicType
//        // updateJSDocNamepathType
//        function updateJSDocUnaryTypeWorker<T extends JSDocType & { readonly
//        optionalNode<TypeNode> type; }>(SyntaxKind kind, node: T, type:
//        T["type"]): T {
//            return node->type != type
//                ? update(createJSDocUnaryTypeWorker(kind, type), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocFunctionType(node<NodeArray> parameters,
//        optionalNode<TypeNode> type): JSDocFunctionType {
//            auto node = createBaseSignatureDeclaration<JSDocFunctionType>(
//                SyntaxKind::JSDocFunctionType,
//                /*decorators*/ nullptr,
//                /*modifiers*/ nullptr,
//                /*name*/ {},
//                /*typeParameters*/ {},
//                parameters,
//                type
//            );
//            return node;
//        }
//
//        // @api
//        function updateJSDocFunctionType(node: JSDocFunctionType,
//        tscpp::node<NodeArray> parameters, optionalNode<TypeNode> type):
//        JSDocFunctionType {
//            return node->parameters != parameters
//                || node->type != type
//                ? update(createJSDocFunctionType(parameters, type), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocTypeLiteral(propertyTags?: readonly
//        JSDocPropertyLikeTag[], isArrayType = false): JSDocTypeLiteral {
//            auto node =
//            createBaseNode<JSDocTypeLiteral>(SyntaxKind::JSDocTypeLiteral);
//            node->jsDocPropertyTags = asNodeArray(propertyTags);
//            node->isArrayType = isArrayType;
//            return node;
//        }
//
//        // @api
//        function updateJSDocTypeLiteral(node: JSDocTypeLiteral, propertyTags:
//        readonly JSDocPropertyLikeTag[] | undefined, isArrayType: boolean):
//        JSDocTypeLiteral {
//            return node->jsDocPropertyTags != propertyTags
//                || node->isArrayType != isArrayType
//                ? update(createJSDocTypeLiteral(propertyTags, isArrayType),
//                node) : node;
//        }
//
//        // @api
//        function createJSDocTypeExpression(node<TypeNode> type):
//        JSDocTypeExpression {
//            auto node =
//            createBaseNode<JSDocTypeExpression>(SyntaxKind::JSDocTypeExpression);
//            node->type = type;
//            return node;
//        }
//
//        // @api
//        function updateJSDocTypeExpression(node: JSDocTypeExpression,
//        tscpp::node<TypeNode> type): JSDocTypeExpression {
//            return node->type != type
//                ? update(createJSDocTypeExpression(type), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocSignature(typeParameters: readonly
//        JSDocTemplateTag[] | undefined, parameters: readonly
//        JSDocParameterTag[], type?: JSDocReturnTag): JSDocSignature {
//            auto node =
//            createBaseNode<JSDocSignature>(SyntaxKind::JSDocSignature);
//            node->typeParameters = asNodeArray(typeParameters);
//            node->parameters = createNodeArray(parameters);
//            node->type = type;
//            return node;
//        }
//
//        // @api
//        function updateJSDocSignature(node: JSDocSignature, typeParameters:
//        readonly JSDocTemplateTag[] | undefined, parameters: readonly
//        JSDocParameterTag[], type: JSDocReturnTag | undefined): JSDocSignature
//        {
//            return node->typeParameters != typeParameters
//                || node->parameters != parameters
//                || node->type != type
//                ? update(createJSDocSignature(typeParameters, parameters,
//                type), node) : node;
//        }
//
//        function getDefaultTagName(node: JSDocTag) {
//            auto defaultTagName = getDefaultTagNameForKind(node->kind);
//            return node->tagName.escapedText ==
//            escapeLeadingUnderscores(defaultTagName)
//                ? node->tagName
//                : createIdentifier(defaultTagName);
//        }
//
//        // @api
//        function createBaseJSDocTag<T extends JSDocTag>(SyntaxKind kind,
//        tagName: Identifier, comment: string | NodeArray<JSDocComment> |
//        undefined) {
//            auto node = createBaseNode<T>(kind);
//            node->tagName = tagName;
//            node->comment = comment;
//            return node;
//        }
//
//        // @api
//        function createJSDocTemplateTag(tagName: Identifier | undefined,
//        constraint: JSDocTypeExpression | undefined, typeParameters: readonly
//        TypeParameterDeclaration[], comment?: string |
//        NodeArray<JSDocComment>): JSDocTemplateTag {
//            auto node =
//            createBaseJSDocTag<JSDocTemplateTag>(SyntaxKind::JSDocTemplateTag,
//            tagName ?? createIdentifier("template"), comment);
//            node->constraint = constraint;
//            node->typeParameters = createNodeArray(typeParameters);
//            return node;
//        }
//
//        // @api
//        function updateJSDocTemplateTag(node: JSDocTemplateTag, tagName:
//        Identifier = getDefaultTagName(node), constraint: JSDocTypeExpression
//        | undefined, typeParameters: readonly TypeParameterDeclaration[],
//        comment: string | NodeArray<JSDocComment> | undefined):
//        JSDocTemplateTag {
//            return node->tagName != tagName
//                || node->constraint != constraint
//                || node->typeParameters != typeParameters
//                || node->comment != comment
//                ? update(createJSDocTemplateTag(tagName, constraint,
//                typeParameters, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocTypedefTag(tagName: Identifier | undefined,
//        typeExpression?: JSDocTypeExpression, fullName?: Identifier |
//        JSDocNamespaceDeclaration, comment?: string |
//        NodeArray<JSDocComment>): JSDocTypedefTag {
//            auto node =
//            createBaseJSDocTag<JSDocTypedefTag>(SyntaxKind::JSDocTypedefTag,
//            tagName ?? createIdentifier("typedef"), comment);
//            node->typeExpression = typeExpression;
//            node->fullName = fullName;
//            node->name = getJSDocTypeAliasName(fullName);
//            return node;
//        }
//
//        // @api
//        function updateJSDocTypedefTag(node: JSDocTypedefTag, tagName:
//        Identifier = getDefaultTagName(node), typeExpression:
//        JSDocTypeExpression | undefined, fullName: Identifier |
//        JSDocNamespaceDeclaration | undefined, comment: string |
//        NodeArray<JSDocComment> | undefined): JSDocTypedefTag {
//            return node->tagName != tagName
//                || node->typeExpression != typeExpression
//                || node->fullName != fullName
//                || node->comment != comment
//                ? update(createJSDocTypedefTag(tagName, typeExpression,
//                fullName, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocParameterTag(tagName: Identifier | undefined,
//        name: EntityName, isBracketed: boolean, typeExpression?:
//        JSDocTypeExpression, isNameFirst?: boolean, comment?: string |
//        NodeArray<JSDocComment>): JSDocParameterTag {
//            auto node =
//            createBaseJSDocTag<JSDocParameterTag>(SyntaxKind::JSDocParameterTag,
//            tagName ?? createIdentifier("param"), comment);
//            node->typeExpression = typeExpression;
//            node->name = name;
//            node->isNameFirst = !!isNameFirst;
//            node->isBracketed = isBracketed;
//            return node;
//        }
//
//        // @api
//        function updateJSDocParameterTag(node: JSDocParameterTag, tagName:
//        Identifier = getDefaultTagName(node), name: EntityName, isBracketed:
//        boolean, typeExpression: JSDocTypeExpression | undefined, isNameFirst:
//        boolean, comment: string | NodeArray<JSDocComment> | undefined):
//        JSDocParameterTag {
//            return node->tagName != tagName
//                || node->name != name
//                || node->isBracketed != isBracketed
//                || node->typeExpression != typeExpression
//                || node->isNameFirst != isNameFirst
//                || node->comment != comment
//                ? update(createJSDocParameterTag(tagName, name, isBracketed,
//                typeExpression, isNameFirst, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocPropertyTag(tagName: Identifier | undefined, name:
//        EntityName, isBracketed: boolean, typeExpression?:
//        JSDocTypeExpression, isNameFirst?: boolean, comment?: string |
//        NodeArray<JSDocComment>): JSDocPropertyTag {
//            auto node =
//            createBaseJSDocTag<JSDocPropertyTag>(SyntaxKind::JSDocPropertyTag,
//            tagName ?? createIdentifier("prop"), comment);
//            node->typeExpression = typeExpression;
//            node->name = name;
//            node->isNameFirst = !!isNameFirst;
//            node->isBracketed = isBracketed;
//            return node;
//        }
//
//        // @api
//        function updateJSDocPropertyTag(node: JSDocPropertyTag, tagName:
//        Identifier = getDefaultTagName(node), name: EntityName, isBracketed:
//        boolean, typeExpression: JSDocTypeExpression | undefined, isNameFirst:
//        boolean, comment: string | NodeArray<JSDocComment> | undefined):
//        JSDocPropertyTag {
//            return node->tagName != tagName
//                || node->name != name
//                || node->isBracketed != isBracketed
//                || node->typeExpression != typeExpression
//                || node->isNameFirst != isNameFirst
//                || node->comment != comment
//                ? update(createJSDocPropertyTag(tagName, name, isBracketed,
//                typeExpression, isNameFirst, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocCallbackTag(tagName: Identifier | undefined,
//        typeExpression: JSDocSignature, fullName?: Identifier |
//        JSDocNamespaceDeclaration, comment?: string |
//        NodeArray<JSDocComment>): JSDocCallbackTag {
//            auto node =
//            createBaseJSDocTag<JSDocCallbackTag>(SyntaxKind::JSDocCallbackTag,
//            tagName ?? createIdentifier("callback"), comment);
//            node->typeExpression = typeExpression;
//            node->fullName = fullName;
//            node->name = getJSDocTypeAliasName(fullName);
//            return node;
//        }
//
//        // @api
//        function updateJSDocCallbackTag(node: JSDocCallbackTag, tagName:
//        Identifier = getDefaultTagName(node), typeExpression: JSDocSignature,
//        fullName: Identifier | JSDocNamespaceDeclaration | undefined, comment:
//        string | NodeArray<JSDocComment> | undefined): JSDocCallbackTag {
//            return node->tagName != tagName
//                || node->typeExpression != typeExpression
//                || node->fullName != fullName
//                || node->comment != comment
//                ? update(createJSDocCallbackTag(tagName, typeExpression,
//                fullName, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocAugmentsTag(tagName: Identifier | undefined,
//        className: JSDocAugmentsTag["class"], comment?: string |
//        NodeArray<JSDocComment>): JSDocAugmentsTag {
//            auto node =
//            createBaseJSDocTag<JSDocAugmentsTag>(SyntaxKind::JSDocAugmentsTag,
//            tagName ?? createIdentifier("augments"), comment); node->class =
//            className; return node;
//        }
//
//        // @api
//        function updateJSDocAugmentsTag(node: JSDocAugmentsTag, tagName:
//        Identifier = getDefaultTagName(node), className:
//        JSDocAugmentsTag["class"], comment: string | NodeArray<JSDocComment> |
//        undefined): JSDocAugmentsTag {
//            return node->tagName != tagName
//                || node->class != className
//                || node->comment != comment
//                ? update(createJSDocAugmentsTag(tagName, className, comment),
//                node) : node;
//        }
//
//        // @api
//        function createJSDocImplementsTag(tagName: Identifier | undefined,
//        className: JSDocImplementsTag["class"], comment?: string |
//        NodeArray<JSDocComment>): JSDocImplementsTag {
//            auto node =
//            createBaseJSDocTag<JSDocImplementsTag>(SyntaxKind::JSDocImplementsTag,
//            tagName ?? createIdentifier("implements"), comment); node->class =
//            className; return node;
//        }
//
//        // @api
//        function createJSDocSeeTag(tagName: Identifier | undefined, name:
//        JSDocNameReference | undefined, comment?: string |
//        NodeArray<JSDocComment>): JSDocSeeTag {
//            auto node =
//            createBaseJSDocTag<JSDocSeeTag>(SyntaxKind::JSDocSeeTag, tagName
//            ?? createIdentifier("see"), comment); node->name = name; return
//            node;
//        }
//
//        // @api
//        function updateJSDocSeeTag(node: JSDocSeeTag, tagName: Identifier |
//        undefined, name: JSDocNameReference | undefined, comment?: string |
//        NodeArray<JSDocComment>): JSDocSeeTag {
//            return node->tagName != tagName
//                || node->name != name
//                || node->comment != comment
//                ? update(createJSDocSeeTag(tagName, name, comment), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocNameReference(name: EntityName | JSDocMemberName):
//        JSDocNameReference {
//            auto node =
//            createBaseNode<JSDocNameReference>(SyntaxKind::JSDocNameReference);
//            node->name = name;
//            return node;
//        }
//
//        // @api
//        function updateJSDocNameReference(node: JSDocNameReference, name:
//        EntityName | JSDocMemberName): JSDocNameReference {
//            return node->name != name
//                ? update(createJSDocNameReference(name), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocMemberName(left: EntityName | JSDocMemberName,
//        right: Identifier) {
//            auto node =
//            createBaseNode<JSDocMemberName>(SyntaxKind::JSDocMemberName);
//            node->left = left;
//            node->right = right;
//            node->transformFlags |=
//                propagateChildFlags(node->left) |
//                propagateChildFlags(node->right);
//            return node;
//        }
//
//        // @api
//        function updateJSDocMemberName(node: JSDocMemberName, left: EntityName
//        | JSDocMemberName, right: Identifier) {
//            return node->left != left
//                || node->right != right
//                ? update(createJSDocMemberName(left, right), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocLink(name: EntityName | JSDocMemberName |
//        undefined, text: string): JSDocLink {
//            auto node = createBaseNode<JSDocLink>(SyntaxKind::JSDocLink);
//            node->name = name;
//            node->text = text;
//            return node;
//        }
//
//        // @api
//        function updateJSDocLink(node: JSDocLink, name: EntityName |
//        JSDocMemberName | undefined, text: string): JSDocLink {
//            return node->name != name
//                ? update(createJSDocLink(name, text), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocLinkCode(name: EntityName | JSDocMemberName |
//        undefined, text: string): JSDocLinkCode {
//            auto node =
//            createBaseNode<JSDocLinkCode>(SyntaxKind::JSDocLinkCode);
//            node->name = name;
//            node->text = text;
//            return node;
//        }
//
//        // @api
//        function updateJSDocLinkCode(node: JSDocLinkCode, name: EntityName |
//        JSDocMemberName | undefined, text: string): JSDocLinkCode {
//            return node->name != name
//                ? update(createJSDocLinkCode(name, text), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocLinkPlain(name: EntityName | JSDocMemberName |
//        undefined, text: string): JSDocLinkPlain {
//            auto node =
//            createBaseNode<JSDocLinkPlain>(SyntaxKind::JSDocLinkPlain);
//            node->name = name;
//            node->text = text;
//            return node;
//        }
//
//        // @api
//        function updateJSDocLinkPlain(node: JSDocLinkPlain, name: EntityName |
//        JSDocMemberName | undefined, text: string): JSDocLinkPlain {
//            return node->name != name
//                ? update(createJSDocLinkPlain(name, text), node)
//                : node;
//        }
//
//        // @api
//        function updateJSDocImplementsTag(node: JSDocImplementsTag, tagName:
//        Identifier = getDefaultTagName(node), className:
//        JSDocImplementsTag["class"], comment: string | NodeArray<JSDocComment>
//        | undefined): JSDocImplementsTag {
//            return node->tagName != tagName
//                || node->class != className
//                || node->comment != comment
//                ? update(createJSDocImplementsTag(tagName, className,
//                comment), node) : node;
//        }
//
//        // @api
//        // createJSDocAuthorTag
//        // createJSDocClassTag
//        // createJSDocPublicTag
//        // createJSDocPrivateTag
//        // createJSDocProtectedTag
//        // createJSDocReadonlyTag
//        // createJSDocDeprecatedTag
//        function createJSDocSimpleTagWorker<T extends JSDocTag>(SyntaxKind
//        kind, tagName: Identifier | undefined, comment?: string |
//        NodeArray<JSDocComment>) {
//            auto node = createBaseJSDocTag<T>(kind, tagName ??
//            createIdentifier(getDefaultTagNameForKind(kind)), comment); return
//            node;
//        }
//
//        // @api
//        // updateJSDocAuthorTag
//        // updateJSDocClassTag
//        // updateJSDocPublicTag
//        // updateJSDocPrivateTag
//        // updateJSDocProtectedTag
//        // updateJSDocReadonlyTag
//        // updateJSDocDeprecatedTag
//        function updateJSDocSimpleTagWorker<T extends JSDocTag>(SyntaxKind
//        kind, node: T, tagName: Identifier = getDefaultTagName(node), comment:
//        string | NodeArray<JSDocComment> | undefined) {
//            return node->tagName != tagName
//                || node->comment != comment
//                ? update(createJSDocSimpleTagWorker(kind, tagName, comment),
//                node) : node;
//        }
//
//        // @api
//        // createJSDocTypeTag
//        // createJSDocReturnTag
//        // createJSDocThisTag
//        // createJSDocEnumTag
//        function createJSDocTypeLikeTagWorker<T extends JSDocTag & {
//        typeExpression?: JSDocTypeExpression }>(SyntaxKind kind, tagName:
//        Identifier | undefined, typeExpression?: JSDocTypeExpression,
//        comment?: string | NodeArray<JSDocComment>) {
//            auto node = createBaseJSDocTag<T>(kind, tagName ??
//            createIdentifier(getDefaultTagNameForKind(kind)), comment);
//            node->typeExpression = typeExpression;
//            return node;
//        }
//
//        // @api
//        // updateJSDocTypeTag
//        // updateJSDocReturnTag
//        // updateJSDocThisTag
//        // updateJSDocEnumTag
//        function updateJSDocTypeLikeTagWorker<T extends JSDocTag & {
//        typeExpression?: JSDocTypeExpression }>(SyntaxKind kind, node: T,
//        tagName: Identifier = getDefaultTagName(node), typeExpression:
//        JSDocTypeExpression | undefined, comment: string |
//        NodeArray<JSDocComment> | undefined) {
//            return node->tagName != tagName
//                || node->typeExpression != typeExpression
//                || node->comment != comment
//                ? update(createJSDocTypeLikeTagWorker(kind, tagName,
//                typeExpression, comment), node) : node;
//        }
//
//        // @api
//        function createJSDocUnknownTag(tagName: Identifier, comment?: string |
//        NodeArray<JSDocComment>): JSDocUnknownTag {
//            auto node =
//            createBaseJSDocTag<JSDocUnknownTag>(SyntaxKind::JSDocTag, tagName,
//            comment); return node;
//        }
//
//        // @api
//        function updateJSDocUnknownTag(node: JSDocUnknownTag, tagName:
//        Identifier, comment: string | NodeArray<JSDocComment> | undefined):
//        JSDocUnknownTag {
//            return node->tagName != tagName
//                || node->comment != comment
//                ? update(createJSDocUnknownTag(tagName, comment), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocText(text: string): JSDocText {
//            auto node = createBaseNode<JSDocText>(SyntaxKind::JSDocText);
//            node->text = text;
//            return node;
//        }
//
//        // @api
//        function updateJSDocText(node: JSDocText, text: string): JSDocText {
//            return node->text != text
//                ? update(createJSDocText(text), node)
//                : node;
//        }
//
//        // @api
//        function createJSDocComment(comment?: string | NodeArray<JSDocComment>
//        | undefined, tags?: readonly JSDocTag[] | undefined) {
//            auto node = createBaseNode<JSDoc>(SyntaxKind::JSDoc);
//            node->comment = comment;
//            node->tags = asNodeArray(tags);
//            return node;
//        }
//
//        // @api
//        function updateJSDocComment(node: JSDoc, comment: string |
//        NodeArray<JSDocComment> | undefined, tags: readonly JSDocTag[] |
//        undefined) {
//            return node->comment != comment
//                || node->tags != tags
//                ? update(createJSDocComment(comment, tags), node)
//                : node;
//        }
//
//        //
//        // JSX
//        //
//
// @api
node<JsxElement> Factory::createJsxElement(
    node<JsxOpeningElement> openingElement, tscpp::node<NodeArray> children,
    tscpp::node<JsxClosingElement> closingElement) {
  auto node = createBaseNode<JsxElement>(SyntaxKind::JsxElement);
  node->openingElement = openingElement;
  node->children = createNodeArray(children);
  node->closingElement = closingElement;
  node->transformFlags |= propagateChildFlags(node->openingElement) |
                          propagateChildrenFlags(node->children) |
                          propagateChildFlags(node->closingElement) |
                          (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxElement(node: JsxElement, openingElement:
//        JsxOpeningElement, children: readonly JsxChild[], closingElement:
//        JsxClosingElement) {
//            return node->openingElement != openingElement
//                || node->children != children
//                || node->closingElement != closingElement
//                ? update(createJsxElement(openingElement, children,
//                closingElement), node) : node;
//        }

// @api
node<JsxSelfClosingElement> Factory::createJsxSelfClosingElement(
    node<NodeUnion(JsxTagNameExpression)> tagName,
    optionalNode<NodeArray> typeArguments, tscpp::node<JsxAttributes> attributes) {
  auto node =
      createBaseNode<JsxSelfClosingElement>(SyntaxKind::JsxSelfClosingElement);
  node->tagName = tagName;
  node->typeArguments = asNodeArray(typeArguments);
  node->attributes = attributes;
  node->transformFlags |= propagateChildFlags(node->tagName) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildFlags(node->attributes) |
                          (int)TransformFlags::ContainsJsx;
  if (node->typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}
//
//        // @api
//        function updateJsxSelfClosingElement(node: JsxSelfClosingElement,
//        tagName: JsxTagNameExpression, optionalNode<NodeArray> typeArguments,
//        attributes: JsxAttributes) {
//            return node->tagName != tagName
//                || node->typeArguments != typeArguments
//                || node->attributes != attributes
//                ? update(createJsxSelfClosingElement(tagName, typeArguments,
//                attributes), node) : node;
//        }
//
// @api
node<JsxOpeningElement> Factory::createJsxOpeningElement(
    node<NodeUnion(JsxTagNameExpression)> tagName,
    optionalNode<NodeArray> typeArguments, tscpp::node<JsxAttributes> attributes) {
  auto node = createBaseNode<JsxOpeningElement>(SyntaxKind::JsxOpeningElement);
  node->tagName = tagName;
  node->typeArguments = asNodeArray(typeArguments);
  node->attributes = attributes;
  node->transformFlags |= propagateChildFlags(node->tagName) |
                          propagateChildrenFlags(node->typeArguments) |
                          propagateChildFlags(node->attributes) |
                          (int)TransformFlags::ContainsJsx;
  if (typeArguments) {
    node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
  }
  return node;
}
//
//        // @api
//        function updateJsxOpeningElement(node: JsxOpeningElement, tagName:
//        JsxTagNameExpression, optionalNode<NodeArray> typeArguments,
//        attributes: JsxAttributes) {
//            return node->tagName != tagName
//                || node->typeArguments != typeArguments
//                || node->attributes != attributes
//                ? update(createJsxOpeningElement(tagName, typeArguments,
//                attributes), node) : node;
//        }
//
// @api
node<JsxClosingElement> Factory::createJsxClosingElement(
    node<NodeUnion(JsxTagNameExpression)> tagName) {
  auto node = createBaseNode<JsxClosingElement>(SyntaxKind::JsxClosingElement);
  node->tagName = tagName;
  node->transformFlags |=
      propagateChildFlags(node->tagName) | (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxClosingElement(node: JsxClosingElement, tagName:
//        JsxTagNameExpression) {
//            return node->tagName != tagName
//                ? update(createJsxClosingElement(tagName), node)
//                : node;
//        }

// @api
node<JsxFragment> Factory::createJsxFragment(
    node<JsxOpeningFragment> openingFragment, tscpp::node<NodeArray> children,
    tscpp::node<JsxClosingFragment> closingFragment) {
  auto node = createBaseNode<JsxFragment>(SyntaxKind::JsxFragment);
  node->openingFragment = openingFragment;
  node->children = createNodeArray(children);
  node->closingFragment = closingFragment;
  node->transformFlags |= propagateChildFlags(node->openingFragment) |
                          propagateChildrenFlags(node->children) |
                          propagateChildFlags(node->closingFragment) |
                          (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxFragment(node: JsxFragment, openingFragment:
//        JsxOpeningFragment, children: readonly JsxChild[], closingFragment:
//        JsxClosingFragment) {
//            return node->openingFragment != openingFragment
//                || node->children != children
//                || node->closingFragment != closingFragment
//                ? update(createJsxFragment(openingFragment, children,
//                closingFragment), node) : node;
//        }
//
//
//        // @api
//        function updateJsxText(node: JsxText, text: string,
//        containsOnlyTriviaWhiteSpaces?: boolean) {
//            return node->text != text
//                || node->containsOnlyTriviaWhiteSpaces !=
//                containsOnlyTriviaWhiteSpaces ? update(createJsxText(text,
//                containsOnlyTriviaWhiteSpaces), node) : node;
//        }
//
// @api
node<JsxOpeningFragment> Factory::createJsxOpeningFragment() {
  auto node =
      createBaseNode<JsxOpeningFragment>(SyntaxKind::JsxOpeningFragment);
  node->transformFlags |= (int)TransformFlags::ContainsJsx;
  return node;
}

// @api
node<JsxClosingFragment> Factory::createJsxJsxClosingFragment() {
  auto node =
      createBaseNode<JsxClosingFragment>(SyntaxKind::JsxClosingFragment);
  node->transformFlags |= (int)TransformFlags::ContainsJsx;
  return node;
}

// @api
node<JsxAttribute> Factory::createJsxAttribute(
    node<Identifier> name,
    optionalNode<NodeUnion(JsxAttributeValue)> initializer) {
  auto node = createBaseNode<JsxAttribute>(SyntaxKind::JsxAttribute);
  node->name = name;
  node->initializer = initializer;
  node->transformFlags |= propagateChildFlags(node->name) |
                          propagateChildFlags(node->initializer) |
                          (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxAttribute(node: JsxAttribute, name: Identifier,
//        initializer: JsxAttributeValue | undefined) {
//            return node->name != name
//                || node->initializer != initializer
//                ? update(createJsxAttribute(name, initializer), node)
//                : node;
//        }
//
// @api
node<JsxAttributes> Factory::createJsxAttributes(node<NodeArray> properties) {
  auto node = createBaseNode<JsxAttributes>(SyntaxKind::JsxAttributes);
  node->properties = createNodeArray(properties);
  node->transformFlags |= propagateChildrenFlags(node->properties) |
                          (int)TransformFlags::ContainsJsx;
  return node;
}
//
//        // @api
//        function updateJsxAttributes(node: JsxAttributes, properties: readonly
//        JsxAttributeLike[]) {
//            return node->properties != properties
//                ? update(createJsxAttributes(properties), node)
//                : node;
//        }

// @api
node<JsxSpreadAttribute> Factory::createJsxSpreadAttribute(
    node<Expression> expression) {
  auto node =
      createBaseNode<JsxSpreadAttribute>(SyntaxKind::JsxSpreadAttribute);
  node->expression = expression;
  node->transformFlags |=
      propagateChildFlags(node->expression) | (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxSpreadAttribute(node: JsxSpreadAttribute,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createJsxSpreadAttribute(expression), node)
//                : node;
//        }
//
// @api
node<JsxExpression> Factory::createJsxExpression(
    optionalNode<DotDotDotToken> dotDotDotToken,
    optionalNode<Expression> expression) {
  auto node = createBaseNode<JsxExpression>(SyntaxKind::JsxExpression);
  node->dotDotDotToken = dotDotDotToken;
  node->expression = expression;
  node->transformFlags |= propagateChildFlags(node->dotDotDotToken) |
                          propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsJsx;
  return node;
}

//        // @api
//        function updateJsxExpression(node: JsxExpression,
//        optionalNode<Expression> expression) {
//            return node->expression != expression
//                ? update(createJsxExpression(node->dotDotDotToken,
//                expression), node) : node;
//        }
//
//        //
//        // Clauses
//        //
//
//        // @api
//        function createCaseClause(node<Expression> expression, statements:
//        readonly Statement[]) {
//            auto node = createBaseNode<CaseClause>(SyntaxKind::CaseClause);
//            node->expression =
//            parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
//            node->statements = createNodeArray(statements);
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildrenFlags(node->statements);
//            return node;
//        }
//
//        // @api
//        function updateCaseClause(node: CaseClause, tscpp::node<Expression>
//        expression, statements: readonly Statement[]) {
//            return node->expression != expression
//                || node->statements != statements
//                ? update(createCaseClause(expression, statements), node)
//                : node;
//        }
//
//        // @api
//        function createDefaultClause(statements: readonly Statement[]) {
//            auto node =
//            createBaseNode<DefaultClause>(SyntaxKind::DefaultClause);
//            node->statements = createNodeArray(statements);
//            node->transformFlags = propagateChildrenFlags(node->statements);
//            return node;
//        }
//
//        // @api
//        function updateDefaultClause(node: DefaultClause, statements: readonly
//        Statement[]) {
//            return node->statements != statements
//                ? update(createDefaultClause(statements), node)
//                : node;
//        }

// @api
node<HeritageClause> Factory::createHeritageClause(SyntaxKind token,
                                                   tscpp::node<NodeArray> types) {
  auto node = createBaseNode<HeritageClause>(SyntaxKind::HeritageClause);
  node->token = token;
  node->types = createNodeArray(types);
  node->transformFlags |= propagateChildrenFlags(node->types);
  switch (token) {
    case SyntaxKind::ExtendsKeyword:
      node->transformFlags |= (int)TransformFlags::ContainsES2015;
      break;
    case SyntaxKind::ImplementsKeyword:
      node->transformFlags |= (int)TransformFlags::ContainsTypeScript;
      break;
    default:
      throw runtime_error("invalid token");
  }
  return node;
}

//        // @api
//        function updateHeritageClause(node: HeritageClause, types: readonly
//        ExpressionWithTypeArguments[]) {
//            return node->types != types
//                ? update(createHeritageClause(node->token, types), node)
//                : node;
//        }
//
//        // @api
//        function createCatchClause(variableDeclaration: string | BindingName |
//        VariableDeclaration | undefined, block: Block) {
//            auto node = createBaseNode<CatchClause>(SyntaxKind::CatchClause);
//            if (typeof variableDeclaration == "string" || variableDeclaration
//            && !isVariableDeclaration(variableDeclaration)) {
//                variableDeclaration = createVariableDeclaration(
//                    variableDeclaration,
//                    /*exclamationToken*/ {},
//                    /*type*/ {},
//                    /*initializer*/ undefined
//                );
//            }
//            node->variableDeclaration = variableDeclaration;
//            node->block = block;
//            node->transformFlags |=
//                propagateChildFlags(node->variableDeclaration) |
//                propagateChildFlags(node->block);
//            if (!variableDeclaration) node->transformFlags |=
//            (int)TransformFlags::ContainsES2019; return node;
//        }
//
//        // @api
//        function updateCatchClause(node: CatchClause, variableDeclaration:
//        VariableDeclaration | undefined, block: Block) {
//            return node->variableDeclaration != variableDeclaration
//                || node->block != block
//                ? update(createCatchClause(variableDeclaration, block), node)
//                : node;
//        }
//
//        //
//        // Property assignments
//        //
//
// @api
node<PropertyAssignment> Factory::createPropertyAssignment(
    NameType name, tscpp::node<Expression> initializer) {
  auto node = createBaseNamedDeclaration<PropertyAssignment>(
      SyntaxKind::PropertyAssignment,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr, name);
  node->initializer =
      parenthesizer.parenthesizeExpressionForDisallowedComma(initializer);
  node->transformFlags |=
      propagateChildFlags(node->name) | propagateChildFlags(node->initializer);
  return node;
}

//        function finishUpdatePropertyAssignment(updated:
//        Mutable<PropertyAssignment>, original: PropertyAssignment) {
//            // copy children used only for error reporting
//            if (original.decorators) updated.decorators = original.decorators;
//            if (original.modifiers) updated.modifiers = original.modifiers;
//            if (original.questionToken) updated.questionToken =
//            original.questionToken; if (original.exclamationToken)
//            updated.exclamationToken = original.exclamationToken; return
//            update(updated, original);
//        }
//
//        // @api
//        function updatePropertyAssignment(node: PropertyAssignment, name:
//        PropertyName, initializer: Expression) {
//            return node->name != name
//                || node->initializer != initializer
//                ?
//                finishUpdatePropertyAssignment(createPropertyAssignment(name,
//                initializer), node) : node;
//        }
//
// @api
node<ShorthandPropertyAssignment> Factory::createShorthandPropertyAssignment(
    NameType name, optionalNode<Expression> objectAssignmentInitializer) {
  auto node = createBaseNamedDeclaration<ShorthandPropertyAssignment>(
      SyntaxKind::ShorthandPropertyAssignment,
      /*decorators*/ nullptr,
      /*modifiers*/ nullptr, name);
  node->objectAssignmentInitializer =
      objectAssignmentInitializer
          ? parenthesizer.parenthesizeExpressionForDisallowedComma(
                objectAssignmentInitializer)
          : nullptr;
  node->transformFlags |=
      propagateChildFlags(node->objectAssignmentInitializer) |
      (int)TransformFlags::ContainsES2015;
  return node;
}
//
//        function finishUpdateShorthandPropertyAssignment(updated:
//        Mutable<ShorthandPropertyAssignment>, original:
//        ShorthandPropertyAssignment) {
//            // copy children used only for error reporting
//            if (original.decorators) updated.decorators = original.decorators;
//            if (original.modifiers) updated.modifiers = original.modifiers;
//            if (original.equalsToken) updated.equalsToken =
//            original.equalsToken; if (original.questionToken)
//            updated.questionToken = original.questionToken; if
//            (original.exclamationToken) updated.exclamationToken =
//            original.exclamationToken; return update(updated, original);
//        }
//
//        // @api
//        function updateShorthandPropertyAssignment(node:
//        ShorthandPropertyAssignment, name: Identifier,
//        objectAssignmentInitializer: Expression | undefined) {
//            return node->name != name
//                || node->objectAssignmentInitializer !=
//                objectAssignmentInitializer ?
//                finishUpdateShorthandPropertyAssignment(createShorthandPropertyAssignment(name,
//                objectAssignmentInitializer), node) : node;
//        }
//
// @api
node<SpreadAssignment> Factory::createSpreadAssignment(
    node<Expression> expression) {
  auto node = createBaseNode<SpreadAssignment>(SyntaxKind::SpreadAssignment);
  node->expression =
      parenthesizer.parenthesizeExpressionForDisallowedComma(expression);
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsES2018 |
                          (int)TransformFlags::ContainsObjectRestOrSpread;
  return node;
}

//        // @api
//        function updateSpreadAssignment(node: SpreadAssignment,
//        tscpp::node<Expression> expression) {
//            return node->expression != expression
//                ? update(createSpreadAssignment(expression), node)
//                : node;
//        }
//
//        //
//        // Enum
//        //
//
//        // @api
//        function createEnumMember(NameType name, initializer?: Expression) {
//            auto node = createBaseNode<EnumMember>(SyntaxKind::EnumMember);
//            node->name = asName(name);
//            node->initializer = initializer &&
//            parenthesizer.parenthesizeExpressionForDisallowedComma(initializer);
//            node->transformFlags |=
//                propagateChildFlags(node->name) |
//                propagateChildFlags(node->initializer) |
//                (int)TransformFlags::ContainsTypeScript;
//            return node;
//        }
//
//        // @api
//        function updateEnumMember(node: EnumMember, name: PropertyName,
//        optionalNode<Expression> initializer) {
//            return node->name != name
//                || node->initializer != initializer
//                ? update(createEnumMember(name, initializer), node)
//                : node;
//        }
//
//        //
//        // Top-level nodes
//        //
//
//        // @api
//        function createSourceFile(
//            statements: readonly Statement[],
//            endOfFileToken: EndOfFileToken,
//            flags: NodeFlags
//        ) {
//            auto node =
//            basefactory::createBaseSourceFileNode(SyntaxKind::SourceFile) as
//            Mutable<SourceFile>; node->statements =
//            createNodeArray(statements); node->endOfFileToken =
//            endOfFileToken; node->flags |= flags; node->fileName = "";
//            node->text = "";
//            node->languageVersion = 0;
//            node->languageVariant = 0;
//            node->scriptKind = 0;
//            node->isDeclarationFile = false;
//            node->hasNoDefaultLib = false;
//            node->transformFlags |=
//                propagateChildrenFlags(node->statements) |
//                propagateChildFlags(node->endOfFileToken);
//            return node;
//        }
//
//        function cloneSourceFileWithChanges(
//            source: SourceFile,
//            statements: readonly Statement[],
//            isDeclarationFile: boolean,
//            referencedFiles: readonly FileReference[],
//            typeReferences: readonly FileReference[],
//            hasNoDefaultLib: boolean,
//            libReferences: readonly FileReference[]
//        ) {
//            auto node = (source.redirectInfo ?
//            Object.create(source.redirectInfo.redirectTarget) :
//            basefactory::createBaseSourceFileNode(SyntaxKind::SourceFile)) as
//            Mutable<SourceFile>; for (auto p in source) {
//                if (p == "emitNode" || hasProperty(node, p) ||
//                !hasProperty(source, p)) continue; (node as any)[p] = (source
//                as any)[p];
//            }
//            node->flags |= source.flags;
//            node->statements = createNodeArray(statements);
//            node->endOfFileToken = source.endOfFileToken;
//            node->isDeclarationFile = isDeclarationFile;
//            node->referencedFiles = referencedFiles;
//            node->typeReferenceDirectives = typeReferences;
//            node->hasNoDefaultLib = hasNoDefaultLib;
//            node->libReferenceDirectives = libReferences;
//            node->transformFlags =
//                propagateChildrenFlags(node->statements) |
//                propagateChildFlags(node->endOfFileToken);
//            node->impliedNodeFormat = source.impliedNodeFormat;
//            return node;
//        }
//
//        // @api
//        function updateSourceFile(
//            node: SourceFile,
//            statements: readonly Statement[],
//            isDeclarationFile = node->isDeclarationFile,
//            referencedFiles = node->referencedFiles,
//            typeReferenceDirectives = node->typeReferenceDirectives,
//            hasNoDefaultLib = node->hasNoDefaultLib,
//            libReferenceDirectives = node->libReferenceDirectives
//        ) {
//            return node->statements != statements
//                || node->isDeclarationFile != isDeclarationFile
//                || node->referencedFiles != referencedFiles
//                || node->typeReferenceDirectives != typeReferenceDirectives
//                || node->hasNoDefaultLib != hasNoDefaultLib
//                || node->libReferenceDirectives != libReferenceDirectives
//                ? update(cloneSourceFileWithChanges(node, statements,
//                isDeclarationFile, referencedFiles, typeReferenceDirectives,
//                hasNoDefaultLib, libReferenceDirectives), node) : node;
//        }
//
//        // @api
//        function createBundle(sourceFiles: readonly SourceFile[], prepends:
//        readonly (UnparsedSource | InputFiles)[] = emptyArray) {
//            auto node = createBaseNode<Bundle>(SyntaxKind::Bundle);
//            node->prepends = prepends;
//            node->sourceFiles = sourceFiles;
//            return node;
//        }
//
//        // @api
//        function updateBundle(node: Bundle, sourceFiles: readonly
//        SourceFile[], prepends: readonly (UnparsedSource | InputFiles)[] =
//        emptyArray) {
//            return node->sourceFiles != sourceFiles
//                || node->prepends != prepends
//                ? update(createBundle(sourceFiles, prepends), node)
//                : node;
//        }
//
//        // @api
//        function createUnparsedSource(prologues: readonly UnparsedPrologue[],
//        syntheticReferences: readonly UnparsedSyntheticReference[] |
//        undefined, texts: readonly UnparsedSourceText[]) {
//            auto node =
//            createBaseNode<UnparsedSource>(SyntaxKind::UnparsedSource);
//            node->prologues = prologues;
//            node->syntheticReferences = syntheticReferences;
//            node->texts = texts;
//            node->fileName = "";
//            node->text = "";
//            node->referencedFiles = emptyArray;
//            node->libReferenceDirectives = emptyArray;
//            node->getLineAndCharacterOfPosition = pos =>
//            getLineAndCharacterOfPosition(node, pos); return node;
//        }
//
//        function createBaseUnparsedNode<T extends UnparsedNode>(SyntaxKind
//        kind, data?: string) {
//            auto node = createBaseNode(kind);
//            node->data = data;
//            return node;
//        }
//
//        // @api
//        function createUnparsedPrologue(data?: string): UnparsedPrologue {
//            return createBaseUnparsedNode(SyntaxKind::UnparsedPrologue, data);
//        }
//
//        // @api
//        function createUnparsedPrepend(data: string | undefined, texts:
//        readonly UnparsedTextLike[]): UnparsedPrepend {
//            auto node =
//            createBaseUnparsedNode<UnparsedPrepend>(SyntaxKind::UnparsedPrepend,
//            data); node->texts = texts; return node;
//        }
//
//        // @api
//        function createUnparsedTextLike(data: string | undefined, internal:
//        boolean): UnparsedTextLike {
//            return createBaseUnparsedNode(internal ?
//            SyntaxKind::UnparsedInternalText : SyntaxKind::UnparsedText,
//            data);
//        }
//
//        // @api
//        function createUnparsedSyntheticReference(section:
//        BundleFileHasNoDefaultLib | BundleFileReference):
//        UnparsedSyntheticReference {
//            auto node =
//            createBaseNode<UnparsedSyntheticReference>(SyntaxKind::UnparsedSyntheticReference);
//            node->data = section.data;
//            node->section = section;
//            return node;
//        }
//
//        // @api
//        function createInputFiles(): InputFiles {
//            auto node = createBaseNode<InputFiles>(SyntaxKind::InputFiles);
//            node->javascriptText = "";
//            node->declarationText = "";
//            return node;
//        }
//
//        //
//        // Synthetic Nodes (used by checker)
//        //
//
//        // @api
//        function createSyntheticExpression(type: Type, isSpread = false,
//        tupleNameSource?: ParameterDeclaration | NamedTupleMember) {
//            auto node =
//            createBaseNode<SyntheticExpression>(SyntaxKind::SyntheticExpression);
//            node->type = type;
//            node->isSpread = isSpread;
//            node->tupleNameSource = tupleNameSource;
//            return node;
//        }
//
//        // @api
//        function createSyntaxList(children: Node[]) {
//            auto node = createBaseNode<SyntaxList>(SyntaxKind::SyntaxList);
//            node->_children = children;
//            return node;
//        }
//
//        //
//        // Transformation nodes
//        //
//
//        /**
//         * Creates a synthetic statement to act as a placeholder for a
//         not-emitted statement in
//         * order to preserve comments.
//         *
//         * @param original The original statement.
//         */
//        // @api
//        function createNotEmittedStatement(original: Node) {
//            auto node =
//            createBaseNode<NotEmittedStatement>(SyntaxKind::NotEmittedStatement);
//            node->original = original;
//            setTextRange(node, original);
//            return node;
//        }

/**
 * Creates a synthetic expression to act as a placeholder for a not-emitted
 * expression in order to preserve comments or sourcemap positions.
 *
 * @param expression The inner expression to emit.
 * @param original The original outer expression.
 */
// @api
node<PartiallyEmittedExpression> Factory::createPartiallyEmittedExpression(
    node<Expression> expression, optionalNode<Node> original) {
  auto node = createBaseNode<PartiallyEmittedExpression>(
      SyntaxKind::PartiallyEmittedExpression);
  node->expression = expression;
  node->original = original;
  node->transformFlags |= propagateChildFlags(node->expression) |
                          (int)TransformFlags::ContainsTypeScript;
  setTextRange(node, original);
  return node;
}

// @api
auto Factory::updatePartiallyEmittedExpression(
    node<PartiallyEmittedExpression> node, tscpp::node<Expression> expression) {
  return node->expression != expression
             ? update(
                   createPartiallyEmittedExpression(expression, node->original),
                   node)
             : node;
}

//        function flattenCommaElements(node: Expression): Expression | readonly
//        Expression[] {
//            if (nodeIsSynthesized(node) && !isParseTreeNode(node) &&
//            !node->original && !node->emitNode && !node->id) {
//                if (isCommaListExpression(node)) {
//                    return node->elements;
//                }
//                if (isBinaryExpression(node) &&
//                isCommaToken(node->operatorToken)) {
//                    return [node->left, node->right];
//                }
//            }
//            return node;
//        }
//
//        // @api
//        function createCommaListExpression(elements: readonly Expression[]) {
//            auto node =
//            createBaseNode<CommaListExpression>(SyntaxKind::CommaListExpression);
//            node->elements = createNodeArray(sameFlatMap(elements,
//            flattenCommaElements)); node->transformFlags |=
//            propagateChildrenFlags(node->elements); return node;
//        }
//
//        // @api
//        function updateCommaListExpression(node: CommaListExpression,
//        elements: readonly Expression[]) {
//            return node->elements != elements
//                ? update(createCommaListExpression(elements), node)
//                : node;
//        }
//
//        /**
//         * Creates a synthetic element to act as a placeholder for the end of
//         an emitted declaration in
//         * order to properly emit exports.
//         */
//        // @api
//        function createEndOfDeclarationMarker(original: Node) {
//            auto node =
//            createBaseNode<EndOfDeclarationMarker>(SyntaxKind::EndOfDeclarationMarker);
//            node->emitNode = {} as EmitNode;
//            node->original = original;
//            return node;
//        }
//
//        /**
//         * Creates a synthetic element to act as a placeholder for the
//         beginning of a merged declaration in
//         * order to properly emit exports.
//         */
//        // @api
//        function createMergeDeclarationMarker(original: Node) {
//            auto node =
//            createBaseNode<MergeDeclarationMarker>(SyntaxKind::MergeDeclarationMarker);
//            node->emitNode = {} as EmitNode;
//            node->original = original;
//            return node;
//        }
//
//        // @api
//        function createSyntheticReferenceExpression(node<Expression>
//        expression, thisArg: Expression) {
//            auto node =
//            createBaseNode<SyntheticReferenceExpression>(SyntaxKind::SyntheticReferenceExpression);
//            node->expression = expression;
//            node->thisArg = thisArg;
//            node->transformFlags |=
//                propagateChildFlags(node->expression) |
//                propagateChildFlags(node->thisArg);
//            return node;
//        }
//
//        // @api
//        function updateSyntheticReferenceExpression(node:
//        SyntheticReferenceExpression, tscpp::node<Expression> expression,
//        thisArg: Expression) {
//            return node->expression != expression
//                || node->thisArg != thisArg
//                ? update(createSyntheticReferenceExpression(expression,
//                thisArg), node) : node;
//        }
//
//        // @api
//        function cloneNode<T extends Node | undefined>(node: T): T;
//        function cloneNode<T extends Node>(node: T) {
//            // We don't use "clone" from core.ts here, as we need to preserve
//            the prototype chain of
//            // the original node-> We also need to exclude specific properties
//            and only include own-
//            // properties (to skip members already defined on the shared
//            prototype). if (node == undefined) {
//                return node;
//            }
//
//            auto clone =
//                isSourceFile(node) ?
//                basefactory::createBaseSourceFileNode(SyntaxKind::SourceFile)
//                as T : isIdentifier(node) ?
//                basefactory::createBaseIdentifierNode(SyntaxKind::Identifier)
//                as T : isPrivateIdentifier(node) ?
//                basefactory::createBasePrivateIdentifierNode(SyntaxKind::PrivateIdentifier)
//                as T : !isNodeKind(node->kind) ?
//                basefactory::createBaseTokenNode(node->kind) as T :
//                basefactory::createBaseNode(node->kind) as T;
//
//            (clone as Mutable<T>).flags |= (node->flags &
//            ~NodeFlags::Synthesized); (clone as Mutable<T>).transformFlags =
//            node->transformFlags; setOriginalNode(clone, node);
//
//            for (auto key in node) {
//                if (clone.hasOwnProperty(key) || !node->hasOwnProperty(key)) {
//                    continue;
//                }
//
//                clone[key] = node[key];
//            }
//
//            return clone;
//        }
//
//        // compound nodes
//        function createImmediatelyInvokedFunctionExpression(statements:
//        readonly Statement[]): CallExpression; function
//        createImmediatelyInvokedFunctionExpression(statements: readonly
//        Statement[], param: ParameterDeclaration, paramValue: Expression):
//        CallExpression; function
//        createImmediatelyInvokedFunctionExpression(statements: readonly
//        Statement[], param?: ParameterDeclaration, paramValue?: Expression) {
//            return createCallExpression(
//                createFunctionExpression(
//                    /*modifiers*/ nullptr,
//                    /*asteriskToken*/ {},
//                    /*name*/ {},
//                    /*typeParameters*/ {},
//                    /*parameters*/ param ? [param] : [],
//                    /*type*/ {},
//                    createBlock(statements, /*multiLine*/ true)
//                ),
//                /*typeArguments*/ {},
//                /*argumentsArray*/ paramValue ? [paramValue] : []
//            );
//        }
//
//        function createImmediatelyInvokedArrowFunction(statements: readonly
//        Statement[]): CallExpression; function
//        createImmediatelyInvokedArrowFunction(statements: readonly
//        Statement[], param: ParameterDeclaration, paramValue: Expression):
//        CallExpression; function
//        createImmediatelyInvokedArrowFunction(statements: readonly
//        Statement[], param?: ParameterDeclaration, paramValue?: Expression) {
//            return createCallExpression(
//                createArrowFunction(
//                    /*modifiers*/ nullptr,
//                    /*typeParameters*/ {},
//                    /*parameters*/ param ? [param] : [],
//                    /*type*/ {},
//                    /*equalsGreaterThanToken*/ {},
//                    createBlock(statements, /*multiLine*/ true)
//                ),
//                /*typeArguments*/ {},
//                /*argumentsArray*/ paramValue ? [paramValue] : []
//            );
//        }
//
//        function createVoidZero() {
//            return createVoidExpression(createNumericLiteral("0"));
//        }
//
//        function createExportDefault(node<Expression> expression) {
//            return createExportAssignment(
//                /*decorators*/ nullptr,
//                /*modifiers*/ nullptr,
//                /*isExportEquals*/ false,
//                expression);
//        }
//
//        function createExternalModuleExport(exportName: Identifier) {
//            return createExportDeclaration(
//                /*decorators*/ nullptr,
//                /*modifiers*/ nullptr,
//                /*isTypeOnly*/ false,
//                createNamedExports([
//                    createExportSpecifier(/*isTypeOnly*/ false,
//                    /*propertyName*/ {}, exportName)
//                ])
//            );
//        }
//
//        //
//        // Utilities
//        //
//
//        function createTypeCheck(value: Expression, tag: TypeOfTag) {
//            return tag == "undefined"
//                ? factory::createStrictEquality(value, createVoidZero())
//                : factory::createStrictEquality(createTypeOfExpression(value),
//                createStringLiteral(tag));
//        }
//
//        function createMethodCall(object: Expression, methodName: string |
//        Identifier, argumentsList: readonly Expression[]) {
//            // Preserve the optionality of `object`.
//            if (isCallChain(object)) {
//                return createCallChain(
//                    createPropertyAccessChain(object, /*questionDotToken*/ {},
//                    methodName),
//                    /*questionDotToken*/ {},
//                    /*typeArguments*/ {},
//                    argumentsList
//                );
//            }
//            return createCallExpression(
//                createPropertyAccessExpression(object, methodName),
//                /*typeArguments*/ {},
//                argumentsList
//            );
//        }
//
//        function createFunctionBindCall(target: Expression, thisArg:
//        Expression, argumentsList: readonly Expression[]) {
//            return createMethodCall(target, "bind", [thisArg,
//            ...argumentsList]);
//        }
//
//        function createFunctionCallCall(target: Expression, thisArg:
//        Expression, argumentsList: readonly Expression[]) {
//            return createMethodCall(target, "call", [thisArg,
//            ...argumentsList]);
//        }
//
//        function createFunctionApplyCall(target: Expression, thisArg:
//        Expression, argumentsExpression: Expression) {
//            return createMethodCall(target, "apply", [thisArg,
//            argumentsExpression]);
//        }
//
//        function createGlobalMethodCall(globalObjectName: string, methodName:
//        string, argumentsList: readonly Expression[]) {
//            return createMethodCall(createIdentifier(globalObjectName),
//            methodName, argumentsList);
//        }
//
//        function createArraySliceCall(array: Expression, start?: number |
//        Expression) {
//            return createMethodCall(array, "slice", start == undefined ? [] :
//            [asExpression(start)]);
//        }
//
//        function createArrayConcatCall(array: Expression, argumentsList:
//        readonly Expression[]) {
//            return createMethodCall(array, "concat", argumentsList);
//        }
//
//        function createObjectDefinePropertyCall(target: Expression,
//        propertyName: string | Expression, attributes: Expression) {
//            return createGlobalMethodCall("Object", "defineProperty", [target,
//            asExpression(propertyName), attributes]);
//        }
//
//        function createReflectGetCall(target: Expression, propertyKey:
//        Expression, receiver?: Expression): CallExpression {
//            return createGlobalMethodCall("Reflect", "get", receiver ?
//            [target, propertyKey, receiver] : [target, propertyKey]);
//        }
//
//        function createReflectSetCall(target: Expression, propertyKey:
//        Expression, value: Expression, receiver?: Expression): CallExpression
//        {
//            return createGlobalMethodCall("Reflect", "set", receiver ?
//            [target, propertyKey, value, receiver] : [target, propertyKey,
//            value]);
//        }
//
//        function tryAddPropertyAssignment(properties:
//        Push<PropertyAssignment>, propertyName: string,
//        optionalNode<Expression> expression) {
//            if (expression) {
//                properties.push(createPropertyAssignment(propertyName,
//                expression)); return true;
//            }
//            return false;
//        }
//
//        function createPropertyDescriptor(attributes:
//        PropertyDescriptorAttributes, singleLine?: boolean) {
//            auto properties: PropertyAssignment[] = [];
//            tryAddPropertyAssignment(properties, "enumerable",
//            asExpression(attributes.enumerable));
//            tryAddPropertyAssignment(properties, "configurable",
//            asExpression(attributes.configurable));
//
//            let isData = tryAddPropertyAssignment(properties, "writable",
//            asExpression(attributes.writable)); isData =
//            tryAddPropertyAssignment(properties, "value", attributes.value) ||
//            isData;
//
//            let isAccessor = tryAddPropertyAssignment(properties, "get",
//            attributes.get); isAccessor = tryAddPropertyAssignment(properties,
//            "set", attributes.set) || isAccessor;
//
//            Debug::asserts(!(isData && isAccessor), "A PropertyDescriptor may
//            not be both an accessor descriptor and a data descriptor.");
//            return createObjectLiteralExpression(properties, !singleLine);
//        }

node<Expression> Factory::updateOuterExpression(
    node<OuterExpression> outerExpression, tscpp::node<Expression> expression) {
  switch (outerExpression->kind) {
    case SyntaxKind::ParenthesizedExpression:
      return updateParenthesizedExpression(
          to<ParenthesizedExpression>(outerExpression), expression);
    case SyntaxKind::TypeAssertionExpression:
      return updateTypeAssertion(to<TypeAssertion>(outerExpression),
                                 to<TypeAssertion>(outerExpression)->type,
                                 expression);
    case SyntaxKind::AsExpression:
      return updateAsExpression(to<AsExpression>(outerExpression), expression,
                                to<AsExpression>(outerExpression)->type);
    case SyntaxKind::NonNullExpression:
      return updateNonNullExpression(to<NonNullExpression>(outerExpression),
                                     expression);
    case SyntaxKind::PartiallyEmittedExpression:
      return updatePartiallyEmittedExpression(
          to<PartiallyEmittedExpression>(outerExpression), expression);
  }
  throw runtime_error("Invalid OuterExpression passed");
}

/**
 * Determines whether a node is a parenthesized expression that can be ignored
 * when recreating outer expressions.
 *
 * A parenthesized expression can be ignored when all of the following are true:
 *
 * - It's `pos` and `end` are not -1
 * - It does not have a custom source map range
 * - It does not have a custom comment range
 * - It does not have synthetic leading or trailing comments
 *
 * If an outermost parenthesized expression is ignored, but the containing
 * expression requires a parentheses around the expression to maintain
 * precedence, a new parenthesized expression should be created automatically
 * when the containing expression is created/updated.
 */
bool Factory::isIgnorableParen(node<Expression> node) {
  return isParenthesizedExpression(node) && nodeIsSynthesized(node) &&
         nodeIsSynthesized(getSourceMapRange(node)) &&
         nodeIsSynthesized(getCommentRange(node)) &&
         !some(getSyntheticLeadingComments(node)) &&
         !some(getSyntheticTrailingComments(node));
}

node<Expression> Factory::restoreOuterExpressions(
    optionalNode<Expression> outerExpression,
    tscpp::node<Expression> innerExpression, int kinds) {
  if (isOuterExpression(outerExpression, kinds) &&
      !isIgnorableParen(outerExpression)) {
    return updateOuterExpression(
        outerExpression, restoreOuterExpressions(getExpression(outerExpression),
                                                 innerExpression));
  }
  return innerExpression;
}

//        function restoreEnclosingLabel(node: Statement,
//        outermostLabeledStatement: LabeledStatement | undefined,
//        afterRestoreLabelCallback?: (node: LabeledStatement) => void):
//        Statement {
//            if (!outermostLabeledStatement) {
//                return node;
//            }
//            auto updated = updateLabeledStatement(
//                outermostLabeledStatement,
//                outermostLabeledStatement.label,
//                isLabeledStatement(outermostLabeledStatement.statement)
//                    ? restoreEnclosingLabel(node,
//                    outermostLabeledStatement.statement) : node
//            );
//            if (afterRestoreLabelCallback) {
//                afterRestoreLabelCallback(outermostLabeledStatement);
//            }
//            return updated;
//        }
//
//        function shouldBeCapturedInTempVariable(node: Expression,
//        cacheIdentifiers: boolean): boolean {
//            auto target = skipParentheses(node);
//            switch (target.kind) {
//                case SyntaxKind::Identifier:
//                    return cacheIdentifiers;
//                case SyntaxKind::ThisKeyword:
//                case SyntaxKind::NumericLiteral:
//                case SyntaxKind::BigIntLiteral:
//                case SyntaxKind::StringLiteral:
//                    return false;
//                case SyntaxKind::ArrayLiteralExpression:
//                    auto elements = (target as
//                    ArrayLiteralExpression).elements; if (elements.length ==
//                    0) {
//                        return false;
//                    }
//                    return true;
//                case SyntaxKind::ObjectLiteralExpression:
//                    return (target as
//                    ObjectLiteralExpression).properties.length > 0;
//                default:
//                    return true;
//            }
//        }
//
//        function createCallBinding(node<Expression> expression,
//        recordTempVariable: (temp: Identifier) => void, languageVersion?:
//        ScriptTarget, cacheIdentifiers = false): CallBinding {
//            auto callee = skipOuterExpressions(expression,
//            OuterExpressionKinds::All); let thisArg: Expression; let target:
//            LeftHandSideExpression; if (isSuperProperty(callee)) {
//                thisArg = createThis();
//                target = callee;
//            }
//            else if (isSuperKeyword(callee)) {
//                thisArg = createThis();
//                target = languageVersion != undefined && languageVersion <
//                ScriptTarget.ES2015
//                    ? setTextRange(createIdentifier("_super"), callee)
//                    : callee as PrimaryExpression;
//            }
//            else if (getEmitFlags(callee) & EmitFlags.HelperName) {
//                thisArg = createVoidZero();
//                target = parenthesizer.parenthesizeLeftSideOfAccess(callee);
//            }
//            else if (isPropertyAccessExpression(callee)) {
//                if (shouldBeCapturedInTempVariable(callee.expression,
//                cacheIdentifiers)) {
//                    // for `a.b()` target is `(_a = a).b` and thisArg is `_a`
//                    thisArg = createTempVariable(recordTempVariable);
//                    target = createPropertyAccessExpression(
//                        setTextRange(
//                            factory::createAssignment(
//                                thisArg,
//                                callee.expression
//                            ),
//                            callee.expression
//                        ),
//                        callee.name
//                    );
//                    setTextRange(target, callee);
//                }
//                else {
//                    thisArg = callee.expression;
//                    target = callee;
//                }
//            }
//            else if (isElementAccessExpression(callee)) {
//                if (shouldBeCapturedInTempVariable(callee.expression,
//                cacheIdentifiers)) {
//                    // for `a[b]()` target is `(_a = a)[b]` and thisArg is
//                    `_a` thisArg = createTempVariable(recordTempVariable);
//                    target = createElementAccessExpression(
//                        setTextRange(
//                            factory::createAssignment(
//                                thisArg,
//                                callee.expression
//                            ),
//                            callee.expression
//                        ),
//                        callee.argumentExpression
//                    );
//                    setTextRange(target, callee);
//                }
//                else {
//                    thisArg = callee.expression;
//                    target = callee;
//                }
//            }
//            else {
//                // for `a()` target is `a` and thisArg is `void 0`
//                thisArg = createVoidZero();
//                target =
//                parenthesizer.parenthesizeLeftSideOfAccess(expression);
//            }
//
//            return { target, thisArg };
//        }
//
//        function createAssignmentTargetWrapper(paramName: Identifier,
//        tscpp::node<Expression> expression): LeftHandSideExpression {
//            return createPropertyAccessExpression(
//                // Explicit parens required because of v8 regression
//                (https://bugs.chromium.org/p/v8/issues/detail?id=9560)
//                createParenthesizedExpression(
//                    createObjectLiteralExpression([
//                        createSetAccessorDeclaration(
//                            /*decorators*/ nullptr,
//                            /*modifiers*/ nullptr,
//                            "value",
//                            [createParameterDeclaration(
//                                /*decorators*/ nullptr,
//                                /*modifiers*/ nullptr,
//                                /*dotDotDotToken*/ {},
//                                paramName,
//                                /*questionToken*/ {},
//                                /*type*/ {},
//                                /*initializer*/ undefined
//                            )],
//                            createBlock([
//                                createExpressionStatement(expression)
//                            ])
//                        )
//                    ])
//                ),
//                "value"
//            );
//        }
//
//        function inlineExpressions(expressions: readonly Expression[]) {
//            // Avoid deeply nested comma expressions as traversing them during
//            emit can result in "Maximum call
//            // stack size exceeded" errors.
//            return expressions.length > 10
//                ? createCommaListExpression(expressions)
//                : reduceLeft(expressions, factory::createComma)!;
//        }
//
//        function getName(node: Declaration | undefined, allowComments?:
//        boolean, allowSourceMaps?: boolean, emitFlags: EmitFlags = 0) {
//            auto nodeName = getNameOfDeclaration(node);
//            if (nodeName && isIdentifier(nodeName) &&
//            !isGeneratedIdentifier(nodeName)) {
//                // TODO(rbuckton): Does this need to be parented?
//                auto name = setParent(setTextRange(cloneNode(nodeName),
//                nodeName), nodeName.parent); emitFlags |=
//                getEmitFlags(nodeName); if (!allowSourceMaps) emitFlags |=
//                EmitFlags.NoSourceMap; if (!allowComments) emitFlags |=
//                EmitFlags.NoComments; if (emitFlags) setEmitFlags(name,
//                emitFlags); return name;
//            }
//            return getGeneratedNameForNode(node);
//        }
//
//        /**
//         * Gets the internal name of a declaration. This is primarily used for
//         declarations that can be
//         * referred to by name in the body of an ES5 class function body. An
//         internal name will *never*
//         * be prefixed with an module or namespace export modifier like
//         "exports." when emitted as an
//         * expression. An internal name will also *never* be renamed due to a
//         collision with a block
//         * scoped variable.
//         *
//         * @param node The declaration.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getInternalName(node: Declaration, allowComments?: boolean,
//        allowSourceMaps?: boolean) {
//            return getName(node, allowComments, allowSourceMaps,
//            EmitFlags.LocalName | EmitFlags.InternalName);
//        }
//
//        /**
//         * Gets the local name of a declaration. This is primarily used for
//         declarations that can be
//         * referred to by name in the declaration's immediate scope (classes,
//         enums, namespaces). A
//         * local name will *never* be prefixed with an module or namespace
//         export modifier like
//         * "exports." when emitted as an expression.
//         *
//         * @param node The declaration.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getLocalName(node: Declaration, allowComments?: boolean,
//        allowSourceMaps?: boolean) {
//            return getName(node, allowComments, allowSourceMaps,
//            EmitFlags.LocalName);
//        }
//
//        /**
//         * Gets the export name of a declaration. This is primarily used for
//         declarations that can be
//         * referred to by name in the declaration's immediate scope (classes,
//         enums, namespaces). An
//         * export name will *always* be prefixed with an module or namespace
//         export modifier like
//         * `"exports."` when emitted as an expression if the name points to an
//         exported symbol.
//         *
//         * @param node The declaration.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getExportName(node: Declaration, allowComments?: boolean,
//        allowSourceMaps?: boolean): Identifier {
//            return getName(node, allowComments, allowSourceMaps,
//            EmitFlags.ExportName);
//        }
//
//        /**
//         * Gets the name of a declaration for use in declarations.
//         *
//         * @param node The declaration.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getDeclarationName(node: Declaration | undefined,
//        allowComments?: boolean, allowSourceMaps?: boolean) {
//            return getName(node, allowComments, allowSourceMaps);
//        }
//
//        /**
//         * Gets a namespace-qualified name for use in expressions.
//         *
//         * @param ns The namespace identifier.
//         * @param name The name.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getNamespaceMemberName(ns: Identifier, name: Identifier,
//        allowComments?: boolean, allowSourceMaps?: boolean):
//        PropertyAccessExpression {
//            auto qualifiedName = createPropertyAccessExpression(ns,
//            nodeIsSynthesized(name) ? name : cloneNode(name));
//            setTextRange(qualifiedName, name);
//            let emitFlags: EmitFlags = 0;
//            if (!allowSourceMaps) emitFlags |= EmitFlags.NoSourceMap;
//            if (!allowComments) emitFlags |= EmitFlags.NoComments;
//            if (emitFlags) setEmitFlags(qualifiedName, emitFlags);
//            return qualifiedName;
//        }
//
//        /**
//         * Gets the exported name of a declaration for use in expressions.
//         *
//         * An exported name will *always* be prefixed with an module or
//         namespace export modifier like
//         * "exports." if the name points to an exported symbol.
//         *
//         * @param ns The namespace identifier.
//         * @param node The declaration.
//         * @param allowComments A value indicating whether comments may be
//         emitted for the name.
//         * @param allowSourceMaps A value indicating whether source maps may
//         be emitted for the name.
//         */
//        function getExternalModuleOrNamespaceExportName(ns: Identifier |
//        undefined, node: Declaration, allowComments?: boolean,
//        allowSourceMaps?: boolean): Identifier | PropertyAccessExpression {
//            if (ns && hasSyntacticModifier(node, ModifierFlags::Export)) {
//                return getNamespaceMemberName(ns, getName(node),
//                allowComments, allowSourceMaps);
//            }
//            return getExportName(node, allowComments, allowSourceMaps);
//        }
//
//        /**
//         * Copies any necessary standard and custom prologue-directives into
//         target array.
//         * @param source origin statements array
//         * @param target result statements array
//         * @param ensureUseStrict boolean determining whether the function
//         need to add prologue-directives
//         * @param visitor Optional callback used to visit any custom prologue
//         directives.
//         */
//        function copyPrologue(source: readonly Statement[], target:
//        Push<Statement>, ensureUseStrict?: boolean, visitor?: (node: Node) =>
//        VisitResult<Node>): number {
//            auto offset = copyStandardPrologue(source, target, 0,
//            ensureUseStrict); return copyCustomPrologue(source, target,
//            offset, visitor);
//        }
//
//        function isUseStrictPrologue(node: ExpressionStatement): boolean {
//            return isStringLiteral(node->expression) && node->expression.text
//            == "use strict";
//        }
//
//        function createUseStrictPrologue() {
//            return
//            startOnNewLine(createExpressionStatement(createStringLiteral("use
//            strict"))) as PrologueDirective;
//        }
//
//        /**
//         * Copies only the standard (string-expression) prologue-directives
//         into the target statement-array.
//         * @param source origin statements array
//         * @param target result statements array
//         * @param statementOffset The offset at which to begin the copy.
//         * @param ensureUseStrict boolean determining whether the function
//         need to add prologue-directives
//         * @returns Count of how many directive statements were copied.
//         */
//        function copyStandardPrologue(source: readonly Statement[], target:
//        Push<Statement>, statementOffset = 0, ensureUseStrict?: boolean):
//        number {
//            Debug::asserts(target.length == 0, "Prologue directives should be
//            at the first statement in the target statements array"); let
//            foundUseStrict = false; auto numStatements = source.length; while
//            (statementOffset < numStatements) {
//                auto statement = source[statementOffset];
//                if (isPrologueDirective(statement)) {
//                    if (isUseStrictPrologue(statement)) {
//                        foundUseStrict = true;
//                    }
//                    target.push(statement);
//                }
//                else {
//                    break;
//                }
//                statementOffset++;
//            }
//            if (ensureUseStrict && !foundUseStrict) {
//                target.push(createUseStrictPrologue());
//            }
//            return statementOffset;
//        }
//
//        /**
//         * Copies only the custom prologue-directives into target
//         statement-array.
//         * @param source origin statements array
//         * @param target result statements array
//         * @param statementOffset The offset at which to begin the copy.
//         * @param visitor Optional callback used to visit any custom prologue
//         directives.
//         */
//        function copyCustomPrologue(source: readonly Statement[], target:
//        Push<Statement>, statementOffset: number, visitor?: (node: Node) =>
//        VisitResult<Node>, filter?: (node: Node) => boolean): number; function
//        copyCustomPrologue(source: readonly Statement[], target:
//        Push<Statement>, statementOffset: number | undefined, visitor?: (node:
//        Node) => VisitResult<Node>, filter?: (node: Node) => boolean): number
//        | undefined; function copyCustomPrologue(source: readonly Statement[],
//        target: Push<Statement>, statementOffset: number | undefined,
//        visitor?: (node: Node) => VisitResult<Node>, filter: (node: Node) =>
//        boolean = returnTrue): number | undefined {
//            auto numStatements = source.length;
//            while (statementOffset != undefined && statementOffset <
//            numStatements) {
//                auto statement = source[statementOffset];
//                if (getEmitFlags(statement) & EmitFlags.CustomPrologue &&
//                filter(statement)) {
//                    append(target, visitor ? visitNode(statement, visitor,
//                    isStatement) : statement);
//                }
//                else {
//                    break;
//                }
//                statementOffset++;
//            }
//            return statementOffset;
//        }
//
//        /**
//         * Ensures "use strict" directive is added
//         *
//         * @param statements An array of statements
//         */
//        function ensureUseStrict(statements: NodeArray<Statement>):
//        NodeArray<Statement> {
//            auto foundUseStrict = findUseStrictPrologue(statements);
//
//            if (!foundUseStrict) {
//                return
//                setTextRange(createNodeArray<Statement>([createUseStrictPrologue(),
//                ...statements]), statements);
//            }
//
//            return statements;
//        }
//
//        /**
//         * Lifts a node<NodeArray> containing only Statement nodes to a block.
//         *
//         * @param nodes The NodeArray.
//         */
//        function liftToBlock(nodes: readonly Node[]): Statement {
//            Debug::asserts(every(nodes, isStatementOrBlock), "Cannot lift
//            nodes to a Block."); return singleOrUndefined(nodes) as Statement
//            || createBlock(nodes as readonly Statement[]);
//        }
//
//        function findSpanEnd<T>(array: readonly T[], test: (value: T) =>
//        boolean, start: number) {
//            let i = start;
//            while (i < array.length && test(array[i])) {
//                i++;
//            }
//            return i;
//        }
//
//        function mergeLexicalEnvironment(statements: NodeArray<Statement>,
//        declarations: readonly Statement[] | undefined): NodeArray<Statement>;
//        function mergeLexicalEnvironment(statements: Statement[],
//        declarations: readonly Statement[] | undefined): Statement[]; function
//        mergeLexicalEnvironment(statements: Statement[] |
//        NodeArray<Statement>, declarations: readonly Statement[] | undefined)
//        {
//            if (!some(declarations)) {
//                return statements;
//            }
//
//            // When we merge new lexical statements into an existing statement
//            list, we merge them in the following manner:
//            //
//            // Given:
//            //
//            // | Left                               | Right |
//            //
//            |------------------------------------|-------------------------------------|
//            // | [standard prologues (left)]        | [standard prologues
//            (right)]        |
//            // | [hoisted functions (left)]         | [hoisted functions
//            (right)]         |
//            // | [hoisted variables (left)]         | [hoisted variables
//            (right)]         |
//            // | [lexical init statements (left)]   | [lexical init statements
//            (right)]   |
//            // | [other statements (left)]          | |
//            //
//            // The resulting statement list will be:
//            //
//            // | Result                              |
//            // |-------------------------------------|
//            // | [standard prologues (right)]        |
//            // | [standard prologues (left)]         |
//            // | [hoisted functions (right)]         |
//            // | [hoisted functions (left)]          |
//            // | [hoisted variables (right)]         |
//            // | [hoisted variables (left)]          |
//            // | [lexical init statements (right)]   |
//            // | [lexical init statements (left)]    |
//            // | [other statements (left)]           |
//            //
//            // NOTE: It is expected that new lexical init statements must be
//            evaluated before existing lexical init statements,
//            // as the prior transformation may depend on the evaluation of the
//            lexical init statements to be in the correct state.
//
//            // find standard prologues on left in the following order:
//            standard directives, hoisted functions, hoisted variables, other
//            custom auto leftStandardPrologueEnd = findSpanEnd(statements,
//            isPrologueDirective, 0); auto leftHoistedFunctionsEnd =
//            findSpanEnd(statements, isHoistedFunction,
//            leftStandardPrologueEnd); auto leftHoistedVariablesEnd =
//            findSpanEnd(statements, isHoistedVariableStatement,
//            leftHoistedFunctionsEnd);
//
//            // find standard prologues on right in the following order:
//            standard directives, hoisted functions, hoisted variables, other
//            custom auto rightStandardPrologueEnd = findSpanEnd(declarations,
//            isPrologueDirective, 0); auto rightHoistedFunctionsEnd =
//            findSpanEnd(declarations, isHoistedFunction,
//            rightStandardPrologueEnd); auto rightHoistedVariablesEnd =
//            findSpanEnd(declarations, isHoistedVariableStatement,
//            rightHoistedFunctionsEnd); auto rightCustomPrologueEnd =
//            findSpanEnd(declarations, isCustomPrologue,
//            rightHoistedVariablesEnd); Debug::asserts(rightCustomPrologueEnd
//            == declarations.length, "Expected declarations to be valid
//            standard or custom prologues");
//
//            // splice prologues from the right into the left. We do this in
//            reverse order
//            // so that we don't need to recompute the index on the left when
//            we insert items. auto left = isNodeArray(statements) ?
//            statements.slice() : statements;
//
//            // splice other custom prologues from right into left
//            if (rightCustomPrologueEnd > rightHoistedVariablesEnd) {
//                left.splice(leftHoistedVariablesEnd, 0,
//                ...declarations.slice(rightHoistedVariablesEnd,
//                rightCustomPrologueEnd));
//            }
//
//            // splice hoisted variables from right into left
//            if (rightHoistedVariablesEnd > rightHoistedFunctionsEnd) {
//                left.splice(leftHoistedFunctionsEnd, 0,
//                ...declarations.slice(rightHoistedFunctionsEnd,
//                rightHoistedVariablesEnd));
//            }
//
//            // splice hoisted functions from right into left
//            if (rightHoistedFunctionsEnd > rightStandardPrologueEnd) {
//                left.splice(leftStandardPrologueEnd, 0,
//                ...declarations.slice(rightStandardPrologueEnd,
//                rightHoistedFunctionsEnd));
//            }
//
//            // splice standard prologues from right into left (that are not
//            already in left) if (rightStandardPrologueEnd > 0) {
//                if (leftStandardPrologueEnd == 0) {
//                    left.splice(0, 0, ...declarations.slice(0,
//                    rightStandardPrologueEnd));
//                }
//                else {
//                    auto leftPrologues = new Map<string, boolean>();
//                    for (let i = 0; i < leftStandardPrologueEnd; i++) {
//                        auto leftPrologue = statements[i] as
//                        PrologueDirective;
//                        leftPrologues.set(leftPrologue.expression.text, true);
//                    }
//                    for (let i = rightStandardPrologueEnd - 1; i >= 0; i--) {
//                        auto rightPrologue = declarations[i] as
//                        PrologueDirective; if
//                        (!leftPrologues.has(rightPrologue.expression.text)) {
//                            left.unshift(rightPrologue);
//                        }
//                    }
//                }
//            }
//
//            if (isNodeArray(statements)) {
//                return setTextRange(createNodeArray(left,
//                statements.hasTrailingComma), statements);
//            }
//
//            return statements;
//        }
//
//        function updateModifiers<T extends HasModifiers>(node: T, modifiers:
//        readonly Modifier[] | ModifierFlags): T; function
//        updateModifiers(node: HasModifiers, modifiers: readonly Modifier[] |
//        ModifierFlags) {
//            let modifierArray;
//            if (typeof modifiers == "number") {
//                modifierArray = createModifiersFromModifierFlags(modifiers);
//            }
//            else {
//                modifierArray = modifiers;
//            }
//            return isParameter(node) ? updateParameterDeclaration(node,
//            node->decorators, modifierArray, node->dotDotDotToken, node->name,
//            node->questionToken, node->type, node->initializer) :
//                isPropertySignature(node) ? updatePropertySignature(node,
//                modifierArray, node->name, node->questionToken, node->type) :
//                isPropertyDeclaration(node) ? updatePropertyDeclaration(node,
//                node->decorators, modifierArray, node->name,
//                node->questionToken ?? node->exclamationToken, node->type,
//                node->initializer) : isMethodSignature(node) ?
//                updateMethodSignature(node, modifierArray, node->name,
//                node->questionToken, node->typeParameters, node->parameters,
//                node->type) : isMethodDeclaration(node) ?
//                updateMethodDeclaration(node, node->decorators, modifierArray,
//                node->asteriskToken, node->name, node->questionToken,
//                node->typeParameters, node->parameters, node->type,
//                node->body) : isConstructorDeclaration(node) ?
//                updateConstructorDeclaration(node, node->decorators,
//                modifierArray, node->parameters, node->body) :
//                isGetAccessorDeclaration(node) ?
//                updateGetAccessorDeclaration(node, node->decorators,
//                modifierArray, node->name, node->parameters, node->type,
//                node->body) : isSetAccessorDeclaration(node) ?
//                updateSetAccessorDeclaration(node, node->decorators,
//                modifierArray, node->name, node->parameters, node->body) :
//                isIndexSignatureDeclaration(node) ? updateIndexSignature(node,
//                node->decorators, modifierArray, node->parameters, node->type)
//                : isFunctionExpression(node) ? updateFunctionExpression(node,
//                modifierArray, node->asteriskToken, node->name,
//                node->typeParameters, node->parameters, node->type,
//                node->body) : isArrowFunction(node) ?
//                updateArrowFunction(node, modifierArray, node->typeParameters,
//                node->parameters, node->type, node->equalsGreaterThanToken,
//                node->body) : isClassExpression(node) ?
//                updateClassExpression(node, node->decorators, modifierArray,
//                node->name, node->typeParameters, node->heritageClauses,
//                node->members) : isVariableStatement(node) ?
//                updateVariableStatement(node, modifierArray,
//                node->declarationList) : isFunctionDeclaration(node) ?
//                updateFunctionDeclaration(node, node->decorators,
//                modifierArray, node->asteriskToken, node->name,
//                node->typeParameters, node->parameters, node->type,
//                node->body) : isClassDeclaration(node) ?
//                updateClassDeclaration(node, node->decorators, modifierArray,
//                node->name, node->typeParameters, node->heritageClauses,
//                node->members) : isInterfaceDeclaration(node) ?
//                updateInterfaceDeclaration(node, node->decorators,
//                modifierArray, node->name, node->typeParameters,
//                node->heritageClauses, node->members) :
//                isTypeAliasDeclaration(node) ?
//                updateTypeAliasDeclaration(node, node->decorators,
//                modifierArray, node->name, node->typeParameters, node->type) :
//                isEnumDeclaration(node) ? updateEnumDeclaration(node,
//                node->decorators, modifierArray, node->name, node->members) :
//                isModuleDeclaration(node) ? updateModuleDeclaration(node,
//                node->decorators, modifierArray, node->name, node->body) :
//                isImportEqualsDeclaration(node) ?
//                updateImportEqualsDeclaration(node, node->decorators,
//                modifierArray, node->isTypeOnly, node->name,
//                node->moduleReference) : isImportDeclaration(node) ?
//                updateImportDeclaration(node, node->decorators, modifierArray,
//                node->importClause, node->moduleSpecifier, node->assertClause)
//                : isExportAssignment(node) ? updateExportAssignment(node,
//                node->decorators, modifierArray, node->expression) :
//                isExportDeclaration(node) ? updateExportDeclaration(node,
//                node->decorators, modifierArray, node->isTypeOnly,
//                node->exportClause, node->moduleSpecifier, node->assertClause)
//                : Debug.assertNever(node);
//        }
//
//        function asNodeArray<T extends Node>(array: readonly T[]):
//        NodeArray<T>; function asNodeArray<T extends Node>(array: readonly T[]
//        | undefined): NodeArray<T> | undefined; function asNodeArray<T extends
//        Node>(array: readonly T[] | undefined): NodeArray<T> | undefined {
//            return array ? createNodeArray(array) : undefined;
//        }
//
//        function asToken<TKind extends SyntaxKind>(value: TKind |
//        Token<TKind>): Token<TKind> {
//            return typeof value == "number" ? createToken(value) : value;
//        }
//
//        function asEmbeddedStatement<T extends Node>(statement: T): T |
//        EmptyStatement; function asEmbeddedStatement<T extends
//        Node>(statement: T | undefined): T | EmptyStatement | undefined;

//    }

//    function updateWithOriginal<T extends Node>(updated: T, original: T): T {
//        if (updated != original) {
//            setOriginalNode(updated, original);
//            setTextRange(updated, original);
//        }
//        return updated;
//    }
//
//    function getDefaultTagNameForKind(kind: JSDocTag["kind"]): string {
//        switch (kind) {
//            case SyntaxKind::JSDocTypeTag: return "type";
//            case SyntaxKind::JSDocReturnTag: return "returns";
//            case SyntaxKind::JSDocThisTag: return "this";
//            case SyntaxKind::JSDocEnumTag: return "enum";
//            case SyntaxKind::JSDocAuthorTag: return "author";
//            case SyntaxKind::JSDocClassTag: return "class";
//            case SyntaxKind::JSDocPublicTag: return "public";
//            case SyntaxKind::JSDocPrivateTag: return "private";
//            case SyntaxKind::JSDocProtectedTag: return "protected";
//            case SyntaxKind::JSDocReadonlyTag: return "readonly";
//            case SyntaxKind::JSDocOverrideTag: return "override";
//            case SyntaxKind::JSDocTemplateTag: return "template";
//            case SyntaxKind::JSDocTypedefTag: return "typedef";
//            case SyntaxKind::JSDocParameterTag: return "param";
//            case SyntaxKind::JSDocPropertyTag: return "prop";
//            case SyntaxKind::JSDocCallbackTag: return "callback";
//            case SyntaxKind::JSDocAugmentsTag: return "augments";
//            case SyntaxKind::JSDocImplementsTag: return "implements";
//            default:
//                return Debug.fail(`Unsupported kind:
//                ${Debug.formatSyntaxKind(kind)}`);
//        }
//    }
//
//    let rawTextScanner: Scanner | undefined;
//    auto invalidValueSentinel: object = { };
//
//    function getCookedText(kind: TemplateLiteralToken["kind"], rawText:
//    string) {
//        if (!rawTextScanner) {
//            rawTextScanner = createScanner(ScriptTarget.Latest, /*skipTrivia*/
//            false, LanguageVariant.Standard);
//        }
//        switch (kind) {
//            case SyntaxKind::NoSubstitutionTemplateLiteral:
//                rawTextScanner.setText("`" + rawText + "`");
//                break;
//            case SyntaxKind::TemplateHead:
//                // tslint:disable-next-line no-invalid-template-strings
//                rawTextScanner.setText("`" + rawText + "${");
//                break;
//            case SyntaxKind::TemplateMiddle:
//                // tslint:disable-next-line no-invalid-template-strings
//                rawTextScanner.setText("}" + rawText + "${");
//                break;
//            case SyntaxKind::TemplateTail:
//                rawTextScanner.setText("}" + rawText + "`");
//                break;
//        }
//
//        let token = rawTextScanner.scan();
//        if (token == SyntaxKind::CloseBraceToken) {
//            token = rawTextScanner.reScanTemplateToken(/*isTaggedTemplate*/
//            false);
//        }
//
//        if (rawTextScanner.isUnterminated()) {
//            rawTextScanner.setText(undefined);
//            return invalidValueSentinel;
//        }
//
//        let tokenValue: string | undefined;
//        switch (token) {
//            case SyntaxKind::NoSubstitutionTemplateLiteral:
//            case SyntaxKind::TemplateHead:
//            case SyntaxKind::TemplateMiddle:
//            case SyntaxKind::TemplateTail:
//                tokenValue = rawTextScanner.getTokenValue();
//                break;
//        }
//
//        if (tokenValue == undefined || rawTextScanner.scan() !=
//        SyntaxKind::EndOfFileToken) {
//            rawTextScanner.setText(undefined);
//            return invalidValueSentinel;
//        }
//
//        rawTextScanner.setText(undefined);
//        return tokenValue;
//    }

/**
 * Gets the transform flags to exclude when unioning the transform flags of a
 * subtree.
 */
/* @internal */
TransformFlags Factory::getTransformFlagsSubtreeExclusions(SyntaxKind kind) {
  if (kind >= SyntaxKind::FirstTypeNode && kind <= SyntaxKind::LastTypeNode) {
    return TransformFlags::TypeExcludes;
  }

  switch (kind) {
    case SyntaxKind::CallExpression:
    case SyntaxKind::NewExpression:
    case SyntaxKind::ArrayLiteralExpression:
      return TransformFlags::ArrayLiteralOrCallOrNewExcludes;
    case SyntaxKind::ModuleDeclaration:
      return TransformFlags::ModuleExcludes;
    case SyntaxKind::Parameter:
      return TransformFlags::ParameterExcludes;
    case SyntaxKind::ArrowFunction:
      return TransformFlags::ArrowFunctionExcludes;
    case SyntaxKind::FunctionExpression:
    case SyntaxKind::FunctionDeclaration:
      return TransformFlags::FunctionExcludes;
    case SyntaxKind::VariableDeclarationList:
      return TransformFlags::VariableDeclarationListExcludes;
    case SyntaxKind::ClassDeclaration:
    case SyntaxKind::ClassExpression:
      return TransformFlags::ClassExcludes;
    case SyntaxKind::Constructor:
      return TransformFlags::ConstructorExcludes;
    case SyntaxKind::PropertyDeclaration:
      return TransformFlags::PropertyExcludes;
    case SyntaxKind::MethodDeclaration:
    case SyntaxKind::GetAccessor:
    case SyntaxKind::SetAccessor:
      return TransformFlags::MethodOrAccessorExcludes;
    case SyntaxKind::AnyKeyword:
    case SyntaxKind::NumberKeyword:
    case SyntaxKind::BigIntKeyword:
    case SyntaxKind::NeverKeyword:
    case SyntaxKind::StringKeyword:
    case SyntaxKind::ObjectKeyword:
    case SyntaxKind::BooleanKeyword:
    case SyntaxKind::SymbolKeyword:
    case SyntaxKind::VoidKeyword:
    case SyntaxKind::TypeParameter:
    case SyntaxKind::PropertySignature:
    case SyntaxKind::MethodSignature:
    case SyntaxKind::CallSignature:
    case SyntaxKind::ConstructSignature:
    case SyntaxKind::IndexSignature:
    case SyntaxKind::InterfaceDeclaration:
    case SyntaxKind::TypeAliasDeclaration:
      return TransformFlags::TypeExcludes;
    case SyntaxKind::ObjectLiteralExpression:
      return TransformFlags::ObjectLiteralExcludes;
    case SyntaxKind::CatchClause:
      return TransformFlags::CatchClauseExcludes;
    case SyntaxKind::ObjectBindingPattern:
    case SyntaxKind::ArrayBindingPattern:
      return TransformFlags::BindingPatternExcludes;
    case SyntaxKind::TypeAssertionExpression:
    case SyntaxKind::AsExpression:
    case SyntaxKind::PartiallyEmittedExpression:
    case SyntaxKind::ParenthesizedExpression:
    case SyntaxKind::SuperKeyword:
      return TransformFlags::OuterExpressionExcludes;
    case SyntaxKind::PropertyAccessExpression:
    case SyntaxKind::ElementAccessExpression:
      return TransformFlags::PropertyAccessExcludes;
    default:
      return TransformFlags::NodeExcludes;
  }
}
//
//    auto baseFactory = createBaseNodeFactory();
//
//    function makeSynthetic(node: Node) {
//        (node as Mutable<Node>).flags |= NodeFlags::Synthesized;
//        return node;
//    }
//
//    auto syntheticFactory: BaseNodeFactory = {
//        createBaseSourceFileNode: kind =>
//        makeSynthetic(basefactory::createBaseSourceFileNode(kind)),
//        createBaseIdentifierNode: kind =>
//        makeSynthetic(basefactory::createBaseIdentifierNode(kind)),
//        createBasePrivateIdentifierNode: kind =>
//        makeSynthetic(basefactory::createBasePrivateIdentifierNode(kind)),
//        createBaseTokenNode: kind =>
//        makeSynthetic(basefactory::createBaseTokenNode(kind)), createBaseNode:
//        kind => makeSynthetic(basefactory::createBaseNode(kind)),
//    };
//
//    export auto factory =
//    createNodeFactory(NodeFactoryFlags.NoIndentationOnFreshPropertyAccess,
//    syntheticFactory);
//
//    export function createUnparsedSourceFile(text: string): UnparsedSource;
//    export function createUnparsedSourceFile(inputFile: InputFiles, type: "js"
//    | "dts", stripInternal?: boolean): UnparsedSource; export function
//    createUnparsedSourceFile(text: string, mapPath: string | undefined, map:
//    string | undefined): UnparsedSource; export function
//    createUnparsedSourceFile(textOrInputFiles: string | InputFiles,
//    mapPathOrType?: string, mapTextOrStripInternal?: string | boolean):
//    UnparsedSource {
//        let stripInternal: boolean | undefined;
//        let bundleFileInfo: BundleFileInfo | undefined;
//        let fileName: string;
//        let text: string | undefined;
//        let length: number | (() => number);
//        let sourceMapPath: string | undefined;
//        let sourceMapText: string | undefined;
//        let getText: (() => string) | undefined;
//        let getSourceMapText: (() => string | undefined) | undefined;
//        let oldFileOfCurrentEmit: boolean | undefined;
//
//        if (!isString(textOrInputFiles)) {
//            Debug::asserts(mapPathOrType == "js" || mapPathOrType == "dts");
//            fileName = (mapPathOrType == "js" ?
//            textOrInputFiles.javascriptPath :
//            textOrInputFiles.declarationPath) || ""; sourceMapPath =
//            mapPathOrType == "js" ? textOrInputFiles.javascriptMapPath :
//            textOrInputFiles.declarationMapPath; getText = () => mapPathOrType
//            == "js" ? textOrInputFiles.javascriptText :
//            textOrInputFiles.declarationText; getSourceMapText = () =>
//            mapPathOrType == "js" ? textOrInputFiles.javascriptMapText :
//            textOrInputFiles.declarationMapText; length = () =>
//            getText!().length; if (textOrInputFiles.buildInfo &&
//            textOrInputFiles.buildInfo.bundle) {
//                Debug::asserts(mapTextOrStripInternal == undefined || typeof
//                mapTextOrStripInternal == "boolean"); stripInternal =
//                mapTextOrStripInternal; bundleFileInfo = mapPathOrType == "js"
//                ? textOrInputFiles.buildInfo.bundle.js :
//                textOrInputFiles.buildInfo.bundle.dts; oldFileOfCurrentEmit =
//                textOrInputFiles.oldFileOfCurrentEmit;
//            }
//        }
//        else {
//            fileName = "";
//            text = textOrInputFiles;
//            length = textOrInputFiles.length;
//            sourceMapPath = mapPathOrType;
//            sourceMapText = mapTextOrStripInternal as string;
//        }
//        auto node = oldFileOfCurrentEmit ?
//            parseOldFileOfCurrentEmit(Debug.checkDefined(bundleFileInfo)) :
//            parseUnparsedSourceFile(bundleFileInfo, stripInternal, length);
//        node->fileName = fileName;
//        node->sourceMapPath = sourceMapPath;
//        node->oldFileOfCurrentEmit = oldFileOfCurrentEmit;
//        if (getText && getSourceMapText) {
//            Object.defineProperty(node, "text", { get: getText });
//            Object.defineProperty(node, "sourceMapText", { get:
//            getSourceMapText });
//        }
//        else {
//            Debug::asserts(!oldFileOfCurrentEmit);
//            node->text = text ?? "";
//            node->sourceMapText = sourceMapText;
//        }
//
//        return node;
//    }
//
//    function parseUnparsedSourceFile(bundleFileInfo: BundleFileInfo |
//    undefined, stripInternal: boolean | undefined, length: number | (() =>
//    number)) {
//        let prologues: UnparsedPrologue[] | undefined;
//        let helpers: UnscopedEmitHelper[] | undefined;
//        let referencedFiles: FileReference[] | undefined;
//        let typeReferenceDirectives: FileReference[] | undefined;
//        let libReferenceDirectives: FileReference[] | undefined;
//        let prependChildren: UnparsedTextLike[] | undefined;
//        let texts: UnparsedSourceText[] | undefined;
//        let hasNoDefaultLib: boolean | undefined;
//
//        for (auto section of bundleFileInfo ? bundleFileInfo.sections :
//        emptyArray) {
//            switch (section.kind) {
//                case BundleFileSectionKind.Prologue:
//                    prologues = append(prologues,
//                    setTextRange(factory::createUnparsedPrologue(section.data),
//                    section)); break;
//                case BundleFileSectionKind.EmitHelpers:
//                    helpers = append(helpers,
//                    getAllUnscopedEmitHelpers().get(section.data)!); break;
//                case BundleFileSectionKind.NoDefaultLib:
//                    hasNoDefaultLib = true;
//                    break;
//                case BundleFileSectionKind.Reference:
//                    referencedFiles = append(referencedFiles, { pos: -1, end:
//                    -1, fileName: section.data }); break;
//                case BundleFileSectionKind.Type:
//                    typeReferenceDirectives = append(typeReferenceDirectives,
//                    { pos: -1, end: -1, fileName: section.data }); break;
//                case BundleFileSectionKind.TypeResolutionModeImport:
//                    typeReferenceDirectives = append(typeReferenceDirectives,
//                    { pos: -1, end: -1, fileName: section.data,
//                    resolutionMode: ModuleKind.ESNext }); break;
//                case BundleFileSectionKind.TypeResolutionModeRequire:
//                    typeReferenceDirectives = append(typeReferenceDirectives,
//                    { pos: -1, end: -1, fileName: section.data,
//                    resolutionMode: ModuleKind.CommonJS }); break;
//                case BundleFileSectionKind.Lib:
//                    libReferenceDirectives = append(libReferenceDirectives, {
//                    pos: -1, end: -1, fileName: section.data }); break;
//                case BundleFileSectionKind.Prepend:
//                    let prependTexts: UnparsedTextLike[] | undefined;
//                    for (auto text of section.texts) {
//                        if (!stripInternal || text.kind !=
//                        BundleFileSectionKind.Internal) {
//                            prependTexts = append(prependTexts,
//                            setTextRange(factory::createUnparsedTextLike(text.data,
//                            text.kind == BundleFileSectionKind.Internal),
//                            text));
//                        }
//                    }
//                    prependChildren = addRange(prependChildren, prependTexts);
//                    texts = append(texts,
//                    factory::createUnparsedPrepend(section.data, prependTexts
//                    ?? emptyArray)); break;
//                case BundleFileSectionKind.Internal:
//                    if (stripInternal) {
//                        if (!texts) texts = [];
//                        break;
//                    }
//                    // falls through
//
//                case BundleFileSectionKind.Text:
//                    texts = append(texts,
//                    setTextRange(factory::createUnparsedTextLike(section.data,
//                    section.kind == BundleFileSectionKind.Internal),
//                    section)); break;
//                default:
//                    Debug.assertNever(section);
//            }
//        }
//
//        if (!texts) {
//            auto textNode = factory::createUnparsedTextLike(/*data*/ {},
//            /*internal*/ false); setTextRangePosWidth(textNode, 0, typeof
//            length == "function" ? length() : length); texts = [textNode];
//        }
//
//        auto node = parseNodefactory::createUnparsedSource(prologues ??
//        emptyArray, /*syntheticReferences*/ {}, texts);
//        setEachParent(prologues, node);
//        setEachParent(texts, node);
//        setEachParent(prependChildren, node);
//        node->hasNoDefaultLib = hasNoDefaultLib;
//        node->helpers = helpers;
//        node->referencedFiles = referencedFiles || emptyArray;
//        node->typeReferenceDirectives = typeReferenceDirectives;
//        node->libReferenceDirectives = libReferenceDirectives || emptyArray;
//        return node;
//    }
//
//    function parseOldFileOfCurrentEmit(bundleFileInfo: BundleFileInfo) {
//        let texts: UnparsedTextLike[] | undefined;
//        let syntheticReferences: UnparsedSyntheticReference[] | undefined;
//        for (auto section of bundleFileInfo.sections) {
//            switch (section.kind) {
//                case BundleFileSectionKind.Internal:
//                case BundleFileSectionKind.Text:
//                    texts = append(texts,
//                    setTextRange(factory::createUnparsedTextLike(section.data,
//                    section.kind == BundleFileSectionKind.Internal),
//                    section)); break;
//
//                case BundleFileSectionKind.NoDefaultLib:
//                case BundleFileSectionKind.Reference:
//                case BundleFileSectionKind.Type:
//                case BundleFileSectionKind.TypeResolutionModeImport:
//                case BundleFileSectionKind.TypeResolutionModeRequire:
//                case BundleFileSectionKind.Lib:
//                    syntheticReferences = append(syntheticReferences,
//                    setTextRange(factory::createUnparsedSyntheticReference(section),
//                    section)); break;
//
//                // Ignore
//                case BundleFileSectionKind.Prologue:
//                case BundleFileSectionKind.EmitHelpers:
//                case BundleFileSectionKind.Prepend:
//                    break;
//
//                default:
//                    Debug.assertNever(section);
//            }
//        }
//
//        auto node = factory::createUnparsedSource(emptyArray,
//        syntheticReferences, texts ?? emptyArray);
//        setEachParent(syntheticReferences, node);
//        setEachParent(texts, node);
//        node->helpers = map(bundleFileInfo.sources &&
//        bundleFileInfo.sources.helpers, name =>
//        getAllUnscopedEmitHelpers().get(name)!); return node;
//    }
//
//    // TODO(rbuckton): Move part of this to factory
//    export function createInputFiles(
//        javascriptText: string,
//        declarationText: string
//    ): InputFiles;
//    export function createInputFiles(
//        readFileText: (path: string) => string | undefined,
//        javascriptPath: string,
//        javascriptMapPath: string | undefined,
//        declarationPath: string,
//        declarationMapPath: string | undefined,
//        buildInfoPath: string | undefined
//    ): InputFiles;
//    export function createInputFiles(
//        javascriptText: string,
//        declarationText: string,
//        javascriptMapPath: string | undefined,
//        javascriptMapText: string | undefined,
//        declarationMapPath: string | undefined,
//        declarationMapText: string | undefined
//    ): InputFiles;
//    /*@internal*/
//    export function createInputFiles(
//        javascriptText: string,
//        declarationText: string,
//        javascriptMapPath: string | undefined,
//        javascriptMapText: string | undefined,
//        declarationMapPath: string | undefined,
//        declarationMapText: string | undefined,
//        javascriptPath: string | undefined,
//        declarationPath: string | undefined,
//        buildInfoPath?: string | undefined,
//        buildInfo?: BuildInfo,
//        oldFileOfCurrentEmit?: boolean
//    ): InputFiles;
//    export function createInputFiles(
//        javascriptTextOrReadFileText: string | ((path: string) => string |
//        undefined), declarationTextOrJavascriptPath: string,
//        javascriptMapPath?: string,
//        javascriptMapTextOrDeclarationPath?: string,
//        declarationMapPath?: string,
//        declarationMapTextOrBuildInfoPath?: string,
//        javascriptPath?: string | undefined,
//        declarationPath?: string | undefined,
//        buildInfoPath?: string | undefined,
//        buildInfo?: BuildInfo,
//        oldFileOfCurrentEmit?: boolean
//    ): InputFiles {
//        auto node = parseNodefactory::createInputFiles();
//        if (!isString(javascriptTextOrReadFileText)) {
//            auto cache = new Map<string, string | false>();
//            auto textGetter = (path: string | undefined) => {
//                if (path == undefined) return undefined;
//                let value = cache.get(path);
//                if (value == undefined) {
//                    value = javascriptTextOrReadFileText(path);
//                    cache.set(path, value != undefined ? value : false);
//                }
//                return value != false ? value as string : undefined;
//            };
//            auto definedTextGetter = (path: string) => {
//                auto result = textGetter(path);
//                return result != undefined ? result : "/* Input file ${path}
//                was missing */\r\n";
//            };
//            let buildInfo: BuildInfo | false;
//            auto getAndCacheBuildInfo = (getText: () => string | undefined) =>
//            {
//                if (buildInfo == undefined) {
//                    auto result = getText();
//                    buildInfo = result != undefined ? getBuildInfo(result) :
//                    false;
//                }
//                return buildInfo || undefined;
//            };
//            node->javascriptPath = declarationTextOrJavascriptPath;
//            node->javascriptMapPath = javascriptMapPath;
//            node->declarationPath =
//            Debug.checkDefined(javascriptMapTextOrDeclarationPath);
//            node->declarationMapPath = declarationMapPath;
//            node->buildInfoPath = declarationMapTextOrBuildInfoPath;
//            Object.defineProperties(node, {
//                javascriptText: { get() { return
//                definedTextGetter(declarationTextOrJavascriptPath); } },
//                javascriptMapText: { get() { return
//                textGetter(javascriptMapPath); } }, // TODO:: if there is
//                inline sourceMap in jsFile, use that declarationText: { get()
//                { return
//                definedTextGetter(Debug.checkDefined(javascriptMapTextOrDeclarationPath));
//                } }, declarationMapText: { get() { return
//                textGetter(declarationMapPath); } }, // TODO:: if there is
//                inline sourceMap in dtsFile, use that buildInfo: { get() {
//                return getAndCacheBuildInfo(() =>
//                textGetter(declarationMapTextOrBuildInfoPath)); } }
//            });
//        }
//        else {
//            node->javascriptText = javascriptTextOrReadFileText;
//            node->javascriptMapPath = javascriptMapPath;
//            node->javascriptMapText = javascriptMapTextOrDeclarationPath;
//            node->declarationText = declarationTextOrJavascriptPath;
//            node->declarationMapPath = declarationMapPath;
//            node->declarationMapText = declarationMapTextOrBuildInfoPath;
//            node->javascriptPath = javascriptPath;
//            node->declarationPath = declarationPath;
//            node->buildInfoPath = buildInfoPath;
//            node->buildInfo = buildInfo;
//            node->oldFileOfCurrentEmit = oldFileOfCurrentEmit;
//        }
//        return node;
//    }
//
//    // tslint:disable-next-line variable-name
//    let SourceMapSource: new (fileName: string, text: string, skipTrivia?:
//    (pos: number) => number) => SourceMapSource;
//
//    /**
//     * Create an external source map source file reference
//     */
//    export function createSourceMapSource(fileName: string, text: string,
//    skipTrivia?: (pos: number) => number): SourceMapSource {
//        return new (SourceMapSource || (SourceMapSource =
//        objectAllocator.getSourceMapSourceConstructor()))(fileName, text,
//        skipTrivia);
//    }
//
//    // Utilities
//
//    function mergeTokenSourceMapRanges(sourceRanges: (TextRange |
//    undefined)[], destRanges: (TextRange | undefined)[]) {
//        if (!destRanges) destRanges = [];
//        for (auto key in sourceRanges) {
//            destRanges[key] = sourceRanges[key];
//        }
//        return destRanges;
//    }
}  // namespace tscpp