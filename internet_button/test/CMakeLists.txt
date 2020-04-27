# This file is long and looks intimidating.  After you
# read the comments, strip all of them out and you will
# see that the file isn't quite so large or scary.
#######################################################

# CMake file for the unit tests 

# Windows (and maybe OSX) needs this definition
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_definitions(-D__time_t_defined)
endif()

# Some logging macros use __ESP_FILE__ instead of the standard __FILE__.
# not sure why, but some of the ESP CMake uses this substitution and it 
# seems to work when building the test files, so...
add_definitions(-D__ESP_FILE__=__FILE__)

# These make the mock directory and the unity directory 
# available as a source for header files, so if you have
# a file unity_fixture.h in the unity directory, you can 
# write  '#include <unity_fixture.h>' in a file and the
# compiler will know how to find it.
# This works the same for files under the mock directory.

include_directories(SYSTEM ${MOCK_DIR})
include_directories(SYSTEM ${UNITY_DIR})

# These add the include folders from the ESP8266_RTOS_SDK that are needed
# I am added these as they are needed for now
include_directories(SYSTEM $ENV{IDF_PATH}/components/esp_common/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/freertos/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/esp8266/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/heap/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/heap/port/esp8266/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/nvs_flash/include)


include_directories(SYSTEM $ENV{IDF_PATH}/components/esp_http_server/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/http_parser/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/tcpip_adapter/include)

include_directories(SYSTEM $ENV{IDF_PATH}/components/esp_event/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/log/include)

include_directories(SYSTEM $ENV{IDF_PATH}/components/lwip/lwip/src/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/lwip/port/esp8266/include)
include_directories(SYSTEM $ENV{IDF_PATH}/components/lwip/include/apps/sntp)
include_directories(SYSTEM $ENV{IDF_PATH}/components/lwip/include/apps)


# these seem to be ports to bridge between ESP-IDF and the ESP8266 (?)
include_directories(SYSTEM $ENV{IDF_PATH}/components/freertos/port/esp8266/include) 
include_directories(SYSTEM $ENV{IDF_PATH}/components/freertos/port/esp8266/include/freertos) 
include_directories(SYSTEM $ENV{IDF_PATH}/components/freertos/include/freertos/private)


# These folders are created by the `make defconfig` command (or the `make menuconfig`)
# with idf.py.  Test builds will fail until you do that.
include_directories(${PROJECT_SOURCE_DIR}/build-test/config)
include_directories(${PROJECT_SOURCE_DIR}/build-test/include)

# Directories needed for this project
include_directories(${PROJECT_SOURCE_DIR}/main)
include_directories(${PROJECT_SOURCE_DIR}/components/include)

# FILE GLOBing: a unix concept where all files matching a wildcard
# pattern are collected as a group.

# A list of all of the files matching *.c in this directory
# will be assigned to the variable TEST_SRC
FILE(GLOB TEST_SRC *.c)

# A list of all of the files matching *.c in the MOCK_DIR directory
# will be assigned to the variable TEST_SRC (defined one level up)
FILE(GLOB MOCK_SRC ${MOCK_DIR}/*.c)

# A list of all src files in the System Under Test
FILE(GLOB SUT_SRC 
    ../main/*.c
    ../components/*.c
)

# Tells cmake that we want to create an executable named 
# <PROJECTNAME>-test (defined one level up).
add_executable(${PROJECT_TEST} ${TEST_SRC} ${SUT_SRC} ${MOCK_SRC} )

add_custom_target(
    tdd ALL ./${PROJECT_TEST}
    DEPENDS ${PROJECT_TEST}
)

# This says the that executable phonebooth-esp-idf-test will be
# linked with the unity library.
target_link_libraries(${PROJECT_TEST} ${LIB_UNITY})
