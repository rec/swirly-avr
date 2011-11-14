#ifndef __REC_SWIRLY_MORSE_PARTS__
#define __REC_SWIRLY_MORSE_PARTS__

namespace swirly {
namespace morse {

struct Parts {
  int dash_;
  int dot_;
  int symbolGap_;  // Gap between a dot and a dash
  int characterGap_;  // Gap between two characters.
  int wordGap_;  // Gap between two words.

  // Get a pointer to a part.
  int* getPart(char, bool endOfWord);
  const int* getPart(char, bool endOfWord) const;

  // Clear all parts.
  void clear();

  // Return the total number of parts in a character, a string, or a string that
  // represents one word.
  void measure(char, bool endOfWord);
  void measure(const char*, bool endOfWord);

  static Parts getDefault();
  static Parts getReferenceWordMeasure();
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PARTS__
