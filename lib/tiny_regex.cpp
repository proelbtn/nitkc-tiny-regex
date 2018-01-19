#include "tiny_regex.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "nfa.h"
#include <dfa.h>
#include <tiny_regex.h>

NFA str2nfa(std::string str) {
    NFA nfa;

    // とりあえず"a(a|b)*a"のNFAを構築するようにしておく。
    nfa.link(nfa.ch('a'), nfa.link(nfa.star(nfa.select(nfa.ch('a'), nfa.ch('b'))), nfa.ch('a')));

    return nfa;
}

DFA str2dfa(std::string str) {
    if(str[0] == '^') str = str.substr(1);
    if(str[str.size() - 1] == '$') str = str.substr(0, str.size() - 1);

    return str2nfa(str).nfa2dfa();
}

TinyRegex::TinyRegex(std::string regex) : dfa(str2dfa(regex)), flags({false, false}) {
    flags.first = regex[0] == '^';
    flags.last = regex[regex.size() - 1] == '$';
}

bool TinyRegex::test(const std::string &txt) const {
    long pos = 0;
    std::string::const_iterator start = txt.cbegin();

    while(start != txt.end()) {
        std::string::const_iterator it = start;
        for (it = start; it != txt.cend(); it++) {
            if (dfa[pos].is_end && !flags.last) return true;
            if (dfa[pos].refs.find(*it) == dfa[pos].refs.end()) break;
            pos = dfa[pos].refs.at(*it);
        };

        if(it == txt.cend() && dfa[pos].is_end) return true;
        if(flags.first) return false;

        start++;
    }
    return false;
}