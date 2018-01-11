#include <gtest/gtest.h>
#include "tiny_regex/nfa.h"

using namespace tiny_regex;

TEST(NFA, SINGLE_CHAR_CONSTRUCTOR) {
    const char rule = 'a';
    NFA n(rule);
    EXPECT_EQ(n.start()->rule(), rule);
    EXPECT_EQ(n.start()->first(), n.end());
}

TEST(NFA, OPERATOR_AND) {
    const char rule1 = 'a', rule2 = 'b';
    NFA n1(rule1), n2(rule2);
    NFA n = n1 & n2;

    EXPECT_EQ(n.start(), n1.start());
    EXPECT_EQ(n.end(), n2.end());

    EXPECT_EQ(n.start()->rule(), rule1);
    EXPECT_EQ(n.start()->first()->rule(),rule2);
    EXPECT_EQ(n.start()->first()->first(), n.end());
}

TEST(NFA, OPERATOR_OR) {
    const char rule1 = 'a', rule2 = 'b';
    NFA n1(rule1), n2(rule2);
    NFA n = n1 | n2;

    EXPECT_EQ(n.start()->first(), n1.start());
    EXPECT_EQ(n.start()->second(), n2.start());

    EXPECT_EQ(n.start()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.start()->first()->rule(), rule1);
    EXPECT_EQ(n.start()->second()->rule(), rule2);
    EXPECT_EQ(n.start()->first()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.start()->second()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.start()->first()->first()->first(), n.start()->second()->first()->first());
}