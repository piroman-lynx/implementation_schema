
#ifndef tcpServer_hpp
#define tcpServer_hpp

#include "module.hpp"

#include <unistd.h>

class tcpServer : public PoolModule {

  protected:
    int serverSocket;

  public:

//    tcpServer ( void ) : PoolModule ( ) {}

    ~tcpServer () {
        close(serverSocket);
    }

    static PoolModule* getInstance();
    virtual void configure(ModuleConfig *config);
    virtual void startPool();

};

#endif
