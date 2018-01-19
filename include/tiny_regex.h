#pragma once

#include <string>

#include <dfa.h>

class TinyRegex {
    DFA dfa;

public:
    TinyRegex(std::string regex);
};