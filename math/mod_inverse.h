/**
 *  @file math/mod_inverse.h
 */
#pragma once
#include <utility>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup math libcomp::math
 *  @{
 */

pair<ll, ll> extgcd(ll a, ll b){
	ll g = a, x = 1, y = 0;
	if(b != 0){
		pair<ll, ll> p = extgcd(b, a % b);
		x = p.second;
		y = p.first - (a / b) * x;
	}
	return make_pair(x, y);
}

/**
 *  @brief mを法とした時のaの逆元を求める
 *
 *  @param[in] a  対象とする値a
 *  @param[in] m  法とする値
 *  @return    \f$ ax \equiv 1 \pmod{m} \f$ となる \f$ x \f$
 */
ll mod_inverse(ll a, ll m){
	pair<ll, ll> p = extgcd(a, m);
	return (m + p.first % m) % m;
}

/**
 *  @}
 */

}
}

