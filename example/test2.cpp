#include <string_view>
#include <string>

#include <assertion_macro.h>

void testImplicitStringViewConversion() {
  std::string hello("hello");
  std::string_view lhs = hello;

  ASSERT_EQ(lhs, "hello");
}
