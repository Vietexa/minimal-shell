#include "cleanup.h"


void free_content_args(argument_t *args){ // Free the contents of the arguments array
if (args == NULL || args->args == NULL) return;

for (int i = 0; args->args[i]; i++){
        free(args->args[i]);
        args->args[i] = NULL;
    } 
}   

void final_cleanup(argument_t *args, char* line){
    
    free(line);

    free_content_args(args); // free contents
    
    if (args->args){
    free(args->args);
    args->args = NULL;
    }
    
}