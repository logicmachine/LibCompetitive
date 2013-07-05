/**
 *  @file math/linear_equation_lu.h
 */
#pragma once
#include <vector>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup linear_equation_lu Linear equation (LU decomposition)
 *  @ingroup  math
 *  @{
 */

/**
 *  @brief LU分解による連立1次方程式の求解
 *
 *  連立1次方程式 
 *  \f{eqnarray}{
 *      \begin{cases}
 *        A_{11} x_1 + A_{12} x_2 + ... A_{1n} x_n = b_1 & \\
 *        A_{21} x_1 + A_{22} x_2 + ... A_{2n} x_n = b_2 & \\
 *        \vdots & \\
 *        A_{n1} x_1 + A_{n2} x_2 + ... A_{nn} x_n = b_n
 *      \end{cases} \nonumber
 *  \f}
 *  の解 \f$ (x_1, x_2, ... x_n) \f$ を求める。
 *  計算量は \f$ \mathcal{O}(n^3) \f$。
 *
 *  @param[in] a  係数行列
 *  @param[in] b  右辺値
 *  @return    方程式の解。見つからない場合は空のベクタを返す。
 */
vector<double> linear_equation_lu(
	vector< vector<double> > a, vector<double> b)
{
	const int n = b.size();
	for(int i = 0; i < n; ++i){
		int max_row = i;
		for(int j = i + 1; j < n; ++j){
			if(a[j][i] > a[max_row][i]){ max_row = j; }
		}
		if(max_row != i){
			a[i].swap(a[max_row]);
			swap(b[i], b[max_row]);
		}
		const double r = 1.0 / a[i][i];
		for(int j = i; j < n; ++j){ a[i][j] *= r; }
		b[i] *= r;
		for(int j = i + 1; j < n; ++j){
			if(a[j][i] == 0.0){ continue; }
			const double q = a[j][i];
			for(int k = i; k < n; ++k){ a[j][k] -= a[i][k] * q; }
			b[j] -= b[i] * q;
		}
	}
	for(int i = n - 2; i >= 0; --i){
		for(int j = i + 1; j < n; ++j){
			if(a[j][j] == 0.0){ return vector<double>(); }
			const double r = a[i][j] / a[j][j];
			a[i][j] -= a[j][j] * r;
			b[i] -= b[j] * r;
		}
	}
	return b;
}

/**
 *  @}
 */

}
}


