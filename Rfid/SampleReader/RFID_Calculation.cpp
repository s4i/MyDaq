#include <iostream>
#include <stdlib.h>
#include "RFID_Calculation.h"

using namespace std;

unsigned char RFID_Calculation::Calculation(unsigned char *sbuf, int cnt){
  int i;
  unsigned char Calculation=0;
  for(i=2;i<cnt;i++){
    Calculation ^= sbuf[i];
  }

  return Calculation;
}
