

// #include <ctype.h>
// #include <string.h>

namespace swirly {
namespace morse {

// The definition of a single Morse character.
struct Character {
  // The actual ASCII character, in lower case.
  char char_;

  // A string of symbols from "-", "." and " " (for readability.)
  const char* symbols_;
};

// Find a character definition, or return NULL.
const Character* findCharacter(char ch);

} // namespace morse
} // namespace swirly
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
  const Character* end = CHARACTERS + (sizeof(ArraySizeHelper(CHARACTERS)));
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
} // namespace morse
} // namespace swirly
void setup() {
}
void loop() {
}
