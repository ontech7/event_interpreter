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
const char* EMPTY_TYPE = "";

// Special character check
const char* IS_STRING = "\"";
const char* IS_COMMENT = "#";

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
const char* UNKNOWN_LEVEL = "unknown";

// Error Messages
const char* COMMANDS_LENGTH = "Too few arguments. Expected at least 2.";
const char* NOT_INSIDE_SWITCH = "'case' statement not inside 'switch'. Error occurred.";
const char* NOT_INSIDE_OPTIONS = "'text' statement not inside 'options'. Error occurred.";
const char* OPTIONS_NOT_FOUND = "'options' used in 'switch' not found: ";
const char* UNKNOWN_COMMAND = "Unknown command. Check your code.";
const char* TEXTFIELD_EMPTY = "'Textfield is empty. Check your code.";

// Useful variables
int stopPropagation = FALSE;
FILE* eventFile;
char* line = NULL;
size_t strLength = 0;
ssize_t _nxt;
int lineCount = 0;

const int DEBUG_MODE = TRUE;

typedef struct{
    char** commands;
    int size;
} Statement;

Statement split(char*, char*);
char* cpystring(char*, int, size_t);
char* lstrip(char*, char, size_t);
void logger(const char*, char*, const char*, const char*);
ssize_t get_next_statement();
void event_interpreter(const char*, ssize_t);
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
    int i, j, stringLen = strlen(s);

    statement.size = 0;
    if(stringLen > 0) {
        statement.commands = (char**)calloc(++statement.size, sizeof(char*));
        statement.commands[0] = (char*)calloc(64, sizeof(char*));
    }

    for(i = 0, j = 0; i < stringLen; i++, j++) {
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

Statement split(char* s, char* delim) {
    char *p = strtok(s, delim);
    Statement statement;

    statement.size = 0;
    statement.commands = NULL;
    
    while (p != NULL)
    {
        statement.commands = realloc(statement.commands, sizeof(char*) * ++statement.size);
        statement.commands[statement.size-1] = p;
        p = strtok (NULL, delim);
    }

    return statement;
}

char* cpystring(char* s, int index, size_t stringLen) {
    int i = 0, j = 0;
    char* tmp = (char*)calloc(stringLen,sizeof(char));

    for(i = index; i < stringLen; i++) {
        tmp[j] = s[i];
        j++;
    }

    return tmp;
}

char* lstrip(char* s, char delimiter, size_t stringLen) {
    int i = 0;
    char* tmpStr = (char*)calloc(stringLen,sizeof(char));

    for(i = 0; i < stringLen; i++) {
        if(s[i] != ' ') {
            tmpStr = cpystring(s, i, stringLen);
            return tmpStr;
        }
    }

    return s;
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

        line = lstrip(line, ' ', statementLength);

        statement = splitv2(line, "_");

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) {
            event_interpreter(event_type, get_next_statement());
        } else if (!strcmp(statement.commands[0], NAME_TYPE)) { // NAME_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], DIALOG_TYPE)) { // DIALOG_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], OPTIONS_TYPE)) { // OPTIONS_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
                options_statement(OPTIONS_TYPE, get_next_statement(), statement.commands[1]);
            }
        } else if (!strcmp(statement.commands[0], SWITCH_TYPE)) { // SWITCH_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
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
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (!strcmp(statement.commands[0], WAIT_TYPE)) { // WAIT_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
                stopPropagation = TRUE;
            } else {
                logger(event_type, statement.commands[0], TYPE_LEVEL, "");
            }
        } else if (statement.commands[0][0] == '#') { //COMMENT
            event_interpreter(event_type, get_next_statement());
        } else { // UNKNOWN_COMMAND
            logger(event_type, statement.commands[0], ERROR_LEVEL, UNKNOWN_COMMAND);
            stopPropagation = TRUE;
        }
    }
}

void options_statement(const char* event_type, ssize_t next_statement, char* option_name) {
    if(!stopPropagation) {
        Statement statement;
        size_t statementLength = strlen(line);

        line = lstrip(line, ' ', statementLength);

        statement = splitv2(line, "_");

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            options_statement(event_type, get_next_statement(), option_name);
        } else if (!strcmp(statement.commands[0], TEXT_TYPE)) {
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
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

        line = lstrip(line, ' ', statementLength);

        statement = splitv2(line, "_");

        if(!strcmp(statement.commands[0], EMPTY_TYPE)) { //EMPTY_TYPE
            switch_statement(event_type, get_next_statement(), option_name);
        } else if (!strcmp(statement.commands[0], CASE_TYPE)) { //CASE_TYPE
            if(statement.size < 2) {
                logger(event_type, statement.commands[0], ERROR_LEVEL, COMMANDS_LENGTH);
                stopPropagation = TRUE;
            } else if (statement.commands[1] == NULL){
                logger(event_type, statement.commands[0], ERROR_LEVEL, TEXTFIELD_EMPTY);
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

        line = lstrip(line, ' ', statementLength);

        statement = splitv2(line, "_");

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
