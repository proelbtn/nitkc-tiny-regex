cmake_minimum_required(VERSION 3.9)

set(SRCS
        test_nfa.cpp
        test_nfastate.cpp
        test_tiny_regex.cpp)
set(LIBS
        tiny_regex
        pthread
        gtest
        gtest_main)

add_executable(unit_test ${SRCS})
target_link_libraries(unit_test ${LIBS})