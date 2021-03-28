#include <cooltestslib_renderer.h>

#include <cooltestslib_colors.h>

namespace cooltestslib {

  namespace {
    void writeSpaces(std::ostream &os, int number) {
      while(number--) {
	os << ' ';
      }
    }

    const std::string SUCCESS = colors::paint("SUCCESS", colors::Color::Green);
    const std::string FAILURE = colors::paint("FAILURE", colors::Color::Red);
  }

  void Renderer::writeTestNamePrefix(std::string_view testName) {
    d_os << testName;
    int spacesNeeded = 2 + d_longestTestName - testName.size();
    writeSpaces(d_os, spacesNeeded);    
  }

  Renderer::Renderer(int longestTestName, std::ostream& os)
    : d_longestTestName(longestTestName)
    , d_os(os)
  {

  }

  void Renderer::writeTestIsRunning(std::string_view testName) {
    writeTestNamePrefix(testName);
    d_os << "RUNNING" << std::endl;;
  }

  void Renderer::writeTestResult(std::string_view testName, bool success) {
    writeTestNamePrefix(testName);

    const std::string& result = success?
      SUCCESS :
      FAILURE;

    d_os << result << std::endl;
  }
}
