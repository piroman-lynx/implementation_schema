#include "module.h"
#include "functions.h"

#define MODULE_ERROR(x) TRANSLATION_ERROR("cli", x)

static const struct call_description cout_desc = {
  .call = "<",
  .args = 1,
  .args_array = { "char *ARG" },
  .function = "cli_cout",
};

static const struct call_description cin_desc = {
  .call = ">",
  .args = 1,
  .args_array = { "char *ARG[4096]" },
  .function = "cli_cin",
};

unsigned int cli_exports_list_argc() {
   return 2;
}

struct call_description cli_exports_list_argv(unsigned int export) {
   switch (export) {
      case 0:
        return cout_desc;
        break;
      case 1:
        return cin_desc;
        break;
      default:
        MODULE_ERROR("Unknown command");
   }
}

static const struct module_description cli_description = {
/*  .may_init = 0,
  .must_init = 0,
  .may_finish = 0,
  .must_finish = 0,*/
  .exports_argc = &cli_exports_list_argc,
  .exports_argv = &cli_exports_list_argv
};

int main(int argc, char* argv){
    MODULE_REGISTER(cli_description);
    return 0;
}
