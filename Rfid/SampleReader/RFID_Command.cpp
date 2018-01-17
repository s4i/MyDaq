#include <iostream>
#include <memory.h>
#include "RFID_Calculation.h"
#include "RFID_Command.h"
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

RFID_Command::RFID_Command(){
  //printf("Command Constract\n");
}

RFID_Command::~RFID_Command(){
  //printf("Command Destract\n");
}

void RFID_Command::Initialize(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x49;
  buf[4] = 0x02;
  buf[5] = 0x00;
  buf[6] = 0x00;
  buf[7] = 0x10;
  buf[8] = 0x03;

  buf[9] = Bcc.Calculation(buf,9);

  send(sock,buf,sizeof(buf), 0);
  recv(sock,rebuf,sizeof(rebuf),0);
/*
  for(int i=0;i<30;i++){
    printf("%.2x", rebuf[i]);
  }
  printf("\n");
*/
}

void RFID_Command::GetConfig(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x47;
  buf[4] = 0x04;
  buf[5] = 0x01;
  buf[6] = 0x00;
  buf[7] = 0x0A;
  buf[8] = 0x10;
  buf[9] = 0x03;

  buf[10] = Bcc.Calculation(buf,10);

  write(sock,buf,sizeof(buf));
  read(sock,rebuf,sizeof(rebuf));

  for(int i=0;i<30;i++){
    printf("%.2x", rebuf[i]);
  }
  printf("\n");
}

void RFID_Command::SetConfig(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x43;
  buf[4] = 0x03;
  buf[5] = 0x02;
  buf[6] = 0x00;
  buf[7] = 0x00;//取得タグの設定
  buf[8] = 0x02;
  buf[9] = 0x10;
  buf[10] = 0x00;

  buf[11] = Bcc.Calculation(buf,11);

  send(sock,buf,sizeof(buf),0);
  recv(sock,rebuf,sizeof(rebuf),0);

  for(int i=0;i<30;i++){
    printf("%.2x", rebuf[i]);
  }
  printf("\n");
}

//リーダライタの音を出す
void RFID_Command::BuzzerOn(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x6B;
  buf[4] = 0x05;
  buf[5] = 0x02;
  buf[6] = 0x00;
  buf[7] = 0x00;
  buf[8] = 0x80;
  buf[9] = 0x10;
  buf[10] = 0x03;

  buf[11] = Bcc.Calculation(buf,11);

  send(sock,buf,sizeof(buf),0);
  recv(sock,rebuf,sizeof(rebuf),0);

  if(rebuf[7]==0x00){

  } else {
    cout << "Error:buzzer" << endl;
  }
}

void RFID_Command::BuzzerOff(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x6B;
  buf[4] = 0x05;
  buf[5] = 0x02;
  buf[6] = 0x00;
  buf[7] = 0x00;
  buf[8] = 0x80;
  buf[9] = 0x10;
  buf[10] = 0x03;

  buf[11] = Bcc.Calculation(buf,11);

  send(sock,buf,sizeof(buf),0);
  recv(sock,rebuf,sizeof(rebuf),0);

  if(rebuf[7]==0x00){

  } else {
    cout << "Error:buzzer" << endl;
  }
}

//リーダライタの無線出力をオフ
void RFID_Command::RWPowerOff(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x4D;
  buf[4] = 0x02;
  buf[5] = 0x00;
  buf[6] = 0x00;
  buf[7] = 0x10;
  buf[8] = 0x03;

  buf[9] = Bcc.Calculation(buf,9);

  write(sock,buf,sizeof(buf));
  read(sock,rebuf,sizeof(rebuf));
}

char RFID_Command::GetNoiseLevel(int sock){

  memset(buf,'\0',sizeof(buf));
  memset(rebuf,'\0',sizeof(rebuf));

  RFID_Calculation Bcc;

  buf[0] = 0x10;
  buf[1] = 0x02;
  buf[2] = 0x4D;
  buf[3] = 0x07;
  buf[4] = 0x07;
  buf[5] = 0x00;
  buf[6] = 0x00;
  buf[7] = 0x10;
  buf[8] = 0x03;

  buf[9] = Bcc.Calculation(buf,9);

  write(sock,buf,sizeof(buf));
  read(sock,rebuf,sizeof(rebuf));

  return rebuf[8];
}
char* RFID_Command::INVENTORY(int sock){

  char uid[30];
  char qt[30];

  char* data;

  memset(invent, '\0', sizeof(invent));
  memset(invent, '\0', sizeof(reinvent));
  //memset(uid, '\0', sizeof(uid));

  RFID_Calculation Bcc;

  invent[0]=0x10;
  invent[1]=0x02;
  invent[2]=0x53;
  invent[3]=0x40;
  invent[4]=0x01;
  invent[5]=0x00;
  invent[6]=0x00;
  invent[7]=0x10;
  invent[8]=0x03;

  invent[9]=Bcc.Calculation(invent,9);

  send(sock,invent, sizeof(invent), 0);
  recv(sock,reinvent, sizeof(reinvent), 0);

  sprintf(qt,"%.2x",reinvent[2]);
  //printf("%s\n",qt);

  sprintf(uid, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x", reinvent[8],reinvent[9],reinvent[10],reinvent[11],reinvent[12],reinvent[13],reinvent[14],reinvent[15]);
  data = uid;

/*
  if(reinvent[7] == 0x00){
    i->setText(uid);
  } else {
    i->setText("No Uid Data");
  }
*/
  printf("タグUID: %s\n", data);

  return data;
}
char RFID_Command::WRITE(int sock){

  char data[30];

  memset(invent, '\0', sizeof(invent));
  memset(reinvent, '\0', sizeof(reinvent));
  memset(data, '\0', sizeof(data));

  RFID_Calculation Bcc;

  invent[0]=0x10;
  invent[1]=0x02;
  invent[2]=0x69;
  invent[3]=0x57;
  invent[4]=0x06;
  invent[5]=0x12;
  invent[6]=0x00;
  invent[7]=0x08;
  invent[8]=0x02;
  invent[9]=0x33;
  invent[10]=0x34;
  invent[11]=0x35;
  invent[12]=0x36;
  invent[13]=0x37;
  invent[14]=0x38;
  invent[15]=0x39;
  invent[16]=0x4F;

  invent[17]=reinvent[8];
  invent[18]=reinvent[9];
  invent[19]=reinvent[10];
  invent[20]=reinvent[11];
  invent[21]=reinvent[12];
  invent[22]=reinvent[13];
  invent[23]=reinvent[14];
  invent[24]=reinvent[15];

  invent[25]=0x10;
  invent[26]=0x03;

  invent[27]=Bcc.Calculation(invent,27);

  send(sock,invent,sizeof(invent),0);
  recv(sock,reinvent,sizeof(reinvent),0);

  sprintf(data, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
    reinvent[9],reinvent[10],reinvent[11],reinvent[12],reinvent[13],reinvent[14],reinvent[15],reinvent[16]);
  printf("タグData(書き込み):%s\n", data);

  return reinvent[11];
}
char RFID_Command::STAYQUIET(int sock){

  char data[30];

  memset(invent, '\0', sizeof(invent));
  memset(reinvent, '\0', sizeof(reinvent));
  memset(data, '\0', sizeof(data));

  RFID_Calculation Bcc;

  invent[0]=0x10;
  invent[1]=0x02;
  invent[2]=0x53;
  invent[3]=0x44;
  invent[4]=0x02;
  invent[5]=0x08;
  invent[6]=0x00;
  invent[7]=reinvent[8];
  invent[8]=reinvent[9];
  invent[9]=reinvent[10];
  invent[10]=reinvent[11];
  invent[11]=reinvent[12];
  invent[12]=reinvent[13];
  invent[13]=reinvent[14];
  invent[14]=reinvent[15];
  invent[15]=0x10;
  invent[16]=0x03;

  invent[17]=Bcc.Calculation(invent,17);

  send(sock,invent,sizeof(invent),0);
  recv(sock,reinvent,sizeof(reinvent),0);

  return reinvent[16];
}
