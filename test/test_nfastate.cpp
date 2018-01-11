#include <gtest/gtest.h>
#include "tiny_regex/nfa.h"

using namespace tiny_regex;

class twoNFAStates : public ::testing::Test {
protected:
    NFAStateRef s1, s2;

    virtual void SetUp() {
        this->s1 = NFAState::create();
        this->s2 = NFAState::create();
    }
};

class threeNFAStates : public ::testing::Test {
protected:
    NFAStateRef s1, s2, s3;

    virtual void SetUp() {
        this->s1 = NFAState::create();
        this->s2 = NFAState::create();
        this->s3 = NFAState::create();
    }
};

TEST_F(twoNFAStates, IMPLICIT_LINK_TO) {
    s1->link_to(s2);
    EXPECT_EQ(s1->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(s1->first(), s2);
}

TEST_F(twoNFAStates, EXPLICIT_LINK_TO) {
    char rule = 'a';
    s1->link_to(s2, rule);
    EXPECT_EQ(s1->rule(), rule);
    EXPECT_EQ(s1->first(), s2);
}

TEST_F(threeNFAStates, IMPLICIT_LINK_TO) {
    s1->link_to(s2, s3);
    EXPECT_EQ(s1->rule(), NFAState::TR_EPSILON);
    EXPECT_EQ(s1->first(), s2);
    EXPECT_EQ(s1->second(), s3);
}

TEST_F(threeNFAStates, EXPLICIT_LINK_TO) {
    char rule = 'a';
    s1->link_to(s2, s3, rule);
    EXPECT_EQ(s1->rule(), rule);
    EXPECT_EQ(s1->first(), s2);
    EXPECT_EQ(s1->second(), s3);
}

TEST_F(twoNFAStates, COPY_FROM) {
    NFAStateRef s3 = NFAState::create(), s4 = NFAState::create();
    s2->link_to(s3, s4);
    s1->copy_from(s2);
    EXPECT_EQ(s1->first(), s2->first());
}