/*!
 * @file dfa.h
 * @brief DFAを表す諸々の構造体の宣言
 */

#pragma once

#include <map>
#include <vector>

struct DFAState {
    //! この状態が終了状態になるかどうかを示すフラグ
    bool is_end;
    //! 遷移元の文字列と遷移先の状態のインデックスを管理する変数
    std::map<char, long> refs;

    DFAState();
};

typedef std::vector<DFAState> DFA;