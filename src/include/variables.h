#include <stdio.h>
#include "definitions.h"

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

// Useful variables
extern int stopPropagation;
extern FILE* eventFile;
extern char* line;
extern size_t strLength;
extern char* next_statement;
extern int lineCount;
extern int returnCall;
extern int nestedIfCount;

// Storage
extern Function funcs[100];
extern Variable vars[100];

extern int funcsCount;
extern int varsCount;

#endif