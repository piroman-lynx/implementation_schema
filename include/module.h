
struct call_description {
  const char *call;
  unsigned char args;
  const char *arg_0;
  const char *arg_1;
  const char *arg_2;
  const char *arg_3;
  const char *arg_4;
  const char *arg_5;
  const char *arg_6;
  const char *arg_7;
  const char *arg_8;
  const char *arg_9;
  const char *arg_10;
  const char *arg_11;
  const char *arg_12;
  const char *arg_13;
  const char *arg_14;
  const char *arg_15;
  void* function;
};

struct module_description {
  unsigned char may_init;
  unsigned char must_init;
  unsigned char may_finish;
  unsigned char must_finish;
  void* exports_argc;
  void* exports_argv;
};
