#include "module.hpp"
#include <string.h>

class cli : public PipeModule {

  protected:
    static cli* instance;

  public:

    cli ( PipeModule* headPassParent ) : PipeModule ( headPassParent ) {
    }

    cli ( void ) : PipeModule ( ) {
    }

    static PipeModule* getInstance(PipeModule* headPassParent);
    static PipeModule* getInstance();
    virtual bitPack cin();
    virtual void cout(bitPack* in);

};

