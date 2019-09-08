#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_statements.c"

int main() {
    eventFile = fopen("test.evnt", "r");

    if(eventFile == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }    

    while ((next_statement = get_next_statement()) != EOF_TYPE) {
        if(!stopPropagation) {
            event_interpreter(EVENT_TYPE, next_statement);
        } else {
            break;
        }
    }

    fclose(eventFile);

    return 0;
}