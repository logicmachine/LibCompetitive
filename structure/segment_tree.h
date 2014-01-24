/**
 *  @file structure/segment_tree.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "common/header.h"

namespace libcomp {
namespace structure {

/**
 *  @defgroup segment_tree Segment tree
 *  @ingroup  structure
 *  @{
 */

/**
 *  @brief  セグメント木による区間最小クエリ
 *  @tparam T  値の型
 */
template <typename T>
struct MinSegmentTreeTraits {
	/// 値型
	typedef T value_type;
	/// 各ノードのデフォルト値
	T default_value() const { return numeric_limits<T>::max(); }
	/// 二項演算を行う関数
	T operator()(const T &a, const T &b) const { return min(a, b); }
};

/**
 *  @brief  セグメント木による区間最大クエリ
 *  @tparam T  値の型
 */
template <typename T>
struct MaxSegmentTreeTraits {
	/// 値型
	typedef T value_type;
	/// 各ノードのデフォルト値
	T default_value() const { return numeric_limits<T>::min(); }
	/// 二項演算を行う関数
	T operator()(const T &a, const T &b) const { return max(a, b); }
};

/**
 *  @brief  セグメント木
 *  @sa MinSegmentTreeTraits
 *  @tparam Traits  セグメント木の動作を示す型
 */
template <typename Traits>
class SegmentTree {

public:
	/// 値型
	typedef typename Traits::value_type value_type;

private:
	Traits m_traits;
	vector<value_type> m_data;
	size_t m_size;

	void initialize(){
		for(int i = static_cast<int>(m_size) - 2; i >= 0; --i){
			m_data[i] = m_traits(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}

	value_type query(int a, int b, int k, int l, int r) const {
		if(r <= a || b <= l){ return m_traits.default_value(); }
		if(a <= l && r <= b){ return m_data[k]; }
		const value_type vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		const value_type vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return m_traits(vl, vr);
	}

public:
	/**
	 *  @brief コンストラクタ (既定値で初期化)
	 *
	 *  葉をすべて既定値で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(n) \f$。
	 *
	 *  @param[in] size    最低限必要な葉の数
	 *  @param[in] traits  処理内容を示す関数オブジェクト
	 */
	explicit SegmentTree(size_t size, const Traits &traits = Traits()) :
		m_size(1), m_traits(traits)
	{
		while(m_size < size){ m_size *= 2; }
		m_data.resize(m_size * 2 - 1, m_traits.default_value());
		initialize();
	}

	/**
	 *  @brief コンストラクタ (要素列による初期化)
	 *
	 *  葉をすべて [first, last) で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(n) (n = distance(first, last)) \f$。
	 *
	 *  @param[in] first   要素列の先頭を指すイテレータ
	 *  @param[in] last    要素列の終端を指すイテレータ
	 *  @param[in] traits  処理内容を示す関数オブジェクト
	 */
	template <typename Iterator>
	SegmentTree(
		Iterator first, Iterator last, const Traits &traits = Traits()) :
		m_size(1), m_traits(traits)
	{
		const size_t n = distance(first, last);
		while(m_size < n){ m_size *= 2; }
		m_data.resize(m_size * 2 - 1, m_traits.default_value());
		copy(first, last, m_data.begin() + m_size - 1);
		initialize();
	}

	/**
	 *  @brief 葉の更新
	 *
	 *  i番目の葉の値をvalで更新する。また、必要に応じて節点の値も更新する。
	 *  計算量は \f$ \mathcal{O}(\log{n}) \f$。
	 *
	 *  @param[in] i    更新したい葉のインデックス
	 *  @param[in] val  更新後の値
	 */
	void update(size_t i, const value_type &val){
		i += m_size - 1;
		m_data[i] = val;
		while(i > 0){
			i = (i - 1) / 2;
			m_data[i] = m_traits(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}

	/**
	 *  @brief 区間についての問い合わせ
	 *
	 *  インデックスが区間 [a, b) に含まれる要素すべてを結合した結果を求める。
	 *  計算量は \f$ \mathcal{O}(\log{n}) \f$。
	 *
	 *  @param[in] a  区間の始端
	 *  @param[in] b  区間の終端
	 *  @return    計算された結果
	 */
	value_type query(size_t a, size_t b) const {
		return query(a, b, 0, 0, m_size);
	}

};

/**
 *  @}
 */

}
}

