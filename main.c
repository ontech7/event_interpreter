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