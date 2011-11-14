#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <ostream>

#define EMULATION_MODE

#include "morse/morse.h"

int main(int argc, char** argv) {
  swirly::morse::PlayerTimer playerTimer("Hello, Jomar");
  for (int i = 0; i < 20; ++i) {
    printf("%d, ", playerTimer.delay());
    playerTimer.advance();
  }
  printf("\n");
}

