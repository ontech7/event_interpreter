#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

const int DEBUG_MODE = TRUE;

const char* EOF_TYPE = "EOF";
const char* NOT_FOUND = "NOT_FOUND";

// Event types
const char* EVENT_TYPE = "event";
const char* NAME_TYPE = "name";
const char* DIALOG_TYPE = "dialog";
const char* OPTIONS_TYPE = "options";
const char* TEXT_TYPE = "text";
const char* SWITCH_TYPE = "switch";
const char* CASE_TYPE = "case";
const char* IF_TYPE = "if";
const char* ADDITEM_TYPE = "addItem";
const char* WAIT_TYPE = "wait";
const char* DECLARE_TYPE = "declare";
const char* FUNCTION_TYPE = "function";
const char* VARIABLE_TYPE = "variable";
const char* READ_TYPE = "read";
const char* SET_TYPE = "set";
const char* CALL_TYPE = "call";
const char* ADD_TYPE = "add";
const char* SUB_TYPE = "sub";
const char* EMPTY_TYPE = "";

// Special character check
const char IS_STRING = '"';
const char IS_COMMENT = '#';
const char IS_DELIMITER = ' ';
const char IS_VARIABLE = '$';
const char IS_SPECIAL_CHARACTER = '\\';
const char IS_ARRAY_OPEN = '[';
const char IS_ARRAY_CLOSED = ']';

// Conditional check
const char* EQUAL = "=";
const char* NOT_EQUAL = "!=";
const char* EQUAL_GREATER = ">=";
const char* EQUAL_LESS = "<=";
const char* GREATER = ">";
const char* LESS = "<";

// Value types
const char* STRING = "string";
const char* INTEGER = "integer";
const char* ARRAY = "array";

// Closure types
const char* ENDOPTIONS_TYPE = "endoptions";
const char* ENDCASE_TYPE = "endcase";
const char* ENDIF_TYPE = "endif";
const char* ENDSWITCH_TYPE = "endswitch";
const char* ENDDECLARE_TYPE = "enddeclare";
const char* ENDFUNCTION_TYPE = "endfunction";

// Logger Levels
const char* ERROR_LEVEL = "error";
const char* WARNING_LEVEL = "warning";
const char* TYPE_LEVEL = "type";
const char* VALUE_LEVEL = "value";
const char* UNKNOWN_LEVEL = "unknown";

// Error Messages
const char* COMMANDS_LENGTH_2 = "Too few arguments. Expected at least 2.";
const char* COMMANDS_LENGTH_3 = "Too few arguments. Expected at least 3.";
const char* COMMANDS_LENGTH_4 = "Too few arguments. Expected at least 4.";
const char* NOT_INSIDE_SWITCH = "'case' statement not inside 'switch'. Error occurred.";
const char* NOT_INSIDE_OPTIONS = "'text' statement not inside 'options'. Error occurred.";
const char* OPTIONS_NOT_FOUND = "'options' used in 'switch' not found. Error occurred.";
const char* UNKNOWN_COMMAND = "Unknown command. Check your code.";
const char* UNKNOWN_SYMBOL = "Unknown symbol. Check your code.";
const char* SECOND_ARGUMENT_EMPTY = "Second argument is empty. Check your code.";
const char* THIRD_ARGUMENT_EMPTY = "Third argument is empty. Check your code.";
const char* FOURTH_ARGUMENT_EMPTY = "Fourth argument is empty. Check your code.";
const char* NO_NESTED_FUNCTIONS = "Nested function detected. Error occurred.";
const char* FUNC_NOT_FOUND = "Function not found. Error occurred.";
const char* VAR_NOT_FOUND = "Variable not found. Error occurred.";
const char* FUNC_ALREADY_EXISTS = "Function declared already exists. Error occurred.";
const char* VAR_ALREADY_EXISTS = "Variable declared already exists. Error occurred.";
const char* STRING_TYPE_INVALID = "Type invalid. Variable is declared as 'string'. Error occurred.";
const char* DIFFERENT_TYPES = "The two compared values have different types. Error occurred.";
const char* WRONG_CLOSURE = "Wrong closure of the statement. Error occurred.";