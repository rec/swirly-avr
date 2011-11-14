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

  // Points to a member of Parts.
  typedef int Parts::*Pointer;

  // Get a pointer to a part.
  static Pointer getPart(const char ch);

  // Clear all parts.
  void clear();

  // Return the total number of parts in a character, a string, or a string that
  // represents one word.
  void measure(char);
  void measure(const char*);
  void measureWord(const char*);

#if 0
  static const Parts& getDefault();
  static const Parts& getReferenceWordMeasure();
#endif
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PARTS__
