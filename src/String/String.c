#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../Tools/Tools.h"
#include "String.h"


int count(char *str, ssize_t n){
	char *strCp = malloc(sizeof(char) * n);
	if (strCp==NULL){
		exitf("\n[-]ERROR: Allocation error.");
	}
	strcpy(strCp, str);
	char *token = strtok(strCp, " \n");
	int nbToken = 0;
	while (token != NULL){
		nbToken++;
		token = strtok(NULL, " \n");
	}
	free(strCp);
	strCp = NULL;
	return nbToken;
}

int contains(char *str, char c, ssize_t n){
	char *strCp = malloc(sizeof(char) * n);
	if (strCp==NULL){
		exitf("\n[-]ERROR: Allocation error.");
	}
	strcpy(strCp, str);
	if(*(strCp+(n-2))==c|| *(strCp+(n-2))==c){
		free(strCp);
		strCp = NULL;
		return 1;
	}
	free(strCp);
	strCp = NULL;
	return 0;
}



char **parse(char *str, int n){
	char **argv = malloc((n+1) * sizeof(char *));
	char *token = strtok(str, " \n");
	int i;
	for (i = 0; i < n; i++) {
	    *(argv+i) = malloc(sizeof(char) * (strlen(token)+1));
	    strcpy(*(argv+i), token);
	    token = strtok(NULL, " \n");
	}
	*(argv+i) = NULL;
	return argv;
}

char *concatenate(char *str1, char *str2){
	int i;
	for(i = 0; str2[i] != '\0'; i++);
	char *strCp = malloc(sizeof(char) * (i+strlen(str1)));
	if (strCp==NULL){
		exitf("\n[-]ERROR: Allocation error.");
	}
	strcpy(strCp, str1);
	strcat(strCp, str2);
	return strCp;
}

void freeS(char **arr, int n){
	for (int i = 0; i < n+1; i++){
	    free(*(arr+i)); 
	    *(arr+i) = NULL;
	}
	free(arr);
	arr = NULL;
}
