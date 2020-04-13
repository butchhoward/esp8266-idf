# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

SET(TDD FALSE CACHE BOOL "Enable local TDD development cycle")

SET(ENV{ESPTOOL_PORT} "/dec/cu.SLAB_USBtoUART" )
SET(ENV{ESPTOOL_FF} "80m")
SET(ENV{ESPTOOL_FS} "4m")

if (NOT TDD)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

project(morse_code)

if (TDD)
  include(tdd.cmake)
endif()
