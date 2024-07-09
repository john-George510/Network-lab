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
  struct sockaddr_in server_addr,client_addr;
  char buffer[1024];
  socklen_t addr_size;

  sock_fd=socket(AF_INET,SOCK_DGRAM,0);

  if (sock_fd<0){
    perror("[-] Socket error ");
    exit(1);
  }
  printf("[+] UDP server socket created .\n");
  
  memset(&server_addr,'\0',sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(port);
  server_addr.sin_addr.s_addr=inet_addr(ip);

  int bind_val=bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
  if (bind_val<0){
    perror("[-] Bind error ");
    exit(1);
  }
  printf("[+] Bind to the port number :%d\n",port);

  bzero(buffer,1024);
  recvfrom(sock_fd,buffer,1024,0,(struct sockaddr *)&client_addr,&addr_size);
  printf("Data from client:%s",buffer);

  strcpy(buffer,"Data succesfullu recieved");
  printf("(Server) Data to client: %s\n", buffer);
  sendto(sock_fd,buffer,1024,0,(struct sockaddr *)&client_addr,addr_size);

}
