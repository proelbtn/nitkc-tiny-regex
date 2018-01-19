#pragma once

#include <cstddef>
#include <vector>
#include <utility>

#include "dfa.h"

struct NFASubsetRef {
    long start;
    long end;

    NFASubsetRef();
};

struct NFAState {
    char rule;
    std::pair<long, long> refs;

    NFAState();
};

class NFA {
    NFASubsetRef nfa_;
    std::vector<NFAState> vec_;

public:
    static const char RULE_UNDEFINED;
    static const char RULE_EPSILON;
    static const long REF_UNDEFINED;

    NFA();

    NFASubsetRef add_nfa(const char c);

    NFASubsetRef link(const NFASubsetRef lv, const NFASubsetRef rv);
    NFASubsetRef select(const NFASubsetRef lv, const NFASubsetRef rv);
    NFASubsetRef star(const NFASubsetRef v);

    DFA nfa2dfa();
};