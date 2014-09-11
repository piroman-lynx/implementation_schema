#include <map>

#include "module.hpp"

void ModuleConfig::setString(const char *name, char *value)
{
    strings[name] = value;
}

void ModuleConfig::setInteger(const char *name, int value)
{
    ints[name] = value;
}

const char* ModuleConfig::getString(const char *name)
{
    if (strings.find(name) != strings.end()) {
	return strings[name].c_str();
    }
    return NULL;
}

int ModuleConfig::getInteger(const char *name)
{
    if (ints.find(name) != ints.end()) {
	return ints[name];
    }
    return 0;
}

