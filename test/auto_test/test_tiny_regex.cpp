#include <gtest/gtest.h>

#include <regex>
#include <tiny_regex.h>
#include <nfa.h>

#define REGEX_MATCH_CHECK(re, cre, str) EXPECT_EQ(std::regex_search(str, cre), re.test(str));
#define TEST_CASE \
    REGEX_MATCH_CHECK(re, cre, ""); \
    REGEX_MATCH_CHECK(re, cre, "a"); \
    REGEX_MATCH_CHECK(re, cre, "b"); \
    REGEX_MATCH_CHECK(re, cre, "aa"); \
    REGEX_MATCH_CHECK(re, cre, "ab"); \
    REGEX_MATCH_CHECK(re, cre, "ba"); \
    REGEX_MATCH_CHECK(re, cre, "bb"); \
    REGEX_MATCH_CHECK(re, cre, "aaa"); \
    REGEX_MATCH_CHECK(re, cre, "baa"); \
    REGEX_MATCH_CHECK(re, cre, "aba"); \
    REGEX_MATCH_CHECK(re, cre, "aab"); \
    REGEX_MATCH_CHECK(re, cre, "bba"); \
    REGEX_MATCH_CHECK(re, cre, "bab"); \
    REGEX_MATCH_CHECK(re, cre, "abb"); \
    REGEX_MATCH_CHECK(re, cre, "bbb"); \
    REGEX_MATCH_CHECK(re, cre, "aaaa"); \
    REGEX_MATCH_CHECK(re, cre, "baaa"); \
    REGEX_MATCH_CHECK(re, cre, "abaa"); \
    REGEX_MATCH_CHECK(re, cre, "aaba"); \
    REGEX_MATCH_CHECK(re, cre, "aaab"); \
    REGEX_MATCH_CHECK(re, cre, "bbaa"); \
    REGEX_MATCH_CHECK(re, cre, "baba"); \
    REGEX_MATCH_CHECK(re, cre, "baab"); \
    REGEX_MATCH_CHECK(re, cre, "abba"); \
    REGEX_MATCH_CHECK(re, cre, "abab"); \
    REGEX_MATCH_CHECK(re, cre, "aabb"); \
    REGEX_MATCH_CHECK(re, cre, "bbba"); \
    REGEX_MATCH_CHECK(re, cre, "bbab"); \
    REGEX_MATCH_CHECK(re, cre, "babb"); \
    REGEX_MATCH_CHECK(re, cre, "abbb"); \
    REGEX_MATCH_CHECK(re, cre, "bbbb");

TEST(TinyRegex, Test01) {
    NFA nfa;
    TinyRegex re("a(a|b)*a");
    std::regex cre("a(a|b)*a");

    TEST_CASE;
}

TEST(TinyRegex, Test02) {
    NFA nfa;
    TinyRegex re("^a(a|b)*a");
    std::regex cre("^a(a|b)*a");

    TEST_CASE;
}

TEST(TinyRegex, Test03) {
    NFA nfa;
    TinyRegex re("a(a|b)*a$");
    std::regex cre("a(a|b)*a$");

    TEST_CASE;
}

TEST(TinyRegex, Test4) {
    NFA nfa;
    TinyRegex re("^a(a|b)*a$");
    std::regex cre("^a(a|b)*a$");

    TEST_CASE;
}

TEST(TinyRegex, Test05) {
    NFA nfa;
    TinyRegex re("^[0-9]$");
    std::regex cre("^[0-9]$");

    REGEX_MATCH_CHECK(re, cre, "1");
    REGEX_MATCH_CHECK(re, cre, "0");
    REGEX_MATCH_CHECK(re, cre, "2");
    REGEX_MATCH_CHECK(re, cre, "7");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "b");
    REGEX_MATCH_CHECK(re, cre, "c");
}

TEST(TinyRegex, Test06) {
    NFA nfa;
    TinyRegex re("^a?$");
    std::regex cre("^a?$");

    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "aa");
}

TEST(TinyRegex, Test07) {
    NFA nfa;
    TinyRegex re("今日はいい天気ですね。");
    std::regex cre("今日はいい天気ですね。");
}