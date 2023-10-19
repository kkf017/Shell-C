#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "Global.h"

#include "Tools/Tools.h"
#include "String/String.h"
#include "Signal/Signal.h"
#include "Task/Tasks.h"


void shell(){
	char *str;
	size_t n;
	ssize_t size;
	
	int flag;

	//char *home = concatenate("/home/", getlogin());
	chdir(HOME); // get ~ folder
	
	// Ignore SIGQUIT et SIGTERM
	struct sigaction signalIgnore;  
	sigemptyset(&signalIgnore.sa_mask);
	signalIgnore.sa_flags = SA_RESTART ;
	signalIgnore.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signalIgnore, 0); 
	sigaction(SIGTERM, &signalIgnore, 0);
	

	// Manage SIGHUP - signal
	struct sigaction signalClose;  
	sigemptyset(&signalClose.sa_mask);
	signalClose.sa_flags = SA_RESTART ;
	signalClose.sa_handler = exitAll;
	sigaction(SIGHUP, &signalClose, NULL);


	while(1){
		char *workdir = getcwd(NULL, 0);
	
		str = NULL;
		n = 0;
		printf("\n\033[%s%s\033[0m:\033[%s%s\033[0m$ ",COLOR1, USER, COLOR2,workdir); 
		size = getline(&str, &n, stdin);
		

		if (size == -1){
			exitf("\n\033[0;91m[-]ERROR: Command not found.\033[0m.");
		}			

		int argC = count(str, size);	
		flag = contains(str, '&', size);
	
		if(flag){
			argC -= 1;
		}
			
		char **argV = parse(str, argC);
		/*for (int i = 0; i < argC+1; i++){
			printf("\nargV %d: %s",i,*(argV+i));
		}*/
			
		if(strcmp(*argV, "exit") == 0){
			exitp();
		}
		
	
		taskManager(argV, argC, flag); 
			
		
		// implement cd (changedir function) - /bin/ function is not working
                // could be executable (from changedir function) - to call with execv

        	// implement non-existent function in  /bin/

		
		// Signals - manage Ctrl+C, ENTER
		
		// custom - colors, font...etc -

        	/* Not working:
		        press tab to get full path
		        execute script.sh
		        history command
		        sudo apt-get install
                */

		
		//free (allocated)
		free(str);
		freeS(argV, argC);
		
		//sleep(1);
		
	}
}


int main(int argc, char *argv[]){

    shell();
    return 1;
}
