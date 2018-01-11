#include "tiny_regex.h"

#include <algorithm>
#include <stack>

#include <iostream>

using namespace tiny_regex;

namespace tiny_regex {
    EpsilonTransitionTable nfa2ett(NFA nfa) {
        EpsilonTransitionTable ett;
        std::map<NFAStateRef, bool> is_visited;

        std::for_each(nfa.cbegin(), nfa.cend(), [&](const NFAStateRef& s) {
            ett[s] = std::set<NFAStateRef>({s});
            is_visited[s] = false;
        });

        std::for_each(nfa.cbegin(), nfa.cend(), [&](const NFAStateRef& s) {
            if(is_visited[s]) return;

            std::stack<NFAStateRef> stack;
            stack.push(s);
            while(!stack.empty()) {
                bool flag = true;
                NFAStateRef ts = stack.top();
                NFAStateRef first = ts->first();
                NFAStateRef second = ts->second();

                if (s->rule() == NFAState::TR_EPSILON) {
                    if(first != nullptr && !is_visited[first]) {
                        stack.push(first);
                        flag = false;
                    }
                    if(second != nullptr && !is_visited[second]) {
                        stack.push(second);
                        flag = false;
                    }
                }


                if(!flag) continue;

                if(first != nullptr) ett[ts].insert(ett[first].cbegin(), ett[first].cend());
                if(second != nullptr) ett[ts].insert(ett[second].cbegin(), ett[second].cend());

                is_visited[ts] = true;
                stack.pop();
            }
        });

        return ett;
    }
}