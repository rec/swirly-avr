# 1 "sketches/morse/morse.h.in"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "sketches/morse/morse.h.in"
# 1 "./src/swirly/morse/Parts.cpp" 1
# 1 "./src/swirly/morse/Parts.h" 1



namespace swirly {
namespace morse {

struct Parts {
  int dash_;
  int dot_;
  int symbolGap_; // Gap between a dot and a dash
  int characterGap_; // Gap between two characters.
  int wordGap_; // Gap between two words.

  // Get a pointer to a part.
  int* getPart(char, bool endOfWord);
  const int* getPart(char, bool endOfWord) const;

  // Clear all parts.
  void clear();

  // Return the total number of parts in a character, a string, or a string that
  // represents one word.
  void measure(char, bool endOfWord);
  void measure(const char*, bool endOfWord);

  static Parts getDefault();
  static Parts getReferenceWordMeasure();
};

} // namespace morse
} // namespace swirly
# 2 "./src/swirly/morse/Parts.cpp" 2
# 1 "./src/swirly/morse/SymbolString.h" 1



namespace swirly {
namespace morse {

// Finds the symbol string corresponding to the Morse character, or the empty
// string if it is not a valid Morse.
const char* symbolString(char);

} // namespace morse
} // namespace swirly
# 3 "./src/swirly/morse/Parts.cpp" 2

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

} // namespace morse
} // namespace swirly
# 2 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/Player.cpp" 1
# 1 "./src/swirly/morse/Player.h" 1






namespace swirly {
namespace morse {

class Player {
 public:
  Player(const char* msg, float wpm = 10.0);

  void setWPM(float wpm);
  float delay();
  bool advance();

  const Parts& timing() const { return timing_; }
  const char* character() const { return character_; }
  const char* symbol() const { return symbol_; }
  float scale() const { return scale_; }

 private:
  void start();

  void getSymbol();
  bool isOn_;
  bool isEndOfWord_;
  float scale_;

  const char* message_;
  const char* character_;
  const char* symbol_;

  Parts timing_;
  Parts reference_;
};

} // namespace morse
} // namespace swirly
# 2 "./src/swirly/morse/Player.cpp" 2
# 1 "./src/swirly/morse/ScaleToWPM.h" 1





namespace swirly {
namespace morse {

float scaleToWPM(float wpm, const Parts& hand,
                 const Parts& referenceWordMeasure);

} // namespace morse
} // namespace swirly
# 3 "./src/swirly/morse/Player.cpp" 2

namespace swirly {
namespace morse {

Player::Player(const char* msg, float wpm)
    : message_(msg),
      timing_(Parts::getDefault()),
      reference_(Parts::getReferenceWordMeasure()) {
  setWPM(wpm);
  start();
}

void Player::setWPM(float wpm) {
  Parts ref = Parts::getReferenceWordMeasure();
  scale_ = scaleToWPM(wpm, timing_, ref);
}

float Player::delay() {
  return scale_ * (*timing_.getPart(*symbol_, isEndOfWord_));
}

bool Player::advance() {
  isOn_ = !isOn_;
  if (*symbol_) {
    ++symbol_;
    return true;
  } else if (*(character_++)) {
    getSymbol();
    return true;
  } else {
    start();
    return false;
  }
}

void Player::start() {
  isOn_ = true;
  isEndOfWord_ = false;
  character_ = message_;
  getSymbol();
}

void Player::getSymbol() {
  symbol_ = symbolString(*character_);
  char c = character_[1];
  bool isSpace = (c == ' ');
  isEndOfWord_ = (c == 0 || isSpace);
  if (isSpace)
    ++character_;
}

} // namespace morse
} // namespace swirly
# 3 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/ScaleToWPM.cpp" 1



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

} // namespace morse
} // namespace swirly
# 4 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/SymbolString.cpp" 1

# 1 "./src/swirly/base/ArraySize.h" 1
// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.




// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.  In these rare
// cases, you have to use the unsafe ARRAYSIZE_UNSAFE() macro below.  This is
// due to a limitation in C++'s template system.  The limitation might
// eventually be removed, but it hasn't happened yet.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
template <typename TypeName, size_t N>
char (&ArraySizeHelper(TypeName (&array)[N]))[N];

// That gcc wants both of these prototypes seems mysterious. VC, for
// its part, can't decide which to use (another mystery). Matching of
// template overloads: the final frontier.

template <typename TypeName, size_t N>
char (&ArraySizeHelper(const TypeName (&array)[N]))[N];




// ARRAYSIZE_UNSAFE performs essentially the same calculation as arraysize,
// but can be used on anonymous types or types defined inside
// functions.  It's less safe than arraysize as it accepts some
// (although not all) pointers.  Therefore, you should use arraysize
// whenever possible.
//
// The expression ARRAYSIZE_UNSAFE(a) is a compile-time constant of type
// size_t.
//
// ARRAYSIZE_UNSAFE catches a few type errors.  If you see a compiler error
//
//   "warning: division by zero in ..."
//
// when using ARRAYSIZE_UNSAFE, you are (wrongfully) giving it a pointer.
// You should only use ARRAYSIZE_UNSAFE on statically allocated arrays.
//
// The following comments are on the implementation details, and can
// be ignored by the users.
//
// ARRAYSIZE_UNSAFE(arr) works by inspecting sizeof(arr) (the # of bytes in
// the array) and sizeof(*(arr)) (the # of bytes in one array
// element).  If the former is divisible by the latter, perhaps arr is
// indeed an array, in which case the division result is the # of
// elements in the array.  Otherwise, arr cannot possibly be an array,
// and we generate a compiler error to prevent the code from
// compiling.
//
// Since the size of bool is implementation-defined, we need to cast
// !(sizeof(a) & sizeof(*(a))) to size_t in order to ensure the final
// result has type size_t.
//
// This macro is not perfect as it wrongfully accepts certain
// pointers, namely where the pointer size is divisible by the pointee
// size.  Since all our code has to go through a 32-bit compiler,
// where a pointer is 4 bytes, this means all pointers to a type whose
// size is 3 or greater than 4 will be (righteously) rejected.
# 3 "./src/swirly/morse/SymbolString.cpp" 2

namespace swirly {
namespace morse {

namespace {

// The definition of a single Morse character.
struct Character {
  // The actual ASCII character, in lower case.
  char char_;

  // A string of symbols from "-", "." and " " (for readability.)
  const char* symbols_;
};

Character CHARACTERS[] = {
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

} // namespace

const char* symbolString(char ch) {
  ch = tolower(ch);
  const Character* begin = CHARACTERS;
  const Character* end = CHARACTERS + (sizeof(ArraySizeHelper(CHARACTERS))) - 1;
  if (begin->char_ > ch || end->char_ < ch)
    return "";

  while (true) {
    if (begin->char_ == ch)
      return begin->symbols_;

    if (end->char_ == ch)
      return end->symbols_;

    const Character* diff = begin + (end - begin) / 2;
    if (diff == begin || diff == end)
      return "";

    if (diff->char_ < ch)
      begin = diff;
    else
      end = diff;
  }
}

} // namespace morse
} // namespace swirly
# 5 "sketches/morse/morse.h.in" 2

const char* message = "Hello JoMar";
