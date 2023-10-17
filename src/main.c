#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "Colors/colors.h"
#include "Tools/Tools.h"
#include "String/String.h"
#include "Signal/Signal.h"
#include "Task/Tasks.h"



#define COLOR1 BHMAG //BHCYN 
#define COLOR2 BHGRN //BHYEL 


int main(int argc, char *argv[]){
	char *str;
	size_t n;
	ssize_t size;
	
	int flag;

	char *home = concatenate("/home/", getlogin());
	chdir(home); // get ~ folder
	
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
	
		//read line
		str = NULL;
		n = 0;
		printf("\n\033[%sbash-os\033[0m:\033[%s%s\033[0m$ ",COLOR1, COLOR2,workdir); // change to display actual folder + changedir function
		size = getline(&str, &n, stdin);
		
		//parse line
		if (size == -1){
			exitf("\n[-]ERROR: Command not found.");
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
		
			
		//execute comand		
		taskManager(argV, argC, flag);
			
		
		// reimplementer cd (changedir function) + fonction inexistante dans /bin/
		
		// Signals - gérer Ctrl+C
		
		// custom - colors, font...etc - girly
		
		
		//free (allocated)
		free(str);
		freeS(argV, argC);
		
		sleep(3);
		
	}
	
	return 1;
}
