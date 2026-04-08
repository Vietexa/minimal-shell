#include <stdio.h>
#include <string.h>
#include "../shell/shell.h"

void parse_cmd(char* line, argument_t *arguments ){ // Parse the input

   line[strcspn(line, "\n")] = 0;

    int i = 0;
    char *token = strtok(line, " ");

    while (token != NULL) {

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

        arguments->args[i++] = token;
        token = strtok(NULL, " ");
    }

    arguments->args[i] = NULL;
    
}