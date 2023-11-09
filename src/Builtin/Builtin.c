#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Global.h"
#include "../Tools/Tools.h"

void changedir(char **argv, int argc){
    if(argc > 2){
        //exitf("\n[-]ERROR: Unknown command.");
        printf("\n\033[1;91m[-]ERROR: Unknown command.\033[0m");
    }else{

        if(argc == 1){
            chdir(HOME);
        }else{

            char *path = realpath(*(argv+1), NULL);
            if(path == NULL){
                printf("\n\033[1;91m[-]WARNING: Unknown PATH.\033[0m");

            }else{
                chdir(path);
                free(path);
            } 
        } 
    }
}


void script(char **argv, int argc){
    // function to read and run script.sh

    // system("./test.sh");
    // execlp("/bin/sh","/bin/sh","-c",parameters,NULL);
    // execl("/home/amir/Desktop/OSAssignment/script.sh","script.sh",NULL);
}


void cprogram(char **argv, int argc){
    // function to read and run prog.c
    // execv(*argv, argv)
}


void pyprogram(char **argv, int argc){
    // function to read and run prog.py
    // execv(*argv, argv)
    // execlp("python3", "python3", "/home/kk/Documents/main.py", "- Lilly loves U", (char*) NULL);
}

void perlprogram(char **argv, int argc){
    // function to read and run prog.pl
    // execv(*argv, argv)
    // execlp("python3", "python3", "/home/kk/Documents/main.py", "- Lilly loves U", (char*) NULL);
}


void unixcorn(char **argv, int argc){
    // customize - create your own command or interpreter/language

    // https://pavanchitneedi.medium.com/how-to-create-custom-commands-in-linux-782b4d52be79
}
