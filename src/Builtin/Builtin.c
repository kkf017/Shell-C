#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Global.h"
#include "../Tools/Tools.h"

void changedir(char **argv, int argc){
    if(argc > 2){
        //exitf("\n[-]ERROR: Unknown command.");
        printf("\n\033[1;91m[-]ERROR: Unknown command.\033[0m");
    }

    if(argc == 1){
        chdir(HOME);
    }else{

        char *path = realpath(*(argv+1), NULL);
        if(path == NULL){
            printf("\n\033[1;91mWARNING: Unknown PATH.\033[0m");

        } else{
            chdir(path);
            free(path);
        }
        
    } 
}


void script(char **argv, int argc){
    // function to read and run script.sh

    // system("./test.sh");
}


void cprogram(char **argv, int argc){
    // function to read and run prog.c

    // system("./test.sh");
}


void unixcorn(char **argv, int argc){
    // customize - create your own command or interpreter/language

    // https://pavanchitneedi.medium.com/how-to-create-custom-commands-in-linux-782b4d52be79
}
