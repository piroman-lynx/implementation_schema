#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int clientSocket, serverSocket;
struct sockaddr_in servaddr, cliaddr;

void tcp_construct(char *host, unsigned int port)
{
   serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=gethostbyname(host);
   servaddr.sin_port=htons(port);
   
   bind(serverSocket, (struct sockaddr *)&servaddr, sizeof(servaddr));
   listen(serverSocket,1024);
}

void tcp_init(char *host, unsigned int port)
{
   socklen_t clilen;
   clilen=sizeof(cliaddr);
   clientSocket = accept(serverSocket, (struct sockaddr *)&cliaddr, &clilen);
}

void tcp_down()
{
   close(clientSocket);
}

void tcp_cout(char *str)
{
    send(clientSocket, str, strlen(str)+sizeof(char), 0);
}

void tcp_cin(char *buffer[4096])
{
    read(clientSocket, buffer, 4096);
}
