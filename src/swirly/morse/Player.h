#ifndef __REC_SWIRLY_MORSE_PLAYER__
#define __REC_SWIRLY_MORSE_PLAYER__

#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

struct Player {
  Player(const char* msg) : message_(msg) { start(); }

  void start() {
    isOn_ = true;
    character_ = message_;
    symbol_ = symbolString(*character_);
  }

  int getTime(const Parts& timing) const {
    return *(timing.getPart(*symbol_));
  }

  void advance() {
    isOn_ = !isOn_;
    if (*symbol_) {
      symbol_++;
    } else if (*character_) {
      ++character_;
      symbol_ = symbolString(*character_);
    } else {
      start();
    }
  }

  bool isOn_;
  const char* message_;
  const char* character_;
  const char* symbol_;
};


}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PLAYER__
