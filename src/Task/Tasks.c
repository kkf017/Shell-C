#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Tasks.h"
#include "../Tools/Tools.h"
#include "../Signal/Signal.h"
#include "../Processus/Processus.h"

#include "../Builtin/Builtin.h" 



void backgroundTask(char **argv, int argc){
	TPID_T **background = getBackground();
	
	char *SysCall = malloc(sizeof(char) * (5+strlen(*(argv))));
	if (SysCall==NULL){
		exitf("\n\033[0;91m[-]ERROR: Allocation error.\033[0m"); 
	} 
	sprintf(SysCall,"/bin/%s", *(argv));

	//int status;
	pid_t pid = fork();
	push(background, pid);

	printf("\n\033[1;90mPid background: %d\033[0m", pid);
	
	if(pid == 0){
		// process child
		int out = open("/dev/null",O_RDWR);
		dup2(out, 0);
		dup2(out, 1);
		close(out);


        if(strcmp(*argv, "cd") == 0){
                    changedir(argv, argc); 

	    }else{
		    if(execvp(SysCall, argv) == -1){
		    //if(execv(SysCall, argv) == -1){
			    exitf("\n\033[0;91m[-]ERROR: Process execution failed.\033[0m"); 
				    
		    }
        }
	}else if(pid > 0){
		// process parent
		//Background = pid; - push(background, pid)
		
		struct sigaction signalChild; 
		sigfillset(&signalChild.sa_mask);
		signalChild.sa_flags = SA_SIGINFO ;
		signalChild.sa_handler = killBackground;
		sigaction(SIGCHLD, &signalChild, NULL);
		

	}else{
		exitf("\n\033[0;91m[-]ERROR: fork() failed.\033[0m"); 
	}
	free(SysCall);
	SysCall = NULL;
	
	background = NULL;
}

void foregroundTask(char **argv, int argc){
	pid_t *foreground = getForeground();

	char *SysCall = malloc(sizeof(char) * (5+strlen(*(argv))));
	if (SysCall==NULL){
		exitf("\n\033[0;91m[-]ERROR: Allocation error.\033[0m"); 
	} 
	sprintf(SysCall,"/bin/%s", *(argv));

	int status;
	*foreground = fork();

	printf("\n\033[1;90mPid foreground: %d\033[0m", *foreground);
	
	if(*foreground == 0){
		// process child
		
		if(strcmp(*argv, "cd") == 0){
		            changedir(argv, argc);

		}else if(access(*argv, F_OK|X_OK) == 0){
		    //system(*argv); // executable 

		    // execl("/home/amir/Desktop/OSAssignment/script.sh","script.sh",NULL);
		 
		    	if(execv(*argv, argv) == -1){
				    exitf("\n\033[0;91m[-]ERROR: Process execution failed.\033[0m");
			    }            
		}else{
			    if(execv(SysCall, argv) == -1){
				    exitf("\n\033[0;91m[-]ERROR: Process execution failed.\033[0m");
			    }
		}

	}else if(*foreground > 0){
		// process parent
		
		// add signal Ctrl+C
		struct sigaction signalCrtlC;  
		sigemptyset(&signalCrtlC.sa_mask);
		signalCrtlC.sa_flags = SA_RESTART;
		signalCrtlC.sa_handler = exitForeground;
		sigaction(SIGINT, &signalCrtlC, 0);
		
		waitpid(*foreground,&status, 0);
		printf("\n\033[1;90mForeground parent: My child exited with status %d\033[0m\n", status);

	}else{
		exitf("\n\033[0;91m[-]ERROR: fork() failed.\033[0m");
	}
	free(SysCall);
	SysCall = NULL;
	
}



void taskManager(char **argv, int argc, int flag){	
	if(flag){
		backgroundTask(argv, argc);
	}else{
		foregroundTask(argv, argc);
	}	
}


