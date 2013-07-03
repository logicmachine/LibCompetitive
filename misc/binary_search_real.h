/**
 *  @file misc/binary_search_real.h
 */
#pragma once
#include <common/header.h>

namespace libcomp {
namespace misc {

/**
 *  @defgroup binary_search_real Binary Search (real)
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief 汎用二分探索
 *
 *  \f$ f(x) = \mathit{true}, l \le x < r \f$ となる最小の \f$ x \f$ を求める。
 *  計算量は \f$ \mathcal{O}(log(r-l)) \f$。
 *
 *  @param[in] l     探索範囲の下限
 *  @param[in] r     探索範囲の上限
 *  @param[in] func  探索対象の関数
 */
template <typename Function>
double binary_search(double l, double r, const Function &f){
	while(true){
		const double c = l + (r - l) / 2;
		if(c == l){ break; }
		if(f(c)){
			r = c;
		}else{
			l = c;
		}
	}
	return l;
}

/**
 *  @}
 */

}
}

