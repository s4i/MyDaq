#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "RFID_Connection.h"
#include <arpa/inet.h>

/*変更*/
using namespace std;

RFID_Connection::RFID_Connection(){
  sock = 0;
  ret = 0;
  addr = 0;
  memset(&server_host,'\0',sizeof(server_host));
  memset(&server_addr,'\0',sizeof(server_addr));
}

RFID_Connection::~RFID_Connection(){

}

int RFID_Connection::CreateSocket(char *hostname){
  /*各リーダライタのソケットを作成*/
  if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
    printf("error: socket %s \n", hostname);
    exit(1);
  }

  /*アドレス構造体を作成　IP(ホスト名)で対応可*/
  if((addr = inet_addr(hostname)) == INADDR_NONE){
    if((server_host = gethostbyname2(hostname,AF_INET)) == NULL){
      return -1;
    }
    server_addr.sin_family = server_host->h_addrtype;
    server_addr.sin_port = htons(PORT);
    memcpy(&(server_addr.sin_addr),server_host->h_addr,server_host->h_length);
  } else {
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = addr;
  }

  /*各リーダライタの接続確立*/
  while(1){
    ret = connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret<0){
      printf("%s:Connect Error!!\n",hostname);
      sleep(2);
      close(sock);
      CreateSocket(hostname);
    } else {
      printf("%s:Connect Complete!!\n", hostname);
      break;
    }
  }

  /*ソケットディスクリプトの返し*/
  return sock;
}

int RFID_Connection::AcceptConnection(int ssock){

  int csock;
  struct sockaddr_in client_addr;
  unsigned int clen;

  clen = sizeof(client_addr);

  csock = accept(ssock,(struct sockaddr *) &client_addr, &clen);

  return csock;
}
