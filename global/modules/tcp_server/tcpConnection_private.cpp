#include "tcpConnection.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

PipeModule* tcpConnection::getInstance(PipeModule* headPassParent) {
    return new tcpConnection(headPassParent);
}

PipeModule* tcpConnection::getInstance() {
    return new tcpConnection();
}

bitPack tcpConnection::cin() {
    if ((long)passParent != 0) {
        return passParent->cin();
    }
    bitPack out;
    out.bytes = new char [4096];
    out.len = read(clientSocket, out.bytes, 4096);
    return out;
}

void tcpConnection::cout(bitPack *in) {
    if ((long)passParent != 0) {
        passParent->cout(in);
        return;
    }
    send(clientSocket, in->bytes, in->len, 0);
}

void tcpConnection::configure(int socket) {
    clientSocket = socket;
}
