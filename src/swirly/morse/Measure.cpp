#include "rec/swirly/morse/Measure.h"
#include "rec/swirly/morse/Morse.h"

namespace swirly {
namespace morse {

void clear(Parts* p) {
  p->dash_ = p->dot_ = p->symbolGap_ = p->characterGap_ = p->wordGap_ = 0;
}

void measure(const char* s, Parts* p) {
  for (; *s; ++s)
    measure(*s, p);
}

void measure(char c, Parts* p) {
  if (const Character* ch = findCharacter(ch)) {
    for (const char* s = ch->symbols_; *s; ++s)
      switch (*s)
      case '-': p->dot_++;
  }
}

}  // namespace morse
}  // namespace swirly
