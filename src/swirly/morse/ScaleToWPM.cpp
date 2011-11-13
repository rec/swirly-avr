#include "swirly/morse/ScaleToWPM.h"
#include "swirly/morse/Parts.h"

namespace swirly {
namespace morse {

static int product(const Parts& x, const Parts& y) {
  return
    x.dash_ * y.dash_ +
    x.dot_ * y.dot_ +
    x.symbolGap_ * y.symbolGap_ +
    x.characterGap_ * y.characterGap_ +
    x.wordGap_ * y.wordGap_;
}

Parts scaleToWPM(float wpm, const Parts& hand, const Parts& referenceWord) {
  Parts p = hand;
  float scale = 60000.0 / product(hand, referenceWord);

  p.dash_ *= scale;
  p.dot_ *= scale;
  p.symbolGap_ *= scale;
  p.characterGap_ *= scale;
  p.wordGap_ *= scale;

  return p;
}

}  // namespace morse
}  // namespace swirly
