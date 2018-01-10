#include "tiny_regex/nfa.h"

namespace tiny_regex {
    char NFALink::TR_UNDEFINED = -1;
    char NFALink::TR_EPSILON = -2;

    NFALink::NFALink() {
        this->trans_rule = NFALink::TR_UNDEFINED;
    }
}

