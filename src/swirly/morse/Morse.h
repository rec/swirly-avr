#ifndef __REC_SWIRLY_MORSE_MORSE__
#define __REC_SWIRLY_MORSE_MORSE__

// Definitions for Morse code, ported from my private JS repo
// https://github.com/rec/private-max

namespace swirly {
namespace morse {


struct Parts {
  int dash_;
  int dot_;
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
