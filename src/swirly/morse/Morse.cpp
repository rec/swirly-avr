#include <cctype>
#include <cstring>

#include "rec/swirly/morse/Morse.h"
#include "rec/swirly/base/ArraySize.h"

namespace swirly {
namespace morse {

static Character CHARACTERS[] = {
  {'!', "- . - . - -"},
  {'"', ". - . . - ."},
  {'$', ". . . - . . -"},
  {'&', ". - . . ."},
  {'(', "- . - - ."},
  {')', "- . - - . -"},
  {'+', ". - . - ."},
  {',', "- - . . - -"},
  {'-', "- . . . . -"},
  {'.', ". - . - . -"},
  {'/', "- . . - ."},
  {'0', "- - - - -"},
  {'1', ". - - - -"},
  {'2', ". . - - -"},
  {'3', ". . . - -"},
  {'4', ". . . . -"},
  {'5', ". . . . ."},
  {'6', "- . . . ."},
  {'7', "- - . . ."},
  {'8', "- - - . ."},
  {'9', "- - - - ."},
  {':', "- - - . . ."},
  {';', "- . - . - ."},
  {'=', "- . . . -"},
  {'?', ". . - - . ."},
  {'@', ". - - . - ."},
  {'\'', ". - - - - ."},
  {'_', ". . - - . -"},
  {'a', ". -"},
  {'b', "- . . ."},
  {'c', "- . - ."},
  {'d', "- . ."},
  {'e', "."},
  {'f', ". . - ."},
  {'g', "- - ."},
  {'h', ". . . ."},
  {'i', ". ."},
  {'j', ". - - -"},
  {'k', "- . -"},
  {'l', ". - . ."},
  {'m', "- -"},
  {'n', "- ."},
  {'o', "- - -"},
  {'p', ". - - ."},
  {'q', "- - . -"},
  {'r', ". - ."},
  {'s', ". . ."},
  {'t', "-"},
  {'u', ". . -"},
  {'v', ". . . -"},
  {'w', ". - -"},
  {'x', "- . . -"},
  {'y', "- . - -"},
  {'z', "- - . ."},
};

const Character* findCharacter(char ch) {
  ch = tolower(cg);
  const Character* begin = CHARACTERS;
  const Character* end = CHARACTERS + arraysize(CHARACTERS);
  if (begin->char_ < ch || end->char_ > ch)
    return NULL;

  while (true) {
    if (begin->char_ == ch)
      return begin;
    if (end->char_ == ch)
      return end;
    const Character* diff = begin + (end - begin) / 2;
    if (diff == begin || diff == end)
      return NULL;
    if (diff->char_ < ch)
      begin = diff;
    else
      end = diff;
  }
}

int nextTiming(const Timing& timing, const Character& ch,
               int position, bool isEndOfWord) {
  if (!(position & 1)) {
    if (ch.symbols_[position] == '.')
      return timing.dot_;
    else
      return timing.dash_;
  }

  if (position < strlen(ch.symbols_) - 1)
    return timing.symbolGap_;

  if (isEndOfWord)
    return timing.wordGap_;

  return timing.characterGap_;
}

}  // namespace morse
}  // namespace swirly
}  // namespace rec
