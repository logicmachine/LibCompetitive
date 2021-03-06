/**
 *  @file math/matrix.h
 */
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include "common/header.h"

namespace libcomp {
namespace math {

/**
 *  @defgroup matrix Matrix
 *  @ingroup  math
 *  @{
 */

/**
 *  @brief 可変サイズ行列
 *
 *  実行時にサイズ設定可能な行列型。
 *
 *  @tparam T  要素の表現に用いる型
 */
template <typename T>
class Matrix {

private:
	int N, M;
	vector< vector<T> > data;

	template <typename _Func>
	Matrix<T> apply(_Func f) const {
		Matrix<T> ret(N, M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j]); }
		}
		return ret;
	}

	template <typename _Func>
	Matrix<T> apply_scalar(const T &s, _Func f) const { return apply(bind2nd(f, s)); }

	template <typename _Func>
	Matrix<T> apply_mat(const Matrix<T> &m, _Func f) const {
		assert(N == m.N && M == m.M);
		Matrix<T> ret(N, M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j], m(i, j)); }
		}
		return ret;
	}

public:
	/**
	 *  @brief コンストラクタ
	 *  @param[in] N  行列の行数
	 *  @param[in] M  行列の列数
	 */
	Matrix(int N, int M) : N(N), M(M), data(N, vector<T>(M)) { }

	/**
	 *  @brief 行列の行数の取得
	 *  @return 行列の行数
	 */
	int rows() const { return N; }
	/**
	 *  @brief 行列の列数の取得
	 *  @return 行列の列数
	 */
	int columns() const { return M; }

	/**
	 *  @brief 行列内の要素の取得
	 *  @param[in] i  取得したい要素の行番号
	 *  @param[in] j  取得したい要素の列番号
	 *  @return    指定したインデックスに対応する要素への参照
	 */
	const T &operator()(int i, int j) const { return data[i][j]; }
	/**
	 *  @brief 行列内の要素の取得
	 *  @param[in] i  取得したい要素の行番号
	 *  @param[in] j  取得したい要素の列番号
	 *  @return    指定したインデックスに対応する要素への参照
	 */
	T &operator()(int i, int j){ return data[i][j]; }

	/**
	 *  @brief 行列の符号を反転
	 *  @return すべての要素の正負が入れ替えられた行列
	 */
	Matrix<T> operator-() const { return apply(negate<T>()); }

	/**
	 *  @brief 行列とスカラの加算
	 *  @param[in] s  加算するスカラ
	 *  @return    すべての要素にsを加算した行列
	 */
	Matrix<T> operator+(const T &s) const { return apply_scalar(s, plus<T>()); }
	/**
	 *  @brief 行列とスカラの加算 + 代入
	 *  @param[in] s  加算するスカラ
	 *  @return    自身への参照
	 */
	Matrix<T> &operator+=(const T &s){ return *this = *this + s; }

	/**
	 *  @brief 行列とスカラの減算
	 *  @param[in] s  減算するスカラ
	 *  @return    すべての要素にsを減算した行列
	 */
	Matrix<T> operator-(const T &s) const { return apply_scalar(s, minus<T>()); }
	/**
	 *  @brief 行列とスカラの減算 + 代入
	 *  @param[in] s  減算するスカラ
	 *  @return    自身への参照
	 */
	Matrix<T> &operator-=(const T &s){ return *this = *this - s; }

	/**
	 *  @brief 行列とスカラの乗算
	 *  @param[in] s  乗算するスカラ
	 *  @return    すべての要素にsを乗算した行列
	 */
	Matrix<T> operator*(const T &s) const { return apply_scalar(s, multiplies<T>()); }
	/**
	 *  @brief 行列とスカラの乗算 + 代入
	 *  @param[in] s  乗算するスカラ
	 *  @return    自身への参照
	 */
	Matrix<T> &operator*=(const T &s){ return *this = *this * s; }

	/**
	 *  @brief 行列とスカラの除算
	 *  @param[in] s  除算するスカラ
	 *  @return    すべての要素にsを除算した行列
	 */
	Matrix<T> operator/(const T &s) const { return apply_scalar(s, divides<T>()); }
	/**
	 *  @brief 行列とスカラの除算 + 代入
	 *  @param[in] s  除算するスカラ
	 *  @return    自身への参照
	 */
	Matrix<T> &operator/=(const T &s){ return *this = *this / s; }

	/**
	 *  @brief 行列とスカラの剰余
	 *  @param[in] s  剰余を取るスカラ
	 *  @return    すべての要素にsとの剰余をとった行列
	 */
	Matrix<T> operator%(const T &s) const { return apply_scalar(s, modulus<T>()); }
	/**
	 *  @brief 行列とスカラの剰余 + 代入
	 *  @param[in] s  剰余を取るスカラ
	 *  @return    自身への参照
	 */
	Matrix<T> &operator%=(const T &s){ return *this = *this % s; }

	/**
	 *  @brief 行列と行列の加算
	 *  @param[in] m  加算する行列
	 *  @return    (*this)とmの和
	 */
	Matrix<T> operator+(const Matrix<T> &m) const { return apply_mat(m, plus<T>()); }
	/**
	 *  @brief 行列と行列の加算 + 代入
	 *  @param[in] m  加算する行列
	 *  @return    自身への参照
	 */
	Matrix<T> &operator+=(const Matrix<T> &m){ return *this = *this + m; }

	/**
	 *  @brief 行列と行列の減算
	 *  @param[in] m  減算する行列
	 *  @return    (*this)とmの差
	 */
	Matrix<T> operator-(const Matrix<T> &m) const { return apply_mat(m, minus<T>()); }
	/**
	 *  @brief 行列と行列の減算 + 代入
	 *  @param[in] m  減算する行列
	 *  @return    自身への参照
	 */
	Matrix<T> &operator-=(const Matrix<T> &m){ return *this = *this - m; }

	/**
	 *  @brief 行列と行列の乗算
	 *  @param[in] m  乗算する行列
	 *  @return    (*this)とmの積
	 */
	Matrix<T> operator*(const Matrix<T> &m) const {
		assert(M == m.N);
		Matrix<T> ret(N, m.M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < m.M; ++j){
				for(int k = 0; k < M; ++k){ ret(i, j) += data[i][k] * m(k, j); }
			}
		}
		return ret;
	}
	/**
	 *  @brief 行列と行列の乗算 + 代入
	 *  @param[in] m  乗算する行列
	 *  @return    自身への参照
	 */
	Matrix<T> &operator*=(const Matrix<T> &m){ return *this = *this * m; }

	/**
	 *  @brief 行の入れ替え
	 *  @param[in] a  入れ替える行
	 *  @param[in] b  入れ替える行
	 */
	void swap_rows(int a, int b){
		if(a == b){ return; }
		data[a].swap(data[b]);
	}

	/**
	 *  @brief 列の入れ替え
	 *  @param[in] a  入れ替える列
	 *  @param[in] b  入れ替える列
	 */
	void swap_columns(int a, int b){
		if(a == b){ return; }
		for(int i = 0; i < N; ++i){ swap(data[i][a], data[i][b]); }
	}

	/**
	 *  @brief 行列の階数
	 *
	 *  行列の階数 rank(A) を求める。
	 *  計算量は $\f \mathcal{O}(N^2 M) $\f。
	 *
	 *  @return 行列の階数
	 */
	int rank() const {
		const double EPS = 1e-10;
		Matrix<double> A(N, M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ A(i, j) = (*this)(i, j); }
		}
		int r = 0;
		for(int i = 0; r < N && i < M; ++i){
			int max_r = r;
			for(int j = r + 1; j < N; ++j){
				if(::abs(A(j, i)) > ::abs(A(max_r, i))){ max_r = j; }
			}
			if(::abs(A(max_r, i)) < EPS){ continue; }
			A.swap_rows(max_r, r);
			const double x = 1.0 / A(r, i);
			for(int j = i; j < M; ++j){ A(r, j) *= x; }
			for(int j = r + 1; j < N; ++j){
				const double y = A(j, i);
				for(int k = i; k < M; ++k){ A(j, k) -= A(r, k) * y; }
			}
			++r;
		}
		return r;
	}

};

/**
 *  @brief 行列の出力
 *  @param[in,out] os  出力先ストリーム
 *  @param[in]     m   出力する行列
 *  @return        出力先ストリーム
 */
template <typename T>
ostream &operator<<(ostream &os, const Matrix<T> &m){
	for(int i = 0; i < m.rows(); ++i){
		for(int j = 0; j < m.columns(); ++j){ os << m(i, j) << "\t"; }
		os << endl;
	}
	return os;
}

/**
 *  @}
 */

}
}

