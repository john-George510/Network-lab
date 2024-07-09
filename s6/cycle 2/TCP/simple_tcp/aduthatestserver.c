#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 12345

int main(){
  printf("Hello");

  struct sockaddr_in servaddr, cli;
  char buffer[1024];
  int sock, len,conn;
printf("Hello");
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
    printf("SOcket Creation Error");
  printf("Hello");
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  if(bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    printf("Bind Error");
  
  listen(sock, 5);

  len = sizeof(cli);
  printf("Hello");
  if(conn = accept(sock, (struct sockaddr*)&cli, &len) < 0);
    printf("Connection Failed");
  bzero(buffer, sizeof(buffer));
  read(conn, buffer, sizeof(buffer));
  int i = 0, j = strlen(buffer) - 1;
        while (i < j)
        {
            if (buffer[i] != buffer[j])
            {
                strcpy(buffer, "NOT PALINDROME");
                break;
            }
            i++;
            j--;
        }
        if (i >= j)
        {
            strcpy(buffer, "PALINDROME");
        }
        printf(" Server : %s\n", buffer);
        send(conn, buffer, strlen(buffer), 0);
        close(conn);
        printf("[+] Client disconnected.\n\n");
    

}