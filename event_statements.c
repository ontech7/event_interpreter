#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/definitions.h"
#include "utils/constants.h"
#include "utils/variables.h"

void event_interpreter(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            //event_interpreter(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], DECLARE_TYPE)) { // DECLARE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            declare_statement(DECLARE_TYPE, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], NAME_TYPE)) { // NAME_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            }
        } else if (!strcmp(statement.commands[0], DIALOG_TYPE)) { // DIALOG_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                logger(event_type, subs_var_recursive(statement.commands[1]), VALUE_LEVEL, "");
                return;
            }
        } else if (!strcmp(statement.commands[0], CALL_TYPE)) { // CALL_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                call_statement(CALL_TYPE, next_statement, lineCount);
                return;
            }
        } else if (!strcmp(statement.commands[0], SET_TYPE)) { // SET_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                set_statement(SET_TYPE, next_statement);
                return;
            }
        } else if (!strcmp(statement.commands[0], ADD_TYPE)) { // ADD_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if(!strcmp(get_value_type(statement.commands[2]), STRING)) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                add_statement(ADD_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], SUB_TYPE)) { // SUB_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if(!strcmp(get_value_type(statement.commands[2]), STRING)) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                sub_statement(SUB_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], MUL_TYPE)) { // MUL_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if(!strcmp(get_value_type(statement.commands[2]), STRING)) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                mul_statement(MUL_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], DIV_TYPE)) { // DIV_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else if(!strcmp(get_value_type(statement.commands[2]), STRING)) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                div_statement(DIV_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], READ_TYPE)) { // READ_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                read_statement(READ_TYPE, next_statement);
                return;
            }
        } else if (!strcmp(statement.commands[0], OPTIONS_TYPE)) { // OPTIONS_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                options_statement(OPTIONS_TYPE, next_statement);
                return;
            }
        } else if (!strcmp(statement.commands[0], IF_TYPE)) { // IF_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                if_statement(IF_TYPE, next_statement);
                return;
            }
        } else if (!strcmp(statement.commands[0], SWITCH_TYPE)) { // SWITCH_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                switch_statement(SWITCH_TYPE, next_statement);
                return;
            }
        } else if (!strcmp(statement.commands[0], TEXT_TYPE)) { // TEXT_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_INSIDE_OPTIONS);
            stopPropagation = TRUE;
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { // CASE_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_INSIDE_SWITCH);
            stopPropagation = TRUE;
            return;
        } else if (!strcmp(statement.commands[0], ADDITEM_TYPE)) { // ADDITEM_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            }
        } else if (!strcmp(statement.commands[0], WAIT_TYPE)) { // WAIT_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
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
        } else { // UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
            return;
        }
    }
}

void declare_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1, funcsIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], FUNCTION_TYPE)) { //FUNCTION_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                for(i = 0; i < funcsCount; i++) {
                    if(!strcmp(funcs[i].name, statement.commands[1])) {
                        funcsIndex = i;
                    }
                }
                if(funcsIndex == -1) {
                    funcs[funcsCount].name = statement.commands[1];
                    funcs[funcsCount].lineCount = lineCount;
                    funcsCount++;
                    function_skip_statement(FUNCTION_TYPE, get_next_statement());
                    declare_statement(event_type, get_next_statement());
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, FUNC_ALREADY_EXISTS);
                    stopPropagation = TRUE;
                }
                return;
            }
        } else if (!strcmp(statement.commands[0], VARIABLE_TYPE)) { //VARIABLE_TYPE
            if(statement.size < 3) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_3);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[2] == NULL || !strcmp(statement.commands[2], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, THIRD_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex == -1) {
                    vars[varsCount].name = statement.commands[1];
                    vars[varsCount].value = statement.commands[2];
                    vars[varsCount].type = get_value_type(statement.commands[2]);
                    varsCount++;
                    declare_statement(event_type, get_next_statement());
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_ALREADY_EXISTS);
                    stopPropagation = TRUE;
                }
                return;
            }
        } else if (!strcmp(statement.commands[0], ENDDECLARE_TYPE)) { //ENDDECLARE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
            return;
        }
    }
}

void call_statement(const char* event_type, char* next_statement, int callLine) {
    if(!stopPropagation) {
        Statement statement;
        int i, funcIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            call_statement(event_type, get_next_statement(), callLine);
            return;
        } else if(!strcmp(statement.commands[0], CALL_TYPE)) { //CALL_TYPE
            for(i = 0; i < funcsCount; i++) {
                if(!strcmp(funcs[i].name, statement.commands[1])) {
                    funcIndex = i;
                }
            }
            if(funcIndex != -1) {
                skip_statements_from_beginning(funcs[funcIndex].lineCount);
                function_statement(FUNCTION_TYPE, next_statement, callLine);
                skip_statements_from_beginning(callLine);
                return;
            } else { //FUNC_NOT_FOUND
                logger(event_type, statement.commands[0], ERROR_LEVEL, FUNC_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        } 
    }
}

void function_statement(const char* event_type, char* next_statement, int callLine) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            function_statement(event_type, get_next_statement(), callLine);
            return;
        } else if(!strcmp(statement.commands[0], FUNCTION_TYPE)) { //FUNCTION_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            event_interpreter(event_type, get_next_statement());
            function_statement(event_type, get_next_statement(), callLine);
            return;
        } else if(!strcmp(statement.commands[0], ENDFUNCTION_TYPE)) { //ENDFUNCTION_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else {
            event_interpreter(event_type, next_statement);
            function_statement(event_type, get_next_statement(), callLine);
            return;
        }
    }
}

void set_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            set_statement(event_type, get_next_statement());
            return;
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                vars[varsIndex].name = statement.commands[1];
                vars[varsIndex].value = statement.commands[2];
                vars[varsIndex].type = get_value_type(statement.commands[2]);
                return;
            } else {
                vars[varsCount].name = statement.commands[1];
                vars[varsCount].value = statement.commands[2];
                vars[varsCount].type = get_value_type(statement.commands[2]);
                varsCount++;
                return;
            }
        }
    }
}

void read_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            read_statement(event_type, get_next_statement());
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                logger(event_type, vars[varsIndex].value, VALUE_LEVEL, "");
                return;
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void add_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;
        int tmpValue = 0;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            add_statement(event_type, get_next_statement());
            return;
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                if(!strcmp(vars[varsIndex].type, INTEGER)) {
                    tmpValue = get_value_as_integer(vars[varsIndex].value);
                    tmpValue = tmpValue + get_value_as_integer(statement.commands[2]);
                    sprintf(vars[varsIndex].value, "%d", tmpValue);
                    return;
                } else if(!strcmp(vars[varsIndex].type, STRING)) {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void sub_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;
        int tmpValue = 0;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            sub_statement(event_type, get_next_statement());
            return;
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                if(!strcmp(vars[varsIndex].type, INTEGER)) {
                    tmpValue = get_value_as_integer(vars[varsIndex].value);
                    tmpValue = tmpValue - get_value_as_integer(statement.commands[2]);
                    sprintf(vars[varsIndex].value, "%d", tmpValue);
                    return;
                } else if(!strcmp(vars[varsIndex].type, STRING)) {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void mul_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;
        int tmpValue = 0;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            add_statement(event_type, get_next_statement());
            return;
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                if(!strcmp(vars[varsIndex].type, INTEGER)) {
                    tmpValue = get_value_as_integer(vars[varsIndex].value);
                    tmpValue = tmpValue * get_value_as_integer(statement.commands[2]);
                    sprintf(vars[varsIndex].value, "%d", tmpValue);
                    return;
                } else if(!strcmp(vars[varsIndex].type, STRING)) {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void div_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1;
        int tmpValue = 0;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            add_statement(event_type, get_next_statement());
            return;
        } else {
            for(i = 0; i < varsCount; i++) {
                if(!strcmp(vars[i].name, statement.commands[1])) {
                    varsIndex = i;
                }
            }
            if(varsIndex != -1) {
                if(!strcmp(vars[varsIndex].type, INTEGER)) {
                    tmpValue = get_value_as_integer(vars[varsIndex].value);
                    if(get_value_as_integer(statement.commands[2]) == 0) {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, DIV_ZERO);
                        stopPropagation = TRUE;
                        return;
                    } else {
                        tmpValue = tmpValue / get_value_as_integer(statement.commands[2]);
                        sprintf(vars[varsIndex].value, "%d", tmpValue);
                        return;
                    }
                } else if(!strcmp(vars[varsIndex].type, STRING)) {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void options_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            options_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], OPTIONS_TYPE)) { //OPTIONS_TYPE
            //Check if statement.commands[1] var 'options' already exists
            //If not exists, create it
            options_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], TEXT_TYPE)) { //TEXT_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                //Realloc options and add statement.commands[1]
                options_statement(event_type, get_next_statement());
                return;
            }
        } else if (!strcmp(statement.commands[0], ENDOPTIONS_TYPE)) { //ENDOPTIONS_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
            return;
        }
    }
}

void switch_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            switch_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], SWITCH_TYPE)) { //SWITCH_TYPE
            //Check if statement.commands[1] var 'options' already exists
            //If not exists, throw error
            switch_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { //CASE_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
                return;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                case_statement(CASE_TYPE, next_statement);
                switch_statement(event_type, get_next_statement());
                return;
            }
        } else if (!strcmp(statement.commands[0], ENDSWITCH_TYPE)) { //ENDSWITCH_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
            return;
        }
    }
}

void case_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            case_statement(CASE_TYPE, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { //CASE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            case_statement(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], ENDCASE_TYPE)) { //ENDCASE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else {
            event_interpreter(event_type, next_statement);
            case_statement(event_type, get_next_statement());
            return;
        }
    }
}

void if_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation) {
        Statement statement;
        int i, varsIndex = -1, tmpValueArg2 = 0, tmpValueArg4 = 0;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) {
            if_statement(IF_TYPE, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) {
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            return;
        } else if(!strcmp(statement.commands[0], IF_TYPE)) {
            if(statement.size == 2) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex != -1) {
                    event_interpreter(event_type, get_next_statement());
                    if_statement(IF_TYPE, get_next_statement());
                    return;
                } else {
                    if_skip_statement(event_type, next_statement);
                    return;
                }
            } else if (statement.size == 4) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex != -1) {
                    if(!strcmp(get_value_type(statement.commands[3]), vars[varsIndex].type) 
                    && !strcmp(vars[varsIndex].type, INTEGER)) {
                        tmpValueArg2 = get_value_as_integer(vars[varsIndex].value);
                        tmpValueArg4 = get_value_as_integer(statement.commands[3]);

                        if(!strcmp(statement.commands[2], EQUAL)) {
                            if(tmpValueArg2 == tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], NOT_EQUAL)) {
                            if(tmpValueArg2 != tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], EQUAL_GREATER)) {
                            if(tmpValueArg2 >= tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], EQUAL_LESS)) {
                            if(tmpValueArg2 <= tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], LESS)) {
                            if(tmpValueArg2 < tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], GREATER)) {
                            if(tmpValueArg2 > tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else {
                            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_SYMBOL);
                            stopPropagation = TRUE;
                            return;
                        }
                    } if(!strcmp(get_value_type(statement.commands[3]), vars[varsIndex].type) 
                    && !strcmp(vars[varsIndex].type, STRING)) {
                        if(!strcmp(statement.commands[2], EQUAL)) {
                            if(!strcmp(statement.commands[3], vars[varsIndex].value)) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], NOT_EQUAL)) {
                            if(strcmp(statement.commands[3], vars[varsIndex].value) > 0 ||
                            strcmp(statement.commands[3], vars[varsIndex].value) < 0) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, next_statement);
                                return;
                            }
                        } else {
                            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_SYMBOL);
                            stopPropagation = TRUE;
                            return;
                        }
                    }else {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, DIFFERENT_TYPES);
                        stopPropagation = TRUE;
                        return;
                    }
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, FOURTH_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
                return;
            }
        } else {
            event_interpreter(event_type, next_statement);
            if_statement(IF_TYPE, get_next_statement());
            return;
        }
    }
}