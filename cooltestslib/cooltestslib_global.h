#pragma once

namespace cooltestslib::global {
  using TestFunction = void(*)();

  struct Test {
    const char*  humanReadableName;
    TestFunction function;
  };

  // These will be the two global variables populated
  // by the python-generated source code
  extern const int testNo;
  extern const Test tests[];

}
