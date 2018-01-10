#include <gtest/gtest.h>
#include "tiny_regex/nfa.h"

using namespace tiny_regex;

TEST(NFA, SINGLE_CHAR_CONSTRUCTOR) {
    const char rule = 'a';
    NFA n(rule);
    ASSERT_EQ(rule, n.start_state.lock()->trans_rules.first.trans_rule);
    ASSERT_EQ(n.end_state.lock(), n.start_state.lock()->trans_rules.first.trans_des.lock());
}