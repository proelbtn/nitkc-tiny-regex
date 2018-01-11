#include <gtest/gtest.h>
#include "tiny_regex.h"

using namespace tiny_regex;

TEST(TINY_REGEX, NFA2ETT_1) {
    NFA nfa(NFAState::TR_EPSILON);
    EpsilonTransitionTable ett = nfa2ett(nfa);
    NFAStateRef entry = nfa.entry(), exit = nfa.exit();
}