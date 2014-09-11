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
    std::cout < in->bytes;
}

