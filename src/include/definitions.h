#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

// Structures
typedef struct {
    char** commands;
    int size;
} Statement;

typedef struct {
    char* string;
    int index;
} StringExtracted;

typedef struct {
    char* name;
    int lineCount;
} Function;

typedef struct {
    char* name;
    char** value;
    char* type;
    int size;
    int isConstant;
} Variable;

//helpers.c
StringExtracted string_extractor(char*, int, int);
Statement tokenizer(char*);
char* cpystring(char*, int, int, int);
char* strip(char*, char, int);
char* subs_var(char*);
char* subs_var_recursive(char*);
void logger(const char*, char*, const char*, const char*);
char* get_var_name(char*, int, int);
char* get_value_type(char*);
int get_value_as_integer(char*);
char* get_next_statement();
void skip_statements_from_beginning(int);

//event_statements.c
void event_interpreter(const char*, char*);
void declare_statement(const char*, char*);
void set_statement(const char*, char*);
void read_statement(const char*, char*);
void add_statement(const char*, char*);
void sub_statement(const char*, char*);
void mul_statement(const char*, char*);
void div_statement(const char*, char*);
void call_statement(const char*, char*, int);
void options_statement(const char*, char*);
void switch_statement(const char*, char*);
void case_statement(const char*, char*);
void if_statement(const char*, char*);
void function_statement(const char*, char*, int);

//skip_statements.c
void function_skip_statement(const char*, char*);
void if_skip_statement(const char*, char*, int);

#endif