
#include "shell.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../parser/parser.h" 
#include "../cleanup/cleanup.h"
#include "../commands/commands.h"


void run_shell(void){
        

    char *line = NULL;

    argument_t arguments;
    arguments.capacity = 10; // initial capacity


    arguments.args = calloc(arguments.capacity, sizeof(char*));


    while (1) {
        
        fflush(stdout);

        if (line) {
            free(line);
            line = NULL;
        }

        line = readline("VTShell>");

        if (!line) {
        printf("\n");
        break;
}

    if (*line) {
        add_history(line);
    }
        //free the previous arguments if any
        free_content_args(&arguments);
           
        parse_cmd(line, &arguments);

        if (arguments.args[0] == NULL)
            continue;

        // Exit the shell
       if (check_if_cmd_used_and_call(&arguments,line)){
        continue;
       }

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

    free_content_args(&arguments); // free contents
    
    if (arguments.args){
    free(arguments.args);
    arguments.args = NULL;
    }
    
    
}