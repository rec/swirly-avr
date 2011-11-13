#ifndef __REC_SWIRLY_MORSE_CHARACTERPOSITION__
#define __REC_SWIRLY_MORSE_CHARACTERPOSITION__

// #include <ctype.h>
// #include <string.h>

#include "swirly/morse/Character.h"

namespace swirly {
namespace morse {

// A position within a Character during playback.
// position = 0 means the period in the first symbol
// position = 1 means the gap after the first symbol.
// position = 2 means during the second symbol, etc.

struct CharacterPosition {
  const Character* char_;
  int pos_;

  CharacterPosition() {}
  CharacterPosition(const Character* c, int p = 0) : char_(c), pos_(p) {}

  char get() const { return char_->symbols_[pos_]; }
  int length() const { return char_->length(); }
  bool isDot() const { return get() == '.'; }
  bool isDash() const { return get() == '-'; }
  bool isEnd() const { return !get(); }
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_CHARACTERPOSITION__
