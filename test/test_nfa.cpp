#include <gtest/gtest.h>
#include "tiny_regex/nfa.h"

using namespace tiny_regex;

TEST(NFA, SINGLE_CHAR_CONSTRUCTOR) {
    const char rule = 'a';
    NFA n(rule);
    EXPECT_EQ(n.entry()->rule(), rule);
    EXPECT_EQ(n.entry()->first(), n.exit());
}

TEST(NFA, OPERATOR_AND) {
    const char rule1 = 'a', rule2 = 'b';
    NFA n1(rule1), n2(rule2);
    NFA n = n1 & n2;

    EXPECT_EQ(n.entry(), n1.entry());
    EXPECT_EQ(n.entry()->rule(), rule1);
    EXPECT_EQ(n.entry()->first(), n1.exit());
    EXPECT_EQ(n.entry()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.entry()->first()->first(), n2.entry());
    EXPECT_EQ(n.entry()->first()->first()->rule(), rule2);
    EXPECT_EQ(n.entry()->first()->first()->first(), n2.exit());
    EXPECT_EQ(n.entry()->first()->first()->first(), n.exit());
}

TEST(NFA, OPERATOR_OR) {
    const char rule1 = 'a', rule2 = 'b';
    NFA n1(rule1), n2(rule2);
    NFA n = n1 | n2;

    EXPECT_EQ(n.entry()->first(), n1.entry());
    EXPECT_EQ(n.entry()->second(), n2.entry());

    EXPECT_EQ(n.entry()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.entry()->first()->rule(), rule1);
    EXPECT_EQ(n.entry()->second()->rule(), rule2);
    EXPECT_EQ(n.entry()->first()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.entry()->second()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n.entry()->first()->first()->first(), n.entry()->second()->first()->first());
}

TEST(NFA, OPERATOR_ASTERISK) {
    const char rule = 'a';
    NFA n(rule), n_star = *n;

    EXPECT_EQ(n_star.entry()->first(), n.entry());
    EXPECT_EQ(n_star.entry()->first()->rule(), rule);
    EXPECT_EQ(n_star.entry()->first()->first(), n.exit());
    EXPECT_EQ(n_star.entry()->first()->first()->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(n_star.entry()->first()->first()->first(), n_star.entry());
    EXPECT_EQ(n_star.entry()->second(), n_star.exit());
}

TEST(NFA, SIZE) {
    NFA n1('a'), n2('a'), n3('b'), n4('a');
    NFA n = n1 & *(n2 | n3) & n4;
    EXPECT_EQ(n.size(), 12);
}