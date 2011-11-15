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
      if (state_ != reading && state_ == HIGH) {
        // running = true;
        callback_();
      }
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

int button1State = HIGH;
int button1Next = button1State;
bool button1Debouncing = false;
long button1Time = 0;

int button2State = HIGH;
int button2Next = button2State;
bool button2Debouncing = false;
long button2Time = 0;


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

  if (false) {
    int state1 = digitalRead(BUTTON1_PIN);

    if (state1 != button1State) {
      button1State = state1;
      if (state1 == LOW)
        button1Press();
    }

    int state2 = digitalRead(BUTTON2_PIN);

    if (state2 != button2State) {
      button2State = state2;
      if (state2 == LOW)
        button2Press();
    }
  } else {
    button1.read(time);
    button2.read(time);
  }

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
