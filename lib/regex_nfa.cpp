#include "tiny_regex/nfa.h"

#include <string>
#include <memory>

namespace tiny_regex {
    NFA::NFA() {
    }

    NFA::NFA(const char rule) {
        NFAStateRef s1 = NFAState::create();
        NFAStateRef s2 = NFAState::create();

        s1->link_to(s2, rule);
        this->states.insert({s1, s2});
        this->start_state = s1;
        this->end_state = s2;
    }

    NFA regex2nfa(std::string regex) {
        NFA nfa;
    }
}

