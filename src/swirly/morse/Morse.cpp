#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

#define EMULATION_MODE

#include "morse/morse.h"

namespace swirly {
namespace morse {

int main(int argc, char** argv) {
  Player player("Hello, Jomar");
  const Parts& t = player.timing();
  std::cout << "Parts: "
            << " dash_ = " << t.dash_
            << " dot_ = " << t.dot_
            << " symbolGap_ = " << t.symbolGap_
            << " characterGap_ = " << t.characterGap_
            << " wordGap_ = " << t.wordGap_
            << "\n";

  std::cout << "scale: " << player.scale() << "\n"\;

  do {
    std::cout << "Player: "
              << player.delay() << ", "
              << player.character() << ", "
              << player.symbol() << "\n";
  } while (player.advance());
}

}  // namespace morse
}  // namespace swirly

int main(int argc, char** argv) { return swirly::morse::main(argc, argv); }
