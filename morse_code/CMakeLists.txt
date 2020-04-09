# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

SET(TDD FALSE CACHE BOOL "Enable local TDD development cycle")

if (NOT TDD)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

project(morse_code)

if (TDD)
  include(tdd.cmake)
endif()
