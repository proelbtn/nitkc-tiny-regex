#include "tiny_regex.h"

#include <algorithm>
#include <stack>
#include <list>

#include <iostream>

using namespace tiny_regex;

namespace tiny_regex {
    EpsilonTransitionTable nfa2ett(NFA nfa) {
        EpsilonTransitionTable ett;
        std::map<NFAStateRef, bool> is_visited;

        std::for_each(nfa.cbegin(), nfa.cend(), [&](const NFAStateRef& s) {
            ett[s] = std::set<NFAStateRef>({s});
            is_visited[s] = s->rule() != NFAState::TR_EPSILON;
        });

        std::for_each(nfa.cbegin(), nfa.cend(), [&](const NFAStateRef& s) {
            if(is_visited[s]) return;

            std::stack<NFAStateRef> stack;
            stack.push(s);
            while(!stack.empty()) {
                bool flag = true;
                NFAStateRef s_arg = stack.top();
                NFAStateRef first = s_arg->first();
                NFAStateRef second = s_arg->second();

                if (s_arg->rule() == NFAState::TR_EPSILON) {
                    if(first != nullptr && !is_visited[first]) {
                        stack.push(first);
                        flag = false;
                    }
                    if(second != nullptr && !is_visited[second]) {
                        stack.push(second);
                        flag = false;
                    }

                    if(!flag) continue;

                    if(first != nullptr) ett[s_arg].insert(ett[first].cbegin(), ett[first].cend());
                    if(second != nullptr) ett[s_arg].insert(ett[second].cbegin(), ett[second].cend());
                }

                is_visited[s_arg] = true;
                stack.pop();
            }
        });

        return ett;
    }

    void nfa2dfa(NFA nfa) {
        NFAStateRef ns_entry = nfa.entry(), ns_exit = nfa.exit();
        EpsilonTransitionTable ett = nfa2ett(nfa);

        std::list<NFAStateRefSet> ds;
        ds.push_back(ett[ns_entry]);

        for(auto it = ds.begin(); it != ds.end(); it++) {
            std::cout << std::distance(ds.begin(), it) << std::endl;
            std::map<char, NFAStateRefSet> trans_map;

            // nsrsから移動可能なNFAStateRefSetを文字ごとに調べる。
            std::for_each(it->begin(), it->end(), [&](const NFAStateRef& nsr) {
                if(nsr->rule() != NFAState::TR_EPSILON && nsr->rule() != NFAState::TR_UNDEFINED) {
                    NFAStateRef first = nsr->first();
                    NFAStateRef second = nsr->second();

                    // trans_mapに遷移条件の文字に対応する集合がないなら、作る。
                    if(trans_map.find(nsr->rule()) == trans_map.end()) trans_map[nsr->rule()] = NFAStateRefSet();

                    if(first != nullptr) trans_map[nsr->rule()].insert(ett[first].cbegin(), ett[first].cend());
                    if(second != nullptr) trans_map[nsr->rule()].insert(ett[second].cbegin(), ett[second].cend());
                }
            });

            std::for_each(trans_map.begin(), trans_map.end(), [&](const std::pair<char, NFAStateRefSet>& record) {
                char c = record.first;
                NFAStateRefSet set = record.second;

                if(std::find(ds.begin(), ds.end(), set) == ds.end()) ds.push_back(set);
                long nsrs_index = std::distance(ds.begin(), std::find(ds.begin(), ds.end(), *it));
                long set_index = std::distance(ds.begin(), std::find(ds.begin(), ds.end(), set));

                std::cout << nsrs_index << " - " << c << " -> " << set_index << std::endl;
             });
        };
    }
}