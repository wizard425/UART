#include"schicht1.h"
#include<stdio.h>
#include<string.h>

char checkSum(char * toSend){
  char checksum = xor(toSend[0], toSend[1]);
  for( int i = 1; i < strlen(toSend); i++){
    checksum = xor(checksum, toSend[i]);
  }
  return checkSum;
}

void writeFrame(char *  toSend){
 
  char laenge = (char) strlen(toSend);
  //schickt die Laenge des Frames
  writeByte(laenge);
  
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
  char send[] = "Hallo ihr da";
  int check = checkSum(send);
  writeFrame(send);
  printf("Checksumme: %i\n", check);
  


}
