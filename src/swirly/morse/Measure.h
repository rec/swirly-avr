#ifndef __REC_SWIRLY_MORSE_MEASURE__
#define __REC_SWIRLY_MORSE_MEASURE__

#include "swirly/Morse/Morse.h"

namespace swirly {
namespace morse {

// Return the total number of parts in a string.
void clear(Parts*);
void measure(char, Parts*);
void measure(const char*, Parts*);

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_MEASURE__
