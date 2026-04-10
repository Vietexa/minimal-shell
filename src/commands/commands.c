
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../cleanup/cleanup.h"

static void shell_exit(argument_t *args, char *line){
final_cleanup(args, line);
exit(0);
} //cleanup so we can leave

static void change_directory(argument_t *args, char* line){

    char *target;

    if (args->args[1] == NULL) {// if no location specified go home
        target = getenv("HOME"); // get the home env
        if (target == NULL) { // couldn't get it, shit
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    } else {
        target = args->args[1]; // otherwise make the target be that 2nd arg
    }

    if (chdir(target) != 0) {// change the working directory, and if it's not zero print the error
        perror("cd");
    }

}

int check_if_cmd_used_and_call(argument_t *args, char* line){
    //this is self explanatory
    if(strcmp(args->args[0], "exit") == 0){
        shell_exit(args,line);
        return 1;
    }

    else if (strcmp(args->args[0], "cd") == 0){
        change_directory(args,line);
        return 1;

    }


    return 0;
}