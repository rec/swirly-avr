#include "swirly/morse/ScaleToWPM.h"
#include "swirly/morse/Parts.h"

namespace swirly {
namespace morse {

static const float MILLISECONDS_PER_SECOND = 1000.0;
static const float SECONDS_PER_MINUTE = 60.0;
static const float MILLISECONDS_PER_MINUTE =
  MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE;

static int product(const Parts& x, const Parts& y) {
  return
    x.dash_ * y.dash_ +
    x.dot_ * y.dot_ +
    x.symbolGap_ * y.symbolGap_ +
    x.characterGap_ * y.characterGap_ +
    x.wordGap_ * y.wordGap_;
}

float scaleToWPM(float wpm, const Parts& hand, const Parts& referenceWord) {
  int prod = product(hand, referenceWord);
  return MILLISECONDS_PER_MINUTE / (prod * wpm);
}

}  // namespace morse
}  // namespace swirly
