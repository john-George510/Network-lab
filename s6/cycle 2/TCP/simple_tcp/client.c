/*
    TCP client program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
    char *ip = "127.0.0.1";
    int port = 434527; // should be same as server port
    int sock, connection_status;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-] Socket error ");
        exit(1);
    }
    printf("[+] TCP server socket created .\n");

    memset(&addr, '\0', sizeof(addr)); // clear the addr
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connection_status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (connection_status < 0)
    {
        perror("[-] Connection error ");
        exit(1);
    }
    printf("[+] Connected to the server .\n");
    bzero(buffer, 1024);
    strcpy(buffer, " AMMA ");
    printf(" Client : %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf(" Server : %s\n", buffer);
    close(sock);
    printf(" Disconnected from the server .\n");
}