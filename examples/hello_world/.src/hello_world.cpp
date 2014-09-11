#include "cli.hpp"

int main(int argc, char* argv[]) {
  cli* cli_local = (cli*)cli::getInstance();
char var_1000[] = "Hello world";
bitPack *var_1001 = new bitPack();
var_1001->len = (strlen(var_1000)+1)*sizeof(char);
var_1001->bytes = new char [var_1001->len];
strcpy(var_1001->bytes, var_1000);
  cli_local->cout(var_1001);
}

