#include <gtest/gtest.h>

#include <regex>
#include <tiny_regex.h>
#include <nfa.h>
#include <fstream>
#include <chrono>

#define REGEX_MATCH_CHECK(re, cre, str) EXPECT_EQ(re.test(str), std::regex_search(str, cre));


TEST(TinyRegex, Test01) {
    NFA nfa;
    nfa.link(nfa.ch('a'), nfa.link(nfa.star(nfa.select(nfa.ch('a'), nfa.ch('b'))), nfa.ch('a')));
    TinyRegex re(nfa, false, false);
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
    NFA nfa;
    nfa.link(nfa.ch('a'), nfa.link(nfa.star(nfa.select(nfa.ch('a'), nfa.ch('b'))), nfa.ch('a')));
    TinyRegex re(nfa, true, false);
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
    NFA nfa;
    nfa.link(nfa.ch('a'), nfa.link(nfa.star(nfa.select(nfa.ch('a'), nfa.ch('b'))), nfa.ch('a')));
    TinyRegex re(nfa, false, true);
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
    NFA nfa;
    nfa.link(nfa.ch('a'), nfa.link(nfa.star(nfa.select(nfa.ch('a'), nfa.ch('b'))), nfa.ch('a')));
    TinyRegex re(nfa, true, true);
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

TEST(TinyRegex, Test05) {
    NFA nfa;
    nfa.digit();
    TinyRegex re(nfa, true, true);
    std::regex cre("^[\\d]$");
    REGEX_MATCH_CHECK(re, cre, "");
    REGEX_MATCH_CHECK(re, cre, "0");
    REGEX_MATCH_CHECK(re, cre, "1");
    REGEX_MATCH_CHECK(re, cre, "2");
    REGEX_MATCH_CHECK(re, cre, "3");
    REGEX_MATCH_CHECK(re, cre, "4");
    REGEX_MATCH_CHECK(re, cre, "5");
    REGEX_MATCH_CHECK(re, cre, "6");
    REGEX_MATCH_CHECK(re, cre, "7");
    REGEX_MATCH_CHECK(re, cre, "8");
    REGEX_MATCH_CHECK(re, cre, "9");
    REGEX_MATCH_CHECK(re, cre, "a");
}

TEST(TinyRegex, Test06) {
    NFA nfa;
    nfa.star(nfa.digit());
    TinyRegex re(nfa, true, true);
    std::regex cre("^[\\d]*$");

    REGEX_MATCH_CHECK(re, cre, "0000");
    REGEX_MATCH_CHECK(re, cre, "1111");
    REGEX_MATCH_CHECK(re, cre, "2222");
    REGEX_MATCH_CHECK(re, cre, "3333");
    REGEX_MATCH_CHECK(re, cre, "....");
    REGEX_MATCH_CHECK(re, cre, "5555");
    REGEX_MATCH_CHECK(re, cre, "????");
    REGEX_MATCH_CHECK(re, cre, "6666");
    REGEX_MATCH_CHECK(re, cre, "77777");
    REGEX_MATCH_CHECK(re, cre, "888");
    REGEX_MATCH_CHECK(re, cre, "9999");
}