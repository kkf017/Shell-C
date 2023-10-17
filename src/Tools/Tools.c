#include <stdio.h>
#include <stdlib.h>




void exitf(char *msg){
  perror(msg); 
  exit(EXIT_FAILURE); 
}
