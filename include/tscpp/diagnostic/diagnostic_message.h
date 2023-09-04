#ifndef TSCPP_DIAGNOSTIC_DIAGNOSTIC_MESSAGE_H
#define TSCPP_DIAGNOSTIC_DIAGNOSTIC_MESSAGE_H

#include <memory>
#include <string>
#include <type_traits>

#include "tscpp/base/types.h"

namespace tscpp {
using types::DiagnosticCategory;
using types::DiagnosticMessage;

inline shared_ptr<DiagnosticMessage> diag(
    int code, DiagnosticCategory category, const std::string_view& key,
    const std::string_view& message, bool reportsUnnecessary = false,
    bool elidedInCompatabilityPyramid = false, bool reportsDeprecated = false) {
  return std::make_shared<DiagnosticMessage>(
      code, category, key, message, reportsUnnecessary,
      elidedInCompatabilityPyramid, reportsDeprecated);
}

namespace Diagnostics {
static shared_ptr<DiagnosticMessage> Unterminated_string_literal() {
  return diag(1002, DiagnosticCategory::Error,
              "Unterminated_string_literal_1002",
              "Unterminated string literal.");
};
static shared_ptr<DiagnosticMessage> Identifier_expected() {
  return diag(1003, DiagnosticCategory::Error, "Identifier_expected_1003",
              "Identifier expected.");
};
static shared_ptr<DiagnosticMessage> _0_expected() {
  return diag(1005, DiagnosticCategory::Error, "_0_expected_1005",
              "'{0}' expected.");
};
static shared_ptr<DiagnosticMessage>
A_file_cannot_have_a_reference_to_itself() {
  return diag(1006, DiagnosticCategory::Error,
              "A_file_cannot_have_a_reference_to_itself_1006",
              "A file cannot have a reference to itself.");
};
static shared_ptr<DiagnosticMessage>
The_parser_expected_to_find_a_1_to_match_the_0_token_here() {
  return diag(
      1007, DiagnosticCategory::Error,
      "The_parser_expected_to_find_a_1_to_match_the_0_token_here_1007",
      "The parser expected to find a '{1}' to match the '{0}' token here.");
};
static shared_ptr<DiagnosticMessage> Trailing_comma_not_allowed() {
  return diag(1009, DiagnosticCategory::Error,
              "Trailing_comma_not_allowed_1009", "Trailing comma not allowed.");
};
static shared_ptr<DiagnosticMessage> Asterisk_Slash_expected() {
  return diag(1010, DiagnosticCategory::Error, "Asterisk_Slash_expected_1010",
              "'*/' expected.");
};
static shared_ptr<DiagnosticMessage>
An_element_access_expression_should_take_an_argument() {
  return diag(1011, DiagnosticCategory::Error,
              "An_element_access_expression_should_take_an_argument_1011",
              "An element access expression should take an argument.");
};
static shared_ptr<DiagnosticMessage> Unexpected_token() {
  return diag(1012, DiagnosticCategory::Error, "Unexpected_token_1012",
              "Unexpected token.");
};
static shared_ptr<DiagnosticMessage>
A_rest_parameter_or_binding_pattern_may_not_have_a_trailing_comma() {
  return diag(
      1013, DiagnosticCategory::Error,
      "A_rest_parameter_or_binding_pattern_may_not_have_a_trailing_comma_1013",
      "A rest parameter or binding pattern may not have a trailing comma.");
};
static shared_ptr<DiagnosticMessage>
A_rest_parameter_must_be_last_in_a_parameter_list() {
  return diag(1014, DiagnosticCategory::Error,
              "A_rest_parameter_must_be_last_in_a_parameter_list_1014",
              "A rest parameter must be last in a parameter list.");
};
static shared_ptr<DiagnosticMessage>
Parameter_cannot_have_question_mark_and_initializer() {
  return diag(1015, DiagnosticCategory::Error,
              "Parameter_cannot_have_question_mark_and_initializer_1015",
              "Parameter cannot have question mark and initializer.");
};
static shared_ptr<DiagnosticMessage>
A_required_parameter_cannot_follow_an_optional_parameter() {
  return diag(1016, DiagnosticCategory::Error,
              "A_required_parameter_cannot_follow_an_optional_parameter_1016",
              "A required parameter cannot follow an optional parameter.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_cannot_have_a_rest_parameter() {
  return diag(1017, DiagnosticCategory::Error,
              "An_index_signature_cannot_have_a_rest_parameter_1017",
              "An index signature cannot have a rest parameter.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_cannot_have_an_accessibility_modifier() {
  return diag(
      1018, DiagnosticCategory::Error,
      "An_index_signature_parameter_cannot_have_an_accessibility_modifier_1018",
      "An index signature parameter cannot have an accessibility modifier.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_cannot_have_a_question_mark() {
  return diag(1019, DiagnosticCategory::Error,
              "An_index_signature_parameter_cannot_have_a_question_mark_1019",
              "An index signature parameter cannot have a question mark.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_cannot_have_an_initializer() {
  return diag(1020, DiagnosticCategory::Error,
              "An_index_signature_parameter_cannot_have_an_initializer_1020",
              "An index signature parameter cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_must_have_a_type_annotation() {
  return diag(1021, DiagnosticCategory::Error,
              "An_index_signature_must_have_a_type_annotation_1021",
              "An index signature must have a type annotation.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_must_have_a_type_annotation() {
  return diag(1022, DiagnosticCategory::Error,
              "An_index_signature_parameter_must_have_a_type_annotation_1022",
              "An index signature parameter must have a type annotation.");
};
static shared_ptr<DiagnosticMessage>
readonly_modifier_can_only_appear_on_a_property_declaration_or_index_signature() {
  return diag(1024, DiagnosticCategory::Error,
              "readonly_modifier_can_only_appear_on_a_property_declaration_or_"
              "index_signature_1024",
              "'readonly' modifier can only appear on a property declaration "
              "or index signature.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_cannot_have_a_trailing_comma() {
  return diag(1025, DiagnosticCategory::Error,
              "An_index_signature_cannot_have_a_trailing_comma_1025",
              "An index signature cannot have a trailing comma.");
};
static shared_ptr<DiagnosticMessage> Accessibility_modifier_already_seen() {
  return diag(1028, DiagnosticCategory::Error,
              "Accessibility_modifier_already_seen_1028",
              "Accessibility modifier already seen.");
};
static shared_ptr<DiagnosticMessage> _0_modifier_must_precede_1_modifier() {
  return diag(1029, DiagnosticCategory::Error,
              "_0_modifier_must_precede_1_modifier_1029",
              "'{0}' modifier must precede '{1}' modifier.");
};
static shared_ptr<DiagnosticMessage> _0_modifier_already_seen() {
  return diag(1030, DiagnosticCategory::Error, "_0_modifier_already_seen_1030",
              "'{0}' modifier already seen.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_class_elements_of_this_kind() {
  return diag(1031, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_class_elements_of_this_kind_1031",
              "'{0}' modifier cannot appear on class elements of this kind.");
};
static shared_ptr<DiagnosticMessage>
super_must_be_followed_by_an_argument_list_or_member_access() {
  return diag(
      1034, DiagnosticCategory::Error,
      "super_must_be_followed_by_an_argument_list_or_member_access_1034",
      "'super' must be followed by an argument list or member access.");
};
static shared_ptr<DiagnosticMessage>
Only_ambient_modules_can_use_quoted_names() {
  return diag(1035, DiagnosticCategory::Error,
              "Only_ambient_modules_can_use_quoted_names_1035",
              "Only ambient modules can use quoted names.");
};
static shared_ptr<DiagnosticMessage>
Statements_are_not_allowed_in_ambient_contexts() {
  return diag(1036, DiagnosticCategory::Error,
              "Statements_are_not_allowed_in_ambient_contexts_1036",
              "Statements are not allowed in ambient contexts.");
};
static shared_ptr<DiagnosticMessage>
A_declare_modifier_cannot_be_used_in_an_already_ambient_context() {
  return diag(
      1038, DiagnosticCategory::Error,
      "A_declare_modifier_cannot_be_used_in_an_already_ambient_context_1038",
      "A 'declare' modifier cannot be used in an already ambient context.");
};
static shared_ptr<DiagnosticMessage>
Initializers_are_not_allowed_in_ambient_contexts() {
  return diag(1039, DiagnosticCategory::Error,
              "Initializers_are_not_allowed_in_ambient_contexts_1039",
              "Initializers are not allowed in ambient contexts.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_be_used_in_an_ambient_context() {
  return diag(1040, DiagnosticCategory::Error,
              "_0_modifier_cannot_be_used_in_an_ambient_context_1040",
              "'{0}' modifier cannot be used in an ambient context.");
};
static shared_ptr<DiagnosticMessage> _0_modifier_cannot_be_used_here() {
  return diag(1042, DiagnosticCategory::Error,
              "_0_modifier_cannot_be_used_here_1042",
              "'{0}' modifier cannot be used here.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_a_module_or_namespace_element() {
  return diag(1044, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_a_module_or_namespace_element_1044",
              "'{0}' modifier cannot appear on a module or namespace element.");
};
static shared_ptr<DiagnosticMessage>
Top_level_declarations_in_d_ts_files_must_start_with_either_a_declare_or_export_modifier() {
  return diag(1046, DiagnosticCategory::Error,
              "Top_level_declarations_in_d_ts_files_must_start_with_either_a_"
              "declare_or_export_modifier_1046",
              "Top-level declarations in .d.ts files must start with either a "
              "'declare' or 'export' modifier.");
};
static shared_ptr<DiagnosticMessage> A_rest_parameter_cannot_be_optional() {
  return diag(1047, DiagnosticCategory::Error,
              "A_rest_parameter_cannot_be_optional_1047",
              "A rest parameter cannot be optional.");
};
static shared_ptr<DiagnosticMessage>
A_rest_parameter_cannot_have_an_initializer() {
  return diag(1048, DiagnosticCategory::Error,
              "A_rest_parameter_cannot_have_an_initializer_1048",
              "A rest parameter cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
A_set_accessor_must_have_exactly_one_parameter() {
  return diag(1049, DiagnosticCategory::Error,
              "A_set_accessor_must_have_exactly_one_parameter_1049",
              "A 'set' accessor must have exactly one parameter.");
};
static shared_ptr<DiagnosticMessage>
A_set_accessor_cannot_have_an_optional_parameter() {
  return diag(1051, DiagnosticCategory::Error,
              "A_set_accessor_cannot_have_an_optional_parameter_1051",
              "A 'set' accessor cannot have an optional parameter.");
};
static shared_ptr<DiagnosticMessage>
A_set_accessor_parameter_cannot_have_an_initializer() {
  return diag(1052, DiagnosticCategory::Error,
              "A_set_accessor_parameter_cannot_have_an_initializer_1052",
              "A 'set' accessor parameter cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
A_set_accessor_cannot_have_rest_parameter() {
  return diag(1053, DiagnosticCategory::Error,
              "A_set_accessor_cannot_have_rest_parameter_1053",
              "A 'set' accessor cannot have rest parameter.");
};
static shared_ptr<DiagnosticMessage> A_get_accessor_cannot_have_parameters() {
  return diag(1054, DiagnosticCategory::Error,
              "A_get_accessor_cannot_have_parameters_1054",
              "A 'get' accessor cannot have parameters.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_a_valid_async_function_return_type_in_ES5_SlashES3_because_it_does_not_refer_to_a_Promise_compatible_constructor_value() {
  return diag(
      1055, DiagnosticCategory::Error,
      "Type_0_is_not_a_valid_async_function_return_type_in_ES5_SlashES3_"
      "because_it_does_not_refer_to_a_Prom_1055",
      "Type '{0}' is not a valid async function return type in ES5/ES3 because "
      "it does not refer to a Promise-compatible constructor value.");
};
static shared_ptr<DiagnosticMessage>
Accessors_are_only_available_when_targeting_ECMAScript_5_and_higher() {
  return diag(
      1056, DiagnosticCategory::Error,
      "Accessors_are_only_available_when_targeting_ECMAScript_5_and_higher_"
      "1056",
      "Accessors are only available when targeting ECMAScript 5 and higher.");
};
static shared_ptr<DiagnosticMessage>
The_return_type_of_an_async_function_must_either_be_a_valid_promise_or_must_not_contain_a_callable_then_member() {
  return diag(1058, DiagnosticCategory::Error,
              "The_return_type_of_an_async_function_must_either_be_a_valid_"
              "promise_or_must_not_contain_a_callable_t_1058",
              "The return type of an async function must either be a valid "
              "promise or must not contain a callable 'then' member.");
};
static shared_ptr<DiagnosticMessage> A_promise_must_have_a_then_method() {
  return diag(1059, DiagnosticCategory::Error,
              "A_promise_must_have_a_then_method_1059",
              "A promise must have a 'then' method.");
};
static shared_ptr<DiagnosticMessage>
The_first_parameter_of_the_then_method_of_a_promise_must_be_a_callback() {
  return diag(1060, DiagnosticCategory::Error,
              "The_first_parameter_of_the_then_method_of_a_promise_must_be_a_"
              "callback_1060",
              "The first parameter of the 'then' method of a promise must be a "
              "callback.");
};
static shared_ptr<DiagnosticMessage> Enum_member_must_have_initializer() {
  return diag(1061, DiagnosticCategory::Error,
              "Enum_member_must_have_initializer_1061",
              "Enum member must have initializer.");
};
static shared_ptr<DiagnosticMessage>
Type_is_referenced_directly_or_indirectly_in_the_fulfillment_callback_of_its_own_then_method() {
  return diag(1062, DiagnosticCategory::Error,
              "Type_is_referenced_directly_or_indirectly_in_the_fulfillment_"
              "callback_of_its_own_then_method_1062",
              "Type is referenced directly or indirectly in the fulfillment "
              "callback of its own 'then' method.");
};
static shared_ptr<DiagnosticMessage>
An_export_assignment_cannot_be_used_in_a_namespace() {
  return diag(1063, DiagnosticCategory::Error,
              "An_export_assignment_cannot_be_used_in_a_namespace_1063",
              "An export assignment cannot be used in a namespace.");
};
static shared_ptr<DiagnosticMessage>
The_return_type_of_an_async_function_or_method_must_be_the_global_Promise_T_type_Did_you_mean_to_write_Promise_0() {
  return diag(1064, DiagnosticCategory::Error,
              "The_return_type_of_an_async_function_or_method_must_be_the_"
              "global_Promise_T_type_Did_you_mean_to_wri_1064",
              "The return type of an async function or method must be the "
              "global Promise<T> type. Did you mean to write 'Promise<{0}>'?");
};
static shared_ptr<DiagnosticMessage>
In_ambient_enum_declarations_member_initializer_must_be_constant_expression() {
  return diag(1066, DiagnosticCategory::Error,
              "In_ambient_enum_declarations_member_initializer_must_be_"
              "constant_expression_1066",
              "In ambient enum declarations member initializer must be "
              "constant expression.");
};
static shared_ptr<DiagnosticMessage>
Unexpected_token_A_constructor_method_accessor_or_property_was_expected() {
  return diag(1068, DiagnosticCategory::Error,
              "Unexpected_token_A_constructor_method_accessor_or_property_was_"
              "expected_1068",
              "Unexpected token. A constructor, method, accessor, or property "
              "was expected.");
};
static shared_ptr<DiagnosticMessage>
Unexpected_token_A_type_parameter_name_was_expected_without_curly_braces() {
  return diag(1069, DiagnosticCategory::Error,
              "Unexpected_token_A_type_parameter_name_was_expected_without_"
              "curly_braces_1069",
              "Unexpected token. A type parameter name was expected without "
              "curly braces.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_a_type_member() {
  return diag(1070, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_a_type_member_1070",
              "'{0}' modifier cannot appear on a type member.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_an_index_signature() {
  return diag(1071, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_an_index_signature_1071",
              "'{0}' modifier cannot appear on an index signature.");
};
static shared_ptr<DiagnosticMessage>
A_0_modifier_cannot_be_used_with_an_import_declaration() {
  return diag(1079, DiagnosticCategory::Error,
              "A_0_modifier_cannot_be_used_with_an_import_declaration_1079",
              "A '{0}' modifier cannot be used with an import declaration.");
};
static shared_ptr<DiagnosticMessage> Invalid_reference_directive_syntax() {
  return diag(1084, DiagnosticCategory::Error,
              "Invalid_reference_directive_syntax_1084",
              "Invalid 'reference' directive syntax.");
};
static shared_ptr<DiagnosticMessage>
Octal_literals_are_not_available_when_targeting_ECMAScript_5_and_higher_Use_the_syntax_0() {
  return diag(1085, DiagnosticCategory::Error,
              "Octal_literals_are_not_available_when_targeting_ECMAScript_5_"
              "and_higher_Use_the_syntax_0_1085",
              "Octal literals are not available when targeting ECMAScript 5 "
              "and higher. Use the syntax '{0}'.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_a_constructor_declaration() {
  return diag(1089, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_a_constructor_declaration_1089",
              "'{0}' modifier cannot appear on a constructor declaration.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_appear_on_a_parameter() {
  return diag(1090, DiagnosticCategory::Error,
              "_0_modifier_cannot_appear_on_a_parameter_1090",
              "'{0}' modifier cannot appear on a parameter.");
};
static shared_ptr<DiagnosticMessage>
Only_a_single_variable_declaration_is_allowed_in_a_for_in_statement() {
  return diag(1091, DiagnosticCategory::Error,
              "Only_a_single_variable_declaration_is_allowed_in_a_for_in_"
              "statement_1091",
              "Only a single variable declaration is allowed in a 'for...in' "
              "statement.");
};
static shared_ptr<DiagnosticMessage>
Type_parameters_cannot_appear_on_a_constructor_declaration() {
  return diag(1092, DiagnosticCategory::Error,
              "Type_parameters_cannot_appear_on_a_constructor_declaration_1092",
              "Type parameters cannot appear on a constructor declaration.");
};
static shared_ptr<DiagnosticMessage>
Type_annotation_cannot_appear_on_a_constructor_declaration() {
  return diag(1093, DiagnosticCategory::Error,
              "Type_annotation_cannot_appear_on_a_constructor_declaration_1093",
              "Type annotation cannot appear on a constructor declaration.");
};
static shared_ptr<DiagnosticMessage> An_accessor_cannot_have_type_parameters() {
  return diag(1094, DiagnosticCategory::Error,
              "An_accessor_cannot_have_type_parameters_1094",
              "An accessor cannot have type parameters.");
};
static shared_ptr<DiagnosticMessage>
A_set_accessor_cannot_have_a_return_type_annotation() {
  return diag(1095, DiagnosticCategory::Error,
              "A_set_accessor_cannot_have_a_return_type_annotation_1095",
              "A 'set' accessor cannot have a return type annotation.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_must_have_exactly_one_parameter() {
  return diag(1096, DiagnosticCategory::Error,
              "An_index_signature_must_have_exactly_one_parameter_1096",
              "An index signature must have exactly one parameter.");
};
static shared_ptr<DiagnosticMessage> _0_list_cannot_be_empty() {
  return diag(1097, DiagnosticCategory::Error, "_0_list_cannot_be_empty_1097",
              "'{0}' list cannot be empty.");
};
static shared_ptr<DiagnosticMessage> Type_parameter_list_cannot_be_empty() {
  return diag(1098, DiagnosticCategory::Error,
              "Type_parameter_list_cannot_be_empty_1098",
              "Type parameter list cannot be empty.");
};
static shared_ptr<DiagnosticMessage> Type_argument_list_cannot_be_empty() {
  return diag(1099, DiagnosticCategory::Error,
              "Type_argument_list_cannot_be_empty_1099",
              "Type argument list cannot be empty.");
};
static shared_ptr<DiagnosticMessage> Invalid_use_of_0_in_strict_mode() {
  return diag(1100, DiagnosticCategory::Error,
              "Invalid_use_of_0_in_strict_mode_1100",
              "Invalid use of '{0}' in strict mode.");
};
static shared_ptr<DiagnosticMessage>
with_statements_are_not_allowed_in_strict_mode() {
  return diag(1101, DiagnosticCategory::Error,
              "with_statements_are_not_allowed_in_strict_mode_1101",
              "'with' statements are not allowed in strict mode.");
};
static shared_ptr<DiagnosticMessage>
delete_cannot_be_called_on_an_identifier_in_strict_mode() {
  return diag(1102, DiagnosticCategory::Error,
              "delete_cannot_be_called_on_an_identifier_in_strict_mode_1102",
              "'delete' cannot be called on an identifier in strict mode.");
};
static shared_ptr<DiagnosticMessage>
for_await_loops_are_only_allowed_within_async_functions_and_at_the_top_levels_of_modules() {
  return diag(1103, DiagnosticCategory::Error,
              "for_await_loops_are_only_allowed_within_async_functions_and_at_"
              "the_top_levels_of_modules_1103",
              "'for await' loops are only allowed within async functions and "
              "at the top levels of modules.");
};
static shared_ptr<DiagnosticMessage>
A_continue_statement_can_only_be_used_within_an_enclosing_iteration_statement() {
  return diag(1104, DiagnosticCategory::Error,
              "A_continue_statement_can_only_be_used_within_an_enclosing_"
              "iteration_statement_1104",
              "A 'continue' statement can only be used within an enclosing "
              "iteration statement.");
};
static shared_ptr<DiagnosticMessage>
A_break_statement_can_only_be_used_within_an_enclosing_iteration_or_switch_statement() {
  return diag(1105, DiagnosticCategory::Error,
              "A_break_statement_can_only_be_used_within_an_enclosing_"
              "iteration_or_switch_statement_1105",
              "A 'break' statement can only be used within an enclosing "
              "iteration or switch statement.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_of_statement_may_not_be_async() {
  return diag(
      1106, DiagnosticCategory::Error,
      "The_left_hand_side_of_a_for_of_statement_may_not_be_async_1106",
      "The left-hand side of a 'for...of' statement may not be 'async'.");
};
static shared_ptr<DiagnosticMessage>
Jump_target_cannot_cross_function_boundary() {
  return diag(1107, DiagnosticCategory::Error,
              "Jump_target_cannot_cross_function_boundary_1107",
              "Jump target cannot cross function boundary.");
};
static shared_ptr<DiagnosticMessage>
A_return_statement_can_only_be_used_within_a_function_body() {
  return diag(1108, DiagnosticCategory::Error,
              "A_return_statement_can_only_be_used_within_a_function_body_1108",
              "A 'return' statement can only be used within a function body.");
};
static shared_ptr<DiagnosticMessage> Expression_expected() {
  return diag(1109, DiagnosticCategory::Error, "Expression_expected_1109",
              "Expression expected.");
};
static shared_ptr<DiagnosticMessage> Type_expected() {
  return diag(1110, DiagnosticCategory::Error, "Type_expected_1110",
              "Type expected.");
};
static shared_ptr<DiagnosticMessage>
A_default_clause_cannot_appear_more_than_once_in_a_switch_statement() {
  return diag(1113, DiagnosticCategory::Error,
              "A_default_clause_cannot_appear_more_than_once_in_a_switch_"
              "statement_1113",
              "A 'default' clause cannot appear more than once in a 'switch' "
              "statement.");
};
static shared_ptr<DiagnosticMessage> Duplicate_label_0() {
  return diag(1114, DiagnosticCategory::Error, "Duplicate_label_0_1114",
              "Duplicate label '{0}'.");
};
static shared_ptr<DiagnosticMessage>
A_continue_statement_can_only_jump_to_a_label_of_an_enclosing_iteration_statement() {
  return diag(1115, DiagnosticCategory::Error,
              "A_continue_statement_can_only_jump_to_a_label_of_an_enclosing_"
              "iteration_statement_1115",
              "A 'continue' statement can only jump to a label of an enclosing "
              "iteration statement.");
};
static shared_ptr<DiagnosticMessage>
A_break_statement_can_only_jump_to_a_label_of_an_enclosing_statement() {
  return diag(1116, DiagnosticCategory::Error,
              "A_break_statement_can_only_jump_to_a_label_of_an_enclosing_"
              "statement_1116",
              "A 'break' statement can only jump to a label of an enclosing "
              "statement.");
};
static shared_ptr<DiagnosticMessage>
An_object_literal_cannot_have_multiple_properties_with_the_same_name_in_strict_mode() {
  return diag(1117, DiagnosticCategory::Error,
              "An_object_literal_cannot_have_multiple_properties_with_the_same_"
              "name_in_strict_mode_1117",
              "An object literal cannot have multiple properties with the same "
              "name in strict mode.");
};
static shared_ptr<DiagnosticMessage>
An_object_literal_cannot_have_multiple_get_Slashset_accessors_with_the_same_name() {
  return diag(1118, DiagnosticCategory::Error,
              "An_object_literal_cannot_have_multiple_get_Slashset_accessors_"
              "with_the_same_name_1118",
              "An object literal cannot have multiple get/set accessors with "
              "the same name.");
};
static shared_ptr<DiagnosticMessage>
An_object_literal_cannot_have_property_and_accessor_with_the_same_name() {
  return diag(1119, DiagnosticCategory::Error,
              "An_object_literal_cannot_have_property_and_accessor_with_the_"
              "same_name_1119",
              "An object literal cannot have property and accessor with the "
              "same name.");
};
static shared_ptr<DiagnosticMessage>
An_export_assignment_cannot_have_modifiers() {
  return diag(1120, DiagnosticCategory::Error,
              "An_export_assignment_cannot_have_modifiers_1120",
              "An export assignment cannot have modifiers.");
};
static shared_ptr<DiagnosticMessage>
Octal_literals_are_not_allowed_in_strict_mode() {
  return diag(1121, DiagnosticCategory::Error,
              "Octal_literals_are_not_allowed_in_strict_mode_1121",
              "Octal literals are not allowed in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Variable_declaration_list_cannot_be_empty() {
  return diag(1123, DiagnosticCategory::Error,
              "Variable_declaration_list_cannot_be_empty_1123",
              "Variable declaration list cannot be empty.");
};
static shared_ptr<DiagnosticMessage> Digit_expected() {
  return diag(1124, DiagnosticCategory::Error, "Digit_expected_1124",
              "Digit expected.");
};
static shared_ptr<DiagnosticMessage> Hexadecimal_digit_expected() {
  return diag(1125, DiagnosticCategory::Error,
              "Hexadecimal_digit_expected_1125", "Hexadecimal digit expected.");
};
static shared_ptr<DiagnosticMessage> Unexpected_end_of_text() {
  return diag(1126, DiagnosticCategory::Error, "Unexpected_end_of_text_1126",
              "Unexpected end of text.");
};
static shared_ptr<DiagnosticMessage> Invalid_character() {
  return diag(1127, DiagnosticCategory::Error, "Invalid_character_1127",
              "Invalid character.");
};
static shared_ptr<DiagnosticMessage> Declaration_or_statement_expected() {
  return diag(1128, DiagnosticCategory::Error,
              "Declaration_or_statement_expected_1128",
              "Declaration or statement expected.");
};
static shared_ptr<DiagnosticMessage> Statement_expected() {
  return diag(1129, DiagnosticCategory::Error, "Statement_expected_1129",
              "Statement expected.");
};
static shared_ptr<DiagnosticMessage> case_or_default_expected() {
  return diag(1130, DiagnosticCategory::Error, "case_or_default_expected_1130",
              "'case' or 'default' expected.");
};
static shared_ptr<DiagnosticMessage> Property_or_signature_expected() {
  return diag(1131, DiagnosticCategory::Error,
              "Property_or_signature_expected_1131",
              "Property or signature expected.");
};
static shared_ptr<DiagnosticMessage> Enum_member_expected() {
  return diag(1132, DiagnosticCategory::Error, "Enum_member_expected_1132",
              "Enum member expected.");
};
static shared_ptr<DiagnosticMessage> Variable_declaration_expected() {
  return diag(1134, DiagnosticCategory::Error,
              "Variable_declaration_expected_1134",
              "Variable declaration expected.");
};
static shared_ptr<DiagnosticMessage> Argument_expression_expected() {
  return diag(1135, DiagnosticCategory::Error,
              "Argument_expression_expected_1135",
              "Argument expression expected.");
};
static shared_ptr<DiagnosticMessage> Property_assignment_expected() {
  return diag(1136, DiagnosticCategory::Error,
              "Property_assignment_expected_1136",
              "Property assignment expected.");
};
static shared_ptr<DiagnosticMessage> Expression_or_comma_expected() {
  return diag(1137, DiagnosticCategory::Error,
              "Expression_or_comma_expected_1137",
              "Expression or comma expected.");
};
static shared_ptr<DiagnosticMessage> Parameter_declaration_expected() {
  return diag(1138, DiagnosticCategory::Error,
              "Parameter_declaration_expected_1138",
              "Parameter declaration expected.");
};
static shared_ptr<DiagnosticMessage> Type_parameter_declaration_expected() {
  return diag(1139, DiagnosticCategory::Error,
              "Type_parameter_declaration_expected_1139",
              "Type parameter declaration expected.");
};
static shared_ptr<DiagnosticMessage> Type_argument_expected() {
  return diag(1140, DiagnosticCategory::Error, "Type_argument_expected_1140",
              "Type argument expected.");
};
static shared_ptr<DiagnosticMessage> String_literal_expected() {
  return diag(1141, DiagnosticCategory::Error, "String_literal_expected_1141",
              "String literal expected.");
};
static shared_ptr<DiagnosticMessage> Line_break_not_permitted_here() {
  return diag(1142, DiagnosticCategory::Error,
              "Line_break_not_permitted_here_1142",
              "Line break not permitted here.");
};
static shared_ptr<DiagnosticMessage> or_expected() {
  return diag(1144, DiagnosticCategory::Error, "or_expected_1144",
              "'{' or ';' expected.");
};
static shared_ptr<DiagnosticMessage> or_JSX_element_expected() {
  return diag(1145, DiagnosticCategory::Error, "or_JSX_element_expected_1145",
              "{' or JSX element expected.");
};
static shared_ptr<DiagnosticMessage> Declaration_expected() {
  return diag(1146, DiagnosticCategory::Error, "Declaration_expected_1146",
              "Declaration expected.");
};
static shared_ptr<DiagnosticMessage>
Import_declarations_in_a_namespace_cannot_reference_a_module() {
  return diag(
      1147, DiagnosticCategory::Error,
      "Import_declarations_in_a_namespace_cannot_reference_a_module_1147",
      "Import declarations in a namespace cannot reference a module.");
};
static shared_ptr<DiagnosticMessage>
Cannot_use_imports_exports_or_module_augmentations_when_module_is_none() {
  return diag(1148, DiagnosticCategory::Error,
              "Cannot_use_imports_exports_or_module_augmentations_when_module_"
              "is_none_1148",
              "Cannot use imports, exports, or module augmentations when "
              "'--module' is 'none'.");
};
static shared_ptr<DiagnosticMessage>
File_name_0_differs_from_already_included_file_name_1_only_in_casing() {
  return diag(1149, DiagnosticCategory::Error,
              "File_name_0_differs_from_already_included_file_name_1_only_in_"
              "casing_1149",
              "File name '{0}' differs from already included file name '{1}' "
              "only in casing.");
};
static shared_ptr<DiagnosticMessage> const_declarations_must_be_initialized() {
  return diag(1155, DiagnosticCategory::Error,
              "const_declarations_must_be_initialized_1155",
              "'const' declarations must be initialized.");
};
static shared_ptr<DiagnosticMessage>
const_declarations_can_only_be_declared_inside_a_block() {
  return diag(1156, DiagnosticCategory::Error,
              "const_declarations_can_only_be_declared_inside_a_block_1156",
              "'const' declarations can only be declared inside a block.");
};
static shared_ptr<DiagnosticMessage>
let_declarations_can_only_be_declared_inside_a_block() {
  return diag(1157, DiagnosticCategory::Error,
              "let_declarations_can_only_be_declared_inside_a_block_1157",
              "'let' declarations can only be declared inside a block.");
};
static shared_ptr<DiagnosticMessage> Unterminated_template_literal() {
  return diag(1160, DiagnosticCategory::Error,
              "Unterminated_template_literal_1160",
              "Unterminated template literal.");
};
static shared_ptr<DiagnosticMessage> Unterminated_regular_expression_literal() {
  return diag(1161, DiagnosticCategory::Error,
              "Unterminated_regular_expression_literal_1161",
              "Unterminated regular expression literal.");
};
static shared_ptr<DiagnosticMessage>
An_object_member_cannot_be_declared_optional() {
  return diag(1162, DiagnosticCategory::Error,
              "An_object_member_cannot_be_declared_optional_1162",
              "An object member cannot be declared optional.");
};
static shared_ptr<DiagnosticMessage>
A_yield_expression_is_only_allowed_in_a_generator_body() {
  return diag(1163, DiagnosticCategory::Error,
              "A_yield_expression_is_only_allowed_in_a_generator_body_1163",
              "A 'yield' expression is only allowed in a generator body.");
};
static shared_ptr<DiagnosticMessage>
Computed_property_names_are_not_allowed_in_enums() {
  return diag(1164, DiagnosticCategory::Error,
              "Computed_property_names_are_not_allowed_in_enums_1164",
              "Computed property names are not allowed in enums.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_in_an_ambient_context_must_refer_to_an_expression_whose_type_is_a_literal_type_or_a_unique_symbol_type() {
  return diag(
      1165, DiagnosticCategory::Error,
      "A_computed_property_name_in_an_ambient_context_must_refer_to_an_"
      "expression_whose_type_is_a_literal_t_1165",
      "A computed property name in an ambient context must refer to an "
      "expression whose type is a literal type or a 'unique symbol' type.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_in_a_class_property_declaration_must_have_a_simple_literal_type_or_a_unique_symbol_type() {
  return diag(1166, DiagnosticCategory::Error,
              "A_computed_property_name_in_a_class_property_declaration_must_"
              "have_a_simple_literal_type_or_a_unique_1166",
              "A computed property name in a class property declaration must "
              "have a simple literal type or a 'unique symbol' type.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_in_a_method_overload_must_refer_to_an_expression_whose_type_is_a_literal_type_or_a_unique_symbol_type() {
  return diag(
      1168, DiagnosticCategory::Error,
      "A_computed_property_name_in_a_method_overload_must_refer_to_an_"
      "expression_whose_type_is_a_literal_ty_1168",
      "A computed property name in a method overload must refer to an "
      "expression whose type is a literal type or a 'unique symbol' type.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_in_an_interface_must_refer_to_an_expression_whose_type_is_a_literal_type_or_a_unique_symbol_type() {
  return diag(
      1169, DiagnosticCategory::Error,
      "A_computed_property_name_in_an_interface_must_refer_to_an_expression_"
      "whose_type_is_a_literal_type_or_1169",
      "A computed property name in an interface must refer to an expression "
      "whose type is a literal type or a 'unique symbol' type.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_in_a_type_literal_must_refer_to_an_expression_whose_type_is_a_literal_type_or_a_unique_symbol_type() {
  return diag(
      1170, DiagnosticCategory::Error,
      "A_computed_property_name_in_a_type_literal_must_refer_to_an_expression_"
      "whose_type_is_a_literal_type__1170",
      "A computed property name in a type literal must refer to an expression "
      "whose type is a literal type or a 'unique symbol' type.");
};
static shared_ptr<DiagnosticMessage>
A_comma_expression_is_not_allowed_in_a_computed_property_name() {
  return diag(
      1171, DiagnosticCategory::Error,
      "A_comma_expression_is_not_allowed_in_a_computed_property_name_1171",
      "A comma expression is not allowed in a computed property name.");
};
static shared_ptr<DiagnosticMessage> extends_clause_already_seen() {
  return diag(1172, DiagnosticCategory::Error,
              "extends_clause_already_seen_1172",
              "'extends' clause already seen.");
};
static shared_ptr<DiagnosticMessage>
extends_clause_must_precede_implements_clause() {
  return diag(1173, DiagnosticCategory::Error,
              "extends_clause_must_precede_implements_clause_1173",
              "'extends' clause must precede 'implements' clause.");
};
static shared_ptr<DiagnosticMessage> Classes_can_only_extend_a_single_class() {
  return diag(1174, DiagnosticCategory::Error,
              "Classes_can_only_extend_a_single_class_1174",
              "Classes can only extend a single class.");
};
static shared_ptr<DiagnosticMessage> implements_clause_already_seen() {
  return diag(1175, DiagnosticCategory::Error,
              "implements_clause_already_seen_1175",
              "'implements' clause already seen.");
};
static shared_ptr<DiagnosticMessage>
Interface_declaration_cannot_have_implements_clause() {
  return diag(1176, DiagnosticCategory::Error,
              "Interface_declaration_cannot_have_implements_clause_1176",
              "Interface declaration cannot have 'implements' clause.");
};
static shared_ptr<DiagnosticMessage> Binary_digit_expected() {
  return diag(1177, DiagnosticCategory::Error, "Binary_digit_expected_1177",
              "Binary digit expected.");
};
static shared_ptr<DiagnosticMessage> Octal_digit_expected() {
  return diag(1178, DiagnosticCategory::Error, "Octal_digit_expected_1178",
              "Octal digit expected.");
};
static shared_ptr<DiagnosticMessage> Unexpected_token_expected() {
  return diag(1179, DiagnosticCategory::Error, "Unexpected_token_expected_1179",
              "Unexpected token. '{' expected.");
};
static shared_ptr<DiagnosticMessage> Property_destructuring_pattern_expected() {
  return diag(1180, DiagnosticCategory::Error,
              "Property_destructuring_pattern_expected_1180",
              "Property destructuring pattern expected.");
};
static shared_ptr<DiagnosticMessage>
Array_element_destructuring_pattern_expected() {
  return diag(1181, DiagnosticCategory::Error,
              "Array_element_destructuring_pattern_expected_1181",
              "Array element destructuring pattern expected.");
};
static shared_ptr<DiagnosticMessage>
A_destructuring_declaration_must_have_an_initializer() {
  return diag(1182, DiagnosticCategory::Error,
              "A_destructuring_declaration_must_have_an_initializer_1182",
              "A destructuring declaration must have an initializer.");
};
static shared_ptr<DiagnosticMessage>
An_implementation_cannot_be_declared_in_ambient_contexts() {
  return diag(1183, DiagnosticCategory::Error,
              "An_implementation_cannot_be_declared_in_ambient_contexts_1183",
              "An implementation cannot be declared in ambient contexts.");
};
static shared_ptr<DiagnosticMessage> Modifiers_cannot_appear_here() {
  return diag(1184, DiagnosticCategory::Error,
              "Modifiers_cannot_appear_here_1184",
              "Modifiers cannot appear here.");
};
static shared_ptr<DiagnosticMessage> Merge_conflict_marker_encountered() {
  return diag(1185, DiagnosticCategory::Error,
              "Merge_conflict_marker_encountered_1185",
              "Merge conflict marker encountered.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_cannot_have_an_initializer() {
  return diag(1186, DiagnosticCategory::Error,
              "A_rest_element_cannot_have_an_initializer_1186",
              "A rest element cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
A_parameter_property_may_not_be_declared_using_a_binding_pattern() {
  return diag(
      1187, DiagnosticCategory::Error,
      "A_parameter_property_may_not_be_declared_using_a_binding_pattern_1187",
      "A parameter property may not be declared using a binding pattern.");
};
static shared_ptr<DiagnosticMessage>
Only_a_single_variable_declaration_is_allowed_in_a_for_of_statement() {
  return diag(1188, DiagnosticCategory::Error,
              "Only_a_single_variable_declaration_is_allowed_in_a_for_of_"
              "statement_1188",
              "Only a single variable declaration is allowed in a 'for...of' "
              "statement.");
};
static shared_ptr<DiagnosticMessage>
The_variable_declaration_of_a_for_in_statement_cannot_have_an_initializer() {
  return diag(1189, DiagnosticCategory::Error,
              "The_variable_declaration_of_a_for_in_statement_cannot_have_an_"
              "initializer_1189",
              "The variable declaration of a 'for...in' statement cannot have "
              "an initializer.");
};
static shared_ptr<DiagnosticMessage>
The_variable_declaration_of_a_for_of_statement_cannot_have_an_initializer() {
  return diag(1190, DiagnosticCategory::Error,
              "The_variable_declaration_of_a_for_of_statement_cannot_have_an_"
              "initializer_1190",
              "The variable declaration of a 'for...of' statement cannot have "
              "an initializer.");
};
static shared_ptr<DiagnosticMessage>
An_import_declaration_cannot_have_modifiers() {
  return diag(1191, DiagnosticCategory::Error,
              "An_import_declaration_cannot_have_modifiers_1191",
              "An import declaration cannot have modifiers.");
};
static shared_ptr<DiagnosticMessage> Module_0_has_no_default_export() {
  return diag(1192, DiagnosticCategory::Error,
              "Module_0_has_no_default_export_1192",
              "Module '{0}' has no default export.");
};
static shared_ptr<DiagnosticMessage>
An_export_declaration_cannot_have_modifiers() {
  return diag(1193, DiagnosticCategory::Error,
              "An_export_declaration_cannot_have_modifiers_1193",
              "An export declaration cannot have modifiers.");
};
static shared_ptr<DiagnosticMessage>
Export_declarations_are_not_permitted_in_a_namespace() {
  return diag(1194, DiagnosticCategory::Error,
              "Export_declarations_are_not_permitted_in_a_namespace_1194",
              "Export declarations are not permitted in a namespace.");
};
static shared_ptr<DiagnosticMessage>
export_Asterisk_does_not_re_export_a_default() {
  return diag(1195, DiagnosticCategory::Error,
              "export_Asterisk_does_not_re_export_a_default_1195",
              "'export *' does not re-export a default.");
};
static shared_ptr<DiagnosticMessage>
Catch_clause_variable_type_annotation_must_be_any_or_unknown_if_specified() {
  return diag(1196, DiagnosticCategory::Error,
              "Catch_clause_variable_type_annotation_must_be_any_or_unknown_if_"
              "specified_1196",
              "Catch clause variable type annotation must be 'any' or "
              "'unknown' if specified.");
};
static shared_ptr<DiagnosticMessage>
Catch_clause_variable_cannot_have_an_initializer() {
  return diag(1197, DiagnosticCategory::Error,
              "Catch_clause_variable_cannot_have_an_initializer_1197",
              "Catch clause variable cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
An_extended_Unicode_escape_value_must_be_between_0x0_and_0x10FFFF_inclusive() {
  return diag(1198, DiagnosticCategory::Error,
              "An_extended_Unicode_escape_value_must_be_between_0x0_and_"
              "0x10FFFF_inclusive_1198",
              "An extended Unicode escape value must be between 0x0 and "
              "0x10FFFF inclusive.");
};
static shared_ptr<DiagnosticMessage> Unterminated_Unicode_escape_sequence() {
  return diag(1199, DiagnosticCategory::Error,
              "Unterminated_Unicode_escape_sequence_1199",
              "Unterminated Unicode escape sequence.");
};
static shared_ptr<DiagnosticMessage>
Line_terminator_not_permitted_before_arrow() {
  return diag(1200, DiagnosticCategory::Error,
              "Line_terminator_not_permitted_before_arrow_1200",
              "Line terminator not permitted before arrow.");
};
static shared_ptr<DiagnosticMessage>
Import_assignment_cannot_be_used_when_targeting_ECMAScript_modules_Consider_using_import_Asterisk_as_ns_from_mod_import_a_from_mod_import_d_from_mod_or_another_module_format_instead() {
  return diag(
      1202, DiagnosticCategory::Error,
      "Import_assignment_cannot_be_used_when_targeting_ECMAScript_modules_"
      "Consider_using_import_Asterisk_as_1202",
      "Import assignment cannot be used when targeting ECMAScript modules. "
      "Consider using 'import * as ns from \"mod\"', 'import {a} from "
      "\"mod\"', 'import d from \"mod\"', or another module format instead.");
};
static shared_ptr<DiagnosticMessage>
Export_assignment_cannot_be_used_when_targeting_ECMAScript_modules_Consider_using_export_default_or_another_module_format_instead() {
  return diag(
      1203, DiagnosticCategory::Error,
      "Export_assignment_cannot_be_used_when_targeting_ECMAScript_modules_"
      "Consider_using_export_default_or__1203",
      "Export assignment cannot be used when targeting ECMAScript modules. "
      "Consider using 'export default' or another module format instead.");
};
static shared_ptr<DiagnosticMessage>
Re_exporting_a_type_when_the_isolatedModules_flag_is_provided_requires_using_export_type() {
  return diag(1205, DiagnosticCategory::Error,
              "Re_exporting_a_type_when_the_isolatedModules_flag_is_provided_"
              "requires_using_export_type_1205",
              "Re-exporting a type when the '--isolatedModules' flag is "
              "provided requires using 'export type'.");
};
static shared_ptr<DiagnosticMessage> Decorators_are_not_valid_here() {
  return diag(1206, DiagnosticCategory::Error,
              "Decorators_are_not_valid_here_1206",
              "Decorators are not valid here.");
};
static shared_ptr<DiagnosticMessage>
Decorators_cannot_be_applied_to_multiple_get_Slashset_accessors_of_the_same_name() {
  return diag(1207, DiagnosticCategory::Error,
              "Decorators_cannot_be_applied_to_multiple_get_Slashset_accessors_"
              "of_the_same_name_1207",
              "Decorators cannot be applied to multiple get/set accessors of "
              "the same name.");
};
static shared_ptr<DiagnosticMessage>
_0_cannot_be_compiled_under_isolatedModules_because_it_is_considered_a_global_script_file_Add_an_import_export_or_an_empty_export_statement_to_make_it_a_module() {
  return diag(1208, DiagnosticCategory::Error,
              "_0_cannot_be_compiled_under_isolatedModules_because_it_is_"
              "considered_a_global_script_file_Add_an_imp_1208",
              "'{0}' cannot be compiled under '--isolatedModules' because it "
              "is considered a global script file. Add an import, export, or "
              "an empty 'export {}' statement to make it a module.");
};
static shared_ptr<DiagnosticMessage>
Code_contained_in_a_class_is_evaluated_in_JavaScript_s_strict_mode_which_does_not_allow_this_use_of_0_For_more_information_see_https_Colon_Slash_Slashdeveloper_mozilla_org_Slashen_US_Slashdocs_SlashWeb_SlashJavaScript_SlashReference_SlashStrict_mode() {
  return diag(
      1210, DiagnosticCategory::Error,
      "Code_contained_in_a_class_is_evaluated_in_JavaScript_s_strict_mode_"
      "which_does_not_allow_this_use_of__1210",
      "Code contained in a class is evaluated in JavaScript's strict mode "
      "which does not allow this use of '{0}'. For more information, see "
      "https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/"
      "Strict_mode.");
};
static shared_ptr<DiagnosticMessage>
A_class_declaration_without_the_default_modifier_must_have_a_name() {
  return diag(
      1211, DiagnosticCategory::Error,
      "A_class_declaration_without_the_default_modifier_must_have_a_name_1211",
      "A class declaration without the 'default' modifier must have a name.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_0_is_a_reserved_word_in_strict_mode() {
  return diag(1212, DiagnosticCategory::Error,
              "Identifier_expected_0_is_a_reserved_word_in_strict_mode_1212",
              "Identifier expected. '{0}' is a reserved word in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_0_is_a_reserved_word_in_strict_mode_Class_definitions_are_automatically_in_strict_mode() {
  return diag(1213, DiagnosticCategory::Error,
              "Identifier_expected_0_is_a_reserved_word_in_strict_mode_Class_"
              "definitions_are_automatically_in_stric_1213",
              "Identifier expected. '{0}' is a reserved word in strict mode. "
              "Class definitions are automatically in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_0_is_a_reserved_word_in_strict_mode_Modules_are_automatically_in_strict_mode() {
  return diag(1214, DiagnosticCategory::Error,
              "Identifier_expected_0_is_a_reserved_word_in_strict_mode_Modules_"
              "are_automatically_in_strict_mode_1214",
              "Identifier expected. '{0}' is a reserved word in strict mode. "
              "Modules are automatically in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Invalid_use_of_0_Modules_are_automatically_in_strict_mode() {
  return diag(
      1215, DiagnosticCategory::Error,
      "Invalid_use_of_0_Modules_are_automatically_in_strict_mode_1215",
      "Invalid use of '{0}'. Modules are automatically in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_esModule_is_reserved_as_an_exported_marker_when_transforming_ECMAScript_modules() {
  return diag(1216, DiagnosticCategory::Error,
              "Identifier_expected_esModule_is_reserved_as_an_exported_marker_"
              "when_transforming_ECMAScript_modules_1216",
              "Identifier expected. '__esModule' is reserved as an exported "
              "marker when transforming ECMAScript modules.");
};
static shared_ptr<DiagnosticMessage>
Export_assignment_is_not_supported_when_module_flag_is_system() {
  return diag(
      1218, DiagnosticCategory::Error,
      "Export_assignment_is_not_supported_when_module_flag_is_system_1218",
      "Export assignment is not supported when '--module' flag is 'system'.");
};
static shared_ptr<DiagnosticMessage>
Experimental_support_for_decorators_is_a_feature_that_is_subject_to_change_in_a_future_release_Set_the_experimentalDecorators_option_in_your_tsconfig_or_jsconfig_to_remove_this_warning() {
  return diag(
      1219, DiagnosticCategory::Error,
      "Experimental_support_for_decorators_is_a_feature_that_is_subject_to_"
      "change_in_a_future_release_Set_t_1219",
      "Experimental support for decorators is a feature that is subject to "
      "change in a future release. Set the 'experimentalDecorators' option in "
      "your 'tsconfig' or 'jsconfig' to remove this warning.");
};
static shared_ptr<DiagnosticMessage>
Generators_are_not_allowed_in_an_ambient_context() {
  return diag(1221, DiagnosticCategory::Error,
              "Generators_are_not_allowed_in_an_ambient_context_1221",
              "Generators are not allowed in an ambient context.");
};
static shared_ptr<DiagnosticMessage>
An_overload_signature_cannot_be_declared_as_a_generator() {
  return diag(1222, DiagnosticCategory::Error,
              "An_overload_signature_cannot_be_declared_as_a_generator_1222",
              "An overload signature cannot be declared as a generator.");
};
static shared_ptr<DiagnosticMessage> _0_tag_already_specified() {
  return diag(1223, DiagnosticCategory::Error, "_0_tag_already_specified_1223",
              "'{0}' tag already specified.");
};
static shared_ptr<DiagnosticMessage> Signature_0_must_be_a_type_predicate() {
  return diag(1224, DiagnosticCategory::Error,
              "Signature_0_must_be_a_type_predicate_1224",
              "Signature '{0}' must be a type predicate.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_parameter_0() {
  return diag(1225, DiagnosticCategory::Error, "Cannot_find_parameter_0_1225",
              "Cannot find parameter '{0}'.");
};
static shared_ptr<DiagnosticMessage> Type_predicate_0_is_not_assignable_to_1() {
  return diag(1226, DiagnosticCategory::Error,
              "Type_predicate_0_is_not_assignable_to_1_1226",
              "Type predicate '{0}' is not assignable to '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_is_not_in_the_same_position_as_parameter_1() {
  return diag(
      1227, DiagnosticCategory::Error,
      "Parameter_0_is_not_in_the_same_position_as_parameter_1_1227",
      "Parameter '{0}' is not in the same position as parameter '{1}'.");
};
static shared_ptr<DiagnosticMessage>
A_type_predicate_is_only_allowed_in_return_type_position_for_functions_and_methods() {
  return diag(1228, DiagnosticCategory::Error,
              "A_type_predicate_is_only_allowed_in_return_type_position_for_"
              "functions_and_methods_1228",
              "A type predicate is only allowed in return type position for "
              "functions and methods.");
};
static shared_ptr<DiagnosticMessage>
A_type_predicate_cannot_reference_a_rest_parameter() {
  return diag(1229, DiagnosticCategory::Error,
              "A_type_predicate_cannot_reference_a_rest_parameter_1229",
              "A type predicate cannot reference a rest parameter.");
};
static shared_ptr<DiagnosticMessage>
A_type_predicate_cannot_reference_element_0_in_a_binding_pattern() {
  return diag(
      1230, DiagnosticCategory::Error,
      "A_type_predicate_cannot_reference_element_0_in_a_binding_pattern_1230",
      "A type predicate cannot reference element '{0}' in a binding pattern.");
};
static shared_ptr<DiagnosticMessage>
An_export_assignment_must_be_at_the_top_level_of_a_file_or_module_declaration() {
  return diag(1231, DiagnosticCategory::Error,
              "An_export_assignment_must_be_at_the_top_level_of_a_file_or_"
              "module_declaration_1231",
              "An export assignment must be at the top level of a file or "
              "module declaration.");
};
static shared_ptr<DiagnosticMessage>
An_import_declaration_can_only_be_used_in_a_namespace_or_module() {
  return diag(
      1232, DiagnosticCategory::Error,
      "An_import_declaration_can_only_be_used_in_a_namespace_or_module_1232",
      "An import declaration can only be used in a namespace or module.");
};
static shared_ptr<DiagnosticMessage>
An_export_declaration_can_only_be_used_in_a_module() {
  return diag(1233, DiagnosticCategory::Error,
              "An_export_declaration_can_only_be_used_in_a_module_1233",
              "An export declaration can only be used in a module.");
};
static shared_ptr<DiagnosticMessage>
An_ambient_module_declaration_is_only_allowed_at_the_top_level_in_a_file() {
  return diag(1234, DiagnosticCategory::Error,
              "An_ambient_module_declaration_is_only_allowed_at_the_top_level_"
              "in_a_file_1234",
              "An ambient module declaration is only allowed at the top level "
              "in a file.");
};
static shared_ptr<DiagnosticMessage>
A_namespace_declaration_is_only_allowed_in_a_namespace_or_module() {
  return diag(
      1235, DiagnosticCategory::Error,
      "A_namespace_declaration_is_only_allowed_in_a_namespace_or_module_1235",
      "A namespace declaration is only allowed in a namespace or module.");
};
static shared_ptr<DiagnosticMessage>
The_return_type_of_a_property_decorator_function_must_be_either_void_or_any() {
  return diag(1236, DiagnosticCategory::Error,
              "The_return_type_of_a_property_decorator_function_must_be_either_"
              "void_or_any_1236",
              "The return type of a property decorator function must be either "
              "'void' or 'any'.");
};
static shared_ptr<DiagnosticMessage>
The_return_type_of_a_parameter_decorator_function_must_be_either_void_or_any() {
  return diag(1237, DiagnosticCategory::Error,
              "The_return_type_of_a_parameter_decorator_function_must_be_"
              "either_void_or_any_1237",
              "The return type of a parameter decorator function must be "
              "either 'void' or 'any'.");
};
static shared_ptr<DiagnosticMessage>
Unable_to_resolve_signature_of_class_decorator_when_called_as_an_expression() {
  return diag(1238, DiagnosticCategory::Error,
              "Unable_to_resolve_signature_of_class_decorator_when_called_as_"
              "an_expression_1238",
              "Unable to resolve signature of class decorator when called as "
              "an expression.");
};
static shared_ptr<DiagnosticMessage>
Unable_to_resolve_signature_of_parameter_decorator_when_called_as_an_expression() {
  return diag(1239, DiagnosticCategory::Error,
              "Unable_to_resolve_signature_of_parameter_decorator_when_called_"
              "as_an_expression_1239",
              "Unable to resolve signature of parameter decorator when called "
              "as an expression.");
};
static shared_ptr<DiagnosticMessage>
Unable_to_resolve_signature_of_property_decorator_when_called_as_an_expression() {
  return diag(1240, DiagnosticCategory::Error,
              "Unable_to_resolve_signature_of_property_decorator_when_called_"
              "as_an_expression_1240",
              "Unable to resolve signature of property decorator when called "
              "as an expression.");
};
static shared_ptr<DiagnosticMessage>
Unable_to_resolve_signature_of_method_decorator_when_called_as_an_expression() {
  return diag(1241, DiagnosticCategory::Error,
              "Unable_to_resolve_signature_of_method_decorator_when_called_as_"
              "an_expression_1241",
              "Unable to resolve signature of method decorator when called as "
              "an expression.");
};
static shared_ptr<DiagnosticMessage>
abstract_modifier_can_only_appear_on_a_class_method_or_property_declaration() {
  return diag(1242, DiagnosticCategory::Error,
              "abstract_modifier_can_only_appear_on_a_class_method_or_property_"
              "declaration_1242",
              "'abstract' modifier can only appear on a class, method, or "
              "property declaration.");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_be_used_with_1_modifier() {
  return diag(1243, DiagnosticCategory::Error,
              "_0_modifier_cannot_be_used_with_1_modifier_1243",
              "'{0}' modifier cannot be used with '{1}' modifier.");
};
static shared_ptr<DiagnosticMessage>
Abstract_methods_can_only_appear_within_an_abstract_class() {
  return diag(1244, DiagnosticCategory::Error,
              "Abstract_methods_can_only_appear_within_an_abstract_class_1244",
              "Abstract methods can only appear within an abstract class.");
};
static shared_ptr<DiagnosticMessage>
Method_0_cannot_have_an_implementation_because_it_is_marked_abstract() {
  return diag(1245, DiagnosticCategory::Error,
              "Method_0_cannot_have_an_implementation_because_it_is_marked_"
              "abstract_1245",
              "Method '{0}' cannot have an implementation because it is marked "
              "abstract.");
};
static shared_ptr<DiagnosticMessage>
An_interface_property_cannot_have_an_initializer() {
  return diag(1246, DiagnosticCategory::Error,
              "An_interface_property_cannot_have_an_initializer_1246",
              "An interface property cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
A_type_literal_property_cannot_have_an_initializer() {
  return diag(1247, DiagnosticCategory::Error,
              "A_type_literal_property_cannot_have_an_initializer_1247",
              "A type literal property cannot have an initializer.");
};
static shared_ptr<DiagnosticMessage>
A_class_member_cannot_have_the_0_keyword() {
  return diag(1248, DiagnosticCategory::Error,
              "A_class_member_cannot_have_the_0_keyword_1248",
              "A class member cannot have the '{0}' keyword.");
};
static shared_ptr<DiagnosticMessage>
A_decorator_can_only_decorate_a_method_implementation_not_an_overload() {
  return diag(1249, DiagnosticCategory::Error,
              "A_decorator_can_only_decorate_a_method_implementation_not_an_"
              "overload_1249",
              "A decorator can only decorate a method implementation, not an "
              "overload.");
};
static shared_ptr<DiagnosticMessage>
Function_declarations_are_not_allowed_inside_blocks_in_strict_mode_when_targeting_ES3_or_ES5() {
  return diag(1250, DiagnosticCategory::Error,
              "Function_declarations_are_not_allowed_inside_blocks_in_strict_"
              "mode_when_targeting_ES3_or_ES5_1250",
              "Function declarations are not allowed inside blocks in strict "
              "mode when targeting 'ES3' or 'ES5'.");
};
static shared_ptr<DiagnosticMessage>
Function_declarations_are_not_allowed_inside_blocks_in_strict_mode_when_targeting_ES3_or_ES5_Class_definitions_are_automatically_in_strict_mode() {
  return diag(1251, DiagnosticCategory::Error,
              "Function_declarations_are_not_allowed_inside_blocks_in_strict_"
              "mode_when_targeting_ES3_or_ES5_Class_d_1251",
              "Function declarations are not allowed inside blocks in strict "
              "mode when targeting 'ES3' or 'ES5'. Class definitions are "
              "automatically in strict mode.");
};
static shared_ptr<DiagnosticMessage>
Function_declarations_are_not_allowed_inside_blocks_in_strict_mode_when_targeting_ES3_or_ES5_Modules_are_automatically_in_strict_mode() {
  return diag(
      1252, DiagnosticCategory::Error,
      "Function_declarations_are_not_allowed_inside_blocks_in_strict_mode_when_"
      "targeting_ES3_or_ES5_Modules_1252",
      "Function declarations are not allowed inside blocks in strict mode when "
      "targeting 'ES3' or 'ES5'. Modules are automatically in strict mode.");
};
static shared_ptr<DiagnosticMessage>
A_const_initializer_in_an_ambient_context_must_be_a_string_or_numeric_literal_or_literal_enum_reference() {
  return diag(1254, DiagnosticCategory::Error,
              "A_const_initializer_in_an_ambient_context_must_be_a_string_or_"
              "numeric_literal_or_literal_enum_refere_1254",
              "A 'const' initializer in an ambient context must be a string or "
              "numeric literal or literal enum reference.");
};
static shared_ptr<DiagnosticMessage>
A_definite_assignment_assertion_is_not_permitted_in_this_context() {
  return diag(
      1255, DiagnosticCategory::Error,
      "A_definite_assignment_assertion_is_not_permitted_in_this_context_1255",
      "A definite assignment assertion '!' is not permitted in this context.");
};
static shared_ptr<DiagnosticMessage>
A_required_element_cannot_follow_an_optional_element() {
  return diag(1257, DiagnosticCategory::Error,
              "A_required_element_cannot_follow_an_optional_element_1257",
              "A required element cannot follow an optional element.");
};
static shared_ptr<DiagnosticMessage>
A_default_export_must_be_at_the_top_level_of_a_file_or_module_declaration() {
  return diag(1258, DiagnosticCategory::Error,
              "A_default_export_must_be_at_the_top_level_of_a_file_or_module_"
              "declaration_1258",
              "A default export must be at the top level of a file or module "
              "declaration.");
};
static shared_ptr<DiagnosticMessage>
Module_0_can_only_be_default_imported_using_the_1_flag() {
  return diag(1259, DiagnosticCategory::Error,
              "Module_0_can_only_be_default_imported_using_the_1_flag_1259",
              "Module '{0}' can only be default-imported using the '{1}' flag");
};
static shared_ptr<DiagnosticMessage>
Keywords_cannot_contain_escape_characters() {
  return diag(1260, DiagnosticCategory::Error,
              "Keywords_cannot_contain_escape_characters_1260",
              "Keywords cannot contain escape characters.");
};
static shared_ptr<DiagnosticMessage>
Already_included_file_name_0_differs_from_file_name_1_only_in_casing() {
  return diag(1261, DiagnosticCategory::Error,
              "Already_included_file_name_0_differs_from_file_name_1_only_in_"
              "casing_1261",
              "Already included file name '{0}' differs from file name '{1}' "
              "only in casing.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_0_is_a_reserved_word_at_the_top_level_of_a_module() {
  return diag(1262, DiagnosticCategory::Error,
              "Identifier_expected_0_is_a_reserved_word_at_the_top_level_of_a_"
              "module_1262",
              "Identifier expected. '{0}' is a reserved word at the top-level "
              "of a module.");
};
static shared_ptr<DiagnosticMessage>
Declarations_with_initializers_cannot_also_have_definite_assignment_assertions() {
  return diag(1263, DiagnosticCategory::Error,
              "Declarations_with_initializers_cannot_also_have_definite_"
              "assignment_assertions_1263",
              "Declarations with initializers cannot also have definite "
              "assignment assertions.");
};
static shared_ptr<DiagnosticMessage>
Declarations_with_definite_assignment_assertions_must_also_have_type_annotations() {
  return diag(1264, DiagnosticCategory::Error,
              "Declarations_with_definite_assignment_assertions_must_also_have_"
              "type_annotations_1264",
              "Declarations with definite assignment assertions must also have "
              "type annotations.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_cannot_follow_another_rest_element() {
  return diag(1265, DiagnosticCategory::Error,
              "A_rest_element_cannot_follow_another_rest_element_1265",
              "A rest element cannot follow another rest element.");
};
static shared_ptr<DiagnosticMessage>
An_optional_element_cannot_follow_a_rest_element() {
  return diag(1266, DiagnosticCategory::Error,
              "An_optional_element_cannot_follow_a_rest_element_1266",
              "An optional element cannot follow a rest element.");
};
static shared_ptr<DiagnosticMessage>
Property_0_cannot_have_an_initializer_because_it_is_marked_abstract() {
  return diag(1267, DiagnosticCategory::Error,
              "Property_0_cannot_have_an_initializer_because_it_is_marked_"
              "abstract_1267",
              "Property '{0}' cannot have an initializer because it is marked "
              "abstract.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_type_must_be_string_number_symbol_or_a_template_literal_type() {
  return diag(1268, DiagnosticCategory::Error,
              "An_index_signature_parameter_type_must_be_string_number_symbol_"
              "or_a_template_literal_type_1268",
              "An index signature parameter type must be 'string', 'number', "
              "'symbol', or a template literal type.");
};
static shared_ptr<DiagnosticMessage>
with_statements_are_not_allowed_in_an_async_function_block() {
  return diag(1300, DiagnosticCategory::Error,
              "with_statements_are_not_allowed_in_an_async_function_block_1300",
              "'with' statements are not allowed in an async function block.");
};
static shared_ptr<DiagnosticMessage>
await_expressions_are_only_allowed_within_async_functions_and_at_the_top_levels_of_modules() {
  return diag(1308, DiagnosticCategory::Error,
              "await_expressions_are_only_allowed_within_async_functions_and_"
              "at_the_top_levels_of_modules_1308",
              "'await' expressions are only allowed within async functions and "
              "at the top levels of modules.");
};
static shared_ptr<DiagnosticMessage>
Did_you_mean_to_use_a_Colon_An_can_only_follow_a_property_name_when_the_containing_object_literal_is_part_of_a_destructuring_pattern() {
  return diag(
      1312, DiagnosticCategory::Error,
      "Did_you_mean_to_use_a_Colon_An_can_only_follow_a_property_name_when_the_"
      "containing_object_literal_is_1312",
      "Did you mean to use a ':'? An '=' can only follow a property name when "
      "the containing object literal is part of a destructuring pattern.");
};
static shared_ptr<DiagnosticMessage>
The_body_of_an_if_statement_cannot_be_the_empty_statement() {
  return diag(1313, DiagnosticCategory::Error,
              "The_body_of_an_if_statement_cannot_be_the_empty_statement_1313",
              "The body of an 'if' statement cannot be the empty statement.");
};
static shared_ptr<DiagnosticMessage>
Global_module_exports_may_only_appear_in_module_files() {
  return diag(1314, DiagnosticCategory::Error,
              "Global_module_exports_may_only_appear_in_module_files_1314",
              "Global module exports may only appear in module files.");
};
static shared_ptr<DiagnosticMessage>
Global_module_exports_may_only_appear_in_declaration_files() {
  return diag(1315, DiagnosticCategory::Error,
              "Global_module_exports_may_only_appear_in_declaration_files_1315",
              "Global module exports may only appear in declaration files.");
};
static shared_ptr<DiagnosticMessage>
Global_module_exports_may_only_appear_at_top_level() {
  return diag(1316, DiagnosticCategory::Error,
              "Global_module_exports_may_only_appear_at_top_level_1316",
              "Global module exports may only appear at top level.");
};
static shared_ptr<DiagnosticMessage>
A_parameter_property_cannot_be_declared_using_a_rest_parameter() {
  return diag(
      1317, DiagnosticCategory::Error,
      "A_parameter_property_cannot_be_declared_using_a_rest_parameter_1317",
      "A parameter property cannot be declared using a rest parameter.");
};
static shared_ptr<DiagnosticMessage>
An_abstract_accessor_cannot_have_an_implementation() {
  return diag(1318, DiagnosticCategory::Error,
              "An_abstract_accessor_cannot_have_an_implementation_1318",
              "An abstract accessor cannot have an implementation.");
};
static shared_ptr<DiagnosticMessage>
A_default_export_can_only_be_used_in_an_ECMAScript_style_module() {
  return diag(
      1319, DiagnosticCategory::Error,
      "A_default_export_can_only_be_used_in_an_ECMAScript_style_module_1319",
      "A default export can only be used in an ECMAScript-style module.");
};
static shared_ptr<DiagnosticMessage>
Type_of_await_operand_must_either_be_a_valid_promise_or_must_not_contain_a_callable_then_member() {
  return diag(1320, DiagnosticCategory::Error,
              "Type_of_await_operand_must_either_be_a_valid_promise_or_must_"
              "not_contain_a_callable_then_member_1320",
              "Type of 'await' operand must either be a valid promise or must "
              "not contain a callable 'then' member.");
};
static shared_ptr<DiagnosticMessage>
Type_of_yield_operand_in_an_async_generator_must_either_be_a_valid_promise_or_must_not_contain_a_callable_then_member() {
  return diag(1321, DiagnosticCategory::Error,
              "Type_of_yield_operand_in_an_async_generator_must_either_be_a_"
              "valid_promise_or_must_not_contain_a_cal_1321",
              "Type of 'yield' operand in an async generator must either be a "
              "valid promise or must not contain a callable 'then' member.");
};
static shared_ptr<DiagnosticMessage>
Type_of_iterated_elements_of_a_yield_Asterisk_operand_must_either_be_a_valid_promise_or_must_not_contain_a_callable_then_member() {
  return diag(1322, DiagnosticCategory::Error,
              "Type_of_iterated_elements_of_a_yield_Asterisk_operand_must_"
              "either_be_a_valid_promise_or_must_not_con_1322",
              "Type of iterated elements of a 'yield*' operand must either be "
              "a valid promise or must not contain a callable 'then' member.");
};
static shared_ptr<DiagnosticMessage>
Dynamic_imports_are_only_supported_when_the_module_flag_is_set_to_es2020_es2022_esnext_commonjs_amd_system_umd_node12_or_nodenext() {
  return diag(1323, DiagnosticCategory::Error,
              "Dynamic_imports_are_only_supported_when_the_module_flag_is_set_"
              "to_es2020_es2022_esnext_commonjs_amd__1323",
              "Dynamic imports are only supported when the '--module' flag is "
              "set to 'es2020', 'es2022', 'esnext', 'commonjs', 'amd', "
              "'system', 'umd', 'node12', or 'nodenext'.");
};
static shared_ptr<DiagnosticMessage>
Dynamic_imports_only_support_a_second_argument_when_the_module_option_is_set_to_esnext_or_nodenext() {
  return diag(1324, DiagnosticCategory::Error,
              "Dynamic_imports_only_support_a_second_argument_when_the_module_"
              "option_is_set_to_esnext_or_nodenext_1324",
              "Dynamic imports only support a second argument when the "
              "'--module' option is set to 'esnext' or 'nodenext'.");
};
static shared_ptr<DiagnosticMessage>
Argument_of_dynamic_import_cannot_be_spread_element() {
  return diag(1325, DiagnosticCategory::Error,
              "Argument_of_dynamic_import_cannot_be_spread_element_1325",
              "Argument of dynamic import cannot be spread element.");
};
static shared_ptr<DiagnosticMessage>
Dynamic_import_cannot_have_type_arguments() {
  return diag(1326, DiagnosticCategory::Error,
              "Dynamic_import_cannot_have_type_arguments_1326",
              "Dynamic import cannot have type arguments.");
};
static shared_ptr<DiagnosticMessage>
String_literal_with_double_quotes_expected() {
  return diag(1327, DiagnosticCategory::Error,
              "String_literal_with_double_quotes_expected_1327",
              "String literal with double quotes expected.");
};
static shared_ptr<DiagnosticMessage>
Property_value_can_only_be_string_literal_numeric_literal_true_false_null_object_literal_or_array_literal() {
  return diag(1328, DiagnosticCategory::Error,
              "Property_value_can_only_be_string_literal_numeric_literal_true_"
              "false_null_object_literal_or_array_li_1328",
              "Property value can only be string literal, numeric literal, "
              "'true', 'false', 'null', object literal or array literal.");
};
static shared_ptr<DiagnosticMessage>
_0_accepts_too_few_arguments_to_be_used_as_a_decorator_here_Did_you_mean_to_call_it_first_and_write_0() {
  return diag(1329, DiagnosticCategory::Error,
              "_0_accepts_too_few_arguments_to_be_used_as_a_decorator_here_Did_"
              "you_mean_to_call_it_first_and_write__1329",
              "'{0}' accepts too few arguments to be used as a decorator here. "
              "Did you mean to call it first and write '@{0}()'?");
};
static shared_ptr<DiagnosticMessage>
A_property_of_an_interface_or_type_literal_whose_type_is_a_unique_symbol_type_must_be_readonly() {
  return diag(1330, DiagnosticCategory::Error,
              "A_property_of_an_interface_or_type_literal_whose_type_is_a_"
              "unique_symbol_type_must_be_readonly_1330",
              "A property of an interface or type literal whose type is a "
              "'unique symbol' type must be 'readonly'.");
};
static shared_ptr<DiagnosticMessage>
A_property_of_a_class_whose_type_is_a_unique_symbol_type_must_be_both_static_and_readonly() {
  return diag(1331, DiagnosticCategory::Error,
              "A_property_of_a_class_whose_type_is_a_unique_symbol_type_must_"
              "be_both_static_and_readonly_1331",
              "A property of a class whose type is a 'unique symbol' type must "
              "be both 'static' and 'readonly'.");
};
static shared_ptr<DiagnosticMessage>
A_variable_whose_type_is_a_unique_symbol_type_must_be_const() {
  return diag(
      1332, DiagnosticCategory::Error,
      "A_variable_whose_type_is_a_unique_symbol_type_must_be_const_1332",
      "A variable whose type is a 'unique symbol' type must be 'const'.");
};
static shared_ptr<DiagnosticMessage>
unique_symbol_types_may_not_be_used_on_a_variable_declaration_with_a_binding_name() {
  return diag(1333, DiagnosticCategory::Error,
              "unique_symbol_types_may_not_be_used_on_a_variable_declaration_"
              "with_a_binding_name_1333",
              "'unique symbol' types may not be used on a variable declaration "
              "with a binding name.");
};
static shared_ptr<DiagnosticMessage>
unique_symbol_types_are_only_allowed_on_variables_in_a_variable_statement() {
  return diag(1334, DiagnosticCategory::Error,
              "unique_symbol_types_are_only_allowed_on_variables_in_a_variable_"
              "statement_1334",
              "'unique symbol' types are only allowed on variables in a "
              "variable statement.");
};
static shared_ptr<DiagnosticMessage>
unique_symbol_types_are_not_allowed_here() {
  return diag(1335, DiagnosticCategory::Error,
              "unique_symbol_types_are_not_allowed_here_1335",
              "'unique symbol' types are not allowed here.");
};
static shared_ptr<DiagnosticMessage>
An_index_signature_parameter_type_cannot_be_a_literal_type_or_generic_type_Consider_using_a_mapped_object_type_instead() {
  return diag(1337, DiagnosticCategory::Error,
              "An_index_signature_parameter_type_cannot_be_a_literal_type_or_"
              "generic_type_Consider_using_a_mapped_o_1337",
              "An index signature parameter type cannot be a literal type or "
              "generic type. Consider using a mapped object type instead.");
};
static shared_ptr<DiagnosticMessage>
infer_declarations_are_only_permitted_in_the_extends_clause_of_a_conditional_type() {
  return diag(1338, DiagnosticCategory::Error,
              "infer_declarations_are_only_permitted_in_the_extends_clause_of_"
              "a_conditional_type_1338",
              "'infer' declarations are only permitted in the 'extends' clause "
              "of a conditional type.");
};
static shared_ptr<DiagnosticMessage>
Module_0_does_not_refer_to_a_value_but_is_used_as_a_value_here() {
  return diag(
      1339, DiagnosticCategory::Error,
      "Module_0_does_not_refer_to_a_value_but_is_used_as_a_value_here_1339",
      "Module '{0}' does not refer to a value, but is used as a value here.");
};
static shared_ptr<DiagnosticMessage>
Module_0_does_not_refer_to_a_type_but_is_used_as_a_type_here_Did_you_mean_typeof_import_0() {
  return diag(1340, DiagnosticCategory::Error,
              "Module_0_does_not_refer_to_a_type_but_is_used_as_a_type_here_"
              "Did_you_mean_typeof_import_0_1340",
              "Module '{0}' does not refer to a type, but is used as a type "
              "here. Did you mean 'typeof import('{0}')'?");
};
static shared_ptr<DiagnosticMessage> Type_arguments_cannot_be_used_here() {
  return diag(1342, DiagnosticCategory::Error,
              "Type_arguments_cannot_be_used_here_1342",
              "Type arguments cannot be used here.");
};
static shared_ptr<DiagnosticMessage>
The_import_meta_meta_property_is_only_allowed_when_the_module_option_is_es2020_es2022_esnext_system_node12_or_nodenext() {
  return diag(1343, DiagnosticCategory::Error,
              "The_import_meta_meta_property_is_only_allowed_when_the_module_"
              "option_is_es2020_es2022_esnext_system__1343",
              "The 'import.meta' meta-property is only allowed when the "
              "'--module' option is 'es2020', 'es2022', 'esnext', 'system', "
              "'node12', or 'nodenext'.");
};
static shared_ptr<DiagnosticMessage> A_label_is_not_allowed_here() {
  return diag(1344, DiagnosticCategory::Error,
              "A_label_is_not_allowed_here_1344",
              "'A label is not allowed here.");
};
static shared_ptr<DiagnosticMessage>
An_expression_of_type_void_cannot_be_tested_for_truthiness() {
  return diag(1345, DiagnosticCategory::Error,
              "An_expression_of_type_void_cannot_be_tested_for_truthiness_1345",
              "An expression of type 'void' cannot be tested for truthiness.");
};
static shared_ptr<DiagnosticMessage>
This_parameter_is_not_allowed_with_use_strict_directive() {
  return diag(1346, DiagnosticCategory::Error,
              "This_parameter_is_not_allowed_with_use_strict_directive_1346",
              "This parameter is not allowed with 'use strict' directive.");
};
static shared_ptr<DiagnosticMessage>
use_strict_directive_cannot_be_used_with_non_simple_parameter_list() {
  return diag(
      1347, DiagnosticCategory::Error,
      "use_strict_directive_cannot_be_used_with_non_simple_parameter_list_1347",
      "'use strict' directive cannot be used with non-simple parameter list.");
};
static shared_ptr<DiagnosticMessage> Non_simple_parameter_declared_here() {
  return diag(1348, DiagnosticCategory::Error,
              "Non_simple_parameter_declared_here_1348",
              "Non-simple parameter declared here.");
};
static shared_ptr<DiagnosticMessage> use_strict_directive_used_here() {
  return diag(1349, DiagnosticCategory::Error,
              "use_strict_directive_used_here_1349",
              "'use strict' directive used here.");
};
static shared_ptr<DiagnosticMessage>
Print_the_final_configuration_instead_of_building() {
  return diag(1350, DiagnosticCategory::Message,
              "Print_the_final_configuration_instead_of_building_1350",
              "Print the final configuration instead of building.");
};
static shared_ptr<DiagnosticMessage>
An_identifier_or_keyword_cannot_immediately_follow_a_numeric_literal() {
  return diag(
      1351, DiagnosticCategory::Error,
      "An_identifier_or_keyword_cannot_immediately_follow_a_numeric_literal_"
      "1351",
      "An identifier or keyword cannot immediately follow a numeric literal.");
};
static shared_ptr<DiagnosticMessage>
A_bigint_literal_cannot_use_exponential_notation() {
  return diag(1352, DiagnosticCategory::Error,
              "A_bigint_literal_cannot_use_exponential_notation_1352",
              "A bigint literal cannot use exponential notation.");
};
static shared_ptr<DiagnosticMessage> A_bigint_literal_must_be_an_integer() {
  return diag(1353, DiagnosticCategory::Error,
              "A_bigint_literal_must_be_an_integer_1353",
              "A bigint literal must be an integer.");
};
static shared_ptr<DiagnosticMessage>
readonly_type_modifier_is_only_permitted_on_array_and_tuple_literal_types() {
  return diag(1354, DiagnosticCategory::Error,
              "readonly_type_modifier_is_only_permitted_on_array_and_tuple_"
              "literal_types_1354",
              "'readonly' type modifier is only permitted on array and tuple "
              "literal types.");
};
static shared_ptr<DiagnosticMessage>
A_const_assertions_can_only_be_applied_to_references_to_enum_members_or_string_number_boolean_array_or_object_literals() {
  return diag(
      1355, DiagnosticCategory::Error,
      "A_const_assertions_can_only_be_applied_to_references_to_enum_members_or_"
      "string_number_boolean_array__1355",
      "A 'const' assertions can only be applied to references to enum members, "
      "or string, number, boolean, array, or object literals.");
};
static shared_ptr<DiagnosticMessage>
Did_you_mean_to_mark_this_function_as_async() {
  return diag(1356, DiagnosticCategory::Error,
              "Did_you_mean_to_mark_this_function_as_async_1356",
              "Did you mean to mark this function as 'async'?");
};
static shared_ptr<DiagnosticMessage>
An_enum_member_name_must_be_followed_by_a_or() {
  return diag(1357, DiagnosticCategory::Error,
              "An_enum_member_name_must_be_followed_by_a_or_1357",
              "An enum member name must be followed by a ',', '=', or '}'.");
};
static shared_ptr<DiagnosticMessage>
Tagged_template_expressions_are_not_permitted_in_an_optional_chain() {
  return diag(
      1358, DiagnosticCategory::Error,
      "Tagged_template_expressions_are_not_permitted_in_an_optional_chain_1358",
      "Tagged template expressions are not permitted in an optional chain.");
};
static shared_ptr<DiagnosticMessage>
Identifier_expected_0_is_a_reserved_word_that_cannot_be_used_here() {
  return diag(
      1359, DiagnosticCategory::Error,
      "Identifier_expected_0_is_a_reserved_word_that_cannot_be_used_here_1359",
      "Identifier expected. '{0}' is a reserved word that cannot be used "
      "here.");
};
static shared_ptr<DiagnosticMessage>
_0_cannot_be_used_as_a_value_because_it_was_imported_using_import_type() {
  return diag(1361, DiagnosticCategory::Error,
              "_0_cannot_be_used_as_a_value_because_it_was_imported_using_"
              "import_type_1361",
              "'{0}' cannot be used as a value because it was imported using "
              "'import type'.");
};
static shared_ptr<DiagnosticMessage>
_0_cannot_be_used_as_a_value_because_it_was_exported_using_export_type() {
  return diag(1362, DiagnosticCategory::Error,
              "_0_cannot_be_used_as_a_value_because_it_was_exported_using_"
              "export_type_1362",
              "'{0}' cannot be used as a value because it was exported using "
              "'export type'.");
};
static shared_ptr<DiagnosticMessage>
A_type_only_import_can_specify_a_default_import_or_named_bindings_but_not_both() {
  return diag(1363, DiagnosticCategory::Error,
              "A_type_only_import_can_specify_a_default_import_or_named_"
              "bindings_but_not_both_1363",
              "A type-only import can specify a default import or named "
              "bindings, but not both.");
};
static shared_ptr<DiagnosticMessage> Convert_to_type_only_export() {
  return diag(1364, DiagnosticCategory::Message,
              "Convert_to_type_only_export_1364",
              "Convert to type-only export");
};
static shared_ptr<DiagnosticMessage>
Convert_all_re_exported_types_to_type_only_exports() {
  return diag(1365, DiagnosticCategory::Message,
              "Convert_all_re_exported_types_to_type_only_exports_1365",
              "Convert all re-exported types to type-only exports");
};
static shared_ptr<DiagnosticMessage>
Split_into_two_separate_import_declarations() {
  return diag(1366, DiagnosticCategory::Message,
              "Split_into_two_separate_import_declarations_1366",
              "Split into two separate import declarations");
};
static shared_ptr<DiagnosticMessage> Split_all_invalid_type_only_imports() {
  return diag(1367, DiagnosticCategory::Message,
              "Split_all_invalid_type_only_imports_1367",
              "Split all invalid type-only imports");
};
static shared_ptr<DiagnosticMessage> Did_you_mean_0() {
  return diag(1369, DiagnosticCategory::Message, "Did_you_mean_0_1369",
              "Did you mean '{0}'?");
};
static shared_ptr<DiagnosticMessage>
This_import_is_never_used_as_a_value_and_must_use_import_type_because_importsNotUsedAsValues_is_set_to_error() {
  return diag(1371, DiagnosticCategory::Error,
              "This_import_is_never_used_as_a_value_and_must_use_import_type_"
              "because_importsNotUsedAsValues_is_set__1371",
              "This import is never used as a value and must use 'import type' "
              "because 'importsNotUsedAsValues' is set to 'error'.");
};
static shared_ptr<DiagnosticMessage> Convert_to_type_only_import() {
  return diag(1373, DiagnosticCategory::Message,
              "Convert_to_type_only_import_1373",
              "Convert to type-only import");
};
static shared_ptr<DiagnosticMessage>
Convert_all_imports_not_used_as_a_value_to_type_only_imports() {
  return diag(
      1374, DiagnosticCategory::Message,
      "Convert_all_imports_not_used_as_a_value_to_type_only_imports_1374",
      "Convert all imports not used as a value to type-only imports");
};
static shared_ptr<DiagnosticMessage>
await_expressions_are_only_allowed_at_the_top_level_of_a_file_when_that_file_is_a_module_but_this_file_has_no_imports_or_exports_Consider_adding_an_empty_export_to_make_this_file_a_module() {
  return diag(
      1375, DiagnosticCategory::Error,
      "await_expressions_are_only_allowed_at_the_top_level_of_a_file_when_that_"
      "file_is_a_module_but_this_fi_1375",
      "'await' expressions are only allowed at the top level of a file when "
      "that file is a module, but this file has no imports or exports. "
      "Consider adding an empty 'export {}' to make this file a module.");
};
static shared_ptr<DiagnosticMessage> _0_was_imported_here() {
  return diag(1376, DiagnosticCategory::Message, "_0_was_imported_here_1376",
              "'{0}' was imported here.");
};
static shared_ptr<DiagnosticMessage> _0_was_exported_here() {
  return diag(1377, DiagnosticCategory::Message, "_0_was_exported_here_1377",
              "'{0}' was exported here.");
};
static shared_ptr<DiagnosticMessage>
Top_level_await_expressions_are_only_allowed_when_the_module_option_is_set_to_es2022_esnext_system_or_nodenext_and_the_target_option_is_set_to_es2017_or_higher() {
  return diag(
      1378, DiagnosticCategory::Error,
      "Top_level_await_expressions_are_only_allowed_when_the_module_option_is_"
      "set_to_es2022_esnext_system_o_1378",
      "Top-level 'await' expressions are only allowed when the 'module' option "
      "is set to 'es2022', 'esnext', 'system', or 'nodenext', and the 'target' "
      "option is set to 'es2017' or higher.");
};
static shared_ptr<DiagnosticMessage>
An_import_alias_cannot_reference_a_declaration_that_was_exported_using_export_type() {
  return diag(1379, DiagnosticCategory::Error,
              "An_import_alias_cannot_reference_a_declaration_that_was_"
              "exported_using_export_type_1379",
              "An import alias cannot reference a declaration that was "
              "exported using 'export type'.");
};
static shared_ptr<DiagnosticMessage>
An_import_alias_cannot_reference_a_declaration_that_was_imported_using_import_type() {
  return diag(1380, DiagnosticCategory::Error,
              "An_import_alias_cannot_reference_a_declaration_that_was_"
              "imported_using_import_type_1380",
              "An import alias cannot reference a declaration that was "
              "imported using 'import type'.");
};
static shared_ptr<DiagnosticMessage> Unexpected_token_Did_you_mean_or_rbrace() {
  return diag(1381, DiagnosticCategory::Error,
              "Unexpected_token_Did_you_mean_or_rbrace_1381",
              "Unexpected token. Did you mean `{'}'}` or `&rbrace;`?");
};
static shared_ptr<DiagnosticMessage> Unexpected_token_Did_you_mean_or_gt() {
  return diag(1382, DiagnosticCategory::Error,
              "Unexpected_token_Did_you_mean_or_gt_1382",
              "Unexpected token. Did you mean `{'>'}` or `&gt;`?");
};
static shared_ptr<DiagnosticMessage> Only_named_exports_may_use_export_type() {
  return diag(1383, DiagnosticCategory::Error,
              "Only_named_exports_may_use_export_type_1383",
              "Only named exports may use 'export type'.");
};
static shared_ptr<DiagnosticMessage>
A_new_expression_with_type_arguments_must_always_be_followed_by_a_parenthesized_argument_list() {
  return diag(1384, DiagnosticCategory::Error,
              "A_new_expression_with_type_arguments_must_always_be_followed_by_"
              "a_parenthesized_argument_list_1384",
              "A 'new' expression with type arguments must always be followed "
              "by a parenthesized argument list.");
};
static shared_ptr<DiagnosticMessage>
Function_type_notation_must_be_parenthesized_when_used_in_a_union_type() {
  return diag(1385, DiagnosticCategory::Error,
              "Function_type_notation_must_be_parenthesized_when_used_in_a_"
              "union_type_1385",
              "Function type notation must be parenthesized when used in a "
              "union type.");
};
static shared_ptr<DiagnosticMessage>
Constructor_type_notation_must_be_parenthesized_when_used_in_a_union_type() {
  return diag(1386, DiagnosticCategory::Error,
              "Constructor_type_notation_must_be_parenthesized_when_used_in_a_"
              "union_type_1386",
              "Constructor type notation must be parenthesized when used in a "
              "union type.");
};
static shared_ptr<DiagnosticMessage>
Function_type_notation_must_be_parenthesized_when_used_in_an_intersection_type() {
  return diag(1387, DiagnosticCategory::Error,
              "Function_type_notation_must_be_parenthesized_when_used_in_an_"
              "intersection_type_1387",
              "Function type notation must be parenthesized when used in an "
              "intersection type.");
};
static shared_ptr<DiagnosticMessage>
Constructor_type_notation_must_be_parenthesized_when_used_in_an_intersection_type() {
  return diag(1388, DiagnosticCategory::Error,
              "Constructor_type_notation_must_be_parenthesized_when_used_in_an_"
              "intersection_type_1388",
              "Constructor type notation must be parenthesized when used in an "
              "intersection type.");
};
static shared_ptr<DiagnosticMessage>
_0_is_not_allowed_as_a_variable_declaration_name() {
  return diag(1389, DiagnosticCategory::Error,
              "_0_is_not_allowed_as_a_variable_declaration_name_1389",
              "'{0}' is not allowed as a variable declaration name.");
};
static shared_ptr<DiagnosticMessage> _0_is_not_allowed_as_a_parameter_name() {
  return diag(1390, DiagnosticCategory::Error,
              "_0_is_not_allowed_as_a_parameter_name_1390",
              "'{0}' is not allowed as a parameter name.");
};
static shared_ptr<DiagnosticMessage> An_import_alias_cannot_use_import_type() {
  return diag(1392, DiagnosticCategory::Error,
              "An_import_alias_cannot_use_import_type_1392",
              "An import alias cannot use 'import type'");
};
static shared_ptr<DiagnosticMessage> Imported_via_0_from_file_1() {
  return diag(1393, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_1393",
              "Imported via {0} from file '{1}'");
};
static shared_ptr<DiagnosticMessage>
Imported_via_0_from_file_1_with_packageId_2() {
  return diag(1394, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_with_packageId_2_1394",
              "Imported via {0} from file '{1}' with packageId '{2}'");
};
static shared_ptr<DiagnosticMessage>
Imported_via_0_from_file_1_to_import_importHelpers_as_specified_in_compilerOptions() {
  return diag(1395, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_to_import_importHelpers_as_specified_"
              "in_compilerOptions_1395",
              "Imported via {0} from file '{1}' to import 'importHelpers' as "
              "specified in compilerOptions");
};
static shared_ptr<DiagnosticMessage>
Imported_via_0_from_file_1_with_packageId_2_to_import_importHelpers_as_specified_in_compilerOptions() {
  return diag(1396, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_with_packageId_2_to_import_"
              "importHelpers_as_specified_in_compilerOptions_1396",
              "Imported via {0} from file '{1}' with packageId '{2}' to import "
              "'importHelpers' as specified in compilerOptions");
};
static shared_ptr<DiagnosticMessage>
Imported_via_0_from_file_1_to_import_jsx_and_jsxs_factory_functions() {
  return diag(1397, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_to_import_jsx_and_jsxs_factory_"
              "functions_1397",
              "Imported via {0} from file '{1}' to import 'jsx' and 'jsxs' "
              "factory functions");
};
static shared_ptr<DiagnosticMessage>
Imported_via_0_from_file_1_with_packageId_2_to_import_jsx_and_jsxs_factory_functions() {
  return diag(1398, DiagnosticCategory::Message,
              "Imported_via_0_from_file_1_with_packageId_2_to_import_jsx_and_"
              "jsxs_factory_functions_1398",
              "Imported via {0} from file '{1}' with packageId '{2}' to import "
              "'jsx' and 'jsxs' factory functions");
};
static shared_ptr<DiagnosticMessage> File_is_included_via_import_here() {
  return diag(1399, DiagnosticCategory::Message,
              "File_is_included_via_import_here_1399",
              "File is included via import here.");
};
static shared_ptr<DiagnosticMessage> Referenced_via_0_from_file_1() {
  return diag(1400, DiagnosticCategory::Message,
              "Referenced_via_0_from_file_1_1400",
              "Referenced via '{0}' from file '{1}'");
};
static shared_ptr<DiagnosticMessage> File_is_included_via_reference_here() {
  return diag(1401, DiagnosticCategory::Message,
              "File_is_included_via_reference_here_1401",
              "File is included via reference here.");
};
static shared_ptr<DiagnosticMessage>
Type_library_referenced_via_0_from_file_1() {
  return diag(1402, DiagnosticCategory::Message,
              "Type_library_referenced_via_0_from_file_1_1402",
              "Type library referenced via '{0}' from file '{1}'");
};
static shared_ptr<DiagnosticMessage>
Type_library_referenced_via_0_from_file_1_with_packageId_2() {
  return diag(
      1403, DiagnosticCategory::Message,
      "Type_library_referenced_via_0_from_file_1_with_packageId_2_1403",
      "Type library referenced via '{0}' from file '{1}' with packageId '{2}'");
};
static shared_ptr<DiagnosticMessage>
File_is_included_via_type_library_reference_here() {
  return diag(1404, DiagnosticCategory::Message,
              "File_is_included_via_type_library_reference_here_1404",
              "File is included via type library reference here.");
};
static shared_ptr<DiagnosticMessage> Library_referenced_via_0_from_file_1() {
  return diag(1405, DiagnosticCategory::Message,
              "Library_referenced_via_0_from_file_1_1405",
              "Library referenced via '{0}' from file '{1}'");
};
static shared_ptr<DiagnosticMessage>
File_is_included_via_library_reference_here() {
  return diag(1406, DiagnosticCategory::Message,
              "File_is_included_via_library_reference_here_1406",
              "File is included via library reference here.");
};
static shared_ptr<DiagnosticMessage> Matched_by_include_pattern_0_in_1() {
  return diag(1407, DiagnosticCategory::Message,
              "Matched_by_include_pattern_0_in_1_1407",
              "Matched by include pattern '{0}' in '{1}'");
};
static shared_ptr<DiagnosticMessage>
File_is_matched_by_include_pattern_specified_here() {
  return diag(1408, DiagnosticCategory::Message,
              "File_is_matched_by_include_pattern_specified_here_1408",
              "File is matched by include pattern specified here.");
};
static shared_ptr<DiagnosticMessage> Part_of_files_list_in_tsconfig_json() {
  return diag(1409, DiagnosticCategory::Message,
              "Part_of_files_list_in_tsconfig_json_1409",
              "Part of 'files' list in tsconfig.json");
};
static shared_ptr<DiagnosticMessage>
File_is_matched_by_files_list_specified_here() {
  return diag(1410, DiagnosticCategory::Message,
              "File_is_matched_by_files_list_specified_here_1410",
              "File is matched by 'files' list specified here.");
};
static shared_ptr<DiagnosticMessage>
Output_from_referenced_project_0_included_because_1_specified() {
  return diag(
      1411, DiagnosticCategory::Message,
      "Output_from_referenced_project_0_included_because_1_specified_1411",
      "Output from referenced project '{0}' included because '{1}' specified");
};
static shared_ptr<DiagnosticMessage>
Output_from_referenced_project_0_included_because_module_is_specified_as_none() {
  return diag(1412, DiagnosticCategory::Message,
              "Output_from_referenced_project_0_included_because_module_is_"
              "specified_as_none_1412",
              "Output from referenced project '{0}' included because "
              "'--module' is specified as 'none'");
};
static shared_ptr<DiagnosticMessage>
File_is_output_from_referenced_project_specified_here() {
  return diag(1413, DiagnosticCategory::Message,
              "File_is_output_from_referenced_project_specified_here_1413",
              "File is output from referenced project specified here.");
};
static shared_ptr<DiagnosticMessage>
Source_from_referenced_project_0_included_because_1_specified() {
  return diag(
      1414, DiagnosticCategory::Message,
      "Source_from_referenced_project_0_included_because_1_specified_1414",
      "Source from referenced project '{0}' included because '{1}' specified");
};
static shared_ptr<DiagnosticMessage>
Source_from_referenced_project_0_included_because_module_is_specified_as_none() {
  return diag(1415, DiagnosticCategory::Message,
              "Source_from_referenced_project_0_included_because_module_is_"
              "specified_as_none_1415",
              "Source from referenced project '{0}' included because "
              "'--module' is specified as 'none'");
};
static shared_ptr<DiagnosticMessage>
File_is_source_from_referenced_project_specified_here() {
  return diag(1416, DiagnosticCategory::Message,
              "File_is_source_from_referenced_project_specified_here_1416",
              "File is source from referenced project specified here.");
};
static shared_ptr<DiagnosticMessage>
Entry_point_of_type_library_0_specified_in_compilerOptions() {
  return diag(1417, DiagnosticCategory::Message,
              "Entry_point_of_type_library_0_specified_in_compilerOptions_1417",
              "Entry point of type library '{0}' specified in compilerOptions");
};
static shared_ptr<DiagnosticMessage>
Entry_point_of_type_library_0_specified_in_compilerOptions_with_packageId_1() {
  return diag(1418, DiagnosticCategory::Message,
              "Entry_point_of_type_library_0_specified_in_compilerOptions_with_"
              "packageId_1_1418",
              "Entry point of type library '{0}' specified in compilerOptions "
              "with packageId '{1}'");
};
static shared_ptr<DiagnosticMessage>
File_is_entry_point_of_type_library_specified_here() {
  return diag(1419, DiagnosticCategory::Message,
              "File_is_entry_point_of_type_library_specified_here_1419",
              "File is entry point of type library specified here.");
};
static shared_ptr<DiagnosticMessage> Entry_point_for_implicit_type_library_0() {
  return diag(1420, DiagnosticCategory::Message,
              "Entry_point_for_implicit_type_library_0_1420",
              "Entry point for implicit type library '{0}'");
};
static shared_ptr<DiagnosticMessage>
Entry_point_for_implicit_type_library_0_with_packageId_1() {
  return diag(
      1421, DiagnosticCategory::Message,
      "Entry_point_for_implicit_type_library_0_with_packageId_1_1421",
      "Entry point for implicit type library '{0}' with packageId '{1}'");
};
static shared_ptr<DiagnosticMessage> Library_0_specified_in_compilerOptions() {
  return diag(1422, DiagnosticCategory::Message,
              "Library_0_specified_in_compilerOptions_1422",
              "Library '{0}' specified in compilerOptions");
};
static shared_ptr<DiagnosticMessage> File_is_library_specified_here() {
  return diag(1423, DiagnosticCategory::Message,
              "File_is_library_specified_here_1423",
              "File is library specified here.");
};
static shared_ptr<DiagnosticMessage> Default_library() {
  return diag(1424, DiagnosticCategory::Message, "Default_library_1424",
              "Default library");
};
static shared_ptr<DiagnosticMessage> Default_library_for_target_0() {
  return diag(1425, DiagnosticCategory::Message,
              "Default_library_for_target_0_1425",
              "Default library for target '{0}'");
};
static shared_ptr<DiagnosticMessage>
File_is_default_library_for_target_specified_here() {
  return diag(1426, DiagnosticCategory::Message,
              "File_is_default_library_for_target_specified_here_1426",
              "File is default library for target specified here.");
};
static shared_ptr<DiagnosticMessage> Root_file_specified_for_compilation() {
  return diag(1427, DiagnosticCategory::Message,
              "Root_file_specified_for_compilation_1427",
              "Root file specified for compilation");
};
static shared_ptr<DiagnosticMessage>
File_is_output_of_project_reference_source_0() {
  return diag(1428, DiagnosticCategory::Message,
              "File_is_output_of_project_reference_source_0_1428",
              "File is output of project reference source '{0}'");
};
static shared_ptr<DiagnosticMessage> File_redirects_to_file_0() {
  return diag(1429, DiagnosticCategory::Message,
              "File_redirects_to_file_0_1429", "File redirects to file '{0}'");
};
static shared_ptr<DiagnosticMessage>
The_file_is_in_the_program_because_Colon() {
  return diag(1430, DiagnosticCategory::Message,
              "The_file_is_in_the_program_because_Colon_1430",
              "The file is in the program because:");
};
static shared_ptr<DiagnosticMessage>
for_await_loops_are_only_allowed_at_the_top_level_of_a_file_when_that_file_is_a_module_but_this_file_has_no_imports_or_exports_Consider_adding_an_empty_export_to_make_this_file_a_module() {
  return diag(
      1431, DiagnosticCategory::Error,
      "for_await_loops_are_only_allowed_at_the_top_level_of_a_file_when_that_"
      "file_is_a_module_but_this_file_1431",
      "'for await' loops are only allowed at the top level of a file when that "
      "file is a module, but this file has no imports or exports. Consider "
      "adding an empty 'export {}' to make this file a module.");
};
static shared_ptr<DiagnosticMessage>
Top_level_for_await_loops_are_only_allowed_when_the_module_option_is_set_to_es2022_esnext_system_or_nodenext_and_the_target_option_is_set_to_es2017_or_higher() {
  return diag(1432, DiagnosticCategory::Error,
              "Top_level_for_await_loops_are_only_allowed_when_the_module_"
              "option_is_set_to_es2022_esnext_system_or__1432",
              "Top-level 'for await' loops are only allowed when the 'module' "
              "option is set to 'es2022', 'esnext', 'system', or 'nodenext', "
              "and the 'target' option is set to 'es2017' or higher.");
};
static shared_ptr<DiagnosticMessage>
Decorators_may_not_be_applied_to_this_parameters() {
  return diag(1433, DiagnosticCategory::Error,
              "Decorators_may_not_be_applied_to_this_parameters_1433",
              "Decorators may not be applied to 'this' parameters.");
};
static shared_ptr<DiagnosticMessage> Unexpected_keyword_or_identifier() {
  return diag(1434, DiagnosticCategory::Error,
              "Unexpected_keyword_or_identifier_1434",
              "Unexpected keyword or identifier.");
};
static shared_ptr<DiagnosticMessage>
Unknown_keyword_or_identifier_Did_you_mean_0() {
  return diag(1435, DiagnosticCategory::Error,
              "Unknown_keyword_or_identifier_Did_you_mean_0_1435",
              "Unknown keyword or identifier. Did you mean '{0}'?");
};
static shared_ptr<DiagnosticMessage>
Decorators_must_precede_the_name_and_all_keywords_of_property_declarations() {
  return diag(1436, DiagnosticCategory::Error,
              "Decorators_must_precede_the_name_and_all_keywords_of_property_"
              "declarations_1436",
              "Decorators must precede the name and all keywords of property "
              "declarations.");
};
static shared_ptr<DiagnosticMessage> Namespace_must_be_given_a_name() {
  return diag(1437, DiagnosticCategory::Error,
              "Namespace_must_be_given_a_name_1437",
              "Namespace must be given a name.");
};
static shared_ptr<DiagnosticMessage> Interface_must_be_given_a_name() {
  return diag(1438, DiagnosticCategory::Error,
              "Interface_must_be_given_a_name_1438",
              "Interface must be given a name.");
};
static shared_ptr<DiagnosticMessage> Type_alias_must_be_given_a_name() {
  return diag(1439, DiagnosticCategory::Error,
              "Type_alias_must_be_given_a_name_1439",
              "Type alias must be given a name.");
};
static shared_ptr<DiagnosticMessage>
Variable_declaration_not_allowed_at_this_location() {
  return diag(1440, DiagnosticCategory::Error,
              "Variable_declaration_not_allowed_at_this_location_1440",
              "Variable declaration not allowed at this location.");
};
static shared_ptr<DiagnosticMessage>
Cannot_start_a_function_call_in_a_type_annotation() {
  return diag(1441, DiagnosticCategory::Error,
              "Cannot_start_a_function_call_in_a_type_annotation_1441",
              "Cannot start a function call in a type annotation.");
};
static shared_ptr<DiagnosticMessage> Expected_for_property_initializer() {
  return diag(1442, DiagnosticCategory::Error,
              "Expected_for_property_initializer_1442",
              "Expected '=' for property initializer.");
};
static shared_ptr<DiagnosticMessage>
Module_declaration_names_may_only_use_or_quoted_strings() {
  return diag(1443, DiagnosticCategory::Error,
              "Module_declaration_names_may_only_use_or_quoted_strings_1443",
              "Module declaration names may only use ' or \" quoted strings.");
};
static shared_ptr<DiagnosticMessage>
_0_is_a_type_and_must_be_imported_using_a_type_only_import_when_preserveValueImports_and_isolatedModules_are_both_enabled() {
  return diag(
      1444, DiagnosticCategory::Error,
      "_0_is_a_type_and_must_be_imported_using_a_type_only_import_when_"
      "preserveValueImports_and_isolatedMod_1444",
      "'{0}' is a type and must be imported using a type-only import when "
      "'preserveValueImports' and 'isolatedModules' are both enabled.");
};
static shared_ptr<DiagnosticMessage>
_0_resolves_to_a_type_only_declaration_and_must_be_imported_using_a_type_only_import_when_preserveValueImports_and_isolatedModules_are_both_enabled() {
  return diag(1446, DiagnosticCategory::Error,
              "_0_resolves_to_a_type_only_declaration_and_must_be_imported_"
              "using_a_type_only_import_when_preserveVa_1446",
              "'{0}' resolves to a type-only declaration and must be imported "
              "using a type-only import when 'preserveValueImports' and "
              "'isolatedModules' are both enabled.");
};
static shared_ptr<DiagnosticMessage>
_0_resolves_to_a_type_only_declaration_and_must_be_re_exported_using_a_type_only_re_export_when_isolatedModules_is_enabled() {
  return diag(
      1448, DiagnosticCategory::Error,
      "_0_resolves_to_a_type_only_declaration_and_must_be_re_exported_using_a_"
      "type_only_re_export_when_isol_1448",
      "'{0}' resolves to a type-only declaration and must be re-exported using "
      "a type-only re-export when 'isolatedModules' is enabled.");
};
static shared_ptr<DiagnosticMessage>
Preserve_unused_imported_values_in_the_JavaScript_output_that_would_otherwise_be_removed() {
  return diag(1449, DiagnosticCategory::Message,
              "Preserve_unused_imported_values_in_the_JavaScript_output_that_"
              "would_otherwise_be_removed_1449",
              "Preserve unused imported values in the JavaScript output that "
              "would otherwise be removed.");
};
static shared_ptr<DiagnosticMessage>
Dynamic_imports_can_only_accept_a_module_specifier_and_an_optional_assertion_as_arguments() {
  return diag(1450, DiagnosticCategory::Message,
              "Dynamic_imports_can_only_accept_a_module_specifier_and_an_"
              "optional_assertion_as_arguments_1450",
              "Dynamic imports can only accept a module specifier and an "
              "optional assertion as arguments");
};
static shared_ptr<DiagnosticMessage>
Private_identifiers_are_only_allowed_in_class_bodies_and_may_only_be_used_as_part_of_a_class_member_declaration_property_access_or_on_the_left_hand_side_of_an_in_expression() {
  return diag(1451, DiagnosticCategory::Error,
              "Private_identifiers_are_only_allowed_in_class_bodies_and_may_"
              "only_be_used_as_part_of_a_class_member__1451",
              "Private identifiers are only allowed in class bodies and may "
              "only be used as part of a class member declaration, property "
              "access, or on the left-hand-side of an 'in' expression");
};
static shared_ptr<DiagnosticMessage>
The_import_meta_meta_property_is_not_allowed_in_files_which_will_build_into_CommonJS_output() {
  return diag(1470, DiagnosticCategory::Error,
              "The_import_meta_meta_property_is_not_allowed_in_files_which_"
              "will_build_into_CommonJS_output_1470",
              "The 'import.meta' meta-property is not allowed in files which "
              "will build into CommonJS output.");
};
static shared_ptr<DiagnosticMessage>
Module_0_cannot_be_imported_using_this_construct_The_specifier_only_resolves_to_an_ES_module_which_cannot_be_imported_synchronously_Use_dynamic_import_instead() {
  return diag(1471, DiagnosticCategory::Error,
              "Module_0_cannot_be_imported_using_this_construct_The_specifier_"
              "only_resolves_to_an_ES_module_which_c_1471",
              "Module '{0}' cannot be imported using this construct. The "
              "specifier only resolves to an ES module, which cannot be "
              "imported synchronously. Use dynamic import instead.");
};
static shared_ptr<DiagnosticMessage>
The_types_of_0_are_incompatible_between_these_types() {
  return diag(2200, DiagnosticCategory::Error,
              "The_types_of_0_are_incompatible_between_these_types_2200",
              "The types of '{0}' are incompatible between these types.");
};
static shared_ptr<DiagnosticMessage>
The_types_returned_by_0_are_incompatible_between_these_types() {
  return diag(
      2201, DiagnosticCategory::Error,
      "The_types_returned_by_0_are_incompatible_between_these_types_2201",
      "The types returned by '{0}' are incompatible between these types.");
};
static shared_ptr<DiagnosticMessage>
Call_signature_return_types_0_and_1_are_incompatible() {
  return diag(2202, DiagnosticCategory::Error,
              "Call_signature_return_types_0_and_1_are_incompatible_2202",
              "Call signature return types '{0}' and '{1}' are incompatible.",
              /*reportsUnnecessary*/ false,
              /*elidedInCompatabilityPyramid*/ true);
};
static shared_ptr<DiagnosticMessage>
Construct_signature_return_types_0_and_1_are_incompatible() {
  return diag(
      2203, DiagnosticCategory::Error,
      "Construct_signature_return_types_0_and_1_are_incompatible_2203",
      "Construct signature return types '{0}' and '{1}' are incompatible.",
      /*reportsUnnecessary*/ false, /*elidedInCompatabilityPyramid*/ true);
};
static shared_ptr<DiagnosticMessage>
Call_signatures_with_no_arguments_have_incompatible_return_types_0_and_1() {
  return diag(2204, DiagnosticCategory::Error,
              "Call_signatures_with_no_arguments_have_incompatible_return_"
              "types_0_and_1_2204",
              "Call signatures with no arguments have incompatible return "
              "types '{0}' and '{1}'.",
              /*reportsUnnecessary*/ false,
              /*elidedInCompatabilityPyramid*/ true);
};
static shared_ptr<DiagnosticMessage>
Construct_signatures_with_no_arguments_have_incompatible_return_types_0_and_1() {
  return diag(2205, DiagnosticCategory::Error,
              "Construct_signatures_with_no_arguments_have_incompatible_return_"
              "types_0_and_1_2205",
              "Construct signatures with no arguments have incompatible return "
              "types '{0}' and '{1}'.",
              /*reportsUnnecessary*/ false,
              /*elidedInCompatabilityPyramid*/ true);
};
static shared_ptr<DiagnosticMessage>
The_type_modifier_cannot_be_used_on_a_named_import_when_import_type_is_used_on_its_import_statement() {
  return diag(2206, DiagnosticCategory::Error,
              "The_type_modifier_cannot_be_used_on_a_named_import_when_import_"
              "type_is_used_on_its_import_statement_2206",
              "The 'type' modifier cannot be used on a named import when "
              "'import type' is used on its import statement.");
};
static shared_ptr<DiagnosticMessage>
The_type_modifier_cannot_be_used_on_a_named_export_when_export_type_is_used_on_its_export_statement() {
  return diag(2207, DiagnosticCategory::Error,
              "The_type_modifier_cannot_be_used_on_a_named_export_when_export_"
              "type_is_used_on_its_export_statement_2207",
              "The 'type' modifier cannot be used on a named export when "
              "'export type' is used on its export statement.");
};
static shared_ptr<DiagnosticMessage> Duplicate_identifier_0() {
  return diag(2300, DiagnosticCategory::Error, "Duplicate_identifier_0_2300",
              "Duplicate identifier '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Initializer_of_instance_member_variable_0_cannot_reference_identifier_1_declared_in_the_constructor() {
  return diag(2301, DiagnosticCategory::Error,
              "Initializer_of_instance_member_variable_0_cannot_reference_"
              "identifier_1_declared_in_the_constructor_2301",
              "Initializer of instance member variable '{0}' cannot reference "
              "identifier '{1}' declared in the constructor.");
};
static shared_ptr<DiagnosticMessage>
Static_members_cannot_reference_class_type_parameters() {
  return diag(2302, DiagnosticCategory::Error,
              "Static_members_cannot_reference_class_type_parameters_2302",
              "Static members cannot reference class type parameters.");
};
static shared_ptr<DiagnosticMessage> Circular_definition_of_import_alias_0() {
  return diag(2303, DiagnosticCategory::Error,
              "Circular_definition_of_import_alias_0_2303",
              "Circular definition of import alias '{0}'.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_name_0() {
  return diag(2304, DiagnosticCategory::Error, "Cannot_find_name_0_2304",
              "Cannot find name '{0}'.");
};
static shared_ptr<DiagnosticMessage> Module_0_has_no_exported_member_1() {
  return diag(2305, DiagnosticCategory::Error,
              "Module_0_has_no_exported_member_1_2305",
              "Module '{0}' has no exported member '{1}'.");
};
static shared_ptr<DiagnosticMessage> File_0_is_not_a_module() {
  return diag(2306, DiagnosticCategory::Error, "File_0_is_not_a_module_2306",
              "File '{0}' is not a module.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_module_0_or_its_corresponding_type_declarations() {
  return diag(
      2307, DiagnosticCategory::Error,
      "Cannot_find_module_0_or_its_corresponding_type_declarations_2307",
      "Cannot find module '{0}' or its corresponding type declarations.");
};
static shared_ptr<DiagnosticMessage>
Module_0_has_already_exported_a_member_named_1_Consider_explicitly_re_exporting_to_resolve_the_ambiguity() {
  return diag(2308, DiagnosticCategory::Error,
              "Module_0_has_already_exported_a_member_named_1_Consider_"
              "explicitly_re_exporting_to_resolve_the_ambig_2308",
              "Module {0} has already exported a member named '{1}'. Consider "
              "explicitly re-exporting to resolve the ambiguity.");
};
static shared_ptr<DiagnosticMessage>
An_export_assignment_cannot_be_used_in_a_module_with_other_exported_elements() {
  return diag(2309, DiagnosticCategory::Error,
              "An_export_assignment_cannot_be_used_in_a_module_with_other_"
              "exported_elements_2309",
              "An export assignment cannot be used in a module with other "
              "exported elements.");
};
static shared_ptr<DiagnosticMessage>
Type_0_recursively_references_itself_as_a_base_type() {
  return diag(2310, DiagnosticCategory::Error,
              "Type_0_recursively_references_itself_as_a_base_type_2310",
              "Type '{0}' recursively references itself as a base type.");
};
static shared_ptr<DiagnosticMessage>
An_interface_can_only_extend_an_object_type_or_intersection_of_object_types_with_statically_known_members() {
  return diag(2312, DiagnosticCategory::Error,
              "An_interface_can_only_extend_an_object_type_or_intersection_of_"
              "object_types_with_statically_known_me_2312",
              "An interface can only extend an object type or intersection of "
              "object types with statically known members.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_has_a_circular_constraint() {
  return diag(2313, DiagnosticCategory::Error,
              "Type_parameter_0_has_a_circular_constraint_2313",
              "Type parameter '{0}' has a circular constraint.");
};
static shared_ptr<DiagnosticMessage>
Generic_type_0_requires_1_type_argument_s() {
  return diag(2314, DiagnosticCategory::Error,
              "Generic_type_0_requires_1_type_argument_s_2314",
              "Generic type '{0}' requires {1} type argument(s).");
};
static shared_ptr<DiagnosticMessage> Type_0_is_not_generic() {
  return diag(2315, DiagnosticCategory::Error, "Type_0_is_not_generic_2315",
              "Type '{0}' is not generic.");
};
static shared_ptr<DiagnosticMessage>
Global_type_0_must_be_a_class_or_interface_type() {
  return diag(2316, DiagnosticCategory::Error,
              "Global_type_0_must_be_a_class_or_interface_type_2316",
              "Global type '{0}' must be a class or interface type.");
};
static shared_ptr<DiagnosticMessage>
Global_type_0_must_have_1_type_parameter_s() {
  return diag(2317, DiagnosticCategory::Error,
              "Global_type_0_must_have_1_type_parameter_s_2317",
              "Global type '{0}' must have {1} type parameter(s).");
};
static shared_ptr<DiagnosticMessage> Cannot_find_global_type_0() {
  return diag(2318, DiagnosticCategory::Error, "Cannot_find_global_type_0_2318",
              "Cannot find global type '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Named_property_0_of_types_1_and_2_are_not_identical() {
  return diag(
      2319, DiagnosticCategory::Error,
      "Named_property_0_of_types_1_and_2_are_not_identical_2319",
      "Named property '{0}' of types '{1}' and '{2}' are not identical.");
};
static shared_ptr<DiagnosticMessage>
Interface_0_cannot_simultaneously_extend_types_1_and_2() {
  return diag(
      2320, DiagnosticCategory::Error,
      "Interface_0_cannot_simultaneously_extend_types_1_and_2_2320",
      "Interface '{0}' cannot simultaneously extend types '{1}' and '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Excessive_stack_depth_comparing_types_0_and_1() {
  return diag(2321, DiagnosticCategory::Error,
              "Excessive_stack_depth_comparing_types_0_and_1_2321",
              "Excessive stack depth comparing types '{0}' and '{1}'.");
};
static shared_ptr<DiagnosticMessage> Type_0_is_not_assignable_to_type_1() {
  return diag(2322, DiagnosticCategory::Error,
              "Type_0_is_not_assignable_to_type_1_2322",
              "Type '{0}' is not assignable to type '{1}'.");
};
static shared_ptr<DiagnosticMessage> Cannot_redeclare_exported_variable_0() {
  return diag(2323, DiagnosticCategory::Error,
              "Cannot_redeclare_exported_variable_0_2323",
              "Cannot redeclare exported variable '{0}'.");
};
static shared_ptr<DiagnosticMessage> Property_0_is_missing_in_type_1() {
  return diag(2324, DiagnosticCategory::Error,
              "Property_0_is_missing_in_type_1_2324",
              "Property '{0}' is missing in type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_private_in_type_1_but_not_in_type_2() {
  return diag(2325, DiagnosticCategory::Error,
              "Property_0_is_private_in_type_1_but_not_in_type_2_2325",
              "Property '{0}' is private in type '{1}' but not in type '{2}'.");
};
static shared_ptr<DiagnosticMessage> Types_of_property_0_are_incompatible() {
  return diag(2326, DiagnosticCategory::Error,
              "Types_of_property_0_are_incompatible_2326",
              "Types of property '{0}' are incompatible.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_optional_in_type_1_but_required_in_type_2() {
  return diag(
      2327, DiagnosticCategory::Error,
      "Property_0_is_optional_in_type_1_but_required_in_type_2_2327",
      "Property '{0}' is optional in type '{1}' but required in type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Types_of_parameters_0_and_1_are_incompatible() {
  return diag(2328, DiagnosticCategory::Error,
              "Types_of_parameters_0_and_1_are_incompatible_2328",
              "Types of parameters '{0}' and '{1}' are incompatible.");
};
static shared_ptr<DiagnosticMessage>
Index_signature_for_type_0_is_missing_in_type_1() {
  return diag(2329, DiagnosticCategory::Error,
              "Index_signature_for_type_0_is_missing_in_type_1_2329",
              "Index signature for type '{0}' is missing in type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
_0_and_1_index_signatures_are_incompatible() {
  return diag(2330, DiagnosticCategory::Error,
              "_0_and_1_index_signatures_are_incompatible_2330",
              "'{0}' and '{1}' index signatures are incompatible.");
};
static shared_ptr<DiagnosticMessage>
this_cannot_be_referenced_in_a_module_or_namespace_body() {
  return diag(2331, DiagnosticCategory::Error,
              "this_cannot_be_referenced_in_a_module_or_namespace_body_2331",
              "'this' cannot be referenced in a module or namespace body.");
};
static shared_ptr<DiagnosticMessage>
this_cannot_be_referenced_in_current_location() {
  return diag(2332, DiagnosticCategory::Error,
              "this_cannot_be_referenced_in_current_location_2332",
              "'this' cannot be referenced in current location.");
};
static shared_ptr<DiagnosticMessage>
this_cannot_be_referenced_in_constructor_arguments() {
  return diag(2333, DiagnosticCategory::Error,
              "this_cannot_be_referenced_in_constructor_arguments_2333",
              "'this' cannot be referenced in constructor arguments.");
};
static shared_ptr<DiagnosticMessage>
this_cannot_be_referenced_in_a_static_property_initializer() {
  return diag(2334, DiagnosticCategory::Error,
              "this_cannot_be_referenced_in_a_static_property_initializer_2334",
              "'this' cannot be referenced in a static property initializer.");
};
static shared_ptr<DiagnosticMessage>
super_can_only_be_referenced_in_a_derived_class() {
  return diag(2335, DiagnosticCategory::Error,
              "super_can_only_be_referenced_in_a_derived_class_2335",
              "'super' can only be referenced in a derived class.");
};
static shared_ptr<DiagnosticMessage>
super_cannot_be_referenced_in_constructor_arguments() {
  return diag(2336, DiagnosticCategory::Error,
              "super_cannot_be_referenced_in_constructor_arguments_2336",
              "'super' cannot be referenced in constructor arguments.");
};
static shared_ptr<DiagnosticMessage>
Super_calls_are_not_permitted_outside_constructors_or_in_nested_functions_inside_constructors() {
  return diag(2337, DiagnosticCategory::Error,
              "Super_calls_are_not_permitted_outside_constructors_or_in_nested_"
              "functions_inside_constructors_2337",
              "Super calls are not permitted outside constructors or in nested "
              "functions inside constructors.");
};
static shared_ptr<DiagnosticMessage>
super_property_access_is_permitted_only_in_a_constructor_member_function_or_member_accessor_of_a_derived_class() {
  return diag(2338, DiagnosticCategory::Error,
              "super_property_access_is_permitted_only_in_a_constructor_member_"
              "function_or_member_accessor_of_a_der_2338",
              "'super' property access is permitted only in a constructor, "
              "member function, or member accessor of a derived class.");
};
static shared_ptr<DiagnosticMessage> Property_0_does_not_exist_on_type_1() {
  return diag(2339, DiagnosticCategory::Error,
              "Property_0_does_not_exist_on_type_1_2339",
              "Property '{0}' does not exist on type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Only_public_and_protected_methods_of_the_base_class_are_accessible_via_the_super_keyword() {
  return diag(2340, DiagnosticCategory::Error,
              "Only_public_and_protected_methods_of_the_base_class_are_"
              "accessible_via_the_super_keyword_2340",
              "Only public and protected methods of the base class are "
              "accessible via the 'super' keyword.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_private_and_only_accessible_within_class_1() {
  return diag(
      2341, DiagnosticCategory::Error,
      "Property_0_is_private_and_only_accessible_within_class_1_2341",
      "Property '{0}' is private and only accessible within class '{1}'.");
};
static shared_ptr<DiagnosticMessage>
This_syntax_requires_an_imported_helper_named_1_which_does_not_exist_in_0_Consider_upgrading_your_version_of_0() {
  return diag(2343, DiagnosticCategory::Error,
              "This_syntax_requires_an_imported_helper_named_1_which_does_not_"
              "exist_in_0_Consider_upgrading_your_ve_2343",
              "This syntax requires an imported helper named '{1}' which does "
              "not exist in '{0}'. Consider upgrading your version of '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_does_not_satisfy_the_constraint_1() {
  return diag(2344, DiagnosticCategory::Error,
              "Type_0_does_not_satisfy_the_constraint_1_2344",
              "Type '{0}' does not satisfy the constraint '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Argument_of_type_0_is_not_assignable_to_parameter_of_type_1() {
  return diag(
      2345, DiagnosticCategory::Error,
      "Argument_of_type_0_is_not_assignable_to_parameter_of_type_1_2345",
      "Argument of type '{0}' is not assignable to parameter of type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Call_target_does_not_contain_any_signatures() {
  return diag(2346, DiagnosticCategory::Error,
              "Call_target_does_not_contain_any_signatures_2346",
              "Call target does not contain any signatures.");
};
static shared_ptr<DiagnosticMessage>
Untyped_function_calls_may_not_accept_type_arguments() {
  return diag(2347, DiagnosticCategory::Error,
              "Untyped_function_calls_may_not_accept_type_arguments_2347",
              "Untyped function calls may not accept type arguments.");
};
static shared_ptr<DiagnosticMessage>
Value_of_type_0_is_not_callable_Did_you_mean_to_include_new() {
  return diag(
      2348, DiagnosticCategory::Error,
      "Value_of_type_0_is_not_callable_Did_you_mean_to_include_new_2348",
      "Value of type '{0}' is not callable. Did you mean to include 'new'?");
};
static shared_ptr<DiagnosticMessage> This_expression_is_not_callable() {
  return diag(2349, DiagnosticCategory::Error,
              "This_expression_is_not_callable_2349",
              "This expression is not callable.");
};
static shared_ptr<DiagnosticMessage>
Only_a_void_function_can_be_called_with_the_new_keyword() {
  return diag(2350, DiagnosticCategory::Error,
              "Only_a_void_function_can_be_called_with_the_new_keyword_2350",
              "Only a void function can be called with the 'new' keyword.");
};
static shared_ptr<DiagnosticMessage> This_expression_is_not_constructable() {
  return diag(2351, DiagnosticCategory::Error,
              "This_expression_is_not_constructable_2351",
              "This expression is not constructable.");
};
static shared_ptr<DiagnosticMessage>
Conversion_of_type_0_to_type_1_may_be_a_mistake_because_neither_type_sufficiently_overlaps_with_the_other_If_this_was_intentional_convert_the_expression_to_unknown_first() {
  return diag(2352, DiagnosticCategory::Error,
              "Conversion_of_type_0_to_type_1_may_be_a_mistake_because_neither_"
              "type_sufficiently_overlaps_with_the__2352",
              "Conversion of type '{0}' to type '{1}' may be a mistake because "
              "neither type sufficiently overlaps with the other. If this was "
              "intentional, convert the expression to 'unknown' first.");
};
static shared_ptr<DiagnosticMessage>
Object_literal_may_only_specify_known_properties_and_0_does_not_exist_in_type_1() {
  return diag(2353, DiagnosticCategory::Error,
              "Object_literal_may_only_specify_known_properties_and_0_does_not_"
              "exist_in_type_1_2353",
              "Object literal may only specify known properties, and '{0}' "
              "does not exist in type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
This_syntax_requires_an_imported_helper_but_module_0_cannot_be_found() {
  return diag(2354, DiagnosticCategory::Error,
              "This_syntax_requires_an_imported_helper_but_module_0_cannot_be_"
              "found_2354",
              "This syntax requires an imported helper but module '{0}' cannot "
              "be found.");
};
static shared_ptr<DiagnosticMessage>
A_function_whose_declared_type_is_neither_void_nor_any_must_return_a_value() {
  return diag(2355, DiagnosticCategory::Error,
              "A_function_whose_declared_type_is_neither_void_nor_any_must_"
              "return_a_value_2355",
              "A function whose declared type is neither 'void' nor 'any' must "
              "return a value.");
};
static shared_ptr<DiagnosticMessage>
An_arithmetic_operand_must_be_of_type_any_number_bigint_or_an_enum_type() {
  return diag(2356, DiagnosticCategory::Error,
              "An_arithmetic_operand_must_be_of_type_any_number_bigint_or_an_"
              "enum_type_2356",
              "An arithmetic operand must be of type 'any', 'number', 'bigint' "
              "or an enum type.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_an_increment_or_decrement_operator_must_be_a_variable_or_a_property_access() {
  return diag(2357, DiagnosticCategory::Error,
              "The_operand_of_an_increment_or_decrement_operator_must_be_a_"
              "variable_or_a_property_access_2357",
              "The operand of an increment or decrement operator must be a "
              "variable or a property access.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_an_instanceof_expression_must_be_of_type_any_an_object_type_or_a_type_parameter() {
  return diag(2358, DiagnosticCategory::Error,
              "The_left_hand_side_of_an_instanceof_expression_must_be_of_type_"
              "any_an_object_type_or_a_type_paramete_2358",
              "The left-hand side of an 'instanceof' expression must be of "
              "type 'any', an object type or a type parameter.");
};
static shared_ptr<DiagnosticMessage>
The_right_hand_side_of_an_instanceof_expression_must_be_of_type_any_or_of_a_type_assignable_to_the_Function_interface_type() {
  return diag(
      2359, DiagnosticCategory::Error,
      "The_right_hand_side_of_an_instanceof_expression_must_be_of_type_any_or_"
      "of_a_type_assignable_to_the_F_2359",
      "The right-hand side of an 'instanceof' expression must be of type 'any' "
      "or of a type assignable to the 'Function' interface type.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_an_in_expression_must_be_a_private_identifier_or_of_type_any_string_number_or_symbol() {
  return diag(2360, DiagnosticCategory::Error,
              "The_left_hand_side_of_an_in_expression_must_be_a_private_"
              "identifier_or_of_type_any_string_number_or__2360",
              "The left-hand side of an 'in' expression must be a private "
              "identifier or of type 'any', 'string', 'number', or 'symbol'.");
};
static shared_ptr<DiagnosticMessage>
The_right_hand_side_of_an_in_expression_must_not_be_a_primitive() {
  return diag(
      2361, DiagnosticCategory::Error,
      "The_right_hand_side_of_an_in_expression_must_not_be_a_primitive_2361",
      "The right-hand side of an 'in' expression must not be a primitive.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_an_arithmetic_operation_must_be_of_type_any_number_bigint_or_an_enum_type() {
  return diag(2362, DiagnosticCategory::Error,
              "The_left_hand_side_of_an_arithmetic_operation_must_be_of_type_"
              "any_number_bigint_or_an_enum_type_2362",
              "The left-hand side of an arithmetic operation must be of type "
              "'any', 'number', 'bigint' or an enum type.");
};
static shared_ptr<DiagnosticMessage>
The_right_hand_side_of_an_arithmetic_operation_must_be_of_type_any_number_bigint_or_an_enum_type() {
  return diag(2363, DiagnosticCategory::Error,
              "The_right_hand_side_of_an_arithmetic_operation_must_be_of_type_"
              "any_number_bigint_or_an_enum_type_2363",
              "The right-hand side of an arithmetic operation must be of type "
              "'any', 'number', 'bigint' or an enum type.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_an_assignment_expression_must_be_a_variable_or_a_property_access() {
  return diag(2364, DiagnosticCategory::Error,
              "The_left_hand_side_of_an_assignment_expression_must_be_a_"
              "variable_or_a_property_access_2364",
              "The left-hand side of an assignment expression must be a "
              "variable or a property access.");
};
static shared_ptr<DiagnosticMessage>
Operator_0_cannot_be_applied_to_types_1_and_2() {
  return diag(2365, DiagnosticCategory::Error,
              "Operator_0_cannot_be_applied_to_types_1_and_2_2365",
              "Operator '{0}' cannot be applied to types '{1}' and '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Function_lacks_ending_return_statement_and_return_type_does_not_include_undefined() {
  return diag(2366, DiagnosticCategory::Error,
              "Function_lacks_ending_return_statement_and_return_type_does_not_"
              "include_undefined_2366",
              "Function lacks ending return statement and return type does not "
              "include 'undefined'.");
};
static shared_ptr<DiagnosticMessage>
This_condition_will_always_return_0_since_the_types_1_and_2_have_no_overlap() {
  return diag(2367, DiagnosticCategory::Error,
              "This_condition_will_always_return_0_since_the_types_1_and_2_"
              "have_no_overlap_2367",
              "This condition will always return '{0}' since the types '{1}' "
              "and '{2}' have no overlap.");
};
static shared_ptr<DiagnosticMessage> Type_parameter_name_cannot_be_0() {
  return diag(2368, DiagnosticCategory::Error,
              "Type_parameter_name_cannot_be_0_2368",
              "Type parameter name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
A_parameter_property_is_only_allowed_in_a_constructor_implementation() {
  return diag(
      2369, DiagnosticCategory::Error,
      "A_parameter_property_is_only_allowed_in_a_constructor_implementation_"
      "2369",
      "A parameter property is only allowed in a constructor implementation.");
};
static shared_ptr<DiagnosticMessage>
A_rest_parameter_must_be_of_an_array_type() {
  return diag(2370, DiagnosticCategory::Error,
              "A_rest_parameter_must_be_of_an_array_type_2370",
              "A rest parameter must be of an array type.");
};
static shared_ptr<DiagnosticMessage>
A_parameter_initializer_is_only_allowed_in_a_function_or_constructor_implementation() {
  return diag(2371, DiagnosticCategory::Error,
              "A_parameter_initializer_is_only_allowed_in_a_function_or_"
              "constructor_implementation_2371",
              "A parameter initializer is only allowed in a function or "
              "constructor implementation.");
};
static shared_ptr<DiagnosticMessage> Parameter_0_cannot_reference_itself() {
  return diag(2372, DiagnosticCategory::Error,
              "Parameter_0_cannot_reference_itself_2372",
              "Parameter '{0}' cannot reference itself.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_cannot_reference_identifier_1_declared_after_it() {
  return diag(
      2373, DiagnosticCategory::Error,
      "Parameter_0_cannot_reference_identifier_1_declared_after_it_2373",
      "Parameter '{0}' cannot reference identifier '{1}' declared after it.");
};
static shared_ptr<DiagnosticMessage> Duplicate_index_signature_for_type_0() {
  return diag(2374, DiagnosticCategory::Error,
              "Duplicate_index_signature_for_type_0_2374",
              "Duplicate index signature for type '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_assignable_to_type_1_with_exactOptionalPropertyTypes_Colon_true_Consider_adding_undefined_to_the_types_of_the_target_s_properties() {
  return diag(
      2375, DiagnosticCategory::Error,
      "Type_0_is_not_assignable_to_type_1_with_exactOptionalPropertyTypes_"
      "Colon_true_Consider_adding_undefi_2375",
      "Type '{0}' is not assignable to type '{1}' with "
      "'exactOptionalPropertyTypes: true'. Consider adding 'undefined' to the "
      "types of the target's properties.");
};
static shared_ptr<DiagnosticMessage>
A_super_call_must_be_the_first_statement_in_the_constructor_when_a_class_contains_initialized_properties_parameter_properties_or_private_identifiers() {
  return diag(2376, DiagnosticCategory::Error,
              "A_super_call_must_be_the_first_statement_in_the_constructor_"
              "when_a_class_contains_initialized_proper_2376",
              "A 'super' call must be the first statement in the constructor "
              "when a class contains initialized properties, parameter "
              "properties, or private identifiers.");
};
static shared_ptr<DiagnosticMessage>
Constructors_for_derived_classes_must_contain_a_super_call() {
  return diag(2377, DiagnosticCategory::Error,
              "Constructors_for_derived_classes_must_contain_a_super_call_2377",
              "Constructors for derived classes must contain a 'super' call.");
};
static shared_ptr<DiagnosticMessage> A_get_accessor_must_return_a_value() {
  return diag(2378, DiagnosticCategory::Error,
              "A_get_accessor_must_return_a_value_2378",
              "A 'get' accessor must return a value.");
};
static shared_ptr<DiagnosticMessage>
Argument_of_type_0_is_not_assignable_to_parameter_of_type_1_with_exactOptionalPropertyTypes_Colon_true_Consider_adding_undefined_to_the_types_of_the_target_s_properties() {
  return diag(2379, DiagnosticCategory::Error,
              "Argument_of_type_0_is_not_assignable_to_parameter_of_type_1_"
              "with_exactOptionalPropertyTypes_Colon_tr_2379",
              "Argument of type '{0}' is not assignable to parameter of type "
              "'{1}' with 'exactOptionalPropertyTypes: true'. Consider adding "
              "'undefined' to the types of the target's properties.");
};
static shared_ptr<DiagnosticMessage>
The_return_type_of_a_get_accessor_must_be_assignable_to_its_set_accessor_type() {
  return diag(2380, DiagnosticCategory::Error,
              "The_return_type_of_a_get_accessor_must_be_assignable_to_its_set_"
              "accessor_type_2380",
              "The return type of a 'get' accessor must be assignable to its "
              "'set' accessor type");
};
static shared_ptr<DiagnosticMessage>
Overload_signatures_must_all_be_exported_or_non_exported() {
  return diag(2383, DiagnosticCategory::Error,
              "Overload_signatures_must_all_be_exported_or_non_exported_2383",
              "Overload signatures must all be exported or non-exported.");
};
static shared_ptr<DiagnosticMessage>
Overload_signatures_must_all_be_ambient_or_non_ambient() {
  return diag(2384, DiagnosticCategory::Error,
              "Overload_signatures_must_all_be_ambient_or_non_ambient_2384",
              "Overload signatures must all be ambient or non-ambient.");
};
static shared_ptr<DiagnosticMessage>
Overload_signatures_must_all_be_public_private_or_protected() {
  return diag(
      2385, DiagnosticCategory::Error,
      "Overload_signatures_must_all_be_public_private_or_protected_2385",
      "Overload signatures must all be public, private or protected.");
};
static shared_ptr<DiagnosticMessage>
Overload_signatures_must_all_be_optional_or_required() {
  return diag(2386, DiagnosticCategory::Error,
              "Overload_signatures_must_all_be_optional_or_required_2386",
              "Overload signatures must all be optional or required.");
};
static shared_ptr<DiagnosticMessage> Function_overload_must_be_static() {
  return diag(2387, DiagnosticCategory::Error,
              "Function_overload_must_be_static_2387",
              "Function overload must be static.");
};
static shared_ptr<DiagnosticMessage> Function_overload_must_not_be_static() {
  return diag(2388, DiagnosticCategory::Error,
              "Function_overload_must_not_be_static_2388",
              "Function overload must not be static.");
};
static shared_ptr<DiagnosticMessage> Function_implementation_name_must_be_0() {
  return diag(2389, DiagnosticCategory::Error,
              "Function_implementation_name_must_be_0_2389",
              "Function implementation name must be '{0}'.");
};
static shared_ptr<DiagnosticMessage> Constructor_implementation_is_missing() {
  return diag(2390, DiagnosticCategory::Error,
              "Constructor_implementation_is_missing_2390",
              "Constructor implementation is missing.");
};
static shared_ptr<DiagnosticMessage>
Function_implementation_is_missing_or_not_immediately_following_the_declaration() {
  return diag(2391, DiagnosticCategory::Error,
              "Function_implementation_is_missing_or_not_immediately_following_"
              "the_declaration_2391",
              "Function implementation is missing or not immediately following "
              "the declaration.");
};
static shared_ptr<DiagnosticMessage>
Multiple_constructor_implementations_are_not_allowed() {
  return diag(2392, DiagnosticCategory::Error,
              "Multiple_constructor_implementations_are_not_allowed_2392",
              "Multiple constructor implementations are not allowed.");
};
static shared_ptr<DiagnosticMessage> Duplicate_function_implementation() {
  return diag(2393, DiagnosticCategory::Error,
              "Duplicate_function_implementation_2393",
              "Duplicate function implementation.");
};
static shared_ptr<DiagnosticMessage>
This_overload_signature_is_not_compatible_with_its_implementation_signature() {
  return diag(2394, DiagnosticCategory::Error,
              "This_overload_signature_is_not_compatible_with_its_"
              "implementation_signature_2394",
              "This overload signature is not compatible with its "
              "implementation signature.");
};
static shared_ptr<DiagnosticMessage>
Individual_declarations_in_merged_declaration_0_must_be_all_exported_or_all_local() {
  return diag(2395, DiagnosticCategory::Error,
              "Individual_declarations_in_merged_declaration_0_must_be_all_"
              "exported_or_all_local_2395",
              "Individual declarations in merged declaration '{0}' must be all "
              "exported or all local.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_arguments_Compiler_uses_arguments_to_initialize_rest_parameters() {
  return diag(2396, DiagnosticCategory::Error,
              "Duplicate_identifier_arguments_Compiler_uses_arguments_to_"
              "initialize_rest_parameters_2396",
              "Duplicate identifier 'arguments'. Compiler uses 'arguments' to "
              "initialize rest parameters.");
};
static shared_ptr<DiagnosticMessage>
Declaration_name_conflicts_with_built_in_global_identifier_0() {
  return diag(
      2397, DiagnosticCategory::Error,
      "Declaration_name_conflicts_with_built_in_global_identifier_0_2397",
      "Declaration name conflicts with built-in global identifier '{0}'.");
};
static shared_ptr<DiagnosticMessage>
constructor_cannot_be_used_as_a_parameter_property_name() {
  return diag(2398, DiagnosticCategory::Error,
              "constructor_cannot_be_used_as_a_parameter_property_name_2398",
              "'constructor' cannot be used as a parameter property name.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_this_Compiler_uses_variable_declaration_this_to_capture_this_reference() {
  return diag(2399, DiagnosticCategory::Error,
              "Duplicate_identifier_this_Compiler_uses_variable_declaration_"
              "this_to_capture_this_reference_2399",
              "Duplicate identifier '_this'. Compiler uses variable "
              "declaration '_this' to capture 'this' reference.");
};
static shared_ptr<DiagnosticMessage>
Expression_resolves_to_variable_declaration_this_that_compiler_uses_to_capture_this_reference() {
  return diag(2400, DiagnosticCategory::Error,
              "Expression_resolves_to_variable_declaration_this_that_compiler_"
              "uses_to_capture_this_reference_2400",
              "Expression resolves to variable declaration '_this' that "
              "compiler uses to capture 'this' reference.");
};
static shared_ptr<DiagnosticMessage>
Expression_resolves_to_super_that_compiler_uses_to_capture_base_class_reference() {
  return diag(2402, DiagnosticCategory::Error,
              "Expression_resolves_to_super_that_compiler_uses_to_capture_base_"
              "class_reference_2402",
              "Expression resolves to '_super' that compiler uses to capture "
              "base class reference.");
};
static shared_ptr<DiagnosticMessage>
Subsequent_variable_declarations_must_have_the_same_type_Variable_0_must_be_of_type_1_but_here_has_type_2() {
  return diag(2403, DiagnosticCategory::Error,
              "Subsequent_variable_declarations_must_have_the_same_type_"
              "Variable_0_must_be_of_type_1_but_here_has_t_2403",
              "Subsequent variable declarations must have the same type.  "
              "Variable '{0}' must be of type '{1}', but here has type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_in_statement_cannot_use_a_type_annotation() {
  return diag(2404, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_in_statement_cannot_use_a_type_"
              "annotation_2404",
              "The left-hand side of a 'for...in' statement cannot use a type "
              "annotation.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_in_statement_must_be_of_type_string_or_any() {
  return diag(2405, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_in_statement_must_be_of_type_string_"
              "or_any_2405",
              "The left-hand side of a 'for...in' statement must be of type "
              "'string' or 'any'.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_in_statement_must_be_a_variable_or_a_property_access() {
  return diag(2406, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_in_statement_must_be_a_variable_or_"
              "a_property_access_2406",
              "The left-hand side of a 'for...in' statement must be a variable "
              "or a property access.");
};
static shared_ptr<DiagnosticMessage>
The_right_hand_side_of_a_for_in_statement_must_be_of_type_any_an_object_type_or_a_type_parameter_but_here_has_type_0() {
  return diag(
      2407, DiagnosticCategory::Error,
      "The_right_hand_side_of_a_for_in_statement_must_be_of_type_any_an_object_"
      "type_or_a_type_parameter_but_2407",
      "The right-hand side of a 'for...in' statement must be of type 'any', an "
      "object type or a type parameter, but here has type '{0}'.");
};
static shared_ptr<DiagnosticMessage> Setters_cannot_return_a_value() {
  return diag(2408, DiagnosticCategory::Error,
              "Setters_cannot_return_a_value_2408",
              "Setters cannot return a value.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_constructor_signature_must_be_assignable_to_the_instance_type_of_the_class() {
  return diag(2409, DiagnosticCategory::Error,
              "Return_type_of_constructor_signature_must_be_assignable_to_the_"
              "instance_type_of_the_class_2409",
              "Return type of constructor signature must be assignable to the "
              "instance type of the class.");
};
static shared_ptr<DiagnosticMessage>
The_with_statement_is_not_supported_All_symbols_in_a_with_block_will_have_type_any() {
  return diag(2410, DiagnosticCategory::Error,
              "The_with_statement_is_not_supported_All_symbols_in_a_with_block_"
              "will_have_type_any_2410",
              "The 'with' statement is not supported. All symbols in a 'with' "
              "block will have type 'any'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_assignable_to_type_1_with_exactOptionalPropertyTypes_Colon_true_Consider_adding_undefined_to_the_type_of_the_target() {
  return diag(
      2412, DiagnosticCategory::Error,
      "Type_0_is_not_assignable_to_type_1_with_exactOptionalPropertyTypes_"
      "Colon_true_Consider_adding_undefi_2412",
      "Type '{0}' is not assignable to type '{1}' with "
      "'exactOptionalPropertyTypes: true'. Consider adding 'undefined' to the "
      "type of the target.");
};
static shared_ptr<DiagnosticMessage>
Property_0_of_type_1_is_not_assignable_to_2_index_type_3() {
  return diag(2411, DiagnosticCategory::Error,
              "Property_0_of_type_1_is_not_assignable_to_2_index_type_3_2411",
              "Property '{0}' of type '{1}' is not assignable to '{2}' index "
              "type '{3}'.");
};
static shared_ptr<DiagnosticMessage>
_0_index_type_1_is_not_assignable_to_2_index_type_3() {
  return diag(
      2413, DiagnosticCategory::Error,
      "_0_index_type_1_is_not_assignable_to_2_index_type_3_2413",
      "'{0}' index type '{1}' is not assignable to '{2}' index type '{3}'.");
};
static shared_ptr<DiagnosticMessage> Class_name_cannot_be_0() {
  return diag(2414, DiagnosticCategory::Error, "Class_name_cannot_be_0_2414",
              "Class name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Class_0_incorrectly_extends_base_class_1() {
  return diag(2415, DiagnosticCategory::Error,
              "Class_0_incorrectly_extends_base_class_1_2415",
              "Class '{0}' incorrectly extends base class '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_in_type_1_is_not_assignable_to_the_same_property_in_base_type_2() {
  return diag(2416, DiagnosticCategory::Error,
              "Property_0_in_type_1_is_not_assignable_to_the_same_property_in_"
              "base_type_2_2416",
              "Property '{0}' in type '{1}' is not assignable to the same "
              "property in base type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Class_static_side_0_incorrectly_extends_base_class_static_side_1() {
  return diag(
      2417, DiagnosticCategory::Error,
      "Class_static_side_0_incorrectly_extends_base_class_static_side_1_2417",
      "Class static side '{0}' incorrectly extends base class static side "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_of_computed_property_s_value_is_0_which_is_not_assignable_to_type_1() {
  return diag(2418, DiagnosticCategory::Error,
              "Type_of_computed_property_s_value_is_0_which_is_not_assignable_"
              "to_type_1_2418",
              "Type of computed property's value is '{0}', which is not "
              "assignable to type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Types_of_construct_signatures_are_incompatible() {
  return diag(2419, DiagnosticCategory::Error,
              "Types_of_construct_signatures_are_incompatible_2419",
              "Types of construct signatures are incompatible.");
};
static shared_ptr<DiagnosticMessage>
Class_0_incorrectly_implements_interface_1() {
  return diag(2420, DiagnosticCategory::Error,
              "Class_0_incorrectly_implements_interface_1_2420",
              "Class '{0}' incorrectly implements interface '{1}'.");
};
static shared_ptr<DiagnosticMessage>
A_class_can_only_implement_an_object_type_or_intersection_of_object_types_with_statically_known_members() {
  return diag(2422, DiagnosticCategory::Error,
              "A_class_can_only_implement_an_object_type_or_intersection_of_"
              "object_types_with_statically_known_memb_2422",
              "A class can only implement an object type or intersection of "
              "object types with statically known members.");
};
static shared_ptr<DiagnosticMessage>
Class_0_defines_instance_member_function_1_but_extended_class_2_defines_it_as_instance_member_accessor() {
  return diag(2423, DiagnosticCategory::Error,
              "Class_0_defines_instance_member_function_1_but_extended_class_2_"
              "defines_it_as_instance_member_access_2423",
              "Class '{0}' defines instance member function '{1}', but "
              "extended class '{2}' defines it as instance member accessor.");
};
static shared_ptr<DiagnosticMessage>
Class_0_defines_instance_member_property_1_but_extended_class_2_defines_it_as_instance_member_function() {
  return diag(2425, DiagnosticCategory::Error,
              "Class_0_defines_instance_member_property_1_but_extended_class_2_"
              "defines_it_as_instance_member_functi_2425",
              "Class '{0}' defines instance member property '{1}', but "
              "extended class '{2}' defines it as instance member function.");
};
static shared_ptr<DiagnosticMessage>
Class_0_defines_instance_member_accessor_1_but_extended_class_2_defines_it_as_instance_member_function() {
  return diag(2426, DiagnosticCategory::Error,
              "Class_0_defines_instance_member_accessor_1_but_extended_class_2_"
              "defines_it_as_instance_member_functi_2426",
              "Class '{0}' defines instance member accessor '{1}', but "
              "extended class '{2}' defines it as instance member function.");
};
static shared_ptr<DiagnosticMessage> Interface_name_cannot_be_0() {
  return diag(2427, DiagnosticCategory::Error,
              "Interface_name_cannot_be_0_2427",
              "Interface name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
All_declarations_of_0_must_have_identical_type_parameters() {
  return diag(2428, DiagnosticCategory::Error,
              "All_declarations_of_0_must_have_identical_type_parameters_2428",
              "All declarations of '{0}' must have identical type parameters.");
};
static shared_ptr<DiagnosticMessage>
Interface_0_incorrectly_extends_interface_1() {
  return diag(2430, DiagnosticCategory::Error,
              "Interface_0_incorrectly_extends_interface_1_2430",
              "Interface '{0}' incorrectly extends interface '{1}'.");
};
static shared_ptr<DiagnosticMessage> Enum_name_cannot_be_0() {
  return diag(2431, DiagnosticCategory::Error, "Enum_name_cannot_be_0_2431",
              "Enum name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
In_an_enum_with_multiple_declarations_only_one_declaration_can_omit_an_initializer_for_its_first_enum_element() {
  return diag(2432, DiagnosticCategory::Error,
              "In_an_enum_with_multiple_declarations_only_one_declaration_can_"
              "omit_an_initializer_for_its_first_enu_2432",
              "In an enum with multiple declarations, only one declaration can "
              "omit an initializer for its first enum element.");
};
static shared_ptr<DiagnosticMessage>
A_namespace_declaration_cannot_be_in_a_different_file_from_a_class_or_function_with_which_it_is_merged() {
  return diag(2433, DiagnosticCategory::Error,
              "A_namespace_declaration_cannot_be_in_a_different_file_from_a_"
              "class_or_function_with_which_it_is_merg_2433",
              "A namespace declaration cannot be in a different file from a "
              "class or function with which it is merged.");
};
static shared_ptr<DiagnosticMessage>
A_namespace_declaration_cannot_be_located_prior_to_a_class_or_function_with_which_it_is_merged() {
  return diag(2434, DiagnosticCategory::Error,
              "A_namespace_declaration_cannot_be_located_prior_to_a_class_or_"
              "function_with_which_it_is_merged_2434",
              "A namespace declaration cannot be located prior to a class or "
              "function with which it is merged.");
};
static shared_ptr<DiagnosticMessage>
Ambient_modules_cannot_be_nested_in_other_modules_or_namespaces() {
  return diag(
      2435, DiagnosticCategory::Error,
      "Ambient_modules_cannot_be_nested_in_other_modules_or_namespaces_2435",
      "Ambient modules cannot be nested in other modules or namespaces.");
};
static shared_ptr<DiagnosticMessage>
Ambient_module_declaration_cannot_specify_relative_module_name() {
  return diag(
      2436, DiagnosticCategory::Error,
      "Ambient_module_declaration_cannot_specify_relative_module_name_2436",
      "Ambient module declaration cannot specify relative module name.");
};
static shared_ptr<DiagnosticMessage>
Module_0_is_hidden_by_a_local_declaration_with_the_same_name() {
  return diag(
      2437, DiagnosticCategory::Error,
      "Module_0_is_hidden_by_a_local_declaration_with_the_same_name_2437",
      "Module '{0}' is hidden by a local declaration with the same name.");
};
static shared_ptr<DiagnosticMessage> Import_name_cannot_be_0() {
  return diag(2438, DiagnosticCategory::Error, "Import_name_cannot_be_0_2438",
              "Import name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Import_or_export_declaration_in_an_ambient_module_declaration_cannot_reference_module_through_relative_module_name() {
  return diag(2439, DiagnosticCategory::Error,
              "Import_or_export_declaration_in_an_ambient_module_declaration_"
              "cannot_reference_module_through_relati_2439",
              "Import or export declaration in an ambient module declaration "
              "cannot reference module through relative module name.");
};
static shared_ptr<DiagnosticMessage>
Import_declaration_conflicts_with_local_declaration_of_0() {
  return diag(2440, DiagnosticCategory::Error,
              "Import_declaration_conflicts_with_local_declaration_of_0_2440",
              "Import declaration conflicts with local declaration of '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_0_Compiler_reserves_name_1_in_top_level_scope_of_a_module() {
  return diag(2441, DiagnosticCategory::Error,
              "Duplicate_identifier_0_Compiler_reserves_name_1_in_top_level_"
              "scope_of_a_module_2441",
              "Duplicate identifier '{0}'. Compiler reserves name '{1}' in top "
              "level scope of a module.");
};
static shared_ptr<DiagnosticMessage>
Types_have_separate_declarations_of_a_private_property_0() {
  return diag(2442, DiagnosticCategory::Error,
              "Types_have_separate_declarations_of_a_private_property_0_2442",
              "Types have separate declarations of a private property '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_protected_but_type_1_is_not_a_class_derived_from_2() {
  return diag(
      2443, DiagnosticCategory::Error,
      "Property_0_is_protected_but_type_1_is_not_a_class_derived_from_2_2443",
      "Property '{0}' is protected but type '{1}' is not a class derived from "
      "'{2}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_protected_in_type_1_but_public_in_type_2() {
  return diag(
      2444, DiagnosticCategory::Error,
      "Property_0_is_protected_in_type_1_but_public_in_type_2_2444",
      "Property '{0}' is protected in type '{1}' but public in type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_protected_and_only_accessible_within_class_1_and_its_subclasses() {
  return diag(2445, DiagnosticCategory::Error,
              "Property_0_is_protected_and_only_accessible_within_class_1_and_"
              "its_subclasses_2445",
              "Property '{0}' is protected and only accessible within class "
              "'{1}' and its subclasses.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_protected_and_only_accessible_through_an_instance_of_class_1_This_is_an_instance_of_class_2() {
  return diag(2446, DiagnosticCategory::Error,
              "Property_0_is_protected_and_only_accessible_through_an_instance_"
              "of_class_1_This_is_an_instance_of_cl_2446",
              "Property '{0}' is protected and only accessible through an "
              "instance of class '{1}'. This is an instance of class '{2}'.");
};
static shared_ptr<DiagnosticMessage>
The_0_operator_is_not_allowed_for_boolean_types_Consider_using_1_instead() {
  return diag(2447, DiagnosticCategory::Error,
              "The_0_operator_is_not_allowed_for_boolean_types_Consider_using_"
              "1_instead_2447",
              "The '{0}' operator is not allowed for boolean types. Consider "
              "using '{1}' instead.");
};
static shared_ptr<DiagnosticMessage>
Block_scoped_variable_0_used_before_its_declaration() {
  return diag(2448, DiagnosticCategory::Error,
              "Block_scoped_variable_0_used_before_its_declaration_2448",
              "Block-scoped variable '{0}' used before its declaration.");
};
static shared_ptr<DiagnosticMessage> Class_0_used_before_its_declaration() {
  return diag(2449, DiagnosticCategory::Error,
              "Class_0_used_before_its_declaration_2449",
              "Class '{0}' used before its declaration.");
};
static shared_ptr<DiagnosticMessage> Enum_0_used_before_its_declaration() {
  return diag(2450, DiagnosticCategory::Error,
              "Enum_0_used_before_its_declaration_2450",
              "Enum '{0}' used before its declaration.");
};
static shared_ptr<DiagnosticMessage>
Cannot_redeclare_block_scoped_variable_0() {
  return diag(2451, DiagnosticCategory::Error,
              "Cannot_redeclare_block_scoped_variable_0_2451",
              "Cannot redeclare block-scoped variable '{0}'.");
};
static shared_ptr<DiagnosticMessage>
An_enum_member_cannot_have_a_numeric_name() {
  return diag(2452, DiagnosticCategory::Error,
              "An_enum_member_cannot_have_a_numeric_name_2452",
              "An enum member cannot have a numeric name.");
};
static shared_ptr<DiagnosticMessage>
Variable_0_is_used_before_being_assigned() {
  return diag(2454, DiagnosticCategory::Error,
              "Variable_0_is_used_before_being_assigned_2454",
              "Variable '{0}' is used before being assigned.");
};
static shared_ptr<DiagnosticMessage>
Type_alias_0_circularly_references_itself() {
  return diag(2456, DiagnosticCategory::Error,
              "Type_alias_0_circularly_references_itself_2456",
              "Type alias '{0}' circularly references itself.");
};
static shared_ptr<DiagnosticMessage> Type_alias_name_cannot_be_0() {
  return diag(2457, DiagnosticCategory::Error,
              "Type_alias_name_cannot_be_0_2457",
              "Type alias name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
An_AMD_module_cannot_have_multiple_name_assignments() {
  return diag(2458, DiagnosticCategory::Error,
              "An_AMD_module_cannot_have_multiple_name_assignments_2458",
              "An AMD module cannot have multiple name assignments.");
};
static shared_ptr<DiagnosticMessage>
Module_0_declares_1_locally_but_it_is_not_exported() {
  return diag(2459, DiagnosticCategory::Error,
              "Module_0_declares_1_locally_but_it_is_not_exported_2459",
              "Module '{0}' declares '{1}' locally, but it is not exported.");
};
static shared_ptr<DiagnosticMessage>
Module_0_declares_1_locally_but_it_is_exported_as_2() {
  return diag(
      2460, DiagnosticCategory::Error,
      "Module_0_declares_1_locally_but_it_is_exported_as_2_2460",
      "Module '{0}' declares '{1}' locally, but it is exported as '{2}'.");
};
static shared_ptr<DiagnosticMessage> Type_0_is_not_an_array_type() {
  return diag(2461, DiagnosticCategory::Error,
              "Type_0_is_not_an_array_type_2461",
              "Type '{0}' is not an array type.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_must_be_last_in_a_destructuring_pattern() {
  return diag(2462, DiagnosticCategory::Error,
              "A_rest_element_must_be_last_in_a_destructuring_pattern_2462",
              "A rest element must be last in a destructuring pattern.");
};
static shared_ptr<DiagnosticMessage>
A_binding_pattern_parameter_cannot_be_optional_in_an_implementation_signature() {
  return diag(2463, DiagnosticCategory::Error,
              "A_binding_pattern_parameter_cannot_be_optional_in_an_"
              "implementation_signature_2463",
              "A binding pattern parameter cannot be optional in an "
              "implementation signature.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_must_be_of_type_string_number_symbol_or_any() {
  return diag(2464, DiagnosticCategory::Error,
              "A_computed_property_name_must_be_of_type_string_number_symbol_"
              "or_any_2464",
              "A computed property name must be of type 'string', 'number', "
              "'symbol', or 'any'.");
};
static shared_ptr<DiagnosticMessage>
this_cannot_be_referenced_in_a_computed_property_name() {
  return diag(2465, DiagnosticCategory::Error,
              "this_cannot_be_referenced_in_a_computed_property_name_2465",
              "'this' cannot be referenced in a computed property name.");
};
static shared_ptr<DiagnosticMessage>
super_cannot_be_referenced_in_a_computed_property_name() {
  return diag(2466, DiagnosticCategory::Error,
              "super_cannot_be_referenced_in_a_computed_property_name_2466",
              "'super' cannot be referenced in a computed property name.");
};
static shared_ptr<DiagnosticMessage>
A_computed_property_name_cannot_reference_a_type_parameter_from_its_containing_type() {
  return diag(2467, DiagnosticCategory::Error,
              "A_computed_property_name_cannot_reference_a_type_parameter_from_"
              "its_containing_type_2467",
              "A computed property name cannot reference a type parameter from "
              "its containing type.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_global_value_0() {
  return diag(2468, DiagnosticCategory::Error,
              "Cannot_find_global_value_0_2468",
              "Cannot find global value '{0}'.");
};
static shared_ptr<DiagnosticMessage>
The_0_operator_cannot_be_applied_to_type_symbol() {
  return diag(2469, DiagnosticCategory::Error,
              "The_0_operator_cannot_be_applied_to_type_symbol_2469",
              "The '{0}' operator cannot be applied to type 'symbol'.");
};
static shared_ptr<DiagnosticMessage>
Spread_operator_in_new_expressions_is_only_available_when_targeting_ECMAScript_5_and_higher() {
  return diag(2472, DiagnosticCategory::Error,
              "Spread_operator_in_new_expressions_is_only_available_when_"
              "targeting_ECMAScript_5_and_higher_2472",
              "Spread operator in 'new' expressions is only available when "
              "targeting ECMAScript 5 and higher.");
};
static shared_ptr<DiagnosticMessage>
Enum_declarations_must_all_be_const_or_non_const() {
  return diag(2473, DiagnosticCategory::Error,
              "Enum_declarations_must_all_be_const_or_non_const_2473",
              "Enum declarations must all be const or non-const.");
};
static shared_ptr<DiagnosticMessage>
const_enum_member_initializers_can_only_contain_literal_values_and_other_computed_enum_values() {
  return diag(2474, DiagnosticCategory::Error,
              "const_enum_member_initializers_can_only_contain_literal_values_"
              "and_other_computed_enum_values_2474",
              "const enum member initializers can only contain literal values "
              "and other computed enum values.");
};
static shared_ptr<DiagnosticMessage>
const_enums_can_only_be_used_in_property_or_index_access_expressions_or_the_right_hand_side_of_an_import_declaration_or_export_assignment_or_type_query() {
  return diag(2475, DiagnosticCategory::Error,
              "const_enums_can_only_be_used_in_property_or_index_access_"
              "expressions_or_the_right_hand_side_of_an_im_2475",
              "'const' enums can only be used in property or index access "
              "expressions or the right hand side of an import declaration or "
              "export assignment or type query.");
};
static shared_ptr<DiagnosticMessage>
A_const_enum_member_can_only_be_accessed_using_a_string_literal() {
  return diag(
      2476, DiagnosticCategory::Error,
      "A_const_enum_member_can_only_be_accessed_using_a_string_literal_2476",
      "A const enum member can only be accessed using a string literal.");
};
static shared_ptr<DiagnosticMessage>
const_enum_member_initializer_was_evaluated_to_a_non_finite_value() {
  return diag(
      2477, DiagnosticCategory::Error,
      "const_enum_member_initializer_was_evaluated_to_a_non_finite_value_2477",
      "'const' enum member initializer was evaluated to a non-finite value.");
};
static shared_ptr<DiagnosticMessage>
const_enum_member_initializer_was_evaluated_to_disallowed_value_NaN() {
  return diag(2478, DiagnosticCategory::Error,
              "const_enum_member_initializer_was_evaluated_to_disallowed_value_"
              "NaN_2478",
              "'const' enum member initializer was evaluated to disallowed "
              "value 'NaN'.");
};
static shared_ptr<DiagnosticMessage>
let_is_not_allowed_to_be_used_as_a_name_in_let_or_const_declarations() {
  return diag(2480, DiagnosticCategory::Error,
              "let_is_not_allowed_to_be_used_as_a_name_in_let_or_const_"
              "declarations_2480",
              "'let' is not allowed to be used as a name in 'let' or 'const' "
              "declarations.");
};
static shared_ptr<DiagnosticMessage>
Cannot_initialize_outer_scoped_variable_0_in_the_same_scope_as_block_scoped_declaration_1() {
  return diag(2481, DiagnosticCategory::Error,
              "Cannot_initialize_outer_scoped_variable_0_in_the_same_scope_as_"
              "block_scoped_declaration_1_2481",
              "Cannot initialize outer scoped variable '{0}' in the same scope "
              "as block scoped declaration '{1}'.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_of_statement_cannot_use_a_type_annotation() {
  return diag(2483, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_of_statement_cannot_use_a_type_"
              "annotation_2483",
              "The left-hand side of a 'for...of' statement cannot use a type "
              "annotation.");
};
static shared_ptr<DiagnosticMessage>
Export_declaration_conflicts_with_exported_declaration_of_0() {
  return diag(
      2484, DiagnosticCategory::Error,
      "Export_declaration_conflicts_with_exported_declaration_of_0_2484",
      "Export declaration conflicts with exported declaration of '{0}'.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_of_statement_must_be_a_variable_or_a_property_access() {
  return diag(2487, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_of_statement_must_be_a_variable_or_"
              "a_property_access_2487",
              "The left-hand side of a 'for...of' statement must be a variable "
              "or a property access.");
};
static shared_ptr<DiagnosticMessage>
Type_0_must_have_a_Symbol_iterator_method_that_returns_an_iterator() {
  return diag(
      2488, DiagnosticCategory::Error,
      "Type_0_must_have_a_Symbol_iterator_method_that_returns_an_iterator_2488",
      "Type '{0}' must have a '[Symbol.iterator]()' method that returns an "
      "iterator.");
};
static shared_ptr<DiagnosticMessage> An_iterator_must_have_a_next_method() {
  return diag(2489, DiagnosticCategory::Error,
              "An_iterator_must_have_a_next_method_2489",
              "An iterator must have a 'next()' method.");
};
static shared_ptr<DiagnosticMessage>
The_type_returned_by_the_0_method_of_an_iterator_must_have_a_value_property() {
  return diag(2490, DiagnosticCategory::Error,
              "The_type_returned_by_the_0_method_of_an_iterator_must_have_a_"
              "value_property_2490",
              "The type returned by the '{0}()' method of an iterator must "
              "have a 'value' property.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_in_statement_cannot_be_a_destructuring_pattern() {
  return diag(2491, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_in_statement_cannot_be_a_"
              "destructuring_pattern_2491",
              "The left-hand side of a 'for...in' statement cannot be a "
              "destructuring pattern.");
};
static shared_ptr<DiagnosticMessage>
Cannot_redeclare_identifier_0_in_catch_clause() {
  return diag(2492, DiagnosticCategory::Error,
              "Cannot_redeclare_identifier_0_in_catch_clause_2492",
              "Cannot redeclare identifier '{0}' in catch clause.");
};
static shared_ptr<DiagnosticMessage>
Tuple_type_0_of_length_1_has_no_element_at_index_2() {
  return diag(
      2493, DiagnosticCategory::Error,
      "Tuple_type_0_of_length_1_has_no_element_at_index_2_2493",
      "Tuple type '{0}' of length '{1}' has no element at index '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Using_a_string_in_a_for_of_statement_is_only_supported_in_ECMAScript_5_and_higher() {
  return diag(2494, DiagnosticCategory::Error,
              "Using_a_string_in_a_for_of_statement_is_only_supported_in_"
              "ECMAScript_5_and_higher_2494",
              "Using a string in a 'for...of' statement is only supported in "
              "ECMAScript 5 and higher.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_an_array_type_or_a_string_type() {
  return diag(2495, DiagnosticCategory::Error,
              "Type_0_is_not_an_array_type_or_a_string_type_2495",
              "Type '{0}' is not an array type or a string type.");
};
static shared_ptr<DiagnosticMessage>
The_arguments_object_cannot_be_referenced_in_an_arrow_function_in_ES3_and_ES5_Consider_using_a_standard_function_expression() {
  return diag(
      2496, DiagnosticCategory::Error,
      "The_arguments_object_cannot_be_referenced_in_an_arrow_function_in_ES3_"
      "and_ES5_Consider_using_a_stand_2496",
      "The 'arguments' object cannot be referenced in an arrow function in ES3 "
      "and ES5. Consider using a standard function expression.");
};
static shared_ptr<DiagnosticMessage>
This_module_can_only_be_referenced_with_ECMAScript_imports_Slashexports_by_turning_on_the_0_flag_and_referencing_its_default_export() {
  return diag(
      2497, DiagnosticCategory::Error,
      "This_module_can_only_be_referenced_with_ECMAScript_imports_Slashexports_"
      "by_turning_on_the_0_flag_and_2497",
      "This module can only be referenced with ECMAScript imports/exports by "
      "turning on the '{0}' flag and referencing its default export.");
};
static shared_ptr<DiagnosticMessage>
Module_0_uses_export_and_cannot_be_used_with_export_Asterisk() {
  return diag(
      2498, DiagnosticCategory::Error,
      "Module_0_uses_export_and_cannot_be_used_with_export_Asterisk_2498",
      "Module '{0}' uses 'export =' and cannot be used with 'export *'.");
};
static shared_ptr<DiagnosticMessage>
An_interface_can_only_extend_an_identifier_Slashqualified_name_with_optional_type_arguments() {
  return diag(2499, DiagnosticCategory::Error,
              "An_interface_can_only_extend_an_identifier_Slashqualified_name_"
              "with_optional_type_arguments_2499",
              "An interface can only extend an identifier/qualified-name with "
              "optional type arguments.");
};
static shared_ptr<DiagnosticMessage>
A_class_can_only_implement_an_identifier_Slashqualified_name_with_optional_type_arguments() {
  return diag(2500, DiagnosticCategory::Error,
              "A_class_can_only_implement_an_identifier_Slashqualified_name_"
              "with_optional_type_arguments_2500",
              "A class can only implement an identifier/qualified-name with "
              "optional type arguments.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_cannot_contain_a_binding_pattern() {
  return diag(2501, DiagnosticCategory::Error,
              "A_rest_element_cannot_contain_a_binding_pattern_2501",
              "A rest element cannot contain a binding pattern.");
};
static shared_ptr<DiagnosticMessage>
_0_is_referenced_directly_or_indirectly_in_its_own_type_annotation() {
  return diag(
      2502, DiagnosticCategory::Error,
      "_0_is_referenced_directly_or_indirectly_in_its_own_type_annotation_2502",
      "'{0}' is referenced directly or indirectly in its own type annotation.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_namespace_0() {
  return diag(2503, DiagnosticCategory::Error, "Cannot_find_namespace_0_2503",
              "Cannot find namespace '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_must_have_a_Symbol_asyncIterator_method_that_returns_an_async_iterator() {
  return diag(2504, DiagnosticCategory::Error,
              "Type_0_must_have_a_Symbol_asyncIterator_method_that_returns_an_"
              "async_iterator_2504",
              "Type '{0}' must have a '[Symbol.asyncIterator]()' method that "
              "returns an async iterator.");
};
static shared_ptr<DiagnosticMessage>
A_generator_cannot_have_a_void_type_annotation() {
  return diag(2505, DiagnosticCategory::Error,
              "A_generator_cannot_have_a_void_type_annotation_2505",
              "A generator cannot have a 'void' type annotation.");
};
static shared_ptr<DiagnosticMessage>
_0_is_referenced_directly_or_indirectly_in_its_own_base_expression() {
  return diag(
      2506, DiagnosticCategory::Error,
      "_0_is_referenced_directly_or_indirectly_in_its_own_base_expression_2506",
      "'{0}' is referenced directly or indirectly in its own base expression.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_a_constructor_function_type() {
  return diag(2507, DiagnosticCategory::Error,
              "Type_0_is_not_a_constructor_function_type_2507",
              "Type '{0}' is not a constructor function type.");
};
static shared_ptr<DiagnosticMessage>
No_base_constructor_has_the_specified_number_of_type_arguments() {
  return diag(
      2508, DiagnosticCategory::Error,
      "No_base_constructor_has_the_specified_number_of_type_arguments_2508",
      "No base constructor has the specified number of type arguments.");
};
static shared_ptr<DiagnosticMessage>
Base_constructor_return_type_0_is_not_an_object_type_or_intersection_of_object_types_with_statically_known_members() {
  return diag(2509, DiagnosticCategory::Error,
              "Base_constructor_return_type_0_is_not_an_object_type_or_"
              "intersection_of_object_types_with_statically_2509",
              "Base constructor return type '{0}' is not an object type or "
              "intersection of object types with statically known members.");
};
static shared_ptr<DiagnosticMessage>
Base_constructors_must_all_have_the_same_return_type() {
  return diag(2510, DiagnosticCategory::Error,
              "Base_constructors_must_all_have_the_same_return_type_2510",
              "Base constructors must all have the same return type.");
};
static shared_ptr<DiagnosticMessage>
Cannot_create_an_instance_of_an_abstract_class() {
  return diag(2511, DiagnosticCategory::Error,
              "Cannot_create_an_instance_of_an_abstract_class_2511",
              "Cannot create an instance of an abstract class.");
};
static shared_ptr<DiagnosticMessage>
Overload_signatures_must_all_be_abstract_or_non_abstract() {
  return diag(2512, DiagnosticCategory::Error,
              "Overload_signatures_must_all_be_abstract_or_non_abstract_2512",
              "Overload signatures must all be abstract or non-abstract.");
};
static shared_ptr<DiagnosticMessage>
Abstract_method_0_in_class_1_cannot_be_accessed_via_super_expression() {
  return diag(2513, DiagnosticCategory::Error,
              "Abstract_method_0_in_class_1_cannot_be_accessed_via_super_"
              "expression_2513",
              "Abstract method '{0}' in class '{1}' cannot be accessed via "
              "super expression.");
};
static shared_ptr<DiagnosticMessage>
Non_abstract_class_0_does_not_implement_inherited_abstract_member_1_from_class_2() {
  return diag(2515, DiagnosticCategory::Error,
              "Non_abstract_class_0_does_not_implement_inherited_abstract_"
              "member_1_from_class_2_2515",
              "Non-abstract class '{0}' does not implement inherited abstract "
              "member '{1}' from class '{2}'.");
};
static shared_ptr<DiagnosticMessage>
All_declarations_of_an_abstract_method_must_be_consecutive() {
  return diag(2516, DiagnosticCategory::Error,
              "All_declarations_of_an_abstract_method_must_be_consecutive_2516",
              "All declarations of an abstract method must be consecutive.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_an_abstract_constructor_type_to_a_non_abstract_constructor_type() {
  return diag(2517, DiagnosticCategory::Error,
              "Cannot_assign_an_abstract_constructor_type_to_a_non_abstract_"
              "constructor_type_2517",
              "Cannot assign an abstract constructor type to a non-abstract "
              "constructor type.");
};
static shared_ptr<DiagnosticMessage>
A_this_based_type_guard_is_not_compatible_with_a_parameter_based_type_guard() {
  return diag(2518, DiagnosticCategory::Error,
              "A_this_based_type_guard_is_not_compatible_with_a_parameter_"
              "based_type_guard_2518",
              "A 'this'-based type guard is not compatible with a "
              "parameter-based type guard.");
};
static shared_ptr<DiagnosticMessage>
An_async_iterator_must_have_a_next_method() {
  return diag(2519, DiagnosticCategory::Error,
              "An_async_iterator_must_have_a_next_method_2519",
              "An async iterator must have a 'next()' method.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_0_Compiler_uses_declaration_1_to_support_async_functions() {
  return diag(2520, DiagnosticCategory::Error,
              "Duplicate_identifier_0_Compiler_uses_declaration_1_to_support_"
              "async_functions_2520",
              "Duplicate identifier '{0}'. Compiler uses declaration '{1}' to "
              "support async functions.");
};
static shared_ptr<DiagnosticMessage>
The_arguments_object_cannot_be_referenced_in_an_async_function_or_method_in_ES3_and_ES5_Consider_using_a_standard_function_or_method() {
  return diag(
      2522, DiagnosticCategory::Error,
      "The_arguments_object_cannot_be_referenced_in_an_async_function_or_"
      "method_in_ES3_and_ES5_Consider_usi_2522",
      "The 'arguments' object cannot be referenced in an async function or "
      "method in ES3 and ES5. Consider using a standard function or method.");
};
static shared_ptr<DiagnosticMessage>
yield_expressions_cannot_be_used_in_a_parameter_initializer() {
  return diag(
      2523, DiagnosticCategory::Error,
      "yield_expressions_cannot_be_used_in_a_parameter_initializer_2523",
      "'yield' expressions cannot be used in a parameter initializer.");
};
static shared_ptr<DiagnosticMessage>
await_expressions_cannot_be_used_in_a_parameter_initializer() {
  return diag(
      2524, DiagnosticCategory::Error,
      "await_expressions_cannot_be_used_in_a_parameter_initializer_2524",
      "'await' expressions cannot be used in a parameter initializer.");
};
static shared_ptr<DiagnosticMessage>
Initializer_provides_no_value_for_this_binding_element_and_the_binding_element_has_no_default_value() {
  return diag(2525, DiagnosticCategory::Error,
              "Initializer_provides_no_value_for_this_binding_element_and_the_"
              "binding_element_has_no_default_value_2525",
              "Initializer provides no value for this binding element and the "
              "binding element has no default value.");
};
static shared_ptr<DiagnosticMessage>
A_this_type_is_available_only_in_a_non_static_member_of_a_class_or_interface() {
  return diag(2526, DiagnosticCategory::Error,
              "A_this_type_is_available_only_in_a_non_static_member_of_a_class_"
              "or_interface_2526",
              "A 'this' type is available only in a non-static member of a "
              "class or interface.");
};
static shared_ptr<DiagnosticMessage>
The_inferred_type_of_0_references_an_inaccessible_1_type_A_type_annotation_is_necessary() {
  return diag(2527, DiagnosticCategory::Error,
              "The_inferred_type_of_0_references_an_inaccessible_1_type_A_type_"
              "annotation_is_necessary_2527",
              "The inferred type of '{0}' references an inaccessible '{1}' "
              "type. A type annotation is necessary.");
};
static shared_ptr<DiagnosticMessage>
A_module_cannot_have_multiple_default_exports() {
  return diag(2528, DiagnosticCategory::Error,
              "A_module_cannot_have_multiple_default_exports_2528",
              "A module cannot have multiple default exports.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_0_Compiler_reserves_name_1_in_top_level_scope_of_a_module_containing_async_functions() {
  return diag(2529, DiagnosticCategory::Error,
              "Duplicate_identifier_0_Compiler_reserves_name_1_in_top_level_"
              "scope_of_a_module_containing_async_func_2529",
              "Duplicate identifier '{0}'. Compiler reserves name '{1}' in top "
              "level scope of a module containing async functions.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_incompatible_with_index_signature() {
  return diag(2530, DiagnosticCategory::Error,
              "Property_0_is_incompatible_with_index_signature_2530",
              "Property '{0}' is incompatible with index signature.");
};
static shared_ptr<DiagnosticMessage> Object_is_possibly_null() {
  return diag(2531, DiagnosticCategory::Error, "Object_is_possibly_null_2531",
              "Object is possibly 'null'.");
};
static shared_ptr<DiagnosticMessage> Object_is_possibly_undefined() {
  return diag(2532, DiagnosticCategory::Error,
              "Object_is_possibly_undefined_2532",
              "Object is possibly 'undefined'.");
};
static shared_ptr<DiagnosticMessage> Object_is_possibly_null_or_undefined() {
  return diag(2533, DiagnosticCategory::Error,
              "Object_is_possibly_null_or_undefined_2533",
              "Object is possibly 'null' or 'undefined'.");
};
static shared_ptr<DiagnosticMessage>
A_function_returning_never_cannot_have_a_reachable_end_point() {
  return diag(
      2534, DiagnosticCategory::Error,
      "A_function_returning_never_cannot_have_a_reachable_end_point_2534",
      "A function returning 'never' cannot have a reachable end point.");
};
static shared_ptr<DiagnosticMessage>
Enum_type_0_has_members_with_initializers_that_are_not_literals() {
  return diag(
      2535, DiagnosticCategory::Error,
      "Enum_type_0_has_members_with_initializers_that_are_not_literals_2535",
      "Enum type '{0}' has members with initializers that are not literals.");
};
static shared_ptr<DiagnosticMessage> Type_0_cannot_be_used_to_index_type_1() {
  return diag(2536, DiagnosticCategory::Error,
              "Type_0_cannot_be_used_to_index_type_1_2536",
              "Type '{0}' cannot be used to index type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_has_no_matching_index_signature_for_type_1() {
  return diag(2537, DiagnosticCategory::Error,
              "Type_0_has_no_matching_index_signature_for_type_1_2537",
              "Type '{0}' has no matching index signature for type '{1}'.");
};
static shared_ptr<DiagnosticMessage> Type_0_cannot_be_used_as_an_index_type() {
  return diag(2538, DiagnosticCategory::Error,
              "Type_0_cannot_be_used_as_an_index_type_2538",
              "Type '{0}' cannot be used as an index type.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_not_a_variable() {
  return diag(2539, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_not_a_variable_2539",
              "Cannot assign to '{0}' because it is not a variable.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_a_read_only_property() {
  return diag(2540, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_a_read_only_property_2540",
              "Cannot assign to '{0}' because it is a read-only property.");
};
static shared_ptr<DiagnosticMessage>
Index_signature_in_type_0_only_permits_reading() {
  return diag(2542, DiagnosticCategory::Error,
              "Index_signature_in_type_0_only_permits_reading_2542",
              "Index signature in type '{0}' only permits reading.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_newTarget_Compiler_uses_variable_declaration_newTarget_to_capture_new_target_meta_property_reference() {
  return diag(
      2543, DiagnosticCategory::Error,
      "Duplicate_identifier_newTarget_Compiler_uses_variable_declaration_"
      "newTarget_to_capture_new_target_me_2543",
      "Duplicate identifier '_newTarget'. Compiler uses variable declaration "
      "'_newTarget' to capture 'new.target' meta-property reference.");
};
static shared_ptr<DiagnosticMessage>
Expression_resolves_to_variable_declaration_newTarget_that_compiler_uses_to_capture_new_target_meta_property_reference() {
  return diag(2544, DiagnosticCategory::Error,
              "Expression_resolves_to_variable_declaration_newTarget_that_"
              "compiler_uses_to_capture_new_target_meta__2544",
              "Expression resolves to variable declaration '_newTarget' that "
              "compiler uses to capture 'new.target' meta-property reference.");
};
static shared_ptr<DiagnosticMessage>
A_mixin_class_must_have_a_constructor_with_a_single_rest_parameter_of_type_any() {
  return diag(2545, DiagnosticCategory::Error,
              "A_mixin_class_must_have_a_constructor_with_a_single_rest_"
              "parameter_of_type_any_2545",
              "A mixin class must have a constructor with a single rest "
              "parameter of type 'any[]'.");
};
static shared_ptr<DiagnosticMessage>
The_type_returned_by_the_0_method_of_an_async_iterator_must_be_a_promise_for_a_type_with_a_value_property() {
  return diag(2547, DiagnosticCategory::Error,
              "The_type_returned_by_the_0_method_of_an_async_iterator_must_be_"
              "a_promise_for_a_type_with_a_value_pro_2547",
              "The type returned by the '{0}()' method of an async iterator "
              "must be a promise for a type with a 'value' property.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_an_array_type_or_does_not_have_a_Symbol_iterator_method_that_returns_an_iterator() {
  return diag(2548, DiagnosticCategory::Error,
              "Type_0_is_not_an_array_type_or_does_not_have_a_Symbol_iterator_"
              "method_that_returns_an_iterator_2548",
              "Type '{0}' is not an array type or does not have a "
              "'[Symbol.iterator]()' method that returns an iterator.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_an_array_type_or_a_string_type_or_does_not_have_a_Symbol_iterator_method_that_returns_an_iterator() {
  return diag(2549, DiagnosticCategory::Error,
              "Type_0_is_not_an_array_type_or_a_string_type_or_does_not_have_a_"
              "Symbol_iterator_method_that_returns__2549",
              "Type '{0}' is not an array type or a string type or does not "
              "have a '[Symbol.iterator]()' method that returns an iterator.");
};
static shared_ptr<DiagnosticMessage>
Property_0_does_not_exist_on_type_1_Do_you_need_to_change_your_target_library_Try_changing_the_lib_compiler_option_to_2_or_later() {
  return diag(2550, DiagnosticCategory::Error,
              "Property_0_does_not_exist_on_type_1_Do_you_need_to_change_your_"
              "target_library_Try_changing_the_lib_c_2550",
              "Property '{0}' does not exist on type '{1}'. Do you need to "
              "change your target library? Try changing the 'lib' compiler "
              "option to '{2}' or later.");
};
static shared_ptr<DiagnosticMessage>
Property_0_does_not_exist_on_type_1_Did_you_mean_2() {
  return diag(
      2551, DiagnosticCategory::Error,
      "Property_0_does_not_exist_on_type_1_Did_you_mean_2_2551",
      "Property '{0}' does not exist on type '{1}'. Did you mean '{2}'?");
};
static shared_ptr<DiagnosticMessage> Cannot_find_name_0_Did_you_mean_1() {
  return diag(2552, DiagnosticCategory::Error,
              "Cannot_find_name_0_Did_you_mean_1_2552",
              "Cannot find name '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Computed_values_are_not_permitted_in_an_enum_with_string_valued_members() {
  return diag(2553, DiagnosticCategory::Error,
              "Computed_values_are_not_permitted_in_an_enum_with_string_valued_"
              "members_2553",
              "Computed values are not permitted in an enum with string valued "
              "members.");
};
static shared_ptr<DiagnosticMessage> Expected_0_arguments_but_got_1() {
  return diag(2554, DiagnosticCategory::Error,
              "Expected_0_arguments_but_got_1_2554",
              "Expected {0} arguments, but got {1}.");
};
static shared_ptr<DiagnosticMessage> Expected_at_least_0_arguments_but_got_1() {
  return diag(2555, DiagnosticCategory::Error,
              "Expected_at_least_0_arguments_but_got_1_2555",
              "Expected at least {0} arguments, but got {1}.");
};
static shared_ptr<DiagnosticMessage>
A_spread_argument_must_either_have_a_tuple_type_or_be_passed_to_a_rest_parameter() {
  return diag(2556, DiagnosticCategory::Error,
              "A_spread_argument_must_either_have_a_tuple_type_or_be_passed_to_"
              "a_rest_parameter_2556",
              "A spread argument must either have a tuple type or be passed to "
              "a rest parameter.");
};
static shared_ptr<DiagnosticMessage> Expected_0_type_arguments_but_got_1() {
  return diag(2558, DiagnosticCategory::Error,
              "Expected_0_type_arguments_but_got_1_2558",
              "Expected {0} type arguments, but got {1}.");
};
static shared_ptr<DiagnosticMessage>
Type_0_has_no_properties_in_common_with_type_1() {
  return diag(2559, DiagnosticCategory::Error,
              "Type_0_has_no_properties_in_common_with_type_1_2559",
              "Type '{0}' has no properties in common with type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Value_of_type_0_has_no_properties_in_common_with_type_1_Did_you_mean_to_call_it() {
  return diag(2560, DiagnosticCategory::Error,
              "Value_of_type_0_has_no_properties_in_common_with_type_1_Did_you_"
              "mean_to_call_it_2560",
              "Value of type '{0}' has no properties in common with type "
              "'{1}'. Did you mean to call it?");
};
static shared_ptr<DiagnosticMessage>
Object_literal_may_only_specify_known_properties_but_0_does_not_exist_in_type_1_Did_you_mean_to_write_2() {
  return diag(2561, DiagnosticCategory::Error,
              "Object_literal_may_only_specify_known_properties_but_0_does_not_"
              "exist_in_type_1_Did_you_mean_to_writ_2561",
              "Object literal may only specify known properties, but '{0}' "
              "does not exist in type '{1}'. Did you mean to write '{2}'?");
};
static shared_ptr<DiagnosticMessage>
Base_class_expressions_cannot_reference_class_type_parameters() {
  return diag(
      2562, DiagnosticCategory::Error,
      "Base_class_expressions_cannot_reference_class_type_parameters_2562",
      "Base class expressions cannot reference class type parameters.");
};
static shared_ptr<DiagnosticMessage>
The_containing_function_or_module_body_is_too_large_for_control_flow_analysis() {
  return diag(2563, DiagnosticCategory::Error,
              "The_containing_function_or_module_body_is_too_large_for_control_"
              "flow_analysis_2563",
              "The containing function or module body is too large for control "
              "flow analysis.");
};
static shared_ptr<DiagnosticMessage>
Property_0_has_no_initializer_and_is_not_definitely_assigned_in_the_constructor() {
  return diag(2564, DiagnosticCategory::Error,
              "Property_0_has_no_initializer_and_is_not_definitely_assigned_in_"
              "the_constructor_2564",
              "Property '{0}' has no initializer and is not definitely "
              "assigned in the constructor.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_used_before_being_assigned() {
  return diag(2565, DiagnosticCategory::Error,
              "Property_0_is_used_before_being_assigned_2565",
              "Property '{0}' is used before being assigned.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_cannot_have_a_property_name() {
  return diag(2566, DiagnosticCategory::Error,
              "A_rest_element_cannot_have_a_property_name_2566",
              "A rest element cannot have a property name.");
};
static shared_ptr<DiagnosticMessage>
Enum_declarations_can_only_merge_with_namespace_or_other_enum_declarations() {
  return diag(2567, DiagnosticCategory::Error,
              "Enum_declarations_can_only_merge_with_namespace_or_other_enum_"
              "declarations_2567",
              "Enum declarations can only merge with namespace or other enum "
              "declarations.");
};
static shared_ptr<DiagnosticMessage>
Property_0_may_not_exist_on_type_1_Did_you_mean_2() {
  return diag(
      2568, DiagnosticCategory::Error,
      "Property_0_may_not_exist_on_type_1_Did_you_mean_2_2568",
      "Property '{0}' may not exist on type '{1}'. Did you mean '{2}'?");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_an_array_type_or_a_string_type_Use_compiler_option_downlevelIteration_to_allow_iterating_of_iterators() {
  return diag(2569, DiagnosticCategory::Error,
              "Type_0_is_not_an_array_type_or_a_string_type_Use_compiler_"
              "option_downlevelIteration_to_allow_iterati_2569",
              "Type '{0}' is not an array type or a string type. Use compiler "
              "option '--downlevelIteration' to allow iterating of iterators.");
};
static shared_ptr<DiagnosticMessage> Could_not_find_name_0_Did_you_mean_1() {
  return diag(2570, DiagnosticCategory::Error,
              "Could_not_find_name_0_Did_you_mean_1_2570",
              "Could not find name '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage> Object_is_of_type_unknown() {
  return diag(2571, DiagnosticCategory::Error, "Object_is_of_type_unknown_2571",
              "Object is of type 'unknown'.");
};
static shared_ptr<DiagnosticMessage>
A_rest_element_type_must_be_an_array_type() {
  return diag(2574, DiagnosticCategory::Error,
              "A_rest_element_type_must_be_an_array_type_2574",
              "A rest element type must be an array type.");
};
static shared_ptr<DiagnosticMessage>
No_overload_expects_0_arguments_but_overloads_do_exist_that_expect_either_1_or_2_arguments() {
  return diag(2575, DiagnosticCategory::Error,
              "No_overload_expects_0_arguments_but_overloads_do_exist_that_"
              "expect_either_1_or_2_arguments_2575",
              "No overload expects {0} arguments, but overloads do exist that "
              "expect either {1} or {2} arguments.");
};
static shared_ptr<DiagnosticMessage>
Property_0_does_not_exist_on_type_1_Did_you_mean_to_access_the_static_member_2_instead() {
  return diag(2576, DiagnosticCategory::Error,
              "Property_0_does_not_exist_on_type_1_Did_you_mean_to_access_the_"
              "static_member_2_instead_2576",
              "Property '{0}' does not exist on type '{1}'. Did you mean to "
              "access the static member '{2}' instead?");
};
static shared_ptr<DiagnosticMessage>
Return_type_annotation_circularly_references_itself() {
  return diag(2577, DiagnosticCategory::Error,
              "Return_type_annotation_circularly_references_itself_2577",
              "Return type annotation circularly references itself.");
};
static shared_ptr<DiagnosticMessage> Unused_ts_expect_error_directive() {
  return diag(2578, DiagnosticCategory::Error,
              "Unused_ts_expect_error_directive_2578",
              "Unused '@ts-expect-error' directive.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_node_Try_npm_i_save_dev_types_Slashnode() {
  return diag(2580, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "node_Try_npm_i_save_dev_types_Slashno_2580",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for node? Try `npm i --save-dev @types/node`.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_jQuery_Try_npm_i_save_dev_types_Slashjquery() {
  return diag(2581, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "jQuery_Try_npm_i_save_dev_types_Slash_2581",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for jQuery? Try `npm i --save-dev @types/jquery`.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_a_test_runner_Try_npm_i_save_dev_types_Slashjest_or_npm_i_save_dev_types_Slashmocha() {
  return diag(2582, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "a_test_runner_Try_npm_i_save_dev_type_2582",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for a test runner? Try `npm i --save-dev @types/jest` or `npm i "
              "--save-dev @types/mocha`.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_change_your_target_library_Try_changing_the_lib_compiler_option_to_1_or_later() {
  return diag(
      2583, DiagnosticCategory::Error,
      "Cannot_find_name_0_Do_you_need_to_change_your_target_library_Try_"
      "changing_the_lib_compiler_option_to_2583",
      "Cannot find name '{0}'. Do you need to change your target library? Try "
      "changing the 'lib' compiler option to '{1}' or later.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_change_your_target_library_Try_changing_the_lib_compiler_option_to_include_dom() {
  return diag(
      2584, DiagnosticCategory::Error,
      "Cannot_find_name_0_Do_you_need_to_change_your_target_library_Try_"
      "changing_the_lib_compiler_option_to_2584",
      "Cannot find name '{0}'. Do you need to change your target library? Try "
      "changing the 'lib' compiler option to include 'dom'.");
};
static shared_ptr<DiagnosticMessage>
_0_only_refers_to_a_type_but_is_being_used_as_a_value_here_Do_you_need_to_change_your_target_library_Try_changing_the_lib_compiler_option_to_es2015_or_later() {
  return diag(2585, DiagnosticCategory::Error,
              "_0_only_refers_to_a_type_but_is_being_used_as_a_value_here_Do_"
              "you_need_to_change_your_target_library_2585",
              "'{0}' only refers to a type, but is being used as a value here. "
              "Do you need to change your target library? Try changing the "
              "'lib' compiler option to es2015 or later.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_a_constant() {
  return diag(2588, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_a_constant_2588",
              "Cannot assign to '{0}' because it is a constant.");
};
static shared_ptr<DiagnosticMessage>
Type_instantiation_is_excessively_deep_and_possibly_infinite() {
  return diag(
      2589, DiagnosticCategory::Error,
      "Type_instantiation_is_excessively_deep_and_possibly_infinite_2589",
      "Type instantiation is excessively deep and possibly infinite.");
};
static shared_ptr<DiagnosticMessage>
Expression_produces_a_union_type_that_is_too_complex_to_represent() {
  return diag(
      2590, DiagnosticCategory::Error,
      "Expression_produces_a_union_type_that_is_too_complex_to_represent_2590",
      "Expression produces a union type that is too complex to represent.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_node_Try_npm_i_save_dev_types_Slashnode_and_then_add_node_to_the_types_field_in_your_tsconfig() {
  return diag(2591, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "node_Try_npm_i_save_dev_types_Slashno_2591",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for node? Try `npm i --save-dev @types/node` and then add "
              "'node' to the types field in your tsconfig.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_jQuery_Try_npm_i_save_dev_types_Slashjquery_and_then_add_jquery_to_the_types_field_in_your_tsconfig() {
  return diag(2592, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "jQuery_Try_npm_i_save_dev_types_Slash_2592",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for jQuery? Try `npm i --save-dev @types/jquery` and then add "
              "'jquery' to the types field in your tsconfig.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_a_test_runner_Try_npm_i_save_dev_types_Slashjest_or_npm_i_save_dev_types_Slashmocha_and_then_add_jest_or_mocha_to_the_types_field_in_your_tsconfig() {
  return diag(2593, DiagnosticCategory::Error,
              "Cannot_find_name_0_Do_you_need_to_install_type_definitions_for_"
              "a_test_runner_Try_npm_i_save_dev_type_2593",
              "Cannot find name '{0}'. Do you need to install type definitions "
              "for a test runner? Try `npm i --save-dev @types/jest` or `npm i "
              "--save-dev @types/mocha` and then add 'jest' or 'mocha' to the "
              "types field in your tsconfig.");
};
static shared_ptr<DiagnosticMessage>
This_module_is_declared_with_using_export_and_can_only_be_used_with_a_default_import_when_using_the_0_flag() {
  return diag(2594, DiagnosticCategory::Error,
              "This_module_is_declared_with_using_export_and_can_only_be_used_"
              "with_a_default_import_when_using_the__2594",
              "This module is declared with using 'export =', and can only be "
              "used with a default import when using the '{0}' flag.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_using_a_default_import() {
  return diag(2595, DiagnosticCategory::Error,
              "_0_can_only_be_imported_by_using_a_default_import_2595",
              "'{0}' can only be imported by using a default import.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_turning_on_the_esModuleInterop_flag_and_using_a_default_import() {
  return diag(2596, DiagnosticCategory::Error,
              "_0_can_only_be_imported_by_turning_on_the_esModuleInterop_flag_"
              "and_using_a_default_import_2596",
              "'{0}' can only be imported by turning on the 'esModuleInterop' "
              "flag and using a default import.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_using_a_require_call_or_by_using_a_default_import() {
  return diag(2597, DiagnosticCategory::Error,
              "_0_can_only_be_imported_by_using_a_require_call_or_by_using_a_"
              "default_import_2597",
              "'{0}' can only be imported by using a 'require' call or by "
              "using a default import.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_using_a_require_call_or_by_turning_on_the_esModuleInterop_flag_and_using_a_default_import() {
  return diag(
      2598, DiagnosticCategory::Error,
      "_0_can_only_be_imported_by_using_a_require_call_or_by_turning_on_the_"
      "esModuleInterop_flag_and_using__2598",
      "'{0}' can only be imported by using a 'require' call or by turning on "
      "the 'esModuleInterop' flag and using a default import.");
};
static shared_ptr<DiagnosticMessage>
JSX_element_implicitly_has_type_any_because_the_global_type_JSX_Element_does_not_exist() {
  return diag(2602, DiagnosticCategory::Error,
              "JSX_element_implicitly_has_type_any_because_the_global_type_JSX_"
              "Element_does_not_exist_2602",
              "JSX element implicitly has type 'any' because the global type "
              "'JSX.Element' does not exist.");
};
static shared_ptr<DiagnosticMessage>
Property_0_in_type_1_is_not_assignable_to_type_2() {
  return diag(2603, DiagnosticCategory::Error,
              "Property_0_in_type_1_is_not_assignable_to_type_2_2603",
              "Property '{0}' in type '{1}' is not assignable to type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
JSX_element_type_0_does_not_have_any_construct_or_call_signatures() {
  return diag(
      2604, DiagnosticCategory::Error,
      "JSX_element_type_0_does_not_have_any_construct_or_call_signatures_2604",
      "JSX element type '{0}' does not have any construct or call signatures.");
};
static shared_ptr<DiagnosticMessage>
Property_0_of_JSX_spread_attribute_is_not_assignable_to_target_property() {
  return diag(2606, DiagnosticCategory::Error,
              "Property_0_of_JSX_spread_attribute_is_not_assignable_to_target_"
              "property_2606",
              "Property '{0}' of JSX spread attribute is not assignable to "
              "target property.");
};
static shared_ptr<DiagnosticMessage>
JSX_element_class_does_not_support_attributes_because_it_does_not_have_a_0_property() {
  return diag(2607, DiagnosticCategory::Error,
              "JSX_element_class_does_not_support_attributes_because_it_does_"
              "not_have_a_0_property_2607",
              "JSX element class does not support attributes because it does "
              "not have a '{0}' property.");
};
static shared_ptr<DiagnosticMessage>
The_global_type_JSX_0_may_not_have_more_than_one_property() {
  return diag(2608, DiagnosticCategory::Error,
              "The_global_type_JSX_0_may_not_have_more_than_one_property_2608",
              "The global type 'JSX.{0}' may not have more than one property.");
};
static shared_ptr<DiagnosticMessage> JSX_spread_child_must_be_an_array_type() {
  return diag(2609, DiagnosticCategory::Error,
              "JSX_spread_child_must_be_an_array_type_2609",
              "JSX spread child must be an array type.");
};
static shared_ptr<DiagnosticMessage>
_0_is_defined_as_an_accessor_in_class_1_but_is_overridden_here_in_2_as_an_instance_property() {
  return diag(2610, DiagnosticCategory::Error,
              "_0_is_defined_as_an_accessor_in_class_1_but_is_overridden_here_"
              "in_2_as_an_instance_property_2610",
              "'{0}' is defined as an accessor in class '{1}', but is "
              "overridden here in '{2}' as an instance property.");
};
static shared_ptr<DiagnosticMessage>
_0_is_defined_as_a_property_in_class_1_but_is_overridden_here_in_2_as_an_accessor() {
  return diag(2611, DiagnosticCategory::Error,
              "_0_is_defined_as_a_property_in_class_1_but_is_overridden_here_"
              "in_2_as_an_accessor_2611",
              "'{0}' is defined as a property in class '{1}', but is "
              "overridden here in '{2}' as an accessor.");
};
static shared_ptr<DiagnosticMessage>
Property_0_will_overwrite_the_base_property_in_1_If_this_is_intentional_add_an_initializer_Otherwise_add_a_declare_modifier_or_remove_the_redundant_declaration() {
  return diag(2612, DiagnosticCategory::Error,
              "Property_0_will_overwrite_the_base_property_in_1_If_this_is_"
              "intentional_add_an_initializer_Otherwise_2612",
              "Property '{0}' will overwrite the base property in '{1}'. If "
              "this is intentional, add an initializer. Otherwise, add a "
              "'declare' modifier or remove the redundant declaration.");
};
static shared_ptr<DiagnosticMessage>
Module_0_has_no_default_export_Did_you_mean_to_use_import_1_from_0_instead() {
  return diag(2613, DiagnosticCategory::Error,
              "Module_0_has_no_default_export_Did_you_mean_to_use_import_1_"
              "from_0_instead_2613",
              "Module '{0}' has no default export. Did you mean to use 'import "
              "{ {1} } from {0}' instead?");
};
static shared_ptr<DiagnosticMessage>
Module_0_has_no_exported_member_1_Did_you_mean_to_use_import_1_from_0_instead() {
  return diag(2614, DiagnosticCategory::Error,
              "Module_0_has_no_exported_member_1_Did_you_mean_to_use_import_1_"
              "from_0_instead_2614",
              "Module '{0}' has no exported member '{1}'. Did you mean to use "
              "'import {1} from {0}' instead?");
};
static shared_ptr<DiagnosticMessage>
Type_of_property_0_circularly_references_itself_in_mapped_type_1() {
  return diag(
      2615, DiagnosticCategory::Error,
      "Type_of_property_0_circularly_references_itself_in_mapped_type_1_2615",
      "Type of property '{0}' circularly references itself in mapped type "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_using_import_1_require_2_or_a_default_import() {
  return diag(2616, DiagnosticCategory::Error,
              "_0_can_only_be_imported_by_using_import_1_require_2_or_a_"
              "default_import_2616",
              "'{0}' can only be imported by using 'import {1} = require({2})' "
              "or a default import.");
};
static shared_ptr<DiagnosticMessage>
_0_can_only_be_imported_by_using_import_1_require_2_or_by_turning_on_the_esModuleInterop_flag_and_using_a_default_import() {
  return diag(
      2617, DiagnosticCategory::Error,
      "_0_can_only_be_imported_by_using_import_1_require_2_or_by_turning_on_"
      "the_esModuleInterop_flag_and_us_2617",
      "'{0}' can only be imported by using 'import {1} = require({2})' or by "
      "turning on the 'esModuleInterop' flag and using a default import.");
};
static shared_ptr<DiagnosticMessage>
Source_has_0_element_s_but_target_requires_1() {
  return diag(2618, DiagnosticCategory::Error,
              "Source_has_0_element_s_but_target_requires_1_2618",
              "Source has {0} element(s) but target requires {1}.");
};
static shared_ptr<DiagnosticMessage>
Source_has_0_element_s_but_target_allows_only_1() {
  return diag(2619, DiagnosticCategory::Error,
              "Source_has_0_element_s_but_target_allows_only_1_2619",
              "Source has {0} element(s) but target allows only {1}.");
};
static shared_ptr<DiagnosticMessage>
Target_requires_0_element_s_but_source_may_have_fewer() {
  return diag(2620, DiagnosticCategory::Error,
              "Target_requires_0_element_s_but_source_may_have_fewer_2620",
              "Target requires {0} element(s) but source may have fewer.");
};
static shared_ptr<DiagnosticMessage>
Target_allows_only_0_element_s_but_source_may_have_more() {
  return diag(2621, DiagnosticCategory::Error,
              "Target_allows_only_0_element_s_but_source_may_have_more_2621",
              "Target allows only {0} element(s) but source may have more.");
};
static shared_ptr<DiagnosticMessage>
Source_provides_no_match_for_required_element_at_position_0_in_target() {
  return diag(2623, DiagnosticCategory::Error,
              "Source_provides_no_match_for_required_element_at_position_0_in_"
              "target_2623",
              "Source provides no match for required element at position {0} "
              "in target.");
};
static shared_ptr<DiagnosticMessage>
Source_provides_no_match_for_variadic_element_at_position_0_in_target() {
  return diag(2624, DiagnosticCategory::Error,
              "Source_provides_no_match_for_variadic_element_at_position_0_in_"
              "target_2624",
              "Source provides no match for variadic element at position {0} "
              "in target.");
};
static shared_ptr<DiagnosticMessage>
Variadic_element_at_position_0_in_source_does_not_match_element_at_position_1_in_target() {
  return diag(2625, DiagnosticCategory::Error,
              "Variadic_element_at_position_0_in_source_does_not_match_element_"
              "at_position_1_in_target_2625",
              "Variadic element at position {0} in source does not match "
              "element at position {1} in target.");
};
static shared_ptr<DiagnosticMessage>
Type_at_position_0_in_source_is_not_compatible_with_type_at_position_1_in_target() {
  return diag(2626, DiagnosticCategory::Error,
              "Type_at_position_0_in_source_is_not_compatible_with_type_at_"
              "position_1_in_target_2626",
              "Type at position {0} in source is not compatible with type at "
              "position {1} in target.");
};
static shared_ptr<DiagnosticMessage>
Type_at_positions_0_through_1_in_source_is_not_compatible_with_type_at_position_2_in_target() {
  return diag(2627, DiagnosticCategory::Error,
              "Type_at_positions_0_through_1_in_source_is_not_compatible_with_"
              "type_at_position_2_in_target_2627",
              "Type at positions {0} through {1} in source is not compatible "
              "with type at position {2} in target.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_an_enum() {
  return diag(2628, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_an_enum_2628",
              "Cannot assign to '{0}' because it is an enum.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_a_class() {
  return diag(2629, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_a_class_2629",
              "Cannot assign to '{0}' because it is a class.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_a_function() {
  return diag(2630, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_a_function_2630",
              "Cannot assign to '{0}' because it is a function.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_a_namespace() {
  return diag(2631, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_a_namespace_2631",
              "Cannot assign to '{0}' because it is a namespace.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_0_because_it_is_an_import() {
  return diag(2632, DiagnosticCategory::Error,
              "Cannot_assign_to_0_because_it_is_an_import_2632",
              "Cannot assign to '{0}' because it is an import.");
};
static shared_ptr<DiagnosticMessage>
JSX_property_access_expressions_cannot_include_JSX_namespace_names() {
  return diag(
      2633, DiagnosticCategory::Error,
      "JSX_property_access_expressions_cannot_include_JSX_namespace_names_2633",
      "JSX property access expressions cannot include JSX namespace names");
};
static shared_ptr<DiagnosticMessage> _0_index_signatures_are_incompatible() {
  return diag(2634, DiagnosticCategory::Error,
              "_0_index_signatures_are_incompatible_2634",
              "'{0}' index signatures are incompatible.");
};
static shared_ptr<DiagnosticMessage>
Cannot_augment_module_0_with_value_exports_because_it_resolves_to_a_non_module_entity() {
  return diag(2649, DiagnosticCategory::Error,
              "Cannot_augment_module_0_with_value_exports_because_it_resolves_"
              "to_a_non_module_entity_2649",
              "Cannot augment module '{0}' with value exports because it "
              "resolves to a non-module entity.");
};
static shared_ptr<DiagnosticMessage>
A_member_initializer_in_a_enum_declaration_cannot_reference_members_declared_after_it_including_members_defined_in_other_enums() {
  return diag(
      2651, DiagnosticCategory::Error,
      "A_member_initializer_in_a_enum_declaration_cannot_reference_members_"
      "declared_after_it_including_memb_2651",
      "A member initializer in a enum declaration cannot reference members "
      "declared after it, including members defined in other enums.");
};
static shared_ptr<DiagnosticMessage>
Merged_declaration_0_cannot_include_a_default_export_declaration_Consider_adding_a_separate_export_default_0_declaration_instead() {
  return diag(
      2652, DiagnosticCategory::Error,
      "Merged_declaration_0_cannot_include_a_default_export_declaration_"
      "Consider_adding_a_separate_export_d_2652",
      "Merged declaration '{0}' cannot include a default export declaration. "
      "Consider adding a separate 'export default {0}' declaration instead.");
};
static shared_ptr<DiagnosticMessage>
Non_abstract_class_expression_does_not_implement_inherited_abstract_member_0_from_class_1() {
  return diag(2653, DiagnosticCategory::Error,
              "Non_abstract_class_expression_does_not_implement_inherited_"
              "abstract_member_0_from_class_1_2653",
              "Non-abstract class expression does not implement inherited "
              "abstract member '{0}' from class '{1}'.");
};
static shared_ptr<DiagnosticMessage>
JSX_expressions_must_have_one_parent_element() {
  return diag(2657, DiagnosticCategory::Error,
              "JSX_expressions_must_have_one_parent_element_2657",
              "JSX expressions must have one parent element.");
};
static shared_ptr<DiagnosticMessage>
Type_0_provides_no_match_for_the_signature_1() {
  return diag(2658, DiagnosticCategory::Error,
              "Type_0_provides_no_match_for_the_signature_1_2658",
              "Type '{0}' provides no match for the signature '{1}'.");
};
static shared_ptr<DiagnosticMessage>
super_is_only_allowed_in_members_of_object_literal_expressions_when_option_target_is_ES2015_or_higher() {
  return diag(2659, DiagnosticCategory::Error,
              "super_is_only_allowed_in_members_of_object_literal_expressions_"
              "when_option_target_is_ES2015_or_highe_2659",
              "'super' is only allowed in members of object literal "
              "expressions when option 'target' is 'ES2015' or higher.");
};
static shared_ptr<DiagnosticMessage>
super_can_only_be_referenced_in_members_of_derived_classes_or_object_literal_expressions() {
  return diag(2660, DiagnosticCategory::Error,
              "super_can_only_be_referenced_in_members_of_derived_classes_or_"
              "object_literal_expressions_2660",
              "'super' can only be referenced in members of derived classes or "
              "object literal expressions.");
};
static shared_ptr<DiagnosticMessage>
Cannot_export_0_Only_local_declarations_can_be_exported_from_a_module() {
  return diag(2661, DiagnosticCategory::Error,
              "Cannot_export_0_Only_local_declarations_can_be_exported_from_a_"
              "module_2661",
              "Cannot export '{0}'. Only local declarations can be exported "
              "from a module.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Did_you_mean_the_static_member_1_0() {
  return diag(
      2662, DiagnosticCategory::Error,
      "Cannot_find_name_0_Did_you_mean_the_static_member_1_0_2662",
      "Cannot find name '{0}'. Did you mean the static member '{1}.{0}'?");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_name_0_Did_you_mean_the_instance_member_this_0() {
  return diag(
      2663, DiagnosticCategory::Error,
      "Cannot_find_name_0_Did_you_mean_the_instance_member_this_0_2663",
      "Cannot find name '{0}'. Did you mean the instance member 'this.{0}'?");
};
static shared_ptr<DiagnosticMessage>
Invalid_module_name_in_augmentation_module_0_cannot_be_found() {
  return diag(
      2664, DiagnosticCategory::Error,
      "Invalid_module_name_in_augmentation_module_0_cannot_be_found_2664",
      "Invalid module name in augmentation, module '{0}' cannot be found.");
};
static shared_ptr<DiagnosticMessage>
Invalid_module_name_in_augmentation_Module_0_resolves_to_an_untyped_module_at_1_which_cannot_be_augmented() {
  return diag(2665, DiagnosticCategory::Error,
              "Invalid_module_name_in_augmentation_Module_0_resolves_to_an_"
              "untyped_module_at_1_which_cannot_be_augm_2665",
              "Invalid module name in augmentation. Module '{0}' resolves to "
              "an untyped module at '{1}', which cannot be augmented.");
};
static shared_ptr<DiagnosticMessage>
Exports_and_export_assignments_are_not_permitted_in_module_augmentations() {
  return diag(2666, DiagnosticCategory::Error,
              "Exports_and_export_assignments_are_not_permitted_in_module_"
              "augmentations_2666",
              "Exports and export assignments are not permitted in module "
              "augmentations.");
};
static shared_ptr<DiagnosticMessage>
Imports_are_not_permitted_in_module_augmentations_Consider_moving_them_to_the_enclosing_external_module() {
  return diag(2667, DiagnosticCategory::Error,
              "Imports_are_not_permitted_in_module_augmentations_Consider_"
              "moving_them_to_the_enclosing_external_mod_2667",
              "Imports are not permitted in module augmentations. Consider "
              "moving them to the enclosing external module.");
};
static shared_ptr<DiagnosticMessage>
export_modifier_cannot_be_applied_to_ambient_modules_and_module_augmentations_since_they_are_always_visible() {
  return diag(2668, DiagnosticCategory::Error,
              "export_modifier_cannot_be_applied_to_ambient_modules_and_module_"
              "augmentations_since_they_are_always__2668",
              "'export' modifier cannot be applied to ambient modules and "
              "module augmentations since they are always visible.");
};
static shared_ptr<DiagnosticMessage>
Augmentations_for_the_global_scope_can_only_be_directly_nested_in_external_modules_or_ambient_module_declarations() {
  return diag(2669, DiagnosticCategory::Error,
              "Augmentations_for_the_global_scope_can_only_be_directly_nested_"
              "in_external_modules_or_ambient_module_2669",
              "Augmentations for the global scope can only be directly nested "
              "in external modules or ambient module declarations.");
};
static shared_ptr<DiagnosticMessage>
Augmentations_for_the_global_scope_should_have_declare_modifier_unless_they_appear_in_already_ambient_context() {
  return diag(2670, DiagnosticCategory::Error,
              "Augmentations_for_the_global_scope_should_have_declare_modifier_"
              "unless_they_appear_in_already_ambien_2670",
              "Augmentations for the global scope should have 'declare' "
              "modifier unless they appear in already ambient context.");
};
static shared_ptr<DiagnosticMessage>
Cannot_augment_module_0_because_it_resolves_to_a_non_module_entity() {
  return diag(
      2671, DiagnosticCategory::Error,
      "Cannot_augment_module_0_because_it_resolves_to_a_non_module_entity_2671",
      "Cannot augment module '{0}' because it resolves to a non-module "
      "entity.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_a_0_constructor_type_to_a_1_constructor_type() {
  return diag(
      2672, DiagnosticCategory::Error,
      "Cannot_assign_a_0_constructor_type_to_a_1_constructor_type_2672",
      "Cannot assign a '{0}' constructor type to a '{1}' constructor type.");
};
static shared_ptr<DiagnosticMessage>
Constructor_of_class_0_is_private_and_only_accessible_within_the_class_declaration() {
  return diag(2673, DiagnosticCategory::Error,
              "Constructor_of_class_0_is_private_and_only_accessible_within_"
              "the_class_declaration_2673",
              "Constructor of class '{0}' is private and only accessible "
              "within the class declaration.");
};
static shared_ptr<DiagnosticMessage>
Constructor_of_class_0_is_protected_and_only_accessible_within_the_class_declaration() {
  return diag(2674, DiagnosticCategory::Error,
              "Constructor_of_class_0_is_protected_and_only_accessible_within_"
              "the_class_declaration_2674",
              "Constructor of class '{0}' is protected and only accessible "
              "within the class declaration.");
};
static shared_ptr<DiagnosticMessage>
Cannot_extend_a_class_0_Class_constructor_is_marked_as_private() {
  return diag(
      2675, DiagnosticCategory::Error,
      "Cannot_extend_a_class_0_Class_constructor_is_marked_as_private_2675",
      "Cannot extend a class '{0}'. Class constructor is marked as private.");
};
static shared_ptr<DiagnosticMessage>
Accessors_must_both_be_abstract_or_non_abstract() {
  return diag(2676, DiagnosticCategory::Error,
              "Accessors_must_both_be_abstract_or_non_abstract_2676",
              "Accessors must both be abstract or non-abstract.");
};
static shared_ptr<DiagnosticMessage>
A_type_predicate_s_type_must_be_assignable_to_its_parameter_s_type() {
  return diag(
      2677, DiagnosticCategory::Error,
      "A_type_predicate_s_type_must_be_assignable_to_its_parameter_s_type_2677",
      "A type predicate's type must be assignable to its parameter's type.");
};
static shared_ptr<DiagnosticMessage> Type_0_is_not_comparable_to_type_1() {
  return diag(2678, DiagnosticCategory::Error,
              "Type_0_is_not_comparable_to_type_1_2678",
              "Type '{0}' is not comparable to type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
A_function_that_is_called_with_the_new_keyword_cannot_have_a_this_type_that_is_void() {
  return diag(2679, DiagnosticCategory::Error,
              "A_function_that_is_called_with_the_new_keyword_cannot_have_a_"
              "this_type_that_is_void_2679",
              "A function that is called with the 'new' keyword cannot have a "
              "'this' type that is 'void'.");
};
static shared_ptr<DiagnosticMessage>
A_0_parameter_must_be_the_first_parameter() {
  return diag(2680, DiagnosticCategory::Error,
              "A_0_parameter_must_be_the_first_parameter_2680",
              "A '{0}' parameter must be the first parameter.");
};
static shared_ptr<DiagnosticMessage>
A_constructor_cannot_have_a_this_parameter() {
  return diag(2681, DiagnosticCategory::Error,
              "A_constructor_cannot_have_a_this_parameter_2681",
              "A constructor cannot have a 'this' parameter.");
};
static shared_ptr<DiagnosticMessage>
this_implicitly_has_type_any_because_it_does_not_have_a_type_annotation() {
  return diag(2683, DiagnosticCategory::Error,
              "this_implicitly_has_type_any_because_it_does_not_have_a_type_"
              "annotation_2683",
              "'this' implicitly has type 'any' because it does not have a "
              "type annotation.");
};
static shared_ptr<DiagnosticMessage>
The_this_context_of_type_0_is_not_assignable_to_method_s_this_of_type_1() {
  return diag(2684, DiagnosticCategory::Error,
              "The_this_context_of_type_0_is_not_assignable_to_method_s_this_"
              "of_type_1_2684",
              "The 'this' context of type '{0}' is not assignable to method's "
              "'this' of type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
The_this_types_of_each_signature_are_incompatible() {
  return diag(2685, DiagnosticCategory::Error,
              "The_this_types_of_each_signature_are_incompatible_2685",
              "The 'this' types of each signature are incompatible.");
};
static shared_ptr<DiagnosticMessage>
_0_refers_to_a_UMD_global_but_the_current_file_is_a_module_Consider_adding_an_import_instead() {
  return diag(2686, DiagnosticCategory::Error,
              "_0_refers_to_a_UMD_global_but_the_current_file_is_a_module_"
              "Consider_adding_an_import_instead_2686",
              "'{0}' refers to a UMD global, but the current file is a module. "
              "Consider adding an import instead.");
};
static shared_ptr<DiagnosticMessage>
All_declarations_of_0_must_have_identical_modifiers() {
  return diag(2687, DiagnosticCategory::Error,
              "All_declarations_of_0_must_have_identical_modifiers_2687",
              "All declarations of '{0}' must have identical modifiers.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_type_definition_file_for_0() {
  return diag(2688, DiagnosticCategory::Error,
              "Cannot_find_type_definition_file_for_0_2688",
              "Cannot find type definition file for '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_extend_an_interface_0_Did_you_mean_implements() {
  return diag(2689, DiagnosticCategory::Error,
              "Cannot_extend_an_interface_0_Did_you_mean_implements_2689",
              "Cannot extend an interface '{0}'. Did you mean 'implements'?");
};
static shared_ptr<DiagnosticMessage>
_0_only_refers_to_a_type_but_is_being_used_as_a_value_here_Did_you_mean_to_use_1_in_0() {
  return diag(2690, DiagnosticCategory::Error,
              "_0_only_refers_to_a_type_but_is_being_used_as_a_value_here_Did_"
              "you_mean_to_use_1_in_0_2690",
              "'{0}' only refers to a type, but is being used as a value here. "
              "Did you mean to use '{1} in {0}'?");
};
static shared_ptr<DiagnosticMessage>
An_import_path_cannot_end_with_a_0_extension_Consider_importing_1_instead() {
  return diag(2691, DiagnosticCategory::Error,
              "An_import_path_cannot_end_with_a_0_extension_Consider_importing_"
              "1_instead_2691",
              "An import path cannot end with a '{0}' extension. Consider "
              "importing '{1}' instead.");
};
static shared_ptr<DiagnosticMessage>
_0_is_a_primitive_but_1_is_a_wrapper_object_Prefer_using_0_when_possible() {
  return diag(2692, DiagnosticCategory::Error,
              "_0_is_a_primitive_but_1_is_a_wrapper_object_Prefer_using_0_when_"
              "possible_2692",
              "'{0}' is a primitive, but '{1}' is a wrapper object. Prefer "
              "using '{0}' when possible.");
};
static shared_ptr<DiagnosticMessage>
_0_only_refers_to_a_type_but_is_being_used_as_a_value_here() {
  return diag(
      2693, DiagnosticCategory::Error,
      "_0_only_refers_to_a_type_but_is_being_used_as_a_value_here_2693",
      "'{0}' only refers to a type, but is being used as a value here.");
};
static shared_ptr<DiagnosticMessage> Namespace_0_has_no_exported_member_1() {
  return diag(2694, DiagnosticCategory::Error,
              "Namespace_0_has_no_exported_member_1_2694",
              "Namespace '{0}' has no exported member '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Left_side_of_comma_operator_is_unused_and_has_no_side_effects() {
  return diag(
      2695, DiagnosticCategory::Error,
      "Left_side_of_comma_operator_is_unused_and_has_no_side_effects_2695",
      "Left side of comma operator is unused and has no side effects.",
      /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage>
The_Object_type_is_assignable_to_very_few_other_types_Did_you_mean_to_use_the_any_type_instead() {
  return diag(2696, DiagnosticCategory::Error,
              "The_Object_type_is_assignable_to_very_few_other_types_Did_you_"
              "mean_to_use_the_any_type_instead_2696",
              "The 'Object' type is assignable to very few other types. Did "
              "you mean to use the 'any' type instead?");
};
static shared_ptr<DiagnosticMessage>
An_async_function_or_method_must_return_a_Promise_Make_sure_you_have_a_declaration_for_Promise_or_include_ES2015_in_your_lib_option() {
  return diag(2697, DiagnosticCategory::Error,
              "An_async_function_or_method_must_return_a_Promise_Make_sure_you_"
              "have_a_declaration_for_Promise_or_in_2697",
              "An async function or method must return a 'Promise'. Make sure "
              "you have a declaration for 'Promise' or include 'ES2015' in "
              "your '--lib' option.");
};
static shared_ptr<DiagnosticMessage>
Spread_types_may_only_be_created_from_object_types() {
  return diag(2698, DiagnosticCategory::Error,
              "Spread_types_may_only_be_created_from_object_types_2698",
              "Spread types may only be created from object types.");
};
static shared_ptr<DiagnosticMessage>
Static_property_0_conflicts_with_built_in_property_Function_0_of_constructor_function_1() {
  return diag(2699, DiagnosticCategory::Error,
              "Static_property_0_conflicts_with_built_in_property_Function_0_"
              "of_constructor_function_1_2699",
              "Static property '{0}' conflicts with built-in property "
              "'Function.{0}' of constructor function '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Rest_types_may_only_be_created_from_object_types() {
  return diag(2700, DiagnosticCategory::Error,
              "Rest_types_may_only_be_created_from_object_types_2700",
              "Rest types may only be created from object types.");
};
static shared_ptr<DiagnosticMessage>
The_target_of_an_object_rest_assignment_must_be_a_variable_or_a_property_access() {
  return diag(2701, DiagnosticCategory::Error,
              "The_target_of_an_object_rest_assignment_must_be_a_variable_or_a_"
              "property_access_2701",
              "The target of an object rest assignment must be a variable or a "
              "property access.");
};
static shared_ptr<DiagnosticMessage>
_0_only_refers_to_a_type_but_is_being_used_as_a_namespace_here() {
  return diag(
      2702, DiagnosticCategory::Error,
      "_0_only_refers_to_a_type_but_is_being_used_as_a_namespace_here_2702",
      "'{0}' only refers to a type, but is being used as a namespace here.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_a_delete_operator_must_be_a_property_reference() {
  return diag(
      2703, DiagnosticCategory::Error,
      "The_operand_of_a_delete_operator_must_be_a_property_reference_2703",
      "The operand of a 'delete' operator must be a property reference.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_a_delete_operator_cannot_be_a_read_only_property() {
  return diag(
      2704, DiagnosticCategory::Error,
      "The_operand_of_a_delete_operator_cannot_be_a_read_only_property_2704",
      "The operand of a 'delete' operator cannot be a read-only property.");
};
static shared_ptr<DiagnosticMessage>
An_async_function_or_method_in_ES5_SlashES3_requires_the_Promise_constructor_Make_sure_you_have_a_declaration_for_the_Promise_constructor_or_include_ES2015_in_your_lib_option() {
  return diag(
      2705, DiagnosticCategory::Error,
      "An_async_function_or_method_in_ES5_SlashES3_requires_the_Promise_"
      "constructor_Make_sure_you_have_a_de_2705",
      "An async function or method in ES5/ES3 requires the 'Promise' "
      "constructor.  Make sure you have a declaration for the 'Promise' "
      "constructor or include 'ES2015' in your '--lib' option.");
};
static shared_ptr<DiagnosticMessage>
Required_type_parameters_may_not_follow_optional_type_parameters() {
  return diag(
      2706, DiagnosticCategory::Error,
      "Required_type_parameters_may_not_follow_optional_type_parameters_2706",
      "Required type parameters may not follow optional type parameters.");
};
static shared_ptr<DiagnosticMessage>
Generic_type_0_requires_between_1_and_2_type_arguments() {
  return diag(
      2707, DiagnosticCategory::Error,
      "Generic_type_0_requires_between_1_and_2_type_arguments_2707",
      "Generic type '{0}' requires between {1} and {2} type arguments.");
};
static shared_ptr<DiagnosticMessage> Cannot_use_namespace_0_as_a_value() {
  return diag(2708, DiagnosticCategory::Error,
              "Cannot_use_namespace_0_as_a_value_2708",
              "Cannot use namespace '{0}' as a value.");
};
static shared_ptr<DiagnosticMessage> Cannot_use_namespace_0_as_a_type() {
  return diag(2709, DiagnosticCategory::Error,
              "Cannot_use_namespace_0_as_a_type_2709",
              "Cannot use namespace '{0}' as a type.");
};
static shared_ptr<DiagnosticMessage>
_0_are_specified_twice_The_attribute_named_0_will_be_overwritten() {
  return diag(
      2710, DiagnosticCategory::Error,
      "_0_are_specified_twice_The_attribute_named_0_will_be_overwritten_2710",
      "'{0}' are specified twice. The attribute named '{0}' will be "
      "overwritten.");
};
static shared_ptr<DiagnosticMessage>
A_dynamic_import_call_returns_a_Promise_Make_sure_you_have_a_declaration_for_Promise_or_include_ES2015_in_your_lib_option() {
  return diag(
      2711, DiagnosticCategory::Error,
      "A_dynamic_import_call_returns_a_Promise_Make_sure_you_have_a_"
      "declaration_for_Promise_or_include_ES20_2711",
      "A dynamic import call returns a 'Promise'. Make sure you have a "
      "declaration for 'Promise' or include 'ES2015' in your '--lib' option.");
};
static shared_ptr<DiagnosticMessage>
A_dynamic_import_call_in_ES5_SlashES3_requires_the_Promise_constructor_Make_sure_you_have_a_declaration_for_the_Promise_constructor_or_include_ES2015_in_your_lib_option() {
  return diag(
      2712, DiagnosticCategory::Error,
      "A_dynamic_import_call_in_ES5_SlashES3_requires_the_Promise_constructor_"
      "Make_sure_you_have_a_declarat_2712",
      "A dynamic import call in ES5/ES3 requires the 'Promise' constructor.  "
      "Make sure you have a declaration for the 'Promise' constructor or "
      "include 'ES2015' in your '--lib' option.");
};
static shared_ptr<DiagnosticMessage>
Cannot_access_0_1_because_0_is_a_type_but_not_a_namespace_Did_you_mean_to_retrieve_the_type_of_the_property_1_in_0_with_0_1() {
  return diag(2713, DiagnosticCategory::Error,
              "Cannot_access_0_1_because_0_is_a_type_but_not_a_namespace_Did_"
              "you_mean_to_retrieve_the_type_of_the_p_2713",
              "Cannot access '{0}.{1}' because '{0}' is a type, but not a "
              "namespace. Did you mean to retrieve the type of the property "
              "'{1}' in '{0}' with '{0}[\"{1}\"]'?");
};
static shared_ptr<DiagnosticMessage>
The_expression_of_an_export_assignment_must_be_an_identifier_or_qualified_name_in_an_ambient_context() {
  return diag(2714, DiagnosticCategory::Error,
              "The_expression_of_an_export_assignment_must_be_an_identifier_or_"
              "qualified_name_in_an_ambient_context_2714",
              "The expression of an export assignment must be an identifier or "
              "qualified name in an ambient context.");
};
static shared_ptr<DiagnosticMessage>
Abstract_property_0_in_class_1_cannot_be_accessed_in_the_constructor() {
  return diag(2715, DiagnosticCategory::Error,
              "Abstract_property_0_in_class_1_cannot_be_accessed_in_the_"
              "constructor_2715",
              "Abstract property '{0}' in class '{1}' cannot be accessed in "
              "the constructor.");
};
static shared_ptr<DiagnosticMessage> Type_parameter_0_has_a_circular_default() {
  return diag(2716, DiagnosticCategory::Error,
              "Type_parameter_0_has_a_circular_default_2716",
              "Type parameter '{0}' has a circular default.");
};
static shared_ptr<DiagnosticMessage>
Subsequent_property_declarations_must_have_the_same_type_Property_0_must_be_of_type_1_but_here_has_type_2() {
  return diag(2717, DiagnosticCategory::Error,
              "Subsequent_property_declarations_must_have_the_same_type_"
              "Property_0_must_be_of_type_1_but_here_has_t_2717",
              "Subsequent property declarations must have the same type.  "
              "Property '{0}' must be of type '{1}', but here has type '{2}'.");
};
static shared_ptr<DiagnosticMessage> Duplicate_property_0() {
  return diag(2718, DiagnosticCategory::Error, "Duplicate_property_0_2718",
              "Duplicate property '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_assignable_to_type_1_Two_different_types_with_this_name_exist_but_they_are_unrelated() {
  return diag(2719, DiagnosticCategory::Error,
              "Type_0_is_not_assignable_to_type_1_Two_different_types_with_"
              "this_name_exist_but_they_are_unrelated_2719",
              "Type '{0}' is not assignable to type '{1}'. Two different types "
              "with this name exist, but they are unrelated.");
};
static shared_ptr<DiagnosticMessage>
Class_0_incorrectly_implements_class_1_Did_you_mean_to_extend_1_and_inherit_its_members_as_a_subclass() {
  return diag(2720, DiagnosticCategory::Error,
              "Class_0_incorrectly_implements_class_1_Did_you_mean_to_extend_1_"
              "and_inherit_its_members_as_a_subclas_2720",
              "Class '{0}' incorrectly implements class '{1}'. Did you mean to "
              "extend '{1}' and inherit its members as a subclass?");
};
static shared_ptr<DiagnosticMessage>
Cannot_invoke_an_object_which_is_possibly_null() {
  return diag(2721, DiagnosticCategory::Error,
              "Cannot_invoke_an_object_which_is_possibly_null_2721",
              "Cannot invoke an object which is possibly 'null'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_invoke_an_object_which_is_possibly_undefined() {
  return diag(2722, DiagnosticCategory::Error,
              "Cannot_invoke_an_object_which_is_possibly_undefined_2722",
              "Cannot invoke an object which is possibly 'undefined'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_invoke_an_object_which_is_possibly_null_or_undefined() {
  return diag(
      2723, DiagnosticCategory::Error,
      "Cannot_invoke_an_object_which_is_possibly_null_or_undefined_2723",
      "Cannot invoke an object which is possibly 'null' or 'undefined'.");
};
static shared_ptr<DiagnosticMessage>
_0_has_no_exported_member_named_1_Did_you_mean_2() {
  return diag(2724, DiagnosticCategory::Error,
              "_0_has_no_exported_member_named_1_Did_you_mean_2_2724",
              "'{0}' has no exported member named '{1}'. Did you mean '{2}'?");
};
static shared_ptr<DiagnosticMessage>
Class_name_cannot_be_Object_when_targeting_ES5_with_module_0() {
  return diag(
      2725, DiagnosticCategory::Error,
      "Class_name_cannot_be_Object_when_targeting_ES5_with_module_0_2725",
      "Class name cannot be 'Object' when targeting ES5 with module {0}.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_lib_definition_for_0() {
  return diag(2726, DiagnosticCategory::Error,
              "Cannot_find_lib_definition_for_0_2726",
              "Cannot find lib definition for '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_lib_definition_for_0_Did_you_mean_1() {
  return diag(2727, DiagnosticCategory::Error,
              "Cannot_find_lib_definition_for_0_Did_you_mean_1_2727",
              "Cannot find lib definition for '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage> _0_is_declared_here() {
  return diag(2728, DiagnosticCategory::Message, "_0_is_declared_here_2728",
              "'{0}' is declared here.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_used_before_its_initialization() {
  return diag(2729, DiagnosticCategory::Error,
              "Property_0_is_used_before_its_initialization_2729",
              "Property '{0}' is used before its initialization.");
};
static shared_ptr<DiagnosticMessage>
An_arrow_function_cannot_have_a_this_parameter() {
  return diag(2730, DiagnosticCategory::Error,
              "An_arrow_function_cannot_have_a_this_parameter_2730",
              "An arrow function cannot have a 'this' parameter.");
};
static shared_ptr<DiagnosticMessage>
Implicit_conversion_of_a_symbol_to_a_string_will_fail_at_runtime_Consider_wrapping_this_expression_in_String() {
  return diag(2731, DiagnosticCategory::Error,
              "Implicit_conversion_of_a_symbol_to_a_string_will_fail_at_"
              "runtime_Consider_wrapping_this_expression_i_2731",
              "Implicit conversion of a 'symbol' to a 'string' will fail at "
              "runtime. Consider wrapping this expression in 'String(...)'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_module_0_Consider_using_resolveJsonModule_to_import_module_with_json_extension() {
  return diag(2732, DiagnosticCategory::Error,
              "Cannot_find_module_0_Consider_using_resolveJsonModule_to_import_"
              "module_with_json_extension_2732",
              "Cannot find module '{0}'. Consider using '--resolveJsonModule' "
              "to import module with '.json' extension.");
};
static shared_ptr<DiagnosticMessage> Property_0_was_also_declared_here() {
  return diag(2733, DiagnosticCategory::Error,
              "Property_0_was_also_declared_here_2733",
              "Property '{0}' was also declared here.");
};
static shared_ptr<DiagnosticMessage> Are_you_missing_a_semicolon() {
  return diag(2734, DiagnosticCategory::Error,
              "Are_you_missing_a_semicolon_2734",
              "Are you missing a semicolon?");
};
static shared_ptr<DiagnosticMessage>
Did_you_mean_for_0_to_be_constrained_to_type_new_args_Colon_any_1() {
  return diag(
      2735, DiagnosticCategory::Error,
      "Did_you_mean_for_0_to_be_constrained_to_type_new_args_Colon_any_1_2735",
      "Did you mean for '{0}' to be constrained to type 'new (...args: any[]) "
      "=> {1}'?");
};
static shared_ptr<DiagnosticMessage> Operator_0_cannot_be_applied_to_type_1() {
  return diag(2736, DiagnosticCategory::Error,
              "Operator_0_cannot_be_applied_to_type_1_2736",
              "Operator '{0}' cannot be applied to type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
BigInt_literals_are_not_available_when_targeting_lower_than_ES2020() {
  return diag(
      2737, DiagnosticCategory::Error,
      "BigInt_literals_are_not_available_when_targeting_lower_than_ES2020_2737",
      "BigInt literals are not available when targeting lower than ES2020.");
};
static shared_ptr<DiagnosticMessage>
An_outer_value_of_this_is_shadowed_by_this_container() {
  return diag(2738, DiagnosticCategory::Message,
              "An_outer_value_of_this_is_shadowed_by_this_container_2738",
              "An outer value of 'this' is shadowed by this container.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_missing_the_following_properties_from_type_1_Colon_2() {
  return diag(
      2739, DiagnosticCategory::Error,
      "Type_0_is_missing_the_following_properties_from_type_1_Colon_2_2739",
      "Type '{0}' is missing the following properties from type '{1}': {2}");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_missing_the_following_properties_from_type_1_Colon_2_and_3_more() {
  return diag(2740, DiagnosticCategory::Error,
              "Type_0_is_missing_the_following_properties_from_type_1_Colon_2_"
              "and_3_more_2740",
              "Type '{0}' is missing the following properties from type '{1}': "
              "{2}, and {3} more.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_missing_in_type_1_but_required_in_type_2() {
  return diag(
      2741, DiagnosticCategory::Error,
      "Property_0_is_missing_in_type_1_but_required_in_type_2_2741",
      "Property '{0}' is missing in type '{1}' but required in type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
The_inferred_type_of_0_cannot_be_named_without_a_reference_to_1_This_is_likely_not_portable_A_type_annotation_is_necessary() {
  return diag(
      2742, DiagnosticCategory::Error,
      "The_inferred_type_of_0_cannot_be_named_without_a_reference_to_1_This_is_"
      "likely_not_portable_A_type_a_2742",
      "The inferred type of '{0}' cannot be named without a reference to "
      "'{1}'. This is likely not portable. A type annotation is necessary.");
};
static shared_ptr<DiagnosticMessage>
No_overload_expects_0_type_arguments_but_overloads_do_exist_that_expect_either_1_or_2_type_arguments() {
  return diag(2743, DiagnosticCategory::Error,
              "No_overload_expects_0_type_arguments_but_overloads_do_exist_"
              "that_expect_either_1_or_2_type_arguments_2743",
              "No overload expects {0} type arguments, but overloads do exist "
              "that expect either {1} or {2} type arguments.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_defaults_can_only_reference_previously_declared_type_parameters() {
  return diag(2744, DiagnosticCategory::Error,
              "Type_parameter_defaults_can_only_reference_previously_declared_"
              "type_parameters_2744",
              "Type parameter defaults can only reference previously declared "
              "type parameters.");
};
static shared_ptr<DiagnosticMessage>
This_JSX_tag_s_0_prop_expects_type_1_which_requires_multiple_children_but_only_a_single_child_was_provided() {
  return diag(2745, DiagnosticCategory::Error,
              "This_JSX_tag_s_0_prop_expects_type_1_which_requires_multiple_"
              "children_but_only_a_single_child_was_pr_2745",
              "This JSX tag's '{0}' prop expects type '{1}' which requires "
              "multiple children, but only a single child was provided.");
};
static shared_ptr<DiagnosticMessage>
This_JSX_tag_s_0_prop_expects_a_single_child_of_type_1_but_multiple_children_were_provided() {
  return diag(2746, DiagnosticCategory::Error,
              "This_JSX_tag_s_0_prop_expects_a_single_child_of_type_1_but_"
              "multiple_children_were_provided_2746",
              "This JSX tag's '{0}' prop expects a single child of type '{1}', "
              "but multiple children were provided.");
};
static shared_ptr<DiagnosticMessage>
_0_components_don_t_accept_text_as_child_elements_Text_in_JSX_has_the_type_string_but_the_expected_type_of_1_is_2() {
  return diag(
      2747, DiagnosticCategory::Error,
      "_0_components_don_t_accept_text_as_child_elements_Text_in_JSX_has_the_"
      "type_string_but_the_expected_t_2747",
      "'{0}' components don't accept text as child elements. Text in JSX has "
      "the type 'string', but the expected type of '{1}' is '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_access_ambient_const_enums_when_the_isolatedModules_flag_is_provided() {
  return diag(2748, DiagnosticCategory::Error,
              "Cannot_access_ambient_const_enums_when_the_isolatedModules_flag_"
              "is_provided_2748",
              "Cannot access ambient const enums when the '--isolatedModules' "
              "flag is provided.");
};
static shared_ptr<DiagnosticMessage>
_0_refers_to_a_value_but_is_being_used_as_a_type_here_Did_you_mean_typeof_0() {
  return diag(2749, DiagnosticCategory::Error,
              "_0_refers_to_a_value_but_is_being_used_as_a_type_here_Did_you_"
              "mean_typeof_0_2749",
              "'{0}' refers to a value, but is being used as a type here. Did "
              "you mean 'typeof {0}'?");
};
static shared_ptr<DiagnosticMessage>
The_implementation_signature_is_declared_here() {
  return diag(2750, DiagnosticCategory::Error,
              "The_implementation_signature_is_declared_here_2750",
              "The implementation signature is declared here.");
};
static shared_ptr<DiagnosticMessage>
Circularity_originates_in_type_at_this_location() {
  return diag(2751, DiagnosticCategory::Error,
              "Circularity_originates_in_type_at_this_location_2751",
              "Circularity originates in type at this location.");
};
static shared_ptr<DiagnosticMessage> The_first_export_default_is_here() {
  return diag(2752, DiagnosticCategory::Error,
              "The_first_export_default_is_here_2752",
              "The first export default is here.");
};
static shared_ptr<DiagnosticMessage> Another_export_default_is_here() {
  return diag(2753, DiagnosticCategory::Error,
              "Another_export_default_is_here_2753",
              "Another export default is here.");
};
static shared_ptr<DiagnosticMessage> super_may_not_use_type_arguments() {
  return diag(2754, DiagnosticCategory::Error,
              "super_may_not_use_type_arguments_2754",
              "'super' may not use type arguments.");
};
static shared_ptr<DiagnosticMessage> No_constituent_of_type_0_is_callable() {
  return diag(2755, DiagnosticCategory::Error,
              "No_constituent_of_type_0_is_callable_2755",
              "No constituent of type '{0}' is callable.");
};
static shared_ptr<DiagnosticMessage>
Not_all_constituents_of_type_0_are_callable() {
  return diag(2756, DiagnosticCategory::Error,
              "Not_all_constituents_of_type_0_are_callable_2756",
              "Not all constituents of type '{0}' are callable.");
};
static shared_ptr<DiagnosticMessage> Type_0_has_no_call_signatures() {
  return diag(2757, DiagnosticCategory::Error,
              "Type_0_has_no_call_signatures_2757",
              "Type '{0}' has no call signatures.");
};
static shared_ptr<DiagnosticMessage>
Each_member_of_the_union_type_0_has_signatures_but_none_of_those_signatures_are_compatible_with_each_other() {
  return diag(2758, DiagnosticCategory::Error,
              "Each_member_of_the_union_type_0_has_signatures_but_none_of_"
              "those_signatures_are_compatible_with_each_2758",
              "Each member of the union type '{0}' has signatures, but none of "
              "those signatures are compatible with each other.");
};
static shared_ptr<DiagnosticMessage>
No_constituent_of_type_0_is_constructable() {
  return diag(2759, DiagnosticCategory::Error,
              "No_constituent_of_type_0_is_constructable_2759",
              "No constituent of type '{0}' is constructable.");
};
static shared_ptr<DiagnosticMessage>
Not_all_constituents_of_type_0_are_constructable() {
  return diag(2760, DiagnosticCategory::Error,
              "Not_all_constituents_of_type_0_are_constructable_2760",
              "Not all constituents of type '{0}' are constructable.");
};
static shared_ptr<DiagnosticMessage> Type_0_has_no_construct_signatures() {
  return diag(2761, DiagnosticCategory::Error,
              "Type_0_has_no_construct_signatures_2761",
              "Type '{0}' has no construct signatures.");
};
static shared_ptr<DiagnosticMessage>
Each_member_of_the_union_type_0_has_construct_signatures_but_none_of_those_signatures_are_compatible_with_each_other() {
  return diag(2762, DiagnosticCategory::Error,
              "Each_member_of_the_union_type_0_has_construct_signatures_but_"
              "none_of_those_signatures_are_compatible_2762",
              "Each member of the union type '{0}' has construct signatures, "
              "but none of those signatures are compatible with each other.");
};
static shared_ptr<DiagnosticMessage>
Cannot_iterate_value_because_the_next_method_of_its_iterator_expects_type_1_but_for_of_will_always_send_0() {
  return diag(2763, DiagnosticCategory::Error,
              "Cannot_iterate_value_because_the_next_method_of_its_iterator_"
              "expects_type_1_but_for_of_will_always_s_2763",
              "Cannot iterate value because the 'next' method of its iterator "
              "expects type '{1}', but for-of will always send '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_iterate_value_because_the_next_method_of_its_iterator_expects_type_1_but_array_spread_will_always_send_0() {
  return diag(2764, DiagnosticCategory::Error,
              "Cannot_iterate_value_because_the_next_method_of_its_iterator_"
              "expects_type_1_but_array_spread_will_al_2764",
              "Cannot iterate value because the 'next' method of its iterator "
              "expects type '{1}', but array spread will always send '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_iterate_value_because_the_next_method_of_its_iterator_expects_type_1_but_array_destructuring_will_always_send_0() {
  return diag(
      2765, DiagnosticCategory::Error,
      "Cannot_iterate_value_because_the_next_method_of_its_iterator_expects_"
      "type_1_but_array_destructuring__2765",
      "Cannot iterate value because the 'next' method of its iterator expects "
      "type '{1}', but array destructuring will always send '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_delegate_iteration_to_value_because_the_next_method_of_its_iterator_expects_type_1_but_the_containing_generator_will_always_send_0() {
  return diag(2766, DiagnosticCategory::Error,
              "Cannot_delegate_iteration_to_value_because_the_next_method_of_"
              "its_iterator_expects_type_1_but_the_co_2766",
              "Cannot delegate iteration to value because the 'next' method of "
              "its iterator expects type '{1}', but the containing generator "
              "will always send '{0}'.");
};
static shared_ptr<DiagnosticMessage>
The_0_property_of_an_iterator_must_be_a_method() {
  return diag(2767, DiagnosticCategory::Error,
              "The_0_property_of_an_iterator_must_be_a_method_2767",
              "The '{0}' property of an iterator must be a method.");
};
static shared_ptr<DiagnosticMessage>
The_0_property_of_an_async_iterator_must_be_a_method() {
  return diag(2768, DiagnosticCategory::Error,
              "The_0_property_of_an_async_iterator_must_be_a_method_2768",
              "The '{0}' property of an async iterator must be a method.");
};
static shared_ptr<DiagnosticMessage> No_overload_matches_this_call() {
  return diag(2769, DiagnosticCategory::Error,
              "No_overload_matches_this_call_2769",
              "No overload matches this call.");
};
static shared_ptr<DiagnosticMessage>
The_last_overload_gave_the_following_error() {
  return diag(2770, DiagnosticCategory::Error,
              "The_last_overload_gave_the_following_error_2770",
              "The last overload gave the following error.");
};
static shared_ptr<DiagnosticMessage> The_last_overload_is_declared_here() {
  return diag(2771, DiagnosticCategory::Error,
              "The_last_overload_is_declared_here_2771",
              "The last overload is declared here.");
};
static shared_ptr<DiagnosticMessage>
Overload_0_of_1_2_gave_the_following_error() {
  return diag(2772, DiagnosticCategory::Error,
              "Overload_0_of_1_2_gave_the_following_error_2772",
              "Overload {0} of {1}, '{2}', gave the following error.");
};
static shared_ptr<DiagnosticMessage> Did_you_forget_to_use_await() {
  return diag(2773, DiagnosticCategory::Error,
              "Did_you_forget_to_use_await_2773",
              "Did you forget to use 'await'?");
};
static shared_ptr<DiagnosticMessage>
This_condition_will_always_return_true_since_this_function_is_always_defined_Did_you_mean_to_call_it_instead() {
  return diag(2774, DiagnosticCategory::Error,
              "This_condition_will_always_return_true_since_this_function_is_"
              "always_defined_Did_you_mean_to_call_it_2774",
              "This condition will always return true since this function is "
              "always defined. Did you mean to call it instead?");
};
static shared_ptr<DiagnosticMessage>
Assertions_require_every_name_in_the_call_target_to_be_declared_with_an_explicit_type_annotation() {
  return diag(2775, DiagnosticCategory::Error,
              "Assertions_require_every_name_in_the_call_target_to_be_declared_"
              "with_an_explicit_type_annotation_2775",
              "Assertions require every name in the call target to be declared "
              "with an explicit type annotation.");
};
static shared_ptr<DiagnosticMessage>
Assertions_require_the_call_target_to_be_an_identifier_or_qualified_name() {
  return diag(2776, DiagnosticCategory::Error,
              "Assertions_require_the_call_target_to_be_an_identifier_or_"
              "qualified_name_2776",
              "Assertions require the call target to be an identifier or "
              "qualified name.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_an_increment_or_decrement_operator_may_not_be_an_optional_property_access() {
  return diag(2777, DiagnosticCategory::Error,
              "The_operand_of_an_increment_or_decrement_operator_may_not_be_an_"
              "optional_property_access_2777",
              "The operand of an increment or decrement operator may not be an "
              "optional property access.");
};
static shared_ptr<DiagnosticMessage>
The_target_of_an_object_rest_assignment_may_not_be_an_optional_property_access() {
  return diag(2778, DiagnosticCategory::Error,
              "The_target_of_an_object_rest_assignment_may_not_be_an_optional_"
              "property_access_2778",
              "The target of an object rest assignment may not be an optional "
              "property access.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_an_assignment_expression_may_not_be_an_optional_property_access() {
  return diag(2779, DiagnosticCategory::Error,
              "The_left_hand_side_of_an_assignment_expression_may_not_be_an_"
              "optional_property_access_2779",
              "The left-hand side of an assignment expression may not be an "
              "optional property access.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_in_statement_may_not_be_an_optional_property_access() {
  return diag(2780, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_in_statement_may_not_be_an_optional_"
              "property_access_2780",
              "The left-hand side of a 'for...in' statement may not be an "
              "optional property access.");
};
static shared_ptr<DiagnosticMessage>
The_left_hand_side_of_a_for_of_statement_may_not_be_an_optional_property_access() {
  return diag(2781, DiagnosticCategory::Error,
              "The_left_hand_side_of_a_for_of_statement_may_not_be_an_optional_"
              "property_access_2781",
              "The left-hand side of a 'for...of' statement may not be an "
              "optional property access.");
};
static shared_ptr<DiagnosticMessage> _0_needs_an_explicit_type_annotation() {
  return diag(2782, DiagnosticCategory::Message,
              "_0_needs_an_explicit_type_annotation_2782",
              "'{0}' needs an explicit type annotation.");
};
static shared_ptr<DiagnosticMessage>
_0_is_specified_more_than_once_so_this_usage_will_be_overwritten() {
  return diag(
      2783, DiagnosticCategory::Error,
      "_0_is_specified_more_than_once_so_this_usage_will_be_overwritten_2783",
      "'{0}' is specified more than once, so this usage will be overwritten.");
};
static shared_ptr<DiagnosticMessage>
get_and_set_accessors_cannot_declare_this_parameters() {
  return diag(2784, DiagnosticCategory::Error,
              "get_and_set_accessors_cannot_declare_this_parameters_2784",
              "'get' and 'set' accessors cannot declare 'this' parameters.");
};
static shared_ptr<DiagnosticMessage>
This_spread_always_overwrites_this_property() {
  return diag(2785, DiagnosticCategory::Error,
              "This_spread_always_overwrites_this_property_2785",
              "This spread always overwrites this property.");
};
static shared_ptr<DiagnosticMessage> _0_cannot_be_used_as_a_JSX_component() {
  return diag(2786, DiagnosticCategory::Error,
              "_0_cannot_be_used_as_a_JSX_component_2786",
              "'{0}' cannot be used as a JSX component.");
};
static shared_ptr<DiagnosticMessage>
Its_return_type_0_is_not_a_valid_JSX_element() {
  return diag(2787, DiagnosticCategory::Error,
              "Its_return_type_0_is_not_a_valid_JSX_element_2787",
              "Its return type '{0}' is not a valid JSX element.");
};
static shared_ptr<DiagnosticMessage>
Its_instance_type_0_is_not_a_valid_JSX_element() {
  return diag(2788, DiagnosticCategory::Error,
              "Its_instance_type_0_is_not_a_valid_JSX_element_2788",
              "Its instance type '{0}' is not a valid JSX element.");
};
static shared_ptr<DiagnosticMessage>
Its_element_type_0_is_not_a_valid_JSX_element() {
  return diag(2789, DiagnosticCategory::Error,
              "Its_element_type_0_is_not_a_valid_JSX_element_2789",
              "Its element type '{0}' is not a valid JSX element.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_a_delete_operator_must_be_optional() {
  return diag(2790, DiagnosticCategory::Error,
              "The_operand_of_a_delete_operator_must_be_optional_2790",
              "The operand of a 'delete' operator must be optional.");
};
static shared_ptr<DiagnosticMessage>
Exponentiation_cannot_be_performed_on_bigint_values_unless_the_target_option_is_set_to_es2016_or_later() {
  return diag(2791, DiagnosticCategory::Error,
              "Exponentiation_cannot_be_performed_on_bigint_values_unless_the_"
              "target_option_is_set_to_es2016_or_lat_2791",
              "Exponentiation cannot be performed on 'bigint' values unless "
              "the 'target' option is set to 'es2016' or later.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_module_0_Did_you_mean_to_set_the_moduleResolution_option_to_node_or_to_add_aliases_to_the_paths_option() {
  return diag(
      2792, DiagnosticCategory::Error,
      "Cannot_find_module_0_Did_you_mean_to_set_the_moduleResolution_option_to_"
      "node_or_to_add_aliases_to_th_2792",
      "Cannot find module '{0}'. Did you mean to set the 'moduleResolution' "
      "option to 'node', or to add aliases to the 'paths' option?");
};
static shared_ptr<DiagnosticMessage>
The_call_would_have_succeeded_against_this_implementation_but_implementation_signatures_of_overloads_are_not_externally_visible() {
  return diag(
      2793, DiagnosticCategory::Error,
      "The_call_would_have_succeeded_against_this_implementation_but_"
      "implementation_signatures_of_overloads_2793",
      "The call would have succeeded against this implementation, but "
      "implementation signatures of overloads are not externally visible.");
};
static shared_ptr<DiagnosticMessage>
Expected_0_arguments_but_got_1_Did_you_forget_to_include_void_in_your_type_argument_to_Promise() {
  return diag(2794, DiagnosticCategory::Error,
              "Expected_0_arguments_but_got_1_Did_you_forget_to_include_void_"
              "in_your_type_argument_to_Promise_2794",
              "Expected {0} arguments, but got {1}. Did you forget to include "
              "'void' in your type argument to 'Promise'?");
};
static shared_ptr<DiagnosticMessage>
The_intrinsic_keyword_can_only_be_used_to_declare_compiler_provided_intrinsic_types() {
  return diag(2795, DiagnosticCategory::Error,
              "The_intrinsic_keyword_can_only_be_used_to_declare_compiler_"
              "provided_intrinsic_types_2795",
              "The 'intrinsic' keyword can only be used to declare compiler "
              "provided intrinsic types.");
};
static shared_ptr<DiagnosticMessage>
It_is_likely_that_you_are_missing_a_comma_to_separate_these_two_template_expressions_They_form_a_tagged_template_expression_which_cannot_be_invoked() {
  return diag(2796, DiagnosticCategory::Error,
              "It_is_likely_that_you_are_missing_a_comma_to_separate_these_two_"
              "template_expressions_They_form_a_tag_2796",
              "It is likely that you are missing a comma to separate these two "
              "template expressions. They form a tagged template expression "
              "which cannot be invoked.");
};
static shared_ptr<DiagnosticMessage>
A_mixin_class_that_extends_from_a_type_variable_containing_an_abstract_construct_signature_must_also_be_declared_abstract() {
  return diag(2797, DiagnosticCategory::Error,
              "A_mixin_class_that_extends_from_a_type_variable_containing_an_"
              "abstract_construct_signature_must_also_2797",
              "A mixin class that extends from a type variable containing an "
              "abstract construct signature must also be declared 'abstract'.");
};
static shared_ptr<DiagnosticMessage>
The_declaration_was_marked_as_deprecated_here() {
  return diag(2798, DiagnosticCategory::Error,
              "The_declaration_was_marked_as_deprecated_here_2798",
              "The declaration was marked as deprecated here.");
};
static shared_ptr<DiagnosticMessage>
Type_produces_a_tuple_type_that_is_too_large_to_represent() {
  return diag(2799, DiagnosticCategory::Error,
              "Type_produces_a_tuple_type_that_is_too_large_to_represent_2799",
              "Type produces a tuple type that is too large to represent.");
};
static shared_ptr<DiagnosticMessage>
Expression_produces_a_tuple_type_that_is_too_large_to_represent() {
  return diag(
      2800, DiagnosticCategory::Error,
      "Expression_produces_a_tuple_type_that_is_too_large_to_represent_2800",
      "Expression produces a tuple type that is too large to represent.");
};
static shared_ptr<DiagnosticMessage>
This_condition_will_always_return_true_since_this_0_is_always_defined() {
  return diag(2801, DiagnosticCategory::Error,
              "This_condition_will_always_return_true_since_this_0_is_always_"
              "defined_2801",
              "This condition will always return true since this '{0}' is "
              "always defined.");
};
static shared_ptr<DiagnosticMessage>
Type_0_can_only_be_iterated_through_when_using_the_downlevelIteration_flag_or_with_a_target_of_es2015_or_higher() {
  return diag(2802, DiagnosticCategory::Error,
              "Type_0_can_only_be_iterated_through_when_using_the_"
              "downlevelIteration_flag_or_with_a_target_of_es201_2802",
              "Type '{0}' can only be iterated through when using the "
              "'--downlevelIteration' flag or with a '--target' of 'es2015' or "
              "higher.");
};
static shared_ptr<DiagnosticMessage>
Cannot_assign_to_private_method_0_Private_methods_are_not_writable() {
  return diag(
      2803, DiagnosticCategory::Error,
      "Cannot_assign_to_private_method_0_Private_methods_are_not_writable_2803",
      "Cannot assign to private method '{0}'. Private methods are not "
      "writable.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_0_Static_and_instance_elements_cannot_share_the_same_private_name() {
  return diag(2804, DiagnosticCategory::Error,
              "Duplicate_identifier_0_Static_and_instance_elements_cannot_"
              "share_the_same_private_name_2804",
              "Duplicate identifier '{0}'. Static and instance elements cannot "
              "share the same private name.");
};
static shared_ptr<DiagnosticMessage>
Static_fields_with_private_names_can_t_have_initializers_when_the_useDefineForClassFields_flag_is_not_specified_with_a_target_of_esnext_Consider_adding_the_useDefineForClassFields_flag() {
  return diag(
      2805, DiagnosticCategory::Error,
      "Static_fields_with_private_names_can_t_have_initializers_when_the_"
      "useDefineForClassFields_flag_is_no_2805",
      "Static fields with private names can't have initializers when the "
      "'--useDefineForClassFields' flag is not specified with a '--target' of "
      "'esnext'. Consider adding the '--useDefineForClassFields' flag.");
};
static shared_ptr<DiagnosticMessage>
Private_accessor_was_defined_without_a_getter() {
  return diag(2806, DiagnosticCategory::Error,
              "Private_accessor_was_defined_without_a_getter_2806",
              "Private accessor was defined without a getter.");
};
static shared_ptr<DiagnosticMessage>
This_syntax_requires_an_imported_helper_named_1_with_2_parameters_which_is_not_compatible_with_the_one_in_0_Consider_upgrading_your_version_of_0() {
  return diag(2807, DiagnosticCategory::Error,
              "This_syntax_requires_an_imported_helper_named_1_with_2_"
              "parameters_which_is_not_compatible_with_the_o_2807",
              "This syntax requires an imported helper named '{1}' with {2} "
              "parameters, which is not compatible with the one in '{0}'. "
              "Consider upgrading your version of '{0}'.");
};
static shared_ptr<DiagnosticMessage>
A_get_accessor_must_be_at_least_as_accessible_as_the_setter() {
  return diag(
      2808, DiagnosticCategory::Error,
      "A_get_accessor_must_be_at_least_as_accessible_as_the_setter_2808",
      "A get accessor must be at least as accessible as the setter");
};
static shared_ptr<DiagnosticMessage>
Declaration_or_statement_expected_This_follows_a_block_of_statements_so_if_you_intended_to_write_a_destructuring_assignment_you_might_need_to_wrap_the_the_whole_assignment_in_parentheses() {
  return diag(
      2809, DiagnosticCategory::Error,
      "Declaration_or_statement_expected_This_follows_a_block_of_statements_so_"
      "if_you_intended_to_write_a_d_2809",
      "Declaration or statement expected. This '=' follows a block of "
      "statements, so if you intended to write a destructuring assignment, you "
      "might need to wrap the the whole assignment in parentheses.");
};
static shared_ptr<DiagnosticMessage>
Property_0_may_not_be_used_in_a_static_property_s_initializer_in_the_same_class_when_target_is_esnext_and_useDefineForClassFields_is_false() {
  return diag(2810, DiagnosticCategory::Error,
              "Property_0_may_not_be_used_in_a_static_property_s_initializer_"
              "in_the_same_class_when_target_is_esnex_2810",
              "Property '{0}' may not be used in a static property's "
              "initializer in the same class when 'target' is 'esnext' and "
              "'useDefineForClassFields' is 'false'.");
};
static shared_ptr<DiagnosticMessage> Initializer_for_property_0() {
  return diag(2811, DiagnosticCategory::Error,
              "Initializer_for_property_0_2811",
              "Initializer for property '{0}'");
};
static shared_ptr<DiagnosticMessage>
Property_0_does_not_exist_on_type_1_Try_changing_the_lib_compiler_option_to_include_dom() {
  return diag(2812, DiagnosticCategory::Error,
              "Property_0_does_not_exist_on_type_1_Try_changing_the_lib_"
              "compiler_option_to_include_dom_2812",
              "Property '{0}' does not exist on type '{1}'. Try changing the "
              "'lib' compiler option to include 'dom'.");
};
static shared_ptr<DiagnosticMessage>
Class_declaration_cannot_implement_overload_list_for_0() {
  return diag(2813, DiagnosticCategory::Error,
              "Class_declaration_cannot_implement_overload_list_for_0_2813",
              "Class declaration cannot implement overload list for '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Function_with_bodies_can_only_merge_with_classes_that_are_ambient() {
  return diag(
      2814, DiagnosticCategory::Error,
      "Function_with_bodies_can_only_merge_with_classes_that_are_ambient_2814",
      "Function with bodies can only merge with classes that are ambient.");
};
static shared_ptr<DiagnosticMessage>
arguments_cannot_be_referenced_in_property_initializers() {
  return diag(2815, DiagnosticCategory::Error,
              "arguments_cannot_be_referenced_in_property_initializers_2815",
              "'arguments' cannot be referenced in property initializers.");
};
static shared_ptr<DiagnosticMessage>
Cannot_use_this_in_a_static_property_initializer_of_a_decorated_class() {
  return diag(2816, DiagnosticCategory::Error,
              "Cannot_use_this_in_a_static_property_initializer_of_a_decorated_"
              "class_2816",
              "Cannot use 'this' in a static property initializer of a "
              "decorated class.");
};
static shared_ptr<DiagnosticMessage>
Property_0_has_no_initializer_and_is_not_definitely_assigned_in_a_class_static_block() {
  return diag(2817, DiagnosticCategory::Error,
              "Property_0_has_no_initializer_and_is_not_definitely_assigned_in_"
              "a_class_static_block_2817",
              "Property '{0}' has no initializer and is not definitely "
              "assigned in a class static block.");
};
static shared_ptr<DiagnosticMessage>
Duplicate_identifier_0_Compiler_reserves_name_1_when_emitting_super_references_in_static_initializers() {
  return diag(2818, DiagnosticCategory::Error,
              "Duplicate_identifier_0_Compiler_reserves_name_1_when_emitting_"
              "super_references_in_static_initializer_2818",
              "Duplicate identifier '{0}'. Compiler reserves name '{1}' when "
              "emitting 'super' references in static initializers.");
};
static shared_ptr<DiagnosticMessage> Namespace_name_cannot_be_0() {
  return diag(2819, DiagnosticCategory::Error,
              "Namespace_name_cannot_be_0_2819",
              "Namespace name cannot be '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_0_is_not_assignable_to_type_1_Did_you_mean_2() {
  return diag(
      2820, DiagnosticCategory::Error,
      "Type_0_is_not_assignable_to_type_1_Did_you_mean_2_2820",
      "Type '{0}' is not assignable to type '{1}'. Did you mean '{2}'?");
};
static shared_ptr<DiagnosticMessage>
Import_assertions_are_only_supported_when_the_module_option_is_set_to_esnext_or_nodenext() {
  return diag(2821, DiagnosticCategory::Error,
              "Import_assertions_are_only_supported_when_the_module_option_is_"
              "set_to_esnext_or_nodenext_2821",
              "Import assertions are only supported when the '--module' option "
              "is set to 'esnext' or 'nodenext'.");
};
static shared_ptr<DiagnosticMessage>
Import_assertions_cannot_be_used_with_type_only_imports_or_exports() {
  return diag(
      2822, DiagnosticCategory::Error,
      "Import_assertions_cannot_be_used_with_type_only_imports_or_exports_2822",
      "Import assertions cannot be used with type-only imports or exports.");
};
static shared_ptr<DiagnosticMessage> Cannot_find_namespace_0_Did_you_mean_1() {
  return diag(2833, DiagnosticCategory::Error,
              "Cannot_find_namespace_0_Did_you_mean_1_2833",
              "Cannot find namespace '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Relative_import_paths_need_explicit_file_extensions_in_EcmaScript_imports_when_moduleResolution_is_node12_or_nodenext_Consider_adding_an_extension_to_the_import_path() {
  return diag(2834, DiagnosticCategory::Error,
              "Relative_import_paths_need_explicit_file_extensions_in_"
              "EcmaScript_imports_when_moduleResolution_is_n_2834",
              "Relative import paths need explicit file extensions in "
              "EcmaScript imports when '--moduleResolution' is 'node12' or "
              "'nodenext'. Consider adding an extension to the import path.");
};
static shared_ptr<DiagnosticMessage>
Relative_import_paths_need_explicit_file_extensions_in_EcmaScript_imports_when_moduleResolution_is_node12_or_nodenext_Did_you_mean_0() {
  return diag(2835, DiagnosticCategory::Error,
              "Relative_import_paths_need_explicit_file_extensions_in_"
              "EcmaScript_imports_when_moduleResolution_is_n_2835",
              "Relative import paths need explicit file extensions in "
              "EcmaScript imports when '--moduleResolution' is 'node12' or "
              "'nodenext'. Did you mean '{0}'?");
};
static shared_ptr<DiagnosticMessage>
Import_assertions_are_not_allowed_on_statements_that_transpile_to_commonjs_require_calls() {
  return diag(2836, DiagnosticCategory::Error,
              "Import_assertions_are_not_allowed_on_statements_that_transpile_"
              "to_commonjs_require_calls_2836",
              "Import assertions are not allowed on statements that transpile "
              "to commonjs 'require' calls.");
};
static shared_ptr<DiagnosticMessage>
Import_declaration_0_is_using_private_name_1() {
  return diag(4000, DiagnosticCategory::Error,
              "Import_declaration_0_is_using_private_name_1_4000",
              "Import declaration '{0}' is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_exported_class_has_or_is_using_private_name_1() {
  return diag(
      4002, DiagnosticCategory::Error,
      "Type_parameter_0_of_exported_class_has_or_is_using_private_name_1_4002",
      "Type parameter '{0}' of exported class has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_exported_interface_has_or_is_using_private_name_1() {
  return diag(4004, DiagnosticCategory::Error,
              "Type_parameter_0_of_exported_interface_has_or_is_using_private_"
              "name_1_4004",
              "Type parameter '{0}' of exported interface has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_constructor_signature_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4006, DiagnosticCategory::Error,
              "Type_parameter_0_of_constructor_signature_from_exported_"
              "interface_has_or_is_using_private_name_1_4006",
              "Type parameter '{0}' of constructor signature from exported "
              "interface has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_call_signature_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4008, DiagnosticCategory::Error,
              "Type_parameter_0_of_call_signature_from_exported_interface_has_"
              "or_is_using_private_name_1_4008",
              "Type parameter '{0}' of call signature from exported interface "
              "has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_public_static_method_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4010, DiagnosticCategory::Error,
              "Type_parameter_0_of_public_static_method_from_exported_class_"
              "has_or_is_using_private_name_1_4010",
              "Type parameter '{0}' of public static method from exported "
              "class has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_public_method_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4012, DiagnosticCategory::Error,
              "Type_parameter_0_of_public_method_from_exported_class_has_or_is_"
              "using_private_name_1_4012",
              "Type parameter '{0}' of public method from exported class has "
              "or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_method_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4014, DiagnosticCategory::Error,
              "Type_parameter_0_of_method_from_exported_interface_has_or_is_"
              "using_private_name_1_4014",
              "Type parameter '{0}' of method from exported interface has or "
              "is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_exported_function_has_or_is_using_private_name_1() {
  return diag(4016, DiagnosticCategory::Error,
              "Type_parameter_0_of_exported_function_has_or_is_using_private_"
              "name_1_4016",
              "Type parameter '{0}' of exported function has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Implements_clause_of_exported_class_0_has_or_is_using_private_name_1() {
  return diag(4019, DiagnosticCategory::Error,
              "Implements_clause_of_exported_class_0_has_or_is_using_private_"
              "name_1_4019",
              "Implements clause of exported class '{0}' has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
extends_clause_of_exported_class_0_has_or_is_using_private_name_1() {
  return diag(
      4020, DiagnosticCategory::Error,
      "extends_clause_of_exported_class_0_has_or_is_using_private_name_1_4020",
      "'extends' clause of exported class '{0}' has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
extends_clause_of_exported_class_has_or_is_using_private_name_0() {
  return diag(
      4021, DiagnosticCategory::Error,
      "extends_clause_of_exported_class_has_or_is_using_private_name_0_4021",
      "'extends' clause of exported class has or is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
extends_clause_of_exported_interface_0_has_or_is_using_private_name_1() {
  return diag(4022, DiagnosticCategory::Error,
              "extends_clause_of_exported_interface_0_has_or_is_using_private_"
              "name_1_4022",
              "'extends' clause of exported interface '{0}' has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Exported_variable_0_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4023, DiagnosticCategory::Error,
              "Exported_variable_0_has_or_is_using_name_1_from_external_module_"
              "2_but_cannot_be_named_4023",
              "Exported variable '{0}' has or is using name '{1}' from "
              "external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Exported_variable_0_has_or_is_using_name_1_from_private_module_2() {
  return diag(
      4024, DiagnosticCategory::Error,
      "Exported_variable_0_has_or_is_using_name_1_from_private_module_2_4024",
      "Exported variable '{0}' has or is using name '{1}' from private module "
      "'{2}'.");
};
static shared_ptr<DiagnosticMessage>
Exported_variable_0_has_or_is_using_private_name_1() {
  return diag(4025, DiagnosticCategory::Error,
              "Exported_variable_0_has_or_is_using_private_name_1_4025",
              "Exported variable '{0}' has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Public_static_property_0_of_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4026, DiagnosticCategory::Error,
              "Public_static_property_0_of_exported_class_has_or_is_using_name_"
              "1_from_external_module_2_but_cannot__4026",
              "Public static property '{0}' of exported class has or is using "
              "name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Public_static_property_0_of_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4027, DiagnosticCategory::Error,
              "Public_static_property_0_of_exported_class_has_or_is_using_name_"
              "1_from_private_module_2_4027",
              "Public static property '{0}' of exported class has or is using "
              "name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Public_static_property_0_of_exported_class_has_or_is_using_private_name_1() {
  return diag(4028, DiagnosticCategory::Error,
              "Public_static_property_0_of_exported_class_has_or_is_using_"
              "private_name_1_4028",
              "Public static property '{0}' of exported class has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Public_property_0_of_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4029, DiagnosticCategory::Error,
              "Public_property_0_of_exported_class_has_or_is_using_name_1_from_"
              "external_module_2_but_cannot_be_name_4029",
              "Public property '{0}' of exported class has or is using name "
              "'{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Public_property_0_of_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4030, DiagnosticCategory::Error,
              "Public_property_0_of_exported_class_has_or_is_using_name_1_from_"
              "private_module_2_4030",
              "Public property '{0}' of exported class has or is using name "
              "'{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Public_property_0_of_exported_class_has_or_is_using_private_name_1() {
  return diag(
      4031, DiagnosticCategory::Error,
      "Public_property_0_of_exported_class_has_or_is_using_private_name_1_4031",
      "Public property '{0}' of exported class has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_of_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(4032, DiagnosticCategory::Error,
              "Property_0_of_exported_interface_has_or_is_using_name_1_from_"
              "private_module_2_4032",
              "Property '{0}' of exported interface has or is using name '{1}' "
              "from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_of_exported_interface_has_or_is_using_private_name_1() {
  return diag(
      4033, DiagnosticCategory::Error,
      "Property_0_of_exported_interface_has_or_is_using_private_name_1_4033",
      "Property '{0}' of exported interface has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_type_of_public_static_setter_0_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4034, DiagnosticCategory::Error,
              "Parameter_type_of_public_static_setter_0_from_exported_class_"
              "has_or_is_using_name_1_from_private_mod_4034",
              "Parameter type of public static setter '{0}' from exported "
              "class has or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_type_of_public_static_setter_0_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4035, DiagnosticCategory::Error,
              "Parameter_type_of_public_static_setter_0_from_exported_class_"
              "has_or_is_using_private_name_1_4035",
              "Parameter type of public static setter '{0}' from exported "
              "class has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_type_of_public_setter_0_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4036, DiagnosticCategory::Error,
              "Parameter_type_of_public_setter_0_from_exported_class_has_or_is_"
              "using_name_1_from_private_module_2_4036",
              "Parameter type of public setter '{0}' from exported class has "
              "or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_type_of_public_setter_0_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4037, DiagnosticCategory::Error,
              "Parameter_type_of_public_setter_0_from_exported_class_has_or_is_"
              "using_private_name_1_4037",
              "Parameter type of public setter '{0}' from exported class has "
              "or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_getter_0_from_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(
      4038, DiagnosticCategory::Error,
      "Return_type_of_public_static_getter_0_from_exported_class_has_or_is_"
      "using_name_1_from_external_modul_4038",
      "Return type of public static getter '{0}' from exported class has or is "
      "using name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_getter_0_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4039, DiagnosticCategory::Error,
              "Return_type_of_public_static_getter_0_from_exported_class_has_"
              "or_is_using_name_1_from_private_module_4039",
              "Return type of public static getter '{0}' from exported class "
              "has or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_getter_0_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4040, DiagnosticCategory::Error,
              "Return_type_of_public_static_getter_0_from_exported_class_has_"
              "or_is_using_private_name_1_4040",
              "Return type of public static getter '{0}' from exported class "
              "has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_getter_0_from_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(
      4041, DiagnosticCategory::Error,
      "Return_type_of_public_getter_0_from_exported_class_has_or_is_using_name_"
      "1_from_external_module_2_but_4041",
      "Return type of public getter '{0}' from exported class has or is using "
      "name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_getter_0_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4042, DiagnosticCategory::Error,
              "Return_type_of_public_getter_0_from_exported_class_has_or_is_"
              "using_name_1_from_private_module_2_4042",
              "Return type of public getter '{0}' from exported class has or "
              "is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_getter_0_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4043, DiagnosticCategory::Error,
              "Return_type_of_public_getter_0_from_exported_class_has_or_is_"
              "using_private_name_1_4043",
              "Return type of public getter '{0}' from exported class has or "
              "is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_constructor_signature_from_exported_interface_has_or_is_using_name_0_from_private_module_1() {
  return diag(4044, DiagnosticCategory::Error,
              "Return_type_of_constructor_signature_from_exported_interface_"
              "has_or_is_using_name_0_from_private_mod_4044",
              "Return type of constructor signature from exported interface "
              "has or is using name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_constructor_signature_from_exported_interface_has_or_is_using_private_name_0() {
  return diag(4045, DiagnosticCategory::Error,
              "Return_type_of_constructor_signature_from_exported_interface_"
              "has_or_is_using_private_name_0_4045",
              "Return type of constructor signature from exported interface "
              "has or is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_call_signature_from_exported_interface_has_or_is_using_name_0_from_private_module_1() {
  return diag(4046, DiagnosticCategory::Error,
              "Return_type_of_call_signature_from_exported_interface_has_or_is_"
              "using_name_0_from_private_module_1_4046",
              "Return type of call signature from exported interface has or is "
              "using name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_call_signature_from_exported_interface_has_or_is_using_private_name_0() {
  return diag(4047, DiagnosticCategory::Error,
              "Return_type_of_call_signature_from_exported_interface_has_or_is_"
              "using_private_name_0_4047",
              "Return type of call signature from exported interface has or is "
              "using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_index_signature_from_exported_interface_has_or_is_using_name_0_from_private_module_1() {
  return diag(4048, DiagnosticCategory::Error,
              "Return_type_of_index_signature_from_exported_interface_has_or_"
              "is_using_name_0_from_private_module_1_4048",
              "Return type of index signature from exported interface has or "
              "is using name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_index_signature_from_exported_interface_has_or_is_using_private_name_0() {
  return diag(4049, DiagnosticCategory::Error,
              "Return_type_of_index_signature_from_exported_interface_has_or_"
              "is_using_private_name_0_4049",
              "Return type of index signature from exported interface has or "
              "is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_method_from_exported_class_has_or_is_using_name_0_from_external_module_1_but_cannot_be_named() {
  return diag(
      4050, DiagnosticCategory::Error,
      "Return_type_of_public_static_method_from_exported_class_has_or_is_using_"
      "name_0_from_external_module__4050",
      "Return type of public static method from exported class has or is using "
      "name '{0}' from external module {1} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_method_from_exported_class_has_or_is_using_name_0_from_private_module_1() {
  return diag(4051, DiagnosticCategory::Error,
              "Return_type_of_public_static_method_from_exported_class_has_or_"
              "is_using_name_0_from_private_module_1_4051",
              "Return type of public static method from exported class has or "
              "is using name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_static_method_from_exported_class_has_or_is_using_private_name_0() {
  return diag(4052, DiagnosticCategory::Error,
              "Return_type_of_public_static_method_from_exported_class_has_or_"
              "is_using_private_name_0_4052",
              "Return type of public static method from exported class has or "
              "is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_method_from_exported_class_has_or_is_using_name_0_from_external_module_1_but_cannot_be_named() {
  return diag(4053, DiagnosticCategory::Error,
              "Return_type_of_public_method_from_exported_class_has_or_is_"
              "using_name_0_from_external_module_1_but_c_4053",
              "Return type of public method from exported class has or is "
              "using name '{0}' from external module {1} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_method_from_exported_class_has_or_is_using_name_0_from_private_module_1() {
  return diag(4054, DiagnosticCategory::Error,
              "Return_type_of_public_method_from_exported_class_has_or_is_"
              "using_name_0_from_private_module_1_4054",
              "Return type of public method from exported class has or is "
              "using name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_public_method_from_exported_class_has_or_is_using_private_name_0() {
  return diag(4055, DiagnosticCategory::Error,
              "Return_type_of_public_method_from_exported_class_has_or_is_"
              "using_private_name_0_4055",
              "Return type of public method from exported class has or is "
              "using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_method_from_exported_interface_has_or_is_using_name_0_from_private_module_1() {
  return diag(4056, DiagnosticCategory::Error,
              "Return_type_of_method_from_exported_interface_has_or_is_using_"
              "name_0_from_private_module_1_4056",
              "Return type of method from exported interface has or is using "
              "name '{0}' from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_method_from_exported_interface_has_or_is_using_private_name_0() {
  return diag(4057, DiagnosticCategory::Error,
              "Return_type_of_method_from_exported_interface_has_or_is_using_"
              "private_name_0_4057",
              "Return type of method from exported interface has or is using "
              "private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_exported_function_has_or_is_using_name_0_from_external_module_1_but_cannot_be_named() {
  return diag(4058, DiagnosticCategory::Error,
              "Return_type_of_exported_function_has_or_is_using_name_0_from_"
              "external_module_1_but_cannot_be_named_4058",
              "Return type of exported function has or is using name '{0}' "
              "from external module {1} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_exported_function_has_or_is_using_name_0_from_private_module_1() {
  return diag(4059, DiagnosticCategory::Error,
              "Return_type_of_exported_function_has_or_is_using_name_0_from_"
              "private_module_1_4059",
              "Return type of exported function has or is using name '{0}' "
              "from private module '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Return_type_of_exported_function_has_or_is_using_private_name_0() {
  return diag(
      4060, DiagnosticCategory::Error,
      "Return_type_of_exported_function_has_or_is_using_private_name_0_4060",
      "Return type of exported function has or is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_constructor_from_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4061, DiagnosticCategory::Error,
              "Parameter_0_of_constructor_from_exported_class_has_or_is_using_"
              "name_1_from_external_module_2_but_can_4061",
              "Parameter '{0}' of constructor from exported class has or is "
              "using name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_constructor_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4062, DiagnosticCategory::Error,
              "Parameter_0_of_constructor_from_exported_class_has_or_is_using_"
              "name_1_from_private_module_2_4062",
              "Parameter '{0}' of constructor from exported class has or is "
              "using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_constructor_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4063, DiagnosticCategory::Error,
              "Parameter_0_of_constructor_from_exported_class_has_or_is_using_"
              "private_name_1_4063",
              "Parameter '{0}' of constructor from exported class has or is "
              "using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_constructor_signature_from_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(
      4064, DiagnosticCategory::Error,
      "Parameter_0_of_constructor_signature_from_exported_interface_has_or_is_"
      "using_name_1_from_private_mod_4064",
      "Parameter '{0}' of constructor signature from exported interface has or "
      "is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_constructor_signature_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4065, DiagnosticCategory::Error,
              "Parameter_0_of_constructor_signature_from_exported_interface_"
              "has_or_is_using_private_name_1_4065",
              "Parameter '{0}' of constructor signature from exported "
              "interface has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_call_signature_from_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(4066, DiagnosticCategory::Error,
              "Parameter_0_of_call_signature_from_exported_interface_has_or_is_"
              "using_name_1_from_private_module_2_4066",
              "Parameter '{0}' of call signature from exported interface has "
              "or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_call_signature_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4067, DiagnosticCategory::Error,
              "Parameter_0_of_call_signature_from_exported_interface_has_or_is_"
              "using_private_name_1_4067",
              "Parameter '{0}' of call signature from exported interface has "
              "or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_static_method_from_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(
      4068, DiagnosticCategory::Error,
      "Parameter_0_of_public_static_method_from_exported_class_has_or_is_using_"
      "name_1_from_external_module__4068",
      "Parameter '{0}' of public static method from exported class has or is "
      "using name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_static_method_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4069, DiagnosticCategory::Error,
              "Parameter_0_of_public_static_method_from_exported_class_has_or_"
              "is_using_name_1_from_private_module_2_4069",
              "Parameter '{0}' of public static method from exported class has "
              "or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_static_method_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4070, DiagnosticCategory::Error,
              "Parameter_0_of_public_static_method_from_exported_class_has_or_"
              "is_using_private_name_1_4070",
              "Parameter '{0}' of public static method from exported class has "
              "or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_method_from_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4071, DiagnosticCategory::Error,
              "Parameter_0_of_public_method_from_exported_class_has_or_is_"
              "using_name_1_from_external_module_2_but_c_4071",
              "Parameter '{0}' of public method from exported class has or is "
              "using name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_method_from_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4072, DiagnosticCategory::Error,
              "Parameter_0_of_public_method_from_exported_class_has_or_is_"
              "using_name_1_from_private_module_2_4072",
              "Parameter '{0}' of public method from exported class has or is "
              "using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_public_method_from_exported_class_has_or_is_using_private_name_1() {
  return diag(4073, DiagnosticCategory::Error,
              "Parameter_0_of_public_method_from_exported_class_has_or_is_"
              "using_private_name_1_4073",
              "Parameter '{0}' of public method from exported class has or is "
              "using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_method_from_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(4074, DiagnosticCategory::Error,
              "Parameter_0_of_method_from_exported_interface_has_or_is_using_"
              "name_1_from_private_module_2_4074",
              "Parameter '{0}' of method from exported interface has or is "
              "using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_method_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4075, DiagnosticCategory::Error,
              "Parameter_0_of_method_from_exported_interface_has_or_is_using_"
              "private_name_1_4075",
              "Parameter '{0}' of method from exported interface has or is "
              "using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_exported_function_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4076, DiagnosticCategory::Error,
              "Parameter_0_of_exported_function_has_or_is_using_name_1_from_"
              "external_module_2_but_cannot_be_named_4076",
              "Parameter '{0}' of exported function has or is using name '{1}' "
              "from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_exported_function_has_or_is_using_name_1_from_private_module_2() {
  return diag(4077, DiagnosticCategory::Error,
              "Parameter_0_of_exported_function_has_or_is_using_name_1_from_"
              "private_module_2_4077",
              "Parameter '{0}' of exported function has or is using name '{1}' "
              "from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_exported_function_has_or_is_using_private_name_1() {
  return diag(
      4078, DiagnosticCategory::Error,
      "Parameter_0_of_exported_function_has_or_is_using_private_name_1_4078",
      "Parameter '{0}' of exported function has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Exported_type_alias_0_has_or_is_using_private_name_1() {
  return diag(4081, DiagnosticCategory::Error,
              "Exported_type_alias_0_has_or_is_using_private_name_1_4081",
              "Exported type alias '{0}' has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Default_export_of_the_module_has_or_is_using_private_name_0() {
  return diag(
      4082, DiagnosticCategory::Error,
      "Default_export_of_the_module_has_or_is_using_private_name_0_4082",
      "Default export of the module has or is using private name '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_exported_type_alias_has_or_is_using_private_name_1() {
  return diag(4083, DiagnosticCategory::Error,
              "Type_parameter_0_of_exported_type_alias_has_or_is_using_private_"
              "name_1_4083",
              "Type parameter '{0}' of exported type alias has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Exported_type_alias_0_has_or_is_using_private_name_1_from_module_2() {
  return diag(
      4084, DiagnosticCategory::Error,
      "Exported_type_alias_0_has_or_is_using_private_name_1_from_module_2_4084",
      "Exported type alias '{0}' has or is using private name '{1}' from "
      "module {2}.");
};
static shared_ptr<DiagnosticMessage>
Conflicting_definitions_for_0_found_at_1_and_2_Consider_installing_a_specific_version_of_this_library_to_resolve_the_conflict() {
  return diag(
      4090, DiagnosticCategory::Error,
      "Conflicting_definitions_for_0_found_at_1_and_2_Consider_installing_a_"
      "specific_version_of_this_librar_4090",
      "Conflicting definitions for '{0}' found at '{1}' and '{2}'. Consider "
      "installing a specific version of this library to resolve the conflict.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_index_signature_from_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(4091, DiagnosticCategory::Error,
              "Parameter_0_of_index_signature_from_exported_interface_has_or_"
              "is_using_name_1_from_private_module_2_4091",
              "Parameter '{0}' of index signature from exported interface has "
              "or is using name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_index_signature_from_exported_interface_has_or_is_using_private_name_1() {
  return diag(4092, DiagnosticCategory::Error,
              "Parameter_0_of_index_signature_from_exported_interface_has_or_"
              "is_using_private_name_1_4092",
              "Parameter '{0}' of index signature from exported interface has "
              "or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_of_exported_class_expression_may_not_be_private_or_protected() {
  return diag(4094, DiagnosticCategory::Error,
              "Property_0_of_exported_class_expression_may_not_be_private_or_"
              "protected_4094",
              "Property '{0}' of exported class expression may not be private "
              "or protected.");
};
static shared_ptr<DiagnosticMessage>
Public_static_method_0_of_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4095, DiagnosticCategory::Error,
              "Public_static_method_0_of_exported_class_has_or_is_using_name_1_"
              "from_external_module_2_but_cannot_be_4095",
              "Public static method '{0}' of exported class has or is using "
              "name '{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Public_static_method_0_of_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4096, DiagnosticCategory::Error,
              "Public_static_method_0_of_exported_class_has_or_is_using_name_1_"
              "from_private_module_2_4096",
              "Public static method '{0}' of exported class has or is using "
              "name '{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Public_static_method_0_of_exported_class_has_or_is_using_private_name_1() {
  return diag(4097, DiagnosticCategory::Error,
              "Public_static_method_0_of_exported_class_has_or_is_using_"
              "private_name_1_4097",
              "Public static method '{0}' of exported class has or is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Public_method_0_of_exported_class_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4098, DiagnosticCategory::Error,
              "Public_method_0_of_exported_class_has_or_is_using_name_1_from_"
              "external_module_2_but_cannot_be_named_4098",
              "Public method '{0}' of exported class has or is using name "
              "'{1}' from external module {2} but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Public_method_0_of_exported_class_has_or_is_using_name_1_from_private_module_2() {
  return diag(4099, DiagnosticCategory::Error,
              "Public_method_0_of_exported_class_has_or_is_using_name_1_from_"
              "private_module_2_4099",
              "Public method '{0}' of exported class has or is using name "
              "'{1}' from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Public_method_0_of_exported_class_has_or_is_using_private_name_1() {
  return diag(
      4100, DiagnosticCategory::Error,
      "Public_method_0_of_exported_class_has_or_is_using_private_name_1_4100",
      "Public method '{0}' of exported class has or is using private name "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Method_0_of_exported_interface_has_or_is_using_name_1_from_private_module_2() {
  return diag(4101, DiagnosticCategory::Error,
              "Method_0_of_exported_interface_has_or_is_using_name_1_from_"
              "private_module_2_4101",
              "Method '{0}' of exported interface has or is using name '{1}' "
              "from private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Method_0_of_exported_interface_has_or_is_using_private_name_1() {
  return diag(
      4102, DiagnosticCategory::Error,
      "Method_0_of_exported_interface_has_or_is_using_private_name_1_4102",
      "Method '{0}' of exported interface has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_0_of_exported_mapped_object_type_is_using_private_name_1() {
  return diag(4103, DiagnosticCategory::Error,
              "Type_parameter_0_of_exported_mapped_object_type_is_using_"
              "private_name_1_4103",
              "Type parameter '{0}' of exported mapped object type is using "
              "private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
The_type_0_is_readonly_and_cannot_be_assigned_to_the_mutable_type_1() {
  return diag(4104, DiagnosticCategory::Error,
              "The_type_0_is_readonly_and_cannot_be_assigned_to_the_mutable_"
              "type_1_4104",
              "The type '{0}' is 'readonly' and cannot be assigned to the "
              "mutable type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Private_or_protected_member_0_cannot_be_accessed_on_a_type_parameter() {
  return diag(4105, DiagnosticCategory::Error,
              "Private_or_protected_member_0_cannot_be_accessed_on_a_type_"
              "parameter_4105",
              "Private or protected member '{0}' cannot be accessed on a type "
              "parameter.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_accessor_has_or_is_using_private_name_1() {
  return diag(
      4106, DiagnosticCategory::Error,
      "Parameter_0_of_accessor_has_or_is_using_private_name_1_4106",
      "Parameter '{0}' of accessor has or is using private name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_accessor_has_or_is_using_name_1_from_private_module_2() {
  return diag(4107, DiagnosticCategory::Error,
              "Parameter_0_of_accessor_has_or_is_using_name_1_from_private_"
              "module_2_4107",
              "Parameter '{0}' of accessor has or is using name '{1}' from "
              "private module '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_of_accessor_has_or_is_using_name_1_from_external_module_2_but_cannot_be_named() {
  return diag(4108, DiagnosticCategory::Error,
              "Parameter_0_of_accessor_has_or_is_using_name_1_from_external_"
              "module_2_but_cannot_be_named_4108",
              "Parameter '{0}' of accessor has or is using name '{1}' from "
              "external module '{2}' but cannot be named.");
};
static shared_ptr<DiagnosticMessage>
Type_arguments_for_0_circularly_reference_themselves() {
  return diag(4109, DiagnosticCategory::Error,
              "Type_arguments_for_0_circularly_reference_themselves_4109",
              "Type arguments for '{0}' circularly reference themselves.");
};
static shared_ptr<DiagnosticMessage>
Tuple_type_arguments_circularly_reference_themselves() {
  return diag(4110, DiagnosticCategory::Error,
              "Tuple_type_arguments_circularly_reference_themselves_4110",
              "Tuple type arguments circularly reference themselves.");
};
static shared_ptr<DiagnosticMessage>
Property_0_comes_from_an_index_signature_so_it_must_be_accessed_with_0() {
  return diag(4111, DiagnosticCategory::Error,
              "Property_0_comes_from_an_index_signature_so_it_must_be_accessed_"
              "with_0_4111",
              "Property '{0}' comes from an index signature, so it must be "
              "accessed with ['{0}'].");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_an_override_modifier_because_its_containing_class_0_does_not_extend_another_class() {
  return diag(4112, DiagnosticCategory::Error,
              "This_member_cannot_have_an_override_modifier_because_its_"
              "containing_class_0_does_not_extend_another__4112",
              "This member cannot have an 'override' modifier because its "
              "containing class '{0}' does not extend another class.");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_an_override_modifier_because_it_is_not_declared_in_the_base_class_0() {
  return diag(4113, DiagnosticCategory::Error,
              "This_member_cannot_have_an_override_modifier_because_it_is_not_"
              "declared_in_the_base_class_0_4113",
              "This member cannot have an 'override' modifier because it is "
              "not declared in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_member_must_have_an_override_modifier_because_it_overrides_a_member_in_the_base_class_0() {
  return diag(4114, DiagnosticCategory::Error,
              "This_member_must_have_an_override_modifier_because_it_overrides_"
              "a_member_in_the_base_class_0_4114",
              "This member must have an 'override' modifier because it "
              "overrides a member in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_parameter_property_must_have_an_override_modifier_because_it_overrides_a_member_in_base_class_0() {
  return diag(4115, DiagnosticCategory::Error,
              "This_parameter_property_must_have_an_override_modifier_because_"
              "it_overrides_a_member_in_base_class_0_4115",
              "This parameter property must have an 'override' modifier "
              "because it overrides a member in base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_member_must_have_an_override_modifier_because_it_overrides_an_abstract_method_that_is_declared_in_the_base_class_0() {
  return diag(
      4116, DiagnosticCategory::Error,
      "This_member_must_have_an_override_modifier_because_it_overrides_an_"
      "abstract_method_that_is_declared__4116",
      "This member must have an 'override' modifier because it overrides an "
      "abstract method that is declared in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_an_override_modifier_because_it_is_not_declared_in_the_base_class_0_Did_you_mean_1() {
  return diag(4117, DiagnosticCategory::Error,
              "This_member_cannot_have_an_override_modifier_because_it_is_not_"
              "declared_in_the_base_class_0_Did_you__4117",
              "This member cannot have an 'override' modifier because it is "
              "not declared in the base class '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
The_type_of_this_node_cannot_be_serialized_because_its_property_0_cannot_be_serialized() {
  return diag(4118, DiagnosticCategory::Error,
              "The_type_of_this_node_cannot_be_serialized_because_its_property_"
              "0_cannot_be_serialized_4118",
              "The type of this node cannot be serialized because its property "
              "'{0}' cannot be serialized.");
};
static shared_ptr<DiagnosticMessage>
This_member_must_have_a_JSDoc_comment_with_an_override_tag_because_it_overrides_a_member_in_the_base_class_0() {
  return diag(4119, DiagnosticCategory::Error,
              "This_member_must_have_a_JSDoc_comment_with_an_override_tag_"
              "because_it_overrides_a_member_in_the_base_4119",
              "This member must have a JSDoc comment with an '@override' tag "
              "because it overrides a member in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_parameter_property_must_have_a_JSDoc_comment_with_an_override_tag_because_it_overrides_a_member_in_the_base_class_0() {
  return diag(
      4120, DiagnosticCategory::Error,
      "This_parameter_property_must_have_a_JSDoc_comment_with_an_override_tag_"
      "because_it_overrides_a_member_4120",
      "This parameter property must have a JSDoc comment with an '@override' "
      "tag because it overrides a member in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_because_its_containing_class_0_does_not_extend_another_class() {
  return diag(
      4121, DiagnosticCategory::Error,
      "This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_because_"
      "its_containing_class_0_does_not_4121",
      "This member cannot have a JSDoc comment with an '@override' tag because "
      "its containing class '{0}' does not extend another class.");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_because_it_is_not_declared_in_the_base_class_0() {
  return diag(4122, DiagnosticCategory::Error,
              "This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_"
              "because_it_is_not_declared_in_the_base__4122",
              "This member cannot have a JSDoc comment with an '@override' tag "
              "because it is not declared in the base class '{0}'.");
};
static shared_ptr<DiagnosticMessage>
This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_because_it_is_not_declared_in_the_base_class_0_Did_you_mean_1() {
  return diag(
      4123, DiagnosticCategory::Error,
      "This_member_cannot_have_a_JSDoc_comment_with_an_override_tag_because_it_"
      "is_not_declared_in_the_base__4123",
      "This member cannot have a JSDoc comment with an 'override' tag because "
      "it is not declared in the base class '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Compiler_option_0_of_value_1_is_unstable_Use_nightly_TypeScript_to_silence_this_error_Try_updating_with_npm_install_D_typescript_next() {
  return diag(4124, DiagnosticCategory::Error,
              "Compiler_option_0_of_value_1_is_unstable_Use_nightly_TypeScript_"
              "to_silence_this_error_Try_updating_w_4124",
              "Compiler option '{0}' of value '{1}' is unstable. Use nightly "
              "TypeScript to silence this error. Try updating with 'npm "
              "install -D typescript@next'.");
};
static shared_ptr<DiagnosticMessage>
The_current_host_does_not_support_the_0_option() {
  return diag(5001, DiagnosticCategory::Error,
              "The_current_host_does_not_support_the_0_option_5001",
              "The current host does not support the '{0}' option.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_the_common_subdirectory_path_for_the_input_files() {
  return diag(
      5009, DiagnosticCategory::Error,
      "Cannot_find_the_common_subdirectory_path_for_the_input_files_5009",
      "Cannot find the common subdirectory path for the input files.");
};
static shared_ptr<DiagnosticMessage>
File_specification_cannot_end_in_a_recursive_directory_wildcard_Asterisk_Asterisk_Colon_0() {
  return diag(5010, DiagnosticCategory::Error,
              "File_specification_cannot_end_in_a_recursive_directory_wildcard_"
              "Asterisk_Asterisk_Colon_0_5010",
              "File specification cannot end in a recursive directory wildcard "
              "('**'): '{0}'.");
};
static shared_ptr<DiagnosticMessage> Cannot_read_file_0_Colon_1() {
  return diag(5012, DiagnosticCategory::Error,
              "Cannot_read_file_0_Colon_1_5012",
              "Cannot read file '{0}': {1}.");
};
static shared_ptr<DiagnosticMessage> Failed_to_parse_file_0_Colon_1() {
  return diag(5014, DiagnosticCategory::Error,
              "Failed_to_parse_file_0_Colon_1_5014",
              "Failed to parse file '{0}': {1}.");
};
static shared_ptr<DiagnosticMessage> Unknown_compiler_option_0() {
  return diag(5023, DiagnosticCategory::Error, "Unknown_compiler_option_0_5023",
              "Unknown compiler option '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Compiler_option_0_requires_a_value_of_type_1() {
  return diag(5024, DiagnosticCategory::Error,
              "Compiler_option_0_requires_a_value_of_type_1_5024",
              "Compiler option '{0}' requires a value of type {1}.");
};
static shared_ptr<DiagnosticMessage>
Unknown_compiler_option_0_Did_you_mean_1() {
  return diag(5025, DiagnosticCategory::Error,
              "Unknown_compiler_option_0_Did_you_mean_1_5025",
              "Unknown compiler option '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage> Could_not_write_file_0_Colon_1() {
  return diag(5033, DiagnosticCategory::Error,
              "Could_not_write_file_0_Colon_1_5033",
              "Could not write file '{0}': {1}.");
};
static shared_ptr<DiagnosticMessage>
Option_project_cannot_be_mixed_with_source_files_on_a_command_line() {
  return diag(
      5042, DiagnosticCategory::Error,
      "Option_project_cannot_be_mixed_with_source_files_on_a_command_line_5042",
      "Option 'project' cannot be mixed with source files on a command line.");
};
static shared_ptr<DiagnosticMessage>
Option_isolatedModules_can_only_be_used_when_either_option_module_is_provided_or_option_target_is_ES2015_or_higher() {
  return diag(
      5047, DiagnosticCategory::Error,
      "Option_isolatedModules_can_only_be_used_when_either_option_module_is_"
      "provided_or_option_target_is_ES_5047",
      "Option 'isolatedModules' can only be used when either option '--module' "
      "is provided or option 'target' is 'ES2015' or higher.");
};
static shared_ptr<DiagnosticMessage>
Option_0_cannot_be_specified_when_option_target_is_ES3() {
  return diag(
      5048, DiagnosticCategory::Error,
      "Option_0_cannot_be_specified_when_option_target_is_ES3_5048",
      "Option '{0}' cannot be specified when option 'target' is 'ES3'.");
};
static shared_ptr<DiagnosticMessage>
Option_0_can_only_be_used_when_either_option_inlineSourceMap_or_option_sourceMap_is_provided() {
  return diag(5051, DiagnosticCategory::Error,
              "Option_0_can_only_be_used_when_either_option_inlineSourceMap_or_"
              "option_sourceMap_is_provided_5051",
              "Option '{0} can only be used when either option "
              "'--inlineSourceMap' or option '--sourceMap' is provided.");
};
static shared_ptr<DiagnosticMessage>
Option_0_cannot_be_specified_without_specifying_option_1() {
  return diag(
      5052, DiagnosticCategory::Error,
      "Option_0_cannot_be_specified_without_specifying_option_1_5052",
      "Option '{0}' cannot be specified without specifying option '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Option_0_cannot_be_specified_with_option_1() {
  return diag(5053, DiagnosticCategory::Error,
              "Option_0_cannot_be_specified_with_option_1_5053",
              "Option '{0}' cannot be specified with option '{1}'.");
};
static shared_ptr<DiagnosticMessage>
A_tsconfig_json_file_is_already_defined_at_Colon_0() {
  return diag(5054, DiagnosticCategory::Error,
              "A_tsconfig_json_file_is_already_defined_at_Colon_0_5054",
              "A 'tsconfig.json' file is already defined at: '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_write_file_0_because_it_would_overwrite_input_file() {
  return diag(5055, DiagnosticCategory::Error,
              "Cannot_write_file_0_because_it_would_overwrite_input_file_5055",
              "Cannot write file '{0}' because it would overwrite input file.");
};
static shared_ptr<DiagnosticMessage>
Cannot_write_file_0_because_it_would_be_overwritten_by_multiple_input_files() {
  return diag(5056, DiagnosticCategory::Error,
              "Cannot_write_file_0_because_it_would_be_overwritten_by_multiple_"
              "input_files_5056",
              "Cannot write file '{0}' because it would be overwritten by "
              "multiple input files.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_a_tsconfig_json_file_at_the_specified_directory_Colon_0() {
  return diag(
      5057, DiagnosticCategory::Error,
      "Cannot_find_a_tsconfig_json_file_at_the_specified_directory_Colon_0_"
      "5057",
      "Cannot find a tsconfig.json file at the specified directory: '{0}'.");
};
static shared_ptr<DiagnosticMessage>
The_specified_path_does_not_exist_Colon_0() {
  return diag(5058, DiagnosticCategory::Error,
              "The_specified_path_does_not_exist_Colon_0_5058",
              "The specified path does not exist: '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Invalid_value_for_reactNamespace_0_is_not_a_valid_identifier() {
  return diag(
      5059, DiagnosticCategory::Error,
      "Invalid_value_for_reactNamespace_0_is_not_a_valid_identifier_5059",
      "Invalid value for '--reactNamespace'. '{0}' is not a valid identifier.");
};
static shared_ptr<DiagnosticMessage>
Pattern_0_can_have_at_most_one_Asterisk_character() {
  return diag(5061, DiagnosticCategory::Error,
              "Pattern_0_can_have_at_most_one_Asterisk_character_5061",
              "Pattern '{0}' can have at most one '*' character.");
};
static shared_ptr<DiagnosticMessage>
Substitution_0_in_pattern_1_can_have_at_most_one_Asterisk_character() {
  return diag(5062, DiagnosticCategory::Error,
              "Substitution_0_in_pattern_1_can_have_at_most_one_Asterisk_"
              "character_5062",
              "Substitution '{0}' in pattern '{1}' can have at most one '*' "
              "character.");
};
static shared_ptr<DiagnosticMessage>
Substitutions_for_pattern_0_should_be_an_array() {
  return diag(5063, DiagnosticCategory::Error,
              "Substitutions_for_pattern_0_should_be_an_array_5063",
              "Substitutions for pattern '{0}' should be an array.");
};
static shared_ptr<DiagnosticMessage>
Substitution_0_for_pattern_1_has_incorrect_type_expected_string_got_2() {
  return diag(5064, DiagnosticCategory::Error,
              "Substitution_0_for_pattern_1_has_incorrect_type_expected_string_"
              "got_2_5064",
              "Substitution '{0}' for pattern '{1}' has incorrect type, "
              "expected 'string', got '{2}'.");
};
static shared_ptr<DiagnosticMessage>
File_specification_cannot_contain_a_parent_directory_that_appears_after_a_recursive_directory_wildcard_Asterisk_Asterisk_Colon_0() {
  return diag(
      5065, DiagnosticCategory::Error,
      "File_specification_cannot_contain_a_parent_directory_that_appears_after_"
      "a_recursive_directory_wildca_5065",
      "File specification cannot contain a parent directory ('..') that "
      "appears after a recursive directory wildcard ('**'): '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Substitutions_for_pattern_0_shouldn_t_be_an_empty_array() {
  return diag(5066, DiagnosticCategory::Error,
              "Substitutions_for_pattern_0_shouldn_t_be_an_empty_array_5066",
              "Substitutions for pattern '{0}' shouldn't be an empty array.");
};
static shared_ptr<DiagnosticMessage>
Invalid_value_for_jsxFactory_0_is_not_a_valid_identifier_or_qualified_name() {
  return diag(5067, DiagnosticCategory::Error,
              "Invalid_value_for_jsxFactory_0_is_not_a_valid_identifier_or_"
              "qualified_name_5067",
              "Invalid value for 'jsxFactory'. '{0}' is not a valid identifier "
              "or qualified-name.");
};
static shared_ptr<DiagnosticMessage>
Adding_a_tsconfig_json_file_will_help_organize_projects_that_contain_both_TypeScript_and_JavaScript_files_Learn_more_at_https_Colon_Slash_Slashaka_ms_Slashtsconfig() {
  return diag(5068, DiagnosticCategory::Error,
              "Adding_a_tsconfig_json_file_will_help_organize_projects_that_"
              "contain_both_TypeScript_and_JavaScript__5068",
              "Adding a tsconfig.json file will help organize projects that "
              "contain both TypeScript and JavaScript files. Learn more at "
              "https://aka.ms/tsconfig.");
};
static shared_ptr<DiagnosticMessage>
Option_0_cannot_be_specified_without_specifying_option_1_or_option_2() {
  return diag(5069, DiagnosticCategory::Error,
              "Option_0_cannot_be_specified_without_specifying_option_1_or_"
              "option_2_5069",
              "Option '{0}' cannot be specified without specifying option "
              "'{1}' or option '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Option_resolveJsonModule_cannot_be_specified_without_node_module_resolution_strategy() {
  return diag(5070, DiagnosticCategory::Error,
              "Option_resolveJsonModule_cannot_be_specified_without_node_"
              "module_resolution_strategy_5070",
              "Option '--resolveJsonModule' cannot be specified without 'node' "
              "module resolution strategy.");
};
static shared_ptr<DiagnosticMessage>
Option_resolveJsonModule_can_only_be_specified_when_module_code_generation_is_commonjs_amd_es2015_or_esNext() {
  return diag(5071, DiagnosticCategory::Error,
              "Option_resolveJsonModule_can_only_be_specified_when_module_code_"
              "generation_is_commonjs_amd_es2015_or_5071",
              "Option '--resolveJsonModule' can only be specified when module "
              "code generation is 'commonjs', 'amd', 'es2015' or 'esNext'.");
};
static shared_ptr<DiagnosticMessage> Unknown_build_option_0() {
  return diag(5072, DiagnosticCategory::Error, "Unknown_build_option_0_5072",
              "Unknown build option '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Build_option_0_requires_a_value_of_type_1() {
  return diag(5073, DiagnosticCategory::Error,
              "Build_option_0_requires_a_value_of_type_1_5073",
              "Build option '{0}' requires a value of type {1}.");
};
static shared_ptr<DiagnosticMessage>
Option_incremental_can_only_be_specified_using_tsconfig_emitting_to_single_file_or_when_option_tsBuildInfoFile_is_specified() {
  return diag(
      5074, DiagnosticCategory::Error,
      "Option_incremental_can_only_be_specified_using_tsconfig_emitting_to_"
      "single_file_or_when_option_tsBui_5074",
      "Option '--incremental' can only be specified using tsconfig, emitting "
      "to single file or when option '--tsBuildInfoFile' is specified.");
};
static shared_ptr<DiagnosticMessage>
_0_is_assignable_to_the_constraint_of_type_1_but_1_could_be_instantiated_with_a_different_subtype_of_constraint_2() {
  return diag(
      5075, DiagnosticCategory::Error,
      "_0_is_assignable_to_the_constraint_of_type_1_but_1_could_be_"
      "instantiated_with_a_different_subtype_of_5075",
      "'{0}' is assignable to the constraint of type '{1}', but '{1}' could be "
      "instantiated with a different subtype of constraint '{2}'.");
};
static shared_ptr<DiagnosticMessage>
_0_and_1_operations_cannot_be_mixed_without_parentheses() {
  return diag(
      5076, DiagnosticCategory::Error,
      "_0_and_1_operations_cannot_be_mixed_without_parentheses_5076",
      "'{0}' and '{1}' operations cannot be mixed without parentheses.");
};
static shared_ptr<DiagnosticMessage> Unknown_build_option_0_Did_you_mean_1() {
  return diag(5077, DiagnosticCategory::Error,
              "Unknown_build_option_0_Did_you_mean_1_5077",
              "Unknown build option '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage> Unknown_watch_option_0() {
  return diag(5078, DiagnosticCategory::Error, "Unknown_watch_option_0_5078",
              "Unknown watch option '{0}'.");
};
static shared_ptr<DiagnosticMessage> Unknown_watch_option_0_Did_you_mean_1() {
  return diag(5079, DiagnosticCategory::Error,
              "Unknown_watch_option_0_Did_you_mean_1_5079",
              "Unknown watch option '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Watch_option_0_requires_a_value_of_type_1() {
  return diag(5080, DiagnosticCategory::Error,
              "Watch_option_0_requires_a_value_of_type_1_5080",
              "Watch option '{0}' requires a value of type {1}.");
};
static shared_ptr<DiagnosticMessage>
Cannot_find_a_tsconfig_json_file_at_the_current_directory_Colon_0() {
  return diag(
      5081, DiagnosticCategory::Error,
      "Cannot_find_a_tsconfig_json_file_at_the_current_directory_Colon_0_5081",
      "Cannot find a tsconfig.json file at the current directory: {0}.");
};
static shared_ptr<DiagnosticMessage>
_0_could_be_instantiated_with_an_arbitrary_type_which_could_be_unrelated_to_1() {
  return diag(5082, DiagnosticCategory::Error,
              "_0_could_be_instantiated_with_an_arbitrary_type_which_could_be_"
              "unrelated_to_1_5082",
              "'{0}' could be instantiated with an arbitrary type which could "
              "be unrelated to '{1}'.");
};
static shared_ptr<DiagnosticMessage> Cannot_read_file_0() {
  return diag(5083, DiagnosticCategory::Error, "Cannot_read_file_0_5083",
              "Cannot read file '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Tuple_members_must_all_have_names_or_all_not_have_names() {
  return diag(5084, DiagnosticCategory::Error,
              "Tuple_members_must_all_have_names_or_all_not_have_names_5084",
              "Tuple members must all have names or all not have names.");
};
static shared_ptr<DiagnosticMessage>
A_tuple_member_cannot_be_both_optional_and_rest() {
  return diag(5085, DiagnosticCategory::Error,
              "A_tuple_member_cannot_be_both_optional_and_rest_5085",
              "A tuple member cannot be both optional and rest.");
};
static shared_ptr<DiagnosticMessage>
A_labeled_tuple_element_is_declared_as_optional_with_a_question_mark_after_the_name_and_before_the_colon_rather_than_after_the_type() {
  return diag(
      5086, DiagnosticCategory::Error,
      "A_labeled_tuple_element_is_declared_as_optional_with_a_question_mark_"
      "after_the_name_and_before_the_c_5086",
      "A labeled tuple element is declared as optional with a question mark "
      "after the name and before the colon, rather than after the type.");
};
static shared_ptr<DiagnosticMessage>
A_labeled_tuple_element_is_declared_as_rest_with_a_before_the_name_rather_than_before_the_type() {
  return diag(5087, DiagnosticCategory::Error,
              "A_labeled_tuple_element_is_declared_as_rest_with_a_before_the_"
              "name_rather_than_before_the_type_5087",
              "A labeled tuple element is declared as rest with a '...' before "
              "the name, rather than before the type.");
};
static shared_ptr<DiagnosticMessage>
The_inferred_type_of_0_references_a_type_with_a_cyclic_structure_which_cannot_be_trivially_serialized_A_type_annotation_is_necessary() {
  return diag(
      5088, DiagnosticCategory::Error,
      "The_inferred_type_of_0_references_a_type_with_a_cyclic_structure_which_"
      "cannot_be_trivially_serialize_5088",
      "The inferred type of '{0}' references a type with a cyclic structure "
      "which cannot be trivially serialized. A type annotation is necessary.");
};
static shared_ptr<DiagnosticMessage>
Option_0_cannot_be_specified_when_option_jsx_is_1() {
  return diag(5089, DiagnosticCategory::Error,
              "Option_0_cannot_be_specified_when_option_jsx_is_1_5089",
              "Option '{0}' cannot be specified when option 'jsx' is '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Non_relative_paths_are_not_allowed_when_baseUrl_is_not_set_Did_you_forget_a_leading_Slash() {
  return diag(5090, DiagnosticCategory::Error,
              "Non_relative_paths_are_not_allowed_when_baseUrl_is_not_set_Did_"
              "you_forget_a_leading_Slash_5090",
              "Non-relative paths are not allowed when 'baseUrl' is not set. "
              "Did you forget a leading './'?");
};
static shared_ptr<DiagnosticMessage>
Option_preserveConstEnums_cannot_be_disabled_when_isolatedModules_is_enabled() {
  return diag(5091, DiagnosticCategory::Error,
              "Option_preserveConstEnums_cannot_be_disabled_when_"
              "isolatedModules_is_enabled_5091",
              "Option 'preserveConstEnums' cannot be disabled when "
              "'isolatedModules' is enabled.");
};
static shared_ptr<DiagnosticMessage>
The_root_value_of_a_0_file_must_be_an_object() {
  return diag(5092, DiagnosticCategory::Error,
              "The_root_value_of_a_0_file_must_be_an_object_5092",
              "The root value of a '{0}' file must be an object.");
};
static shared_ptr<DiagnosticMessage>
Compiler_option_0_may_only_be_used_with_build() {
  return diag(5093, DiagnosticCategory::Error,
              "Compiler_option_0_may_only_be_used_with_build_5093",
              "Compiler option '--{0}' may only be used with '--build'.");
};
static shared_ptr<DiagnosticMessage>
Compiler_option_0_may_not_be_used_with_build() {
  return diag(5094, DiagnosticCategory::Error,
              "Compiler_option_0_may_not_be_used_with_build_5094",
              "Compiler option '--{0}' may not be used with '--build'.");
};
static shared_ptr<DiagnosticMessage>
Option_preserveValueImports_can_only_be_used_when_module_is_set_to_es2015_or_later() {
  return diag(5095, DiagnosticCategory::Error,
              "Option_preserveValueImports_can_only_be_used_when_module_is_set_"
              "to_es2015_or_later_5095",
              "Option 'preserveValueImports' can only be used when 'module' is "
              "set to 'es2015' or later.");
};
static shared_ptr<DiagnosticMessage>
Generates_a_sourcemap_for_each_corresponding_d_ts_file() {
  return diag(6000, DiagnosticCategory::Message,
              "Generates_a_sourcemap_for_each_corresponding_d_ts_file_6000",
              "Generates a sourcemap for each corresponding '.d.ts' file.");
};
static shared_ptr<DiagnosticMessage>
Concatenate_and_emit_output_to_single_file() {
  return diag(6001, DiagnosticCategory::Message,
              "Concatenate_and_emit_output_to_single_file_6001",
              "Concatenate and emit output to single file.");
};
static shared_ptr<DiagnosticMessage> Generates_corresponding_d_ts_file() {
  return diag(6002, DiagnosticCategory::Message,
              "Generates_corresponding_d_ts_file_6002",
              "Generates corresponding '.d.ts' file.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_location_where_debugger_should_locate_TypeScript_files_instead_of_source_locations() {
  return diag(6004, DiagnosticCategory::Message,
              "Specify_the_location_where_debugger_should_locate_TypeScript_"
              "files_instead_of_source_locations_6004",
              "Specify the location where debugger should locate TypeScript "
              "files instead of source locations.");
};
static shared_ptr<DiagnosticMessage> Watch_input_files() {
  return diag(6005, DiagnosticCategory::Message, "Watch_input_files_6005",
              "Watch input files.");
};
static shared_ptr<DiagnosticMessage>
Redirect_output_structure_to_the_directory() {
  return diag(6006, DiagnosticCategory::Message,
              "Redirect_output_structure_to_the_directory_6006",
              "Redirect output structure to the directory.");
};
static shared_ptr<DiagnosticMessage>
Do_not_erase_const_enum_declarations_in_generated_code() {
  return diag(6007, DiagnosticCategory::Message,
              "Do_not_erase_const_enum_declarations_in_generated_code_6007",
              "Do not erase const enum declarations in generated code.");
};
static shared_ptr<DiagnosticMessage>
Do_not_emit_outputs_if_any_errors_were_reported() {
  return diag(6008, DiagnosticCategory::Message,
              "Do_not_emit_outputs_if_any_errors_were_reported_6008",
              "Do not emit outputs if any errors were reported.");
};
static shared_ptr<DiagnosticMessage> Do_not_emit_comments_to_output() {
  return diag(6009, DiagnosticCategory::Message,
              "Do_not_emit_comments_to_output_6009",
              "Do not emit comments to output.");
};
static shared_ptr<DiagnosticMessage> Do_not_emit_outputs() {
  return diag(6010, DiagnosticCategory::Message, "Do_not_emit_outputs_6010",
              "Do not emit outputs.");
};
static shared_ptr<DiagnosticMessage>
Allow_default_imports_from_modules_with_no_default_export_This_does_not_affect_code_emit_just_typechecking() {
  return diag(6011, DiagnosticCategory::Message,
              "Allow_default_imports_from_modules_with_no_default_export_This_"
              "does_not_affect_code_emit_just_typech_6011",
              "Allow default imports from modules with no default export. This "
              "does not affect code emit, just typechecking.");
};
static shared_ptr<DiagnosticMessage> Skip_type_checking_of_declaration_files() {
  return diag(6012, DiagnosticCategory::Message,
              "Skip_type_checking_of_declaration_files_6012",
              "Skip type checking of declaration files.");
};
static shared_ptr<DiagnosticMessage>
Do_not_resolve_the_real_path_of_symlinks() {
  return diag(6013, DiagnosticCategory::Message,
              "Do_not_resolve_the_real_path_of_symlinks_6013",
              "Do not resolve the real path of symlinks.");
};
static shared_ptr<DiagnosticMessage> Only_emit_d_ts_declaration_files() {
  return diag(6014, DiagnosticCategory::Message,
              "Only_emit_d_ts_declaration_files_6014",
              "Only emit '.d.ts' declaration files.");
};
static shared_ptr<DiagnosticMessage> Specify_ECMAScript_target_version() {
  return diag(6015, DiagnosticCategory::Message,
              "Specify_ECMAScript_target_version_6015",
              "Specify ECMAScript target version.");
};
static shared_ptr<DiagnosticMessage> Specify_module_code_generation() {
  return diag(6016, DiagnosticCategory::Message,
              "Specify_module_code_generation_6016",
              "Specify module code generation.");
};
static shared_ptr<DiagnosticMessage> Print_this_message() {
  return diag(6017, DiagnosticCategory::Message, "Print_this_message_6017",
              "Print this message.");
};
static shared_ptr<DiagnosticMessage> Print_the_compiler_s_version() {
  return diag(6019, DiagnosticCategory::Message,
              "Print_the_compiler_s_version_6019",
              "Print the compiler's version.");
};
static shared_ptr<DiagnosticMessage>
Compile_the_project_given_the_path_to_its_configuration_file_or_to_a_folder_with_a_tsconfig_json() {
  return diag(6020, DiagnosticCategory::Message,
              "Compile_the_project_given_the_path_to_its_configuration_file_or_"
              "to_a_folder_with_a_tsconfig_json_6020",
              "Compile the project given the path to its configuration file, "
              "or to a folder with a 'tsconfig.json'.");
};
static shared_ptr<DiagnosticMessage> Syntax_Colon_0() {
  return diag(6023, DiagnosticCategory::Message, "Syntax_Colon_0_6023",
              "Syntax: {0}");
};
static shared_ptr<DiagnosticMessage> options() {
  return diag(6024, DiagnosticCategory::Message, "options_6024", "options");
};
static shared_ptr<DiagnosticMessage> file() {
  return diag(6025, DiagnosticCategory::Message, "file_6025", "file");
};
static shared_ptr<DiagnosticMessage> Examples_Colon_0() {
  return diag(6026, DiagnosticCategory::Message, "Examples_Colon_0_6026",
              "Examples: {0}");
};
static shared_ptr<DiagnosticMessage> Options_Colon() {
  return diag(6027, DiagnosticCategory::Message, "Options_Colon_6027",
              "Options:");
};
static shared_ptr<DiagnosticMessage> Version_0() {
  return diag(6029, DiagnosticCategory::Message, "Version_0_6029",
              "Version {0}");
};
static shared_ptr<DiagnosticMessage>
Insert_command_line_options_and_files_from_a_file() {
  return diag(6030, DiagnosticCategory::Message,
              "Insert_command_line_options_and_files_from_a_file_6030",
              "Insert command line options and files from a file.");
};
static shared_ptr<DiagnosticMessage> Starting_compilation_in_watch_mode() {
  return diag(6031, DiagnosticCategory::Message,
              "Starting_compilation_in_watch_mode_6031",
              "Starting compilation in watch mode...");
};
static shared_ptr<DiagnosticMessage>
File_change_detected_Starting_incremental_compilation() {
  return diag(6032, DiagnosticCategory::Message,
              "File_change_detected_Starting_incremental_compilation_6032",
              "File change detected. Starting incremental compilation...");
};
static shared_ptr<DiagnosticMessage> KIND() {
  return diag(6034, DiagnosticCategory::Message, "KIND_6034", "KIND");
};
static shared_ptr<DiagnosticMessage> FILE() {
  return diag(6035, DiagnosticCategory::Message, "FILE_6035", "FILE");
};
static shared_ptr<DiagnosticMessage> VERSION() {
  return diag(6036, DiagnosticCategory::Message, "VERSION_6036", "VERSION");
};
static shared_ptr<DiagnosticMessage> LOCATION() {
  return diag(6037, DiagnosticCategory::Message, "LOCATION_6037", "LOCATION");
};
static shared_ptr<DiagnosticMessage> DIRECTORY() {
  return diag(6038, DiagnosticCategory::Message, "DIRECTORY_6038", "DIRECTORY");
};
static shared_ptr<DiagnosticMessage> STRATEGY() {
  return diag(6039, DiagnosticCategory::Message, "STRATEGY_6039", "STRATEGY");
};
static shared_ptr<DiagnosticMessage> FILE_OR_DIRECTORY() {
  return diag(6040, DiagnosticCategory::Message, "FILE_OR_DIRECTORY_6040",
              "FILE OR DIRECTORY");
};
static shared_ptr<DiagnosticMessage> Generates_corresponding_map_file() {
  return diag(6043, DiagnosticCategory::Message,
              "Generates_corresponding_map_file_6043",
              "Generates corresponding '.map' file.");
};
static shared_ptr<DiagnosticMessage> Compiler_option_0_expects_an_argument() {
  return diag(6044, DiagnosticCategory::Error,
              "Compiler_option_0_expects_an_argument_6044",
              "Compiler option '{0}' expects an argument.");
};
static shared_ptr<DiagnosticMessage>
Unterminated_quoted_string_in_response_file_0() {
  return diag(6045, DiagnosticCategory::Error,
              "Unterminated_quoted_string_in_response_file_0_6045",
              "Unterminated quoted string in response file '{0}'.");
};
static shared_ptr<DiagnosticMessage> Argument_for_0_option_must_be_Colon_1() {
  return diag(6046, DiagnosticCategory::Error,
              "Argument_for_0_option_must_be_Colon_1_6046",
              "Argument for '{0}' option must be: {1}.");
};
static shared_ptr<DiagnosticMessage>
Locale_must_be_of_the_form_language_or_language_territory_For_example_0_or_1() {
  return diag(6048, DiagnosticCategory::Error,
              "Locale_must_be_of_the_form_language_or_language_territory_For_"
              "example_0_or_1_6048",
              "Locale must be of the form <language> or "
              "<language>-<territory>. For example '{0}' or '{1}'.");
};
static shared_ptr<DiagnosticMessage> Unable_to_open_file_0() {
  return diag(6050, DiagnosticCategory::Error, "Unable_to_open_file_0_6050",
              "Unable to open file '{0}'.");
};
static shared_ptr<DiagnosticMessage> Corrupted_locale_file_0() {
  return diag(6051, DiagnosticCategory::Error, "Corrupted_locale_file_0_6051",
              "Corrupted locale file {0}.");
};
static shared_ptr<DiagnosticMessage>
Raise_error_on_expressions_and_declarations_with_an_implied_any_type() {
  return diag(6052, DiagnosticCategory::Message,
              "Raise_error_on_expressions_and_declarations_with_an_implied_any_"
              "type_6052",
              "Raise error on expressions and declarations with an implied "
              "'any' type.");
};
static shared_ptr<DiagnosticMessage> File_0_not_found() {
  return diag(6053, DiagnosticCategory::Error, "File_0_not_found_6053",
              "File '{0}' not found.");
};
static shared_ptr<DiagnosticMessage>
File_0_has_an_unsupported_extension_The_only_supported_extensions_are_1() {
  return diag(6054, DiagnosticCategory::Error,
              "File_0_has_an_unsupported_extension_The_only_supported_"
              "extensions_are_1_6054",
              "File '{0}' has an unsupported extension. The only supported "
              "extensions are {1}.");
};
static shared_ptr<DiagnosticMessage>
Suppress_noImplicitAny_errors_for_indexing_objects_lacking_index_signatures() {
  return diag(6055, DiagnosticCategory::Message,
              "Suppress_noImplicitAny_errors_for_indexing_objects_lacking_"
              "index_signatures_6055",
              "Suppress noImplicitAny errors for indexing objects lacking "
              "index signatures.");
};
static shared_ptr<DiagnosticMessage>
Do_not_emit_declarations_for_code_that_has_an_internal_annotation() {
  return diag(
      6056, DiagnosticCategory::Message,
      "Do_not_emit_declarations_for_code_that_has_an_internal_annotation_6056",
      "Do not emit declarations for code that has an '@internal' annotation.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_root_directory_of_input_files_Use_to_control_the_output_directory_structure_with_outDir() {
  return diag(6058, DiagnosticCategory::Message,
              "Specify_the_root_directory_of_input_files_Use_to_control_the_"
              "output_directory_structure_with_outDir_6058",
              "Specify the root directory of input files. Use to control the "
              "output directory structure with --outDir.");
};
static shared_ptr<DiagnosticMessage>
File_0_is_not_under_rootDir_1_rootDir_is_expected_to_contain_all_source_files() {
  return diag(6059, DiagnosticCategory::Error,
              "File_0_is_not_under_rootDir_1_rootDir_is_expected_to_contain_"
              "all_source_files_6059",
              "File '{0}' is not under 'rootDir' '{1}'. 'rootDir' is expected "
              "to contain all source files.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_end_of_line_sequence_to_be_used_when_emitting_files_Colon_CRLF_dos_or_LF_unix() {
  return diag(6060, DiagnosticCategory::Message,
              "Specify_the_end_of_line_sequence_to_be_used_when_emitting_files_"
              "Colon_CRLF_dos_or_LF_unix_6060",
              "Specify the end of line sequence to be used when emitting "
              "files: 'CRLF' (dos) or 'LF' (unix).");
};
static shared_ptr<DiagnosticMessage> NEWLINE() {
  return diag(6061, DiagnosticCategory::Message, "NEWLINE_6061", "NEWLINE");
};
static shared_ptr<DiagnosticMessage>
Option_0_can_only_be_specified_in_tsconfig_json_file_or_set_to_null_on_command_line() {
  return diag(6064, DiagnosticCategory::Error,
              "Option_0_can_only_be_specified_in_tsconfig_json_file_or_set_to_"
              "null_on_command_line_6064",
              "Option '{0}' can only be specified in 'tsconfig.json' file or "
              "set to 'null' on command line.");
};
static shared_ptr<DiagnosticMessage>
Enables_experimental_support_for_ES7_decorators() {
  return diag(6065, DiagnosticCategory::Message,
              "Enables_experimental_support_for_ES7_decorators_6065",
              "Enables experimental support for ES7 decorators.");
};
static shared_ptr<DiagnosticMessage>
Enables_experimental_support_for_emitting_type_metadata_for_decorators() {
  return diag(6066, DiagnosticCategory::Message,
              "Enables_experimental_support_for_emitting_type_metadata_for_"
              "decorators_6066",
              "Enables experimental support for emitting type metadata for "
              "decorators.");
};
static shared_ptr<DiagnosticMessage>
Specify_module_resolution_strategy_Colon_node_Node_js_or_classic_TypeScript_pre_1_6() {
  return diag(6069, DiagnosticCategory::Message,
              "Specify_module_resolution_strategy_Colon_node_Node_js_or_"
              "classic_TypeScript_pre_1_6_6069",
              "Specify module resolution strategy: 'node' (Node.js) or "
              "'classic' (TypeScript pre-1.6).");
};
static shared_ptr<DiagnosticMessage>
Initializes_a_TypeScript_project_and_creates_a_tsconfig_json_file() {
  return diag(
      6070, DiagnosticCategory::Message,
      "Initializes_a_TypeScript_project_and_creates_a_tsconfig_json_file_6070",
      "Initializes a TypeScript project and creates a tsconfig.json file.");
};
static shared_ptr<DiagnosticMessage>
Successfully_created_a_tsconfig_json_file() {
  return diag(6071, DiagnosticCategory::Message,
              "Successfully_created_a_tsconfig_json_file_6071",
              "Successfully created a tsconfig.json file.");
};
static shared_ptr<DiagnosticMessage>
Suppress_excess_property_checks_for_object_literals() {
  return diag(6072, DiagnosticCategory::Message,
              "Suppress_excess_property_checks_for_object_literals_6072",
              "Suppress excess property checks for object literals.");
};
static shared_ptr<DiagnosticMessage>
Stylize_errors_and_messages_using_color_and_context_experimental() {
  return diag(
      6073, DiagnosticCategory::Message,
      "Stylize_errors_and_messages_using_color_and_context_experimental_6073",
      "Stylize errors and messages using color and context (experimental).");
};
static shared_ptr<DiagnosticMessage> Do_not_report_errors_on_unused_labels() {
  return diag(6074, DiagnosticCategory::Message,
              "Do_not_report_errors_on_unused_labels_6074",
              "Do not report errors on unused labels.");
};
static shared_ptr<DiagnosticMessage>
Report_error_when_not_all_code_paths_in_function_return_a_value() {
  return diag(
      6075, DiagnosticCategory::Message,
      "Report_error_when_not_all_code_paths_in_function_return_a_value_6075",
      "Report error when not all code paths in function return a value.");
};
static shared_ptr<DiagnosticMessage>
Report_errors_for_fallthrough_cases_in_switch_statement() {
  return diag(6076, DiagnosticCategory::Message,
              "Report_errors_for_fallthrough_cases_in_switch_statement_6076",
              "Report errors for fallthrough cases in switch statement.");
};
static shared_ptr<DiagnosticMessage>
Do_not_report_errors_on_unreachable_code() {
  return diag(6077, DiagnosticCategory::Message,
              "Do_not_report_errors_on_unreachable_code_6077",
              "Do not report errors on unreachable code.");
};
static shared_ptr<DiagnosticMessage>
Disallow_inconsistently_cased_references_to_the_same_file() {
  return diag(6078, DiagnosticCategory::Message,
              "Disallow_inconsistently_cased_references_to_the_same_file_6078",
              "Disallow inconsistently-cased references to the same file.");
};
static shared_ptr<DiagnosticMessage>
Specify_library_files_to_be_included_in_the_compilation() {
  return diag(6079, DiagnosticCategory::Message,
              "Specify_library_files_to_be_included_in_the_compilation_6079",
              "Specify library files to be included in the compilation.");
};
static shared_ptr<DiagnosticMessage> Specify_JSX_code_generation() {
  return diag(6080, DiagnosticCategory::Message,
              "Specify_JSX_code_generation_6080",
              "Specify JSX code generation.");
};
static shared_ptr<DiagnosticMessage>
File_0_has_an_unsupported_extension_so_skipping_it() {
  return diag(6081, DiagnosticCategory::Message,
              "File_0_has_an_unsupported_extension_so_skipping_it_6081",
              "File '{0}' has an unsupported extension, so skipping it.");
};
static shared_ptr<DiagnosticMessage>
Only_amd_and_system_modules_are_supported_alongside_0() {
  return diag(6082, DiagnosticCategory::Error,
              "Only_amd_and_system_modules_are_supported_alongside_0_6082",
              "Only 'amd' and 'system' modules are supported alongside --{0}.");
};
static shared_ptr<DiagnosticMessage>
Base_directory_to_resolve_non_absolute_module_names() {
  return diag(6083, DiagnosticCategory::Message,
              "Base_directory_to_resolve_non_absolute_module_names_6083",
              "Base directory to resolve non-absolute module names.");
};
static shared_ptr<DiagnosticMessage>
Deprecated_Use_jsxFactory_instead_Specify_the_object_invoked_for_createElement_when_targeting_react_JSX_emit() {
  return diag(6084, DiagnosticCategory::Message,
              "Deprecated_Use_jsxFactory_instead_Specify_the_object_invoked_"
              "for_createElement_when_targeting_react__6084",
              "[Deprecated] Use '--jsxFactory' instead. Specify the object "
              "invoked for createElement when targeting 'react' JSX emit");
};
static shared_ptr<DiagnosticMessage>
Enable_tracing_of_the_name_resolution_process() {
  return diag(6085, DiagnosticCategory::Message,
              "Enable_tracing_of_the_name_resolution_process_6085",
              "Enable tracing of the name resolution process.");
};
static shared_ptr<DiagnosticMessage> Resolving_module_0_from_1() {
  return diag(6086, DiagnosticCategory::Message,
              "Resolving_module_0_from_1_6086",
              "======== Resolving module '{0}' from '{1}'. ========");
};
static shared_ptr<DiagnosticMessage>
Explicitly_specified_module_resolution_kind_Colon_0() {
  return diag(6087, DiagnosticCategory::Message,
              "Explicitly_specified_module_resolution_kind_Colon_0_6087",
              "Explicitly specified module resolution kind: '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Module_resolution_kind_is_not_specified_using_0() {
  return diag(6088, DiagnosticCategory::Message,
              "Module_resolution_kind_is_not_specified_using_0_6088",
              "Module resolution kind is not specified, using '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Module_name_0_was_successfully_resolved_to_1() {
  return diag(6089, DiagnosticCategory::Message,
              "Module_name_0_was_successfully_resolved_to_1_6089",
              "======== Module name '{0}' was successfully resolved to '{1}'. "
              "========");
};
static shared_ptr<DiagnosticMessage> Module_name_0_was_not_resolved() {
  return diag(6090, DiagnosticCategory::Message,
              "Module_name_0_was_not_resolved_6090",
              "======== Module name '{0}' was not resolved. ========");
};
static shared_ptr<DiagnosticMessage>
paths_option_is_specified_looking_for_a_pattern_to_match_module_name_0() {
  return diag(6091, DiagnosticCategory::Message,
              "paths_option_is_specified_looking_for_a_pattern_to_match_module_"
              "name_0_6091",
              "'paths' option is specified, looking for a pattern to match "
              "module name '{0}'.");
};
static shared_ptr<DiagnosticMessage> Module_name_0_matched_pattern_1() {
  return diag(6092, DiagnosticCategory::Message,
              "Module_name_0_matched_pattern_1_6092",
              "Module name '{0}', matched pattern '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Trying_substitution_0_candidate_module_location_Colon_1() {
  return diag(6093, DiagnosticCategory::Message,
              "Trying_substitution_0_candidate_module_location_Colon_1_6093",
              "Trying substitution '{0}', candidate module location: '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Resolving_module_name_0_relative_to_base_url_1_2() {
  return diag(
      6094, DiagnosticCategory::Message,
      "Resolving_module_name_0_relative_to_base_url_1_2_6094",
      "Resolving module name '{0}' relative to base url '{1}' - '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Loading_module_as_file_Slash_folder_candidate_module_location_0_target_file_type_1() {
  return diag(6095, DiagnosticCategory::Message,
              "Loading_module_as_file_Slash_folder_candidate_module_location_0_"
              "target_file_type_1_6095",
              "Loading module as file / folder, candidate module location "
              "'{0}', target file type '{1}'.");
};
static shared_ptr<DiagnosticMessage> File_0_does_not_exist() {
  return diag(6096, DiagnosticCategory::Message, "File_0_does_not_exist_6096",
              "File '{0}' does not exist.");
};
static shared_ptr<DiagnosticMessage>
File_0_exist_use_it_as_a_name_resolution_result() {
  return diag(6097, DiagnosticCategory::Message,
              "File_0_exist_use_it_as_a_name_resolution_result_6097",
              "File '{0}' exist - use it as a name resolution result.");
};
static shared_ptr<DiagnosticMessage>
Loading_module_0_from_node_modules_folder_target_file_type_1() {
  return diag(
      6098, DiagnosticCategory::Message,
      "Loading_module_0_from_node_modules_folder_target_file_type_1_6098",
      "Loading module '{0}' from 'node_modules' folder, target file type "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage> Found_package_json_at_0() {
  return diag(6099, DiagnosticCategory::Message, "Found_package_json_at_0_6099",
              "Found 'package.json' at '{0}'.");
};
static shared_ptr<DiagnosticMessage> package_json_does_not_have_a_0_field() {
  return diag(6100, DiagnosticCategory::Message,
              "package_json_does_not_have_a_0_field_6100",
              "'package.json' does not have a '{0}' field.");
};
static shared_ptr<DiagnosticMessage>
package_json_has_0_field_1_that_references_2() {
  return diag(6101, DiagnosticCategory::Message,
              "package_json_has_0_field_1_that_references_2_6101",
              "'package.json' has '{0}' field '{1}' that references '{2}'.");
};
static shared_ptr<DiagnosticMessage> Allow_javascript_files_to_be_compiled() {
  return diag(6102, DiagnosticCategory::Message,
              "Allow_javascript_files_to_be_compiled_6102",
              "Allow javascript files to be compiled.");
};
static shared_ptr<DiagnosticMessage>
Checking_if_0_is_the_longest_matching_prefix_for_1_2() {
  return diag(
      6104, DiagnosticCategory::Message,
      "Checking_if_0_is_the_longest_matching_prefix_for_1_2_6104",
      "Checking if '{0}' is the longest matching prefix for '{1}' - '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Expected_type_of_0_field_in_package_json_to_be_1_got_2() {
  return diag(
      6105, DiagnosticCategory::Message,
      "Expected_type_of_0_field_in_package_json_to_be_1_got_2_6105",
      "Expected type of '{0}' field in 'package.json' to be '{1}', got '{2}'.");
};
static shared_ptr<DiagnosticMessage>
baseUrl_option_is_set_to_0_using_this_value_to_resolve_non_relative_module_name_1() {
  return diag(6106, DiagnosticCategory::Message,
              "baseUrl_option_is_set_to_0_using_this_value_to_resolve_non_"
              "relative_module_name_1_6106",
              "'baseUrl' option is set to '{0}', using this value to resolve "
              "non-relative module name '{1}'.");
};
static shared_ptr<DiagnosticMessage>
rootDirs_option_is_set_using_it_to_resolve_relative_module_name_0() {
  return diag(
      6107, DiagnosticCategory::Message,
      "rootDirs_option_is_set_using_it_to_resolve_relative_module_name_0_6107",
      "'rootDirs' option is set, using it to resolve relative module name "
      "'{0}'.");
};
static shared_ptr<DiagnosticMessage> Longest_matching_prefix_for_0_is_1() {
  return diag(6108, DiagnosticCategory::Message,
              "Longest_matching_prefix_for_0_is_1_6108",
              "Longest matching prefix for '{0}' is '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Loading_0_from_the_root_dir_1_candidate_location_2() {
  return diag(
      6109, DiagnosticCategory::Message,
      "Loading_0_from_the_root_dir_1_candidate_location_2_6109",
      "Loading '{0}' from the root dir '{1}', candidate location '{2}'.");
};
static shared_ptr<DiagnosticMessage> Trying_other_entries_in_rootDirs() {
  return diag(6110, DiagnosticCategory::Message,
              "Trying_other_entries_in_rootDirs_6110",
              "Trying other entries in 'rootDirs'.");
};
static shared_ptr<DiagnosticMessage>
Module_resolution_using_rootDirs_has_failed() {
  return diag(6111, DiagnosticCategory::Message,
              "Module_resolution_using_rootDirs_has_failed_6111",
              "Module resolution using 'rootDirs' has failed.");
};
static shared_ptr<DiagnosticMessage>
Do_not_emit_use_strict_directives_in_module_output() {
  return diag(6112, DiagnosticCategory::Message,
              "Do_not_emit_use_strict_directives_in_module_output_6112",
              "Do not emit 'use strict' directives in module output.");
};
static shared_ptr<DiagnosticMessage> Enable_strict_null_checks() {
  return diag(6113, DiagnosticCategory::Message,
              "Enable_strict_null_checks_6113", "Enable strict null checks.");
};
static shared_ptr<DiagnosticMessage>
Unknown_option_excludes_Did_you_mean_exclude() {
  return diag(6114, DiagnosticCategory::Error,
              "Unknown_option_excludes_Did_you_mean_exclude_6114",
              "Unknown option 'excludes'. Did you mean 'exclude'?");
};
static shared_ptr<DiagnosticMessage>
Raise_error_on_this_expressions_with_an_implied_any_type() {
  return diag(6115, DiagnosticCategory::Message,
              "Raise_error_on_this_expressions_with_an_implied_any_type_6115",
              "Raise error on 'this' expressions with an implied 'any' type.");
};
static shared_ptr<DiagnosticMessage>
Resolving_type_reference_directive_0_containing_file_1_root_directory_2() {
  return diag(6116, DiagnosticCategory::Message,
              "Resolving_type_reference_directive_0_containing_file_1_root_"
              "directory_2_6116",
              "======== Resolving type reference directive '{0}', containing "
              "file '{1}', root directory '{2}'. ========");
};
static shared_ptr<DiagnosticMessage>
Type_reference_directive_0_was_successfully_resolved_to_1_primary_Colon_2() {
  return diag(6119, DiagnosticCategory::Message,
              "Type_reference_directive_0_was_successfully_resolved_to_1_"
              "primary_Colon_2_6119",
              "======== Type reference directive '{0}' was successfully "
              "resolved to '{1}', primary: {2}. ========");
};
static shared_ptr<DiagnosticMessage>
Type_reference_directive_0_was_not_resolved() {
  return diag(
      6120, DiagnosticCategory::Message,
      "Type_reference_directive_0_was_not_resolved_6120",
      "======== Type reference directive '{0}' was not resolved. ========");
};
static shared_ptr<DiagnosticMessage> Resolving_with_primary_search_path_0() {
  return diag(6121, DiagnosticCategory::Message,
              "Resolving_with_primary_search_path_0_6121",
              "Resolving with primary search path '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Root_directory_cannot_be_determined_skipping_primary_search_paths() {
  return diag(
      6122, DiagnosticCategory::Message,
      "Root_directory_cannot_be_determined_skipping_primary_search_paths_6122",
      "Root directory cannot be determined, skipping primary search paths.");
};
static shared_ptr<DiagnosticMessage>
Resolving_type_reference_directive_0_containing_file_1_root_directory_not_set() {
  return diag(6123, DiagnosticCategory::Message,
              "Resolving_type_reference_directive_0_containing_file_1_root_"
              "directory_not_set_6123",
              "======== Resolving type reference directive '{0}', containing "
              "file '{1}', root directory not set. ========");
};
static shared_ptr<DiagnosticMessage>
Type_declaration_files_to_be_included_in_compilation() {
  return diag(6124, DiagnosticCategory::Message,
              "Type_declaration_files_to_be_included_in_compilation_6124",
              "Type declaration files to be included in compilation.");
};
static shared_ptr<DiagnosticMessage>
Looking_up_in_node_modules_folder_initial_location_0() {
  return diag(6125, DiagnosticCategory::Message,
              "Looking_up_in_node_modules_folder_initial_location_0_6125",
              "Looking up in 'node_modules' folder, initial location '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Containing_file_is_not_specified_and_root_directory_cannot_be_determined_skipping_lookup_in_node_modules_folder() {
  return diag(6126, DiagnosticCategory::Message,
              "Containing_file_is_not_specified_and_root_directory_cannot_be_"
              "determined_skipping_lookup_in_node_mod_6126",
              "Containing file is not specified and root directory cannot be "
              "determined, skipping lookup in 'node_modules' folder.");
};
static shared_ptr<DiagnosticMessage>
Resolving_type_reference_directive_0_containing_file_not_set_root_directory_1() {
  return diag(6127, DiagnosticCategory::Message,
              "Resolving_type_reference_directive_0_containing_file_not_set_"
              "root_directory_1_6127",
              "======== Resolving type reference directive '{0}', containing "
              "file not set, root directory '{1}'. ========");
};
static shared_ptr<DiagnosticMessage>
Resolving_type_reference_directive_0_containing_file_not_set_root_directory_not_set() {
  return diag(6128, DiagnosticCategory::Message,
              "Resolving_type_reference_directive_0_containing_file_not_set_"
              "root_directory_not_set_6128",
              "======== Resolving type reference directive '{0}', containing "
              "file not set, root directory not set. ========");
};
static shared_ptr<DiagnosticMessage> Resolving_real_path_for_0_result_1() {
  return diag(6130, DiagnosticCategory::Message,
              "Resolving_real_path_for_0_result_1_6130",
              "Resolving real path for '{0}', result '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_compile_modules_using_option_0_unless_the_module_flag_is_amd_or_system() {
  return diag(6131, DiagnosticCategory::Error,
              "Cannot_compile_modules_using_option_0_unless_the_module_flag_is_"
              "amd_or_system_6131",
              "Cannot compile modules using option '{0}' unless the '--module' "
              "flag is 'amd' or 'system'.");
};
static shared_ptr<DiagnosticMessage>
File_name_0_has_a_1_extension_stripping_it() {
  return diag(6132, DiagnosticCategory::Message,
              "File_name_0_has_a_1_extension_stripping_it_6132",
              "File name '{0}' has a '{1}' extension - stripping it.");
};
static shared_ptr<DiagnosticMessage>
_0_is_declared_but_its_value_is_never_read() {
  return diag(6133, DiagnosticCategory::Error,
              "_0_is_declared_but_its_value_is_never_read_6133",
              "'{0}' is declared but its value is never read.",
              /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> Report_errors_on_unused_locals() {
  return diag(6134, DiagnosticCategory::Message,
              "Report_errors_on_unused_locals_6134",
              "Report errors on unused locals.");
};
static shared_ptr<DiagnosticMessage> Report_errors_on_unused_parameters() {
  return diag(6135, DiagnosticCategory::Message,
              "Report_errors_on_unused_parameters_6135",
              "Report errors on unused parameters.");
};
static shared_ptr<DiagnosticMessage>
The_maximum_dependency_depth_to_search_under_node_modules_and_load_JavaScript_files() {
  return diag(6136, DiagnosticCategory::Message,
              "The_maximum_dependency_depth_to_search_under_node_modules_and_"
              "load_JavaScript_files_6136",
              "The maximum dependency depth to search under node_modules and "
              "load JavaScript files.");
};
static shared_ptr<DiagnosticMessage>
Cannot_import_type_declaration_files_Consider_importing_0_instead_of_1() {
  return diag(6137, DiagnosticCategory::Error,
              "Cannot_import_type_declaration_files_Consider_importing_0_"
              "instead_of_1_6137",
              "Cannot import type declaration files. Consider importing '{0}' "
              "instead of '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_declared_but_its_value_is_never_read() {
  return diag(6138, DiagnosticCategory::Error,
              "Property_0_is_declared_but_its_value_is_never_read_6138",
              "Property '{0}' is declared but its value is never read.",
              /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> Import_emit_helpers_from_tslib() {
  return diag(6139, DiagnosticCategory::Message,
              "Import_emit_helpers_from_tslib_6139",
              "Import emit helpers from 'tslib'.");
};
static shared_ptr<DiagnosticMessage>
Auto_discovery_for_typings_is_enabled_in_project_0_Running_extra_resolution_pass_for_module_1_using_cache_location_2() {
  return diag(
      6140, DiagnosticCategory::Error,
      "Auto_discovery_for_typings_is_enabled_in_project_0_Running_extra_"
      "resolution_pass_for_module_1_using__6140",
      "Auto discovery for typings is enabled in project '{0}'. Running extra "
      "resolution pass for module '{1}' using cache location '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Parse_in_strict_mode_and_emit_use_strict_for_each_source_file() {
  return diag(
      6141, DiagnosticCategory::Message,
      "Parse_in_strict_mode_and_emit_use_strict_for_each_source_file_6141",
      "Parse in strict mode and emit \"use strict\" for each source file.");
};
static shared_ptr<DiagnosticMessage>
Module_0_was_resolved_to_1_but_jsx_is_not_set() {
  return diag(6142, DiagnosticCategory::Error,
              "Module_0_was_resolved_to_1_but_jsx_is_not_set_6142",
              "Module '{0}' was resolved to '{1}', but '--jsx' is not set.");
};
static shared_ptr<DiagnosticMessage>
Module_0_was_resolved_as_locally_declared_ambient_module_in_file_1() {
  return diag(
      6144, DiagnosticCategory::Message,
      "Module_0_was_resolved_as_locally_declared_ambient_module_in_file_1_6144",
      "Module '{0}' was resolved as locally declared ambient module in file "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Module_0_was_resolved_as_ambient_module_declared_in_1_since_this_file_was_not_modified() {
  return diag(6145, DiagnosticCategory::Message,
              "Module_0_was_resolved_as_ambient_module_declared_in_1_since_"
              "this_file_was_not_modified_6145",
              "Module '{0}' was resolved as ambient module declared in '{1}' "
              "since this file was not modified.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_JSX_factory_function_to_use_when_targeting_react_JSX_emit_e_g_React_createElement_or_h() {
  return diag(6146, DiagnosticCategory::Message,
              "Specify_the_JSX_factory_function_to_use_when_targeting_react_"
              "JSX_emit_e_g_React_createElement_or_h_6146",
              "Specify the JSX factory function to use when targeting 'react' "
              "JSX emit, e.g. 'React.createElement' or 'h'.");
};
static shared_ptr<DiagnosticMessage>
Resolution_for_module_0_was_found_in_cache_from_location_1() {
  return diag(
      6147, DiagnosticCategory::Message,
      "Resolution_for_module_0_was_found_in_cache_from_location_1_6147",
      "Resolution for module '{0}' was found in cache from location '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Directory_0_does_not_exist_skipping_all_lookups_in_it() {
  return diag(6148, DiagnosticCategory::Message,
              "Directory_0_does_not_exist_skipping_all_lookups_in_it_6148",
              "Directory '{0}' does not exist, skipping all lookups in it.");
};
static shared_ptr<DiagnosticMessage> Show_diagnostic_information() {
  return diag(6149, DiagnosticCategory::Message,
              "Show_diagnostic_information_6149",
              "Show diagnostic information.");
};
static shared_ptr<DiagnosticMessage> Show_verbose_diagnostic_information() {
  return diag(6150, DiagnosticCategory::Message,
              "Show_verbose_diagnostic_information_6150",
              "Show verbose diagnostic information.");
};
static shared_ptr<DiagnosticMessage>
Emit_a_single_file_with_source_maps_instead_of_having_a_separate_file() {
  return diag(
      6151, DiagnosticCategory::Message,
      "Emit_a_single_file_with_source_maps_instead_of_having_a_separate_file_"
      "6151",
      "Emit a single file with source maps instead of having a separate file.");
};
static shared_ptr<DiagnosticMessage>
Emit_the_source_alongside_the_sourcemaps_within_a_single_file_requires_inlineSourceMap_or_sourceMap_to_be_set() {
  return diag(6152, DiagnosticCategory::Message,
              "Emit_the_source_alongside_the_sourcemaps_within_a_single_file_"
              "requires_inlineSourceMap_or_sourceMap__6152",
              "Emit the source alongside the sourcemaps within a single file; "
              "requires '--inlineSourceMap' or '--sourceMap' to be set.");
};
static shared_ptr<DiagnosticMessage>
Transpile_each_file_as_a_separate_module_similar_to_ts_transpileModule() {
  return diag(6153, DiagnosticCategory::Message,
              "Transpile_each_file_as_a_separate_module_similar_to_ts_"
              "transpileModule_6153",
              "Transpile each file as a separate module (similar to "
              "'ts.transpileModule').");
};
static shared_ptr<DiagnosticMessage>
Print_names_of_generated_files_part_of_the_compilation() {
  return diag(6154, DiagnosticCategory::Message,
              "Print_names_of_generated_files_part_of_the_compilation_6154",
              "Print names of generated files part of the compilation.");
};
static shared_ptr<DiagnosticMessage>
Print_names_of_files_part_of_the_compilation() {
  return diag(6155, DiagnosticCategory::Message,
              "Print_names_of_files_part_of_the_compilation_6155",
              "Print names of files part of the compilation.");
};
static shared_ptr<DiagnosticMessage>
The_locale_used_when_displaying_messages_to_the_user_e_g_en_us() {
  return diag(
      6156, DiagnosticCategory::Message,
      "The_locale_used_when_displaying_messages_to_the_user_e_g_en_us_6156",
      "The locale used when displaying messages to the user (e.g. 'en-us')");
};
static shared_ptr<DiagnosticMessage>
Do_not_generate_custom_helper_functions_like_extends_in_compiled_output() {
  return diag(6157, DiagnosticCategory::Message,
              "Do_not_generate_custom_helper_functions_like_extends_in_"
              "compiled_output_6157",
              "Do not generate custom helper functions like '__extends' in "
              "compiled output.");
};
static shared_ptr<DiagnosticMessage>
Do_not_include_the_default_library_file_lib_d_ts() {
  return diag(6158, DiagnosticCategory::Message,
              "Do_not_include_the_default_library_file_lib_d_ts_6158",
              "Do not include the default library file (lib.d.ts).");
};
static shared_ptr<DiagnosticMessage>
Do_not_add_triple_slash_references_or_imported_modules_to_the_list_of_compiled_files() {
  return diag(6159, DiagnosticCategory::Message,
              "Do_not_add_triple_slash_references_or_imported_modules_to_the_"
              "list_of_compiled_files_6159",
              "Do not add triple-slash references or imported modules to the "
              "list of compiled files.");
};
static shared_ptr<DiagnosticMessage>
Deprecated_Use_skipLibCheck_instead_Skip_type_checking_of_default_library_declaration_files() {
  return diag(6160, DiagnosticCategory::Message,
              "Deprecated_Use_skipLibCheck_instead_Skip_type_checking_of_"
              "default_library_declaration_files_6160",
              "[Deprecated] Use '--skipLibCheck' instead. Skip type checking "
              "of default library declaration files.");
};
static shared_ptr<DiagnosticMessage>
List_of_folders_to_include_type_definitions_from() {
  return diag(6161, DiagnosticCategory::Message,
              "List_of_folders_to_include_type_definitions_from_6161",
              "List of folders to include type definitions from.");
};
static shared_ptr<DiagnosticMessage>
Disable_size_limitations_on_JavaScript_projects() {
  return diag(6162, DiagnosticCategory::Message,
              "Disable_size_limitations_on_JavaScript_projects_6162",
              "Disable size limitations on JavaScript projects.");
};
static shared_ptr<DiagnosticMessage> The_character_set_of_the_input_files() {
  return diag(6163, DiagnosticCategory::Message,
              "The_character_set_of_the_input_files_6163",
              "The character set of the input files.");
};
static shared_ptr<DiagnosticMessage> Do_not_truncate_error_messages() {
  return diag(6165, DiagnosticCategory::Message,
              "Do_not_truncate_error_messages_6165",
              "Do not truncate error messages.");
};
static shared_ptr<DiagnosticMessage>
Output_directory_for_generated_declaration_files() {
  return diag(6166, DiagnosticCategory::Message,
              "Output_directory_for_generated_declaration_files_6166",
              "Output directory for generated declaration files.");
};
static shared_ptr<DiagnosticMessage>
A_series_of_entries_which_re_map_imports_to_lookup_locations_relative_to_the_baseUrl() {
  return diag(6167, DiagnosticCategory::Message,
              "A_series_of_entries_which_re_map_imports_to_lookup_locations_"
              "relative_to_the_baseUrl_6167",
              "A series of entries which re-map imports to lookup locations "
              "relative to the 'baseUrl'.");
};
static shared_ptr<DiagnosticMessage>
List_of_root_folders_whose_combined_content_represents_the_structure_of_the_project_at_runtime() {
  return diag(6168, DiagnosticCategory::Message,
              "List_of_root_folders_whose_combined_content_represents_the_"
              "structure_of_the_project_at_runtime_6168",
              "List of root folders whose combined content represents the "
              "structure of the project at runtime.");
};
static shared_ptr<DiagnosticMessage> Show_all_compiler_options() {
  return diag(6169, DiagnosticCategory::Message,
              "Show_all_compiler_options_6169", "Show all compiler options.");
};
static shared_ptr<DiagnosticMessage>
Deprecated_Use_outFile_instead_Concatenate_and_emit_output_to_single_file() {
  return diag(6170, DiagnosticCategory::Message,
              "Deprecated_Use_outFile_instead_Concatenate_and_emit_output_to_"
              "single_file_6170",
              "[Deprecated] Use '--outFile' instead. Concatenate and emit "
              "output to single file");
};
static shared_ptr<DiagnosticMessage> Command_line_Options() {
  return diag(6171, DiagnosticCategory::Message, "Command_line_Options_6171",
              "Command-line Options");
};
static shared_ptr<DiagnosticMessage>
Provide_full_support_for_iterables_in_for_of_spread_and_destructuring_when_targeting_ES5_or_ES3() {
  return diag(6179, DiagnosticCategory::Message,
              "Provide_full_support_for_iterables_in_for_of_spread_and_"
              "destructuring_when_targeting_ES5_or_ES3_6179",
              "Provide full support for iterables in 'for-of', spread, and "
              "destructuring when targeting 'ES5' or 'ES3'.");
};
static shared_ptr<DiagnosticMessage> Enable_all_strict_type_checking_options() {
  return diag(6180, DiagnosticCategory::Message,
              "Enable_all_strict_type_checking_options_6180",
              "Enable all strict type-checking options.");
};
static shared_ptr<DiagnosticMessage> List_of_language_service_plugins() {
  return diag(6181, DiagnosticCategory::Message,
              "List_of_language_service_plugins_6181",
              "List of language service plugins.");
};
static shared_ptr<DiagnosticMessage> Scoped_package_detected_looking_in_0() {
  return diag(6182, DiagnosticCategory::Message,
              "Scoped_package_detected_looking_in_0_6182",
              "Scoped package detected, looking in '{0}'");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_of_old_program_it_was_successfully_resolved_to_2() {
  return diag(6183, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_of_old_program_it_was_"
              "successfully_resolved_to_2_6183",
              "Reusing resolution of module '{0}' from '{1}' of old program, "
              "it was successfully resolved to '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_of_old_program_it_was_successfully_resolved_to_2_with_Package_ID_3() {
  return diag(6184, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_of_old_program_it_was_"
              "successfully_resolved_to_2_with_Package__6184",
              "Reusing resolution of module '{0}' from '{1}' of old program, "
              "it was successfully resolved to '{2}' with Package ID '{3}'.");
};
static shared_ptr<DiagnosticMessage>
Enable_strict_checking_of_function_types() {
  return diag(6186, DiagnosticCategory::Message,
              "Enable_strict_checking_of_function_types_6186",
              "Enable strict checking of function types.");
};
static shared_ptr<DiagnosticMessage>
Enable_strict_checking_of_property_initialization_in_classes() {
  return diag(
      6187, DiagnosticCategory::Message,
      "Enable_strict_checking_of_property_initialization_in_classes_6187",
      "Enable strict checking of property initialization in classes.");
};
static shared_ptr<DiagnosticMessage> Numeric_separators_are_not_allowed_here() {
  return diag(6188, DiagnosticCategory::Error,
              "Numeric_separators_are_not_allowed_here_6188",
              "Numeric separators are not allowed here.");
};
static shared_ptr<DiagnosticMessage>
Multiple_consecutive_numeric_separators_are_not_permitted() {
  return diag(6189, DiagnosticCategory::Error,
              "Multiple_consecutive_numeric_separators_are_not_permitted_6189",
              "Multiple consecutive numeric separators are not permitted.");
};
static shared_ptr<DiagnosticMessage>
Whether_to_keep_outdated_console_output_in_watch_mode_instead_of_clearing_the_screen() {
  return diag(6191, DiagnosticCategory::Message,
              "Whether_to_keep_outdated_console_output_in_watch_mode_instead_"
              "of_clearing_the_screen_6191",
              "Whether to keep outdated console output in watch mode instead "
              "of clearing the screen.");
};
static shared_ptr<DiagnosticMessage>
All_imports_in_import_declaration_are_unused() {
  return diag(6192, DiagnosticCategory::Error,
              "All_imports_in_import_declaration_are_unused_6192",
              "All imports in import declaration are unused.",
              /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> Found_1_error_Watching_for_file_changes() {
  return diag(6193, DiagnosticCategory::Message,
              "Found_1_error_Watching_for_file_changes_6193",
              "Found 1 error. Watching for file changes.");
};
static shared_ptr<DiagnosticMessage>
Found_0_errors_Watching_for_file_changes() {
  return diag(6194, DiagnosticCategory::Message,
              "Found_0_errors_Watching_for_file_changes_6194",
              "Found {0} errors. Watching for file changes.");
};
static shared_ptr<DiagnosticMessage>
Resolve_keyof_to_string_valued_property_names_only_no_numbers_or_symbols() {
  return diag(6195, DiagnosticCategory::Message,
              "Resolve_keyof_to_string_valued_property_names_only_no_numbers_"
              "or_symbols_6195",
              "Resolve 'keyof' to string valued property names only (no "
              "numbers or symbols).");
};
static shared_ptr<DiagnosticMessage> _0_is_declared_but_never_used() {
  return diag(6196, DiagnosticCategory::Error,
              "_0_is_declared_but_never_used_6196",
              "'{0}' is declared but never used.", /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage>
Include_modules_imported_with_json_extension() {
  return diag(6197, DiagnosticCategory::Message,
              "Include_modules_imported_with_json_extension_6197",
              "Include modules imported with '.json' extension");
};
static shared_ptr<DiagnosticMessage> All_destructured_elements_are_unused() {
  return diag(6198, DiagnosticCategory::Error,
              "All_destructured_elements_are_unused_6198",
              "All destructured elements are unused.",
              /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> All_variables_are_unused() {
  return diag(6199, DiagnosticCategory::Error, "All_variables_are_unused_6199",
              "All variables are unused.", /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage>
Definitions_of_the_following_identifiers_conflict_with_those_in_another_file_Colon_0() {
  return diag(6200, DiagnosticCategory::Error,
              "Definitions_of_the_following_identifiers_conflict_with_those_in_"
              "another_file_Colon_0_6200",
              "Definitions of the following identifiers conflict with those in "
              "another file: {0}");
};
static shared_ptr<DiagnosticMessage> Conflicts_are_in_this_file() {
  return diag(6201, DiagnosticCategory::Message,
              "Conflicts_are_in_this_file_6201", "Conflicts are in this file.");
};
static shared_ptr<DiagnosticMessage>
Project_references_may_not_form_a_circular_graph_Cycle_detected_Colon_0() {
  return diag(
      6202, DiagnosticCategory::Error,
      "Project_references_may_not_form_a_circular_graph_Cycle_detected_Colon_0_"
      "6202",
      "Project references may not form a circular graph. Cycle detected: {0}");
};
static shared_ptr<DiagnosticMessage> _0_was_also_declared_here() {
  return diag(6203, DiagnosticCategory::Message,
              "_0_was_also_declared_here_6203",
              "'{0}' was also declared here.");
};
static shared_ptr<DiagnosticMessage> and_here() {
  return diag(6204, DiagnosticCategory::Message, "and_here_6204", "and here.");
};
static shared_ptr<DiagnosticMessage> All_type_parameters_are_unused() {
  return diag(6205, DiagnosticCategory::Error,
              "All_type_parameters_are_unused_6205",
              "All type parameters are unused.");
};
static shared_ptr<DiagnosticMessage>
package_json_has_a_typesVersions_field_with_version_specific_path_mappings() {
  return diag(6206, DiagnosticCategory::Message,
              "package_json_has_a_typesVersions_field_with_version_specific_"
              "path_mappings_6206",
              "'package.json' has a 'typesVersions' field with "
              "version-specific path mappings.");
};
static shared_ptr<DiagnosticMessage>
package_json_does_not_have_a_typesVersions_entry_that_matches_version_0() {
  return diag(6207, DiagnosticCategory::Message,
              "package_json_does_not_have_a_typesVersions_entry_that_matches_"
              "version_0_6207",
              "'package.json' does not have a 'typesVersions' entry that "
              "matches version '{0}'.");
};
static shared_ptr<DiagnosticMessage>
package_json_has_a_typesVersions_entry_0_that_matches_compiler_version_1_looking_for_a_pattern_to_match_module_name_2() {
  return diag(
      6208, DiagnosticCategory::Message,
      "package_json_has_a_typesVersions_entry_0_that_matches_compiler_version_"
      "1_looking_for_a_pattern_to_ma_6208",
      "'package.json' has a 'typesVersions' entry '{0}' that matches compiler "
      "version '{1}', looking for a pattern to match module name '{2}'.");
};
static shared_ptr<DiagnosticMessage>
package_json_has_a_typesVersions_entry_0_that_is_not_a_valid_semver_range() {
  return diag(6209, DiagnosticCategory::Message,
              "package_json_has_a_typesVersions_entry_0_that_is_not_a_valid_"
              "semver_range_6209",
              "'package.json' has a 'typesVersions' entry '{0}' that is not a "
              "valid semver range.");
};
static shared_ptr<DiagnosticMessage> An_argument_for_0_was_not_provided() {
  return diag(6210, DiagnosticCategory::Message,
              "An_argument_for_0_was_not_provided_6210",
              "An argument for '{0}' was not provided.");
};
static shared_ptr<DiagnosticMessage>
An_argument_matching_this_binding_pattern_was_not_provided() {
  return diag(6211, DiagnosticCategory::Message,
              "An_argument_matching_this_binding_pattern_was_not_provided_6211",
              "An argument matching this binding pattern was not provided.");
};
static shared_ptr<DiagnosticMessage> Did_you_mean_to_call_this_expression() {
  return diag(6212, DiagnosticCategory::Message,
              "Did_you_mean_to_call_this_expression_6212",
              "Did you mean to call this expression?");
};
static shared_ptr<DiagnosticMessage>
Did_you_mean_to_use_new_with_this_expression() {
  return diag(6213, DiagnosticCategory::Message,
              "Did_you_mean_to_use_new_with_this_expression_6213",
              "Did you mean to use 'new' with this expression?");
};
static shared_ptr<DiagnosticMessage>
Enable_strict_bind_call_and_apply_methods_on_functions() {
  return diag(
      6214, DiagnosticCategory::Message,
      "Enable_strict_bind_call_and_apply_methods_on_functions_6214",
      "Enable strict 'bind', 'call', and 'apply' methods on functions.");
};
static shared_ptr<DiagnosticMessage>
Using_compiler_options_of_project_reference_redirect_0() {
  return diag(6215, DiagnosticCategory::Message,
              "Using_compiler_options_of_project_reference_redirect_0_6215",
              "Using compiler options of project reference redirect '{0}'.");
};
static shared_ptr<DiagnosticMessage> Found_1_error() {
  return diag(6216, DiagnosticCategory::Message, "Found_1_error_6216",
              "Found 1 error.");
};
static shared_ptr<DiagnosticMessage> Found_0_errors() {
  return diag(6217, DiagnosticCategory::Message, "Found_0_errors_6217",
              "Found {0} errors.");
};
static shared_ptr<DiagnosticMessage>
Module_name_0_was_successfully_resolved_to_1_with_Package_ID_2() {
  return diag(
      6218, DiagnosticCategory::Message,
      "Module_name_0_was_successfully_resolved_to_1_with_Package_ID_2_6218",
      "======== Module name '{0}' was successfully resolved to '{1}' with "
      "Package ID '{2}'. ========");
};
static shared_ptr<DiagnosticMessage>
Type_reference_directive_0_was_successfully_resolved_to_1_with_Package_ID_2_primary_Colon_3() {
  return diag(
      6219, DiagnosticCategory::Message,
      "Type_reference_directive_0_was_successfully_resolved_to_1_with_Package_"
      "ID_2_primary_Colon_3_6219",
      "======== Type reference directive '{0}' was successfully resolved to "
      "'{1}' with Package ID '{2}', primary: {3}. ========");
};
static shared_ptr<DiagnosticMessage> package_json_had_a_falsy_0_field() {
  return diag(6220, DiagnosticCategory::Message,
              "package_json_had_a_falsy_0_field_6220",
              "'package.json' had a falsy '{0}' field.");
};
static shared_ptr<DiagnosticMessage>
Disable_use_of_source_files_instead_of_declaration_files_from_referenced_projects() {
  return diag(6221, DiagnosticCategory::Message,
              "Disable_use_of_source_files_instead_of_declaration_files_from_"
              "referenced_projects_6221",
              "Disable use of source files instead of declaration files from "
              "referenced projects.");
};
static shared_ptr<DiagnosticMessage>
Emit_class_fields_with_Define_instead_of_Set() {
  return diag(6222, DiagnosticCategory::Message,
              "Emit_class_fields_with_Define_instead_of_Set_6222",
              "Emit class fields with Define instead of Set.");
};
static shared_ptr<DiagnosticMessage> Generates_a_CPU_profile() {
  return diag(6223, DiagnosticCategory::Message, "Generates_a_CPU_profile_6223",
              "Generates a CPU profile.");
};
static shared_ptr<DiagnosticMessage>
Disable_solution_searching_for_this_project() {
  return diag(6224, DiagnosticCategory::Message,
              "Disable_solution_searching_for_this_project_6224",
              "Disable solution searching for this project.");
};
static shared_ptr<DiagnosticMessage>
Specify_strategy_for_watching_file_Colon_FixedPollingInterval_default_PriorityPollingInterval_DynamicPriorityPolling_FixedChunkSizePolling_UseFsEvents_UseFsEventsOnParentDirectory() {
  return diag(6225, DiagnosticCategory::Message,
              "Specify_strategy_for_watching_file_Colon_FixedPollingInterval_"
              "default_PriorityPollingInterval_Dynami_6225",
              "Specify strategy for watching file: 'FixedPollingInterval' "
              "(default), 'PriorityPollingInterval', 'DynamicPriorityPolling', "
              "'FixedChunkSizePolling', 'UseFsEvents', "
              "'UseFsEventsOnParentDirectory'.");
};
static shared_ptr<DiagnosticMessage>
Specify_strategy_for_watching_directory_on_platforms_that_don_t_support_recursive_watching_natively_Colon_UseFsEvents_default_FixedPollingInterval_DynamicPriorityPolling_FixedChunkSizePolling() {
  return diag(6226, DiagnosticCategory::Message,
              "Specify_strategy_for_watching_directory_on_platforms_that_don_t_"
              "support_recursive_watching_natively__6226",
              "Specify strategy for watching directory on platforms that don't "
              "support recursive watching natively: 'UseFsEvents' (default), "
              "'FixedPollingInterval', 'DynamicPriorityPolling', "
              "'FixedChunkSizePolling'.");
};
static shared_ptr<DiagnosticMessage>
Specify_strategy_for_creating_a_polling_watch_when_it_fails_to_create_using_file_system_events_Colon_FixedInterval_default_PriorityInterval_DynamicPriority_FixedChunkSize() {
  return diag(6227, DiagnosticCategory::Message,
              "Specify_strategy_for_creating_a_polling_watch_when_it_fails_to_"
              "create_using_file_system_events_Colon_6227",
              "Specify strategy for creating a polling watch when it fails to "
              "create using file system events: 'FixedInterval' (default), "
              "'PriorityInterval', 'DynamicPriority', 'FixedChunkSize'.");
};
static shared_ptr<DiagnosticMessage>
Tag_0_expects_at_least_1_arguments_but_the_JSX_factory_2_provides_at_most_3() {
  return diag(6229, DiagnosticCategory::Error,
              "Tag_0_expects_at_least_1_arguments_but_the_JSX_factory_2_"
              "provides_at_most_3_6229",
              "Tag '{0}' expects at least '{1}' arguments, but the JSX factory "
              "'{2}' provides at most '{3}'.");
};
static shared_ptr<DiagnosticMessage>
Option_0_can_only_be_specified_in_tsconfig_json_file_or_set_to_false_or_null_on_command_line() {
  return diag(6230, DiagnosticCategory::Error,
              "Option_0_can_only_be_specified_in_tsconfig_json_file_or_set_to_"
              "false_or_null_on_command_line_6230",
              "Option '{0}' can only be specified in 'tsconfig.json' file or "
              "set to 'false' or 'null' on command line.");
};
static shared_ptr<DiagnosticMessage>
Could_not_resolve_the_path_0_with_the_extensions_Colon_1() {
  return diag(6231, DiagnosticCategory::Error,
              "Could_not_resolve_the_path_0_with_the_extensions_Colon_1_6231",
              "Could not resolve the path '{0}' with the extensions: {1}.");
};
static shared_ptr<DiagnosticMessage>
Declaration_augments_declaration_in_another_file_This_cannot_be_serialized() {
  return diag(6232, DiagnosticCategory::Error,
              "Declaration_augments_declaration_in_another_file_This_cannot_be_"
              "serialized_6232",
              "Declaration augments declaration in another file. This cannot "
              "be serialized.");
};
static shared_ptr<DiagnosticMessage>
This_is_the_declaration_being_augmented_Consider_moving_the_augmenting_declaration_into_the_same_file() {
  return diag(6233, DiagnosticCategory::Error,
              "This_is_the_declaration_being_augmented_Consider_moving_the_"
              "augmenting_declaration_into_the_same_fil_6233",
              "This is the declaration being augmented. Consider moving the "
              "augmenting declaration into the same file.");
};
static shared_ptr<DiagnosticMessage>
This_expression_is_not_callable_because_it_is_a_get_accessor_Did_you_mean_to_use_it_without() {
  return diag(6234, DiagnosticCategory::Error,
              "This_expression_is_not_callable_because_it_is_a_get_accessor_"
              "Did_you_mean_to_use_it_without_6234",
              "This expression is not callable because it is a 'get' accessor. "
              "Did you mean to use it without '()'?");
};
static shared_ptr<DiagnosticMessage> Disable_loading_referenced_projects() {
  return diag(6235, DiagnosticCategory::Message,
              "Disable_loading_referenced_projects_6235",
              "Disable loading referenced projects.");
};
static shared_ptr<DiagnosticMessage>
Arguments_for_the_rest_parameter_0_were_not_provided() {
  return diag(6236, DiagnosticCategory::Error,
              "Arguments_for_the_rest_parameter_0_were_not_provided_6236",
              "Arguments for the rest parameter '{0}' were not provided.");
};
static shared_ptr<DiagnosticMessage>
Generates_an_event_trace_and_a_list_of_types() {
  return diag(6237, DiagnosticCategory::Message,
              "Generates_an_event_trace_and_a_list_of_types_6237",
              "Generates an event trace and a list of types.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_module_specifier_to_be_used_to_import_the_jsx_and_jsxs_factory_functions_from_eg_react() {
  return diag(6238, DiagnosticCategory::Error,
              "Specify_the_module_specifier_to_be_used_to_import_the_jsx_and_"
              "jsxs_factory_functions_from_eg_react_6238",
              "Specify the module specifier to be used to import the 'jsx' and "
              "'jsxs' factory functions from. eg, react");
};
static shared_ptr<DiagnosticMessage>
File_0_exists_according_to_earlier_cached_lookups() {
  return diag(6239, DiagnosticCategory::Message,
              "File_0_exists_according_to_earlier_cached_lookups_6239",
              "File '{0}' exists according to earlier cached lookups.");
};
static shared_ptr<DiagnosticMessage>
File_0_does_not_exist_according_to_earlier_cached_lookups() {
  return diag(6240, DiagnosticCategory::Message,
              "File_0_does_not_exist_according_to_earlier_cached_lookups_6240",
              "File '{0}' does not exist according to earlier cached lookups.");
};
static shared_ptr<DiagnosticMessage>
Resolution_for_type_reference_directive_0_was_found_in_cache_from_location_1() {
  return diag(6241, DiagnosticCategory::Message,
              "Resolution_for_type_reference_directive_0_was_found_in_cache_"
              "from_location_1_6241",
              "Resolution for type reference directive '{0}' was found in "
              "cache from location '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Resolving_type_reference_directive_0_containing_file_1() {
  return diag(6242, DiagnosticCategory::Message,
              "Resolving_type_reference_directive_0_containing_file_1_6242",
              "======== Resolving type reference directive '{0}', containing "
              "file '{1}'. ========");
};
static shared_ptr<DiagnosticMessage>
Interpret_optional_property_types_as_written_rather_than_adding_undefined() {
  return diag(6243, DiagnosticCategory::Message,
              "Interpret_optional_property_types_as_written_rather_than_adding_"
              "undefined_6243",
              "Interpret optional property types as written, rather than "
              "adding 'undefined'.");
};
static shared_ptr<DiagnosticMessage> Modules() {
  return diag(6244, DiagnosticCategory::Message, "Modules_6244", "Modules");
};
static shared_ptr<DiagnosticMessage> File_Management() {
  return diag(6245, DiagnosticCategory::Message, "File_Management_6245",
              "File Management");
};
static shared_ptr<DiagnosticMessage> Emit() {
  return diag(6246, DiagnosticCategory::Message, "Emit_6246", "Emit");
};
static shared_ptr<DiagnosticMessage> JavaScript_Support() {
  return diag(6247, DiagnosticCategory::Message, "JavaScript_Support_6247",
              "JavaScript Support");
};
static shared_ptr<DiagnosticMessage> Type_Checking() {
  return diag(6248, DiagnosticCategory::Message, "Type_Checking_6248",
              "Type Checking");
};
static shared_ptr<DiagnosticMessage> Editor_Support() {
  return diag(6249, DiagnosticCategory::Message, "Editor_Support_6249",
              "Editor Support");
};
static shared_ptr<DiagnosticMessage> Watch_and_Build_Modes() {
  return diag(6250, DiagnosticCategory::Message, "Watch_and_Build_Modes_6250",
              "Watch and Build Modes");
};
static shared_ptr<DiagnosticMessage> Compiler_Diagnostics() {
  return diag(6251, DiagnosticCategory::Message, "Compiler_Diagnostics_6251",
              "Compiler Diagnostics");
};
static shared_ptr<DiagnosticMessage> Interop_Constraints() {
  return diag(6252, DiagnosticCategory::Message, "Interop_Constraints_6252",
              "Interop Constraints");
};
static shared_ptr<DiagnosticMessage> Backwards_Compatibility() {
  return diag(6253, DiagnosticCategory::Message, "Backwards_Compatibility_6253",
              "Backwards Compatibility");
};
static shared_ptr<DiagnosticMessage> Language_and_Environment() {
  return diag(6254, DiagnosticCategory::Message,
              "Language_and_Environment_6254", "Language and Environment");
};
static shared_ptr<DiagnosticMessage> Projects() {
  return diag(6255, DiagnosticCategory::Message, "Projects_6255", "Projects");
};
static shared_ptr<DiagnosticMessage> Output_Formatting() {
  return diag(6256, DiagnosticCategory::Message, "Output_Formatting_6256",
              "Output Formatting");
};
static shared_ptr<DiagnosticMessage> Completeness() {
  return diag(6257, DiagnosticCategory::Message, "Completeness_6257",
              "Completeness");
};
static shared_ptr<DiagnosticMessage>
_0_should_be_set_inside_the_compilerOptions_object_of_the_config_json_file() {
  return diag(6258, DiagnosticCategory::Error,
              "_0_should_be_set_inside_the_compilerOptions_object_of_the_"
              "config_json_file_6258",
              "'{0}' should be set inside the 'compilerOptions' object of the "
              "config json file");
};
static shared_ptr<DiagnosticMessage>
Directory_0_has_no_containing_package_json_scope_Imports_will_not_resolve() {
  return diag(6270, DiagnosticCategory::Message,
              "Directory_0_has_no_containing_package_json_scope_Imports_will_"
              "not_resolve_6270",
              "Directory '{0}' has no containing package.json scope. Imports "
              "will not resolve.");
};
static shared_ptr<DiagnosticMessage>
Import_specifier_0_does_not_exist_in_package_json_scope_at_path_1() {
  return diag(
      6271, DiagnosticCategory::Message,
      "Import_specifier_0_does_not_exist_in_package_json_scope_at_path_1_6271",
      "Import specifier '{0}' does not exist in package.json scope at path "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
Invalid_import_specifier_0_has_no_possible_resolutions() {
  return diag(6272, DiagnosticCategory::Message,
              "Invalid_import_specifier_0_has_no_possible_resolutions_6272",
              "Invalid import specifier '{0}' has no possible resolutions.");
};
static shared_ptr<DiagnosticMessage>
package_json_scope_0_has_no_imports_defined() {
  return diag(6273, DiagnosticCategory::Message,
              "package_json_scope_0_has_no_imports_defined_6273",
              "package.json scope '{0}' has no imports defined.");
};
static shared_ptr<DiagnosticMessage>
package_json_scope_0_explicitly_maps_specifier_1_to_null() {
  return diag(
      6274, DiagnosticCategory::Message,
      "package_json_scope_0_explicitly_maps_specifier_1_to_null_6274",
      "package.json scope '{0}' explicitly maps specifier '{1}' to null.");
};
static shared_ptr<DiagnosticMessage>
package_json_scope_0_has_invalid_type_for_target_of_specifier_1() {
  return diag(
      6275, DiagnosticCategory::Message,
      "package_json_scope_0_has_invalid_type_for_target_of_specifier_1_6275",
      "package.json scope '{0}' has invalid type for target of specifier "
      "'{1}'");
};
static shared_ptr<DiagnosticMessage>
Export_specifier_0_does_not_exist_in_package_json_scope_at_path_1() {
  return diag(
      6276, DiagnosticCategory::Message,
      "Export_specifier_0_does_not_exist_in_package_json_scope_at_path_1_6276",
      "Export specifier '{0}' does not exist in package.json scope at path "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage> Enable_project_compilation() {
  return diag(6302, DiagnosticCategory::Message,
              "Enable_project_compilation_6302", "Enable project compilation");
};
static shared_ptr<DiagnosticMessage>
Composite_projects_may_not_disable_declaration_emit() {
  return diag(6304, DiagnosticCategory::Error,
              "Composite_projects_may_not_disable_declaration_emit_6304",
              "Composite projects may not disable declaration emit.");
};
static shared_ptr<DiagnosticMessage>
Output_file_0_has_not_been_built_from_source_file_1() {
  return diag(6305, DiagnosticCategory::Error,
              "Output_file_0_has_not_been_built_from_source_file_1_6305",
              "Output file '{0}' has not been built from source file '{1}'.");
};
static shared_ptr<DiagnosticMessage>
Referenced_project_0_must_have_setting_composite_Colon_true() {
  return diag(
      6306, DiagnosticCategory::Error,
      "Referenced_project_0_must_have_setting_composite_Colon_true_6306",
      "Referenced project '{0}' must have setting \"composite\": true.");
};
static shared_ptr<DiagnosticMessage>
File_0_is_not_listed_within_the_file_list_of_project_1_Projects_must_list_all_files_or_use_an_include_pattern() {
  return diag(6307, DiagnosticCategory::Error,
              "File_0_is_not_listed_within_the_file_list_of_project_1_Projects_"
              "must_list_all_files_or_use_an_includ_6307",
              "File '{0}' is not listed within the file list of project '{1}'. "
              "Projects must list all files or use an 'include' pattern.");
};
static shared_ptr<DiagnosticMessage>
Cannot_prepend_project_0_because_it_does_not_have_outFile_set() {
  return diag(
      6308, DiagnosticCategory::Error,
      "Cannot_prepend_project_0_because_it_does_not_have_outFile_set_6308",
      "Cannot prepend project '{0}' because it does not have 'outFile' set");
};
static shared_ptr<DiagnosticMessage>
Output_file_0_from_project_1_does_not_exist() {
  return diag(6309, DiagnosticCategory::Error,
              "Output_file_0_from_project_1_does_not_exist_6309",
              "Output file '{0}' from project '{1}' does not exist");
};
static shared_ptr<DiagnosticMessage>
Referenced_project_0_may_not_disable_emit() {
  return diag(6310, DiagnosticCategory::Error,
              "Referenced_project_0_may_not_disable_emit_6310",
              "Referenced project '{0}' may not disable emit.");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_out_of_date_because_oldest_output_1_is_older_than_newest_input_2() {
  return diag(6350, DiagnosticCategory::Message,
              "Project_0_is_out_of_date_because_oldest_output_1_is_older_than_"
              "newest_input_2_6350",
              "Project '{0}' is out of date because oldest output '{1}' is "
              "older than newest input '{2}'");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_up_to_date_because_newest_input_1_is_older_than_oldest_output_2() {
  return diag(6351, DiagnosticCategory::Message,
              "Project_0_is_up_to_date_because_newest_input_1_is_older_than_"
              "oldest_output_2_6351",
              "Project '{0}' is up to date because newest input '{1}' is older "
              "than oldest output '{2}'");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_out_of_date_because_output_file_1_does_not_exist() {
  return diag(
      6352, DiagnosticCategory::Message,
      "Project_0_is_out_of_date_because_output_file_1_does_not_exist_6352",
      "Project '{0}' is out of date because output file '{1}' does not exist");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_out_of_date_because_its_dependency_1_is_out_of_date() {
  return diag(
      6353, DiagnosticCategory::Message,
      "Project_0_is_out_of_date_because_its_dependency_1_is_out_of_date_6353",
      "Project '{0}' is out of date because its dependency '{1}' is out of "
      "date");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_up_to_date_with_d_ts_files_from_its_dependencies() {
  return diag(
      6354, DiagnosticCategory::Message,
      "Project_0_is_up_to_date_with_d_ts_files_from_its_dependencies_6354",
      "Project '{0}' is up to date with .d.ts files from its dependencies");
};
static shared_ptr<DiagnosticMessage> Projects_in_this_build_Colon_0() {
  return diag(6355, DiagnosticCategory::Message,
              "Projects_in_this_build_Colon_0_6355",
              "Projects in this build: {0}");
};
static shared_ptr<DiagnosticMessage>
A_non_dry_build_would_delete_the_following_files_Colon_0() {
  return diag(6356, DiagnosticCategory::Message,
              "A_non_dry_build_would_delete_the_following_files_Colon_0_6356",
              "A non-dry build would delete the following files: {0}");
};
static shared_ptr<DiagnosticMessage> A_non_dry_build_would_build_project_0() {
  return diag(6357, DiagnosticCategory::Message,
              "A_non_dry_build_would_build_project_0_6357",
              "A non-dry build would build project '{0}'");
};
static shared_ptr<DiagnosticMessage> Building_project_0() {
  return diag(6358, DiagnosticCategory::Message, "Building_project_0_6358",
              "Building project '{0}'...");
};
static shared_ptr<DiagnosticMessage> Updating_output_timestamps_of_project_0() {
  return diag(6359, DiagnosticCategory::Message,
              "Updating_output_timestamps_of_project_0_6359",
              "Updating output timestamps of project '{0}'...");
};
static shared_ptr<DiagnosticMessage> Project_0_is_up_to_date() {
  return diag(6361, DiagnosticCategory::Message, "Project_0_is_up_to_date_6361",
              "Project '{0}' is up to date");
};
static shared_ptr<DiagnosticMessage>
Skipping_build_of_project_0_because_its_dependency_1_has_errors() {
  return diag(
      6362, DiagnosticCategory::Message,
      "Skipping_build_of_project_0_because_its_dependency_1_has_errors_6362",
      "Skipping build of project '{0}' because its dependency '{1}' has "
      "errors");
};
static shared_ptr<DiagnosticMessage>
Project_0_can_t_be_built_because_its_dependency_1_has_errors() {
  return diag(
      6363, DiagnosticCategory::Message,
      "Project_0_can_t_be_built_because_its_dependency_1_has_errors_6363",
      "Project '{0}' can't be built because its dependency '{1}' has errors");
};
static shared_ptr<DiagnosticMessage>
Build_one_or_more_projects_and_their_dependencies_if_out_of_date() {
  return diag(
      6364, DiagnosticCategory::Message,
      "Build_one_or_more_projects_and_their_dependencies_if_out_of_date_6364",
      "Build one or more projects and their dependencies, if out of date");
};
static shared_ptr<DiagnosticMessage> Delete_the_outputs_of_all_projects() {
  return diag(6365, DiagnosticCategory::Message,
              "Delete_the_outputs_of_all_projects_6365",
              "Delete the outputs of all projects");
};
static shared_ptr<DiagnosticMessage>
Show_what_would_be_built_or_deleted_if_specified_with_clean() {
  return diag(
      6367, DiagnosticCategory::Message,
      "Show_what_would_be_built_or_deleted_if_specified_with_clean_6367",
      "Show what would be built (or deleted, if specified with '--clean')");
};
static shared_ptr<DiagnosticMessage>
Option_build_must_be_the_first_command_line_argument() {
  return diag(6369, DiagnosticCategory::Error,
              "Option_build_must_be_the_first_command_line_argument_6369",
              "Option '--build' must be the first command line argument.");
};
static shared_ptr<DiagnosticMessage> Options_0_and_1_cannot_be_combined() {
  return diag(6370, DiagnosticCategory::Error,
              "Options_0_and_1_cannot_be_combined_6370",
              "Options '{0}' and '{1}' cannot be combined.");
};
static shared_ptr<DiagnosticMessage>
Updating_unchanged_output_timestamps_of_project_0() {
  return diag(6371, DiagnosticCategory::Message,
              "Updating_unchanged_output_timestamps_of_project_0_6371",
              "Updating unchanged output timestamps of project '{0}'...");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_out_of_date_because_output_of_its_dependency_1_has_changed() {
  return diag(6372, DiagnosticCategory::Message,
              "Project_0_is_out_of_date_because_output_of_its_dependency_1_has_"
              "changed_6372",
              "Project '{0}' is out of date because output of its dependency "
              "'{1}' has changed");
};
static shared_ptr<DiagnosticMessage> Updating_output_of_project_0() {
  return diag(6373, DiagnosticCategory::Message,
              "Updating_output_of_project_0_6373",
              "Updating output of project '{0}'...");
};
static shared_ptr<DiagnosticMessage>
A_non_dry_build_would_update_timestamps_for_output_of_project_0() {
  return diag(
      6374, DiagnosticCategory::Message,
      "A_non_dry_build_would_update_timestamps_for_output_of_project_0_6374",
      "A non-dry build would update timestamps for output of project '{0}'");
};
static shared_ptr<DiagnosticMessage>
A_non_dry_build_would_update_output_of_project_0() {
  return diag(6375, DiagnosticCategory::Message,
              "A_non_dry_build_would_update_output_of_project_0_6375",
              "A non-dry build would update output of project '{0}'");
};
static shared_ptr<DiagnosticMessage>
Cannot_update_output_of_project_0_because_there_was_error_reading_file_1() {
  return diag(6376, DiagnosticCategory::Message,
              "Cannot_update_output_of_project_0_because_there_was_error_"
              "reading_file_1_6376",
              "Cannot update output of project '{0}' because there was error "
              "reading file '{1}'");
};
static shared_ptr<DiagnosticMessage>
Cannot_write_file_0_because_it_will_overwrite_tsbuildinfo_file_generated_by_referenced_project_1() {
  return diag(6377, DiagnosticCategory::Error,
              "Cannot_write_file_0_because_it_will_overwrite_tsbuildinfo_file_"
              "generated_by_referenced_project_1_6377",
              "Cannot write file '{0}' because it will overwrite "
              "'.tsbuildinfo' file generated by referenced project '{1}'");
};
static shared_ptr<DiagnosticMessage> Enable_incremental_compilation() {
  return diag(6378, DiagnosticCategory::Message,
              "Enable_incremental_compilation_6378",
              "Enable incremental compilation");
};
static shared_ptr<DiagnosticMessage>
Composite_projects_may_not_disable_incremental_compilation() {
  return diag(6379, DiagnosticCategory::Error,
              "Composite_projects_may_not_disable_incremental_compilation_6379",
              "Composite projects may not disable incremental compilation.");
};
static shared_ptr<DiagnosticMessage>
Specify_file_to_store_incremental_compilation_information() {
  return diag(6380, DiagnosticCategory::Message,
              "Specify_file_to_store_incremental_compilation_information_6380",
              "Specify file to store incremental compilation information");
};
static shared_ptr<DiagnosticMessage>
Project_0_is_out_of_date_because_output_for_it_was_generated_with_version_1_that_differs_with_current_version_2() {
  return diag(
      6381, DiagnosticCategory::Message,
      "Project_0_is_out_of_date_because_output_for_it_was_generated_with_"
      "version_1_that_differs_with_curren_6381",
      "Project '{0}' is out of date because output for it was generated with "
      "version '{1}' that differs with current version '{2}'");
};
static shared_ptr<DiagnosticMessage>
Skipping_build_of_project_0_because_its_dependency_1_was_not_built() {
  return diag(
      6382, DiagnosticCategory::Message,
      "Skipping_build_of_project_0_because_its_dependency_1_was_not_built_6382",
      "Skipping build of project '{0}' because its dependency '{1}' was not "
      "built");
};
static shared_ptr<DiagnosticMessage>
Project_0_can_t_be_built_because_its_dependency_1_was_not_built() {
  return diag(
      6383, DiagnosticCategory::Message,
      "Project_0_can_t_be_built_because_its_dependency_1_was_not_built_6383",
      "Project '{0}' can't be built because its dependency '{1}' was not "
      "built");
};
static shared_ptr<DiagnosticMessage>
Have_recompiles_in_incremental_and_watch_assume_that_changes_within_a_file_will_only_affect_files_directly_depending_on_it() {
  return diag(
      6384, DiagnosticCategory::Message,
      "Have_recompiles_in_incremental_and_watch_assume_that_changes_within_a_"
      "file_will_only_affect_files_di_6384",
      "Have recompiles in '--incremental' and '--watch' assume that changes "
      "within a file will only affect files directly depending on it.");
};
static shared_ptr<DiagnosticMessage> _0_is_deprecated() {
  return diag(6385, DiagnosticCategory::Suggestion, "_0_is_deprecated_6385",
              "'{0}' is deprecated.", /*reportsUnnecessary*/ false,
              /*elidedInCompatabilityPyramid*/ false,
              /*reportsDeprecated*/ true);
};
static shared_ptr<DiagnosticMessage>
Performance_timings_for_diagnostics_or_extendedDiagnostics_are_not_available_in_this_session_A_native_implementation_of_the_Web_Performance_API_could_not_be_found() {
  return diag(
      6386, DiagnosticCategory::Message,
      "Performance_timings_for_diagnostics_or_extendedDiagnostics_are_not_"
      "available_in_this_session_A_nativ_6386",
      "Performance timings for '--diagnostics' or '--extendedDiagnostics' are "
      "not available in this session. A native implementation of the Web "
      "Performance API could not be found.");
};
static shared_ptr<DiagnosticMessage> The_signature_0_of_1_is_deprecated() {
  return diag(6387, DiagnosticCategory::Suggestion,
              "The_signature_0_of_1_is_deprecated_6387",
              "The signature '{0}' of '{1}' is deprecated.",
              /*reportsUnnecessary*/ false,
              /*elidedInCompatabilityPyramid*/ false,
              /*reportsDeprecated*/ true);
};
static shared_ptr<DiagnosticMessage> Project_0_is_being_forcibly_rebuilt() {
  return diag(6388, DiagnosticCategory::Message,
              "Project_0_is_being_forcibly_rebuilt_6388",
              "Project '{0}' is being forcibly rebuilt");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_of_old_program_it_was_not_resolved() {
  return diag(6389, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_of_old_program_it_was_not_"
              "resolved_6389",
              "Reusing resolution of module '{0}' from '{1}' of old program, "
              "it was not resolved.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_of_old_program_it_was_successfully_resolved_to_2() {
  return diag(6390, DiagnosticCategory::Message,
              "Reusing_resolution_of_type_reference_directive_0_from_1_of_old_"
              "program_it_was_successfully_resolved__6390",
              "Reusing resolution of type reference directive '{0}' from '{1}' "
              "of old program, it was successfully resolved to '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_of_old_program_it_was_successfully_resolved_to_2_with_Package_ID_3() {
  return diag(
      6391, DiagnosticCategory::Message,
      "Reusing_resolution_of_type_reference_directive_0_from_1_of_old_program_"
      "it_was_successfully_resolved__6391",
      "Reusing resolution of type reference directive '{0}' from '{1}' of old "
      "program, it was successfully resolved to '{2}' with Package ID '{3}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_of_old_program_it_was_not_resolved() {
  return diag(6392, DiagnosticCategory::Message,
              "Reusing_resolution_of_type_reference_directive_0_from_1_of_old_"
              "program_it_was_not_resolved_6392",
              "Reusing resolution of type reference directive '{0}' from '{1}' "
              "of old program, it was not resolved.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_found_in_cache_from_location_2_it_was_successfully_resolved_to_3() {
  return diag(6393, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_found_in_cache_from_"
              "location_2_it_was_successfully_resolved_to_6393",
              "Reusing resolution of module '{0}' from '{1}' found in cache "
              "from location '{2}', it was successfully resolved to '{3}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_found_in_cache_from_location_2_it_was_successfully_resolved_to_3_with_Package_ID_4() {
  return diag(6394, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_found_in_cache_from_"
              "location_2_it_was_successfully_resolved_to_6394",
              "Reusing resolution of module '{0}' from '{1}' found in cache "
              "from location '{2}', it was successfully resolved to '{3}' with "
              "Package ID '{4}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_module_0_from_1_found_in_cache_from_location_2_it_was_not_resolved() {
  return diag(6395, DiagnosticCategory::Message,
              "Reusing_resolution_of_module_0_from_1_found_in_cache_from_"
              "location_2_it_was_not_resolved_6395",
              "Reusing resolution of module '{0}' from '{1}' found in cache "
              "from location '{2}', it was not resolved.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_found_in_cache_from_location_2_it_was_successfully_resolved_to_3() {
  return diag(
      6396, DiagnosticCategory::Message,
      "Reusing_resolution_of_type_reference_directive_0_from_1_found_in_cache_"
      "from_location_2_it_was_succes_6396",
      "Reusing resolution of type reference directive '{0}' from '{1}' found "
      "in cache from location '{2}', it was successfully resolved to '{3}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_found_in_cache_from_location_2_it_was_successfully_resolved_to_3_with_Package_ID_4() {
  return diag(6397, DiagnosticCategory::Message,
              "Reusing_resolution_of_type_reference_directive_0_from_1_found_"
              "in_cache_from_location_2_it_was_succes_6397",
              "Reusing resolution of type reference directive '{0}' from '{1}' "
              "found in cache from location '{2}', it was successfully "
              "resolved to '{3}' with Package ID '{4}'.");
};
static shared_ptr<DiagnosticMessage>
Reusing_resolution_of_type_reference_directive_0_from_1_found_in_cache_from_location_2_it_was_not_resolved() {
  return diag(6398, DiagnosticCategory::Message,
              "Reusing_resolution_of_type_reference_directive_0_from_1_found_"
              "in_cache_from_location_2_it_was_not_re_6398",
              "Reusing resolution of type reference directive '{0}' from '{1}' "
              "found in cache from location '{2}', it was not resolved.");
};
static shared_ptr<DiagnosticMessage>
The_expected_type_comes_from_property_0_which_is_declared_here_on_type_1() {
  return diag(6500, DiagnosticCategory::Message,
              "The_expected_type_comes_from_property_0_which_is_declared_here_"
              "on_type_1_6500",
              "The expected type comes from property '{0}' which is declared "
              "here on type '{1}'");
};
static shared_ptr<DiagnosticMessage>
The_expected_type_comes_from_this_index_signature() {
  return diag(6501, DiagnosticCategory::Message,
              "The_expected_type_comes_from_this_index_signature_6501",
              "The expected type comes from this index signature.");
};
static shared_ptr<DiagnosticMessage>
The_expected_type_comes_from_the_return_type_of_this_signature() {
  return diag(
      6502, DiagnosticCategory::Message,
      "The_expected_type_comes_from_the_return_type_of_this_signature_6502",
      "The expected type comes from the return type of this signature.");
};
static shared_ptr<DiagnosticMessage>
Print_names_of_files_that_are_part_of_the_compilation_and_then_stop_processing() {
  return diag(6503, DiagnosticCategory::Message,
              "Print_names_of_files_that_are_part_of_the_compilation_and_then_"
              "stop_processing_6503",
              "Print names of files that are part of the compilation and then "
              "stop processing.");
};
static shared_ptr<DiagnosticMessage>
File_0_is_a_JavaScript_file_Did_you_mean_to_enable_the_allowJs_option() {
  return diag(6504, DiagnosticCategory::Error,
              "File_0_is_a_JavaScript_file_Did_you_mean_to_enable_the_allowJs_"
              "option_6504",
              "File '{0}' is a JavaScript file. Did you mean to enable the "
              "'allowJs' option?");
};
static shared_ptr<DiagnosticMessage>
Print_names_of_files_and_the_reason_they_are_part_of_the_compilation() {
  return diag(
      6505, DiagnosticCategory::Message,
      "Print_names_of_files_and_the_reason_they_are_part_of_the_compilation_"
      "6505",
      "Print names of files and the reason they are part of the compilation.");
};
static shared_ptr<DiagnosticMessage>
Consider_adding_a_declare_modifier_to_this_class() {
  return diag(6506, DiagnosticCategory::Message,
              "Consider_adding_a_declare_modifier_to_this_class_6506",
              "Consider adding a 'declare' modifier to this class.");
};
static shared_ptr<DiagnosticMessage>
Allow_JavaScript_files_to_be_a_part_of_your_program_Use_the_checkJS_option_to_get_errors_from_these_files() {
  return diag(6600, DiagnosticCategory::Message,
              "Allow_JavaScript_files_to_be_a_part_of_your_program_Use_the_"
              "checkJS_option_to_get_errors_from_these__6600",
              "Allow JavaScript files to be a part of your program. Use the "
              "`checkJS` option to get errors from these files.");
};
static shared_ptr<DiagnosticMessage>
Allow_import_x_from_y_when_a_module_doesn_t_have_a_default_export() {
  return diag(
      6601, DiagnosticCategory::Message,
      "Allow_import_x_from_y_when_a_module_doesn_t_have_a_default_export_6601",
      "Allow 'import x from y' when a module doesn't have a default export.");
};
static shared_ptr<DiagnosticMessage>
Allow_accessing_UMD_globals_from_modules() {
  return diag(6602, DiagnosticCategory::Message,
              "Allow_accessing_UMD_globals_from_modules_6602",
              "Allow accessing UMD globals from modules.");
};
static shared_ptr<DiagnosticMessage>
Disable_error_reporting_for_unreachable_code() {
  return diag(6603, DiagnosticCategory::Message,
              "Disable_error_reporting_for_unreachable_code_6603",
              "Disable error reporting for unreachable code.");
};
static shared_ptr<DiagnosticMessage>
Disable_error_reporting_for_unused_labels() {
  return diag(6604, DiagnosticCategory::Message,
              "Disable_error_reporting_for_unused_labels_6604",
              "Disable error reporting for unused labels.");
};
static shared_ptr<DiagnosticMessage> Ensure_use_strict_is_always_emitted() {
  return diag(6605, DiagnosticCategory::Message,
              "Ensure_use_strict_is_always_emitted_6605",
              "Ensure 'use strict' is always emitted.");
};
static shared_ptr<DiagnosticMessage>
Have_recompiles_in_projects_that_use_incremental_and_watch_mode_assume_that_changes_within_a_file_will_only_affect_files_directly_depending_on_it() {
  return diag(6606, DiagnosticCategory::Message,
              "Have_recompiles_in_projects_that_use_incremental_and_watch_mode_"
              "assume_that_changes_within_a_file_wi_6606",
              "Have recompiles in projects that use `incremental` and `watch` "
              "mode assume that changes within a file will only affect files "
              "directly depending on it.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_base_directory_to_resolve_non_relative_module_names() {
  return diag(
      6607, DiagnosticCategory::Message,
      "Specify_the_base_directory_to_resolve_non_relative_module_names_6607",
      "Specify the base directory to resolve non-relative module names.");
};
static shared_ptr<DiagnosticMessage>
No_longer_supported_In_early_versions_manually_set_the_text_encoding_for_reading_files() {
  return diag(6608, DiagnosticCategory::Message,
              "No_longer_supported_In_early_versions_manually_set_the_text_"
              "encoding_for_reading_files_6608",
              "No longer supported. In early versions, manually set the text "
              "encoding for reading files.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_in_type_checked_JavaScript_files() {
  return diag(6609, DiagnosticCategory::Message,
              "Enable_error_reporting_in_type_checked_JavaScript_files_6609",
              "Enable error reporting in type-checked JavaScript files.");
};
static shared_ptr<DiagnosticMessage>
Enable_constraints_that_allow_a_TypeScript_project_to_be_used_with_project_references() {
  return diag(6611, DiagnosticCategory::Message,
              "Enable_constraints_that_allow_a_TypeScript_project_to_be_used_"
              "with_project_references_6611",
              "Enable constraints that allow a TypeScript project to be used "
              "with project references.");
};
static shared_ptr<DiagnosticMessage>
Generate_d_ts_files_from_TypeScript_and_JavaScript_files_in_your_project() {
  return diag(6612, DiagnosticCategory::Message,
              "Generate_d_ts_files_from_TypeScript_and_JavaScript_files_in_"
              "your_project_6612",
              "Generate .d.ts files from TypeScript and JavaScript files in "
              "your project.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_output_directory_for_generated_declaration_files() {
  return diag(
      6613, DiagnosticCategory::Message,
      "Specify_the_output_directory_for_generated_declaration_files_6613",
      "Specify the output directory for generated declaration files.");
};
static shared_ptr<DiagnosticMessage> Create_sourcemaps_for_d_ts_files() {
  return diag(6614, DiagnosticCategory::Message,
              "Create_sourcemaps_for_d_ts_files_6614",
              "Create sourcemaps for d.ts files.");
};
static shared_ptr<DiagnosticMessage>
Output_compiler_performance_information_after_building() {
  return diag(6615, DiagnosticCategory::Message,
              "Output_compiler_performance_information_after_building_6615",
              "Output compiler performance information after building.");
};
static shared_ptr<DiagnosticMessage>
Disables_inference_for_type_acquisition_by_looking_at_filenames_in_a_project() {
  return diag(6616, DiagnosticCategory::Message,
              "Disables_inference_for_type_acquisition_by_looking_at_filenames_"
              "in_a_project_6616",
              "Disables inference for type acquisition by looking at filenames "
              "in a project.");
};
static shared_ptr<DiagnosticMessage>
Reduce_the_number_of_projects_loaded_automatically_by_TypeScript() {
  return diag(
      6617, DiagnosticCategory::Message,
      "Reduce_the_number_of_projects_loaded_automatically_by_TypeScript_6617",
      "Reduce the number of projects loaded automatically by TypeScript.");
};
static shared_ptr<DiagnosticMessage>
Remove_the_20mb_cap_on_total_source_code_size_for_JavaScript_files_in_the_TypeScript_language_server() {
  return diag(6618, DiagnosticCategory::Message,
              "Remove_the_20mb_cap_on_total_source_code_size_for_JavaScript_"
              "files_in_the_TypeScript_language_server_6618",
              "Remove the 20mb cap on total source code size for JavaScript "
              "files in the TypeScript language server.");
};
static shared_ptr<DiagnosticMessage>
Opt_a_project_out_of_multi_project_reference_checking_when_editing() {
  return diag(
      6619, DiagnosticCategory::Message,
      "Opt_a_project_out_of_multi_project_reference_checking_when_editing_6619",
      "Opt a project out of multi-project reference checking when editing.");
};
static shared_ptr<DiagnosticMessage>
Disable_preferring_source_files_instead_of_declaration_files_when_referencing_composite_projects() {
  return diag(6620, DiagnosticCategory::Message,
              "Disable_preferring_source_files_instead_of_declaration_files_"
              "when_referencing_composite_projects_6620",
              "Disable preferring source files instead of declaration files "
              "when referencing composite projects");
};
static shared_ptr<DiagnosticMessage>
Emit_more_compliant_but_verbose_and_less_performant_JavaScript_for_iteration() {
  return diag(6621, DiagnosticCategory::Message,
              "Emit_more_compliant_but_verbose_and_less_performant_JavaScript_"
              "for_iteration_6621",
              "Emit more compliant, but verbose and less performant JavaScript "
              "for iteration.");
};
static shared_ptr<DiagnosticMessage>
Emit_a_UTF_8_Byte_Order_Mark_BOM_in_the_beginning_of_output_files() {
  return diag(
      6622, DiagnosticCategory::Message,
      "Emit_a_UTF_8_Byte_Order_Mark_BOM_in_the_beginning_of_output_files_6622",
      "Emit a UTF-8 Byte Order Mark (BOM) in the beginning of output files.");
};
static shared_ptr<DiagnosticMessage>
Only_output_d_ts_files_and_not_JavaScript_files() {
  return diag(6623, DiagnosticCategory::Message,
              "Only_output_d_ts_files_and_not_JavaScript_files_6623",
              "Only output d.ts files and not JavaScript files.");
};
static shared_ptr<DiagnosticMessage>
Emit_design_type_metadata_for_decorated_declarations_in_source_files() {
  return diag(
      6624, DiagnosticCategory::Message,
      "Emit_design_type_metadata_for_decorated_declarations_in_source_files_"
      "6624",
      "Emit design-type metadata for decorated declarations in source files.");
};
static shared_ptr<DiagnosticMessage>
Disable_the_type_acquisition_for_JavaScript_projects() {
  return diag(6625, DiagnosticCategory::Message,
              "Disable_the_type_acquisition_for_JavaScript_projects_6625",
              "Disable the type acquisition for JavaScript projects");
};
static shared_ptr<DiagnosticMessage>
Emit_additional_JavaScript_to_ease_support_for_importing_CommonJS_modules_This_enables_allowSyntheticDefaultImports_for_type_compatibility() {
  return diag(6626, DiagnosticCategory::Message,
              "Emit_additional_JavaScript_to_ease_support_for_importing_"
              "CommonJS_modules_This_enables_allowSyntheti_6626",
              "Emit additional JavaScript to ease support for importing "
              "CommonJS modules. This enables `allowSyntheticDefaultImports` "
              "for type compatibility.");
};
static shared_ptr<DiagnosticMessage> Filters_results_from_the_include_option() {
  return diag(6627, DiagnosticCategory::Message,
              "Filters_results_from_the_include_option_6627",
              "Filters results from the `include` option.");
};
static shared_ptr<DiagnosticMessage>
Remove_a_list_of_directories_from_the_watch_process() {
  return diag(6628, DiagnosticCategory::Message,
              "Remove_a_list_of_directories_from_the_watch_process_6628",
              "Remove a list of directories from the watch process.");
};
static shared_ptr<DiagnosticMessage>
Remove_a_list_of_files_from_the_watch_mode_s_processing() {
  return diag(6629, DiagnosticCategory::Message,
              "Remove_a_list_of_files_from_the_watch_mode_s_processing_6629",
              "Remove a list of files from the watch mode's processing.");
};
static shared_ptr<DiagnosticMessage>
Enable_experimental_support_for_TC39_stage_2_draft_decorators() {
  return diag(
      6630, DiagnosticCategory::Message,
      "Enable_experimental_support_for_TC39_stage_2_draft_decorators_6630",
      "Enable experimental support for TC39 stage 2 draft decorators.");
};
static shared_ptr<DiagnosticMessage>
Print_files_read_during_the_compilation_including_why_it_was_included() {
  return diag(
      6631, DiagnosticCategory::Message,
      "Print_files_read_during_the_compilation_including_why_it_was_included_"
      "6631",
      "Print files read during the compilation including why it was included.");
};
static shared_ptr<DiagnosticMessage>
Output_more_detailed_compiler_performance_information_after_building() {
  return diag(
      6632, DiagnosticCategory::Message,
      "Output_more_detailed_compiler_performance_information_after_building_"
      "6632",
      "Output more detailed compiler performance information after building.");
};
static shared_ptr<DiagnosticMessage>
Specify_one_or_more_path_or_node_module_references_to_base_configuration_files_from_which_settings_are_inherited() {
  return diag(6633, DiagnosticCategory::Message,
              "Specify_one_or_more_path_or_node_module_references_to_base_"
              "configuration_files_from_which_settings_a_6633",
              "Specify one or more path or node module references to base "
              "configuration files from which settings are inherited.");
};
static shared_ptr<DiagnosticMessage>
Specify_what_approach_the_watcher_should_use_if_the_system_runs_out_of_native_file_watchers() {
  return diag(6634, DiagnosticCategory::Message,
              "Specify_what_approach_the_watcher_should_use_if_the_system_runs_"
              "out_of_native_file_watchers_6634",
              "Specify what approach the watcher should use if the system runs "
              "out of native file watchers.");
};
static shared_ptr<DiagnosticMessage>
Include_a_list_of_files_This_does_not_support_glob_patterns_as_opposed_to_include() {
  return diag(6635, DiagnosticCategory::Message,
              "Include_a_list_of_files_This_does_not_support_glob_patterns_as_"
              "opposed_to_include_6635",
              "Include a list of files. This does not support glob patterns, "
              "as opposed to `include`.");
};
static shared_ptr<DiagnosticMessage>
Build_all_projects_including_those_that_appear_to_be_up_to_date() {
  return diag(
      6636, DiagnosticCategory::Message,
      "Build_all_projects_including_those_that_appear_to_be_up_to_date_6636",
      "Build all projects, including those that appear to be up to date");
};
static shared_ptr<DiagnosticMessage>
Ensure_that_casing_is_correct_in_imports() {
  return diag(6637, DiagnosticCategory::Message,
              "Ensure_that_casing_is_correct_in_imports_6637",
              "Ensure that casing is correct in imports.");
};
static shared_ptr<DiagnosticMessage>
Emit_a_v8_CPU_profile_of_the_compiler_run_for_debugging() {
  return diag(6638, DiagnosticCategory::Message,
              "Emit_a_v8_CPU_profile_of_the_compiler_run_for_debugging_6638",
              "Emit a v8 CPU profile of the compiler run for debugging.");
};
static shared_ptr<DiagnosticMessage>
Allow_importing_helper_functions_from_tslib_once_per_project_instead_of_including_them_per_file() {
  return diag(6639, DiagnosticCategory::Message,
              "Allow_importing_helper_functions_from_tslib_once_per_project_"
              "instead_of_including_them_per_file_6639",
              "Allow importing helper functions from tslib once per project, "
              "instead of including them per-file.");
};
static shared_ptr<DiagnosticMessage>
Specify_a_list_of_glob_patterns_that_match_files_to_be_included_in_compilation() {
  return diag(6641, DiagnosticCategory::Message,
              "Specify_a_list_of_glob_patterns_that_match_files_to_be_included_"
              "in_compilation_6641",
              "Specify a list of glob patterns that match files to be included "
              "in compilation.");
};
static shared_ptr<DiagnosticMessage>
Save_tsbuildinfo_files_to_allow_for_incremental_compilation_of_projects() {
  return diag(6642, DiagnosticCategory::Message,
              "Save_tsbuildinfo_files_to_allow_for_incremental_compilation_of_"
              "projects_6642",
              "Save .tsbuildinfo files to allow for incremental compilation of "
              "projects.");
};
static shared_ptr<DiagnosticMessage>
Include_sourcemap_files_inside_the_emitted_JavaScript() {
  return diag(6643, DiagnosticCategory::Message,
              "Include_sourcemap_files_inside_the_emitted_JavaScript_6643",
              "Include sourcemap files inside the emitted JavaScript.");
};
static shared_ptr<DiagnosticMessage>
Include_source_code_in_the_sourcemaps_inside_the_emitted_JavaScript() {
  return diag(
      6644, DiagnosticCategory::Message,
      "Include_source_code_in_the_sourcemaps_inside_the_emitted_JavaScript_"
      "6644",
      "Include source code in the sourcemaps inside the emitted JavaScript.");
};
static shared_ptr<DiagnosticMessage>
Ensure_that_each_file_can_be_safely_transpiled_without_relying_on_other_imports() {
  return diag(6645, DiagnosticCategory::Message,
              "Ensure_that_each_file_can_be_safely_transpiled_without_relying_"
              "on_other_imports_6645",
              "Ensure that each file can be safely transpiled without relying "
              "on other imports.");
};
static shared_ptr<DiagnosticMessage> Specify_what_JSX_code_is_generated() {
  return diag(6646, DiagnosticCategory::Message,
              "Specify_what_JSX_code_is_generated_6646",
              "Specify what JSX code is generated.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_JSX_factory_function_used_when_targeting_React_JSX_emit_e_g_React_createElement_or_h() {
  return diag(6647, DiagnosticCategory::Message,
              "Specify_the_JSX_factory_function_used_when_targeting_React_JSX_"
              "emit_e_g_React_createElement_or_h_6647",
              "Specify the JSX factory function used when targeting React JSX "
              "emit, e.g. 'React.createElement' or 'h'");
};
static shared_ptr<DiagnosticMessage>
Specify_the_JSX_Fragment_reference_used_for_fragments_when_targeting_React_JSX_emit_e_g_React_Fragment_or_Fragment() {
  return diag(6648, DiagnosticCategory::Message,
              "Specify_the_JSX_Fragment_reference_used_for_fragments_when_"
              "targeting_React_JSX_emit_e_g_React_Fragme_6648",
              "Specify the JSX Fragment reference used for fragments when "
              "targeting React JSX emit e.g. 'React.Fragment' or 'Fragment'.");
};
static shared_ptr<DiagnosticMessage>
Specify_module_specifier_used_to_import_the_JSX_factory_functions_when_using_jsx_Colon_react_jsx_Asterisk() {
  return diag(6649, DiagnosticCategory::Message,
              "Specify_module_specifier_used_to_import_the_JSX_factory_"
              "functions_when_using_jsx_Colon_react_jsx_Ast_6649",
              "Specify module specifier used to import the JSX factory "
              "functions when using `jsx: react-jsx*`.`");
};
static shared_ptr<DiagnosticMessage>
Make_keyof_only_return_strings_instead_of_string_numbers_or_symbols_Legacy_option() {
  return diag(6650, DiagnosticCategory::Message,
              "Make_keyof_only_return_strings_instead_of_string_numbers_or_"
              "symbols_Legacy_option_6650",
              "Make keyof only return strings instead of string, numbers or "
              "symbols. Legacy option.");
};
static shared_ptr<DiagnosticMessage>
Specify_a_set_of_bundled_library_declaration_files_that_describe_the_target_runtime_environment() {
  return diag(6651, DiagnosticCategory::Message,
              "Specify_a_set_of_bundled_library_declaration_files_that_"
              "describe_the_target_runtime_environment_6651",
              "Specify a set of bundled library declaration files that "
              "describe the target runtime environment.");
};
static shared_ptr<DiagnosticMessage>
Print_the_names_of_emitted_files_after_a_compilation() {
  return diag(6652, DiagnosticCategory::Message,
              "Print_the_names_of_emitted_files_after_a_compilation_6652",
              "Print the names of emitted files after a compilation.");
};
static shared_ptr<DiagnosticMessage>
Print_all_of_the_files_read_during_the_compilation() {
  return diag(6653, DiagnosticCategory::Message,
              "Print_all_of_the_files_read_during_the_compilation_6653",
              "Print all of the files read during the compilation.");
};
static shared_ptr<DiagnosticMessage>
Set_the_language_of_the_messaging_from_TypeScript_This_does_not_affect_emit() {
  return diag(6654, DiagnosticCategory::Message,
              "Set_the_language_of_the_messaging_from_TypeScript_This_does_not_"
              "affect_emit_6654",
              "Set the language of the messaging from TypeScript. This does "
              "not affect emit.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_location_where_debugger_should_locate_map_files_instead_of_generated_locations() {
  return diag(6655, DiagnosticCategory::Message,
              "Specify_the_location_where_debugger_should_locate_map_files_"
              "instead_of_generated_locations_6655",
              "Specify the location where debugger should locate map files "
              "instead of generated locations.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_maximum_folder_depth_used_for_checking_JavaScript_files_from_node_modules_Only_applicable_with_allowJs() {
  return diag(6656, DiagnosticCategory::Message,
              "Specify_the_maximum_folder_depth_used_for_checking_JavaScript_"
              "files_from_node_modules_Only_applicabl_6656",
              "Specify the maximum folder depth used for checking JavaScript "
              "files from `node_modules`. Only applicable with `allowJs`.");
};
static shared_ptr<DiagnosticMessage> Specify_what_module_code_is_generated() {
  return diag(6657, DiagnosticCategory::Message,
              "Specify_what_module_code_is_generated_6657",
              "Specify what module code is generated.");
};
static shared_ptr<DiagnosticMessage>
Specify_how_TypeScript_looks_up_a_file_from_a_given_module_specifier() {
  return diag(
      6658, DiagnosticCategory::Message,
      "Specify_how_TypeScript_looks_up_a_file_from_a_given_module_specifier_"
      "6658",
      "Specify how TypeScript looks up a file from a given module specifier.");
};
static shared_ptr<DiagnosticMessage>
Set_the_newline_character_for_emitting_files() {
  return diag(6659, DiagnosticCategory::Message,
              "Set_the_newline_character_for_emitting_files_6659",
              "Set the newline character for emitting files.");
};
static shared_ptr<DiagnosticMessage>
Disable_emitting_files_from_a_compilation() {
  return diag(6660, DiagnosticCategory::Message,
              "Disable_emitting_files_from_a_compilation_6660",
              "Disable emitting files from a compilation.");
};
static shared_ptr<DiagnosticMessage>
Disable_generating_custom_helper_functions_like_extends_in_compiled_output() {
  return diag(6661, DiagnosticCategory::Message,
              "Disable_generating_custom_helper_functions_like_extends_in_"
              "compiled_output_6661",
              "Disable generating custom helper functions like `__extends` in "
              "compiled output.");
};
static shared_ptr<DiagnosticMessage>
Disable_emitting_files_if_any_type_checking_errors_are_reported() {
  return diag(
      6662, DiagnosticCategory::Message,
      "Disable_emitting_files_if_any_type_checking_errors_are_reported_6662",
      "Disable emitting files if any type checking errors are reported.");
};
static shared_ptr<DiagnosticMessage>
Disable_truncating_types_in_error_messages() {
  return diag(6663, DiagnosticCategory::Message,
              "Disable_truncating_types_in_error_messages_6663",
              "Disable truncating types in error messages.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_for_fallthrough_cases_in_switch_statements() {
  return diag(
      6664, DiagnosticCategory::Message,
      "Enable_error_reporting_for_fallthrough_cases_in_switch_statements_6664",
      "Enable error reporting for fallthrough cases in switch statements.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_for_expressions_and_declarations_with_an_implied_any_type() {
  return diag(6665, DiagnosticCategory::Message,
              "Enable_error_reporting_for_expressions_and_declarations_with_an_"
              "implied_any_type_6665",
              "Enable error reporting for expressions and declarations with an "
              "implied `any` type..");
};
static shared_ptr<DiagnosticMessage>
Ensure_overriding_members_in_derived_classes_are_marked_with_an_override_modifier() {
  return diag(6666, DiagnosticCategory::Message,
              "Ensure_overriding_members_in_derived_classes_are_marked_with_an_"
              "override_modifier_6666",
              "Ensure overriding members in derived classes are marked with an "
              "override modifier.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_for_codepaths_that_do_not_explicitly_return_in_a_function() {
  return diag(6667, DiagnosticCategory::Message,
              "Enable_error_reporting_for_codepaths_that_do_not_explicitly_"
              "return_in_a_function_6667",
              "Enable error reporting for codepaths that do not explicitly "
              "return in a function.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_when_this_is_given_the_type_any() {
  return diag(6668, DiagnosticCategory::Message,
              "Enable_error_reporting_when_this_is_given_the_type_any_6668",
              "Enable error reporting when `this` is given the type `any`.");
};
static shared_ptr<DiagnosticMessage>
Disable_adding_use_strict_directives_in_emitted_JavaScript_files() {
  return diag(
      6669, DiagnosticCategory::Message,
      "Disable_adding_use_strict_directives_in_emitted_JavaScript_files_6669",
      "Disable adding 'use strict' directives in emitted JavaScript files.");
};
static shared_ptr<DiagnosticMessage>
Disable_including_any_library_files_including_the_default_lib_d_ts() {
  return diag(
      6670, DiagnosticCategory::Message,
      "Disable_including_any_library_files_including_the_default_lib_d_ts_6670",
      "Disable including any library files, including the default lib.d.ts.");
};
static shared_ptr<DiagnosticMessage>
Enforces_using_indexed_accessors_for_keys_declared_using_an_indexed_type() {
  return diag(6671, DiagnosticCategory::Message,
              "Enforces_using_indexed_accessors_for_keys_declared_using_an_"
              "indexed_type_6671",
              "Enforces using indexed accessors for keys declared using an "
              "indexed type");
};
static shared_ptr<DiagnosticMessage>
Disallow_import_s_require_s_or_reference_s_from_expanding_the_number_of_files_TypeScript_should_add_to_a_project() {
  return diag(6672, DiagnosticCategory::Message,
              "Disallow_import_s_require_s_or_reference_s_from_expanding_the_"
              "number_of_files_TypeScript_should_add__6672",
              "Disallow `import`s, `require`s or `<reference>`s from expanding "
              "the number of files TypeScript should add to a project.");
};
static shared_ptr<DiagnosticMessage>
Disable_strict_checking_of_generic_signatures_in_function_types() {
  return diag(
      6673, DiagnosticCategory::Message,
      "Disable_strict_checking_of_generic_signatures_in_function_types_6673",
      "Disable strict checking of generic signatures in function types.");
};
static shared_ptr<DiagnosticMessage>
Add_undefined_to_a_type_when_accessed_using_an_index() {
  return diag(6674, DiagnosticCategory::Message,
              "Add_undefined_to_a_type_when_accessed_using_an_index_6674",
              "Add `undefined` to a type when accessed using an index.");
};
static shared_ptr<DiagnosticMessage>
Enable_error_reporting_when_a_local_variables_aren_t_read() {
  return diag(6675, DiagnosticCategory::Message,
              "Enable_error_reporting_when_a_local_variables_aren_t_read_6675",
              "Enable error reporting when a local variables aren't read.");
};
static shared_ptr<DiagnosticMessage>
Raise_an_error_when_a_function_parameter_isn_t_read() {
  return diag(6676, DiagnosticCategory::Message,
              "Raise_an_error_when_a_function_parameter_isn_t_read_6676",
              "Raise an error when a function parameter isn't read");
};
static shared_ptr<DiagnosticMessage> Deprecated_setting_Use_outFile_instead() {
  return diag(6677, DiagnosticCategory::Message,
              "Deprecated_setting_Use_outFile_instead_6677",
              "Deprecated setting. Use `outFile` instead.");
};
static shared_ptr<DiagnosticMessage>
Specify_an_output_folder_for_all_emitted_files() {
  return diag(6678, DiagnosticCategory::Message,
              "Specify_an_output_folder_for_all_emitted_files_6678",
              "Specify an output folder for all emitted files.");
};
static shared_ptr<DiagnosticMessage>
Specify_a_file_that_bundles_all_outputs_into_one_JavaScript_file_If_declaration_is_true_also_designates_a_file_that_bundles_all_d_ts_output() {
  return diag(6679, DiagnosticCategory::Message,
              "Specify_a_file_that_bundles_all_outputs_into_one_JavaScript_"
              "file_If_declaration_is_true_also_designa_6679",
              "Specify a file that bundles all outputs into one JavaScript "
              "file. If `declaration` is true, also designates a file that "
              "bundles all .d.ts output.");
};
static shared_ptr<DiagnosticMessage>
Specify_a_set_of_entries_that_re_map_imports_to_additional_lookup_locations() {
  return diag(6680, DiagnosticCategory::Message,
              "Specify_a_set_of_entries_that_re_map_imports_to_additional_"
              "lookup_locations_6680",
              "Specify a set of entries that re-map imports to additional "
              "lookup locations.");
};
static shared_ptr<DiagnosticMessage>
Specify_a_list_of_language_service_plugins_to_include() {
  return diag(6681, DiagnosticCategory::Message,
              "Specify_a_list_of_language_service_plugins_to_include_6681",
              "Specify a list of language service plugins to include.");
};
static shared_ptr<DiagnosticMessage>
Disable_erasing_const_enum_declarations_in_generated_code() {
  return diag(6682, DiagnosticCategory::Message,
              "Disable_erasing_const_enum_declarations_in_generated_code_6682",
              "Disable erasing `const enum` declarations in generated code.");
};
static shared_ptr<DiagnosticMessage>
Disable_resolving_symlinks_to_their_realpath_This_correlates_to_the_same_flag_in_node() {
  return diag(6683, DiagnosticCategory::Message,
              "Disable_resolving_symlinks_to_their_realpath_This_correlates_to_"
              "the_same_flag_in_node_6683",
              "Disable resolving symlinks to their realpath. This correlates "
              "to the same flag in node.");
};
static shared_ptr<DiagnosticMessage>
Disable_wiping_the_console_in_watch_mode() {
  return diag(6684, DiagnosticCategory::Message,
              "Disable_wiping_the_console_in_watch_mode_6684",
              "Disable wiping the console in watch mode");
};
static shared_ptr<DiagnosticMessage>
Enable_color_and_formatting_in_TypeScript_s_output_to_make_compiler_errors_easier_to_read() {
  return diag(6685, DiagnosticCategory::Message,
              "Enable_color_and_formatting_in_TypeScript_s_output_to_make_"
              "compiler_errors_easier_to_read_6685",
              "Enable color and formatting in TypeScript's output to make "
              "compiler errors easier to read");
};
static shared_ptr<DiagnosticMessage>
Specify_the_object_invoked_for_createElement_This_only_applies_when_targeting_react_JSX_emit() {
  return diag(6686, DiagnosticCategory::Message,
              "Specify_the_object_invoked_for_createElement_This_only_applies_"
              "when_targeting_react_JSX_emit_6686",
              "Specify the object invoked for `createElement`. This only "
              "applies when targeting `react` JSX emit.");
};
static shared_ptr<DiagnosticMessage>
Specify_an_array_of_objects_that_specify_paths_for_projects_Used_in_project_references() {
  return diag(6687, DiagnosticCategory::Message,
              "Specify_an_array_of_objects_that_specify_paths_for_projects_"
              "Used_in_project_references_6687",
              "Specify an array of objects that specify paths for projects. "
              "Used in project references.");
};
static shared_ptr<DiagnosticMessage> Disable_emitting_comments() {
  return diag(6688, DiagnosticCategory::Message,
              "Disable_emitting_comments_6688", "Disable emitting comments.");
};
static shared_ptr<DiagnosticMessage> Enable_importing_json_files() {
  return diag(6689, DiagnosticCategory::Message,
              "Enable_importing_json_files_6689",
              "Enable importing .json files");
};
static shared_ptr<DiagnosticMessage>
Specify_the_root_folder_within_your_source_files() {
  return diag(6690, DiagnosticCategory::Message,
              "Specify_the_root_folder_within_your_source_files_6690",
              "Specify the root folder within your source files.");
};
static shared_ptr<DiagnosticMessage>
Allow_multiple_folders_to_be_treated_as_one_when_resolving_modules() {
  return diag(
      6691, DiagnosticCategory::Message,
      "Allow_multiple_folders_to_be_treated_as_one_when_resolving_modules_6691",
      "Allow multiple folders to be treated as one when resolving modules.");
};
static shared_ptr<DiagnosticMessage>
Skip_type_checking_d_ts_files_that_are_included_with_TypeScript() {
  return diag(
      6692, DiagnosticCategory::Message,
      "Skip_type_checking_d_ts_files_that_are_included_with_TypeScript_6692",
      "Skip type checking .d.ts files that are included with TypeScript.");
};
static shared_ptr<DiagnosticMessage> Skip_type_checking_all_d_ts_files() {
  return diag(6693, DiagnosticCategory::Message,
              "Skip_type_checking_all_d_ts_files_6693",
              "Skip type checking all .d.ts files.");
};
static shared_ptr<DiagnosticMessage>
Create_source_map_files_for_emitted_JavaScript_files() {
  return diag(6694, DiagnosticCategory::Message,
              "Create_source_map_files_for_emitted_JavaScript_files_6694",
              "Create source map files for emitted JavaScript files.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_root_path_for_debuggers_to_find_the_reference_source_code() {
  return diag(
      6695, DiagnosticCategory::Message,
      "Specify_the_root_path_for_debuggers_to_find_the_reference_source_code_"
      "6695",
      "Specify the root path for debuggers to find the reference source code.");
};
static shared_ptr<DiagnosticMessage>
Check_that_the_arguments_for_bind_call_and_apply_methods_match_the_original_function() {
  return diag(6697, DiagnosticCategory::Message,
              "Check_that_the_arguments_for_bind_call_and_apply_methods_match_"
              "the_original_function_6697",
              "Check that the arguments for `bind`, `call`, and `apply` "
              "methods match the original function.");
};
static shared_ptr<DiagnosticMessage>
When_assigning_functions_check_to_ensure_parameters_and_the_return_values_are_subtype_compatible() {
  return diag(6698, DiagnosticCategory::Message,
              "When_assigning_functions_check_to_ensure_parameters_and_the_"
              "return_values_are_subtype_compatible_6698",
              "When assigning functions, check to ensure parameters and the "
              "return values are subtype-compatible.");
};
static shared_ptr<DiagnosticMessage>
When_type_checking_take_into_account_null_and_undefined() {
  return diag(6699, DiagnosticCategory::Message,
              "When_type_checking_take_into_account_null_and_undefined_6699",
              "When type checking, take into account `null` and `undefined`.");
};
static shared_ptr<DiagnosticMessage>
Check_for_class_properties_that_are_declared_but_not_set_in_the_constructor() {
  return diag(6700, DiagnosticCategory::Message,
              "Check_for_class_properties_that_are_declared_but_not_set_in_the_"
              "constructor_6700",
              "Check for class properties that are declared but not set in the "
              "constructor.");
};
static shared_ptr<DiagnosticMessage>
Disable_emitting_declarations_that_have_internal_in_their_JSDoc_comments() {
  return diag(6701, DiagnosticCategory::Message,
              "Disable_emitting_declarations_that_have_internal_in_their_JSDoc_"
              "comments_6701",
              "Disable emitting declarations that have `@internal` in their "
              "JSDoc comments.");
};
static shared_ptr<DiagnosticMessage>
Disable_reporting_of_excess_property_errors_during_the_creation_of_object_literals() {
  return diag(6702, DiagnosticCategory::Message,
              "Disable_reporting_of_excess_property_errors_during_the_creation_"
              "of_object_literals_6702",
              "Disable reporting of excess property errors during the creation "
              "of object literals.");
};
static shared_ptr<DiagnosticMessage>
Suppress_noImplicitAny_errors_when_indexing_objects_that_lack_index_signatures() {
  return diag(6703, DiagnosticCategory::Message,
              "Suppress_noImplicitAny_errors_when_indexing_objects_that_lack_"
              "index_signatures_6703",
              "Suppress `noImplicitAny` errors when indexing objects that lack "
              "index signatures.");
};
static shared_ptr<DiagnosticMessage>
Synchronously_call_callbacks_and_update_the_state_of_directory_watchers_on_platforms_that_don_t_support_recursive_watching_natively() {
  return diag(
      6704, DiagnosticCategory::Message,
      "Synchronously_call_callbacks_and_update_the_state_of_directory_watchers_"
      "on_platforms_that_don_t_supp_6704",
      "Synchronously call callbacks and update the state of directory watchers "
      "on platforms that don`t support recursive watching natively.");
};
static shared_ptr<DiagnosticMessage>
Set_the_JavaScript_language_version_for_emitted_JavaScript_and_include_compatible_library_declarations() {
  return diag(6705, DiagnosticCategory::Message,
              "Set_the_JavaScript_language_version_for_emitted_JavaScript_and_"
              "include_compatible_library_declaratio_6705",
              "Set the JavaScript language version for emitted JavaScript and "
              "include compatible library declarations.");
};
static shared_ptr<DiagnosticMessage>
Log_paths_used_during_the_moduleResolution_process() {
  return diag(6706, DiagnosticCategory::Message,
              "Log_paths_used_during_the_moduleResolution_process_6706",
              "Log paths used during the `moduleResolution` process.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_folder_for_tsbuildinfo_incremental_compilation_files() {
  return diag(
      6707, DiagnosticCategory::Message,
      "Specify_the_folder_for_tsbuildinfo_incremental_compilation_files_6707",
      "Specify the folder for .tsbuildinfo incremental compilation files.");
};
static shared_ptr<DiagnosticMessage>
Specify_options_for_automatic_acquisition_of_declaration_files() {
  return diag(
      6709, DiagnosticCategory::Message,
      "Specify_options_for_automatic_acquisition_of_declaration_files_6709",
      "Specify options for automatic acquisition of declaration files.");
};
static shared_ptr<DiagnosticMessage>
Specify_multiple_folders_that_act_like_Slashnode_modules_Slash_types() {
  return diag(
      6710, DiagnosticCategory::Message,
      "Specify_multiple_folders_that_act_like_Slashnode_modules_Slash_types_"
      "6710",
      "Specify multiple folders that act like `./node_modules/@types`.");
};
static shared_ptr<DiagnosticMessage>
Specify_type_package_names_to_be_included_without_being_referenced_in_a_source_file() {
  return diag(6711, DiagnosticCategory::Message,
              "Specify_type_package_names_to_be_included_without_being_"
              "referenced_in_a_source_file_6711",
              "Specify type package names to be included without being "
              "referenced in a source file.");
};
static shared_ptr<DiagnosticMessage>
Emit_ECMAScript_standard_compliant_class_fields() {
  return diag(6712, DiagnosticCategory::Message,
              "Emit_ECMAScript_standard_compliant_class_fields_6712",
              "Emit ECMAScript-standard-compliant class fields.");
};
static shared_ptr<DiagnosticMessage> Enable_verbose_logging() {
  return diag(6713, DiagnosticCategory::Message, "Enable_verbose_logging_6713",
              "Enable verbose logging");
};
static shared_ptr<DiagnosticMessage>
Specify_how_directories_are_watched_on_systems_that_lack_recursive_file_watching_functionality() {
  return diag(6714, DiagnosticCategory::Message,
              "Specify_how_directories_are_watched_on_systems_that_lack_"
              "recursive_file_watching_functionality_6714",
              "Specify how directories are watched on systems that lack "
              "recursive file-watching functionality.");
};
static shared_ptr<DiagnosticMessage>
Specify_how_the_TypeScript_watch_mode_works() {
  return diag(6715, DiagnosticCategory::Message,
              "Specify_how_the_TypeScript_watch_mode_works_6715",
              "Specify how the TypeScript watch mode works.");
};
static shared_ptr<DiagnosticMessage>
Include_undefined_in_index_signature_results() {
  return diag(6716, DiagnosticCategory::Message,
              "Include_undefined_in_index_signature_results_6716",
              "Include 'undefined' in index signature results");
};
static shared_ptr<DiagnosticMessage>
Require_undeclared_properties_from_index_signatures_to_use_element_accesses() {
  return diag(6717, DiagnosticCategory::Message,
              "Require_undeclared_properties_from_index_signatures_to_use_"
              "element_accesses_6717",
              "Require undeclared properties from index signatures to use "
              "element accesses.");
};
static shared_ptr<DiagnosticMessage>
Specify_emit_Slashchecking_behavior_for_imports_that_are_only_used_for_types() {
  return diag(6718, DiagnosticCategory::Message,
              "Specify_emit_Slashchecking_behavior_for_imports_that_are_only_"
              "used_for_types_6718",
              "Specify emit/checking behavior for imports that are only used "
              "for types");
};
static shared_ptr<DiagnosticMessage>
Type_catch_clause_variables_as_unknown_instead_of_any() {
  return diag(6803, DiagnosticCategory::Message,
              "Type_catch_clause_variables_as_unknown_instead_of_any_6803",
              "Type catch clause variables as 'unknown' instead of 'any'.");
};
static shared_ptr<DiagnosticMessage> one_of_Colon() {
  return diag(6900, DiagnosticCategory::Message, "one_of_Colon_6900",
              "one of:");
};
static shared_ptr<DiagnosticMessage> one_or_more_Colon() {
  return diag(6901, DiagnosticCategory::Message, "one_or_more_Colon_6901",
              "one or more:");
};
static shared_ptr<DiagnosticMessage> type_Colon() {
  return diag(6902, DiagnosticCategory::Message, "type_Colon_6902", "type:");
};
static shared_ptr<DiagnosticMessage> default_Colon() {
  return diag(6903, DiagnosticCategory::Message, "default_Colon_6903",
              "default:");
};
static shared_ptr<DiagnosticMessage> module_system_or_esModuleInterop() {
  return diag(6904, DiagnosticCategory::Message,
              "module_system_or_esModuleInterop_6904",
              "module === \"system\" or esModuleInterop");
};
static shared_ptr<DiagnosticMessage> false_unless_strict_is_set() {
  return diag(6905, DiagnosticCategory::Message,
              "false_unless_strict_is_set_6905",
              "`false`, unless `strict` is set");
};
static shared_ptr<DiagnosticMessage> false_unless_composite_is_set() {
  return diag(6906, DiagnosticCategory::Message,
              "false_unless_composite_is_set_6906",
              "`false`, unless `composite` is set");
};
static shared_ptr<DiagnosticMessage>
node_modules_bower_components_jspm_packages_plus_the_value_of_outDir_if_one_is_specified() {
  return diag(6907, DiagnosticCategory::Message,
              "node_modules_bower_components_jspm_packages_plus_the_value_of_"
              "outDir_if_one_is_specified_6907",
              "`[\"node_modules\", \"bower_components\", \"jspm_packages\"]`, "
              "plus the value of `outDir` if one is specified.");
};
static shared_ptr<DiagnosticMessage>
if_files_is_specified_otherwise_Asterisk_Asterisk_Slash_Asterisk() {
  return diag(
      6908, DiagnosticCategory::Message,
      "if_files_is_specified_otherwise_Asterisk_Asterisk_Slash_Asterisk_6908",
      "`[]` if `files` is specified, otherwise `[\"**/*\"]`");
};
static shared_ptr<DiagnosticMessage> true_if_composite_false_otherwise() {
  return diag(6909, DiagnosticCategory::Message,
              "true_if_composite_false_otherwise_6909",
              "`true` if `composite`, `false` otherwise");
};
static shared_ptr<DiagnosticMessage>
module_AMD_or_UMD_or_System_or_ES6_then_Classic_Otherwise_Node() {
  return diag(
      69010, DiagnosticCategory::Message,
      "module_AMD_or_UMD_or_System_or_ES6_then_Classic_Otherwise_Node_69010",
      "module === `AMD` or `UMD` or `System` or `ES6`, then `Classic`, "
      "Otherwise `Node`");
};
static shared_ptr<DiagnosticMessage> Computed_from_the_list_of_input_files() {
  return diag(6911, DiagnosticCategory::Message,
              "Computed_from_the_list_of_input_files_6911",
              "Computed from the list of input files");
};
static shared_ptr<DiagnosticMessage> Platform_specific() {
  return diag(6912, DiagnosticCategory::Message, "Platform_specific_6912",
              "Platform specific");
};
static shared_ptr<DiagnosticMessage>
You_can_learn_about_all_of_the_compiler_options_at_0() {
  return diag(6913, DiagnosticCategory::Message,
              "You_can_learn_about_all_of_the_compiler_options_at_0_6913",
              "You can learn about all of the compiler options at {0}");
};
static shared_ptr<DiagnosticMessage>
Including_watch_w_will_start_watching_the_current_project_for_the_file_changes_Once_set_you_can_config_watch_mode_with_Colon() {
  return diag(
      6914, DiagnosticCategory::Message,
      "Including_watch_w_will_start_watching_the_current_project_for_the_file_"
      "changes_Once_set_you_can_conf_6914",
      "Including --watch, -w will start watching the current project for the "
      "file changes. Once set, you can config watch mode with:");
};
static shared_ptr<DiagnosticMessage>
Using_build_b_will_make_tsc_behave_more_like_a_build_orchestrator_than_a_compiler_This_is_used_to_trigger_building_composite_projects_which_you_can_learn_more_about_at_0() {
  return diag(6915, DiagnosticCategory::Message,
              "Using_build_b_will_make_tsc_behave_more_like_a_build_"
              "orchestrator_than_a_compiler_This_is_used_to_tr_6915",
              "Using --build, -b will make tsc behave more like a build "
              "orchestrator than a compiler. This is used to trigger building "
              "composite projects which you can learn more about at {0}");
};
static shared_ptr<DiagnosticMessage> COMMON_COMMANDS() {
  return diag(6916, DiagnosticCategory::Message, "COMMON_COMMANDS_6916",
              "COMMON COMMANDS");
};
static shared_ptr<DiagnosticMessage> ALL_COMPILER_OPTIONS() {
  return diag(6917, DiagnosticCategory::Message, "ALL_COMPILER_OPTIONS_6917",
              "ALL COMPILER OPTIONS");
};
static shared_ptr<DiagnosticMessage> WATCH_OPTIONS() {
  return diag(6918, DiagnosticCategory::Message, "WATCH_OPTIONS_6918",
              "WATCH OPTIONS");
};
static shared_ptr<DiagnosticMessage> BUILD_OPTIONS() {
  return diag(6919, DiagnosticCategory::Message, "BUILD_OPTIONS_6919",
              "BUILD OPTIONS");
};
static shared_ptr<DiagnosticMessage> COMMON_COMPILER_OPTIONS() {
  return diag(6920, DiagnosticCategory::Message, "COMMON_COMPILER_OPTIONS_6920",
              "COMMON COMPILER OPTIONS");
};
static shared_ptr<DiagnosticMessage> COMMAND_LINE_FLAGS() {
  return diag(6921, DiagnosticCategory::Message, "COMMAND_LINE_FLAGS_6921",
              "COMMAND LINE FLAGS");
};
static shared_ptr<DiagnosticMessage> tsc_Colon_The_TypeScript_Compiler() {
  return diag(6922, DiagnosticCategory::Message,
              "tsc_Colon_The_TypeScript_Compiler_6922",
              "tsc: The TypeScript Compiler");
};
static shared_ptr<DiagnosticMessage>
Compiles_the_current_project_tsconfig_json_in_the_working_directory() {
  return diag(
      6923, DiagnosticCategory::Message,
      "Compiles_the_current_project_tsconfig_json_in_the_working_directory_"
      "6923",
      "Compiles the current project (tsconfig.json in the working directory.)");
};
static shared_ptr<DiagnosticMessage>
Ignoring_tsconfig_json_compiles_the_specified_files_with_default_compiler_options() {
  return diag(6924, DiagnosticCategory::Message,
              "Ignoring_tsconfig_json_compiles_the_specified_files_with_"
              "default_compiler_options_6924",
              "Ignoring tsconfig.json, compiles the specified files with "
              "default compiler options.");
};
static shared_ptr<DiagnosticMessage>
Build_a_composite_project_in_the_working_directory() {
  return diag(6925, DiagnosticCategory::Message,
              "Build_a_composite_project_in_the_working_directory_6925",
              "Build a composite project in the working directory.");
};
static shared_ptr<DiagnosticMessage>
Creates_a_tsconfig_json_with_the_recommended_settings_in_the_working_directory() {
  return diag(6926, DiagnosticCategory::Message,
              "Creates_a_tsconfig_json_with_the_recommended_settings_in_the_"
              "working_directory_6926",
              "Creates a tsconfig.json with the recommended settings in the "
              "working directory.");
};
static shared_ptr<DiagnosticMessage>
Compiles_the_TypeScript_project_located_at_the_specified_path() {
  return diag(
      6927, DiagnosticCategory::Message,
      "Compiles_the_TypeScript_project_located_at_the_specified_path_6927",
      "Compiles the TypeScript project located at the specified path.");
};
static shared_ptr<DiagnosticMessage>
An_expanded_version_of_this_information_showing_all_possible_compiler_options() {
  return diag(6928, DiagnosticCategory::Message,
              "An_expanded_version_of_this_information_showing_all_possible_"
              "compiler_options_6928",
              "An expanded version of this information, showing all possible "
              "compiler options");
};
static shared_ptr<DiagnosticMessage>
Compiles_the_current_project_with_additional_settings() {
  return diag(6929, DiagnosticCategory::Message,
              "Compiles_the_current_project_with_additional_settings_6929",
              "Compiles the current project, with additional settings.");
};
static shared_ptr<DiagnosticMessage>
true_for_ES2022_and_above_including_ESNext() {
  return diag(6930, DiagnosticCategory::Message,
              "true_for_ES2022_and_above_including_ESNext_6930",
              "`true` for ES2022 and above, including ESNext.");
};
static shared_ptr<DiagnosticMessage> Variable_0_implicitly_has_an_1_type() {
  return diag(7005, DiagnosticCategory::Error,
              "Variable_0_implicitly_has_an_1_type_7005",
              "Variable '{0}' implicitly has an '{1}' type.");
};
static shared_ptr<DiagnosticMessage> Parameter_0_implicitly_has_an_1_type() {
  return diag(7006, DiagnosticCategory::Error,
              "Parameter_0_implicitly_has_an_1_type_7006",
              "Parameter '{0}' implicitly has an '{1}' type.");
};
static shared_ptr<DiagnosticMessage> Member_0_implicitly_has_an_1_type() {
  return diag(7008, DiagnosticCategory::Error,
              "Member_0_implicitly_has_an_1_type_7008",
              "Member '{0}' implicitly has an '{1}' type.");
};
static shared_ptr<DiagnosticMessage>
new_expression_whose_target_lacks_a_construct_signature_implicitly_has_an_any_type() {
  return diag(7009, DiagnosticCategory::Error,
              "new_expression_whose_target_lacks_a_construct_signature_"
              "implicitly_has_an_any_type_7009",
              "'new' expression, whose target lacks a construct signature, "
              "implicitly has an 'any' type.");
};
static shared_ptr<DiagnosticMessage>
_0_which_lacks_return_type_annotation_implicitly_has_an_1_return_type() {
  return diag(7010, DiagnosticCategory::Error,
              "_0_which_lacks_return_type_annotation_implicitly_has_an_1_"
              "return_type_7010",
              "'{0}', which lacks return-type annotation, implicitly has an "
              "'{1}' return type.");
};
static shared_ptr<DiagnosticMessage>
Function_expression_which_lacks_return_type_annotation_implicitly_has_an_0_return_type() {
  return diag(7011, DiagnosticCategory::Error,
              "Function_expression_which_lacks_return_type_annotation_"
              "implicitly_has_an_0_return_type_7011",
              "Function expression, which lacks return-type annotation, "
              "implicitly has an '{0}' return type.");
};
static shared_ptr<DiagnosticMessage>
Construct_signature_which_lacks_return_type_annotation_implicitly_has_an_any_return_type() {
  return diag(7013, DiagnosticCategory::Error,
              "Construct_signature_which_lacks_return_type_annotation_"
              "implicitly_has_an_any_return_type_7013",
              "Construct signature, which lacks return-type annotation, "
              "implicitly has an 'any' return type.");
};
static shared_ptr<DiagnosticMessage>
Function_type_which_lacks_return_type_annotation_implicitly_has_an_0_return_type() {
  return diag(7014, DiagnosticCategory::Error,
              "Function_type_which_lacks_return_type_annotation_implicitly_has_"
              "an_0_return_type_7014",
              "Function type, which lacks return-type annotation, implicitly "
              "has an '{0}' return type.");
};
static shared_ptr<DiagnosticMessage>
Element_implicitly_has_an_any_type_because_index_expression_is_not_of_type_number() {
  return diag(7015, DiagnosticCategory::Error,
              "Element_implicitly_has_an_any_type_because_index_expression_is_"
              "not_of_type_number_7015",
              "Element implicitly has an 'any' type because index expression "
              "is not of type 'number'.");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_a_declaration_file_for_module_0_1_implicitly_has_an_any_type() {
  return diag(7016, DiagnosticCategory::Error,
              "Could_not_find_a_declaration_file_for_module_0_1_implicitly_has_"
              "an_any_type_7016",
              "Could not find a declaration file for module '{0}'. '{1}' "
              "implicitly has an 'any' type.");
};
static shared_ptr<DiagnosticMessage>
Element_implicitly_has_an_any_type_because_type_0_has_no_index_signature() {
  return diag(7017, DiagnosticCategory::Error,
              "Element_implicitly_has_an_any_type_because_type_0_has_no_index_"
              "signature_7017",
              "Element implicitly has an 'any' type because type '{0}' has no "
              "index signature.");
};
static shared_ptr<DiagnosticMessage>
Object_literal_s_property_0_implicitly_has_an_1_type() {
  return diag(7018, DiagnosticCategory::Error,
              "Object_literal_s_property_0_implicitly_has_an_1_type_7018",
              "Object literal's property '{0}' implicitly has an '{1}' type.");
};
static shared_ptr<DiagnosticMessage>
Rest_parameter_0_implicitly_has_an_any_type() {
  return diag(7019, DiagnosticCategory::Error,
              "Rest_parameter_0_implicitly_has_an_any_type_7019",
              "Rest parameter '{0}' implicitly has an 'any[]' type.");
};
static shared_ptr<DiagnosticMessage>
Call_signature_which_lacks_return_type_annotation_implicitly_has_an_any_return_type() {
  return diag(7020, DiagnosticCategory::Error,
              "Call_signature_which_lacks_return_type_annotation_implicitly_"
              "has_an_any_return_type_7020",
              "Call signature, which lacks return-type annotation, implicitly "
              "has an 'any' return type.");
};
static shared_ptr<DiagnosticMessage>
_0_implicitly_has_type_any_because_it_does_not_have_a_type_annotation_and_is_referenced_directly_or_indirectly_in_its_own_initializer() {
  return diag(7022, DiagnosticCategory::Error,
              "_0_implicitly_has_type_any_because_it_does_not_have_a_type_"
              "annotation_and_is_referenced_directly_or__7022",
              "'{0}' implicitly has type 'any' because it does not have a type "
              "annotation and is referenced directly or indirectly in its own "
              "initializer.");
};
static shared_ptr<DiagnosticMessage>
_0_implicitly_has_return_type_any_because_it_does_not_have_a_return_type_annotation_and_is_referenced_directly_or_indirectly_in_one_of_its_return_expressions() {
  return diag(7023, DiagnosticCategory::Error,
              "_0_implicitly_has_return_type_any_because_it_does_not_have_a_"
              "return_type_annotation_and_is_reference_7023",
              "'{0}' implicitly has return type 'any' because it does not have "
              "a return type annotation and is referenced directly or "
              "indirectly in one of its return expressions.");
};
static shared_ptr<DiagnosticMessage>
Function_implicitly_has_return_type_any_because_it_does_not_have_a_return_type_annotation_and_is_referenced_directly_or_indirectly_in_one_of_its_return_expressions() {
  return diag(7024, DiagnosticCategory::Error,
              "Function_implicitly_has_return_type_any_because_it_does_not_"
              "have_a_return_type_annotation_and_is_ref_7024",
              "Function implicitly has return type 'any' because it does not "
              "have a return type annotation and is referenced directly or "
              "indirectly in one of its return expressions.");
};
static shared_ptr<DiagnosticMessage>
Generator_implicitly_has_yield_type_0_because_it_does_not_yield_any_values_Consider_supplying_a_return_type_annotation() {
  return diag(7025, DiagnosticCategory::Error,
              "Generator_implicitly_has_yield_type_0_because_it_does_not_yield_"
              "any_values_Consider_supplying_a_retu_7025",
              "Generator implicitly has yield type '{0}' because it does not "
              "yield any values. Consider supplying a return type annotation.");
};
static shared_ptr<DiagnosticMessage>
JSX_element_implicitly_has_type_any_because_no_interface_JSX_0_exists() {
  return diag(7026, DiagnosticCategory::Error,
              "JSX_element_implicitly_has_type_any_because_no_interface_JSX_0_"
              "exists_7026",
              "JSX element implicitly has type 'any' because no interface "
              "'JSX.{0}' exists.");
};
static shared_ptr<DiagnosticMessage> Unreachable_code_detected() {
  return diag(7027, DiagnosticCategory::Error, "Unreachable_code_detected_7027",
              "Unreachable code detected.", /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> Unused_label() {
  return diag(7028, DiagnosticCategory::Error, "Unused_label_7028",
              "Unused label.", /*reportsUnnecessary*/ true);
};
static shared_ptr<DiagnosticMessage> Fallthrough_case_in_switch() {
  return diag(7029, DiagnosticCategory::Error,
              "Fallthrough_case_in_switch_7029", "Fallthrough case in switch.");
};
static shared_ptr<DiagnosticMessage> Not_all_code_paths_return_a_value() {
  return diag(7030, DiagnosticCategory::Error,
              "Not_all_code_paths_return_a_value_7030",
              "Not all code paths return a value.");
};
static shared_ptr<DiagnosticMessage>
Binding_element_0_implicitly_has_an_1_type() {
  return diag(7031, DiagnosticCategory::Error,
              "Binding_element_0_implicitly_has_an_1_type_7031",
              "Binding element '{0}' implicitly has an '{1}' type.");
};
static shared_ptr<DiagnosticMessage>
Property_0_implicitly_has_type_any_because_its_set_accessor_lacks_a_parameter_type_annotation() {
  return diag(7032, DiagnosticCategory::Error,
              "Property_0_implicitly_has_type_any_because_its_set_accessor_"
              "lacks_a_parameter_type_annotation_7032",
              "Property '{0}' implicitly has type 'any', because its set "
              "accessor lacks a parameter type annotation.");
};
static shared_ptr<DiagnosticMessage>
Property_0_implicitly_has_type_any_because_its_get_accessor_lacks_a_return_type_annotation() {
  return diag(7033, DiagnosticCategory::Error,
              "Property_0_implicitly_has_type_any_because_its_get_accessor_"
              "lacks_a_return_type_annotation_7033",
              "Property '{0}' implicitly has type 'any', because its get "
              "accessor lacks a return type annotation.");
};
static shared_ptr<DiagnosticMessage>
Variable_0_implicitly_has_type_1_in_some_locations_where_its_type_cannot_be_determined() {
  return diag(7034, DiagnosticCategory::Error,
              "Variable_0_implicitly_has_type_1_in_some_locations_where_its_"
              "type_cannot_be_determined_7034",
              "Variable '{0}' implicitly has type '{1}' in some locations "
              "where its type cannot be determined.");
};
static shared_ptr<DiagnosticMessage>
Try_npm_i_save_dev_types_Slash_1_if_it_exists_or_add_a_new_declaration_d_ts_file_containing_declare_module_0() {
  return diag(7035, DiagnosticCategory::Error,
              "Try_npm_i_save_dev_types_Slash_1_if_it_exists_or_add_a_new_"
              "declaration_d_ts_file_containing_declare__7035",
              "Try `npm i --save-dev @types/{1}` if it exists or add a new "
              "declaration (.d.ts) file containing `declare module '{0}';`");
};
static shared_ptr<DiagnosticMessage>
Dynamic_import_s_specifier_must_be_of_type_string_but_here_has_type_0() {
  return diag(7036, DiagnosticCategory::Error,
              "Dynamic_import_s_specifier_must_be_of_type_string_but_here_has_"
              "type_0_7036",
              "Dynamic import's specifier must be of type 'string', but here "
              "has type '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Enables_emit_interoperability_between_CommonJS_and_ES_Modules_via_creation_of_namespace_objects_for_all_imports_Implies_allowSyntheticDefaultImports() {
  return diag(7037, DiagnosticCategory::Message,
              "Enables_emit_interoperability_between_CommonJS_and_ES_Modules_"
              "via_creation_of_namespace_objects_for__7037",
              "Enables emit interoperability between CommonJS and ES Modules "
              "via creation of namespace objects for all imports. Implies "
              "'allowSyntheticDefaultImports'.");
};
static shared_ptr<DiagnosticMessage>
Type_originates_at_this_import_A_namespace_style_import_cannot_be_called_or_constructed_and_will_cause_a_failure_at_runtime_Consider_using_a_default_import_or_import_require_here_instead() {
  return diag(
      7038, DiagnosticCategory::Message,
      "Type_originates_at_this_import_A_namespace_style_import_cannot_be_"
      "called_or_constructed_and_will_cau_7038",
      "Type originates at this import. A namespace-style import cannot be "
      "called or constructed, and will cause a failure at runtime. Consider "
      "using a default import or import require here instead.");
};
static shared_ptr<DiagnosticMessage>
Mapped_object_type_implicitly_has_an_any_template_type() {
  return diag(7039, DiagnosticCategory::Error,
              "Mapped_object_type_implicitly_has_an_any_template_type_7039",
              "Mapped object type implicitly has an 'any' template type.");
};
static shared_ptr<DiagnosticMessage>
If_the_0_package_actually_exposes_this_module_consider_sending_a_pull_request_to_amend_https_Colon_Slash_Slashgithub_com_SlashDefinitelyTyped_SlashDefinitelyTyped_Slashtree_Slashmaster_Slashtypes_Slash_1() {
  return diag(7040, DiagnosticCategory::Error,
              "If_the_0_package_actually_exposes_this_module_consider_sending_"
              "a_pull_request_to_amend_https_Colon_S_7040",
              "If the '{0}' package actually exposes this module, consider "
              "sending a pull request to amend "
              "'https://github.com/DefinitelyTyped/DefinitelyTyped/tree/master/"
              "types/{1}'");
};
static shared_ptr<DiagnosticMessage>
The_containing_arrow_function_captures_the_global_value_of_this() {
  return diag(
      7041, DiagnosticCategory::Error,
      "The_containing_arrow_function_captures_the_global_value_of_this_7041",
      "The containing arrow function captures the global value of 'this'.");
};
static shared_ptr<DiagnosticMessage>
Module_0_was_resolved_to_1_but_resolveJsonModule_is_not_used() {
  return diag(
      7042, DiagnosticCategory::Error,
      "Module_0_was_resolved_to_1_but_resolveJsonModule_is_not_used_7042",
      "Module '{0}' was resolved to '{1}', but '--resolveJsonModule' is not "
      "used.");
};
static shared_ptr<DiagnosticMessage>
Variable_0_implicitly_has_an_1_type_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7043, DiagnosticCategory::Suggestion,
              "Variable_0_implicitly_has_an_1_type_but_a_better_type_may_be_"
              "inferred_from_usage_7043",
              "Variable '{0}' implicitly has an '{1}' type, but a better type "
              "may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Parameter_0_implicitly_has_an_1_type_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7044, DiagnosticCategory::Suggestion,
              "Parameter_0_implicitly_has_an_1_type_but_a_better_type_may_be_"
              "inferred_from_usage_7044",
              "Parameter '{0}' implicitly has an '{1}' type, but a better type "
              "may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Member_0_implicitly_has_an_1_type_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7045, DiagnosticCategory::Suggestion,
              "Member_0_implicitly_has_an_1_type_but_a_better_type_may_be_"
              "inferred_from_usage_7045",
              "Member '{0}' implicitly has an '{1}' type, but a better type "
              "may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Variable_0_implicitly_has_type_1_in_some_locations_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7046, DiagnosticCategory::Suggestion,
              "Variable_0_implicitly_has_type_1_in_some_locations_but_a_better_"
              "type_may_be_inferred_from_usage_7046",
              "Variable '{0}' implicitly has type '{1}' in some locations, but "
              "a better type may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Rest_parameter_0_implicitly_has_an_any_type_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7047, DiagnosticCategory::Suggestion,
              "Rest_parameter_0_implicitly_has_an_any_type_but_a_better_type_"
              "may_be_inferred_from_usage_7047",
              "Rest parameter '{0}' implicitly has an 'any[]' type, but a "
              "better type may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Property_0_implicitly_has_type_any_but_a_better_type_for_its_get_accessor_may_be_inferred_from_usage() {
  return diag(7048, DiagnosticCategory::Suggestion,
              "Property_0_implicitly_has_type_any_but_a_better_type_for_its_"
              "get_accessor_may_be_inferred_from_usage_7048",
              "Property '{0}' implicitly has type 'any', but a better type for "
              "its get accessor may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Property_0_implicitly_has_type_any_but_a_better_type_for_its_set_accessor_may_be_inferred_from_usage() {
  return diag(7049, DiagnosticCategory::Suggestion,
              "Property_0_implicitly_has_type_any_but_a_better_type_for_its_"
              "set_accessor_may_be_inferred_from_usage_7049",
              "Property '{0}' implicitly has type 'any', but a better type for "
              "its set accessor may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
_0_implicitly_has_an_1_return_type_but_a_better_type_may_be_inferred_from_usage() {
  return diag(7050, DiagnosticCategory::Suggestion,
              "_0_implicitly_has_an_1_return_type_but_a_better_type_may_be_"
              "inferred_from_usage_7050",
              "'{0}' implicitly has an '{1}' return type, but a better type "
              "may be inferred from usage.");
};
static shared_ptr<DiagnosticMessage>
Parameter_has_a_name_but_no_type_Did_you_mean_0_Colon_1() {
  return diag(7051, DiagnosticCategory::Error,
              "Parameter_has_a_name_but_no_type_Did_you_mean_0_Colon_1_7051",
              "Parameter has a name but no type. Did you mean '{0}: {1}'?");
};
static shared_ptr<DiagnosticMessage>
Element_implicitly_has_an_any_type_because_type_0_has_no_index_signature_Did_you_mean_to_call_1() {
  return diag(7052, DiagnosticCategory::Error,
              "Element_implicitly_has_an_any_type_because_type_0_has_no_index_"
              "signature_Did_you_mean_to_call_1_7052",
              "Element implicitly has an 'any' type because type '{0}' has no "
              "index signature. Did you mean to call '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Element_implicitly_has_an_any_type_because_expression_of_type_0_can_t_be_used_to_index_type_1() {
  return diag(7053, DiagnosticCategory::Error,
              "Element_implicitly_has_an_any_type_because_expression_of_type_0_"
              "can_t_be_used_to_index_type_1_7053",
              "Element implicitly has an 'any' type because expression of type "
              "'{0}' can't be used to index type '{1}'.");
};
static shared_ptr<DiagnosticMessage>
No_index_signature_with_a_parameter_of_type_0_was_found_on_type_1() {
  return diag(
      7054, DiagnosticCategory::Error,
      "No_index_signature_with_a_parameter_of_type_0_was_found_on_type_1_7054",
      "No index signature with a parameter of type '{0}' was found on type "
      "'{1}'.");
};
static shared_ptr<DiagnosticMessage>
_0_which_lacks_return_type_annotation_implicitly_has_an_1_yield_type() {
  return diag(7055, DiagnosticCategory::Error,
              "_0_which_lacks_return_type_annotation_implicitly_has_an_1_yield_"
              "type_7055",
              "'{0}', which lacks return-type annotation, implicitly has an "
              "'{1}' yield type.");
};
static shared_ptr<DiagnosticMessage>
The_inferred_type_of_this_node_exceeds_the_maximum_length_the_compiler_will_serialize_An_explicit_type_annotation_is_needed() {
  return diag(
      7056, DiagnosticCategory::Error,
      "The_inferred_type_of_this_node_exceeds_the_maximum_length_the_compiler_"
      "will_serialize_An_explicit_ty_7056",
      "The inferred type of this node exceeds the maximum length the compiler "
      "will serialize. An explicit type annotation is needed.");
};
static shared_ptr<DiagnosticMessage>
yield_expression_implicitly_results_in_an_any_type_because_its_containing_generator_lacks_a_return_type_annotation() {
  return diag(7057, DiagnosticCategory::Error,
              "yield_expression_implicitly_results_in_an_any_type_because_its_"
              "containing_generator_lacks_a_return_t_7057",
              "'yield' expression implicitly results in an 'any' type because "
              "its containing generator lacks a return-type annotation.");
};
static shared_ptr<DiagnosticMessage>
If_the_0_package_actually_exposes_this_module_try_adding_a_new_declaration_d_ts_file_containing_declare_module_1() {
  return diag(
      7058, DiagnosticCategory::Error,
      "If_the_0_package_actually_exposes_this_module_try_adding_a_new_"
      "declaration_d_ts_file_containing_decl_7058",
      "If the '{0}' package actually exposes this module, try adding a new "
      "declaration (.d.ts) file containing `declare module '{1}';`");
};
static shared_ptr<DiagnosticMessage>
This_syntax_is_reserved_in_files_with_the_mts_or_cts_extension_Use_an_as_expression_instead() {
  return diag(7059, DiagnosticCategory::Error,
              "This_syntax_is_reserved_in_files_with_the_mts_or_cts_extension_"
              "Use_an_as_expression_instead_7059",
              "This syntax is reserved in files with the .mts or .cts "
              "extension. Use an `as` expression instead.");
};
static shared_ptr<DiagnosticMessage>
This_syntax_is_reserved_in_files_with_the_mts_or_cts_extension_Add_a_trailing_comma_or_explicit_constraint() {
  return diag(7060, DiagnosticCategory::Error,
              "This_syntax_is_reserved_in_files_with_the_mts_or_cts_extension_"
              "Add_a_trailing_comma_or_explicit_cons_7060",
              "This syntax is reserved in files with the .mts or .cts "
              "extension. Add a trailing comma or explicit constraint.");
};
static shared_ptr<DiagnosticMessage>
A_mapped_type_may_not_declare_properties_or_methods() {
  return diag(7061, DiagnosticCategory::Error,
              "A_mapped_type_may_not_declare_properties_or_methods_7061",
              "A mapped type may not declare properties or methods.");
};
static shared_ptr<DiagnosticMessage>
JSON_imports_are_experimental_in_ES_module_mode_imports() {
  return diag(7062, DiagnosticCategory::Error,
              "JSON_imports_are_experimental_in_ES_module_mode_imports_7062",
              "JSON imports are experimental in ES module mode imports.");
};
static shared_ptr<DiagnosticMessage> You_cannot_rename_this_element() {
  return diag(8000, DiagnosticCategory::Error,
              "You_cannot_rename_this_element_8000",
              "You cannot rename this element.");
};
static shared_ptr<DiagnosticMessage>
You_cannot_rename_elements_that_are_defined_in_the_standard_TypeScript_library() {
  return diag(8001, DiagnosticCategory::Error,
              "You_cannot_rename_elements_that_are_defined_in_the_standard_"
              "TypeScript_library_8001",
              "You cannot rename elements that are defined in the standard "
              "TypeScript library.");
};
static shared_ptr<DiagnosticMessage>
import_can_only_be_used_in_TypeScript_files() {
  return diag(8002, DiagnosticCategory::Error,
              "import_can_only_be_used_in_TypeScript_files_8002",
              "'import ... =' can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
export_can_only_be_used_in_TypeScript_files() {
  return diag(8003, DiagnosticCategory::Error,
              "export_can_only_be_used_in_TypeScript_files_8003",
              "'export =' can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Type_parameter_declarations_can_only_be_used_in_TypeScript_files() {
  return diag(
      8004, DiagnosticCategory::Error,
      "Type_parameter_declarations_can_only_be_used_in_TypeScript_files_8004",
      "Type parameter declarations can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
implements_clauses_can_only_be_used_in_TypeScript_files() {
  return diag(8005, DiagnosticCategory::Error,
              "implements_clauses_can_only_be_used_in_TypeScript_files_8005",
              "'implements' clauses can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
_0_declarations_can_only_be_used_in_TypeScript_files() {
  return diag(8006, DiagnosticCategory::Error,
              "_0_declarations_can_only_be_used_in_TypeScript_files_8006",
              "'{0}' declarations can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Type_aliases_can_only_be_used_in_TypeScript_files() {
  return diag(8008, DiagnosticCategory::Error,
              "Type_aliases_can_only_be_used_in_TypeScript_files_8008",
              "Type aliases can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
The_0_modifier_can_only_be_used_in_TypeScript_files() {
  return diag(8009, DiagnosticCategory::Error,
              "The_0_modifier_can_only_be_used_in_TypeScript_files_8009",
              "The '{0}' modifier can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Type_annotations_can_only_be_used_in_TypeScript_files() {
  return diag(8010, DiagnosticCategory::Error,
              "Type_annotations_can_only_be_used_in_TypeScript_files_8010",
              "Type annotations can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Type_arguments_can_only_be_used_in_TypeScript_files() {
  return diag(8011, DiagnosticCategory::Error,
              "Type_arguments_can_only_be_used_in_TypeScript_files_8011",
              "Type arguments can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Parameter_modifiers_can_only_be_used_in_TypeScript_files() {
  return diag(8012, DiagnosticCategory::Error,
              "Parameter_modifiers_can_only_be_used_in_TypeScript_files_8012",
              "Parameter modifiers can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Non_null_assertions_can_only_be_used_in_TypeScript_files() {
  return diag(8013, DiagnosticCategory::Error,
              "Non_null_assertions_can_only_be_used_in_TypeScript_files_8013",
              "Non-null assertions can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Type_assertion_expressions_can_only_be_used_in_TypeScript_files() {
  return diag(
      8016, DiagnosticCategory::Error,
      "Type_assertion_expressions_can_only_be_used_in_TypeScript_files_8016",
      "Type assertion expressions can only be used in TypeScript files.");
};
static shared_ptr<DiagnosticMessage>
Octal_literal_types_must_use_ES2015_syntax_Use_the_syntax_0() {
  return diag(
      8017, DiagnosticCategory::Error,
      "Octal_literal_types_must_use_ES2015_syntax_Use_the_syntax_0_8017",
      "Octal literal types must use ES2015 syntax. Use the syntax '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Octal_literals_are_not_allowed_in_enums_members_initializer_Use_the_syntax_0() {
  return diag(8018, DiagnosticCategory::Error,
              "Octal_literals_are_not_allowed_in_enums_members_initializer_Use_"
              "the_syntax_0_8018",
              "Octal literals are not allowed in enums members initializer. "
              "Use the syntax '{0}'.");
};
static shared_ptr<DiagnosticMessage> Report_errors_in_js_files() {
  return diag(8019, DiagnosticCategory::Message,
              "Report_errors_in_js_files_8019", "Report errors in .js files.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_types_can_only_be_used_inside_documentation_comments() {
  return diag(8020, DiagnosticCategory::Error,
              "JSDoc_types_can_only_be_used_inside_documentation_comments_8020",
              "JSDoc types can only be used inside documentation comments.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_typedef_tag_should_either_have_a_type_annotation_or_be_followed_by_property_or_member_tags() {
  return diag(8021, DiagnosticCategory::Error,
              "JSDoc_typedef_tag_should_either_have_a_type_annotation_or_be_"
              "followed_by_property_or_member_tags_8021",
              "JSDoc '@typedef' tag should either have a type annotation or be "
              "followed by '@property' or '@member' tags.");
};
static shared_ptr<DiagnosticMessage> JSDoc_0_is_not_attached_to_a_class() {
  return diag(8022, DiagnosticCategory::Error,
              "JSDoc_0_is_not_attached_to_a_class_8022",
              "JSDoc '@{0}' is not attached to a class.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_0_1_does_not_match_the_extends_2_clause() {
  return diag(8023, DiagnosticCategory::Error,
              "JSDoc_0_1_does_not_match_the_extends_2_clause_8023",
              "JSDoc '@{0} {1}' does not match the 'extends {2}' clause.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_param_tag_has_name_0_but_there_is_no_parameter_with_that_name() {
  return diag(8024, DiagnosticCategory::Error,
              "JSDoc_param_tag_has_name_0_but_there_is_no_parameter_with_that_"
              "name_8024",
              "JSDoc '@param' tag has name '{0}', but there is no parameter "
              "with that name.");
};
static shared_ptr<DiagnosticMessage>
Class_declarations_cannot_have_more_than_one_augments_or_extends_tag() {
  return diag(8025, DiagnosticCategory::Error,
              "Class_declarations_cannot_have_more_than_one_augments_or_"
              "extends_tag_8025",
              "Class declarations cannot have more than one '@augments' or "
              "'@extends' tag.");
};
static shared_ptr<DiagnosticMessage>
Expected_0_type_arguments_provide_these_with_an_extends_tag() {
  return diag(
      8026, DiagnosticCategory::Error,
      "Expected_0_type_arguments_provide_these_with_an_extends_tag_8026",
      "Expected {0} type arguments; provide these with an '@extends' tag.");
};
static shared_ptr<DiagnosticMessage>
Expected_0_1_type_arguments_provide_these_with_an_extends_tag() {
  return diag(
      8027, DiagnosticCategory::Error,
      "Expected_0_1_type_arguments_provide_these_with_an_extends_tag_8027",
      "Expected {0}-{1} type arguments; provide these with an '@extends' tag.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_may_only_appear_in_the_last_parameter_of_a_signature() {
  return diag(
      8028, DiagnosticCategory::Error,
      "JSDoc_may_only_appear_in_the_last_parameter_of_a_signature_8028",
      "JSDoc '...' may only appear in the last parameter of a signature.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_param_tag_has_name_0_but_there_is_no_parameter_with_that_name_It_would_match_arguments_if_it_had_an_array_type() {
  return diag(
      8029, DiagnosticCategory::Error,
      "JSDoc_param_tag_has_name_0_but_there_is_no_parameter_with_that_name_It_"
      "would_match_arguments_if_it_h_8029",
      "JSDoc '@param' tag has name '{0}', but there is no parameter with that "
      "name. It would match 'arguments' if it had an array type.");
};
static shared_ptr<DiagnosticMessage>
The_type_of_a_function_declaration_must_match_the_function_s_signature() {
  return diag(8030, DiagnosticCategory::Error,
              "The_type_of_a_function_declaration_must_match_the_function_s_"
              "signature_8030",
              "The type of a function declaration must match the function's "
              "signature.");
};
static shared_ptr<DiagnosticMessage>
You_cannot_rename_a_module_via_a_global_import() {
  return diag(8031, DiagnosticCategory::Error,
              "You_cannot_rename_a_module_via_a_global_import_8031",
              "You cannot rename a module via a global import.");
};
static shared_ptr<DiagnosticMessage>
Qualified_name_0_is_not_allowed_without_a_leading_param_object_1() {
  return diag(
      8032, DiagnosticCategory::Error,
      "Qualified_name_0_is_not_allowed_without_a_leading_param_object_1_8032",
      "Qualified name '{0}' is not allowed without a leading '@param {object} "
      "{1}'.");
};
static shared_ptr<DiagnosticMessage>
A_JSDoc_typedef_comment_may_not_contain_multiple_type_tags() {
  return diag(
      8033, DiagnosticCategory::Error,
      "A_JSDoc_typedef_comment_may_not_contain_multiple_type_tags_8033",
      "A JSDoc '@typedef' comment may not contain multiple '@type' tags.");
};
static shared_ptr<DiagnosticMessage> The_tag_was_first_specified_here() {
  return diag(8034, DiagnosticCategory::Error,
              "The_tag_was_first_specified_here_8034",
              "The tag was first specified here.");
};
static shared_ptr<DiagnosticMessage>
Declaration_emit_for_this_file_requires_using_private_name_0_An_explicit_type_annotation_may_unblock_declaration_emit() {
  return diag(
      9005, DiagnosticCategory::Error,
      "Declaration_emit_for_this_file_requires_using_private_name_0_An_"
      "explicit_type_annotation_may_unblock_9005",
      "Declaration emit for this file requires using private name '{0}'. An "
      "explicit type annotation may unblock declaration emit.");
};
static shared_ptr<DiagnosticMessage>
Declaration_emit_for_this_file_requires_using_private_name_0_from_module_1_An_explicit_type_annotation_may_unblock_declaration_emit() {
  return diag(9006, DiagnosticCategory::Error,
              "Declaration_emit_for_this_file_requires_using_private_name_0_"
              "from_module_1_An_explicit_type_annotati_9006",
              "Declaration emit for this file requires using private name "
              "'{0}' from module '{1}'. An explicit type annotation may "
              "unblock declaration emit.");
};
static shared_ptr<DiagnosticMessage>
JSX_attributes_must_only_be_assigned_a_non_empty_expression() {
  return diag(
      17000, DiagnosticCategory::Error,
      "JSX_attributes_must_only_be_assigned_a_non_empty_expression_17000",
      "JSX attributes must only be assigned a non-empty 'expression'.");
};
static shared_ptr<DiagnosticMessage>
JSX_elements_cannot_have_multiple_attributes_with_the_same_name() {
  return diag(
      17001, DiagnosticCategory::Error,
      "JSX_elements_cannot_have_multiple_attributes_with_the_same_name_17001",
      "JSX elements cannot have multiple attributes with the same name.");
};
static shared_ptr<DiagnosticMessage>
Expected_corresponding_JSX_closing_tag_for_0() {
  return diag(17002, DiagnosticCategory::Error,
              "Expected_corresponding_JSX_closing_tag_for_0_17002",
              "Expected corresponding JSX closing tag for '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Cannot_use_JSX_unless_the_jsx_flag_is_provided() {
  return diag(17004, DiagnosticCategory::Error,
              "Cannot_use_JSX_unless_the_jsx_flag_is_provided_17004",
              "Cannot use JSX unless the '--jsx' flag is provided.");
};
static shared_ptr<DiagnosticMessage>
A_constructor_cannot_contain_a_super_call_when_its_class_extends_null() {
  return diag(17005, DiagnosticCategory::Error,
              "A_constructor_cannot_contain_a_super_call_when_its_class_"
              "extends_null_17005",
              "A constructor cannot contain a 'super' call when its class "
              "extends 'null'.");
};
static shared_ptr<DiagnosticMessage>
An_unary_expression_with_the_0_operator_is_not_allowed_in_the_left_hand_side_of_an_exponentiation_expression_Consider_enclosing_the_expression_in_parentheses() {
  return diag(17006, DiagnosticCategory::Error,
              "An_unary_expression_with_the_0_operator_is_not_allowed_in_the_"
              "left_hand_side_of_an_exponentiation_ex_17006",
              "An unary expression with the '{0}' operator is not allowed in "
              "the left-hand side of an exponentiation expression. Consider "
              "enclosing the expression in parentheses.");
};
static shared_ptr<DiagnosticMessage>
A_type_assertion_expression_is_not_allowed_in_the_left_hand_side_of_an_exponentiation_expression_Consider_enclosing_the_expression_in_parentheses() {
  return diag(17007, DiagnosticCategory::Error,
              "A_type_assertion_expression_is_not_allowed_in_the_left_hand_"
              "side_of_an_exponentiation_expression_Con_17007",
              "A type assertion expression is not allowed in the left-hand "
              "side of an exponentiation expression. Consider enclosing the "
              "expression in parentheses.");
};
static shared_ptr<DiagnosticMessage>
JSX_element_0_has_no_corresponding_closing_tag() {
  return diag(17008, DiagnosticCategory::Error,
              "JSX_element_0_has_no_corresponding_closing_tag_17008",
              "JSX element '{0}' has no corresponding closing tag.");
};
static shared_ptr<DiagnosticMessage>
super_must_be_called_before_accessing_this_in_the_constructor_of_a_derived_class() {
  return diag(17009, DiagnosticCategory::Error,
              "super_must_be_called_before_accessing_this_in_the_constructor_"
              "of_a_derived_class_17009",
              "'super' must be called before accessing 'this' in the "
              "constructor of a derived class.");
};
static shared_ptr<DiagnosticMessage> Unknown_type_acquisition_option_0() {
  return diag(17010, DiagnosticCategory::Error,
              "Unknown_type_acquisition_option_0_17010",
              "Unknown type acquisition option '{0}'.");
};
static shared_ptr<DiagnosticMessage>
super_must_be_called_before_accessing_a_property_of_super_in_the_constructor_of_a_derived_class() {
  return diag(17011, DiagnosticCategory::Error,
              "super_must_be_called_before_accessing_a_property_of_super_in_"
              "the_constructor_of_a_derived_class_17011",
              "'super' must be called before accessing a property of 'super' "
              "in the constructor of a derived class.");
};
static shared_ptr<DiagnosticMessage>
_0_is_not_a_valid_meta_property_for_keyword_1_Did_you_mean_2() {
  return diag(
      17012, DiagnosticCategory::Error,
      "_0_is_not_a_valid_meta_property_for_keyword_1_Did_you_mean_2_17012",
      "'{0}' is not a valid meta-property for keyword '{1}'. Did you mean "
      "'{2}'?");
};
static shared_ptr<DiagnosticMessage>
Meta_property_0_is_only_allowed_in_the_body_of_a_function_declaration_function_expression_or_constructor() {
  return diag(17013, DiagnosticCategory::Error,
              "Meta_property_0_is_only_allowed_in_the_body_of_a_function_"
              "declaration_function_expression_or_constru_17013",
              "Meta-property '{0}' is only allowed in the body of a function "
              "declaration, function expression, or constructor.");
};
static shared_ptr<DiagnosticMessage>
JSX_fragment_has_no_corresponding_closing_tag() {
  return diag(17014, DiagnosticCategory::Error,
              "JSX_fragment_has_no_corresponding_closing_tag_17014",
              "JSX fragment has no corresponding closing tag.");
};
static shared_ptr<DiagnosticMessage>
Expected_corresponding_closing_tag_for_JSX_fragment() {
  return diag(17015, DiagnosticCategory::Error,
              "Expected_corresponding_closing_tag_for_JSX_fragment_17015",
              "Expected corresponding closing tag for JSX fragment.");
};
static shared_ptr<DiagnosticMessage>
The_jsxFragmentFactory_compiler_option_must_be_provided_to_use_JSX_fragments_with_the_jsxFactory_compiler_option() {
  return diag(17016, DiagnosticCategory::Error,
              "The_jsxFragmentFactory_compiler_option_must_be_provided_to_use_"
              "JSX_fragments_with_the_jsxFactory_com_17016",
              "The 'jsxFragmentFactory' compiler option must be provided to "
              "use JSX fragments with the 'jsxFactory' compiler option.");
};
static shared_ptr<DiagnosticMessage>
An_jsxFrag_pragma_is_required_when_using_an_jsx_pragma_with_JSX_fragments() {
  return diag(17017, DiagnosticCategory::Error,
              "An_jsxFrag_pragma_is_required_when_using_an_jsx_pragma_with_JSX_"
              "fragments_17017",
              "An @jsxFrag pragma is required when using an @jsx pragma with "
              "JSX fragments.");
};
static shared_ptr<DiagnosticMessage>
Unknown_type_acquisition_option_0_Did_you_mean_1() {
  return diag(17018, DiagnosticCategory::Error,
              "Unknown_type_acquisition_option_0_Did_you_mean_1_17018",
              "Unknown type acquisition option '{0}'. Did you mean '{1}'?");
};
static shared_ptr<DiagnosticMessage>
Circularity_detected_while_resolving_configuration_Colon_0() {
  return diag(
      18000, DiagnosticCategory::Error,
      "Circularity_detected_while_resolving_configuration_Colon_0_18000",
      "Circularity detected while resolving configuration: {0}");
};
static shared_ptr<DiagnosticMessage>
The_files_list_in_config_file_0_is_empty() {
  return diag(18002, DiagnosticCategory::Error,
              "The_files_list_in_config_file_0_is_empty_18002",
              "The 'files' list in config file '{0}' is empty.");
};
static shared_ptr<DiagnosticMessage>
No_inputs_were_found_in_config_file_0_Specified_include_paths_were_1_and_exclude_paths_were_2() {
  return diag(18003, DiagnosticCategory::Error,
              "No_inputs_were_found_in_config_file_0_Specified_include_paths_"
              "were_1_and_exclude_paths_were_2_18003",
              "No inputs were found in config file '{0}'. Specified 'include' "
              "paths were '{1}' and 'exclude' paths were '{2}'.");
};
static shared_ptr<DiagnosticMessage>
File_is_a_CommonJS_module_it_may_be_converted_to_an_ES_module() {
  return diag(
      80001, DiagnosticCategory::Suggestion,
      "File_is_a_CommonJS_module_it_may_be_converted_to_an_ES_module_80001",
      "File is a CommonJS module; it may be converted to an ES module.");
};
static shared_ptr<DiagnosticMessage>
This_constructor_function_may_be_converted_to_a_class_declaration() {
  return diag(
      80002, DiagnosticCategory::Suggestion,
      "This_constructor_function_may_be_converted_to_a_class_declaration_80002",
      "This constructor function may be converted to a class declaration.");
};
static shared_ptr<DiagnosticMessage>
Import_may_be_converted_to_a_default_import() {
  return diag(80003, DiagnosticCategory::Suggestion,
              "Import_may_be_converted_to_a_default_import_80003",
              "Import may be converted to a default import.");
};
static shared_ptr<DiagnosticMessage>
JSDoc_types_may_be_moved_to_TypeScript_types() {
  return diag(80004, DiagnosticCategory::Suggestion,
              "JSDoc_types_may_be_moved_to_TypeScript_types_80004",
              "JSDoc types may be moved to TypeScript types.");
};
static shared_ptr<DiagnosticMessage>
require_call_may_be_converted_to_an_import() {
  return diag(80005, DiagnosticCategory::Suggestion,
              "require_call_may_be_converted_to_an_import_80005",
              "'require' call may be converted to an import.");
};
static shared_ptr<DiagnosticMessage>
This_may_be_converted_to_an_async_function() {
  return diag(80006, DiagnosticCategory::Suggestion,
              "This_may_be_converted_to_an_async_function_80006",
              "This may be converted to an async function.");
};
static shared_ptr<DiagnosticMessage>
await_has_no_effect_on_the_type_of_this_expression() {
  return diag(80007, DiagnosticCategory::Suggestion,
              "await_has_no_effect_on_the_type_of_this_expression_80007",
              "'await' has no effect on the type of this expression.");
};
static shared_ptr<DiagnosticMessage>
Numeric_literals_with_absolute_values_equal_to_2_53_or_greater_are_too_large_to_be_represented_accurately_as_integers() {
  return diag(80008, DiagnosticCategory::Suggestion,
              "Numeric_literals_with_absolute_values_equal_to_2_53_or_greater_"
              "are_too_large_to_be_represented_accur_80008",
              "Numeric literals with absolute values equal to 2^53 or greater "
              "are too large to be represented accurately as integers.");
};
static shared_ptr<DiagnosticMessage> Add_missing_super_call() {
  return diag(90001, DiagnosticCategory::Message,
              "Add_missing_super_call_90001", "Add missing 'super()' call");
};
static shared_ptr<DiagnosticMessage>
Make_super_call_the_first_statement_in_the_constructor() {
  return diag(90002, DiagnosticCategory::Message,
              "Make_super_call_the_first_statement_in_the_constructor_90002",
              "Make 'super()' call the first statement in the constructor");
};
static shared_ptr<DiagnosticMessage> Change_extends_to_implements() {
  return diag(90003, DiagnosticCategory::Message,
              "Change_extends_to_implements_90003",
              "Change 'extends' to 'implements'");
};
static shared_ptr<DiagnosticMessage> Remove_unused_declaration_for_Colon_0() {
  return diag(90004, DiagnosticCategory::Message,
              "Remove_unused_declaration_for_Colon_0_90004",
              "Remove unused declaration for: '{0}'");
};
static shared_ptr<DiagnosticMessage> Remove_import_from_0() {
  return diag(90005, DiagnosticCategory::Message, "Remove_import_from_0_90005",
              "Remove import from '{0}'");
};
static shared_ptr<DiagnosticMessage> Implement_interface_0() {
  return diag(90006, DiagnosticCategory::Message, "Implement_interface_0_90006",
              "Implement interface '{0}'");
};
static shared_ptr<DiagnosticMessage> Implement_inherited_abstract_class() {
  return diag(90007, DiagnosticCategory::Message,
              "Implement_inherited_abstract_class_90007",
              "Implement inherited abstract class");
};
static shared_ptr<DiagnosticMessage> Add_0_to_unresolved_variable() {
  return diag(90008, DiagnosticCategory::Message,
              "Add_0_to_unresolved_variable_90008",
              "Add '{0}.' to unresolved variable");
};
static shared_ptr<DiagnosticMessage> Remove_variable_statement() {
  return diag(90010, DiagnosticCategory::Message,
              "Remove_variable_statement_90010", "Remove variable statement");
};
static shared_ptr<DiagnosticMessage> Remove_template_tag() {
  return diag(90011, DiagnosticCategory::Message, "Remove_template_tag_90011",
              "Remove template tag");
};
static shared_ptr<DiagnosticMessage> Remove_type_parameters() {
  return diag(90012, DiagnosticCategory::Message,
              "Remove_type_parameters_90012", "Remove type parameters");
};
static shared_ptr<DiagnosticMessage> Import_0_from_module_1() {
  return diag(90013, DiagnosticCategory::Message,
              "Import_0_from_module_1_90013",
              "Import '{0}' from module \"{1}\"");
};
static shared_ptr<DiagnosticMessage> Change_0_to_1() {
  return diag(90014, DiagnosticCategory::Message, "Change_0_to_1_90014",
              "Change '{0}' to '{1}'");
};
static shared_ptr<DiagnosticMessage>
Add_0_to_existing_import_declaration_from_1() {
  return diag(90015, DiagnosticCategory::Message,
              "Add_0_to_existing_import_declaration_from_1_90015",
              "Add '{0}' to existing import declaration from \"{1}\"");
};
static shared_ptr<DiagnosticMessage> Declare_property_0() {
  return diag(90016, DiagnosticCategory::Message, "Declare_property_0_90016",
              "Declare property '{0}'");
};
static shared_ptr<DiagnosticMessage> Add_index_signature_for_property_0() {
  return diag(90017, DiagnosticCategory::Message,
              "Add_index_signature_for_property_0_90017",
              "Add index signature for property '{0}'");
};
static shared_ptr<DiagnosticMessage> Disable_checking_for_this_file() {
  return diag(90018, DiagnosticCategory::Message,
              "Disable_checking_for_this_file_90018",
              "Disable checking for this file");
};
static shared_ptr<DiagnosticMessage> Ignore_this_error_message() {
  return diag(90019, DiagnosticCategory::Message,
              "Ignore_this_error_message_90019", "Ignore this error message");
};
static shared_ptr<DiagnosticMessage>
Initialize_property_0_in_the_constructor() {
  return diag(90020, DiagnosticCategory::Message,
              "Initialize_property_0_in_the_constructor_90020",
              "Initialize property '{0}' in the constructor");
};
static shared_ptr<DiagnosticMessage> Initialize_static_property_0() {
  return diag(90021, DiagnosticCategory::Message,
              "Initialize_static_property_0_90021",
              "Initialize static property '{0}'");
};
static shared_ptr<DiagnosticMessage> Change_spelling_to_0() {
  return diag(90022, DiagnosticCategory::Message, "Change_spelling_to_0_90022",
              "Change spelling to '{0}'");
};
static shared_ptr<DiagnosticMessage> Declare_method_0() {
  return diag(90023, DiagnosticCategory::Message, "Declare_method_0_90023",
              "Declare method '{0}'");
};
static shared_ptr<DiagnosticMessage> Declare_static_method_0() {
  return diag(90024, DiagnosticCategory::Message,
              "Declare_static_method_0_90024", "Declare static method '{0}'");
};
static shared_ptr<DiagnosticMessage> Prefix_0_with_an_underscore() {
  return diag(90025, DiagnosticCategory::Message,
              "Prefix_0_with_an_underscore_90025",
              "Prefix '{0}' with an underscore");
};
static shared_ptr<DiagnosticMessage> Rewrite_as_the_indexed_access_type_0() {
  return diag(90026, DiagnosticCategory::Message,
              "Rewrite_as_the_indexed_access_type_0_90026",
              "Rewrite as the indexed access type '{0}'");
};
static shared_ptr<DiagnosticMessage> Declare_static_property_0() {
  return diag(90027, DiagnosticCategory::Message,
              "Declare_static_property_0_90027",
              "Declare static property '{0}'");
};
static shared_ptr<DiagnosticMessage> Call_decorator_expression() {
  return diag(90028, DiagnosticCategory::Message,
              "Call_decorator_expression_90028", "Call decorator expression");
};
static shared_ptr<DiagnosticMessage>
Add_async_modifier_to_containing_function() {
  return diag(90029, DiagnosticCategory::Message,
              "Add_async_modifier_to_containing_function_90029",
              "Add async modifier to containing function");
};
static shared_ptr<DiagnosticMessage> Replace_infer_0_with_unknown() {
  return diag(90030, DiagnosticCategory::Message,
              "Replace_infer_0_with_unknown_90030",
              "Replace 'infer {0}' with 'unknown'");
};
static shared_ptr<DiagnosticMessage> Replace_all_unused_infer_with_unknown() {
  return diag(90031, DiagnosticCategory::Message,
              "Replace_all_unused_infer_with_unknown_90031",
              "Replace all unused 'infer' with 'unknown'");
};
static shared_ptr<DiagnosticMessage> Import_default_0_from_module_1() {
  return diag(90032, DiagnosticCategory::Message,
              "Import_default_0_from_module_1_90032",
              "Import default '{0}' from module \"{1}\"");
};
static shared_ptr<DiagnosticMessage>
Add_default_import_0_to_existing_import_declaration_from_1() {
  return diag(
      90033, DiagnosticCategory::Message,
      "Add_default_import_0_to_existing_import_declaration_from_1_90033",
      "Add default import '{0}' to existing import declaration from \"{1}\"");
};
static shared_ptr<DiagnosticMessage> Add_parameter_name() {
  return diag(90034, DiagnosticCategory::Message, "Add_parameter_name_90034",
              "Add parameter name");
};
static shared_ptr<DiagnosticMessage> Declare_private_property_0() {
  return diag(90035, DiagnosticCategory::Message,
              "Declare_private_property_0_90035",
              "Declare private property '{0}'");
};
static shared_ptr<DiagnosticMessage> Replace_0_with_Promise_1() {
  return diag(90036, DiagnosticCategory::Message,
              "Replace_0_with_Promise_1_90036",
              "Replace '{0}' with 'Promise<{1}>'");
};
static shared_ptr<DiagnosticMessage>
Fix_all_incorrect_return_type_of_an_async_functions() {
  return diag(90037, DiagnosticCategory::Message,
              "Fix_all_incorrect_return_type_of_an_async_functions_90037",
              "Fix all incorrect return type of an async functions");
};
static shared_ptr<DiagnosticMessage> Declare_private_method_0() {
  return diag(90038, DiagnosticCategory::Message,
              "Declare_private_method_0_90038", "Declare private method '{0}'");
};
static shared_ptr<DiagnosticMessage> Remove_unused_destructuring_declaration() {
  return diag(90039, DiagnosticCategory::Message,
              "Remove_unused_destructuring_declaration_90039",
              "Remove unused destructuring declaration");
};
static shared_ptr<DiagnosticMessage> Remove_unused_declarations_for_Colon_0() {
  return diag(90041, DiagnosticCategory::Message,
              "Remove_unused_declarations_for_Colon_0_90041",
              "Remove unused declarations for: '{0}'");
};
static shared_ptr<DiagnosticMessage> Declare_a_private_field_named_0() {
  return diag(90053, DiagnosticCategory::Message,
              "Declare_a_private_field_named_0_90053",
              "Declare a private field named '{0}'.");
};
static shared_ptr<DiagnosticMessage>
Includes_imports_of_types_referenced_by_0() {
  return diag(90054, DiagnosticCategory::Message,
              "Includes_imports_of_types_referenced_by_0_90054",
              "Includes imports of types referenced by '{0}'");
};
static shared_ptr<DiagnosticMessage> Convert_function_to_an_ES2015_class() {
  return diag(95001, DiagnosticCategory::Message,
              "Convert_function_to_an_ES2015_class_95001",
              "Convert function to an ES2015 class");
};
static shared_ptr<DiagnosticMessage> Convert_0_to_1_in_0() {
  return diag(95003, DiagnosticCategory::Message, "Convert_0_to_1_in_0_95003",
              "Convert '{0}' to '{1} in {0}'");
};
static shared_ptr<DiagnosticMessage> Extract_to_0_in_1() {
  return diag(95004, DiagnosticCategory::Message, "Extract_to_0_in_1_95004",
              "Extract to {0} in {1}");
};
static shared_ptr<DiagnosticMessage> Extract_function() {
  return diag(95005, DiagnosticCategory::Message, "Extract_function_95005",
              "Extract function");
};
static shared_ptr<DiagnosticMessage> Extract_constant() {
  return diag(95006, DiagnosticCategory::Message, "Extract_constant_95006",
              "Extract constant");
};
static shared_ptr<DiagnosticMessage> Extract_to_0_in_enclosing_scope() {
  return diag(95007, DiagnosticCategory::Message,
              "Extract_to_0_in_enclosing_scope_95007",
              "Extract to {0} in enclosing scope");
};
static shared_ptr<DiagnosticMessage> Extract_to_0_in_1_scope() {
  return diag(95008, DiagnosticCategory::Message,
              "Extract_to_0_in_1_scope_95008", "Extract to {0} in {1} scope");
};
static shared_ptr<DiagnosticMessage> Annotate_with_type_from_JSDoc() {
  return diag(95009, DiagnosticCategory::Message,
              "Annotate_with_type_from_JSDoc_95009",
              "Annotate with type from JSDoc");
};
static shared_ptr<DiagnosticMessage> Infer_type_of_0_from_usage() {
  return diag(95011, DiagnosticCategory::Message,
              "Infer_type_of_0_from_usage_95011",
              "Infer type of '{0}' from usage");
};
static shared_ptr<DiagnosticMessage> Infer_parameter_types_from_usage() {
  return diag(95012, DiagnosticCategory::Message,
              "Infer_parameter_types_from_usage_95012",
              "Infer parameter types from usage");
};
static shared_ptr<DiagnosticMessage> Convert_to_default_import() {
  return diag(95013, DiagnosticCategory::Message,
              "Convert_to_default_import_95013", "Convert to default import");
};
static shared_ptr<DiagnosticMessage> Install_0() {
  return diag(95014, DiagnosticCategory::Message, "Install_0_95014",
              "Install '{0}'");
};
static shared_ptr<DiagnosticMessage> Replace_import_with_0() {
  return diag(95015, DiagnosticCategory::Message, "Replace_import_with_0_95015",
              "Replace import with '{0}'.");
};
static shared_ptr<DiagnosticMessage> Use_synthetic_default_member() {
  return diag(95016, DiagnosticCategory::Message,
              "Use_synthetic_default_member_95016",
              "Use synthetic 'default' member.");
};
static shared_ptr<DiagnosticMessage> Convert_to_ES_module() {
  return diag(95017, DiagnosticCategory::Message, "Convert_to_ES_module_95017",
              "Convert to ES module");
};
static shared_ptr<DiagnosticMessage> Add_undefined_type_to_property_0() {
  return diag(95018, DiagnosticCategory::Message,
              "Add_undefined_type_to_property_0_95018",
              "Add 'undefined' type to property '{0}'");
};
static shared_ptr<DiagnosticMessage> Add_initializer_to_property_0() {
  return diag(95019, DiagnosticCategory::Message,
              "Add_initializer_to_property_0_95019",
              "Add initializer to property '{0}'");
};
static shared_ptr<DiagnosticMessage>
Add_definite_assignment_assertion_to_property_0() {
  return diag(95020, DiagnosticCategory::Message,
              "Add_definite_assignment_assertion_to_property_0_95020",
              "Add definite assignment assertion to property '{0}'");
};
static shared_ptr<DiagnosticMessage>
Convert_all_type_literals_to_mapped_type() {
  return diag(95021, DiagnosticCategory::Message,
              "Convert_all_type_literals_to_mapped_type_95021",
              "Convert all type literals to mapped type");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_members() {
  return diag(95022, DiagnosticCategory::Message,
              "Add_all_missing_members_95022", "Add all missing members");
};
static shared_ptr<DiagnosticMessage> Infer_all_types_from_usage() {
  return diag(95023, DiagnosticCategory::Message,
              "Infer_all_types_from_usage_95023", "Infer all types from usage");
};
static shared_ptr<DiagnosticMessage> Delete_all_unused_declarations() {
  return diag(95024, DiagnosticCategory::Message,
              "Delete_all_unused_declarations_95024",
              "Delete all unused declarations");
};
static shared_ptr<DiagnosticMessage>
Prefix_all_unused_declarations_with_where_possible() {
  return diag(95025, DiagnosticCategory::Message,
              "Prefix_all_unused_declarations_with_where_possible_95025",
              "Prefix all unused declarations with '_' where possible");
};
static shared_ptr<DiagnosticMessage> Fix_all_detected_spelling_errors() {
  return diag(95026, DiagnosticCategory::Message,
              "Fix_all_detected_spelling_errors_95026",
              "Fix all detected spelling errors");
};
static shared_ptr<DiagnosticMessage>
Add_initializers_to_all_uninitialized_properties() {
  return diag(95027, DiagnosticCategory::Message,
              "Add_initializers_to_all_uninitialized_properties_95027",
              "Add initializers to all uninitialized properties");
};
static shared_ptr<DiagnosticMessage>
Add_definite_assignment_assertions_to_all_uninitialized_properties() {
  return diag(
      95028, DiagnosticCategory::Message,
      "Add_definite_assignment_assertions_to_all_uninitialized_properties_"
      "95028",
      "Add definite assignment assertions to all uninitialized properties");
};
static shared_ptr<DiagnosticMessage>
Add_undefined_type_to_all_uninitialized_properties() {
  return diag(95029, DiagnosticCategory::Message,
              "Add_undefined_type_to_all_uninitialized_properties_95029",
              "Add undefined type to all uninitialized properties");
};
static shared_ptr<DiagnosticMessage>
Change_all_jsdoc_style_types_to_TypeScript() {
  return diag(95030, DiagnosticCategory::Message,
              "Change_all_jsdoc_style_types_to_TypeScript_95030",
              "Change all jsdoc-style types to TypeScript");
};
static shared_ptr<DiagnosticMessage>
Change_all_jsdoc_style_types_to_TypeScript_and_add_undefined_to_nullable_types() {
  return diag(95031, DiagnosticCategory::Message,
              "Change_all_jsdoc_style_types_to_TypeScript_and_add_undefined_to_"
              "nullable_types_95031",
              "Change all jsdoc-style types to TypeScript (and add '| "
              "undefined' to nullable types)");
};
static shared_ptr<DiagnosticMessage> Implement_all_unimplemented_interfaces() {
  return diag(95032, DiagnosticCategory::Message,
              "Implement_all_unimplemented_interfaces_95032",
              "Implement all unimplemented interfaces");
};
static shared_ptr<DiagnosticMessage> Install_all_missing_types_packages() {
  return diag(95033, DiagnosticCategory::Message,
              "Install_all_missing_types_packages_95033",
              "Install all missing types packages");
};
static shared_ptr<DiagnosticMessage> Rewrite_all_as_indexed_access_types() {
  return diag(95034, DiagnosticCategory::Message,
              "Rewrite_all_as_indexed_access_types_95034",
              "Rewrite all as indexed access types");
};
static shared_ptr<DiagnosticMessage> Convert_all_to_default_imports() {
  return diag(95035, DiagnosticCategory::Message,
              "Convert_all_to_default_imports_95035",
              "Convert all to default imports");
};
static shared_ptr<DiagnosticMessage>
Make_all_super_calls_the_first_statement_in_their_constructor() {
  return diag(
      95036, DiagnosticCategory::Message,
      "Make_all_super_calls_the_first_statement_in_their_constructor_95036",
      "Make all 'super()' calls the first statement in their constructor");
};
static shared_ptr<DiagnosticMessage>
Add_qualifier_to_all_unresolved_variables_matching_a_member_name() {
  return diag(
      95037, DiagnosticCategory::Message,
      "Add_qualifier_to_all_unresolved_variables_matching_a_member_name_95037",
      "Add qualifier to all unresolved variables matching a member name");
};
static shared_ptr<DiagnosticMessage>
Change_all_extended_interfaces_to_implements() {
  return diag(95038, DiagnosticCategory::Message,
              "Change_all_extended_interfaces_to_implements_95038",
              "Change all extended interfaces to 'implements'");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_super_calls() {
  return diag(95039, DiagnosticCategory::Message,
              "Add_all_missing_super_calls_95039",
              "Add all missing super calls");
};
static shared_ptr<DiagnosticMessage>
Implement_all_inherited_abstract_classes() {
  return diag(95040, DiagnosticCategory::Message,
              "Implement_all_inherited_abstract_classes_95040",
              "Implement all inherited abstract classes");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_async_modifiers() {
  return diag(95041, DiagnosticCategory::Message,
              "Add_all_missing_async_modifiers_95041",
              "Add all missing 'async' modifiers");
};
static shared_ptr<DiagnosticMessage> Add_ts_ignore_to_all_error_messages() {
  return diag(95042, DiagnosticCategory::Message,
              "Add_ts_ignore_to_all_error_messages_95042",
              "Add '@ts-ignore' to all error messages");
};
static shared_ptr<DiagnosticMessage>
Annotate_everything_with_types_from_JSDoc() {
  return diag(95043, DiagnosticCategory::Message,
              "Annotate_everything_with_types_from_JSDoc_95043",
              "Annotate everything with types from JSDoc");
};
static shared_ptr<DiagnosticMessage> Add_to_all_uncalled_decorators() {
  return diag(95044, DiagnosticCategory::Message,
              "Add_to_all_uncalled_decorators_95044",
              "Add '()' to all uncalled decorators");
};
static shared_ptr<DiagnosticMessage>
Convert_all_constructor_functions_to_classes() {
  return diag(95045, DiagnosticCategory::Message,
              "Convert_all_constructor_functions_to_classes_95045",
              "Convert all constructor functions to classes");
};
static shared_ptr<DiagnosticMessage> Generate_get_and_set_accessors() {
  return diag(95046, DiagnosticCategory::Message,
              "Generate_get_and_set_accessors_95046",
              "Generate 'get' and 'set' accessors");
};
static shared_ptr<DiagnosticMessage> Convert_require_to_import() {
  return diag(95047, DiagnosticCategory::Message,
              "Convert_require_to_import_95047",
              "Convert 'require' to 'import'");
};
static shared_ptr<DiagnosticMessage> Convert_all_require_to_import() {
  return diag(95048, DiagnosticCategory::Message,
              "Convert_all_require_to_import_95048",
              "Convert all 'require' to 'import'");
};
static shared_ptr<DiagnosticMessage> Move_to_a_new_file() {
  return diag(95049, DiagnosticCategory::Message, "Move_to_a_new_file_95049",
              "Move to a new file");
};
static shared_ptr<DiagnosticMessage> Remove_unreachable_code() {
  return diag(95050, DiagnosticCategory::Message,
              "Remove_unreachable_code_95050", "Remove unreachable code");
};
static shared_ptr<DiagnosticMessage> Remove_all_unreachable_code() {
  return diag(95051, DiagnosticCategory::Message,
              "Remove_all_unreachable_code_95051",
              "Remove all unreachable code");
};
static shared_ptr<DiagnosticMessage> Add_missing_typeof() {
  return diag(95052, DiagnosticCategory::Message, "Add_missing_typeof_95052",
              "Add missing 'typeof'");
};
static shared_ptr<DiagnosticMessage> Remove_unused_label() {
  return diag(95053, DiagnosticCategory::Message, "Remove_unused_label_95053",
              "Remove unused label");
};
static shared_ptr<DiagnosticMessage> Remove_all_unused_labels() {
  return diag(95054, DiagnosticCategory::Message,
              "Remove_all_unused_labels_95054", "Remove all unused labels");
};
static shared_ptr<DiagnosticMessage> Convert_0_to_mapped_object_type() {
  return diag(95055, DiagnosticCategory::Message,
              "Convert_0_to_mapped_object_type_95055",
              "Convert '{0}' to mapped object type");
};
static shared_ptr<DiagnosticMessage>
Convert_namespace_import_to_named_imports() {
  return diag(95056, DiagnosticCategory::Message,
              "Convert_namespace_import_to_named_imports_95056",
              "Convert namespace import to named imports");
};
static shared_ptr<DiagnosticMessage>
Convert_named_imports_to_namespace_import() {
  return diag(95057, DiagnosticCategory::Message,
              "Convert_named_imports_to_namespace_import_95057",
              "Convert named imports to namespace import");
};
static shared_ptr<DiagnosticMessage>
Add_or_remove_braces_in_an_arrow_function() {
  return diag(95058, DiagnosticCategory::Message,
              "Add_or_remove_braces_in_an_arrow_function_95058",
              "Add or remove braces in an arrow function");
};
static shared_ptr<DiagnosticMessage> Add_braces_to_arrow_function() {
  return diag(95059, DiagnosticCategory::Message,
              "Add_braces_to_arrow_function_95059",
              "Add braces to arrow function");
};
static shared_ptr<DiagnosticMessage> Remove_braces_from_arrow_function() {
  return diag(95060, DiagnosticCategory::Message,
              "Remove_braces_from_arrow_function_95060",
              "Remove braces from arrow function");
};
static shared_ptr<DiagnosticMessage> Convert_default_export_to_named_export() {
  return diag(95061, DiagnosticCategory::Message,
              "Convert_default_export_to_named_export_95061",
              "Convert default export to named export");
};
static shared_ptr<DiagnosticMessage> Convert_named_export_to_default_export() {
  return diag(95062, DiagnosticCategory::Message,
              "Convert_named_export_to_default_export_95062",
              "Convert named export to default export");
};
static shared_ptr<DiagnosticMessage> Add_missing_enum_member_0() {
  return diag(95063, DiagnosticCategory::Message,
              "Add_missing_enum_member_0_95063",
              "Add missing enum member '{0}'");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_imports() {
  return diag(95064, DiagnosticCategory::Message,
              "Add_all_missing_imports_95064", "Add all missing imports");
};
static shared_ptr<DiagnosticMessage> Convert_to_async_function() {
  return diag(95065, DiagnosticCategory::Message,
              "Convert_to_async_function_95065", "Convert to async function");
};
static shared_ptr<DiagnosticMessage> Convert_all_to_async_functions() {
  return diag(95066, DiagnosticCategory::Message,
              "Convert_all_to_async_functions_95066",
              "Convert all to async functions");
};
static shared_ptr<DiagnosticMessage> Add_missing_call_parentheses() {
  return diag(95067, DiagnosticCategory::Message,
              "Add_missing_call_parentheses_95067",
              "Add missing call parentheses");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_call_parentheses() {
  return diag(95068, DiagnosticCategory::Message,
              "Add_all_missing_call_parentheses_95068",
              "Add all missing call parentheses");
};
static shared_ptr<DiagnosticMessage>
Add_unknown_conversion_for_non_overlapping_types() {
  return diag(95069, DiagnosticCategory::Message,
              "Add_unknown_conversion_for_non_overlapping_types_95069",
              "Add 'unknown' conversion for non-overlapping types");
};
static shared_ptr<DiagnosticMessage>
Add_unknown_to_all_conversions_of_non_overlapping_types() {
  return diag(95070, DiagnosticCategory::Message,
              "Add_unknown_to_all_conversions_of_non_overlapping_types_95070",
              "Add 'unknown' to all conversions of non-overlapping types");
};
static shared_ptr<DiagnosticMessage> Add_missing_new_operator_to_call() {
  return diag(95071, DiagnosticCategory::Message,
              "Add_missing_new_operator_to_call_95071",
              "Add missing 'new' operator to call");
};
static shared_ptr<DiagnosticMessage> Add_missing_new_operator_to_all_calls() {
  return diag(95072, DiagnosticCategory::Message,
              "Add_missing_new_operator_to_all_calls_95072",
              "Add missing 'new' operator to all calls");
};
static shared_ptr<DiagnosticMessage>
Add_names_to_all_parameters_without_names() {
  return diag(95073, DiagnosticCategory::Message,
              "Add_names_to_all_parameters_without_names_95073",
              "Add names to all parameters without names");
};
static shared_ptr<DiagnosticMessage>
Enable_the_experimentalDecorators_option_in_your_configuration_file() {
  return diag(
      95074, DiagnosticCategory::Message,
      "Enable_the_experimentalDecorators_option_in_your_configuration_file_"
      "95074",
      "Enable the 'experimentalDecorators' option in your configuration file");
};
static shared_ptr<DiagnosticMessage>
Convert_parameters_to_destructured_object() {
  return diag(95075, DiagnosticCategory::Message,
              "Convert_parameters_to_destructured_object_95075",
              "Convert parameters to destructured object");
};
static shared_ptr<DiagnosticMessage> Extract_type() {
  return diag(95077, DiagnosticCategory::Message, "Extract_type_95077",
              "Extract type");
};
static shared_ptr<DiagnosticMessage> Extract_to_type_alias() {
  return diag(95078, DiagnosticCategory::Message, "Extract_to_type_alias_95078",
              "Extract to type alias");
};
static shared_ptr<DiagnosticMessage> Extract_to_typedef() {
  return diag(95079, DiagnosticCategory::Message, "Extract_to_typedef_95079",
              "Extract to typedef");
};
static shared_ptr<DiagnosticMessage> Infer_this_type_of_0_from_usage() {
  return diag(95080, DiagnosticCategory::Message,
              "Infer_this_type_of_0_from_usage_95080",
              "Infer 'this' type of '{0}' from usage");
};
static shared_ptr<DiagnosticMessage> Add_const_to_unresolved_variable() {
  return diag(95081, DiagnosticCategory::Message,
              "Add_const_to_unresolved_variable_95081",
              "Add 'const' to unresolved variable");
};
static shared_ptr<DiagnosticMessage> Add_const_to_all_unresolved_variables() {
  return diag(95082, DiagnosticCategory::Message,
              "Add_const_to_all_unresolved_variables_95082",
              "Add 'const' to all unresolved variables");
};
static shared_ptr<DiagnosticMessage> Add_await() {
  return diag(95083, DiagnosticCategory::Message, "Add_await_95083",
              "Add 'await'");
};
static shared_ptr<DiagnosticMessage> Add_await_to_initializer_for_0() {
  return diag(95084, DiagnosticCategory::Message,
              "Add_await_to_initializer_for_0_95084",
              "Add 'await' to initializer for '{0}'");
};
static shared_ptr<DiagnosticMessage>
Fix_all_expressions_possibly_missing_await() {
  return diag(95085, DiagnosticCategory::Message,
              "Fix_all_expressions_possibly_missing_await_95085",
              "Fix all expressions possibly missing 'await'");
};
static shared_ptr<DiagnosticMessage> Remove_unnecessary_await() {
  return diag(95086, DiagnosticCategory::Message,
              "Remove_unnecessary_await_95086", "Remove unnecessary 'await'");
};
static shared_ptr<DiagnosticMessage> Remove_all_unnecessary_uses_of_await() {
  return diag(95087, DiagnosticCategory::Message,
              "Remove_all_unnecessary_uses_of_await_95087",
              "Remove all unnecessary uses of 'await'");
};
static shared_ptr<DiagnosticMessage>
Enable_the_jsx_flag_in_your_configuration_file() {
  return diag(95088, DiagnosticCategory::Message,
              "Enable_the_jsx_flag_in_your_configuration_file_95088",
              "Enable the '--jsx' flag in your configuration file");
};
static shared_ptr<DiagnosticMessage> Add_await_to_initializers() {
  return diag(95089, DiagnosticCategory::Message,
              "Add_await_to_initializers_95089", "Add 'await' to initializers");
};
static shared_ptr<DiagnosticMessage> Extract_to_interface() {
  return diag(95090, DiagnosticCategory::Message, "Extract_to_interface_95090",
              "Extract to interface");
};
static shared_ptr<DiagnosticMessage> Convert_to_a_bigint_numeric_literal() {
  return diag(95091, DiagnosticCategory::Message,
              "Convert_to_a_bigint_numeric_literal_95091",
              "Convert to a bigint numeric literal");
};
static shared_ptr<DiagnosticMessage> Convert_all_to_bigint_numeric_literals() {
  return diag(95092, DiagnosticCategory::Message,
              "Convert_all_to_bigint_numeric_literals_95092",
              "Convert all to bigint numeric literals");
};
static shared_ptr<DiagnosticMessage> Convert_const_to_let() {
  return diag(95093, DiagnosticCategory::Message, "Convert_const_to_let_95093",
              "Convert 'const' to 'let'");
};
static shared_ptr<DiagnosticMessage> Prefix_with_declare() {
  return diag(95094, DiagnosticCategory::Message, "Prefix_with_declare_95094",
              "Prefix with 'declare'");
};
static shared_ptr<DiagnosticMessage>
Prefix_all_incorrect_property_declarations_with_declare() {
  return diag(95095, DiagnosticCategory::Message,
              "Prefix_all_incorrect_property_declarations_with_declare_95095",
              "Prefix all incorrect property declarations with 'declare'");
};
static shared_ptr<DiagnosticMessage> Convert_to_template_string() {
  return diag(95096, DiagnosticCategory::Message,
              "Convert_to_template_string_95096", "Convert to template string");
};
static shared_ptr<DiagnosticMessage>
Add_export_to_make_this_file_into_a_module() {
  return diag(95097, DiagnosticCategory::Message,
              "Add_export_to_make_this_file_into_a_module_95097",
              "Add 'export {}' to make this file into a module");
};
static shared_ptr<DiagnosticMessage>
Set_the_target_option_in_your_configuration_file_to_0() {
  return diag(95098, DiagnosticCategory::Message,
              "Set_the_target_option_in_your_configuration_file_to_0_95098",
              "Set the 'target' option in your configuration file to '{0}'");
};
static shared_ptr<DiagnosticMessage>
Set_the_module_option_in_your_configuration_file_to_0() {
  return diag(95099, DiagnosticCategory::Message,
              "Set_the_module_option_in_your_configuration_file_to_0_95099",
              "Set the 'module' option in your configuration file to '{0}'");
};
static shared_ptr<DiagnosticMessage>
Convert_invalid_character_to_its_html_entity_code() {
  return diag(95100, DiagnosticCategory::Message,
              "Convert_invalid_character_to_its_html_entity_code_95100",
              "Convert invalid character to its html entity code");
};
static shared_ptr<DiagnosticMessage>
Convert_all_invalid_characters_to_HTML_entity_code() {
  return diag(95101, DiagnosticCategory::Message,
              "Convert_all_invalid_characters_to_HTML_entity_code_95101",
              "Convert all invalid characters to HTML entity code");
};
static shared_ptr<DiagnosticMessage>
Convert_function_expression_0_to_arrow_function() {
  return diag(95105, DiagnosticCategory::Message,
              "Convert_function_expression_0_to_arrow_function_95105",
              "Convert function expression '{0}' to arrow function");
};
static shared_ptr<DiagnosticMessage>
Convert_function_declaration_0_to_arrow_function() {
  return diag(95106, DiagnosticCategory::Message,
              "Convert_function_declaration_0_to_arrow_function_95106",
              "Convert function declaration '{0}' to arrow function");
};
static shared_ptr<DiagnosticMessage> Fix_all_implicit_this_errors() {
  return diag(95107, DiagnosticCategory::Message,
              "Fix_all_implicit_this_errors_95107",
              "Fix all implicit-'this' errors");
};
static shared_ptr<DiagnosticMessage>
Wrap_invalid_character_in_an_expression_container() {
  return diag(95108, DiagnosticCategory::Message,
              "Wrap_invalid_character_in_an_expression_container_95108",
              "Wrap invalid character in an expression container");
};
static shared_ptr<DiagnosticMessage>
Wrap_all_invalid_characters_in_an_expression_container() {
  return diag(95109, DiagnosticCategory::Message,
              "Wrap_all_invalid_characters_in_an_expression_container_95109",
              "Wrap all invalid characters in an expression container");
};
static shared_ptr<DiagnosticMessage>
Visit_https_Colon_Slash_Slashaka_ms_Slashtsconfig_json_to_read_more_about_this_file() {
  return diag(
      95110, DiagnosticCategory::Message,
      "Visit_https_Colon_Slash_Slashaka_ms_Slashtsconfig_json_to_read_more_"
      "about_this_file_95110",
      "Visit https://aka.ms/tsconfig.json to read more about this file");
};
static shared_ptr<DiagnosticMessage> Add_a_return_statement() {
  return diag(95111, DiagnosticCategory::Message,
              "Add_a_return_statement_95111", "Add a return statement");
};
static shared_ptr<DiagnosticMessage> Remove_braces_from_arrow_function_body() {
  return diag(95112, DiagnosticCategory::Message,
              "Remove_braces_from_arrow_function_body_95112",
              "Remove braces from arrow function body");
};
static shared_ptr<DiagnosticMessage>
Wrap_the_following_body_with_parentheses_which_should_be_an_object_literal() {
  return diag(95113, DiagnosticCategory::Message,
              "Wrap_the_following_body_with_parentheses_which_should_be_an_"
              "object_literal_95113",
              "Wrap the following body with parentheses which should be an "
              "object literal");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_return_statement() {
  return diag(95114, DiagnosticCategory::Message,
              "Add_all_missing_return_statement_95114",
              "Add all missing return statement");
};
static shared_ptr<DiagnosticMessage>
Remove_braces_from_all_arrow_function_bodies_with_relevant_issues() {
  return diag(
      95115, DiagnosticCategory::Message,
      "Remove_braces_from_all_arrow_function_bodies_with_relevant_issues_95115",
      "Remove braces from all arrow function bodies with relevant issues");
};
static shared_ptr<DiagnosticMessage>
Wrap_all_object_literal_with_parentheses() {
  return diag(95116, DiagnosticCategory::Message,
              "Wrap_all_object_literal_with_parentheses_95116",
              "Wrap all object literal with parentheses");
};
static shared_ptr<DiagnosticMessage>
Move_labeled_tuple_element_modifiers_to_labels() {
  return diag(95117, DiagnosticCategory::Message,
              "Move_labeled_tuple_element_modifiers_to_labels_95117",
              "Move labeled tuple element modifiers to labels");
};
static shared_ptr<DiagnosticMessage>
Convert_overload_list_to_single_signature() {
  return diag(95118, DiagnosticCategory::Message,
              "Convert_overload_list_to_single_signature_95118",
              "Convert overload list to single signature");
};
static shared_ptr<DiagnosticMessage>
Generate_get_and_set_accessors_for_all_overriding_properties() {
  return diag(
      95119, DiagnosticCategory::Message,
      "Generate_get_and_set_accessors_for_all_overriding_properties_95119",
      "Generate 'get' and 'set' accessors for all overriding properties");
};
static shared_ptr<DiagnosticMessage> Wrap_in_JSX_fragment() {
  return diag(95120, DiagnosticCategory::Message, "Wrap_in_JSX_fragment_95120",
              "Wrap in JSX fragment");
};
static shared_ptr<DiagnosticMessage> Wrap_all_unparented_JSX_in_JSX_fragment() {
  return diag(95121, DiagnosticCategory::Message,
              "Wrap_all_unparented_JSX_in_JSX_fragment_95121",
              "Wrap all unparented JSX in JSX fragment");
};
static shared_ptr<DiagnosticMessage>
Convert_arrow_function_or_function_expression() {
  return diag(95122, DiagnosticCategory::Message,
              "Convert_arrow_function_or_function_expression_95122",
              "Convert arrow function or function expression");
};
static shared_ptr<DiagnosticMessage> Convert_to_anonymous_function() {
  return diag(95123, DiagnosticCategory::Message,
              "Convert_to_anonymous_function_95123",
              "Convert to anonymous function");
};
static shared_ptr<DiagnosticMessage> Convert_to_named_function() {
  return diag(95124, DiagnosticCategory::Message,
              "Convert_to_named_function_95124", "Convert to named function");
};
static shared_ptr<DiagnosticMessage> Convert_to_arrow_function() {
  return diag(95125, DiagnosticCategory::Message,
              "Convert_to_arrow_function_95125", "Convert to arrow function");
};
static shared_ptr<DiagnosticMessage> Remove_parentheses() {
  return diag(95126, DiagnosticCategory::Message, "Remove_parentheses_95126",
              "Remove parentheses");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_a_containing_arrow_function() {
  return diag(95127, DiagnosticCategory::Message,
              "Could_not_find_a_containing_arrow_function_95127",
              "Could not find a containing arrow function");
};
static shared_ptr<DiagnosticMessage>
Containing_function_is_not_an_arrow_function() {
  return diag(95128, DiagnosticCategory::Message,
              "Containing_function_is_not_an_arrow_function_95128",
              "Containing function is not an arrow function");
};
static shared_ptr<DiagnosticMessage> Could_not_find_export_statement() {
  return diag(95129, DiagnosticCategory::Message,
              "Could_not_find_export_statement_95129",
              "Could not find export statement");
};
static shared_ptr<DiagnosticMessage> This_file_already_has_a_default_export() {
  return diag(95130, DiagnosticCategory::Message,
              "This_file_already_has_a_default_export_95130",
              "This file already has a default export");
};
static shared_ptr<DiagnosticMessage> Could_not_find_import_clause() {
  return diag(95131, DiagnosticCategory::Message,
              "Could_not_find_import_clause_95131",
              "Could not find import clause");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_namespace_import_or_named_imports() {
  return diag(95132, DiagnosticCategory::Message,
              "Could_not_find_namespace_import_or_named_imports_95132",
              "Could not find namespace import or named imports");
};
static shared_ptr<DiagnosticMessage> Selection_is_not_a_valid_type_node() {
  return diag(95133, DiagnosticCategory::Message,
              "Selection_is_not_a_valid_type_node_95133",
              "Selection is not a valid type node");
};
static shared_ptr<DiagnosticMessage>
No_type_could_be_extracted_from_this_type_node() {
  return diag(95134, DiagnosticCategory::Message,
              "No_type_could_be_extracted_from_this_type_node_95134",
              "No type could be extracted from this type node");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_property_for_which_to_generate_accessor() {
  return diag(95135, DiagnosticCategory::Message,
              "Could_not_find_property_for_which_to_generate_accessor_95135",
              "Could not find property for which to generate accessor");
};
static shared_ptr<DiagnosticMessage> Name_is_not_valid() {
  return diag(95136, DiagnosticCategory::Message, "Name_is_not_valid_95136",
              "Name is not valid");
};
static shared_ptr<DiagnosticMessage> Can_only_convert_property_with_modifier() {
  return diag(95137, DiagnosticCategory::Message,
              "Can_only_convert_property_with_modifier_95137",
              "Can only convert property with modifier");
};
static shared_ptr<DiagnosticMessage> Switch_each_misused_0_to_1() {
  return diag(95138, DiagnosticCategory::Message,
              "Switch_each_misused_0_to_1_95138",
              "Switch each misused '{0}' to '{1}'");
};
static shared_ptr<DiagnosticMessage> Convert_to_optional_chain_expression() {
  return diag(95139, DiagnosticCategory::Message,
              "Convert_to_optional_chain_expression_95139",
              "Convert to optional chain expression");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_convertible_access_expression() {
  return diag(95140, DiagnosticCategory::Message,
              "Could_not_find_convertible_access_expression_95140",
              "Could not find convertible access expression");
};
static shared_ptr<DiagnosticMessage>
Could_not_find_matching_access_expressions() {
  return diag(95141, DiagnosticCategory::Message,
              "Could_not_find_matching_access_expressions_95141",
              "Could not find matching access expressions");
};
static shared_ptr<DiagnosticMessage>
Can_only_convert_logical_AND_access_chains() {
  return diag(95142, DiagnosticCategory::Message,
              "Can_only_convert_logical_AND_access_chains_95142",
              "Can only convert logical AND access chains");
};
static shared_ptr<DiagnosticMessage>
Add_void_to_Promise_resolved_without_a_value() {
  return diag(95143, DiagnosticCategory::Message,
              "Add_void_to_Promise_resolved_without_a_value_95143",
              "Add 'void' to Promise resolved without a value");
};
static shared_ptr<DiagnosticMessage>
Add_void_to_all_Promises_resolved_without_a_value() {
  return diag(95144, DiagnosticCategory::Message,
              "Add_void_to_all_Promises_resolved_without_a_value_95144",
              "Add 'void' to all Promises resolved without a value");
};
static shared_ptr<DiagnosticMessage> Use_element_access_for_0() {
  return diag(95145, DiagnosticCategory::Message,
              "Use_element_access_for_0_95145", "Use element access for '{0}'");
};
static shared_ptr<DiagnosticMessage>
Use_element_access_for_all_undeclared_properties() {
  return diag(95146, DiagnosticCategory::Message,
              "Use_element_access_for_all_undeclared_properties_95146",
              "Use element access for all undeclared properties.");
};
static shared_ptr<DiagnosticMessage> Delete_all_unused_imports() {
  return diag(95147, DiagnosticCategory::Message,
              "Delete_all_unused_imports_95147", "Delete all unused imports");
};
static shared_ptr<DiagnosticMessage> Infer_function_return_type() {
  return diag(95148, DiagnosticCategory::Message,
              "Infer_function_return_type_95148", "Infer function return type");
};
static shared_ptr<DiagnosticMessage>
Return_type_must_be_inferred_from_a_function() {
  return diag(95149, DiagnosticCategory::Message,
              "Return_type_must_be_inferred_from_a_function_95149",
              "Return type must be inferred from a function");
};
static shared_ptr<DiagnosticMessage>
Could_not_determine_function_return_type() {
  return diag(95150, DiagnosticCategory::Message,
              "Could_not_determine_function_return_type_95150",
              "Could not determine function return type");
};
static shared_ptr<DiagnosticMessage> Could_not_convert_to_arrow_function() {
  return diag(95151, DiagnosticCategory::Message,
              "Could_not_convert_to_arrow_function_95151",
              "Could not convert to arrow function");
};
static shared_ptr<DiagnosticMessage> Could_not_convert_to_named_function() {
  return diag(95152, DiagnosticCategory::Message,
              "Could_not_convert_to_named_function_95152",
              "Could not convert to named function");
};
static shared_ptr<DiagnosticMessage> Could_not_convert_to_anonymous_function() {
  return diag(95153, DiagnosticCategory::Message,
              "Could_not_convert_to_anonymous_function_95153",
              "Could not convert to anonymous function");
};
static shared_ptr<DiagnosticMessage> Can_only_convert_string_concatenation() {
  return diag(95154, DiagnosticCategory::Message,
              "Can_only_convert_string_concatenation_95154",
              "Can only convert string concatenation");
};
static shared_ptr<DiagnosticMessage>
Selection_is_not_a_valid_statement_or_statements() {
  return diag(95155, DiagnosticCategory::Message,
              "Selection_is_not_a_valid_statement_or_statements_95155",
              "Selection is not a valid statement or statements");
};
static shared_ptr<DiagnosticMessage> Add_missing_function_declaration_0() {
  return diag(95156, DiagnosticCategory::Message,
              "Add_missing_function_declaration_0_95156",
              "Add missing function declaration '{0}'");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_function_declarations() {
  return diag(95157, DiagnosticCategory::Message,
              "Add_all_missing_function_declarations_95157",
              "Add all missing function declarations");
};
static shared_ptr<DiagnosticMessage> Method_not_implemented() {
  return diag(95158, DiagnosticCategory::Message,
              "Method_not_implemented_95158", "Method not implemented.");
};
static shared_ptr<DiagnosticMessage> Function_not_implemented() {
  return diag(95159, DiagnosticCategory::Message,
              "Function_not_implemented_95159", "Function not implemented.");
};
static shared_ptr<DiagnosticMessage> Add_override_modifier() {
  return diag(95160, DiagnosticCategory::Message, "Add_override_modifier_95160",
              "Add 'override' modifier");
};
static shared_ptr<DiagnosticMessage> Remove_override_modifier() {
  return diag(95161, DiagnosticCategory::Message,
              "Remove_override_modifier_95161", "Remove 'override' modifier");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_override_modifiers() {
  return diag(95162, DiagnosticCategory::Message,
              "Add_all_missing_override_modifiers_95162",
              "Add all missing 'override' modifiers");
};
static shared_ptr<DiagnosticMessage>
Remove_all_unnecessary_override_modifiers() {
  return diag(95163, DiagnosticCategory::Message,
              "Remove_all_unnecessary_override_modifiers_95163",
              "Remove all unnecessary 'override' modifiers");
};
static shared_ptr<DiagnosticMessage> Can_only_convert_named_export() {
  return diag(95164, DiagnosticCategory::Message,
              "Can_only_convert_named_export_95164",
              "Can only convert named export");
};
static shared_ptr<DiagnosticMessage> Add_missing_properties() {
  return diag(95165, DiagnosticCategory::Message,
              "Add_missing_properties_95165", "Add missing properties");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_properties() {
  return diag(95166, DiagnosticCategory::Message,
              "Add_all_missing_properties_95166", "Add all missing properties");
};
static shared_ptr<DiagnosticMessage> Add_missing_attributes() {
  return diag(95167, DiagnosticCategory::Message,
              "Add_missing_attributes_95167", "Add missing attributes");
};
static shared_ptr<DiagnosticMessage> Add_all_missing_attributes() {
  return diag(95168, DiagnosticCategory::Message,
              "Add_all_missing_attributes_95168", "Add all missing attributes");
};
static shared_ptr<DiagnosticMessage> Add_undefined_to_optional_property_type() {
  return diag(95169, DiagnosticCategory::Message,
              "Add_undefined_to_optional_property_type_95169",
              "Add 'undefined' to optional property type");
};
static shared_ptr<DiagnosticMessage>
No_value_exists_in_scope_for_the_shorthand_property_0_Either_declare_one_or_provide_an_initializer() {
  return diag(18004, DiagnosticCategory::Error,
              "No_value_exists_in_scope_for_the_shorthand_property_0_Either_"
              "declare_one_or_provide_an_initializer_18004",
              "No value exists in scope for the shorthand property '{0}'. "
              "Either declare one or provide an initializer.");
};
static shared_ptr<DiagnosticMessage>
Classes_may_not_have_a_field_named_constructor() {
  return diag(18006, DiagnosticCategory::Error,
              "Classes_may_not_have_a_field_named_constructor_18006",
              "Classes may not have a field named 'constructor'.");
};
static shared_ptr<DiagnosticMessage>
JSX_expressions_may_not_use_the_comma_operator_Did_you_mean_to_write_an_array() {
  return diag(18007, DiagnosticCategory::Error,
              "JSX_expressions_may_not_use_the_comma_operator_Did_you_mean_to_"
              "write_an_array_18007",
              "JSX expressions may not use the comma operator. Did you mean to "
              "write an array?");
};
static shared_ptr<DiagnosticMessage>
Private_identifiers_cannot_be_used_as_parameters() {
  return diag(18009, DiagnosticCategory::Error,
              "Private_identifiers_cannot_be_used_as_parameters_18009",
              "Private identifiers cannot be used as parameters.");
};
static shared_ptr<DiagnosticMessage>
An_accessibility_modifier_cannot_be_used_with_a_private_identifier() {
  return diag(
      18010, DiagnosticCategory::Error,
      "An_accessibility_modifier_cannot_be_used_with_a_private_identifier_"
      "18010",
      "An accessibility modifier cannot be used with a private identifier.");
};
static shared_ptr<DiagnosticMessage>
The_operand_of_a_delete_operator_cannot_be_a_private_identifier() {
  return diag(
      18011, DiagnosticCategory::Error,
      "The_operand_of_a_delete_operator_cannot_be_a_private_identifier_18011",
      "The operand of a 'delete' operator cannot be a private identifier.");
};
static shared_ptr<DiagnosticMessage> constructor_is_a_reserved_word() {
  return diag(18012, DiagnosticCategory::Error,
              "constructor_is_a_reserved_word_18012",
              "'#constructor' is a reserved word.");
};
static shared_ptr<DiagnosticMessage>
Property_0_is_not_accessible_outside_class_1_because_it_has_a_private_identifier() {
  return diag(18013, DiagnosticCategory::Error,
              "Property_0_is_not_accessible_outside_class_1_because_it_has_a_"
              "private_identifier_18013",
              "Property '{0}' is not accessible outside class '{1}' because it "
              "has a private identifier.");
};
static shared_ptr<DiagnosticMessage>
The_property_0_cannot_be_accessed_on_type_1_within_this_class_because_it_is_shadowed_by_another_private_identifier_with_the_same_spelling() {
  return diag(18014, DiagnosticCategory::Error,
              "The_property_0_cannot_be_accessed_on_type_1_within_this_class_"
              "because_it_is_shadowed_by_another_priv_18014",
              "The property '{0}' cannot be accessed on type '{1}' within this "
              "class because it is shadowed by another private identifier with "
              "the same spelling.");
};
static shared_ptr<DiagnosticMessage>
Property_0_in_type_1_refers_to_a_different_member_that_cannot_be_accessed_from_within_type_2() {
  return diag(18015, DiagnosticCategory::Error,
              "Property_0_in_type_1_refers_to_a_different_member_that_cannot_"
              "be_accessed_from_within_type_2_18015",
              "Property '{0}' in type '{1}' refers to a different member that "
              "cannot be accessed from within type '{2}'.");
};
static shared_ptr<DiagnosticMessage>
Private_identifiers_are_not_allowed_outside_class_bodies() {
  return diag(18016, DiagnosticCategory::Error,
              "Private_identifiers_are_not_allowed_outside_class_bodies_18016",
              "Private identifiers are not allowed outside class bodies.");
};
static shared_ptr<DiagnosticMessage>
The_shadowing_declaration_of_0_is_defined_here() {
  return diag(18017, DiagnosticCategory::Error,
              "The_shadowing_declaration_of_0_is_defined_here_18017",
              "The shadowing declaration of '{0}' is defined here");
};
static shared_ptr<DiagnosticMessage>
The_declaration_of_0_that_you_probably_intended_to_use_is_defined_here() {
  return diag(18018, DiagnosticCategory::Error,
              "The_declaration_of_0_that_you_probably_intended_to_use_is_"
              "defined_here_18018",
              "The declaration of '{0}' that you probably intended to use is "
              "defined here");
};
static shared_ptr<DiagnosticMessage>
_0_modifier_cannot_be_used_with_a_private_identifier() {
  return diag(18019, DiagnosticCategory::Error,
              "_0_modifier_cannot_be_used_with_a_private_identifier_18019",
              "'{0}' modifier cannot be used with a private identifier.");
};
static shared_ptr<DiagnosticMessage>
An_enum_member_cannot_be_named_with_a_private_identifier() {
  return diag(18024, DiagnosticCategory::Error,
              "An_enum_member_cannot_be_named_with_a_private_identifier_18024",
              "An enum member cannot be named with a private identifier.");
};
static shared_ptr<DiagnosticMessage> can_only_be_used_at_the_start_of_a_file() {
  return diag(18026, DiagnosticCategory::Error,
              "can_only_be_used_at_the_start_of_a_file_18026",
              "'#!' can only be used at the start of a file.");
};
static shared_ptr<DiagnosticMessage>
Compiler_reserves_name_0_when_emitting_private_identifier_downlevel() {
  return diag(18027, DiagnosticCategory::Error,
              "Compiler_reserves_name_0_when_emitting_private_identifier_"
              "downlevel_18027",
              "Compiler reserves name '{0}' when emitting private identifier "
              "downlevel.");
};
static shared_ptr<DiagnosticMessage>
Private_identifiers_are_only_available_when_targeting_ECMAScript_2015_and_higher() {
  return diag(18028, DiagnosticCategory::Error,
              "Private_identifiers_are_only_available_when_targeting_"
              "ECMAScript_2015_and_higher_18028",
              "Private identifiers are only available when targeting "
              "ECMAScript 2015 and higher.");
};
static shared_ptr<DiagnosticMessage>
Private_identifiers_are_not_allowed_in_variable_declarations() {
  return diag(
      18029, DiagnosticCategory::Error,
      "Private_identifiers_are_not_allowed_in_variable_declarations_18029",
      "Private identifiers are not allowed in variable declarations.");
};
static shared_ptr<DiagnosticMessage>
An_optional_chain_cannot_contain_private_identifiers() {
  return diag(18030, DiagnosticCategory::Error,
              "An_optional_chain_cannot_contain_private_identifiers_18030",
              "An optional chain cannot contain private identifiers.");
};
static shared_ptr<DiagnosticMessage>
The_intersection_0_was_reduced_to_never_because_property_1_has_conflicting_types_in_some_constituents() {
  return diag(18031, DiagnosticCategory::Error,
              "The_intersection_0_was_reduced_to_never_because_property_1_has_"
              "conflicting_types_in_some_constituent_18031",
              "The intersection '{0}' was reduced to 'never' because property "
              "'{1}' has conflicting types in some constituents.");
};
static shared_ptr<DiagnosticMessage>
The_intersection_0_was_reduced_to_never_because_property_1_exists_in_multiple_constituents_and_is_private_in_some() {
  return diag(18032, DiagnosticCategory::Error,
              "The_intersection_0_was_reduced_to_never_because_property_1_"
              "exists_in_multiple_constituents_and_is_pr_18032",
              "The intersection '{0}' was reduced to 'never' because property "
              "'{1}' exists in multiple constituents and is private in some.");
};
static shared_ptr<DiagnosticMessage>
Only_numeric_enums_can_have_computed_members_but_this_expression_has_type_0_If_you_do_not_need_exhaustiveness_checks_consider_using_an_object_literal_instead() {
  return diag(18033, DiagnosticCategory::Error,
              "Only_numeric_enums_can_have_computed_members_but_this_"
              "expression_has_type_0_If_you_do_not_need_exhau_18033",
              "Only numeric enums can have computed members, but this "
              "expression has type '{0}'. If you do not need exhaustiveness "
              "checks, consider using an object literal instead.");
};
static shared_ptr<DiagnosticMessage>
Specify_the_JSX_fragment_factory_function_to_use_when_targeting_react_JSX_emit_with_jsxFactory_compiler_option_is_specified_e_g_Fragment() {
  return diag(18034, DiagnosticCategory::Message,
              "Specify_the_JSX_fragment_factory_function_to_use_when_targeting_"
              "react_JSX_emit_with_jsxFactory_compi_18034",
              "Specify the JSX fragment factory function to use when targeting "
              "'react' JSX emit with 'jsxFactory' compiler option is "
              "specified, e.g. 'Fragment'.");
};
static shared_ptr<DiagnosticMessage>
Invalid_value_for_jsxFragmentFactory_0_is_not_a_valid_identifier_or_qualified_name() {
  return diag(18035, DiagnosticCategory::Error,
              "Invalid_value_for_jsxFragmentFactory_0_is_not_a_valid_"
              "identifier_or_qualified_name_18035",
              "Invalid value for 'jsxFragmentFactory'. '{0}' is not a valid "
              "identifier or qualified-name.");
};
static shared_ptr<DiagnosticMessage>
Class_decorators_can_t_be_used_with_static_private_identifier_Consider_removing_the_experimental_decorator() {
  return diag(18036, DiagnosticCategory::Error,
              "Class_decorators_can_t_be_used_with_static_private_identifier_"
              "Consider_removing_the_experimental_dec_18036",
              "Class decorators can't be used with static private identifier. "
              "Consider removing the experimental decorator.");
};
static shared_ptr<DiagnosticMessage>
Await_expression_cannot_be_used_inside_a_class_static_block() {
  return diag(
      18037, DiagnosticCategory::Error,
      "Await_expression_cannot_be_used_inside_a_class_static_block_18037",
      "Await expression cannot be used inside a class static block.");
};
static shared_ptr<DiagnosticMessage>
For_await_loops_cannot_be_used_inside_a_class_static_block() {
  return diag(
      18038, DiagnosticCategory::Error,
      "For_await_loops_cannot_be_used_inside_a_class_static_block_18038",
      "'For await' loops cannot be used inside a class static block.");
};
static shared_ptr<DiagnosticMessage>
Invalid_use_of_0_It_cannot_be_used_inside_a_class_static_block() {
  return diag(
      18039, DiagnosticCategory::Error,
      "Invalid_use_of_0_It_cannot_be_used_inside_a_class_static_block_18039",
      "Invalid use of '{0}'. It cannot be used inside a class static block.");
};
static shared_ptr<DiagnosticMessage>
A_return_statement_cannot_be_used_inside_a_class_static_block() {
  return diag(
      18041, DiagnosticCategory::Error,
      "A_return_statement_cannot_be_used_inside_a_class_static_block_18041",
      "A 'return' statement cannot be used inside a class static block.");
};
};  // namespace Diagnostics
}  // namespace tscpp

#endif  // TSCPP_DIAGNOSTIC_DIAGNOSTIC_MESSAGE_H