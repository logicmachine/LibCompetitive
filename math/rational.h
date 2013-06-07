/**
 *  @file math/rational.h
 */
#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup math_rational libcomp::math::Rational
 *  @{
 */

/**
 *  @brief 有理数
 *
 *  分子・分母のペアによって表現される有理数型。
 *  値は常に既約分数となる。
 *
 *  @note  環境によっては__gcdがエラーになるので適宜gcdを定義すること
 */
class Rational {

private:
	ll n, d;

	void reduce(){
		ll gcd = __gcd(llabs(n), llabs(d));
		n /= gcd; d /= gcd;
		if(d < 0){ n = -n; d = -d; }
	}

public:
	/**
	 *  @brief コンストラクタ
	 *  @param[in] nume  分子
	 *  @param[in] deno  分母
	 */
	Rational(ll nume = 0, ll deno = 1) : n(nume), d(deno) { reduce(); }

	/**
	 *  @brief 分子の取得
	 *  @return 有理数の分子の値
	 */
	int nume() const { return n; }
	/**
	 *  @brief 分母の取得
	 *  @return 有理数の分母の値
	 */
	int deno() const { return d; }

	/**
	 *  @brief 有理数同士の加算
	 *  @param[in] r  加算する値
	 *  @return    加算した結果
	 */
	Rational operator+(const Rational &r) const {
		return Rational(n * r.d + r.n * d, d * r.d);
	}
	/**
	 *  @brief 有理数同士の加算 + 代入
	 *  @param[in] r  加算する値
	 *  @return    自身への参照
	 */
	Rational &operator+=(const Rational &r){ return *this = *this + r; }

	/**
	 *  @brief 有理数同士の減算
	 *  @param[in] r  減算する値
	 *  @return    減算した結果
	 */
	Rational operator-(const Rational &r) const {
		return Rational(n * r.d - r.n * d, d * r.d);
	}
	/**
	 *  @brief 有理数同士の減算 + 代入
	 *  @param[in] r  減算する値
	 *  @return    自身への参照
	 */
	Rational &operator-=(const Rational &r){ return *this = *this - r; }

	/**
	 *  @brief 有理数同士の乗算
	 *  @param[in] r  乗算する値
	 *  @return    乗算した結果
	 */
	Rational operator*(const Rational &r) const {
		return Rational(n * r.n, d * r.d);
	}
	/**
	 *  @brief 有理数同士の乗算 + 代入
	 *  @param[in] r  乗算する値
	 *  @return    自身への参照
	 */
	Rational &operator*=(const Rational &r){ return *this = *this * r; }

	/**
	 *  @brief 有理数同士の除算
	 *  @param[in] r  除算する値
	 *  @return    除算した結果
	 */
	Rational operator/(const Rational &r) const {
		return Rational(n * r.d, d * r.n);
	}
	/**
	 *  @brief 有理数同士の除算 + 代入
	 *  @param[in] r  除算する値
	 *  @return    自身への参照
	 */
	Rational &operator/=(const Rational &r){ return *this = *this / r; }

	/**
	 *  @brief 有理数同士の比較 (<)
	 *  @param[in] r      比較する値
	 *  @retval    true   (*this) < r の場合
	 *  @retval    false  (*this) >= r の場合
	 */
	bool operator<(const Rational &r) const { return n * r.d < r.n * d; }
	/**
	 *  @brief 有理数同士の比較 (<=)
	 *  @param[in] r      比較する値
	 *  @retval    true   (*this) <= r の場合
	 *  @retval    false  (*this) > r の場合
	 */
	bool operator<=(const Rational &r) const { return n * r.d <= r.n * d; }
	/**
	 *  @brief 有理数同士の比較 (>)
	 *  @param[in] r      比較する値
	 *  @retval    true   (*this) > r の場合
	 *  @retval    false  (*this) <= r の場合
	 */
	bool operator>(const Rational &r) const { return n * r.d > r.n * d; }
	/**
	 *  @brief 有理数同士の比較 (>=)
	 *  @param[in] r      比較する値
	 *  @retval    true   (*this) >= r の場合
	 *  @retval    false  (*this) < r の場合
	 */
	bool operator>=(const Rational &r) const { return n * r.d >= r.n * d; }

};

/**
 *  @brief 有理数の出力
 *  @param[in,out] os  出力先ストリーム
 *  @param[in]     r   出力する値
 *  @return 出力先ストリーム
 */
ostream &operator<<(ostream &os, const Rational &r){
	os << r.nume() << "/" << r.deno();
	return os;
}

/**
 *  @}
 */

}
}

