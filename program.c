#include"schicht2.h"
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void main(int argc, char *argv[]){
  char cmd1[] = "-s";
  char cmd2[] = "-r";
  
  for( int i = 0; i < argc; i++){
    printf("%s\n", argv[i]);
  }
}
