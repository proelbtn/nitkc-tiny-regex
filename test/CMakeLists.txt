cmake_minimum_required(VERSION 3.9)

set(SRCS)
set(LIBS
        tiny_regex
        pthread
        gtest
        gtest_main)

add_executable(unit_test ${SRCS})
target_link_libraries(unit_test ${LIBS})