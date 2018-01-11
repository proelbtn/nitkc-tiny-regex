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

        start->link_to(this->entry(), end);
        this->exit()->link_to(start);

        nfa.states.insert({start, end});
        nfa.states.insert(this->cbegin(), this->cend());
        nfa.start_state = start;
        nfa.end_state = end;

        return nfa;
    }

    NFAStateRef NFA::entry() const {
        return this->start_state.lock();
    }

    NFAStateRef NFA::exit() const {
        return this->end_state.lock();
    }

    NFAStateRefSet::const_iterator NFA::cbegin() const {
        return this->states.cbegin();
    }

    NFAStateRefSet::const_iterator NFA::cend() const {
        return this->states.cend();
    }

    size_t NFA::size() const {
        return this->states.size();
    }

    NFA operator&(const NFA& n1, const NFA& n2) {
        NFA nfa;

        nfa.states.insert(n1.cbegin(), n1.cend());
        nfa.states.insert(n2.cbegin(), n2.cend());

        n1.exit()->link_to(n2.entry());

        nfa.start_state = n1.entry();
        nfa.end_state = n2.exit();

        return nfa;
    }

    NFA operator|(const NFA& n1, const NFA& n2) {
        NFA nfa;
        NFAStateRef s1 = NFAState::create(), s2 = NFAState::create();

        nfa.states.insert({s1, s2});
        nfa.states.insert(n1.cbegin(), n1.cend());
        nfa.states.insert(n2.cbegin(), n2.cend());

        s1->link_to(n1.entry(), n2.entry());
        n1.exit()->link_to(s2);
        n2.exit()->link_to(s2);

        nfa.start_state = s1;
        nfa.end_state = s2;

        return nfa;
    }
}

