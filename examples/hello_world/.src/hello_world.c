#include "cli.hpp"

int main(int argc, char* argv[]) {
  cli_local = cli::getInstance();
  cli_local.cout("Hello world");
}

