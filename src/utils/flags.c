#include <stdio.h>
#include <string.h>
#include "../include/flags.h"
#include "../include/constants.h"

const char get_flag(const char* logger_level) {
    if(!strcmp(logger_level, TYPE_LEVEL)) {
        return TYPE_FLAG;
    } else if(!strcmp(logger_level, WARNING_LEVEL)) {
        return WARNING_FLAG;
    } else if(!strcmp(logger_level, VALUE_LEVEL)) {
        return VALUE_FLAG;
    } else if(!strcmp(logger_level, ERROR_LEVEL)) {
        return ERROR_FLAG;
    }
}
