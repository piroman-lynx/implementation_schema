#include <iostream>
#include <stdlib.h>
#include <string>

#include "module.hpp"

void is_cc_register(const struct module_description is_cc_module_for_explore)
{
    std::cout << "[module] " << (is_cc_module_for_explore).className << std::endl;
}

void is_cc_call_translation_error(char *moduleName, char *message)
{
    std::cout << "ERROR IN BUILD MODULE: [" << moduleName << "] " << message << std::endl;
    exit(1);
}
