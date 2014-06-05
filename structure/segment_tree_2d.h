/**
 *  @file structure/segment_tree_2d.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include "common/header.h"
#include "structure/segment_tree.h"

namespace libcomp {
namespace structure {

/**
 *  @defgroup segment_tree_2d 2D segment tree
 *  @ingroup  structure
 *  @{
 */

/**
 *  @brief  2次元セグメント木
 *  @tparam Traits  セグメント木の動作を示す型
 */
template <typename Traits>
class SegmentTree2D {

public:
	/// 値型
	typedef typename Traits::value_type value_type;

private:
	Traits m_traits;
	vector< SegmentTree<Traits> > m_data;
	size_t m_width, m_height;

	void initialize(){
		vector<value_type> work(m_width);
		for(int i = static_cast<int>(m_height) - 2; i >= 0; --i){
			for(size_t j = 0; j < m_width; ++j){
				work[j] =
					m_traits(m_data[i * 2 + 1][j], m_data[i * 2 + 2][j]);
			}
			m_data[i] = SegmentTree<Traits>(work.begin(), work.end());
		}
	}

	value_type query(
		int x0, int y0, int x1, int y1, int k, int l, int r) const
	{
		if(r <= y0 || y1 <= l){ return m_traits.default_value(); }
		if(y0 <= l && r <= y1){ return m_data[k].query(x0, x1); }
		const value_type vl = query(x0, y0, x1, y1, k * 2 + 1, l, (l + r) / 2);
		const value_type vr = query(x0, y0, x1, y1, k * 2 + 2, (l + r) / 2, r);
		return m_traits(vl, vr);
	}

public:
	/**
	 *  @brief コンストラクタ (既定値で初期化)
	 *
	 *  葉をすべて既定値で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(HW) \f$。
	 *
	 *  @param[in] height  行方向の葉の数
	 *  @param[in] width   列方向の葉の数
	 *  @param[in] traits  処理内容を示す関数オブジェクト
	 */
	explicit SegmentTree2D(
		size_t height = 0, size_t width = 0, const Traits &traits = Traits()) :
		m_traits(traits), m_height(1), m_width(width)
	{
		while(m_height < height){ m_height *= 2; }
		m_data.assign(m_height * 2 - 1, SegmentTree<Traits>(width, traits));
		initialize();
	}

	/**
	 *  @brief コンストラクタ (要素列による初期化)
	 *
	 *  葉をすべて [first, last) で初期化した状態のセグメント木を構築する。
	 *  計算量は \f$ \mathcal{O}(HW) \f$。
	 *
	 *  @param[in] first   要素列の先頭を指すイテレータ
	 *  @param[in] last    要素列の終端を指すイテレータ
	 *  @param[in] traits  処理内容を示す関数オブジェクト
	 */
	template <typename Iterator>
	SegmentTree2D(
		Iterator first, Iterator last, const Traits &traits = Traits()) :
		m_traits(traits), m_height(1), m_width(0)
	{
		const size_t h = distance(first, last);
		while(m_height < h){ m_height *= 2; }
		if(h > 0){ m_width = distance(first->begin(), first->end()); }
		m_data.resize(m_height * 2 - 1, SegmentTree<Traits>(m_width, traits));
		size_t row = m_height - 1;
		for(Iterator it = first; it != last; ++it, ++row){
			m_data[row] = SegmentTree<Traits>(it->begin(), it->end());
		}
		initialize();
	}

	/**
	 *  @brief 葉の更新
	 *
	 *  (i, j)番目の葉の値をvalで更新する。
	 *  計算量は \f$ \mathcal{O}(\log{H} \log{W}) \f$。
	 *
	 *  @param[in] i    更新したい葉の行番号
	 *  @param[in] j    更新したい葉の列番号
	 *  @param[in] val  更新後の値
	 */
	void update(size_t i, size_t j, const value_type &val){
		i += m_height - 1;
		m_data[i].update(j, val);
		while(i > 0){
			i = (i - 1) / 2;
			m_data[i].update(j, m_traits(
				m_data[i * 2 + 1][j], m_data[i * 2 + 2][j]));
		}
	}

	/**
	 *  @brief 区間についての問い合わせ
	 *
	 *  行番号が [y0, y1) に、列番号が [x0, x1) に含まれる要素すべてを結合した
	 *  結果を求める。
	 *  計算量は \f$ \mathcal{O}(\log{H} \log{W}) \f$。
	 *
	 *  @param[in] x0  区間左上の列番号
	 *  @param[in] y0  区間左上の行番号
	 *  @param[in] x1  区間右下の列番号
	 *  @param[in] y1  区間右下の行番号
	 *  @return    計算された結果
	 */
	value_type query(size_t x0, size_t y0, size_t x1, size_t y1) const {
		return query(x0, y0, x1, y1, 0, 0, m_height);
	}

};

/**
 *  @}
 */

}
}

