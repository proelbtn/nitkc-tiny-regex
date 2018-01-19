#pragma once

#include <string>

#include <nfa.h>
#include <dfa.h>

class TinyRegex {
    DFA dfa;
    struct {
        bool first;
        bool last;
    } flags;

public:
    TinyRegex(std::string regex);
    TinyRegex(NFA nfa, bool first, bool last);

    bool test(const std::string &txt) const;
    std::string dump() const;
};