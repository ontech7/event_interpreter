#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/definitions.h"
#include "../include/constants.h"
#include "../include/variables.h"

StringExtracted string_extractor(char* s, int index, int stringLen) {
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

char* get_var_name(char* s, int index, int stringLen) {
    int i, j;
    char* varName = (char*)calloc(64, sizeof(char));

    for(i = index+1, j = 0; i < stringLen; i++, j++) {
        if(s[i] == IS_VARIABLE) {
            return varName;
        }
        varName[j] = s[i];
    }

    return varName;
}

char* subs_var(char* s) {
    int i, j;
    int varsIndex = -1;
    int resume_index = 0; 
    int stringLen = strlen(s);
    int varValueLen, varNameLen;
    char* varName;
    char* subs_s = (char*)calloc(64, sizeof(char));

    for(i = 0; i < stringLen; i++) {
        if(s[i] == IS_VARIABLE) {
            varName = get_var_name(s, i, stringLen);
            for(j = 0; j < varsCount; j++) {
                if(!strcmp(vars[j].name, varName)) {
                    varsIndex = j;
                }
            }
            if(varsIndex != -1) {
                resume_index = i;
                break;
            } else {
                return (char*)NOT_FOUND;
            }
        }
        subs_s[i] = s[i];
    }

    if(!strcmp(subs_s, s)) {
        return "EQUAL";
    }

    if(varsIndex != -1) {
        varValueLen = strlen(vars[varsIndex].value[0]);
        varNameLen = strlen(vars[varsIndex].name);

        //Substituting varName to actual varValue
        for(i = resume_index, j = 0; j < varValueLen; i++, j++) {
            subs_s[i] = vars[varsIndex].value[0][j];
        }

        //Copying string after the second special symbol
        for(i = resume_index + varValueLen, j = resume_index + varNameLen + 2; j < stringLen; i++, j++) {
            subs_s[i] = s[j];
        }

        return subs_s;
    } else {
        return s;
    }
}

char* subs_var_recursive(char* s) {
    char* tmp = subs_var(s);
    char* subs_s = subs_var(s);

    if(!strcmp(tmp, "EQUAL")) {
        return s;
    }

    while((tmp = subs_var(tmp)) != "EQUAL") {
        subs_s = subs_var(subs_s);
    }

    return subs_s;
}

char* cpystring(char* s, int left_index, int right_index, int stringLen) {
    int i = 0, j = 0;
    char* tmp = (char*)calloc(right_index+2 - left_index,sizeof(char));

    for(i = left_index; i < right_index+1; i++) {
        tmp[j] = s[i];
        j++;
    }

    return tmp;
}

char* strip(char* s, char delimiter, int stringLen) {
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

char* get_value_type(char* value) {
    if(value[0] >= '0' && value[0] <= '9') {
        return (char*)INTEGER;
    } else {
        return (char*)STRING;
    }
}

int get_value_as_integer(char* value) {
    return atoi(value);
}

char* get_next_statement() {
    lineCount++;
    int next_statement = getline(&line, &strLength, eventFile);

    if(next_statement == -1) {
        return (char*)EOF_TYPE;
    }

    int i, stringSize = strlen(line);
    for(i = 0; i < stringSize; i++) {
        if(line[i] == '\n')
            line[i] = '\0';
    }

    return line;
}

void skip_statements_from_beginning(int to) {
    int i;
    lineCount = 0;
    fseek(eventFile, 0, SEEK_SET);
    for(i = 0; i < to; i++) {
        next_statement = get_next_statement();
    }
}

void logger(const char* event_type, char* command, const char* logger_level, const char* custom_msg) {
	if(DEBUG_MODE == TRUE) {
	    if(get_flag(logger_level) & LOGGER_FLAGS) {
		    if(!strcmp(custom_msg, "")) {
			    printf("%s::%s -> %s\n", event_type, logger_level, command);
            } else {
			    printf("%s::%s -> %s [msg: \"%s\", line: %i]\n", event_type, logger_level, command, custom_msg, lineCount);
            }
        }
    }
}