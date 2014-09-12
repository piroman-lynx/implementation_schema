#include "module.hpp"
#include <string.h>

#define ENDL "\r\n"

#define EXCEPTION throw 10;
#define CATCH int n

class textproto : public PipeModule {

  private:
    bool checkEndl(char* buff);
    bitPack fromBuffer();

  protected:
    std::string buffer;
    bool hasRN;

  public:

    textproto ( PipeModule* headPassParent ) : PipeModule ( headPassParent ) {
	buffer = "";
	hasRN = false;
    }

    textproto ( void ) : PipeModule ( ) {
	buffer = "";
	hasRN = false;
    }

    static PipeModule* getInstance(PipeModule* headPassParent);
    static PipeModule* getInstance();
    virtual bitPack cin();
    virtual void cout(bitPack* in);

};

