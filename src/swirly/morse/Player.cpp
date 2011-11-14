#include "swirly/morse/Player.h"
#include "swirly/morse/ScaleToWPM.h"

namespace swirly {
namespace morse {

Player::Player(const char* msg, float wpm)
    : message_(msg),
      timing_(Parts::getDefault()),
      reference_(Parts::getReferenceWordMeasure()) {
  setWPM(wpm);
  start();
}

void Player::setWPM(float wpm) {
  Parts ref = Parts::getReferenceWordMeasure();
  scale_ = scaleToWPM(wpm, timing_, ref);
}

float Player::delay() {
  return scale_ * (*timing_.getPart(*symbol_, isEndOfWord_));
}

bool Player::advance() {
  isOn_ = !isOn_;
  if (*symbol_) {
    ++symbol_;
    return true;
  } else if (*(character_++)) {
    getSymbol();
    return true;
  } else {
    start();
    return false;
  }
}

void Player::start() {
  isOn_ = true;
  isEndOfWord_ = false;
  character_ = message_;
  getSymbol();
}

void Player::getSymbol() {
  symbol_ = symbolString(*character_);
  char c = character_[1];
  bool isSpace = (c == ' ');
  isEndOfWord_ = (c == 0 || isSpace);
  if (isSpace)
    ++character_;
}

}  // namespace morse
}  // namespace swirly
