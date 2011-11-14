#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <ostream>

#define EMULATION_MODE

#include "morse/morse.h"

int main(int argc, char** argv) {
  swirly::morse::Player player("Hello, Jomar");
  for (int i = 0; i < 20; ++i) {
    printf("%d, ", static_cast<int>(player.delay()));
   player.advance();
  }
  printf("\n");
}

