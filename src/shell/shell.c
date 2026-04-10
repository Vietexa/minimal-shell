
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 
#include "../parser/parser.h" 


void run_shell(void){
        
    char *line = NULL;
    size_t len = 0;

    argument_t arguments;
    arguments.capacity = 10; // initial capacity


    arguments.args = malloc(arguments.capacity * sizeof(char*));

    while (1) {
        
        printf("VTShell> ");
        fflush(stdout);

        getline(&line, &len, stdin);
           

        parse_cmd(line, &arguments);

        if (arguments.args[0] == NULL)
            continue;

        // Exit the shell
        if (strcmp(arguments.args[0], "exit") == 0)
            break;

        pid_t pid = fork();

        if (pid == 0) {
            // For the child process
            execvp(arguments.args[0], arguments.args);
            fprintf(stderr, "%s: command not found\n", arguments.args[0]);
            exit(1);
        } 
        else {
            // Make the parent process wait
            waitpid(pid, NULL, 0);
        }
    }
    free(line);
    free(arguments.args);
}