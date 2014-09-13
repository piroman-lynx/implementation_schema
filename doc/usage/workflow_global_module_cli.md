Задача:
  Написать глобальный модуль CLI для работы с Command Line Interface

Реализация на C++:

    $ cd modules/
    $ cd cli/
    $ cat cli.cpp 
    #include "module.hpp"
    
    static const struct module_description cli_description = {
        .className = "cli"
    };
    
    int main(int argc, char* argv[])
    {
        MODULE_REGISTER(cli_description);
    }
    $
    $
    $ cat cli.hpp 
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
    $
    $
    $ cat cli_private.cpp 
    #include "cli.hpp"
    
    #include <iostream>
    #include <stdio.h>
    
    cli* cli::instance = 0;
    
    PipeModule* cli::getInstance(PipeModule* headPassParent) {
        if ((long)instance == 0) {
            instance = new cli(headPassParent);
        }
        return instance;
    }
    
    PipeModule* cli::getInstance() {
        if ((long)instance == 0) {
            instance = new cli();
        }
        return instance;
    }
    
    bitPack cli::cin() {
        if ((long)passParent != 0) {
            return passParent->cin();
        }
        bitPack ret;
        std::string input;
        std::getline (std::cin, input);
        ret.bytes = (char *)input.c_str();
        ret.len = input.size()+1;
        return ret;
    }
    
    void cli::cout(bitPack* in) {
        if ((long)passParent != 0) {
            passParent->cout(in);
            return;
        }
        std::cout << in->bytes;
    }
    $
    $ is-cc cli.cpp
    $ is-cc cli_private.cpp
    $ is-cc makemodule cli.cpp cli_private.cpp
    $ cd ../..
    $ is-cc import-global ./modules/cli
