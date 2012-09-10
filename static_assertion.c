/* -----------------------------------------------------------------------------
static_assertion.c
Silly test for a C89 compile time assertion mechanism. For C++, see the
BOOST_STATIC_ASSERT_MSG() implementation.

Success case:
  gcc -std=c89 -Wall -Wextra -Werror -ansi -pedantic -DTEST_TRUE static_assertion.c

Failure case:
  gcc -std=c89 -Wall -Wextra -Werror -ansi -pedantic static_assertion.c

Copyright 2012 Stephen Niedzielski. Licensed under GPLv3.
----------------------------------------------------------------------------- */

/* Name the parameter "static_assert" to give more context for the failure. Use
   a function declaration instead of an extern variable to avoid unused variable
   warnings. Add "msg" for compatibility with GCC's builtin static_assert
   keyword.

   C and C++ prohibit statements at file scope and pedantic C requires any local
   declarations occur prior to statements. As such, this macro cannot work in
   both scopes seamlessly. In the latter case, you must wrap it in brackets
   should it appear after statements have been made. */
#define static_assert(x, msg) int static_assert(int static_assert[(x)?1:-1])

/* -------------------------------------------------------------------------- */

/* Test file scope. */
static_assert(1 || 0, "static_assert() malfunction!");
static_assert(1 | 0, "static_assert() malfunction!");
#ifndef TEST_TRUE
  static_assert(sizeof(long) == sizeof(char),"sizeof(long) != sizeof(char))");
  static_assert(1 - 2 > 0, "-1 < 0");
#endif

int main()
{
  /* Test local scope. */
  static_assert((sizeof(char) + 1) == 2, "static_assert() malfunction!");
  static_assert(5 - 3, "static_assert() malfunction!");
  #ifndef TEST_TRUE
    static_assert(0, "0 is false.");
    static_assert(!!0, "0 notted twice is false.");
  #endif

  ;

  {
    /* Test scope after a statement. */
    #define x 1
    static_assert(x, "static_assert() malfunction!");
    static_assert(__LINE__, "static_assert() malfunction!");
    #ifndef TEST_TRUE
      static_assert(1/2, "Truncation is false.");
      static_assert('\0', "Character constant is false.");
    #endif
  }

  {
    /* Test on same line. */
    static_assert(1, "static_assert() malfunction!"); static_assert(-1, "static_assert() malfunction!");
    #ifndef TEST_TRUE
      static_assert(1 ^ 1, "1 ^ 1 is false."); static_assert(0x0, "Constant is false.");
    #endif
  }
  return 0;
}
