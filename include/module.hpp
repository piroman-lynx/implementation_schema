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

    static PipeModule* getInstance(PipeModule* headPassParent);
    static PipeModule* getInstance();
    virtual char* cin() = 0;
    virtual void cout(char*) = 0;
};

struct module_description {
    char *className;
};

void is_cc_register(const struct module_description md);

#define MODULE_REGISTER(x) is_cc_register(x);

#define TRANSLATION_ERROR(moduleName, message) is_cc_call_translation_error(moduleName, message);

#endif
