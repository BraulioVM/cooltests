#include <string>
#include <unordered_map>

#include <cooltestslib_colors.h>

namespace cooltestslib::colors {
  using ColorMap = std::unordered_map<Color, std::string>;
  namespace {
    const ColorMap& colorMap() {
      // this initialization is not thread-safe but
      // anyway
      static const ColorMap map = {
	{Color::Green, "\u001b[42m"},
	{Color::Red, "\u001b[41m"}
      };
      return map;
    }

    const std::string &resetSequence(){
      static std::string r("\u001b[0m");
      return r;
    }
  }

  std::string paint(std::string_view text, Color color) {
    std::string result(colorMap().at(color));
    result += text;
    result += resetSequence();
    return result;
  }
  

  std::string green(std::string_view text) {
    return paint(text, Color::Green);
  }

  std::string red(std::string_view text) {
    return paint(text, Color::Red);
  }
}
