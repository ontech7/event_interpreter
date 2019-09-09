#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/definitions.h"
#include "include/constants.h"
#include "include/variables.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Too few arguments. Must be 2. Error occurred.\n");
        exit(EXIT_FAILURE);
    }

    eventFile = fopen(argv[1], "r");

    if(eventFile == NULL) {
        printf("Error while opening the file.\n");
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
