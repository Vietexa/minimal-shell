#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../shell/shell.h"

void parse_cmd(char* line, argument_t *arguments ){ // Parse the input

    int i = 0;
    int in_quotes = 0;
    char quote_char = 0;

    char *buffer = malloc(strlen(line) + 1);
    int buf_idx = 0;

    for (int j = 0; line[j]; j++) {
        char c = line[j];

        if (c == '\\') {  
            // Escape next character
            if (line[j + 1]) {
                buffer[buf_idx++] = line[++j];
            }
        }
        else if (c == '"' || c == '\'') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = c;
            } else if (quote_char == c) {
                in_quotes = 0;
            } else {
                buffer[buf_idx++] = c;
            }
        }
        else if (isspace(c) && !in_quotes) {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';

                // Resize if needed
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

                arguments->args[i++] = strdup(buffer);
                buf_idx = 0;
            }
        }
        else {
            buffer[buf_idx++] = c;
        }
    }

    // Last argument
    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        arguments->args[i++] = strdup(buffer);
    }

    arguments->args[i] = NULL;
    free(buffer);
    
}