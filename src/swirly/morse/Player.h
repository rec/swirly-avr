#ifndef __REC_SWIRLY_MORSE_PLAYER__
#define __REC_SWIRLY_MORSE_PLAYER__

#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

class Player {
 public:
  Player(const char* s, const Parts& t) : message_(s), timing_(t) {}

  void start() {
    isOn_ = true;
    character_ = message_;
    symbol_ = symbolString(*character_);
  }

  int getTime() const {
    return timing_.*Parts::getPart(*symbol_);
  }

  bool isOn() const { return isOn_; }
  bool atEnd() const { return !*character_; }

  void advance() {
    isOn_ = !isOn_;
    if (!*(symbol_++)) {
      ++character_;
      symbol_ = symbolString(*character_);
    }
  }

  Parts* timing() { return &timing_; }

 private:
  Parts timing_;

  bool isOn_;
  const char* message_;
  const char* character_;
  const char* symbol_;
};


}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PLAYER__
