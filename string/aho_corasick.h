/**
 *  @file aho_corasick.h
 */
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include "common/header.h"

namespace libcomp {
namespace string {

/**
 *  @defgroup aho_corasick Aho-Corasick
 *  @ingroup  string
 *  @{
 */

/**
 *  @brief Aho-Corasick法によるパターンマッチオートマトン生成
 */
class AhoCorasick {

private:
	struct State {
		int next[256];
		int failure;
		vector<int> accept;
		State() : failure(0), accept() { fill(next, next + 256, -1); }
	};

	vector<State> m_states;

	int get_next(int i, int j) const {
		if(m_states[i].next[j] >= 0){
			return m_states[i].next[j];
		}else if(i == 0){
			return 0;
		}else{
			return -1;
		}
	}

public:
	/**
	 *  @brief コンストラクタ
	 *
	 *  patternsに含まれる文字列からパターンマッチオートマトンを生成する。
	 *  計算量は \f$ \mathcal{O}(\sum {|S_i|}) \f$。
	 *
	 *  @param[in] patterns  パタンマッチオートマトンに含める文字列集合
	 */
	explicit AhoCorasick(const vector<std::string> &patterns) : m_states() {
		vector<State> &ss = m_states;
		ss.push_back(State());
		// Make trie
		for(size_t i = 0; i < patterns.size(); ++i){
			const std::string &s = patterns[i];
			int cur = 0;
			for(size_t j = 0; j < s.size(); ++j){
				const unsigned char c = s[j];
				if(ss[cur].next[c] < 0){
					ss[cur].next[c] = static_cast<int>(ss.size());
					ss.push_back(State());
				}
				cur = ss[cur].next[c];
			}
			ss[cur].accept.push_back(static_cast<int>(i));
		}
		// Make failure paths
		queue<int> q;
		q.push(0);
		while(!q.empty()){
			const int s = q.front();
			q.pop();
			for(int i = 0; i < 256; ++i){
				if(ss[s].next[i] < 0){ continue; }
				const int next = get_next(s, i);
				if(next >= 0){ q.push(next); }
				if(s != 0){
					int f = ss[s].failure;
					while(get_next(f, i) < 0){ f = ss[f].failure; }
					const int failure = get_next(f, i);
					ss[next].failure = failure;
					const vector<int> &acc = ss[failure].accept;
					copy(
						acc.begin(), acc.end(),
						back_inserter(ss[next].accept));
				}
			}
		}
	}

	/**
	 *  @brief 文字列からの検索
	 *
	 *  パターンマッチオートマトンを利用してパターンを検索する。
	 *  計算量は \f$ \mathcal{O}(|s| + \sum {|S_i|}) \f$。
	 *
	 *  @param[in]  s         検索対象の文字列
	 *  @param[out] counters  パターンが何回ずつ見つかったかを保存するバッファ
	 *  @param[in]  state     開始ステート (0なら先頭から検索)
	 *  @return     文字列の終端までオートマトンをたどったあとの状態番号
	 */
	int match(
		const std::string &s, vector<int> &counters, int state = 0) const
	{
		const vector<State> &ss = m_states;
		for(size_t i = 0; i < s.size(); ++i){
			const unsigned char c = s[i];
			while(get_next(state, c) < 0){ state = ss[state].failure; }
			state = get_next(state, c);
			for(size_t j = 0; j < ss[state].accept.size(); ++j){
				++counters[ss[state].accept[j]];
			}
		}
		return state;
	}

	/**
	 *  @brief オートマトンのサイズ取得
	 *
	 *  パターンマッチオートマトンの状態数を取得する。
	 *
	 *  @return  現在のパターンマッチオートマトンに含まれる状態の数
	 */
	size_t size() const { return m_states.size(); }

};

/**
 *  @}
 */

}
}

