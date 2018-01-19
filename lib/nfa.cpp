#include "nfa.h"
#include "dfa.h"
#include <algorithm>
#include <stack>

const char NFA::RULE_UNDEFINED = -1;
const char NFA::RULE_EPSILON = -2;
const long NFA::REF_UNDEFINED = -1;

NFASubsetRef::NFASubsetRef() : start(NFA::REF_UNDEFINED), end(NFA::REF_UNDEFINED) {};

NFAState::NFAState() : rule(NFA::RULE_UNDEFINED), refs(NFA::REF_UNDEFINED, NFA::REF_UNDEFINED) {}

NFA::NFA() : nfa_(), vec_(){}

NFASubsetRef NFA::add_nfa(const char c) {
    nfa_.start = vec_.size();
    nfa_.end = nfa_.start + 1;

    vec_.push_back(NFAState());
    vec_.push_back(NFAState());

    vec_[nfa_.start].rule = c;
    vec_[nfa_.start].refs.first = nfa_.start;

    return nfa_;
}

NFASubsetRef NFA::link(const NFASubsetRef lv, const NFASubsetRef rv) {
    nfa_.start = lv.start;
    nfa_.end = rv.end;

    vec_[nfa_.start].rule = NFA::RULE_EPSILON;
    vec_[nfa_.start].refs.first = rv.start;

    return nfa_;
}

NFASubsetRef NFA::select(const NFASubsetRef lv, const NFASubsetRef rv) {
    nfa_.start = vec_.size();
    nfa_.end = nfa_.start + 1;

    vec_.push_back(NFAState());
    vec_.push_back(NFAState());

    vec_[nfa_.start].rule = NFA::RULE_EPSILON;
    vec_[nfa_.start].refs.first = lv.start;
    vec_[nfa_.start].refs.second = rv.start;

    vec_[lv.end].rule = NFA::RULE_EPSILON;
    vec_[lv.end].refs.first = nfa_.end;

    vec_[rv.end].rule = NFA::RULE_EPSILON;
    vec_[rv.end].refs.first = nfa_.end;

    return nfa_;
}

NFASubsetRef NFA::star(const NFASubsetRef v) {
    nfa_.start = vec_.size();
    nfa_.end = nfa_.start + 1;

    vec_.push_back(NFAState());
    vec_.push_back(NFAState());

    vec_[nfa_.start].rule = NFA::RULE_EPSILON;
    vec_[nfa_.start].refs.first = v.start;
    vec_[nfa_.start].refs.second = nfa_.end;

    vec_[v.end].rule = NFA::RULE_EPSILON;
    vec_[v.end].refs.first = nfa_.start;

    return nfa_;
}

void calculate_epsilon_closure(const std::vector<NFAState> &nss, std::vector<std::set<long>> &ecs, std::vector<bool> &flag, long i) {
    if(flag[i]) return;
    if(nss[i].rule == NFA::RULE_EPSILON) {
        long s1 = nss[i].refs.first, s2 = nss[i].refs.second;
        if(s1 != NFA::REF_UNDEFINED) {
            calculate_epsilon_closure(nss, ecs, flag, s1);
            ecs[i].insert(ecs[s1].begin(), ecs[s1].end());
        }
        if(s2 != NFA::REF_UNDEFINED) {
            calculate_epsilon_closure(nss, ecs, flag, s2);
            ecs[i].insert(ecs[s2].begin(), ecs[s2].end());
        }
    }

    flag[i] = true;
    ecs[i].insert(i);
}

void calculate_epsilon_closures(const std::vector<NFAState> &nss, std::vector<std::set<long>> &ecs) {
    std::vector<bool> is_visited(nss.size(), false);

    for(long i = 0; i < nss.size(); i++) calculate_epsilon_closure(nss, ecs, is_visited, i);

}

DFA NFA::nfa2dfa() {
    std::vector<std::set<long>> epsilon_closures(vec_.size());

    calculate_epsilon_closures(vec_, epsilon_closures);


}