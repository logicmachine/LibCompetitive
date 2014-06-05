/**
 *  @file misc/ternary_search.h
 */
#pragma once
#include "common/header.h"

namespace libcomp {
namespace misc {

/**
 *  @defgroup ternary_search Ternary search (integer)
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief 汎用三分探索
 *
 *  凸関数 \f$ f(x) \f$ の値を最小化する \f$ x \in [l, r) \f$ を求める。
 *  該当する \f$ x \f$ が複数ある場合は最小のものを返す。
 *  計算量は \f$ \mathcal{O}(\log(r - l)) \f$。
 *
 *  @param[in] l     探索範囲の下限
 *  @param[in] r     探索範囲の下限
 *  @param[in] func  探索対象の関数
 */
template <typename Function>
int ternary_search(int l, int r, const Function &f){
	while(l < r){
		const int delta = (r - l);
		const int cl = l + delta / 3, cr = l + 2 * delta / 3;
		if(f(cl) <= f(cr)){
			r = cr;
		}else{
			l = cl + 1;
		}
	}
	return l;
}

/**
 *  @}
 */

}
}

