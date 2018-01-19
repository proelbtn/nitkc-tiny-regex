#pragma once

#include <map>
#include <vector>

struct DFAState {
    bool is_end;
    std::map<char, long> refs;

    DFAState();
};

typedef std::vector<DFAState> DFA;