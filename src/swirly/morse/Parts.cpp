#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

// Points to a member of Parts.
typedef int Parts::*PartPointer;

PartPointer getPartPointer(char ch, bool endOfWord) {
  if (ch == '.')
    return &Parts::dot_;

  if (ch == '-')
    return &Parts::dash_;

  if (ch)
    return &Parts::symbolGap_;

  if (endOfWord)
    return &Parts::wordGap_;

  else
    return &Parts::characterGap_;
}

int* Parts::getPart(char ch, bool endOfWord) {
  return &(this->*getPartPointer(ch, endOfWord));
}

const int* Parts::getPart(char ch, bool endOfWord) const {
  return &(this->*getPartPointer(ch, endOfWord));
}

void Parts::clear() {
  dash_ = dot_ = symbolGap_ = characterGap_ = wordGap_ = 0;
}

void Parts::measure(const char* s, bool endOfWord) {
  for (; *s; ++s)
    measure(*s, endOfWord);
}

void Parts::measure(char c, bool endOfWord) {
  const char* s = symbolString(c);
  do {
    (*getPart(*s, endOfWord))++;
  } while (*(s++));
}

Parts Parts::getDefault() {
  Parts p;

  p.dot_ = 1;
  p.dash_ = 3;
  p.symbolGap_ = 1;
  p.characterGap_ = 3;
  p.wordGap_ = 7;

  return p;
}

Parts Parts::getReferenceWordMeasure() {
  Parts p;

  p.clear();
  p.measure("PARIS", true);

  return p;
}

}  // namespace morse
}  // namespace swirly
