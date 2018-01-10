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
    ASSERT_EQ(s2, s1->trans_rules.first.trans_des.lock());
    ASSERT_EQ(NFALink::TR_EPSILON, s1->trans_rules.first.trans_rule);
}

TEST_F(twoNFAStates, EXPLICIT_LINK_TO) {
    char rule = 'a';
    s1->link_to(s2, rule);
    ASSERT_EQ(s2, s1->trans_rules.first.trans_des.lock());
    ASSERT_EQ(rule, s1->trans_rules.first.trans_rule);
}

TEST_F(threeNFAStates, IMPLICIT_LINK_TO) {
    s1->link_to(s2, s3);
    ASSERT_EQ(s2, s1->trans_rules.first.trans_des.lock());
    ASSERT_EQ(s3, s1->trans_rules.second.trans_des.lock());
    ASSERT_EQ(NFALink::TR_EPSILON, s1->trans_rules.first.trans_rule);
    ASSERT_EQ(NFALink::TR_EPSILON, s1->trans_rules.second.trans_rule);
}

TEST_F(threeNFAStates, EXPLICIT_LINK_TO) {
    char rule = 'a';
    s1->link_to(s2, s3, rule);
    ASSERT_EQ(s2, s1->trans_rules.first.trans_des.lock());
    ASSERT_EQ(s3, s1->trans_rules.second.trans_des.lock());
    ASSERT_EQ(rule, s1->trans_rules.first.trans_rule);
    ASSERT_EQ(rule, s1->trans_rules.second.trans_rule);
}