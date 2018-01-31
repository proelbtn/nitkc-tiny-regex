cmake_minimum_required(VERSION 3.9)

set(SRCS
        test_nfa_dfa.cpp
        test_tiny_regex.cpp)
set(LIBS
        tiny_regex
        pthread
        gtest
        gtest_main)

add_executable(auto_test ${SRCS})
target_link_libraries(auto_test ${LIBS})
