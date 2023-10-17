#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#include "Signal.h"
#include "../Processus/Processus.h"



void exitp(){
	TPID_T **background = getBackground();
	pid_t *foreground = getForeground();
	while(*background != NULL){
		pid_t pid = pop(background);
		kill(pid,SIGKILL);
	}
	kill(*foreground,SIGKILL);
	exit(EXIT_SUCCESS);
}


void  exitForeground(int signal){
	pid_t *foreground = getForeground();
	kill(*foreground,SIGKILL);
}


void exitAll(int signal){
	TPID_T **background = getBackground();	
	pid_t *foreground = getForeground();
	
	while(*background != NULL){
		pid_t pid = pop(background);
		kill(pid,SIGHUP);
	}
	kill(*foreground,SIGHUP);
	
	//nettoyage des zombies
	int status;
	/*while(*background != NULL){
		int pid = pop(background);
		//printf("\nSIGKill %d",pid);
		waitpid(pid,&status, WNOHANG);
	}*/
	//waitpid(background,&status, WNOHANG);
	waitpid(*foreground,&status, WNOHANG);
	
	kill(getpid(),SIGHUP);
	kill(getpid(),SIGKILL);

}

void  killBackground(int signal, siginfo_t *siginfo, void *context){
	int status;
	TPID_T **background = getBackground();
	
	pid_t pid = siginfo->si_pid;
	int flag = in(background, pid);
	
	//printf("\nSIGCHILD killBackGround %d in list of proc (%d) %d, %d.", pid, in(background, pid), getpid(), getppid());
	
	if(flag){
		//display(background);
		pid_t child = popv(background, siginfo->si_pid);
	}
	if(flag){
			
		waitpid(pid,&status, WNOHANG);
		printf("\n\033[1;90mSIGCHILD parent: My child exited with status %d\033[0m\n", status);	
	}
}


