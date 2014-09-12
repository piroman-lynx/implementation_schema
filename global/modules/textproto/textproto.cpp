#include "module.hpp"

static const struct module_description textproto_description = {
    .className = "textproto"
};

int main(int argc, char* argv[])
{
    MODULE_REGISTER(textproto_description);
}
