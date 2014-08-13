#include "cli.hpp"

    cli::PipeModule ( PipeModule* headPassParent ) {
	config_endl = new char[3];
	strcpy(config_endl, "\r\n");
    }

    cli::PipeModule<PipeModule ( void ) {
	config_endl = new char[3];
	strcpy(config_endl, "\r\n");
    }

    PipeModule cli::getInstance(PipeModule* headPassParent) {
	if ((long)instance == 0) {
	    instance = new PipeModule(headPassParent);
	}
	return instance;
    }

    cli::PipeModule getInstance() {
	if ((long)instance == 0) {
	    instance = new PipeModule();
	}
	return instance;
    }

    char* cli::cin() {
	if ((long)passParent != 0) {
	    return passParent.cin();
	}
	char *buffer;
	cin > buffer;
	return buffer;
    }

    void cli::cout(char* in) {
	char *format = new char[strlen(in)+2];
	bzero(format, (strlen(in)+1+strlen(config_endl))*sizeof(char));
	sprintf(format, "%s%s", in, config_endl);
	if ((long)passParent != 0) {
	    passParent.cout(format);
	    return;
	}
	cout < format;
    }
