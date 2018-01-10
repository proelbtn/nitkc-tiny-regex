#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <set>

namespace tiny_regex {
    struct NFALink;
    struct NFAState;
    struct NFA;

    typedef std::weak_ptr<NFAState> NFAStateWeakRef;
    typedef std::shared_ptr<NFAState> NFAStateRef;

    struct NFALink {
        static char TR_UNDEFINED;
        static char TR_EPSILON;

        char trans_rule;
        NFAStateWeakRef trans_des;

        NFALink();
    };

    struct NFAState {
        std::pair<NFALink, NFALink> trans_rules;

        NFAState();

        void link_to(NFAStateWeakRef s1, const char rule = NFALink::TR_EPSILON);
        void link_to(NFAStateWeakRef s1, NFAStateWeakRef s2, const char rule = NFALink::TR_EPSILON);

        static NFAStateRef create();
    };

    struct NFA {
        NFAStateWeakRef start_state;
        NFAStateWeakRef end_state;
        std::set<NFAStateRef> states;

        NFA();
        NFA(const char rule);
    };
}


