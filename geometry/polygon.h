/**
 *  @file geometry/polygon.h
 */
#pragma once
#include <vector>
#include "point.h"

#define LIBCOMP_GEOMETRY_POLYGON

namespace libcomp {
namespace geometry {

/**
 *  @defgroup polygon Polygon
 *  @ingroup  geometry
 *  @{
 */

/**
 *  @brief 多角形
 */
class Polygon {

private:
	vector<Point> m_points;

public:
	/**
	 *  @brief コンストラクタ
	 */
	Polygon() : m_points() { }
	/**
	 *  @brief コンストラクタ
	 *
	 *  頂点数sの多角形を生成する。
	 *
	 *  @param[in] s  生成する多角形の頂点数
	 *  @param[in] p  生成する多角形の各頂点の座標
	 */
	explicit Polygon(size_t s, const Point &p = Point()) :
		m_points(s, p)
	{ }
	/**
	 *  @brief コンストラクタ
	 *
	 *  頂点列から多角形を生成する
	 *
	 *  @tparam    Iterator  イテレータの型
	 *  @param[in] begin     頂点列の先頭を指すイテレータ
	 *  @param[in] end       頂点列の終端を指すイテレータ
	 */
	template <typename Iterator>
	explicit Polygon(Iterator begin, Iterator end) :
		m_points(begin, end)
	{ }

	/**
	 *  @brief 不正な多角形の取得
	 *  @return 不正な多角形を示すデータ
	 */
	static Polygon invalid(){ return Polygon(); }
	/**
	 *  @brief 不正な多角形ではないかの確認
	 *  @retval true   *thisが有効な多角形となっている場合
	 *  @retval false  *thisが有効な多角形ではない場合
	 */
	bool is_valid() const { return m_points.size() > 0; }

	/**
	 *  @brief 頂点情報の取得
	 *  @param[in] i  取得したい頂点のインデックス
	 *  @return    i番目の頂点への参照
	 */
	const Point &operator[](int i) const { return m_points[i]; }
	/**
	 *  @brief 頂点情報の取得
	 *  @param[in] i  取得したい頂点のインデックス
	 *  @return    i番目の頂点への参照
	 */
	Point &operator[](int i){ return m_points[i]; }

	/**
	 *  @brief 多角形の頂点数の取得
	 *  @return 多角形に含まれる頂点の数
	 */
	size_t size() const { return m_points.size(); }

	/**
	 *  @brief 多角形の比較 (<, 厳密評価)
	 *
	 *  コンテナで使用するためのもので数学的な意味はないことに注意。
	 *  (頂点の順番がローテートしている場合など)
	 *
	 *  @param[in] p      比較する値
	 *  @retval    true   *thisがpより辞書順で小さい場合
	 *  @retval    false  *thisがpより辞書順で大きい場合
	 */
	bool operator<(const Polygon &p) const {
		return m_points < p.m_points;
	}
};

/**
 *  @brief 多角形の比較 (==, 誤差許容)
 *  @todo 順番が異なる場合に対応する
 *  @param[in] a      比較する値
 *  @param[in] b      比較する値
 *  @retval    true   aとbが同じ多角形を表している場合
 *  @retval    false  aとbが同じ多角形を表していない場合
 */
inline bool tolerant_eq(const Polygon &a, const Polygon &b){
	if(a.size() != b.size()){ return false; }
	const size_t size = a.size();
	for(size_t i = 0; i < size; ++i){
		if(!tolerant_eq(a[i], b[i])){ return false; }
	}
	return true;
}

/**
 *  @brief 多角形の面積
 *
 *  多角形pの面積を求める。
 *  計算量は \f$ \mathcal{O}(|p|) \f$。
 *
 *  @param[in] p  多角形
 *  @return    多角形pの面積
 */
inline double area(const Polygon &p){
	double s = 0.0;
	for(size_t i = 0; i < p.size(); ++i){
		s += cross(p[i], p[(i + 1) % p.size()]);
	}
	return s * 0.5;
}

/**
 *  @}
 */

}
}

