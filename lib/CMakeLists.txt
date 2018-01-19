cmake_minimum_required(VERSION 3.9)

set(SRCS nfa.cpp)

add_library(tiny_regex STATIC ${SRCS})