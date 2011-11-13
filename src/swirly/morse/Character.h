#ifndef __REC_SWIRLY_MORSE_CHARACTER__
#define __REC_SWIRLY_MORSE_CHARACTER__

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

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_CHARACTER__
