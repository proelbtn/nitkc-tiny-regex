#include <gtest/gtest.h>

#include <nfa.h>

TEST(NFAState, CONSTRUCTOR) {
    NFAState ns;

    EXPECT_EQ(ns.refs.first, NFA::REF_UNDEFINED);
    EXPECT_EQ(ns.refs.second, NFA::REF_UNDEFINED);
    EXPECT_EQ(ns.rule, NFA::RULE_UNDEFINED);
}

#define TEST_NFASTATE(NS, RULE, REF_F, REF_S) \
    EXPECT_EQ(NS.rule, RULE); EXPECT_EQ(NS.refs.first, REF_F); EXPECT_EQ(NS.refs.second, REF_S);

TEST(NFAStatesVector, CH) {
    NFA nfa;
    char rule = 'a';
    NFASubsetRef ns1 = nfa.ch(rule);

    EXPECT_EQ(ns1.start, 0);
    EXPECT_EQ(ns1.end, 1);

    TEST_NFASTATE(nfa[ns1.start], rule, ns1.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns1.end], NFA::RULE_UNDEFINED, NFA::REF_UNDEFINED, NFA::REF_UNDEFINED);
}

TEST(NFAStatesVector, LINK) {
    NFA nfa;
    char rule1 = 'a', rule2 = 'b';
    NFASubsetRef ns1 = nfa.ch(rule1), ns2 = nfa.ch(rule2), ns3 = nfa.link(ns1, ns2);

    EXPECT_EQ(ns3.start, 0);
    EXPECT_EQ(ns3.end, 3);

    TEST_NFASTATE(nfa[ns1.start], rule1, ns1.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns1.end], NFA::RULE_EPSILON, ns2.start, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns2.start], rule2, ns2.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns2.end], NFA::RULE_UNDEFINED, NFA::REF_UNDEFINED, NFA::REF_UNDEFINED);

    EXPECT_EQ(ns3.start, ns1.start);
    EXPECT_EQ(ns3.end, ns2.end);
}

TEST(NFAStatesVector, SELECT) {
    NFA nfa;
    char rule1 = 'a', rule2 = 'b';
    NFASubsetRef ns1 = nfa.ch(rule1), ns2 = nfa.ch(rule2), ns3 = nfa.select(ns1, ns2);

    EXPECT_EQ(ns3.start, 4);
    EXPECT_EQ(ns3.end, 5);

    TEST_NFASTATE(nfa[ns1.start], rule1, ns1.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns1.end], NFA::RULE_EPSILON, ns3.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns2.start], rule2, ns2.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns2.end], NFA::RULE_EPSILON, ns3.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns3.start], NFA::RULE_EPSILON, ns1.start, ns2.start);
    TEST_NFASTATE(nfa[ns3.end], NFA::RULE_UNDEFINED, NFA::REF_UNDEFINED, NFA::REF_UNDEFINED);
}

TEST(NFAStatesVector, STAR) {
    NFA nfa;
    char rule1 = 'a';
    NFASubsetRef ns1 = nfa.ch(rule1), ns2 = nfa.star(ns1);

    EXPECT_EQ(ns2.start, 2);
    EXPECT_EQ(ns2.end, 3);

    TEST_NFASTATE(nfa[ns1.start], rule1, ns1.end, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns1.end], NFA::RULE_EPSILON, ns2.start, NFA::REF_UNDEFINED);
    TEST_NFASTATE(nfa[ns2.start], NFA::RULE_EPSILON, ns1.start, ns2.end);
    TEST_NFASTATE(nfa[ns2.end], NFA::RULE_UNDEFINED, NFA::REF_UNDEFINED, NFA::REF_UNDEFINED);
}