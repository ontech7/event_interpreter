#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// Event types
const char* EVENT_TYPE = "event";
const char* NAME_TYPE = "name";
const char* DIALOG_TYPE = "dialog";
const char* OPTIONS_TYPE = "options";
const char* TEXT_TYPE = "text";
const char* SWITCH_TYPE = "switch";
const char* CASE_TYPE = "case";
const char* IF_TYPE = "if";
const char* ADDITEM_TYPE = "addItem";
const char* WAIT_TYPE = "wait";
const char* DECLARE_TYPE = "declare";
const char* FUNCTION_TYPE = "function";
const char* VARIABLE_TYPE = "variable";
const char* READ_TYPE = "read";
const char* SET_TYPE = "set";
const char* CALL_TYPE = "call";
const char* EMPTY_TYPE = "";

// Special character check
const char IS_STRING = '"';
const char IS_COMMENT = '#';

// Closure types
const char* ENDOPTIONS_TYPE = "endoptions";
const char* ENDCASE_TYPE = "endcase";
const char* ENDSWITCH_TYPE = "endswitch";
const char* ENDDECLARE_TYPE = "enddeclare";
const char* ENDFUNCTION_TYPE = "endfunction";

// Logger Levels
const char* ERROR_LEVEL = "error";
const char* WARNING_LEVEL = "warning";
const char* TYPE_LEVEL = "type";
const char* VALUE_LEVEL = "value";
const char* UNKNOWN_LEVEL = "unknown";

// Error Messages
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

// Structures
typedef struct{
    char** commands;
    int size;
} Statement;

typedef struct{
    char* name;
    int lineCount;
} Function;

typedef struct{
    char* name;
    char* value;
} Variable;

// Storage
Function funcs[100];
Variable vars[100];

int funcsCount = 0;
int varsCount = 0;

// Useful variables
int stopPropagation = FALSE;
FILE* eventFile;
char* line = NULL;
size_t strLength = 0;
ssize_t _nxt;
int lineCount = 0;
int callLine = 0;

const int DEBUG_MODE = TRUE;

Statement splitv2(char*, char*);
char* cpystring(char*, int, int, size_t);
char* strip(char*, char, size_t);
void logger(const char*, char*, const char*, const char*);
ssize_t get_next_statement();
void event_interpreter(const char*, ssize_t);
void declare_statement(const char*, ssize_t);
void function_skip_statement(const char*, ssize_t);
void set_statement(const char*, ssize_t, Statement);
void read_statement(const char*, ssize_t, Statement);
void call_statement(const char*, ssize_t);
void options_statement(const char*, ssize_t, char*);
void switch_statement(const char*, ssize_t, char*);
void case_statement(const char*, ssize_t, char*);

int main() {
    eventFile = fopen("test.evnt", "r");

    if(eventFile == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }    

    while ((_nxt = get_next_statement()) != -1) {
        if(!stopPropagation) {
            event_interpreter(EVENT_TYPE, _nxt);
        } else {
            break;
        }
    }

    fclose(eventFile);

    return 0;
}

Statement splitv2(char* s, char* delim) {
    Statement statement;
    char real_delim = delim[0];
    int i, j, stringLen = strlen(s), whitespaceCount = 0;

    for(i = 0; i < stringLen; i++) {
        if(s[i] == ' ') {
            whitespaceCount++;
        }
    }

    if(whitespaceCount == stringLen) {
        statement.size = 1;
        statement.commands[0] = "";
        return statement;
    }

    statement.size = 0;
    if(stringLen > 0) {
        statement.commands = (char**)calloc(++statement.size, sizeof(char*));
        statement.commands[0] = (char*)calloc(64, sizeof(char*));
    }

    for(i = 0, j = 0; i < stringLen; i++, j++) {
        if(s[i] == IS_COMMENT)
            break;
        if(s[i] == real_delim) {
            statement.commands = realloc(statement.commands, sizeof(char*) * ++statement.size);
            statement.commands[statement.size-1] = (char*)calloc(64, sizeof(char*));
            j = -1;
            continue;
        }
        statement.commands[statement.size-1][j] = s[i];
    }

    return statement;
}

char* cpystring(char* s, int left_index, int right_index, size_t stringLen) {
    int i = 0, j = 0;
    char* tmp = (char*)calloc(right_index+1 - left_index,sizeof(char));

    for(i = left_index; i < right_index+1; i++) {
        tmp[j] = s[i];
        j++;
    }

    return tmp;
}

char* strip(char* s, char delimiter, size_t stringLen) {
    int i = 0;
    char* tmpStr = (char*)calloc(stringLen,sizeof(char));
    int left_index = 0, right_index = 0;

    for(i = 0; i < stringLen; i++) {
        if(s[i] != ' ') {
            left_index = i;
            break;
        }
    }

    for(i = stringLen-1; i >= 0; i--) {
        if(s[i] != ' ') {
            right_index = i;
            break;
        }
    }

    return cpystring(s, left_index, right_index, stringLen);
}

ssize_t get_next_statement() {
    lineCount++;
    ssize_t next_statement = getline(&line, &strLength, eventFile);
    int i, stringSize = strlen(line);
    for(i = 0; i < stringSize; i++) {
        if(line[i] == '\n')
            line[i] = '\0';
    }
    return next_statement;
}

void logger(const char* event_type, char* command, const char* logger_level, const char* custom_msg) {
	if(DEBUG_MODE == TRUE) {
		if(!strcmp(custom_msg, "")) {
			printf("%s::%s -> %s\n", event_type, logger_level, command);
        } else {
			printf("%s::%s -> %s [msg: \"%s\", line: %i]\n", event_type, logger_level, command, custom_msg, lineCount);
        }
    }
}

void event_interpreter(const char* event_type, ssize_t next_statement) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);
        int i;

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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
        } else if (!strcmp(statement.commands[0], IF_TYPE)) { // IF_TYPE
            logger(event_type, statement.commands[0], TYPE_LEVEL, "");
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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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
            logger(event_type, statement.commands[0], VALUE_LEVEL, "");
        } else {
            vars[varsCount].name = statement.commands[1];
            vars[varsCount].value = statement.commands[2];
            varsCount++;
            logger(event_type, statement.commands[0], VALUE_LEVEL, "");
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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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

        statement = splitv2(line, "_");

        for(i = 0; i < statement.size; i++) {
            statement.commands[i] = strip(statement.commands[i], ' ', strlen(statement.commands[i]));
        }

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