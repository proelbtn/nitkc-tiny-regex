cmake_minimum_required(VERSION 3.9)

set(SRCS
        regex_nfa.cpp
        regex_nfalink.cpp
        regex_nfastate.cpp)

add_library(tiny_regex STATIC ${SRCS})