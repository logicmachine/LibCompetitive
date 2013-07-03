/**
 *  @file math/fft.h
 */
#pragma once
#include "common/header.h"
#include <complex>
#include <algorithm>

namespace libcomp {
namespace math {

/**
 *  @defgroup fft FFT
 *  @ingroup  math
 *  @{
 */

/**
 *  @brief 高速フーリエ変換
 *
 *  Cooley-Tukey法による高速フーリエ変換。
 *  計算量は \f$ \mathcal{O}(n log{n}) \f$
 *
 *  @param[out] dst  変換結果の出力先バッファ
 *  @param[in]  src  入力データの先頭を指すポインタ
 *  @param[in]  n    入力データのサイズ (2のべき乗であること)
 *  @param[in]  inv  逆変換を行う場合にtrueを指定する
 */
void fft(
	complex<double> *dst, const complex<double> *src, int n, bool inv = false)
{
	copy(src, src + n, dst);
	for(int i = 0, j = 1; j < n - 1; ++j){
		for(int k = n >> 1; k > (i ^= k); k >>= 1){ }
		if(j < i){ swap(dst[i], dst[j]); }
	}
	double theta = (inv ? -2.0 : 2.0) * M_PI / n;
	for(int mh = 1; (mh << 1) <= n; mh <<= 1){
		const int m = (mh << 1);
		int irev = 0;
		for(int i = 0; i < n; i += m){
			const complex<double> w = exp(complex<double>(0, theta * irev));
			for(int k = n >> 2; k > (irev ^= k); k >>= 1){ }
			for(int j = i; j < mh + i; ++j){
				const int k = j + mh;
				const complex<double> x = dst[j] - dst[k];
				dst[j] += dst[k];
				dst[k] = w * x;
			}
		}
	}
	if(inv){
		const double r = 1.0 / n;
		for(int i = 0; i < n; ++i){ dst[i] *= r; }
	}
}

/**
 *  @}
 */

}
}

