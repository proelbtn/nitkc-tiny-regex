#include "tiny_regex/nfa.h"

#include <memory>

namespace tiny_regex {
    char NFAState::TR_UNDEFINED = -1;
    char NFAState::TR_EPSILON = -2;

    NFAState::NFAState() {
        this->trans_rule = NFAState::TR_UNDEFINED;
    }

    char NFAState::rule() const {
        return this->trans_rule;
    }

    NFAStateRef NFAState::first() const {
        return this->trans_states.first.lock();
    }

    NFAStateRef NFAState::second() const {
        return this->trans_states.second.lock();
    }

    void NFAState::link_to(NFAStateWeakRef s1, const char rule) {
        this->trans_rule = rule;
        this->trans_states.first = s1;
    }

    void NFAState::link_to(NFAStateWeakRef s1, NFAStateWeakRef s2, const char rule) {
        this->trans_rule = rule;
        this->trans_states.first = s1;
        this->trans_states.second = s2;
    }

    void NFAState::copy_from(NFAStateWeakRef ws) {
        NFAStateRef s = ws.lock();
        this->trans_rule = s->trans_rule;
        this->trans_states.first = s->trans_states.first;
        this->trans_states.second = s->trans_states.second;
    }

    NFAStateRef NFAState::create() {
        return std::make_shared<NFAState>();
    }

    bool operator==(const NFAState& s1, const NFAState& s2) {
        return s1.first() == s2.first() && s1.second() == s2.second();
    }
}

