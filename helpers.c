#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.c"

// Structures
typedef struct{
    char** commands;
    int size;
} Statement;

typedef struct{
    char* string;
    int index;
} StringExtracted;

typedef struct{
    char* name;
    int lineCount;
} Function;

typedef struct{
    char* name;
    char* value;
} Variable;

// Useful variables
int stopPropagation = FALSE;
FILE* eventFile;
char* line = NULL;
size_t strLength = 0;
ssize_t _nxt;
int lineCount = 0;
int callLine = 0;

// Storage
Function funcs[100];
Variable vars[100];

int funcsCount = 0;
int varsCount = 0;

StringExtracted string_extractor(char*, int, size_t);
Statement tokenizer(char*);
char* cpystring(char*, int, int, size_t);
char* strip(char*, char, size_t);
void logger(const char*, char*, const char*, const char*);
ssize_t get_next_statement();

StringExtracted string_extractor(char* s, int index, size_t stringLen) {
    StringExtracted str_ext;

    str_ext.string = (char*)calloc((int)stringLen - index + 1, sizeof(char*));
    str_ext.index = 0;
    int i, j;

    for(i = index+1, j = 0; i < stringLen; i++, j++) {
        if(s[i] == IS_STRING) {
            str_ext.index = i;
            break;
        }
        str_ext.string[j] = s[i];
    }

    return str_ext;
}

Statement tokenizer(char* s) {
    Statement statement;
    StringExtracted str_ext;
    char* s_flushed;
    int i, j, stringLen = strlen(s), whitespaceCount = 0, stringLen_flushed = 0;

    for(i = 0; i < stringLen; i++) {
        if(s[i] == ' ') {
            whitespaceCount++;
        }
    }

    if(whitespaceCount == stringLen) {
        statement.size = 1;
        statement.commands = (char**)calloc(statement.size, sizeof(char*)); 
        statement.commands[0] = (char*)calloc(0, sizeof(char));
        return statement;
    }
            
    s_flushed = strip(s, ' ', stringLen);
    stringLen_flushed = strlen(s_flushed);

    statement.size = 0;
    if(stringLen_flushed > 0) {
        statement.commands = (char**)calloc(++statement.size, sizeof(char*));
        statement.commands[0] = (char*)calloc(64, sizeof(char));
    }

    for(i = 0, j = 0; i < stringLen_flushed; i++, j++) {
        if(s_flushed[i] == IS_STRING){
            str_ext = string_extractor(s_flushed, i, stringLen_flushed);
            statement.commands[statement.size-1] = str_ext.string;
            i = str_ext.index;
            j = -1;
        } else if(s_flushed[i] == IS_COMMENT) {
            // Ignore everything ahead this token
            break;
        } else if(s_flushed[i] == IS_DELIMITER) {
            statement.commands = realloc(statement.commands, sizeof(char*) * ++statement.size);
            statement.commands[statement.size-1] = (char*)calloc(64, sizeof(char));
            j = -1;
        } else {
            statement.commands[statement.size-1][j] = s_flushed[i];
        }
    }

    return statement;
}

char* cpystring(char* s, int left_index, int right_index, size_t stringLen) {
    int i = 0, j = 0;
    char* tmp = (char*)calloc(right_index+2 - left_index,sizeof(char));

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
