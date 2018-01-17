#include <iostream>
#include <memory.h>
#include <stdio.h>
#include "RFID_Calculation.h"
#include "AutoAndStop.h"

using namespace std;

AutoAndStop::AutoAndStop(){

}

AutoAndStop::~AutoAndStop(){

}

//write later read block
unsigned char AutoAndStop::SWRRD(unsigned char *sbuf){

  RFID_Calculation Bcc;

  sbuf[0] = 0x10;//DLE
  sbuf[1] = 0x02;//STX
  sbuf[2] = 0x53;//Command Class
  sbuf[3] = 0x4F;//Command Code
  sbuf[4] = 0x0E;//Send Sequence
  sbuf[5] = 0x0B;//Data length High
  sbuf[6] = 0x00;//Head Write Block
  sbuf[7] = 0x07;//Function Code
  sbuf[8] = 0x04;//Head Write Block
  sbuf[9] = 0x01;//Write Block Count
  sbuf[10] = 0x05;//Head Read Block
  sbuf[11] = 0x01;//Read Block Count
  sbuf[12] = 0x41;
  sbuf[13] = 0x42;
  sbuf[14] = 0x43;
  sbuf[15] = 0x44;
  sbuf[16] = 0x45;
  sbuf[17] = 0x46;
  sbuf[18] = 0x47;
  sbuf[19] = 0x48;
  sbuf[20] = 0x10;//DLE
  sbuf[21] = 0x03;//ETX

  //bcc calculation
  sbuf[22] = Bcc.Calculation(sbuf,22);
/*
  printf("%x\n", sbuf[0]);
  printf("%x\n", sbuf[1]);
  printf("%x\n", sbuf[2]);
  printf("%x\n", sbuf[3]);
  printf("%x\n", sbuf[4]);
  printf("%x\n", sbuf[5]);
  printf("%x\n", sbuf[6]);
  printf("%x\n", sbuf[7]);
  printf("%x\n", sbuf[8]);
  printf("%x\n", sbuf[9]);
  printf("%x\n", sbuf[10]);
  printf("%x\n", sbuf[11]);
  printf("%x\n", sbuf[12]);
  printf("%x\n", sbuf[13]);
  printf("%x\n", sbuf[14]);
  printf("%x\n", sbuf[15]);
  printf("%x\n", sbuf[16]);
  printf("%x\n", sbuf[17]);
  printf("%x\n", sbuf[18]);
  printf("%x\n", sbuf[19]);
  printf("%x\n", sbuf[20]);
  printf("%x\n", sbuf[21]);
  printf("%x\n", sbuf[22]);
*/


  return *sbuf;
}

//read only
unsigned char AutoAndStop::SREAD(unsigned char *sbuf){

  RFID_Calculation Bcc;

  sbuf[0] = 0x10;
  sbuf[1] = 0x02;//STX
  sbuf[2] = 0x53;//Command Class
  sbuf[3] = 0x4F;//Command Code
  sbuf[4] = 0x0E;//Send Sequence
  sbuf[5] = 0x03;//Data length High
  sbuf[6] = 0x00;//Head Write Block
  sbuf[7] = 0x03;//Function Code
  sbuf[8] = 0x01;//Head Write Block
  sbuf[9] = 0x01;//Write Block Count
  sbuf[10] = 0x10;//Head Read Block
  sbuf[11] = 0x03;//Read Block Count

  //bcc calculation
  sbuf[12] = Bcc.Calculation(sbuf,12);

  return *sbuf;
}

unsigned char AutoAndStop::STOP(unsigned char *sbuf){

  RFID_Calculation Bcc;

  sbuf[0] = 0x10;
  sbuf[1] = 0x02;
  sbuf[2] = 0x69;
  sbuf[3] = 0x6F;
  sbuf[4] = 0x0F;
  sbuf[5] = 0x00;
  sbuf[6] = 0x00;
  sbuf[7] = 0x10;
  sbuf[8] = 0x03;
  sbuf[9] = Bcc.Calculation(sbuf,9);

  //bcc calculation

  return *sbuf;
}
