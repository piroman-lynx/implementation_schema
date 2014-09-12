#include "tcpServer.hpp"
#include "tcpConnection.hpp"

static const struct module_description tcpServer_description = {
    .className = "tcpServer"
};

int main(int argc, char* argv[])
{
    MODULE_REGISTER(tcpServer_description);
}
