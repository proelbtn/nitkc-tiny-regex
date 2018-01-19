#pragma once

#include <cstddef>
#include <vector>
#include <utility>

struct NFA {
    long start;
    long end;
};

struct NFAState {
    static const char RULE_UNDEFINED;
    static const char RULE_EPSILON;
    static const long REFS_UNDEFINED;

    char rule;
    struct {
        long first;
        long second;
    } refs;

    NFAState();
};

struct NFAStatesVector {
    std::vector<NFAState> vec;

    NFA add_nfa(const char c);

    NFA link(const NFA lv, const NFA rv);
    NFA select(const NFA lv, const NFA rv);
    NFA star(const NFA v);

    void nfa2dfa(const NFA v);
};