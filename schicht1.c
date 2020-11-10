#include<stdio.h>
#include<unistd.h>
#include<sys/io.h>
#include<stdint.h>

#define COM1PORT 0x03F8
#define COM2PORT 0x02F8

//Fuer Permissions
int turn_on = 1, range = 8;


void writeByte(char toSend){
  int lsr = COM2PORT + 5;

  //fordert die Permission an   
  int exit =  ioperm( COM2PORT ,range ,turn_on);

  if(((lsr >> 5) & 0x01) == 1 && exit == 0){
    outb(toSend, COM2PORT);
  }

}

char readByte(){
  int lsr = COM1PORT + 5;

  //fordert die Permission an   
  int exit =  ioperm( COM1PORT,range ,turn_on);

  if((inb(lsr) & 0x01) == 1){
    return inb(COM1PORT);
  }else{
    return;
  }
}
