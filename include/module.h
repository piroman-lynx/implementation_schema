#ifndef is_cc_module
#define is_cc_module 1


#define MODULE_REGISTER(x) is_cc_register(x);

#define TRANSLATION_ERROR(moduleName, message) is_cc_call_translation_error(moduleName, message);

#endif
