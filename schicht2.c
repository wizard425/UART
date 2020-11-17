#include"schicht1.h"
#include<stdio.h>
#include<string.h>
#include<sys/io.h>
#include<stdlib.h>

#define PORT 0x03F8

char speicher[257];

char checkSum(char * toSend){
  char checksum = toSend[0] + toSend[1];
  for( int i = 1; i < strlen(toSend); i++){
    checksum = checksum ^ toSend[i];
  }
  return checkSum;
}



void writeFrame(char *  toSend){
 
  int laenge = strlen(toSend);
  //schickt die Laenge des Frames
  writeByte(laenge);
  printf("Laenge: %i\n", laenge); 
  //schickt den Payload
  for(int i = 0; i < strlen(toSend); i++){
    writeByte(toSend[i]);
  }

  //schickt die Pruefsumme
  writeByte(123); 
}


char* readFrame(){
  char zwischen;
  int i = 0;
  //fordert Permission an  
  ioperm(PORT , 8 , 1);
  //fuer das LSR-Register
  int lsr = PORT + 5;

  int read = 0;
  int zaehler = 0, end = 1;
  int laenge = 0, checksum = 0;
  printf("Waiting...");
  fflush(stdout);
  while(end == 1){
    //kontrolliert ob etwas im Buffer ist
    if((inb(lsr) & 0x01) == 1){
      //ist es das erste Byte, ist es die Laenge
      if(read == 0){
        zwischen = inb(PORT);
	laenge = (int) zwischen;
	speicher[zaehler] = zwischen;
        printf("Laenge: %i\n", speicher[zaehler]);
      }else if(zaehler <= laenge){
	zwischen = inb(PORT);
	speicher[zaehler] = zwischen;
        printf("%c" , speicher[zaehler]);
	fflush(stdout);
      }else if(zaehler == laenge +1 ){
        checksum = inb(PORT);
        end = 0;
	printf("End gesetzt 1\n");
	speicher[zaehler] = checksum;
        printf("Checksumme: %i\n", speicher[zaehler]);
	return;
      }else{
	printf("End gesetzt 2\n");
	end = 0;
	//return;
      }
      zaehler++;
      read++;
    }else{
      printf(".");
      fflush(stdout);
      sleep(1);
    }
  }
  return speicher;
}



void main(void){
 
  readFrame(); 
  printf("Laenge erhalten: %i\n", speicher[0]);

/*  for( int i = 1; i < (int) speicher[0]; i++){
    printf("%c", speicher[i]);
    fflush(stdout);
  }*/

}
