#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/definitions.h"
#include "utils/constants.h"
#include "utils/variables.h"

void function_skip_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            function_skip_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], ENDFUNCTION_TYPE)) { //ENDFUNCTION_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else if (!strcmp(statement.commands[0], FUNCTION_TYPE)) { //FUNCTION_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, NO_NESTED_FUNCTIONS);
            stopPropagation = TRUE;
            return;
        } else { //Skip statements
            function_skip_statement(event_type, get_next_statement());
            return;
        }
    }
}

void if_skip_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            if_skip_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) { //ENDIF_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else if (!strcmp(statement.commands[0], ENDOPTIONS_TYPE)) { // ENDOPTIONS_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ENDCASE_TYPE)) { // ENDCASE_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) { // ENDIF_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ENDSWITCH_TYPE)) { // ENDSWITCH_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ENDDECLARE_TYPE)) { // ENDDECLARE_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ENDFUNCTION_TYPE)) { // ENDFUNCTION_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, WRONG_CLOSURE);
            stopPropagation = TRUE;
            return;
        } else { //Skip statements
            if_skip_statement(event_type, get_next_statement());
            return;
        }
    }
}