#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#include "Processus.h"

TPID_T *BACKGROUND = NULL; 
pid_t FOREGROUND;


pid_t *getForeground(){
	return &FOREGROUND;
}


TPID_T **getBackground(){
	return &BACKGROUND;
}


void push(TPID_T **first,pid_t n){

	TPID_T *new = malloc(sizeof(TPID_T));
	
	if(new == NULL){
		exit(EXIT_FAILURE);
	}
	
	new->element = n;
	new->next = NULL;
	
	new->next = *first;
	*first = new;

}//end insert


int pop(TPID_T **first){
	TPID_T *actual = *first;
	TPID_T *delete = actual;
	
	int value = actual->element;
	*first = (*first)->next;
	
	free(delete);
	
	return value;
		
}//end pop

int popv(TPID_T **first, pid_t n){
	TPID_T *actual = *first;
	
	int value = 0;
	if(actual->element == n){
		int value = actual->element;
		free(actual);
		actual = NULL;
		return value;
		
	}

	while(actual->next->element != n){
		actual = actual->next;
	}
	
	value = actual->next->element;
	TPID_T *delete = actual->next;
	actual->next = actual->next->next;
	
	free(delete);
	
	return value;	
}//end delete


int in(TPID_T **first, pid_t n){
	TPID_T *actual = *first;
	
	if(*first == NULL){
		exit(EXIT_FAILURE);
	}
	while(actual != NULL){
		if(actual->element == n){
			return 1;
		}
		actual = actual->next;
	}
	return 0;

}//end contains



void clear(TPID_T **first){
	TPID_T *actual = *first;
	
	if(*first == NULL){
		exit(EXIT_FAILURE);
	}
	
	
	while(actual->next != NULL){
		TPID_T *delete = actual;
		actual = actual->next;
		free(delete);		
	}		
	TPID_T *delete = actual;
	actual = NULL;
	free(delete);	
	
}//end clear


void display(TPID_T **first){
	TPID_T *actual = *first;
	
	if(*first == NULL){
		//exit(EXIT_FAILURE);
		printf("\nElement: %p", NULL);
	}
	
	printf("%s", "\n");
	while(actual != NULL){
		printf("\nElement: %d", actual->element);
		actual = actual->next;
	}
}//end display
