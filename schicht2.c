#include"schicht1.h"
#include<stdio.h>
#include<string.h>


char checkSum(char * toSend){
  char checksum = toSend[0] ^ toSend[1];
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
  
}

char* readFrame(){
  char speicher[255];
  char zwischen;
  int i = 0;

  while((zwischen = readFrame()) != NULL){
    speicher[i] = zwischen;
    printf("Empfangen: %c\n",zwischen);
    i++;
  }
  return speicher;
}



void main(void){
  char send[] = "was los";
  printf("Laenge1 = %i\n", strlen(send));
  send[strlen(send)] = 0;
  int check = checkSum(send);
  writeFrame(send);
  printf("Checksumme: %i\n", check);

}
