
void tcp_init(char *host, unsigned int port, int *serverSocket)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = gethostbyname(host);
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) {
	error("ERROR on binding");
    }
    listen(sockfd,5);
    (*serverSocket) = sockfd;
}

void tcp_cout(char *str, int *clientSocket)
{
    
}

void tcp_cin(char *buffer[4096], int *clientSocket)
{
    
}
