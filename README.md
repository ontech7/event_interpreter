# Event Interpreter Validator
Validator for the Event Interpreter

## Compiling guide

To compile the artifact, just write this in the terminal:

```gcc -I. *.c */*.c -o <output_name>```

To run it, put a .evnt file as 2nd argument. Ex.:  

```./<output_name> examples/test.evnt```

## Event language statements

| Command | Description | Link
| --- | --- | --- |
| `name <text>` | Sets a name to the object. | . |
| `dialog <text>` | Sets a dialog to the NPC. | . |
| `options <name>` | Creates options for branch features. | . |
| `text <option>` | Sets one option for the 'options' statement. | . |
| `switch <name>` | Creates a switch branching system. | . |
| `case <index>` | Creates one case based on the options given. | . |
| `if <varName> [<conditionalSymbol> <value>]` | Creates a condition to be met in order to enter inside it. | . |
| `declare` | Statement that permits to declare variables and functions inside. | . |
| `function <name>` | Implements a function that can be reused during the execution by 'call' statement. | . |
| `call <name>` | Calls an already defined function, and executes it. | . |
| `variable <name> <value>` | Defines a variable that can be reused and modified during the execution. | . |
| `read <name>` | Reads the value of a variable. | . |
| `set <name> <value/name>` | Sets a variable with a value. | . |
| `add <name> <value/name>` | Adds 'value' to the current value of 'name' variable. | . |
| `sub <name> <value/name>` | Subtracts 'value' to the current value of 'name' variable. | . |
| `mul <name> <value/name>` | Multiply 'value' to the current value of 'name' variable. | . |
| `div <name> <value/name>` | Divides 'value' to the current value of 'name' variable. | . |
| `wait <string>` | Wait some seconds before doing the very next action. | . |
| `addItem <string>` | Adds an item inside Player's inventory | . |
| `return` | Terminates the execution of the current subroutine and returns to the caller. | . |

## Event language special symbols

| Command | Description | Notes |
| --- | --- | --- |
| `#` | Symbol used for writing comments. | Everything ahead this symbol will be ignored during the parse. |
| `"` | Symbol used for making string. | Must be closed with another equal symbol. |
| `$` | Symbol used for calling variables. | The value will be showed instead of the variable. Must be closed with another equal symbol. | 

## Error checks

There are a bunch of error checks, will add some others:

| Error Type | Message |
| --- | --- |
| COMMANDS_LENGTH_2 | Too few arguments. Expected at least 2. |
| COMMANDS_LENGTH_3 | Too few arguments. Expected at least 3. |
| COMMANDS_LENGTH_4 | Too few arguments. Expected at least 4. |
| NOT_INSIDE_SWITCH | 'case' statement not inside 'switch'. Error occurred. |
| NOT_INSIDE_OPTIONS | 'text' statement not inside 'options'. Error occurred. |
| OPTIONS_NOT_FOUND | 'options' used in 'switch' not found. Error occurred. |
| UNKNOWN_COMMAND | Unknown command. Check your code. |
| UNKNOWN_SYMBOL | Unknown symbol. Check your code. |
| SECOND_ARGUMENT_EMPTY | Second argument is empty. Check your code. |
| THIRD_ARGUMENT_EMPTY | Third argument is empty. Check your code. |
| FOURTH_ARGUMENT_EMPTY | Fourth argument is empty. Check your code. |
| NO_NESTED_FUNCTIONS | Nested function detected. Error occurred. |
| FUNC_NOT_FOUND | Function not found. Error occurred. |
| VAR_NOT_FOUND | Variable not found. Error occurred. |
| FUNC_ALREADY_EXISTS | Function declared already exists. Error occurred. |
| VAR_ALREADY_EXISTS | Variable declared already exists. Error occurred. |
| STRING_TYPE_INVALID | Type invalid. Variable is declared as 'string'. Error occurred. |
| INTEGER_TYPE_INVALID | Type invalid. Variable is declared as 'integer'. Error occurred. |
| DIFFERENT_TYPES | The two compared values have different types. Error occurred. |
| WRONG_CLOSURE | Wrong closure of the statement. Error occurred. |