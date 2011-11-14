#include <ctype.h>
#include <string.h>

#include "morse.h"

int NOTE = 1760;
bool LIGHT = true;
bool SOUND = false;

swirly::morse::Player player("Hello, Jomar");

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  if (LIGHT) {
    digitalWrite(13, HIGH);
  }

  if (SOUND) {
    tone(9, NOTE, player.delay());
  } else {
    delay(player.delay());
  }

  player.advance();
  if (LIGHT) {
    digitalWrite(13, LOW);
  }
  delay(player.delay());
  if (SOUND) {
    noTone(9);
  }
  player.advance();
}
