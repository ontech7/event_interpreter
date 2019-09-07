#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.c"

void event_interpreter(const char*, ssize_t);
void declare_statement(const char*, ssize_t);
void function_skip_statement(const char*, ssize_t);
void set_statement(const char*, ssize_t, Statement);
void read_statement(const char*, ssize_t, Statement);
void call_statement(const char*, ssize_t);
void options_statement(const char*, ssize_t, char*);
void switch_statement(const char*, ssize_t, char*);
void case_statement(const char*, ssize_t, char*);
void if_statement(const char*, ssize_t);

void event_interpreter(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) {
            event_interpreter(event_type, get_next_statement());
        } else if (!strcmp(statement.commands[0], DECLARE_TYPE)) { // DECLARE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            declare_statement(DECLARE_TYPE, get_next_statement());
        } else if (!strcmp(statement.commands[0], NAME_TYPE)) { // NAME_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], DIALOG_TYPE)) { // DIALOG_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], CALL_TYPE)) { // CALL_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                call_statement(CALL_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], SET_TYPE)) { // SET_TYPE
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
                set_statement(SET_TYPE, next_statement, statement);
            }
        } else if (!strcmp(statement.commands[0], READ_TYPE)) { // READ_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                read_statement(READ_TYPE, next_statement, statement);
            }
        } else if (!strcmp(statement.commands[0], OPTIONS_TYPE)) { // OPTIONS_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                options_statement(OPTIONS_TYPE, get_next_statement(), statement.commands[1]);
            }
        } else if (!strcmp(statement.commands[0], IF_TYPE)) { // IF_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                if_statement(IF_TYPE, next_statement);
            }
        } else if (!strcmp(statement.commands[0], SWITCH_TYPE)) { // SWITCH_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                switch_statement(SWITCH_TYPE, get_next_statement(), statement.commands[1]);
            }
        } else if (!strcmp(statement.commands[0], TEXT_TYPE)) { // TEXT_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_INSIDE_OPTIONS);
            stopPropagation = TRUE;
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { // CASE_TYPE
            logger(event_type, statement.commands[0], ERROR_LEVEL, NOT_INSIDE_SWITCH);
            stopPropagation = TRUE;
        } else if (!strcmp(statement.commands[0], ADDITEM_TYPE)) { // ADDITEM_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], WAIT_TYPE)) { // WAIT_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else { // UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
        }
    }
}

void declare_statement(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i, varsIndex = -1, funcsIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
        } else if (!strcmp(statement.commands[0], FUNCTION_TYPE)) { //FUNCTION_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
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
            }
        } else if (!strcmp(statement.commands[0], VARIABLE_TYPE)) { //VARIABLE_TYPE
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
                for(i = 0; i < varsCount; i++) {
                    if(!strcmp(vars[i].name, statement.commands[1])) {
                        varsIndex = i;
                    }
                }
                if(varsIndex == -1) {
                    vars[varsCount].name = statement.commands[1];
                    vars[varsCount].value = statement.commands[2];
                    varsCount++;
                    declare_statement(event_type, get_next_statement());
                } else {
                    logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_ALREADY_EXISTS);
                    stopPropagation = TRUE;
                }
            }
        } else if (!strcmp(statement.commands[0], ENDDECLARE_TYPE)) { //ENDDECLARE_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
        }
    }
}

void function_skip_statement(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
        } else if (!strcmp(statement.commands[0], ENDFUNCTION_TYPE)) { //ENDFUNCTION_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else if (!strcmp(statement.commands[0], FUNCTION_TYPE)) {
            logger(event_type, statement.commands[0], ERROR_LEVEL, NO_NESTED_FUNCTIONS);
            stopPropagation = TRUE;
        } else { //Skip statements
            function_skip_statement(event_type, get_next_statement());
        }
    }
}

void call_statement(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i, funcIndex = -1;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
        } else if(!strcmp(statement.commands[0], ENDFUNCTION_TYPE)) { //ENDFUNCTION_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            for(i = lineCount; i < callLine; i++) {
                _nxt = get_next_statement();
            }
        } else if(!strcmp(event_type, FUNCTION_TYPE)) { //event_type = FUNCTION
            event_interpreter(FUNCTION_TYPE, next_statement);
            call_statement(event_type, get_next_statement());
        } else if(!strcmp(statement.commands[0], CALL_TYPE)) { //CALL_TYPE
            for(i = 0; i < funcsCount; i++) {
                if(!strcmp(funcs[i].name, statement.commands[1])) {
                    printf("%s\n", funcs[i].name);
                    funcIndex = i;
                }
            }
            if(funcIndex != -1) {
                if(!strcmp(funcs[funcIndex].name, statement.commands[1])) {
                    callLine = lineCount;
                    lineCount = 0;
                    fseek(eventFile, 0, SEEK_SET);
                    for(i = 0; i < funcs[funcIndex].lineCount; i++) {
                        _nxt = get_next_statement();
                    }
                    event_interpreter(FUNCTION_TYPE, get_next_statement());
                    call_statement(FUNCTION_TYPE, get_next_statement());
                } 
            } else {
                logger(event_type, statement.commands[0], ERROR_LEVEL, FUNC_NOT_FOUND);
                stopPropagation = TRUE;
            }
        }
    }
}

void set_statement(const char* event_type, ssize_t next_statement, Statement statement) {
    if(!stopPropagation) {
        int i, varsIndex = -1;

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
        }

        for(i = 0; i < varsCount; i++) {
            if(!strcmp(vars[i].name, statement.commands[1])) {
                varsIndex = i;
            }
        }
        if(varsIndex != -1) {
            vars[varsIndex].name = statement.commands[1];
            vars[varsIndex].value = statement.commands[2];
            logger(event_type, statement.commands[2], VALUE_LEVEL, "");
        } else {
            vars[varsCount].name = statement.commands[1];
            vars[varsCount].value = statement.commands[2];
            varsCount++;
            logger(event_type, statement.commands[2], VALUE_LEVEL, "");
        }
        
    }
}

void read_statement(const char* event_type, ssize_t next_statement, Statement statement) {
    if(!stopPropagation) {
        int i, varsIndex = -1;

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            declare_statement(event_type, get_next_statement());
        }

        for(i = 0; i < varsCount; i++) {
            if(!strcmp(vars[i].name, statement.commands[1])) {
                varsIndex = i;
            }
        }
        if(varsIndex != -1) {
            logger(event_type, vars[varsIndex].value, VALUE_LEVEL, "");
        } else {
            logger(event_type, statement.commands[0], ERROR_LEVEL, VAR_NOT_FOUND);
            stopPropagation = TRUE;
        }
    }
}

void options_statement(const char* event_type, ssize_t next_statement, char* option_name) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            options_statement(event_type, get_next_statement(), option_name);
        } else if (!strcmp(statement.commands[0], TEXT_TYPE)) {
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                options_statement(event_type, get_next_statement(), option_name);
            }
        } else if (!strcmp(statement.commands[0], ENDOPTIONS_TYPE)) { //ENDOPTIONS_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
        }
    }
}

void switch_statement(const char* event_type, ssize_t next_statement, char* option_name) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            switch_statement(event_type, get_next_statement(), option_name);
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { //CASE_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH_2);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL || !strcmp(statement.commands[1], "")){
                logger(event_type, statement.commands[0], ERROR_LEVEL, SECOND_ARGUMENT_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                case_statement(CASE_TYPE, get_next_statement(), statement.commands[1]);
                switch_statement(event_type, get_next_statement(), option_name);
            }
        } else if (!strcmp(statement.commands[0], ENDSWITCH_TYPE)) { //ENDSWITCH_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else { //UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
        }
    }
}

void case_statement(const char* event_type, ssize_t next_statement, char* index) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) {
            case_statement(CASE_TYPE, get_next_statement(), index);
        } else if (!strcmp(statement.commands[0], ENDCASE_TYPE)) {
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else {
            event_interpreter(event_type, next_statement);
            case_statement(event_type, get_next_statement(), statement.commands[1]);
        }
    }
}

void if_statement(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = tokenizer(line);

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) {
            if_statement(IF_TYPE, get_next_statement());
        } else if (!strcmp(statement.commands[0], ENDIF_TYPE)) {
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
        } else {
            event_interpreter(event_type, get_next_statement());
            if_statement(event_type, get_next_statement());
        }
    }
}
