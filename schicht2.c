#include"schicht1.h"
#include<stdio.h>
#include<string.h>
#include<sys/io.h>
#include<stdlib.h>

#define PORT 0x03F8


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


char * readFrame(){
  char speicher[257];
  char zwischen;
  int i = 0;
  
  ioperm(PORT , 8 , 1);

  int lsr = PORT + 5;




  int read = 0;
  int zaehler = 0, end = 1;
  int laenge = 0, checksum = 0;
  while(end == 1){
    //kontrolliert ob etwas im Buffer ist
    if((inb(lsr) & 0x01) == 1){
      if(read == 0){
        laenge = inb(PORT);
	speicher[zaehler] = laenge;
        printf("Laenge: %i\n", laenge);
      }else if(zaehler <= laenge){
	zwischen = inb(PORT);
        printf("%c" , zwischen);
	speicher[zaehler] = zwischen;
	fflush(stdout);
      }else if(zaehler == laenge +1 ){
        checksum = inb(PORT);
        end = 0;
        printf("\nChecksumme: %i\n", checksum);
	speicher[zaehler] = checksum;
	return;
      }else{
	end = 0;
	return;
      }
      zaehler++;
      read++;
    }else{
      printf("Nichts im Buffer\n");
      sleep(1);
    }
  }
}



void main(void){
  char send[] = "was los";
  readFrame();
  char * empfangen = readFrame();

//  for(int i = 0; i < strlen(empfangen) ; i++){
//    printf("%c", empfangen[i]);
//  }

}
