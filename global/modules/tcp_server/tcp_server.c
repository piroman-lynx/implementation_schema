#include "module.h"
#include "tcp_server.h"

#define MODULE_ERROR(x) TRANSLATION_ERROR("tcp_server", x)

static const struct call_description cout_desc = {
  .call = "<",
  .args = 1,
  .args_array = { "char *ARG" },
  .function = "tcp_server_cout",
};

static const struct call_description cin_desc = {
  .call = ">",
  .args = 1,
  .args_array = { "char *ARG[4096]" },
  .function = "tcp_server_cin",
};

unsigned int tcp_server_exports_list_argc() {
   return 2;
}

struct call_description tcp_server_exports_list_argv(unsigned int export) {
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
  .exports_argc = &tcp_server_exports_list_argc,
  .exports_argv = &tcp_server_exports_list_argv
};

int main(int argc, char* argv){
    MODULE_REGISTER(cli_description);
    return 0;
}
