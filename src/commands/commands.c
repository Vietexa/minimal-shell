
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../cleanup/cleanup.h"

static void shell_exit(argument_t *args, char *line){
final_cleanup(args, line);
exit(0);
}

static void change_directory(argument_t *args, char* line){

    char *target;

    if (args->args[1] == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    } else {
        target = args->args[1];
    }

    if (chdir(target) != 0) {
        perror("cd");
    }

}

int check_if_cmd_used_and_call(argument_t *args, char* line){

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