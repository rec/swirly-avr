#ifndef __REC_SWIRLY_MORSE_PLAYER__
#define __REC_SWIRLY_MORSE_PLAYER__

#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

class Player {
 public:
  Player(const char* msg, float wpm = 10.0);

  void setWPM(float wpm);
  float delay();
  bool advance();

  const Parts& timing() const { return timing_; }
  const char* character() const { return character_; }
  const char* symbol() const { return symbol_; }
  float scale() const { return scale_; }

 private:
  void start();

  void getSymbol();
  bool isOn_;
  bool isEndOfWord_;
  float scale_;

  const char* message_;
  const char* character_;
  const char* symbol_;

  Parts timing_;
  Parts reference_;
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PLAYER__
