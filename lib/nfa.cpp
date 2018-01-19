#include <nfa.h>
#include <set>
#include <algorithm>
#include <stack>

const char NFAState::RULE_UNDEFINED = -1;
const char NFAState::RULE_EPSILON = -2;
const long NFAState::REFS_UNDEFINED = -1;

NFAState::NFAState() {
    this->rule = NFAState::RULE_UNDEFINED;
    this->refs.first = -1;
    this->refs.second = -1;
}

NFA NFAStatesVector::add_nfa(const char c) {
    NFA nfa;
    nfa.start = this->vec.size();
    nfa.end = nfa.start + 1;

    this->vec.push_back(NFAState());
    this->vec.push_back(NFAState());

    this->vec[nfa.start].rule = c;
    this->vec[nfa.start].refs.first = nfa.start;

    return nfa;
}

NFA NFAStatesVector::link(const NFA lv, const NFA rv) {
    NFA nfa;

    nfa.start = lv.start;
    nfa.end = rv.end;

    this->vec[nfa.start].rule = NFAState::RULE_EPSILON;
    this->vec[nfa.start].refs.first = rv.start;

    return nfa;
}

NFA NFAStatesVector::select(const NFA lv, const NFA rv) {
    NFA nfa;

    nfa.start = this->vec.size();
    nfa.end = nfa.start + 1;

    this->vec.push_back(NFAState());
    this->vec.push_back(NFAState());

    this->vec[nfa.start].rule = NFAState::RULE_EPSILON;
    this->vec[nfa.start].refs.first = lv.start;
    this->vec[nfa.start].refs.second = rv.start;

    this->vec[lv.end].rule = NFAState::RULE_EPSILON;
    this->vec[lv.end].refs.first = nfa.end;

    this->vec[rv.end].rule = NFAState::RULE_EPSILON;
    this->vec[rv.end].refs.first = nfa.end;

    return nfa;
}

NFA NFAStatesVector::star(const NFA v) {
    NFA nfa;

    nfa.start = this->vec.size();
    nfa.end = nfa.start + 1;

    this->vec.push_back(NFAState());
    this->vec.push_back(NFAState());

    this->vec[nfa.start].rule = NFAState::RULE_EPSILON;
    this->vec[nfa.start].refs.first = v.start;
    this->vec[nfa.start].refs.second = nfa.end;

    this->vec[v.end].rule = NFAState::RULE_EPSILON;
    this->vec[v.end].refs.first = nfa.start;

    return nfa;
}

void calculate_epsilon_closure(const std::vector<NFAState> &nss, std::vector<std::set<long>> &ecs, std::vector<bool> &flag, long i) {
    if(flag[i]) return;
    if(nss[i].rule == NFAState::RULE_EPSILON) {
        long s1 = nss[i].refs.first, s2 = nss[i].refs.second;
        if(s1 != NFAState::REFS_UNDEFINED) {
            calculate_epsilon_closure(nss, ecs, flag, s1);
            ecs[i].insert(ecs[s1].begin(), ecs[s1].end());
        }
        if(s2 != NFAState::REFS_UNDEFINED) {
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

void NFAStatesVector::nfa2dfa(const NFA v) {
    std::vector<std::set<long>> epsilon_closures(this->vec.size());

    calculate_epsilon_closures(this->vec, epsilon_closures);
}