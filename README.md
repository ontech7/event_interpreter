# Event Interpreter Validator
Validator for the Event Interpreter

## Event language syntax

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

`set <name> <value>`  

Sets a variable with a value.  
If the variable exists, the value will be changed.
If the variable doesn't exists, it will be created automatically.

`wait <string>`  

Wait a certain amount of time (seconds) before doing the very next action.  
  
`addItem <string>`  

Adds an item inside Player's inventory, if the item exists (be careful on what name you put in the statement, otherwise an exception will be thrown).  

## Error checks

There are a bunch of error checks, will add some others:

```c
const char* COMMANDS_LENGTH_2 = "Too few arguments. Expected at least 2.";
const char* COMMANDS_LENGTH_3 = "Too few arguments. Expected at least 3.";
const char* NOT_INSIDE_SWITCH = "'case' statement not inside 'switch'. Error occurred.";
const char* NOT_INSIDE_OPTIONS = "'text' statement not inside 'options'. Error occurred.";
const char* OPTIONS_NOT_FOUND = "'options' used in 'switch' not found. Error occurred.";
const char* UNKNOWN_COMMAND = "Unknown command. Check your code.";
const char* SECOND_ARGUMENT_EMPTY = "Second argument is empty. Check your code.";
const char* THIRD_ARGUMENT_EMPTY = "Third argument is empty. Check your code.";
const char* NO_NESTED_FUNCTIONS = "Nested function detected. Error occurred.";
const char* FUNC_NOT_FOUND = "Function not found. Error occurred.";
const char* VAR_NOT_FOUND = "Variable not found. Error occurred.";
const char* FUNC_ALREADY_EXISTS = "Function declared already exists. Error occurred.";
const char* VAR_ALREADY_EXISTS = "Variable declared already exists. Error occurred.";
```
