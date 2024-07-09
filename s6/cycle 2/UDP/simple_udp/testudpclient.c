#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ctype.h>

void main(){
  char *ip="127.0.0.1";
  int port=5553;
  int sock_fd;
  struct sockaddr_in server_addr;
  char buffer[1024];
  socklen_t addr_size;

  sock_fd=socket(AF_INET,SOCK_DGRAM,0);

  if (sock_fd<0){
    perror("[-] Socket error ");
    exit(1);
  }
  printf("[+] UDP client socket created .\n");
  
  memset(&server_addr,'\0',sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(port);
  server_addr.sin_addr.s_addr=inet_addr(ip);


  bzero(buffer,1024);
  strcpy(buffer,"Hello from client\n");
  printf("(Client) Data to Server: %s\n", buffer);
  sendto(sock_fd,buffer,1024,0,(struct sockaddr *)&server_addr,sizeof(server_addr));
  bzero(buffer,1024);
  recvfrom(sock_fd,buffer,1024,0,(struct sockaddr *)&server_addr,&addr_size);
  printf("Data from server:%s",buffer);

  strcpy(buffer,"Data succesfullu recieved");

}
