#include"schicht1.h"
#include<stdio.h>
#include<string.h>
#include<sys/io.h>
#include<stdlib.h>
#include<unistd.h>

#define PORT 0x03F8

/*
  Die Methode berechnet die Checksumme
  des ihr übergebenen Array indem es
  Byte für Byte xor verknüpft
  (Byte1 xor Byte2 xor Byte3 ...)
*/
char getCheckSum(char * arr){
  int checksummettl = arr[0];
  //checkt bitweise die Pruefsumme mit XOR
  for(int i = 1 ;i < strlen(arr) -1 ; i++){
    checksummettl = checksummettl ^ arr[i];
  }
  return checksummettl;
}


/*
  Die Methode schreibt das ihr
  übergebene Array in den entsprechenden
  Port
*/
void writeFrame(char * toSend){
  ioperm(PORT , 8 , 1);
 
  int laenge = strlen(toSend);
  //schickt die Laenge des Frames
  writeByte(laenge);
  printf("Laenge: %i\n", laenge); 

  //schickt den Payload
  for(int i = 0; i < strlen(toSend); i++){
    writeByte(toSend[i]);
  }

  //schickt die Pruefsumme
  char checkSumme = getCheckSum(toSend);
  printf("Checksumme. %i\n", checkSumme);
  writeByte(checkSumme); 
}



/*
  Die Methode schreibt den erhaltenen Frame 
  in die ihr übergebene Addresse
*/
void readFrame(char * speicher){
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
      if(zaehler == 0){
        zwischen = inb(PORT);
	laenge = (int) zwischen;
	speicher[zaehler] = zwischen;
      }else if(zaehler <= laenge){
	zwischen = inb(PORT);
	speicher[zaehler] = zwischen;
      }else if(zaehler == laenge +1 ){
        checksum = inb(PORT);
        end = 0;
	speicher[zaehler] = checksum;
      }else{
	end = 0;
      }
      zaehler++;
    }else{
      usleep(500);
    }
  }
}
