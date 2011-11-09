#ifndef __REC_SWIRLY_MORSE_MORSE__
#define __REC_SWIRLY_MORSE_MORSE__

// Definitions for Morse code, ported from my private JS repo
// https://github.com/rec/private-max

namespace swirly {
namespace morse {

// The definition of a single Morse character.
struct Character {
  // The actual ASCII character, in lower case.
  char char_;

  // A string of symbols from "-", "." and " " (for readability.)
  const char* symbols_;
};

// Find a character definition, or return NULL.
const Character* findCharacter(char ch);

struct Timing {
  float scale_;  // Overall time scale.

  // All times are in milliseconds.
  int dash_;  // Time length of a dash.
  int dot_;  // Length of a dot.
  int symbolGap_;  // Gap between a dot and a dash
  int characterGap_;  // Gap between two characters.
  int wordGap_;  // Gap between two words.
};

// position = 0 means during the first symbol
// position = 1 means the gap after the first symbol.
// position = 2 means during the second symbol, etc.
int nextTiming(const Timing&, const Character&, int position, bool isEndOfWord);

}  // namespace morse
}  // namespace swirly


#endif  // __REC_SWIRLY_MORSE_MORSE__
