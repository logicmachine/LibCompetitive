/**
 *  @file math/eratosthenes.h
 */
#pragma once
#include <bitset>
#include <vector>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup eratosthenes Eratosthenes
 *  @ingroup  math
 *  @{
 */

/**
 *  @brief エラトステネスの篩による素数列挙
 *
 *  [0, RANGE) の範囲に含まれる素数集合を可変長配列・ビット集合の形で返す。
 *
 *  @tparam        RANGE  列挙される値の範囲
 *  @param[in,out] sieve  素数集合のビット集合による表現
 *  @return        素数集合の可変長配列による表現
 */
template <int RANGE>
vector<int> eratosthenes(bitset<RANGE> &sieve = bitset<RANGE>()){
	sieve[0] = sieve[1] = true;
	vector<int> primes;
	for(int i = 2; i < RANGE; ++i){
		if(sieve[i]){ continue; }
		primes.push_back(i);
		for(int j = i + i; j < RANGE; j += i){ sieve[j] = true; }
	}
	return primes;
}

/**
 *  @}
 */

}
}

