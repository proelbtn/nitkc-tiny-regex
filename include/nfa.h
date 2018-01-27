/*!
 * @file nfa.h
 * @brief NFAを表す諸々の構造体の宣言
 */

#pragma once

#include <vector>
#include <utility>

#include "dfa.h"

struct NFASubsetRef {
    //! 正規表現の最初の状態を指し示す変数
    long start;
    //! 正規表現の最後の状態を指し示す変数
    long end;

    NFASubsetRef();
};

struct NFAState {
    //! この状態から遷移するときの条件
    char rule;
    //! この状態から遷移する遷移先の状態
    std::pair<long, long> refs;

    NFAState();
};

struct NFA {
    //! もっとも最後に作成された正規表現を指し示すポインタ
    NFASubsetRef nfa;
    //! NFAの状態を保持している動的配列
    std::vector<NFAState> vec;

    static const char RULE_UNDEFINED;
    static const char RULE_EPSILON;
    static const long REF_UNDEFINED;

    NFA();

    /**
     * cという正規表現をNFAに追加する。
     *
     * @param c マッチさせる文字
     * @return cという正規表現を指し示すポインタ
     *
     * @code
     * NFA nfa;
     *
     * // aと等価な正規表現
     * NFASubsetRef nsa = nfa.ch('a');
     * @endcode
     */
    NFASubsetRef ch(const char c);

    /**
     * lvが指し示すの正規表現とrvが指し示す正規表現を結合した正規表現をNFAに追加する。
     *
     * @param lv 正規表現を指し示すポインタ
     * @param rv 正規表現を指し示すポインタ
     * @return lrが指し示す正規表現とrvが指し示す正規表現を結合した正規表現を指し示すポインタ
     *
     * @code
     * NFA nfa;
     *
     * NFASubsetRef nsa = nfa.ch('a'), nsb = nfa.ch('b');
     *
     * // abと等価な正規表現
     * NFASubsetRef ns = nfa.link(nsa, nsb);
     * @endcode
     */
    NFASubsetRef link(const NFASubsetRef lv, const NFASubsetRef rv);

    /**
     * lvが指し示すの正規表現とrvが指し示す正規表現を選択する正規表現をNFAに追加する。
     *
     * @param lv 正規表現を指し示すポインタ
     * @param rv 正規表現を指し示すポインタ
     * @return lrが指し示す正規表現とrvが指し示す正規表現を選択する正規表現を指し示すポインタ
     *
     * @code
     * NFA nfa;
     *
     * NFASubsetRef nsa = nfa.ch('a'), nsb = nfa.ch('b');
     *
     * // (a|b)
     * NFASubsetRef ns = nfa.select(nsa, nsb);
     * @endcode
     */
    NFASubsetRef select(const NFASubsetRef lv, const NFASubsetRef rv);

    /**
     * lvが指し示すの正規表現を0回以上繰り返す正規表現をNFAに追加する。
     *
     * @param v 正規表現を指し示すポインタ
     * @return vが指し示す正規表現を0回以上繰り返す正規表現を指し示すポインタ
     *
     * @code
     * NFA nfa;
     *
     * NFASubsetRef nsa = nfa.ch('a');
     *
     * // a*と等価な正規表現
     * NFASubsetRef ns = nfa.star(nsa);
     * @endcode
     */
    NFASubsetRef star(const NFASubsetRef v);

    /**
     * lvが指し示すの正規表現を0回か1回繰り返す正規表現をNFAに追加する。
     *
     * @param v 正規表現を指し示すポインタ
     * @return vが指し示す正規表現を0回か1回繰り返す正規表現を指し示すポインタ
     *
     * @code
     * NFA nfa;
     *
     * NFASubsetRef nsa = nfa.ch('a');
     *
     * // a?と等価な正規表現
     * NFASubsetRef ns = nfa.question(nsa);
     * @endcode
     */
    NFASubsetRef question(const NFASubsetRef v);

    /**
     * sからeのどれかの文字にヒットする正規表現をNFAに追加する。
     * @param s 文字の範囲の始端
     * @param e 文字の範囲の終端
     * @return sからeのどれかの文字にヒットする正規表現を指し示すポインタ
     * @code
     * NFA nfa;
     *
     * // [0-9]と等価な正規表現
     * NFASubsetRef ns = nfa.range('0', '9');
     * @endcode
     */
    NFASubsetRef range(const char s, const char e);

    /**
     * list内のどれかの文字にヒットする正規表現をNFAに追加する。
     * @param list 文字のリスト
     * @return list内のどれかの文字にヒットする正規表現を指し示すポインタ
     * @code
     * NFA nfa;
     *
     * // [question]と等価な正規表現
     * NFASubsetRef ns = nfa.one_of("question");
     * @endcode
     */
    NFASubsetRef one_of(const char *list);

    /**
     * アルファベットか数字にヒットする正規表現をNFAに追加する。
     * @return アルファベットか数字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef alnum();

    /**
     * アルファベットにヒットする正規表現をNFAに追加する。
     * @return アルファベットにヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef alpha();

    /**
     * スペースかタブ文字にヒットする正規表現をNFAに追加する。
     * @return スペースかタブ文字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef blank();

    /**
     * 数字にヒットする正規表現をNFAに追加する。
     * @return 数字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef digit();

    /**
     * アルファベット，数字, 記号にヒットする正規表現をNFAに追加する。
     * @return アルファベット, 数字，記号にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef graph();

    /**
     * 英小文字にヒットする正規表現をNFAに追加する。
     * @return 英小文字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef lower();

    /**
     * アルファベット，数字, 記号, スペースにヒットする正規表現をNFAに追加する。
     * @return アルファベット, 数字，記号にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef print();

    /**
     * 記号にヒットする正規表現をNFAに追加する。
     * @return アルファベット, 数字，記号にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef punct();

    /**
     * 英大文字にヒットする正規表現をNFAに追加する。
     * @return 英大文字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef upper();

    /**
     * 16進数の文字にヒットする正規表現をNFAに追加する。
     * @return 16進数の文字にヒットする正規表現を指し示すポインタ
     */
    NFASubsetRef xdigit();

    /**
     * NFAの状態に添字アクセスするための演算子オーバーロード。
     * ほぼテスト用に実装しているので、基本的にはこれを利用することはない。
     * NFA::vec::operator[]と書くのが面倒なので、NFA::operator[]と書けるようにしただけのもの。
     * @param i インデックス
     * @return NFAの状態を示す要素への参照
     */
    const NFAState& operator[](unsigned long i) const;


    /**
     * 現在のNFAの状態と等価なDFAを生成するメソッド
     * @return 現在のNFAの状態と等価なDFA
     */
    DFA nfa2dfa();
};