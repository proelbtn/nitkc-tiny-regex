/*!
 * @file tiny_regex.cpp
 * @brief TinyRegexクラスの実装
 */

#include "tiny_regex.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#include "nfa.h"
#include <dfa.h>
#include <tiny_regex.h>

NFASubsetRef selects(NFA &nfa, std::string::const_iterator &it);
NFASubsetRef term(NFA &nfa, std::string::const_iterator &it);
NFASubsetRef str2nfa(NFA &nfa, std::string str);

NFASubsetRef selects(NFA &nfa, std::string str) {
    NFASubsetRef ns;

    for(std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        NFASubsetRef tns;

        if(*(it + 1) == '-') {
            tns = nfa.range(*it, *(it + 2));
            it += 2;
        }
        else tns = nfa.ch(*it);

        if (ns.start == NFA::REF_UNDEFINED) ns = tns;
        else ns = nfa.select(ns, tns);
    }

    return ns;
}

NFASubsetRef term(NFA &nfa, std::string::const_iterator &it) {
    NFASubsetRef ns;

    if(*it == '(') {
        int i = 1;
        std::string::const_iterator sit = it + 1;
        while(i != 0) {
            it++;
            if(*it == '(') i++;
            else if (*it == ')') i--;
        }
        ns = str2nfa(nfa, std::string(sit, it));
    }
    else if (*it == '['){
        int i = 1;
        std::string::const_iterator sit = it + 1;
        while(i != 0) {
            it++;
            if(*it == '[') i++;
            else if (*it == ']') i--;
        }
        ns = selects(nfa, std::string(sit, it));
    }
    else ns = nfa.ch(*it);

    it++;

    return ns;
}

NFASubsetRef str2nfa(NFA &nfa, std::string str) {
    NFASubsetRef ns;
    std::string::const_iterator it = str.cbegin();

    ns = term(nfa, it);
    if(*it == '*') {
        ns = nfa.star(ns);
        it++;
    }
    else if(*it == '?') {
        ns = nfa.question(ns);
        it++;
    }

    while(it != str.cend()) {
        NFASubsetRef tns;
        bool s_flag = false;

        if (*it == '|') {
            s_flag = true;
            it++;
        }

        tns = term(nfa, it);
        if(*it == '*') {
            tns = nfa.star(tns);
            it++;
        }
        else if(*it == '?') {
            tns = nfa.question(tns);
            it++;
        }

        if(s_flag) ns = nfa.select(ns, tns);
        else ns = nfa.link(ns, tns);
    }

    return ns;

}

DFA str2dfa(std::string str) {
    NFA nfa;
    if(str[0] == '^') str = str.substr(1);
    if(str[str.size() - 1] == '$') str = str.substr(0, str.size() - 1);

    str2nfa(nfa, str);

    return nfa.nfa2dfa();
}

TinyRegex::TinyRegex(std::string regex) : dfa(str2dfa(regex)), flags({false, false}) {
    flags.first = regex[0] == '^';
    flags.last = regex[regex.size() - 1] == '$';
}

TinyRegex::TinyRegex(NFA nfa, bool first, bool last) : dfa(nfa.nfa2dfa()), flags({first, last}){}

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
    return dfa[pos].is_end;
}

std::string TinyRegex::dump() const {
    std::stringstream ss; bool ff = true;

    ss << "digraph G {";
    for(size_t i = 0; i < dfa.size(); i++) {
        if(dfa[i].is_end) {
            ss << (ff ? " " : ", ") << i;
            ff = false;
        }
    }
    ss << " [shape=square];";
    ss << " node [shape=circle]; ";
    for(size_t i = 0; i < dfa.size(); i++)
        for(auto it = dfa[i].refs.cbegin(); it != dfa[i].refs.cend(); it++)
            ss << i << " -> " << it->second << " [label=\"" << it->first << "\"]; ";
    ss << "}";

    return ss.str();
}