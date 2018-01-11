#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <set>

namespace tiny_regex {
    struct NFAState;
    struct NFA;

    typedef std::weak_ptr<NFAState> NFAStateWeakRef;
    typedef std::shared_ptr<NFAState> NFAStateRef;

    class NFAState {
    private:
        char trans_rule;
        std::pair<NFAStateWeakRef, NFAStateWeakRef> trans_states;

    public:
        NFAState();

        char rule() const;
        NFAStateRef first() const;
        NFAStateRef second() const;
        void link_to(NFAStateWeakRef s1, const char rule = NFAState::TR_EPSILON);
        void link_to(NFAStateWeakRef s1, NFAStateWeakRef s2, const char rule = NFAState::TR_EPSILON);

        static char TR_UNDEFINED;
        static char TR_EPSILON;

        static NFAStateRef create();
        friend bool operator==(const NFAState& s1, const NFAState& s2);
    };

    class NFA {
    private:
        NFAStateWeakRef start_state;
        NFAStateWeakRef end_state;
        std::set<NFAStateRef> states;

    public:
        NFA();
        NFA(const char rule);
        NFA operator*() const;
        NFAStateRef start() const;
        NFAStateRef end() const;
        size_t size() const;

        friend NFA operator&(const NFA& n1, const NFA& n2);
        friend NFA operator|(const NFA& n1, const NFA& n2);
    };
}


