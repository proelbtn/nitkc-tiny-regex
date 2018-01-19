#pragma once

#include <string>

#include <dfa.h>

class TinyRegex {
    DFA dfa;
    struct {
        bool first;
        bool last;
    } flags;

public:
    TinyRegex(std::string regex);

    bool test(const std::string &txt) const;
    std::string dump() const;
};