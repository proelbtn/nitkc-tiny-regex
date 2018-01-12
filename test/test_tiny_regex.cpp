#include <gtest/gtest.h>
#include "tiny_regex.h"

using namespace tiny_regex;

TEST(TINY_REGEX, NFA2ETT_1) {
    NFA nfa(NFAState::TR_EPSILON);
    EpsilonTransitionTable ett = nfa2ett(nfa);
    NFAStateRef entry = nfa.entry(), exit = nfa.exit();
    EXPECT_NE(ett[entry].find(entry), ett[entry].end());
    EXPECT_NE(ett[entry].find(exit), ett[entry].end());
    EXPECT_EQ(ett[exit].find(entry), ett[exit].end());
    EXPECT_NE(ett[exit].find(exit), ett[exit].end());
}

TEST(TINY_REGEX, NFA2ETT_2) {
    NFA a('a'), b('b'), nfa = a & b;
    EpsilonTransitionTable ett = nfa2ett(nfa);

    EXPECT_NE(ett[a.entry()].find(a.entry()), ett[a.entry()].end());
    EXPECT_EQ(ett[a.entry()].find(a.exit()), ett[a.entry()].end());
    EXPECT_EQ(ett[a.entry()].find(b.entry()), ett[a.entry()].end());
    EXPECT_EQ(ett[a.entry()].find(b.exit()), ett[a.entry()].end());

    EXPECT_EQ(ett[a.exit()].find(a.entry()), ett[a.exit()].end());
    EXPECT_NE(ett[a.exit()].find(a.exit()), ett[a.exit()].end());
    EXPECT_NE(ett[a.exit()].find(b.entry()), ett[a.exit()].end());
    EXPECT_EQ(ett[a.exit()].find(b.exit()), ett[a.exit()].end());

    EXPECT_EQ(ett[b.entry()].find(a.entry()), ett[b.entry()].end());
    EXPECT_EQ(ett[b.entry()].find(a.exit()), ett[b.entry()].end());
    EXPECT_NE(ett[b.entry()].find(b.entry()), ett[b.entry()].end());
    EXPECT_EQ(ett[b.entry()].find(b.exit()), ett[b.entry()].end());

    EXPECT_EQ(ett[b.exit()].find(a.entry()), ett[b.exit()].end());
    EXPECT_EQ(ett[b.exit()].find(a.exit()), ett[b.exit()].end());
    EXPECT_EQ(ett[b.exit()].find(b.entry()), ett[b.exit()].end());
    EXPECT_NE(ett[b.exit()].find(b.exit()), ett[b.exit()].end());
}

TEST(TINY_REGEX, NFA2DFA) {
    NFA a('a'), b('b');

    nfa2dfa(a | b);
}