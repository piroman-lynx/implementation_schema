#ifndef is_cc_module
#define is_cc_module 1

struct call_description {
  const char *call;
  unsigned char args;
  const char *args_array[20];
  const char *function;
};

struct module_description {
/*  unsigned char may_init;
  unsigned char must_init;
  unsigned char may_finish;
  unsigned char must_finish;*/
  unsigned int(*exports_argc)();
  struct call_description(*exports_argv)(unsigned int);
};

//void is_cc_module_explore(struct module_description);

//static const struct module_description *is_cc_module_for_explore;

#define MODULE_REGISTER(x) is_cc_register(x);

#define TRANSLATION_ERROR(moduleName, message) is_cc_call_translation_error(moduleName, message);

#endif
