#pragma once
#include <stdlib.h>

typedef struct argument_s {
size_t capacity;
char **args;
} argument_t;

void run_shell(void);


