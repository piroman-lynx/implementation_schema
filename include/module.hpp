#ifndef is_cc_module_hpp
#define is_cc_module_hpp 1

#include <string>
#include <map>

struct bitPack {
    char *bytes;
    long long len;
};

class ModuleConfig {
 private:
    std::map<std::string, std::string> strings;
    std::map<std::string, int> ints;
 public:
    void setString(const char *name, char *value);
    void setInteger(const char *name, int value);
    const char* getString(const char *name);
    int getInteger(const char *name);
};

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
    virtual bitPack cin() = 0;
    virtual void cout(bitPack*) = 0;
};

class PoolModule {

 public:
    PoolModule ( void ) { }

    static PoolModule* getInstance();
    virtual void configure(ModuleConfig *config) = 0;
    virtual void startPool() = 0;
};

struct module_description {
    const char *className;
};

void is_cc_register(const struct module_description md);

#define MODULE_REGISTER(x) is_cc_register(x);

#define TRANSLATION_ERROR(moduleName, message) is_cc_call_translation_error(moduleName, message);

#endif
