#include <stdio.h>
#include "utils/definitions.h"

#ifndef _VARIABLES_H_
#define _VARIABLE_H_

// Useful variables
extern int stopPropagation;
extern FILE* eventFile;
extern char* line;
extern int strLength;
extern char* next_statement;
extern int lineCount;

// Storage
extern Function funcs[100];
extern Variable vars[100];

extern int funcsCount;
extern int varsCount;

#endif