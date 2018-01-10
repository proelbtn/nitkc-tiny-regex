#include "tiny_regex/nfa.h"

#include <memory>

namespace tiny_regex {
    NFAState::NFAState() {
    }

    NFAStateRef NFAState::create() {
        return std::make_shared<NFAState>();
    }

    void NFAState::link_to(NFAStateWeakRef s1, const char rule) {
        this->trans_rules.first.trans_rule = rule;
        this->trans_rules.first.trans_des = s1;
    }

    void NFAState::link_to(NFAStateWeakRef s1, NFAStateWeakRef s2, const char rule) {
        this->trans_rules.first.trans_rule = rule;
        this->trans_rules.first.trans_des = s1;
        this->trans_rules.second.trans_rule = rule;
        this->trans_rules.second.trans_des = s2;
    }
}

