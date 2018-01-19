#include <nfa.h>

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

    nfa.start = this->vec.size();
    nfa.end = nfa.start + 1;

    this->vec.push_back(NFAState());
    this->vec.push_back(NFAState());

    this->vec[nfa.start].rule = NFAState::RULE_EPSILON;
    this->vec[nfa.start].refs.first = lv.start;

    this->vec[lv.end].rule = NFAState::RULE_EPSILON;
    this->vec[lv.end].refs.first = rv.start;

    this->vec[rv.end].rule = NFAState::RULE_EPSILON;
    this->vec[rv.end].refs.first = nfa.end;

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