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

    char* cli::cin() {
	if ((long)passParent != 0) {
	    return passParent->cin();
	}
	char *buffer;
	std::cin > buffer;
	return buffer;
    }

    void cli::cout(char* in) {
	char *format = new char[strlen(in)+2];
	bzero(format, (strlen(in)+1+strlen(config_endl))*sizeof(char));
	sprintf(format, "%s%s", in, config_endl);
	if ((long)passParent != 0) {
	    passParent->cout(format);
	    return;
	}
	std::cout < format;
    }
