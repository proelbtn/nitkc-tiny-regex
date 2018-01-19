#include <nfa.h>
#include <gtest/gtest.h>

TEST(NFAState, CONSTRUCTOR) {
    NFAState ns;

    EXPECT_EQ(ns.refs.first, NFAState::REFS_UNDEFINED);
    EXPECT_EQ(ns.refs.second, NFAState::REFS_UNDEFINED);
    EXPECT_EQ(ns.rule, NFAState::RULE_UNDEFINED);
}

TEST(NFAStatesVector, ADD_NFA) {
    NFAStatesVector nv;
    NFA nfa = nv.add_nfa('a');

    EXPECT_EQ(nfa.start, 0);
    EXPECT_EQ(nfa.end, 1);
}

TEST(NFAStatesVector, LINK) {
    NFAStatesVector nv;
    NFA n1 = nv.add_nfa('a'), n2 = nv.add_nfa('b'), n3 = nv.link(n1, n2);

    EXPECT_EQ(n3.start, 0);
    EXPECT_EQ(n3.end, 3);
}

TEST(NFAStatesVector, SELECT) {
    NFAStatesVector nv;
    NFA n1 = nv.add_nfa('a'), n2 = nv.add_nfa('b'), n3 = nv.select(n1, n2);

    EXPECT_EQ(n3.start, 4);
    EXPECT_EQ(n3.end, 5);
}

TEST(NFAStatesVector, STAR) {
    NFAStatesVector nv;
    NFA n1 = nv.add_nfa('a'), n2 = nv.star(n1);

    EXPECT_EQ(n2.start, 2);
    EXPECT_EQ(n2.end, 3);
}

TEST(NFAStatesVector, NFA2DFA) {
    NFAStatesVector nv;
    NFA n1 = nv.add_nfa('a'), n2 = nv.add_nfa('a'), n3 = nv.add_nfa('b'), n4 = nv.add_nfa('a');

    NFA nfa = nv.link(n1, nv.link(nv.select(n2, n3), n4));

    nv.nfa2dfa(nfa);
}