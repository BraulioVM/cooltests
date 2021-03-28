add_library(cooltestslib STATIC
  cooltestslib_main.cpp
  cooltestslib_colors.cpp
  cooltestslib_renderer.cpp
  )
target_include_directories(cooltestslib PRIVATE .)
