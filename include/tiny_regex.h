/*!
 * @file tiny_regex.h
 * @brief TinyRegexクラスの宣言
 */

#pragma once

#include <string>

#include <nfa.h>
#include <dfa.h>

class TinyRegex {
    //! 入力された正規表現に対応するDFA
    DFA dfa;

    //! ^, $がついていたかを示すフラグ
    struct {
        bool first;
        bool last;
    } flags;

public:
    /**
     * 正規表現エンジンを生成する。部分的な正規表現しかサポートしていない。
     * @param regex 正規表現を表す文字列
     */
    TinyRegex(std::string regex);

    /**
     * 正規表現エンジンを生成する。
     * @param nfa 正規表現を表すNFA
     * @param first 文字列の先頭から始まる場合のみ許す場合にはtrue
     * @param last 文字列の末尾で終わる場合のみ許す場合にはtrue
     */
    TinyRegex(NFA nfa, bool first, bool last);

    /**
     * txtが正規表現にマッチするかどうかを調べる
     * @param txt 検査文字列
     * @return マッチしたかどうか
     */
    bool test(const std::string &txt) const;

    /**
     * 正規表現を表すDFAを文字列としてダンプする。複雑な正規表現が正しく変換されているのかを確かめるために用いる。
     * dot言語でダンプを吐き出すので、それをコンパイルするとオートマトンが得られる。
     * @return 正規表現を表すオートマトンを表すdot言語のソースコード
     */
    std::string dump() const;
};