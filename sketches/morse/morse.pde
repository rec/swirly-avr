#include <ctype.h>
#include <string.h>

#include "morse.h"

int NOTE = 1760;
bool LIGHT = true;
bool SOUND = !false;

enum Pin {
  BUTTON1_PIN = 2,
  BUTTON2_PIN = 3,
  LED_PIN = 13,
};

bool running = false;

int button1State = HIGH;
int button1Next = button1State;
bool button1Debouncing = false;
int button1Time = 0;

int DEBOUNCE_INTERVAL = 50;

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

  int state = digitalRead(BUTTON1_PIN);

  if (state != button1State) {
    button1State = state;
    if (state == LOW)
      running = !running;
  }

  if (running) {
    if (time >= nextTime) {
      bool isOn = player.isOn();
      int delay = advance(time);

      if (isOn) {
        if (LIGHT)
          digitalWrite(LED_PIN, HIGH);

        if (SOUND) {
          noTone(9);  // ??
          tone(9, NOTE, delay);
        }
      } else if (LIGHT) {
        digitalWrite(LED_PIN, LOW);
      }
    }
  } else {
    if (LIGHT)
      digitalWrite(LED_PIN, LOW);
  }
}

/*
  } else
  if (button1Debouncing) {
    if (time >= button1Time) {
      // Button was changed!
      button1State = state;
      button1Debouncing = false;
      if (state == LOW)
        running = !running;
    }
  } else  if (state == button1State) {
    button1Debouncing = false;

  } else {
    button1Debouncing = true;
    button1Time = time + DEBOUNCE_INTERVAL;
    button1State = state;
  }
*/
