#include "module.hpp"

static const struct module_description cli_description = {
    .className = "cli"
};

int main(int argc, char* argv[])
{
    MODULE_REGISTER(cli_description);
}
