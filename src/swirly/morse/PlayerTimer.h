#ifndef __REC_SWIRLY_MORSE_PLAYERTIMER__
#define __REC_SWIRLY_MORSE_PLAYERTIMER__

#include "swirly/base/base.h"
#include "swirly/morse/Parts.h"
#include "swirly/morse/Player.h"
#include "swirly/morse/ScaleToWPM.h"

namespace swirly {
namespace morse {

class PlayerTimer {
 public:
  PlayerTimer(const char* m, float wpm = 20.0)
      : player_(m), timing_(Parts::getDefault()) {
    setWPM(wpm);
  }

  void setWPM(float wpm) {
    static Parts ref = Parts::getReferenceWordMeasure();
    scale_ = scaleToWPM(wpm, timing_, ref);
  }

  void advance() {
    player_.advance();
  }

  int getTiming() {
    return static_cast<int>(scale_ * (*timing_.getPart(player_.symbol())));
  }

 private:
  Player player_;
  Parts timing_;
  float scale_;

  DISALLOW_COPY_AND_ASSIGN(PlayerTimer);
};

}  // namespace morse
}  // namespace swirly

#endif  // __REC_SWIRLY_MORSE_PLAYERTIMER__
