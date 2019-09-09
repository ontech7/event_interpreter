# Event Interpreter Validator
Validator for the Event Interpreter

## Compiling guide

To compile the artifact, just write this in the terminal:

```gcc -I. *.c -o <output_name>```

## Event language statements

`name <text>`  

Sets a name to the object.  
  
`dialog <text>`  

Sets a dialog to the NPC (based on the order of the 'dialog' statements).  
  
`options <name>`  

Creates options for branch features.  
The 2nd argument is the variable used by a 'switch' statement.  
Inside 'options' statement, there must be only 'text' statements.  
To close 'options' statement, there must be an 'endoptions' at the end.  

`text <option>`  

Sets one option for the 'options' statement.  
  
`switch <name>`  

Creates a switch branching system.  
Users 'case' statements based on the order of the option (e.g.: text "Yes" is case 0).  
To close 'switch' statement, there must be an 'endswitch' at the end.  

`case <index>`  

Creates one case based on the options given.  
You can write other new options, switches, etc. inside a 'case', without limits (well, based on hardware limits).  
To close 'case' statement, there must be an 'endcase' at the end.  

`if <varName> [<conditionalSymbol> <value>]`  

Creates a condition to be met in order to enter inside it.  
With 2 arguments checks the existance of the variable, with 4 arguments compares 2nd and 4th argument.  
Possible conditional checks: >, <, >=, <=, =, !=.  
If the variable is a string, the possible checks are only: =, !=.  
To close 'if' statement, there must be an 'endif' at the end.  

`declare`  

Statement that permits to declare variables and functions inside.  
To close 'declare' statement, there must be an 'enddeclare' at the end.  

N.B.: It's usual to use this statement on top of the file, otherwise statements behind 'declare' CAN'T be read, and an exception will be thrown.  

`function <name>`  

Implements a function that can be reused during the execution by 'call' statement.  
The function name can be the same of a variable, because they don't comunicate with each other.  
Everything can be put inside, except for nested functions. An exception will be thrown.  
To close 'function' statement, there must be an 'endfunction' at the end.  

`call <name>`  

Calls an already defined function, and executes it. At the end of the call, the pointer line returns to the very next statement.  
The name must be the same of the function, otherwise an exception will be thrown.  

`variable <name> <value>`  

Defines a variable that can be reused and modified during the execution.  
The variable name can be the same of a function, because they don't comunicate with each other.  

`read <name>`  

Reads the value of a variable.  

`set <name> <value/name>`  

Sets a variable with a value.  
It's possible to call another variable as 3rd argument (INTEGER type).  
If the variable exists, the value will be changed.  
If the variable doesn't exists, it will be created automatically.  

`add <name> <value/name>`  

Adds 'value' to the current value of 'name' variable.  
It's possible to call another variable as 3rd argument (INTEGER type).  

`sub <name> <value/name>`  

Subtracts 'value' to the current value of 'name' variable.  
It's possible to call another variable as 3rd argument (INTEGER type).  

`mul <name> <value/name>`  

Multiply 'value' to the current value of 'name' variable.  
It's possible to call another variable as 3rd argument (INTEGER type).  

`div <name> <value/name>`  

Divides 'value' to the current value of 'name' variable.  
It's possible to call another variable as 3rd argument (INTEGER type).  
It's not possible to divide by zero.  

`wait <string>`  

Wait a certain amount of time (seconds) before doing the very next action.  
  
`addItem <string>`  

Adds an item inside Player's inventory, if the item exists (be careful on what name you put in the statement, otherwise an exception will be thrown).  

## Event language special symbols

`#`  

Symbol used for writing comments.  
Everything ahead this symbol will be ignored during the parse.  

`"`  

Symbol used for making string.  
Must be closed with another equal symbol.  

`$`  

Symbol used for calling variables.  
The value will be showed instead of the variable.  
Must be closed with another equal symbol.  

## Error checks

There are a bunch of error checks, will add some others:

```c
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
const char* INTEGER_TYPE_INVALID = "Type invalid. Variable is declared as 'integer'. Error occurred.";
const char* DIFFERENT_TYPES = "The two compared values have different types. Error occurred.";
const char* WRONG_CLOSURE = "Wrong closure of the statement. Error occurred.";
```
