#include "module.hpp"
#include <string.h>

class cli : public PipeModule {

  protected:
    static cli* instance;
    char* config_endl;

  public:

    cli ( PipeModule* headPassParent ) : PipeModule ( headPassParent ) {
	config_endl = new char[3];
	strcpy(config_endl, "\r\n");
    }

    cli ( void ) : PipeModule ( ) {
	config_endl = new char[3];
	strcpy(config_endl, "\r\n");
    }

    static PipeModule* getInstance(PipeModule* headPassParent);
    static PipeModule* getInstance();
    virtual char* cin();
    virtual void cout(char* in);

};
