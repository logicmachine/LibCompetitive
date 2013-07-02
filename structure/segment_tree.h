/**
 *  @file structure/segment_tree.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include "common/header.h"

namespace libcomp {
namespace structure {

/**
 *  @defgroup structure libcomp::structure
 *  @{
 */

/**
 *  @brief セグメント木
 *  @tparam T         データ型
 *  @tparam DEFAULT   葉の要素の既定値
 *  @tparam Function  二項演算を行う関数オブジェクトの型
 */
template <typename T, T DEFAULT, typename Function>
class SegmentTree {

private:
	vector<T> m_data;		// 節点データ領域
	int m_internal_size;	// 葉の数
	Function m_func;		// 二項演算を行う関数オブジェクト

	void initialize(){
		for(int i = m_internal_size - 2; i >= 0; --i){
			m_data[i] = m_func(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}

	T query(int a, int b, int k, int l, int r) const {
		if(r <= a || b <= l){ return DEFAULT; }
		if(a <= l && r <= b){ return m_data[k]; }
		T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return m_func(vl, vr);
	}

public:
	/**
	 *  @brief コンストラクタ (既定値で初期化)
	 *
	 *  葉をすべて既定値で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(n) \f$。
	 *
	 *  @param[in] n     最低限必要な葉の数
	 *  @param[in] func  計算に用いる二項演算を行う関数オブジェクト
	 */
	explicit SegmentTree(int n, const Function &func = Function()) :
		m_internal_size(1), m_func(func)
	{
		while(m_internal_size < n){ m_internal_size *= 2; }
		m_data = vector<T>(m_internal_size * 2 - 1, DEFAULT);
		initialize();
	}

	/**
	 *  @brief コンストラクタ (要素列による初期化)
	 *
	 *  葉をすべて [begin, end) で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(n) (n = distance(begin, end)) \f$。
	 *
	 *  @param[in] begin  要素列の先頭を指すイテレータ
	 *  @param[in] end    要素列の終端を指すイテレータ
	 *  @param[in] func  計算に用いる二項演算を行う関数オブジェクト
	 */
	template <typename Iterator>
	SegmentTree(
		Iterator begin, Iterator end, const Function &func = Function()) :
		m_internal_size(1), m_func(func)
	{
		const int n = distance(begin, end);
		while(m_internal_size < n){ m_internal_size *= 2; }
		m_data = vector<T>(m_internal_size * 2 - 1, DEFAULT);
		copy(begin, end, m_data.begin());
		initialize();
	}

	/**
	 *  @brief 葉の更新
	 *
	 *  i番目の葉の値をvalで更新する。また、必要に応じて節点の値も更新する。
	 *  計算量は \f$ \mathcal{O}(log{n}) \f$。
	 *
	 *  @param[in] i    更新したい葉のインデックス
	 *  @param[in] val  更新後の値
	 */
	void update(int i, const T &val){
		i += m_internal_size - 1;
		m_data[i] = val;
		while(i > 0){
			i = (i - 1) / 2;
			m_data[i] = m_func(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}

	/**
	 *  @brief 区間についての問い合わせ
	 *
	 *  インデックスが区間 [a, b) に含まれる要素すべてを func で結合した結果を求める。
	 *  計算量は \f$ \mathcal{O}(log{n}) \f$。
	 *
	 *  @param[in] a  区間の始端
	 *  @param[in] b  区間の終端
	 *  @return    計算された結果
	 */
	T query(int a, int b) const {
		return query(a, b, 0, 0, m_internal_size);
	}

};

/**
 *  @}
 */

}
}

