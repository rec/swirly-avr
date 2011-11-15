#include <ctype.h>
#include <string.h>

#include "morse.h"

int NOTE = 1760;

enum Pin {
  BUTTON1_PIN = 2,
  BUTTON2_PIN = 3,
  LED_PIN = 13,
};

enum State {
  ON_OFF,
  LIGHT_SOUND,
  SPEED_UP,
  SLOW_DOWN
};

enum LightSound {
  LIGHT = 1,
  SOUND = 2,
};

int lightSound = LIGHT;

bool running = false;
int state = ON_OFF;

int DEBOUNCE_INTERVAL = 50;

typedef void (*Callback)();

class ButtonDebouncer {
 public:
  ButtonDebouncer(int p, Callback cb) : pin_(p), state_(HIGH), callback_(cb) {}

  void read(unsigned long time) {
    int reading = digitalRead(pin_);
    bool changed = false;
    if (reading != lastState_) {
      debounce_ = time;
    }
    if ((time - debounce_) > DEBOUNCE_INTERVAL) {
      if (state_ != reading && state_ == HIGH)
        callback_();
      state_ = reading;
    }
    lastState_ = reading;
  }

  bool high() const { return state_ == HIGH; }

 private:
  int pin_;
  int state_;
  int lastState_;
  Callback callback_;

  unsigned long debounce_;
};

swirly::morse::Player player("Hello Jomar");

void button1Press() {
  if (state == ON_OFF) {
    running = !running;
  } else if (state == LIGHT_SOUND) {
    if (++lightSound > LIGHT + SOUND)
      lightSound = LIGHT;
  } else if (state == SPEED_UP) {
    player.setScale(player.scale() / 1.5);
  } else {
    player.setScale(player.scale() * 1.5);
  }
}

void button2Press() {
  state = (state < SLOW_DOWN) ? (state + 1) : ON_OFF;
}


ButtonDebouncer button1(BUTTON1_PIN, button1Press);
ButtonDebouncer button2(BUTTON2_PIN, button2Press);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
}

unsigned long nextTime = 0;

int advance(unsigned long time) {
  unsigned long delay = player.delay();
  nextTime = time + delay;
  player.advance();
  return delay;
}

void loop() {
  unsigned long time = millis();

  button1.read(time);
  button2.read(time);

  if (running) {
    if (time >= nextTime) {
      bool light = lightSound & LIGHT;
      bool sound = lightSound & SOUND;
      bool isOn = player.isOn();
      int delay = advance(time);

      if (isOn) {
        if (light)
          digitalWrite(LED_PIN, HIGH);

        if (sound) {
          noTone(9);  // ??
          tone(9, NOTE, delay);
        }
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
