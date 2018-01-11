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

    NFA NFA::operator*() const {
        NFA nfa;
        NFAStateRef start = NFAState::create(), end = NFAState::create();

        start->link_to(this->start(), end);
        this->end()->link_to(start);

        nfa.states.insert({start, end});
        nfa.states.insert(this->states.cbegin(), this->states.cend());
        nfa.start_state = start;
        nfa.end_state = end;

        return nfa;
    }

    NFAStateRef NFA::start() const {
        return this->start_state.lock();
    }

    NFAStateRef NFA::end() const {
        return this->end_state.lock();
    }

    size_t NFA::size() const {
        return this->states.size();
    }

    NFA operator&(const NFA& n1, const NFA& n2) {
        NFA nfa;

        nfa.states.insert(n1.states.cbegin(), n1.states.cend());
        nfa.states.insert(n2.states.cbegin(), n2.states.cend());

        n1.end()->link_to(n2.start());

        nfa.start_state = n1.start();
        nfa.end_state = n2.end();

        return nfa;
    }

    NFA operator|(const NFA& n1, const NFA& n2) {
        NFA nfa;
        NFAStateRef s1 = NFAState::create(), s2 = NFAState::create();

        nfa.states.insert({s1, s2});
        nfa.states.insert(n1.states.cbegin(), n1.states.cend());
        nfa.states.insert(n2.states.cbegin(), n2.states.cend());

        s1->link_to(n1.start(), n2.start());
        n1.end()->link_to(s2);
        n2.end()->link_to(s2);

        nfa.start_state = s1;
        nfa.end_state = s2;

        return nfa;
    }
}

