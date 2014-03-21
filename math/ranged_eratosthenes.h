/**
 *  @file math/ranged_eratosthenes.h
 */
#pragma once
#include <vector>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup ranged_eratosthenes Enumerate primes in range
 *  @ingroup  math
 *  @{
 */

/**
 *  @brief 区間ふるいを用いた素数の列挙
 *
 *  [ low, low + sieve.size() ) の範囲の素数集合を求める。
 *  計算量は \f$ O(B \log{\log{\mathit{low} + B}}) \f$ 程度。
 *  ただし、 \f$ B = \mathit{sieve.size}() \f$。
 *
 *  @tparam        T      篩のデータ型
 *  @param[in]     low    範囲の下限
 *  @param[in,out] sieve  素数集合のビット集合による表現
 *  @return        求めた素数集合の可変長配列による表現
 */
template <typename T>
vector<ll> ranged_eratosthenes(ll low, T &sieve){
	const ll high = low + sieve.size();
	for(int i = 0; i < sieve.size(); ++i){
		sieve[i] = (i + low <= 1 ? 0 : 1);
	}
	ll left = 0, right = high;
	while(left < right){
		const ll center = left + (right - left) / 2;
		if(center * center <= high){
			left = center + 1;
		}else{
			right = center;
		}
	}
	const ll small_sieve_size = max<ll>(left, 2);
	vector<bool> small_sieve(small_sieve_size);
	small_sieve[0] = small_sieve[1] = 1;
	for(ll i = 2; i < small_sieve_size; ++i){
		if(small_sieve[i]){ continue; }
		for(ll j = i + i; j < small_sieve_size; j += i){
			small_sieve[j] = 1;
		}
		const ll init = (low + i - 1) / i * i;
		for(ll j = init + (init == i ? i : 0); j < high; j += i){
			sieve[j - low] = 0;
		}
	}
	vector<ll> primes;
	for(ll i = 0; i < sieve.size(); ++i){
		if(sieve[i]){ primes.push_back(i + low); }
	}
	return primes;
}

/**
 *  @brief 区間ふるいを用いた素数の列挙
 *
 *  [ low, high ) の範囲の素数集合を求める。
 *  計算量は \f$ O(B \log{\log{\mathit{low} + B}}) \f$ 程度。
 *  ただし、 \f$ B = \mathit{high} - \mathit{low} \f$。
 *
 *  @tparam     T     篩のデータ型
 *  @param[in]  low   範囲の下限
 *  @param[in]  high  範囲の上限
 *  @return     求めた素数集合の可変長配列による表現
 */
vector<ll> ranged_eratosthenes(ll low, ll high){
	vector<bool> sieve(high - low);
	return ranged_eratosthenes(low, sieve);
}

/**
 *  @}
 */

}
}

