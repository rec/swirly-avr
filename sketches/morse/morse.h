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
  int* getPart(char);
  const int* getPart(char) const;

  // Clear all parts.
  void clear();

  // Return the total number of parts in a character, a string, or a string that
  // represents one word.
  void measure(char);
  void measure(const char*);
  void measureWord(const char*);

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
  p.measure("PARIS ");
  return p;
}

} // namespace morse
} // namespace swirly
# 2 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/Player.h" 1






namespace swirly {
namespace morse {

class Player {
 public:
  Player(const char* msg) : message_(msg) { start(); }

  void advance() {
    isOn_ = !isOn_;
    if (*symbol_)
      ++symbol_;
    else if (*character_)
      symbol_ = symbolString(*++character_);
    else
      start();
  }

  char symbol() const { return *symbol_; }

 private:
  void start() {
    isOn_ = true;
    character_ = message_;
    symbol_ = symbolString(*character_);
  }

  bool isOn_;
  const char* message_;
  const char* character_;
  const char* symbol_;
};







} // namespace morse
} // namespace swirly
# 3 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/PlayerTimer.h" 1



# 1 "./src/swirly/base/base.h" 1



// Macros to disallow various class methods that C++ unfortunately creates
// automatically.  Place either one of these in the private: section of your
// class.

// A macro to disallow the copy constructor and operator= functions.




// A macro to disallow the default constructor, copy constructor and operator=
// functions.
# 5 "./src/swirly/morse/PlayerTimer.h" 2

# 1 "./src/swirly/morse/Player.h" 1
# 7 "./src/swirly/morse/PlayerTimer.h" 2
# 1 "./src/swirly/morse/ScaleToWPM.h" 1





namespace swirly {
namespace morse {

float scaleToWPM(float wpm, const Parts& hand,
                 const Parts& referenceWordMeasure);

} // namespace morse
} // namespace swirly
# 8 "./src/swirly/morse/PlayerTimer.h" 2

namespace swirly {
namespace morse {

class PlayerTimer {
 public:
  PlayerTimer(const char* m, float wpm = 20.0)
      : player_(m), timing_(Parts::getDefault()) {
    setWPM(wpm);
  }

  void setWPM(float wpm) {
    Parts ref = Parts::getReferenceWordMeasure();
    scale_ = scaleToWPM(wpm, timing_, ref);
  }

  void advance() {
    player_.advance();
  }

  int delay() {
    return static_cast<int>(scale_ * (*timing_.getPart(player_.symbol())));
  }

 private:
  Player player_;
  Parts timing_;
  float scale_;

  PlayerTimer(const PlayerTimer&); void operator=(const PlayerTimer&);
};

} // namespace morse
} // namespace swirly
# 4 "sketches/morse/morse.h.in" 2
# 1 "./src/swirly/morse/ScaleToWPM.cpp" 1



namespace swirly {
namespace morse {

static const float MILLISECONDS_PER_SECOND = 1000.0;
static const float SECONDS_PER_MINUTE = 60.0;
static const float MILLISECONDS_PER_MINUTE =
  MILLISECONDS_PER_MINUTE * SECONDS_PER_MINUTE;

static int product(const Parts& x, const Parts& y) {
  return
    x.dash_ * y.dash_ +
    x.dot_ * y.dot_ +
    x.symbolGap_ * y.symbolGap_ +
    x.characterGap_ * y.characterGap_ +
    x.wordGap_ * y.wordGap_;
}

float scaleToWPM(float wpm, const Parts& hand, const Parts& referenceWord) {
  return MILLISECONDS_PER_MINUTE / product(hand, referenceWord);
}

} // namespace morse
} // namespace swirly
# 5 "sketches/morse/morse.h.in" 2
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
  const Character* end = CHARACTERS + (sizeof(ArraySizeHelper(CHARACTERS)));
  if (begin->char_ < ch || end->char_ > ch)
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
# 6 "sketches/morse/morse.h.in" 2

const char* message = "Hello JoMar";
