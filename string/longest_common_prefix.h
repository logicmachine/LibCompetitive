/**
 *  @file string/longest_common_prefix.h
 */
#pragma once
#include "suffix_array.h"

namespace libcomp {
namespace string {

/**
 *  @defgroup longest_common_prefix Longest common prefix
 *  @ingroup  string
 *  @{
 */

/**
 *  @brief Suffix array上での最長共通接頭辞の計算
 *
 *  全てのSuffix array上で隣接した2接尾辞間の共通接頭辞の長さを求める。
 *  計算量は \f$ \mathcal{O}(|s|) \f$
 *
 *  @param[in] sa  最長共通接頭辞を求めるSuffix array
 *  @return    v[i] = sa[i] と sa[i+1] の共通接頭辞の長さとなるベクタ
 */
vector<int> longest_common_prefix(const SuffixArray &sa){
	const int n = sa.size();
	vector<int> isa(n), lcp(n - 1);
	for(int i = 0; i < n; ++i){ isa[sa.position(i)] = i; }
	int h = 0;
	for(int i = 0; i < n; ++i){
		const int s = isa[i];
		if(s > 0){
			const int t = s - 1;
			while(sa[s][h] == sa[t][h]){ ++h; }
			lcp[t] = h;
			if(h > 0){ --h; }
		}
	}
	return lcp;
}

/**
 *  @}
 */

}
}

