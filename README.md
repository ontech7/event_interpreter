# Event Interpreter Validator
Validator for the Event Interpreter

## Event language syntax

- name_<spacedString>
  
`name_"NPC Name"` 

Gives a name to the NPC (must be the first statement)

- dialog_<spacedString>
  
`dialog_"NPC Name"` 

Sets a dialog to the NPC (based on the order of the 'dialog' statements)

- options_<string>
  
`options_coffee
    text_"Yes"
    text_"No"
endoptions` 

Creates options for branch features. The 2nd argument is the variable used by a 'switch' statement.
Inside 'options' statement, there must be only 'text' statements, like in the example.

- switch_<string>
  
`switch_coffee
    case_0
        dialog_"Oh, me too"
    endcase
    case_1
        dialog_"Mmh... You are a liar... Everyone likes coffee!"
        wait_1
        dialog_"Take this cup of coffee. You will like it"
        addItem_"Cup of coffee"
    endcase
endswitch` 

Creates a complex switch branched features, using 'case' statements based on the order of the option (e.g.: "Yes" is case_0).
You can write other new options, switches, etc. inside a 'case', without limits (well, based on hardware limits).

- wait_<integer_number>

`wait_1`

Wait a certain amount of time (seconds) before doing the very next action. 

- addItem_<spacedString>
  
`addItem_"Cup of coffee"`

Adds an item inside Player's inventory, if the item exists (be careful on what name you put in the statement).

-----

N.B.: Multiline statements such as options, case and switch, must have a closure statement such as endoptions, endcase and endswitch. Usually it's just end-statementname.

## Error checks

There are a bunch of error checks, will add some others:

```const char* COMMANDS_LENGTH = "Too few arguments. Expected at least 2.";
const char* NOT_INSIDE_SWITCH = "'case' statement not inside 'switch'. Error occurred.";
const char* NOT_INSIDE_OPTIONS = "'text' statement not inside 'options'. Error occurred.";
const char* OPTIONS_NOT_FOUND = "'options' used in 'switch' not found: ";
const char* UNKNOWN_COMMAND = "Unknown command. Check your code.";
const char* TEXTFIELD_EMPTY = "'Textfield is empty. Check your code.";```
