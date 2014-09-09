#include "module.hpp"

#include "unistd.h"

class tcpConnection : public PipeModule {

  protected:
    int clientSocket;

  public:

    tcpConnection ( PipeModule* headPassParent ) : PipeModule ( headPassParent ) { }
    tcpConnection ( void ) : PipeModule ( ) {}
    ~tcpConnection () {
        close(clientSocket);
    }

    static PipeModule* getInstance(PipeModule* headPassParent);
    static PipeModule* getInstance();
    virtual bitPack cin();
    virtual void cout(bitPack* in);
    void configure(int socket);

};

