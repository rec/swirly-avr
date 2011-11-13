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

  return &Parts::characterGap_;
}

void Parts::clear() {
  dash_ = dot_ = symbolGap_ = characterGap_ = wordGap_ = 0;
}

void Parts::measure(const char* s) {
  for (; *s; ++s)
    measure(*s);
}

void Parts::measureWord(const char* s) {
  measure(s);
  symbolGap_--;
  wordGap_++;
}

void Parts::measure(char c) {
  if (const Character* ch = Character::find(c)) {
    CharacterPosition cp(ch);
    do {
      ++(this->*Parts::getPart(cp));
      cp.pos_++;
    } while (!cp.isEnd());
  }
}

}  // namespace morse
}  // namespace swirly
