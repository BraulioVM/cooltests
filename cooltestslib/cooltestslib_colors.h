#pragma once

#include <string>
#include <string_view>

namespace cooltestslib::colors {
  enum class Color {
    Green,
    Red
  };
  std::string paint(std::string_view text, Color color);
  std::string green(std::string_view text);
  std::string red(std::string_view text);
}
