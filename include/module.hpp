#ifndef is_cc_module_hpp
#define is_cc_module_hpp 1

class PipeModule {

 protected:
    PipeModule* passParent;

 public:
    PipeModule ( void ) {
	passParent = 0;
    }

    PipeModule ( PipeModule* headPassParent ) {
	passParent = headPassParent;
    }

    virtual PipeModule getInstance(PipeModule* headPassParent) = 0;
    virtual PipeModule getInstance() = 0;
    virtual char* cin() = 0;
    virtual void cout(char*) = 0;
}

struct module_description {
    
};


#define MODULE_REGISTER(x) is_cc_register(x);

#define TRANSLATION_ERROR(moduleName, message) is_cc_call_translation_error(moduleName, message);

#endif
