cmake_minimum_required(VERSION 2.8.11)

project(Front)

option(ENABLE_TESTING "Build test utilities and run internal test suite" ON)

add_subdirectory(frc)

if (ENABLE_TESTING)
  add_subdirectory(test)
endif (ENABLE_TESTING)

