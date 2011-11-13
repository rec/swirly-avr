#ifndef __REC_SWIRLY_MORSE_MORSE__
#define __REC_SWIRLY_MORSE_MORSE__

namespace swirly {
namespace morse {

// position = 0 means during the first symbol
// position = 1 means the gap after the first symbol.
// position = 2 means during the second symbol, etc.
int nextTiming(const Timing&, const Character&, int position, bool isEndOfWord);

}  // namespace morse
}  // namespace swirly


#endif  // __REC_SWIRLY_MORSE_MORSE__
