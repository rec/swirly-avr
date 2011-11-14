#include "swirly/morse/Parts.h"
#include "swirly/morse/SymbolString.h"

namespace swirly {
namespace morse {

// Points to a member of Parts.
typedef int Parts::*PartPointer;

PartPointer getPartPointer(char ch) {
  if (ch == '.')
    return &Parts::dot_;

  if (ch == '-')
    return &Parts::dash_;

  if (ch)
    return &Parts::symbolGap_;

  else
    return &Parts::characterGap_;
}

int* Parts::getPart(char ch) {
  return &(this->*getPartPointer(ch));
}

const int* Parts::getPart(char ch) const {
  return &(this->*getPartPointer(ch));
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
  const char* s = symbolString(c);
  do {
    (*getPart(*s))++;
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
  p.measureWord("PARIS");

  return p;
}

}  // namespace morse
}  // namespace swirly
