#pragma once
#include <stdlib.h>

typedef struct argument_s {
size_t capacity;
char **args;
} argument_t; // our custom struct

void run_shell(void);


