#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/definitions.h"
#include "../include/constants.h"
#include "../include/variables.h"

void function_skip_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

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

void if_skip_statement(const char* event_type, char* next_statement, int nestedIfNum) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            if_skip_statement(event_type, get_next_statement(), nestedIfNum);
            return;
        } else if (!strcmp(statement.commands[0], IF_TYPE)) { //IF_TYPE
            //nested IFs
            nestedIfCount++;
            if_skip_statement(event_type, get_next_statement(), nestedIfNum);
            return;
        } else if (!strcmp(statement.commands[0], ELSE_TYPE)) {
            if(nestedIfCount > nestedIfNum+1) {
                if_skip_statement(event_type, get_next_statement(), nestedIfNum);
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            }
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) { //ENDIF_TYPE
            nestedIfCount--;
            if(nestedIfCount == 0) {
                skip_statements_from_beginning(lineCount-1);
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            } else if(nestedIfCount > nestedIfNum) {
                if_skip_statement(event_type, get_next_statement(), nestedIfNum);
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            }
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
            if_skip_statement(event_type, get_next_statement(), nestedIfNum);
            return;
        }
    }
}
