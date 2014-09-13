#include "textproto.hpp"

#include <iostream>
#include <stdio.h>

PipeModule* textproto::getInstance(PipeModule* headPassParent) {
    return new textproto(headPassParent);
}

PipeModule* textproto::getInstance() {
    return new textproto();
}

bool textproto::checkEndl(char *buff)
{
    int len = strlen(buff);
    int el = strlen(ENDL);
    int i;
    for (i=el-1; i>=0; i--) {
	if (buff[len-i] != ENDL[el-i]) {
	    return false;
	}
    }
    return true;
}


bitPack textproto::fromBuffer()
{
	bitPack fromBuffer;
	std::size_t pos = buffer.find(ENDL);
	if (pos == std::string::npos) {
	    EXCEPTION;
	}
	fromBuffer.len = (pos+1)*sizeof(char);
	fromBuffer.bytes = new char [fromBuffer.len];
	strcpy(fromBuffer.bytes, buffer.substr(0, pos).c_str());
	buffer = buffer.substr(pos+strlen(ENDL));
	
	pos = buffer.find(ENDL);
	if (pos == std::string::npos) {
	    hasRN = false;
	}
	return fromBuffer;
}

bitPack textproto::cin() {
    if ((long)passParent != 0) {
        if (hasRN) {
	    return fromBuffer();
        }
	
	while (true) {
	    bitPack fromParent = passParent->cin();
	    buffer.append(fromParent.bytes);
	    try {
		bitPack ret = fromBuffer();
		return  ret;
	    } catch (CATCH) {
		//goto next loop iteration
	    }
	}
    }
    bitPack empty;
    empty.bytes = '\0';
    empty.len = 1;
    return empty;
}

void textproto::cout(bitPack* in) {
    if ((long)passParent != 0) {
	bitPack pass;
	pass.len = in->len + sizeof(char)*strlen(ENDL) + sizeof(char);
        pass.bytes = new char [pass.len];
        sprintf(pass.bytes, "%s%s", in->bytes, ENDL);
        passParent->cout(&pass);
	delete pass.bytes;
    }
}

