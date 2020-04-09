cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

FILE(GLOB UNITY_SRC *.c)
add_library(unity STATIC ${UNITY_SRC})

