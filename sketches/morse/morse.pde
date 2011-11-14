#include <ctype.h>
#include <string.h>

#include "morse.h"

int NOTE = 1760;
bool LIGHT = true;
bool SOUND = false;

enum Pin {
  BUTTON1_PIN = 2,
  BUTTON2_PIN = 3,
  LED_PIN = 13,
};

swirly::morse::Player player("Hello Jomar");

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
}

unsigned long nextTime = 0;

int advance(unsigned long time) {
  int delay = player.delay();
  nextTime = time + delay;
  player.advance();
  return delay;
 }

void loop() {
  unsigned long time = millis();
  if (time >= nextTime) {
    bool isOn = player.isOn();
    int delay = advance(time);

    if (isOn) {
      if (LIGHT)
        digitalWrite(13, HIGH);

      if (SOUND) {
        noTone(9);  // ??
        tone(9, NOTE, delay);
      }
    } else if (LIGHT) {
      digitalWrite(13, LOW);
    }
  }
}
