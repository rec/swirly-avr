#ifndef __REC_SWIRLY_MORSE_SCALETOWPM__
#define __REC_SWIRLY_MORSE_SCALETOWPM__

#include "swirly/morse/Parts.h"

namespace swirly {
namespace morse {

Parts scaleToWPM(float wpm, const Parts& hand,
                 const Parts& referenceWordMeasure);

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_SCALETOWPM__
