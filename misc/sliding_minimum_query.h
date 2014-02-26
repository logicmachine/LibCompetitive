/**
 *  @file misc/sliding_minimum_query.h
 */
#pragma once
#include <deque>
#include <functional>
#include "common/header.h"

namespace libcomp {
namespace misc {

/**
 *  @defgroup sliding_minimum_query Sliding minimum query
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief  スライド最小値クエリ処理
 *  @tparam T  値の型
 *  @tparam F  比較関数の型
 */
template < typename T, typename F = std::less<T> >
class SlidingMinimumQuery {

private:
	deque<T> m_deque;
	deque<int> m_indices;
	F m_comparator;
	int m_push_count;
	int m_pop_count;

public:
	/**
	 *  @brief デフォルトコンストラクタ
	 *
	 *  要素が含まれない状態にクエリ処理器を初期化する。
	 *
	 *  @param[in] comparator  比較関数
	 */
	explicit SlidingMinimumQuery(const F &comparator = F()) :
		m_deque(), m_indices(), m_comparator(comparator),
		m_push_count(0), m_pop_count(0)
	{ }

	/**
	 *  @brief 最小値クエリ
	 *
	 *  クエリ処理器が持っている区間の最小値を取得する。
	 *  計算量は \f$ \mathcal{O}(1) \f$。
	 *
	 *  @return 区間に含まれている中で最小の値
	 */
	const T &query() const {
		return m_deque.front();
	}

	/**
	 *  @brief 区間の拡大
	 *
	 *  スライドしている区間の末尾に要素を追加する。
	 *  計算量は \f$ \mathcal{O}(1) \f$ (amortized)。
	 *
	 *  @param[in] x  区間に新たに追加される値
	 */
	void push(const T &x){
		while(!m_deque.empty() && m_comparator(x, m_deque.back())){
			m_deque.pop_back();
			m_indices.pop_back();
		}
		m_deque.push_back(x);
		m_indices.push_back(m_push_count++);
	}

	/**
	 *  @brief 区間の縮小
	 *
	 *  スライドしている区間の先頭要素を取り除く。
	 *  計算量は \f$ \mathcal{O}(1) \f$。
	 */
	void pop(){
		if(m_indices.front() == m_pop_count){
			m_deque.pop_front();
			m_indices.pop_front();
		}
		++m_pop_count;
	}

};

/**
 *  @}
 */

}
}

