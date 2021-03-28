#pragma once

#include <iostream>
#include <string_view>

namespace cooltestslib {
  class Renderer {
  private:
    // DATA
    int d_longestTestName;
    std::ostream &d_os;

    // PRIVATE MANIPULATORS
    void writeTestNamePrefix(std::string_view testName);
  public:
    // CREATORS
    Renderer(int longestTestName, std::ostream &os=std::cout);

    // MANIPULATORS
    void writeTestIsRunning(std::string_view testName); 
    void writeTestResult(std::string_view testName, bool success);
  };
}
