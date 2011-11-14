#ifndef __REC_SWIRLY_MORSE_PLAYER__
#define __REC_SWIRLY_MORSE_PLAYER__

#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

class Player {
 public:
  Player(const char* msg) : message_(msg) { start(); }

  void advance() {
    isOn_ = !isOn_;
    if (*symbol_)
      ++symbol_;
    else if (*character_)
      symbol_ = symbolString(*++character_);
    else
      start();
  }

  char symbol() const { return *symbol_; }

 private:
  void start() {
    isOn_ = true;
    character_ = message_;
    symbol_ = symbolString(*character_);
  }

  bool isOn_;
  const char* message_;
  const char* character_;
  const char* symbol_;
};

#if 0
  int getPart(const Parts& parts) const {
    return *(parts.getPart(*symbol_));
  }
#endif

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PLAYER__
