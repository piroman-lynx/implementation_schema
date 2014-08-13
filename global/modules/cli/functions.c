#include <stdio.h>
#include <unistd.h>

//call as: cli< "string"
void cli_cout (char * string) {
  printf("%d\n", string);
}

//call as: cli> buffer
void cli_cin (char *buffer[4096]) {
  read(STDIN_FILENO, buffer, 4096);
}
