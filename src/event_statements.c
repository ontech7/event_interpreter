#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/definitions.h"
#include "include/constants.h"
#include "include/variables.h"

void event_interpreter(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            //event_interpreter(event_type, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], RETURN_TYPE)) { // RETURN_TYPE
            returnCall = TRUE;
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
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex = -1, funcsIndex = -1;

        statement = tokenizer(next_statement);

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
                    vars[varsCount].value = (char**)calloc(1, sizeof(char*));
                    vars[varsCount].value[0] = statement.commands[2];
                    vars[varsCount].size = 1;
                    vars[varsCount].type = get_value_type(statement.commands[2]);
                    vars[varsCount].isConstant = FALSE;
                    varsCount++;
                    declare_statement(event_type, get_next_statement());
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_ALREADY_EXISTS);
                    stopPropagation = TRUE;
                }
                return;
            }
        } else if (!strcmp(statement.commands[0], CONSTANT_TYPE)) { //CONSTANT_TYPE
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
                    vars[varsCount].value = (char**)calloc(1, sizeof(char*));
                    vars[varsCount].value[0] = statement.commands[2];
                    vars[varsCount].size = 1;
                    vars[varsCount].type = get_value_type(statement.commands[2]);
                    vars[varsCount].isConstant = TRUE;
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
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, funcIndex = -1;

        statement = tokenizer(next_statement);

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

        statement = tokenizer(next_statement);

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
            returnCall = FALSE;
            return;
        } else {
            event_interpreter(event_type, next_statement);
            function_statement(event_type, get_next_statement(), callLine);
            return;
        }
    }
}

void set_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex1 = -1, varsIndex2 = -1;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            set_statement(event_type, get_next_statement());
            return;
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex1 = i;
                    }
                }
                if(varsIndex1 != -1) {
                    if(!strcmp(get_value_type(statement.commands[2]), INTEGER) ||
                        !strcmp(get_value_type(statement.commands[2]), STRING)) {
                        if(vars[varsIndex1].isConstant == FALSE) {
                            vars[varsIndex1].value[0] = statement.commands[2];
                            vars[varsIndex1].type = get_value_type(statement.commands[2]);
                            return;
                        } else {
                            logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                            stopPropagation = TRUE;
                            return;
                        }
                    } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                        for(i = 0; i < varsCount; i++) {
                            if(!strcmp(vars[i].name, statement.commands[2])) {
                                varsIndex2 = i;
                            }
                        }
                        if(varsIndex2 != -1) {
                            if(vars[varsIndex1].isConstant == FALSE) {
                                vars[varsIndex1].value[0] = (char*)calloc(strlen(vars[varsIndex2].value[0]), sizeof(char));
                                vars[varsIndex1].type = (char*)calloc(strlen(vars[varsIndex2].type), sizeof(char));
                                strcpy(vars[varsIndex1].value[0], vars[varsIndex2].value[0]);
                                strcpy(vars[varsIndex1].type, vars[varsIndex2].type);
                                return;
                            } else {
                                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                stopPropagation = TRUE;
                                return;
                            }
                        } else {
                            logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                            stopPropagation = TRUE;
                            return;
                        }
                    }
                } else {
                    if(!strcmp(get_value_type(statement.commands[2]), INTEGER) ||
                        !strcmp(get_value_type(statement.commands[2]), STRING)) {
                        vars[varsCount].name = statement.commands[1];
                        vars[varsCount].value = (char**)calloc(1, sizeof(char*));
                        vars[varsCount].value[0] = statement.commands[2];
                        vars[varsCount].size = 1;
                        vars[varsCount].type = get_value_type(statement.commands[2]);
                        varsCount++;
                        return;
                    } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                        for(i = 0; i < varsCount; i++) {
                            if(!strcmp(vars[i].name, statement.commands[2])) {
                                varsIndex2 = i;
                            }
                        }
                        if(varsIndex2 != -1) {
                            vars[varsCount].name = statement.commands[1];
                            vars[varsCount].value = (char**)calloc(1, sizeof(char*));
                            //vars[varsCount].value[0] = vars[varsIndex2].value[0];
                            vars[varsCount].value[0] = (char*)calloc(strlen(vars[varsIndex2].value[0]), sizeof(char));
                            strcpy(vars[varsCount].value[0], vars[varsIndex2].value[0]);
                            vars[varsCount].size = 1;
                            //vars[varsCount].type = vars[varsIndex2].type;
                            vars[varsCount].type = (char*)calloc(strlen(vars[varsIndex2].type), sizeof(char));
                            strcpy(vars[varsCount].value[0], vars[varsIndex2].value[0]);
                            varsCount++;
                            return;
                        } else {
                            logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                            stopPropagation = TRUE;
                            return;
                        }
                    }
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void read_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex = -1;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            read_statement(event_type, get_next_statement());
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex != -1) {
                    logger(event_type, subs_var_recursive(vars[varsIndex].value[0]), VALUE_LEVEL, "");
                    return;
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void add_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex1 = -1, varsIndex2 = -1;
        int tmpValue = 0;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            add_statement(event_type, get_next_statement());
            return;
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex1 = i;
                    }
                }
                if(varsIndex1 != -1) {
                    if(!strcmp(vars[varsIndex1].type, INTEGER)) {
                        if(!strcmp(get_value_type(statement.commands[2]), INTEGER)) {
                            if(vars[varsIndex1].isConstant == FALSE) {
                                tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                tmpValue = tmpValue + get_value_as_integer(statement.commands[2]);
                                sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                return;
                            } else {
                                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                stopPropagation = TRUE;
                                return;
                            }
                        } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                            for(i = 0; i < varsCount; i++) {
                                if(!strcmp(vars[i].name, statement.commands[2])) {
                                    varsIndex2 = i;
                                }
                            }
                            if(varsIndex2 != -1) {
                                if(!strcmp(vars[varsIndex2].type, INTEGER)) {
                                    if(vars[varsIndex1].isConstant == FALSE) {
                                        tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                        tmpValue = tmpValue + get_value_as_integer(vars[varsIndex2].value[0]);
                                        sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                        return;
                                    } else {
                                        logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                        stopPropagation = TRUE;
                                        return;
                                    }
                                } else if(!strcmp(vars[varsIndex2].type, STRING)){
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
                    } else if(!strcmp(vars[varsIndex1].type, STRING)) {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                        stopPropagation = TRUE;
                        return;
                    }
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void sub_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex1 = -1, varsIndex2 = -1;
        int tmpValue = 0;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            sub_statement(event_type, get_next_statement());
            return;
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex1 = i;
                    }
                }
                if(varsIndex1 != -1) {
                    if(!strcmp(vars[varsIndex1].type, INTEGER)) {
                        if(!strcmp(get_value_type(statement.commands[2]), INTEGER)) {
                            if(vars[varsIndex1].isConstant == FALSE) {
                                tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                tmpValue = tmpValue - get_value_as_integer(statement.commands[2]);
                                sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                return;
                            } else {
                                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                stopPropagation = TRUE;
                                return;
                            }
                        } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                            for(i = 0; i < varsCount; i++) {
                                if(!strcmp(vars[i].name, statement.commands[2])) {
                                    varsIndex2 = i;
                                }
                            }
                            if(varsIndex2 != -1) {
                                if(!strcmp(vars[varsIndex2].type, INTEGER)) {
                                    if(vars[varsIndex1].isConstant == FALSE) {
                                        tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                        tmpValue = tmpValue - get_value_as_integer(vars[varsIndex2].value[0]);
                                        sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                        return;
                                    } else {
                                        logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                        stopPropagation = TRUE;
                                        return;
                                    }
                                } else if(!strcmp(vars[varsIndex2].type, STRING)){
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
                    } else if(!strcmp(vars[varsIndex1].type, STRING)) {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                        stopPropagation = TRUE;
                        return;
                    }
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void mul_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex1 = -1, varsIndex2 = -1;
        int tmpValue = 0;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            mul_statement(event_type, get_next_statement());
            return;
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex1 = i;
                    }
                }
                if(varsIndex1 != -1) {
                    if(!strcmp(vars[varsIndex1].type, INTEGER)) {
                        if(!strcmp(get_value_type(statement.commands[2]), INTEGER)) {
                            if(vars[varsIndex1].isConstant == FALSE) {
                                tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                tmpValue = tmpValue * get_value_as_integer(statement.commands[2]);
                                sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                return;
                            } else {
                                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                stopPropagation = TRUE;
                                return;
                            }
                        } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                            for(i = 0; i < varsCount; i++) {
                                if(!strcmp(vars[i].name, statement.commands[2])) {
                                    varsIndex2 = i;
                                }
                            }
                            if(varsIndex2 != -1) {
                                if(!strcmp(vars[varsIndex2].type, INTEGER)) {
                                    if(vars[varsIndex1].isConstant == FALSE) {
                                        tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                        tmpValue = tmpValue * get_value_as_integer(vars[varsIndex2].value[0]);
                                        sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                        return;
                                    } else {
                                        logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                        stopPropagation = TRUE;
                                        return;
                                    }
                                } else if(!strcmp(vars[varsIndex2].type, STRING)){
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
                    } else if(!strcmp(vars[varsIndex1].type, STRING)) {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                        stopPropagation = TRUE;
                        return;
                    }
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void div_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i, varsIndex1 = -1, varsIndex2 = -1;
        int tmpValue = 0;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            div_statement(event_type, get_next_statement());
            return;
        } else {
            if(!strcmp(get_value_type(statement.commands[1]), VAR_CONST)) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex1 = i;
                    }
                }
                if(varsIndex1 != -1) {
                    if(!strcmp(vars[varsIndex1].type, INTEGER)) {
                        if(!strcmp(get_value_type(statement.commands[2]), INTEGER)) {
                            if(vars[varsIndex1].isConstant == FALSE) {
                                tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                if(get_value_as_integer(statement.commands[2]) == 0) {
                                    logger(event_type, statement.commands[0], ERROR_LEVEL, DIV_ZERO);
                                    stopPropagation = TRUE;
                                    return;
                                } else {
                                    tmpValue = tmpValue / get_value_as_integer(statement.commands[2]);
                                    sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                    return;
                                }
                            } else {
                                logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                stopPropagation = TRUE;
                                return;
                            }
                        } else if(!strcmp(get_value_type(statement.commands[2]), VAR_CONST)) {
                            for(i = 0; i < varsCount; i++) {
                                if(!strcmp(vars[i].name, statement.commands[2])) {
                                    varsIndex2 = i;
                                }
                            }
                            if(varsIndex2 != -1) {
                                if(!strcmp(vars[varsIndex2].type, INTEGER)) {
                                    if(vars[varsIndex1].isConstant == FALSE) {
                                        tmpValue = get_value_as_integer(vars[varsIndex1].value[0]);
                                        if(get_value_as_integer(vars[varsIndex2].value[0]) == 0) {
                                            logger(event_type, statement.commands[0], ERROR_LEVEL, DIV_ZERO);
                                            stopPropagation = TRUE;
                                            return;
                                        } else {
                                            tmpValue = tmpValue / get_value_as_integer(vars[varsIndex2].value[0]);
                                            sprintf(vars[varsIndex1].value[0], "%d", tmpValue);
                                            return;
                                        }
                                    } else {
                                        logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_CONSTANT);
                                        stopPropagation = TRUE;
                                        return;
                                    }
                                } else if(!strcmp(vars[varsIndex2].type, STRING)){
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
                    } else if(!strcmp(vars[varsIndex1].type, STRING)) {
                        logger(event_type, statement.commands[0], ERROR_LEVEL, STRING_TYPE_INVALID);
                        stopPropagation = TRUE;
                        return;
                    }
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
                    stopPropagation = TRUE;
                    return;
                }
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_VARIABLE);
                stopPropagation = TRUE;
                return;
            }
        }
    }
}

void options_statement(const char* event_type, char* next_statement) {
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

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
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

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
    if(!stopPropagation & !returnCall) {
        Statement statement;
        int i;

        statement = tokenizer(next_statement);

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
    if(!stopPropagation && !returnCall) {
        Statement statement;
        int i, varsIndex = -1, tmpValueArg2 = 0, tmpValueArg4 = 0;

        statement = tokenizer(next_statement);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            if_statement(IF_TYPE, get_next_statement());
            return;
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) { //ENDIF_TYPE
            nestedIfCount--;
            if(nestedIfCount > 0) {
                if_statement(event_type, get_next_statement());
                return;
            } else {
                nestedIfCount = 0;
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                return;
            }
        } else if (!strcmp(statement.commands[0], ELSE_TYPE)) {
            if_skip_statement(event_type, get_next_statement(), nestedIfCount-1);
            if_statement(IF_TYPE, get_next_statement());
            return;
        } else if(!strcmp(statement.commands[0], IF_TYPE)) { //IF_TYPE
            nestedIfCount++;
            if(statement.size == 2) {
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex != -1) {
                    //event_interpreter(event_type, get_next_statement());
                    if_statement(IF_TYPE, get_next_statement());
                    return;
                } else {
                    if_skip_statement(event_type, get_next_statement(), nestedIfCount-1);
                    if_statement(IF_TYPE, get_next_statement());
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
                        tmpValueArg2 = get_value_as_integer(vars[varsIndex].value[0]);
                        tmpValueArg4 = get_value_as_integer(statement.commands[3]);

                        if(!strcmp(statement.commands[2], EQUAL)) {
                            if(tmpValueArg2 == tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], NOT_EQUAL)) {
                            if(tmpValueArg2 != tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], EQUAL_GREATER)) {
                            if(tmpValueArg2 >= tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], EQUAL_LESS)) {
                            if(tmpValueArg2 <= tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], LESS)) {
                            if(tmpValueArg2 < tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], GREATER)) {
                            if(tmpValueArg2 > tmpValueArg4) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
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
                            if(!strcmp(statement.commands[3], vars[varsIndex].value[0])) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
                                return;
                            }
                        } else if(!strcmp(statement.commands[2], NOT_EQUAL)) {
                            if(strcmp(statement.commands[3], vars[varsIndex].value[0]) > 0 ||
                            strcmp(statement.commands[3], vars[varsIndex].value[0]) < 0) {
                                event_interpreter(event_type, get_next_statement());
                                if_statement(IF_TYPE, get_next_statement());
                                return;
                            } else {
                                if_skip_statement(event_type, get_next_statement(), nestedIfCount);
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