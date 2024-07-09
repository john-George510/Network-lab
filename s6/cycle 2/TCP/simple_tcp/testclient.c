#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

void main(){
  char *ip="127.0.0.1";
  int port=87771;
  int sock,connection_val;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];

  sock=socket(AF_INET,SOCK_STREAM,0);
  if (sock<0)
    perror("socket failed\n");
  printf("socket created\n");

  memset(&addr,'\0',sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_port=port;
  addr.sin_addr.s_addr=inet_addr(ip);

  connection_val=connect(sock,(struct sockaddr *)&addr,sizeof(addr));
  if (connection_val<0){
    perror("connection error");
  }
  printf("connected to server");
  bzero(buffer,1024);
  strcpy(buffer,"Hello from client");
  send(sock,buffer,strlen(buffer),0);
  bzero(buffer,1024);
  recv(sock,buffer,sizeof(buffer),0);
  printf("Server :%s\n",buffer);
  close(sock);
  printf("Disconnected from server");
}