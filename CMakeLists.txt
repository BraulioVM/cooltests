cmake_minimum_required(VERSION 3.19)
project(cooltests)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(cooltestslib)

include(CoolTests.cmake)

if (${cooltests_OwnTests})
  add_executable(mytests
    example/test1.cpp
    example/test2.cpp
    )
  configure_cool_tests(mytests)
endif()

