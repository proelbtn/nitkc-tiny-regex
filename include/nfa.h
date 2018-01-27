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

struct NFA {
    NFASubsetRef nfa;
    std::vector<NFAState> vec;

    static const char RULE_UNDEFINED;
    static const char RULE_EPSILON;
    static const long REF_UNDEFINED;

    NFA();

    NFASubsetRef ch(const char c);
    NFASubsetRef link(const NFASubsetRef lv, const NFASubsetRef rv);
    NFASubsetRef select(const NFASubsetRef lv, const NFASubsetRef rv);

    NFASubsetRef star(const NFASubsetRef v);
    NFASubsetRef question(const NFASubsetRef v);

    // cntrl and space is not implemented.
    NFASubsetRef range(const char s, const char e);
    NFASubsetRef one_of(const char *list);
    NFASubsetRef alnum();
    NFASubsetRef alpha();
    NFASubsetRef blank();
    NFASubsetRef digit();
    NFASubsetRef graph();
    NFASubsetRef lower();
    NFASubsetRef print();
    NFASubsetRef punct();
    NFASubsetRef upper();
    NFASubsetRef xdigit();

    const NFAState& operator[](unsigned long i) const;

    DFA nfa2dfa();
};