#include <nfa.h>
#include <gtest/gtest.h>

TEST(NFAState, CONSTRUCTOR) {
    NFAState ns;

    EXPECT_EQ(ns.refs.first, NFA::REF_UNDEFINED);
    EXPECT_EQ(ns.refs.second, NFA::REF_UNDEFINED);
    EXPECT_EQ(ns.rule, NFA::RULE_UNDEFINED);
}

TEST(NFAStatesVector, ADD_NFA) {
    NFA nv;
    NFASubsetRef nfa = nv.add_nfa('a');

    EXPECT_EQ(nfa.start, 0);
    EXPECT_EQ(nfa.end, 1);
}

TEST(NFAStatesVector, LINK) {
    NFA nv;
    NFASubsetRef n1 = nv.add_nfa('a'), n2 = nv.add_nfa('b'), n3 = nv.link(n1, n2);

    EXPECT_EQ(n3.start, 0);
    EXPECT_EQ(n3.end, 3);
}

TEST(NFAStatesVector, SELECT) {
    NFA nv;
    NFASubsetRef n1 = nv.add_nfa('a'), n2 = nv.add_nfa('b'), n3 = nv.select(n1, n2);

    EXPECT_EQ(n3.start, 4);
    EXPECT_EQ(n3.end, 5);
}

TEST(NFAStatesVector, STAR) {
    NFA nv;
    NFASubsetRef n1 = nv.add_nfa('a'), n2 = nv.star(n1);

    EXPECT_EQ(n2.start, 2);
    EXPECT_EQ(n2.end, 3);
}

TEST(NFAStatesVector, NFA2DFA) {
    NFA nv;
    NFASubsetRef n1 = nv.add_nfa('a'), n2 = nv.add_nfa('a'), n3 = nv.add_nfa('b'), n4 = nv.add_nfa('a');

    nv.link(n1, nv.link(nv.select(n2, n3), n4));

    nv.nfa2dfa();
}