#include <ctype.h>
#include <string.h>

#include "morse.h"

swirly::morse::Player player("Hello, Jomar");

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(player.delay());
  player.advance();

  digitalWrite(13, LOW);
  delay(player.delay());
  player.advance();
}
