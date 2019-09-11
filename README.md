# Event Interpreter Validator

[![Build Status](https://travis-ci.org/ontech7/event_interpreter_validator.svg?branch=develop)](https://travis-ci.org/ontech7/event_interpreter_validator)

Validator for the Event Interpreter

## Contents

- [Compiling guide](#compiling-guide)
- [Command types](#command-types)
- [Special symbols](#special-symbols)
- [Error checks](#error-checks)
- [Credits](#credits)

## Compiling guide

To compile the artifact, just write this in the terminal:

```gcc -I. *.c */*.c -o <output_name>```

To run it, put a .evnt file as 2nd argument. Ex.:  

```./<output_name> examples/test.evnt```

## Command types

| Command | Description | Link
| :---: | --- | :---: |
| `name` | Sets a name to the object. | See [NAME_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/NAME_TYPE.md) |
| `dialog` | Sets a dialog to the NPC. | See [DIALOG_tYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/DIALOG_TYPE.md) |
| `options` | Creates options for branch features. | See [OPTIONS_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/OPTIONS_TYPE.md) |
| `text` | Sets one option for the 'options' statement. | See [TEXT_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/TEXT_TYPE.md) |
| `switch` | Creates a switch branching system. | See [SWITCH_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/SWITCH_TYPE.md) |
| `case` | Creates one case based on the options given. | See [CASE_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/CASE_TYPE.md) |
| `if` | Creates a condition to be met in order to enter inside it. | See [IF_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/IF_TYPE.md) |
| `declare` | Statement that permits to declare variables and functions inside. | See [DECLARE_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/DECLARE_TYPE.md) |
| `function` | Implements a function that can be reused during the execution by 'call' statement. | See [FUNCTION_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/FUNCTION_TYPE.md) |
| `call` | Calls an already defined function, and executes it. | See [CALL_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/CALL_TYPE.md) |
| `variable` | Defines a variable that can be reused and modified during the execution. | See [VARIABLE_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/VARIABLE_TYPE.md) |
| `read` | Reads the value of a variable. | See [READ_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/READ_TYPE.md) |
| `set` | Sets a variable with a value. | See [SET_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/SET_TYPE.md) |
| `add` | Adds 'value' to the current value of 'name' variable. | See [ADD_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/ADD_TYPE.md) |
| `sub` | Subtracts 'value' to the current value of 'name' variable. | See [SUB_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/SUB_TYPE.md) |
| `mul` | Multiply 'value' to the current value of 'name' variable. | See [MUL_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/MUL_TYPE.md) |
| `div` | Divides 'value' to the current value of 'name' variable. | See [DIV_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/DIV_TYPE.md) |
| `wait` | Wait some seconds before doing the very next action. | See [WAIT_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/WAIT_TYPE.md) |
| `addItem` | Adds an item inside Player's inventory | See [ADDITEM_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/ADDITEM_TYPE.md) |
| `return` | Terminates the execution of the current subroutine and returns to the caller. | See [RETURN_TYPE](https://github.com/ontech7/event_interpreter_validator/blob/develop/docs/types/RETURN_TYPE.md) |

## Symbols

| Command | Description | Notes |
| :---: | :---: | :---: |
| `#` | Symbol used for writing comments. | Everything ahead this symbol will be ignored during the parse. |
| `"` | Symbol used for making string. | Must be closed with another equal symbol. |
| `$` | Symbol used for calling variables. | The value will be showed instead of the variable. Must be closed with another equal symbol. | 

## Error checks

There are a bunch of error checks, will add some others:

| Error Type | Message |
| --- | --- |
| `COMMANDS_LENGTH_2` | *Too few arguments. Expected at least 2.* |
| `COMMANDS_LENGTH_3` | *Too few arguments. Expected at least 3.* |
| `COMMANDS_LENGTH_4` | *Too few arguments. Expected at least 4.* |
| `NOT_INSIDE_SWITCH` | *'case' statement not inside 'switch'. Error occurred.* |
| `NOT_INSIDE_OPTIONS` | *'text' statement not inside 'options'. Error occurred.* |
| `OPTIONS_NOT_FOUND` | *'options' used in 'switch' not found. Error occurred.* |
| `UNKNOWN_COMMAND` | *Unknown command. Check your code.* |
| `UNKNOWN_SYMBOL` | *Unknown symbol. Check your code.* |
| `SECOND_ARGUMENT_EMPTY` | *Second argument is empty. Check your code.* |
| `THIRD_ARGUMENT_EMPTY` | *Third argument is empty. Check your code.* |
| `FOURTH_ARGUMENT_EMPTY` | *Fourth argument is empty. Check your code.* |
| `NO_NESTED_FUNCTIONS` | *Nested function detected. Error occurred.* |
| `FUNC_NOT_FOUND` | *Function not found. Error occurred.* |
| `VAR_NOT_FOUND` | *Variable not found. Error occurred.* |
| `FUNC_ALREADY_EXISTS` | *Function declared already exists. Error occurred.* |
| `VAR_ALREADY_EXISTS` | *Variable declared already exists. Error occurred.* |
| `STRING_TYPE_INVALID` | *Type invalid. Variable is declared as 'string'. Error occurred.* |
| `INTEGER_TYPE_INVALID` | *Type invalid. Variable is declared as 'integer'. Error occurred.* |
| `DIFFERENT_TYPES` | *The two compared values have different types. Error occurred.* |
| `WRONG_CLOSURE` | *Wrong closure of the statement. Error occurred.* |

Credits
----

$ Andrea Losavio (https://github.com/ontech7)
