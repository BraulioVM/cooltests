#include <iostream>
#include <span>
#include <numeric>
#include <algorithm>
#include <string_view>
#include <cstring>

#include <cooltestslib_colors.h>
#include <cooltestslib_global.h>
#include <cooltestslib_renderer.h>

namespace colors = cooltestslib::colors;
namespace global = cooltestslib::global;
using Test = global::Test;

namespace {
  int getBiggestString(std::span<const Test> tests) {
    int max = 0;

    std::for_each(tests.begin(),
		  tests.end(),
		  [&max](const auto& test)
		  {
		    std::string_view name(test.humanReadableName);
		    max = max > name.size()? max : name.size();
		  });

    return max;
  }

  bool testPasses(global::TestFunction test) {
    try {
      test();
      return true;
    } catch(...) {
      return false;
    }
  }
}

int main() {
  const auto *currentTest = global::tests;
  std::span<const Test> tests(currentTest + 0, currentTest + global::testNo);
  int biggestStringSize = getBiggestString(tests);

  cooltestslib::Renderer renderer(biggestStringSize);
  
  int testsPassed = 0;

  for (const Test &test : tests) {
    renderer.writeTestIsRunning(test.humanReadableName);

    bool success = testPasses(test.function);

    if (success) {
      testsPassed++;
    }

    renderer.writeTestResult(test.humanReadableName, success);
    std::cout << std::endl;
  }

  std::cout << "Tests passed " << testsPassed << "/" << tests.size() << std::endl;

  return testsPassed == tests.size()? 0 : 1;
}
