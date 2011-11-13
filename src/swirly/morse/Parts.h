#ifndef __REC_SWIRLY_MORSE_PARTS__
#define __REC_SWIRLY_MORSE_PARTS__

namespace swirly {
namespace morse {

class CharacterPosition;

struct Parts {
  int dash_;
  int dot_;
  int symbolGap_;  // Gap between a dot and a dash
  int characterGap_;  // Gap between two characters.
  int wordGap_;  // Gap between two words.

  // Points to a member of Parts.
  typedef int Parts::*Pointer;

  // Get a pointer to a part.
  static Pointer getPart(const CharacterPosition&, bool isEndOfWord = false);
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PARTS__
