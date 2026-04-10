#include <stdio.h>
#include <string.h>
#include "../shell/shell.h"

void parse_cmd(char* line, argument_t *arguments ){ // Parse the input

   line[strcspn(line, "\n")] = 0; // remove newline

    int i = 0;
    char *token = strtok(line, " "); // start splitting the string by delimiter

    while (token != NULL) {

        // if i >= capacity then reallocate with double the size
        if (i >= arguments->capacity - 1) {
            size_t new_capacity = arguments->capacity * 2;

            char **tmp = realloc(arguments->args, sizeof(char*) * new_capacity);
            if (!tmp) {
                perror("realloc");
                exit(1);
            }

            arguments->args = tmp;
            arguments->capacity = new_capacity;
        }

        arguments->args[i++] = token; // store the token and then increment
        token = strtok(NULL, " ");
    }

    arguments->args[i] = NULL;
    
}