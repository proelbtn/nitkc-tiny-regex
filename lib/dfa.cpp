#include <dfa.h>

bool DFAState::operator==(const DFAState &ds) {
    return this->set == ds.set;
}

