/**
 *  @file misc/binary_search_integer.h
 */
#pragma once
#include <common/header.h>

namespace libcomp {
namespace misc {

/**
 *  @defgroup binary_search_integer Binary search (integer)
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief 汎用二分探索
 *
 *  \f$ f(x) = \mathit{true}, x \in [l, r) \f$ となる最小の \f$ x \f$ を求める。
 *  条件を満たす \f$ x \f$ が存在しない場合は \f$ r \f$ を返す。
 *  計算量は \f$ \mathcal{O}(log(r-l)) \f$。
 *
 *  @param[in] l     探索範囲の下限
 *  @param[in] r     探索範囲の上限
 *  @param[in] func  探索対象の関数
 */
template <typename Function>
int binary_search(int l, int r, const Function &f){
	while(l < r){
		const int c = l + (r - l) / 2;
		if(f(c)){
			r = c;
		}else{
			l = c + 1;
		}
	}
	return l;
}

/**
 *  @}
 */

}
}

