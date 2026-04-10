
#include "shell.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pwd.h>
#include <sys/types.h>
#include "../parser/parser.h" 
#include "../cleanup/cleanup.h"
#include "../commands/commands.h"



void run_shell(void){
        

    char *line = NULL;

    argument_t arguments; // custom struct for the arguments, which has capacity and the char**
    arguments.capacity = 10; // initial capacity


    arguments.args = calloc(arguments.capacity, sizeof(char*)); // allocate it zeroed out

    
    //Get the login name the nice way
    char *login_name = getenv("USER");

    if (!login_name){
        struct passwd *pw = getpwuid(getuid()); // Get the login name the not so nice way

        if(pw)
         login_name = pw->pw_name; // you got it!
        else 
         login_name = "Unknown"; //screw you, you'll have no name
    }

    // get some of that sweet stack storage for the hostname, working directory and the final prompt
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    
    char cwd[1024];
    char prompt[1400];

    
    while (1) {
        
        fflush(stdout);

        
        if (line) {
            free(line); //free the line so we can get the new one with readline
            line = NULL;
        }

        getcwd(cwd, sizeof(cwd)); //get the current working directory

        snprintf(prompt, sizeof(prompt), "%s@%s:%s> ", 
         login_name, hostname, cwd); //format it

        line = readline(prompt); //Read the line with Stallman's magic and also print that formatted string

        if (!line) {
        printf("\n");
        break; // Handle potential UB caused by CTRLD + D with 0 characters
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

        pid_t pid = fork(); // create a duplicate process to handle the execution of the program you want the shell to launch

        if (pid == 0) {
            // For the child process
            execvp(arguments.args[0], arguments.args); // execute the bad boy
            fprintf(stderr, "%s: command not found\n", arguments.args[0]);// in case it doesn't work
            exit(1);
        } 
        else {
            // Make the parent process wait
            waitpid(pid, NULL, 0);
        }
    }
    free(line); // free the char*

    free_content_args(&arguments); // free contents of the dynamically allocated char array
    
    //free the char** itself
    if (arguments.args){
    free(arguments.args);
    arguments.args = NULL;
    }
    
    
}