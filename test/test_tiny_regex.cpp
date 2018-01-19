#include <gtest/gtest.h>

#include <regex>
#include <tiny_regex.h>

#define REGEX_MATCH_CHECK(re, cre, str) EXPECT_EQ(re.test(str), std::regex_search(str, cre));


TEST(TinyRegex, Test01) {
    TinyRegex re("a(a|b)*a");
    std::regex cre("a(a|b)*a");

    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "b");
    REGEX_MATCH_CHECK(re, cre, "aa");
    REGEX_MATCH_CHECK(re, cre, "ab");
    REGEX_MATCH_CHECK(re, cre, "ba");
    REGEX_MATCH_CHECK(re, cre, "bb");
    REGEX_MATCH_CHECK(re, cre, "aaa");
    REGEX_MATCH_CHECK(re, cre, "baa");
    REGEX_MATCH_CHECK(re, cre, "aba");
    REGEX_MATCH_CHECK(re, cre, "aab");
    REGEX_MATCH_CHECK(re, cre, "bba");
    REGEX_MATCH_CHECK(re, cre, "bab");
    REGEX_MATCH_CHECK(re, cre, "abb");
    REGEX_MATCH_CHECK(re, cre, "bbb");
    REGEX_MATCH_CHECK(re, cre, "aaaa");
    REGEX_MATCH_CHECK(re, cre, "baaa");
    REGEX_MATCH_CHECK(re, cre, "abaa");
    REGEX_MATCH_CHECK(re, cre, "aaba");
    REGEX_MATCH_CHECK(re, cre, "aaab");
    REGEX_MATCH_CHECK(re, cre, "bbaa");
    REGEX_MATCH_CHECK(re, cre, "baba");
    REGEX_MATCH_CHECK(re, cre, "baab");
    REGEX_MATCH_CHECK(re, cre, "abba");
    REGEX_MATCH_CHECK(re, cre, "abab");
    REGEX_MATCH_CHECK(re, cre, "aabb");
    REGEX_MATCH_CHECK(re, cre, "bbba");
    REGEX_MATCH_CHECK(re, cre, "bbab");
    REGEX_MATCH_CHECK(re, cre, "babb");
    REGEX_MATCH_CHECK(re, cre, "abbb");
    REGEX_MATCH_CHECK(re, cre, "bbbb");
}

TEST(TinyRegex, Test02) {
    TinyRegex re("^a(a|b)*a");
    std::regex cre("^a(a|b)*a");

    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "b");
    REGEX_MATCH_CHECK(re, cre, "aa");
    REGEX_MATCH_CHECK(re, cre, "ab");
    REGEX_MATCH_CHECK(re, cre, "ba");
    REGEX_MATCH_CHECK(re, cre, "bb");
    REGEX_MATCH_CHECK(re, cre, "aaa");
    REGEX_MATCH_CHECK(re, cre, "baa");
    REGEX_MATCH_CHECK(re, cre, "aba");
    REGEX_MATCH_CHECK(re, cre, "aab");
    REGEX_MATCH_CHECK(re, cre, "bba");
    REGEX_MATCH_CHECK(re, cre, "bab");
    REGEX_MATCH_CHECK(re, cre, "abb");
    REGEX_MATCH_CHECK(re, cre, "bbb");
    REGEX_MATCH_CHECK(re, cre, "aaaa");
    REGEX_MATCH_CHECK(re, cre, "baaa");
    REGEX_MATCH_CHECK(re, cre, "abaa");
    REGEX_MATCH_CHECK(re, cre, "aaba");
    REGEX_MATCH_CHECK(re, cre, "aaab");
    REGEX_MATCH_CHECK(re, cre, "bbaa");
    REGEX_MATCH_CHECK(re, cre, "baba");
    REGEX_MATCH_CHECK(re, cre, "baab");
    REGEX_MATCH_CHECK(re, cre, "abba");
    REGEX_MATCH_CHECK(re, cre, "abab");
    REGEX_MATCH_CHECK(re, cre, "aabb");
    REGEX_MATCH_CHECK(re, cre, "bbba");
    REGEX_MATCH_CHECK(re, cre, "bbab");
    REGEX_MATCH_CHECK(re, cre, "babb");
    REGEX_MATCH_CHECK(re, cre, "abbb");
    REGEX_MATCH_CHECK(re, cre, "bbbb");
}

TEST(TinyRegex, Test03) {
    TinyRegex re("a(a|b)*a$");
    std::regex cre("a(a|b)*a$");

    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "b");
    REGEX_MATCH_CHECK(re, cre, "aa");
    REGEX_MATCH_CHECK(re, cre, "ab");
    REGEX_MATCH_CHECK(re, cre, "ba");
    REGEX_MATCH_CHECK(re, cre, "bb");
    REGEX_MATCH_CHECK(re, cre, "aaa");
    REGEX_MATCH_CHECK(re, cre, "baa");
    REGEX_MATCH_CHECK(re, cre, "aba");
    REGEX_MATCH_CHECK(re, cre, "aab");
    REGEX_MATCH_CHECK(re, cre, "bba");
    REGEX_MATCH_CHECK(re, cre, "bab");
    REGEX_MATCH_CHECK(re, cre, "abb");
    REGEX_MATCH_CHECK(re, cre, "bbb");
    REGEX_MATCH_CHECK(re, cre, "aaaa");
    REGEX_MATCH_CHECK(re, cre, "baaa");
    REGEX_MATCH_CHECK(re, cre, "abaa");
    REGEX_MATCH_CHECK(re, cre, "aaba");
    REGEX_MATCH_CHECK(re, cre, "aaab");
    REGEX_MATCH_CHECK(re, cre, "bbaa");
    REGEX_MATCH_CHECK(re, cre, "baba");
    REGEX_MATCH_CHECK(re, cre, "baab");
    REGEX_MATCH_CHECK(re, cre, "abba");
    REGEX_MATCH_CHECK(re, cre, "abab");
    REGEX_MATCH_CHECK(re, cre, "aabb");
    REGEX_MATCH_CHECK(re, cre, "bbba");
    REGEX_MATCH_CHECK(re, cre, "bbab");
    REGEX_MATCH_CHECK(re, cre, "babb");
    REGEX_MATCH_CHECK(re, cre, "abbb");
    REGEX_MATCH_CHECK(re, cre, "bbbb");
}

TEST(TinyRegex, Test04) {
    TinyRegex re("^a(a|b)*a$");
    std::regex cre("^a(a|b)*a$");

    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "a");
    REGEX_MATCH_CHECK(re, cre, "b");
    REGEX_MATCH_CHECK(re, cre, "aa");
    REGEX_MATCH_CHECK(re, cre, "ab");
    REGEX_MATCH_CHECK(re, cre, "ba");
    REGEX_MATCH_CHECK(re, cre, "bb");
    REGEX_MATCH_CHECK(re, cre, "aaa");
    REGEX_MATCH_CHECK(re, cre, "baa");
    REGEX_MATCH_CHECK(re, cre, "aba");
    REGEX_MATCH_CHECK(re, cre, "aab");
    REGEX_MATCH_CHECK(re, cre, "bba");
    REGEX_MATCH_CHECK(re, cre, "bab");
    REGEX_MATCH_CHECK(re, cre, "abb");
    REGEX_MATCH_CHECK(re, cre, "bbb");
    REGEX_MATCH_CHECK(re, cre, "aaaa");
    REGEX_MATCH_CHECK(re, cre, "baaa");
    REGEX_MATCH_CHECK(re, cre, "abaa");
    REGEX_MATCH_CHECK(re, cre, "aaba");
    REGEX_MATCH_CHECK(re, cre, "aaab");
    REGEX_MATCH_CHECK(re, cre, "bbaa");
    REGEX_MATCH_CHECK(re, cre, "baba");
    REGEX_MATCH_CHECK(re, cre, "baab");
    REGEX_MATCH_CHECK(re, cre, "abba");
    REGEX_MATCH_CHECK(re, cre, "abab");
    REGEX_MATCH_CHECK(re, cre, "aabb");
    REGEX_MATCH_CHECK(re, cre, "bbba");
    REGEX_MATCH_CHECK(re, cre, "bbab");
    REGEX_MATCH_CHECK(re, cre, "babb");
    REGEX_MATCH_CHECK(re, cre, "abbb");
    REGEX_MATCH_CHECK(re, cre, "bbbb");
}