cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

add_compile_definitions(
    UNITY_OUTPUT_COLOR 
    UNITY_DIFFERENTIATE_FINAL_FAIL
)

FILE(GLOB UNITY_SRC *.c)
add_library(unity STATIC ${UNITY_SRC})

