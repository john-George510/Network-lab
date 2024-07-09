#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

void main(){
  char *ip="127.0.0.1";
  int port=87771;
  int server_sock,client_sock;
  struct sockaddr_in server_addr,client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int bind_val;

  server_sock=socket(AF_INET,SOCK_STREAM,0);
  if (server_sock<0)
    perror("socket failed\n");
  printf("socket created\n");

  memset(&server_addr,'\0',sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=port;
  server_addr.sin_addr.s_addr=inet_addr(ip);

  bind_val=bind(server_sock,(struct sockaddr *)&server_addr,sizeof(server_addr));

  if (bind_val<0)
    perror("bind failed\n");

  printf("bind created\n");

  printf("Listening...");
  listen(server_sock,10);

  while(1){
    addr_size=sizeof(client_addr);
    client_sock=accept(server_sock,(struct sockaddr *)&client_addr,&addr_size);
    printf("client connected\n");
    printf("Client IP: %s\n",inet_ntoa(client_addr.sin_addr));
    bzero(buffer,1024);
    recv(client_sock,buffer,sizeof(buffer),0);
    printf("Client :%s\n",buffer);
    strcpy(buffer,"Hello from server");
    printf("Server: %s\n",buffer);
    send(client_sock,buffer,sizeof(buffer),0);
    close(client_sock);
    printf("Client disconnected:");
  }
  close(server_sock);
  printf("Server closed");
}