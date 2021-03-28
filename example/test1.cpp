#include <assertion_macro.h>

void testAdditionIsGreat() {
  ASSERT_EQ(1 + 1, 2);
}

void testMultiplicationIsCool() {
  ASSERT_EQ(3 * 7, 21);
}

int helperFunction(int x) {
  return x+1;
}

void testHelperFunctionIsBroken() {
  ASSERT(helperFunction(3) != 4);
}
