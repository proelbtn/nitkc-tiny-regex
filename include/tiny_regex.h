#pragma once

#include "tiny_regex/nfa.h"

#include <map>

namespace tiny_regex {
    typedef std::map<NFAStateRef, NFAStateRefSet> EpsilonTransitionTable;

    EpsilonTransitionTable nfa2ett(NFA nfa);
}

