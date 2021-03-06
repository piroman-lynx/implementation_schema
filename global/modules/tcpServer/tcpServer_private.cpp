#include "tcpServer.hpp"
#include "tcpConnection.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

#include <netdb.h>

PoolModule* tcpServer::getInstance()
{
    return new tcpServer();
}

void tcpServer::configure(ModuleConfig *config)
{
   serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   struct sockaddr_in servaddr;
   struct hostent *server;

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;

   server = gethostbyname(config->getString("host"));
   bcopy((char *)server->h_addr, (char *)&servaddr.sin_addr.s_addr, server->h_length);
   servaddr.sin_port = htons(config->getInteger("port"));

   bind(serverSocket, (struct sockaddr *)&servaddr, sizeof(servaddr));
   listen(serverSocket, 128);
}

void tcpServer::startPool()
{
    for (;;) {
	int clientSocket = accept(serverSocket, 0, 0);
	tcpConnection *conn = (tcpConnection*)tcpConnection::getInstance();
	conn->configure(clientSocket);
    }
}

void tcpServer::startPool(PipeModule* headPassParent)
{
    for (;;) {
	int clientSocket = accept(serverSocket, 0, 0);
	tcpConnection *conn = (tcpConnection*)tcpConnection::getInstance(headPassParent);
	conn->configure(clientSocket);
    }
}
