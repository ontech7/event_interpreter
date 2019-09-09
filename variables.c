#include "utils/variables.h"
#include "utils/constants.h"

// Useful variables
int stopPropagation = FALSE;
FILE* eventFile;
char* next_statement;
char* line = NULL;
int strLength = 0;
int lineCount = 0;

int funcsCount = 0;
int varsCount = 0;

Function funcs[100];
Variable vars[100];