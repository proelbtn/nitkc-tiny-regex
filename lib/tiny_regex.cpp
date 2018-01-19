#include "tiny_regex.h"

#include <string>

#include "nfa.h"
#include <dfa.h>

NFA str2nfa(std::string str) {
    NFA nfa;

    return nfa;
}

DFA str2dfa(std::string str) {
    return str2nfa(str).nfa2dfa();
}

TinyRegex::TinyRegex(std::string regex) : dfa(str2dfa(regex)) {}
