Задача:
  Написать глобальный модуль CLI для работы с Command Line Interface

Реализация на C:

    $ cd modules/
    $ cd cli/
    $ cat modules/cli/cli.c
    #include "module.h"
    #include "unistd.h"
    #include "stdio.h"
    
    #define MODULE_ERROR(x) TRANSLATION_ERROR("cli", x)

    static const struct call_description cout_desc = {
      .call = "<",
      .args = 1,
      .arg_0 = "char *",
      .function = cli_cout,
    }
    
    static const struct call_description cin_desc = {
      .call = ">",
      .args = 1,
      .arg_0 = "char[4096] *",
      .function = cli_cin,
    }

    static const struct module_description cli_description = {
      .may_init = 0,
      .must_init = 0,
      .may_finish = 0,
      .must_finish = 0,
      .exports_argc = cli_exports_list_argc
      .exports_argv = cli_exports_list_argv
    };
    
    unsigned int cli_exports_list_argc() {
       return 2;
    }
    
    call_description cli_exports_list_argv(unsigned int export) {
       switch (export) {
          0:
            return cout_desc;
            break;
          1:
            return cin_desc;
            break;
          default:
            MODULE_ERROR("Unknown command");
       }
    }
    
    $ cat modules/cli/functions.c
    
    void cli_cout (char * string) {
      printf("%d\n", string);
    }

    void cli_cin (char[4096] *buffer) {
      read(STDIN_FILENO, buffer, 4096);
    }
    
    $ is-cc cli.c
    $ is-cc functions.c
    $ is-cc makemodule cli.c functions.c
    $ cd ../..
    $ is-cc import-global ./modules/cli
