
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 
#include "../parser/parser.h" 

static void free_args(argument_t *args){ // Free the contents of the arguments array
if (args == NULL || args->args == NULL) return;

for (int i = 0; args->args[i]; i++){
        free(args->args[i]);
        args->args[i] = NULL;
    } 
}   


void run_shell(void){
        
    char *line = NULL;
    size_t len = 0;

    argument_t arguments;
    arguments.capacity = 10; // initial capacity


    arguments.args = calloc(arguments.capacity, sizeof(char*));

    while (1) {
        
        printf("VTShell> ");
        fflush(stdout);

        getline(&line, &len, stdin);

        //free the previous arguments if any
        free_args(&arguments);
           
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

    free_args(&arguments); // free contents
    free(arguments.args);
    arguments.args = NULL;
    
    
}