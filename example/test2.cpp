#include <iostream>
#include <cassert>
#include <string_view>

#define TEST(name) void test##name ()

void testSomethingGoesWell2() {
  //  std::cout << "something goes well 2" << std::endl;;
}

void testSomething() {
  throw 3;
}


void testSomethingCool2() {
  std::string_view a = "helloo";

  if (a.size() == 5) {
    throw 3;
  }
  
}

void testAaa() {

}
