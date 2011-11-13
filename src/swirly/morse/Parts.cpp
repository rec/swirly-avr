#include "swirly/morse/Parts.h"
#include "swirly/morse/CharacterPosition.h"

namespace swirly {
namespace morse {

Parts::Pointer getPart(const CharacterPosition& cp, bool isEndOfWord) {
  if (cp.isDot())
    return &Parts::dot_;

  if (cp.isDash())
    return &Parts::dash_;

  if (!cp.isEnd())
    return &Parts::symbolGap_;

  if (isEndOfWord)
    return &Parts::wordGap_;

  return &Parts::characterGap_;
}

}  // namespace morse
}  // namespace swirly
