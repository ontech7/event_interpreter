#include <stdio.h>
#include "flags.h"

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define TRUE 1
#define FALSE 0

extern const int DEBUG_MODE;
extern const char LOGGER_FLAGS;

extern const char* EOF_TYPE;
extern const char* NOT_FOUND;

// Event types
extern const char* EVENT_TYPE;
extern const char* NAME_TYPE;
extern const char* DIALOG_TYPE;
extern const char* OPTIONS_TYPE;
extern const char* TEXT_TYPE;
extern const char* SWITCH_TYPE;
extern const char* CASE_TYPE;
extern const char* IF_TYPE;
extern const char* ADDITEM_TYPE;
extern const char* WAIT_TYPE;
extern const char* DECLARE_TYPE;
extern const char* FUNCTION_TYPE;
extern const char* VARIABLE_TYPE;
extern const char* READ_TYPE;
extern const char* SET_TYPE;
extern const char* CALL_TYPE;
extern const char* ADD_TYPE;
extern const char* SUB_TYPE;
extern const char* MUL_TYPE;
extern const char* DIV_TYPE;
extern const char* EMPTY_TYPE;

// Special character check
extern const char IS_STRING;
extern const char IS_COMMENT;
extern const char IS_DELIMITER;
extern const char IS_VARIABLE;
extern const char IS_SPECIAL_CHARACTER;
extern const char IS_ARRAY_OPEN;
extern const char IS_ARRAY_CLOSED;

// Conditional check
extern const char* EQUAL;
extern const char* NOT_EQUAL;
extern const char* EQUAL_GREATER;
extern const char* EQUAL_LESS;
extern const char* GREATER;
extern const char* LESS;

// Value types
extern const char* STRING;
extern const char* INTEGER;
extern const char* ARRAY;

// Closure types
extern const char* ENDOPTIONS_TYPE;
extern const char* ENDCASE_TYPE;
extern const char* ENDIF_TYPE;
extern const char* ENDSWITCH_TYPE;
extern const char* ENDDECLARE_TYPE;
extern const char* ENDFUNCTION_TYPE;

// Logger Levels
extern const char* ERROR_LEVEL;
extern const char* WARNING_LEVEL;
extern const char* TYPE_LEVEL;
extern const char* VALUE_LEVEL;
extern const char* UNKNOWN_LEVEL;

// Error Messages
extern const char* COMMANDS_LENGTH_2;
extern const char* COMMANDS_LENGTH_3;
extern const char* COMMANDS_LENGTH_4;
extern const char* NOT_INSIDE_SWITCH;
extern const char* NOT_INSIDE_OPTIONS;
extern const char* OPTIONS_NOT_FOUND;
extern const char* UNKNOWN_COMMAND;
extern const char* UNKNOWN_SYMBOL;
extern const char* SECOND_ARGUMENT_EMPTY;
extern const char* THIRD_ARGUMENT_EMPTY;
extern const char* FOURTH_ARGUMENT_EMPTY;
extern const char* NO_NESTED_FUNCTIONS;
extern const char* FUNC_NOT_FOUND;
extern const char* VAR_NOT_FOUND;
extern const char* FUNC_ALREADY_EXISTS;
extern const char* VAR_ALREADY_EXISTS;
extern const char* STRING_TYPE_INVALID;
extern const char* DIFFERENT_TYPES;
extern const char* WRONG_CLOSURE;
extern const char* DIV_ZERO;

#endif
