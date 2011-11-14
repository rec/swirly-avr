#include <ctype.h>
#include <string.h>

#include "morse.h"

swirly::morse::PlayerTimer playerTimer("Hello, Jomar");

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(playerTimer.delay());
  playerTimer.advance();

  digitalWrite(13, LOW);
  delay(playerTimer.delay());
  playerTimer.advance();
}
