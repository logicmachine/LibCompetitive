/**
 *  @file geometry/line.h
 */
#pragma once
#include "point.h"

#define LIBCOMP_GEOMETRY_LINE

namespace libcomp {
namespace geometry {

/**
 *  @defgroup line Line
 *  @ingroup  geometry
 *  @{
 */

/**
 *  @brief 直線
 */
struct Line {
	/// 直線状の点
	Point a;
	/// 直線状の点
	Point b;

	/**
	 *  @brief コンストラクタ
	 *  @param[in] a  直線状の点
	 *  @param[in] b  直線状の点 (a != b)
	 */
	explicit Line(const Point &a = Point(), const Point &b = Point()) :
		a(a), b(b)
	{ }

	/**
	 *  @brief 不正な値を示す直線の取得
	 *  @return 不正な直線
	 */
	static Line invalid(){
		Point inv = Point::invalid();
		return Line(inv, inv);
	}
	/**
	 *  @brief 直線データが不正なものではないかの確認
	 *  @retval true   *thisが有効な直線データであった場合
	 *  @retval false  *thisが無効な直線データであった場合
	 */
	bool is_valid() const { return a.is_valid() && b.is_valid(); }

	/**
	 *  @brief 直線の比較 (<, 厳密評価)
	 *
	 *  コンテナで使用するためのもので数学的な意味はないことに注意。
	 *  (同一直線ではあるものの選んでいる点が異なる場合など)
	 *
	 *  @param[in] l      比較する値
	 *  @retval    true   *thisがlより辞書順で小さい場合
	 *  @retval    false  *thisがlより辞書順で小さくない場合
	 */
	bool operator<(const Line &l) const {
		return (a == l.a) ? (b < l.b) : (a < l.a);
	}
};

/**
 *  @brief 直線の比較 (==, 誤差許容, 無向)
 *  @param[in] a      比較する値
 *  @param[in] b      比較する値
 *  @retval    true   aとbが同じ直線を表している場合
 *  @retval    false  aとbが同じ直線を表していない場合
 */
inline bool tolerant_eq(const Line &a, const Line &b){
	return abs(cross(a.b - a.a, b.a - a.a)) < EPS;
}

/**
 *  @brief 直線の比較 (==, 誤差許容, 有向)
 *  @param[in] a      比較する値
 *  @param[in] b      比較する値
 *  @retval    true   aとbが同じ直線を表している場合
 *  @retval    false  aとbが同じ直線を表していない場合
 */
inline bool directed_tolerant_eq(const Line &a, const Line &b){
	return tolerant_eq(a, b) && tolerant_eq(unit(a.a - a.b), unit(b.a - b.b));
}

/**
 *  @brief 点の直線への射影
 *  @param[in] l  射影先となる直線
 *  @param[in] p  射影する点
 *  @return    直線l上で最も点pに近くなる座標
 */
inline Point projection(const Line &l, const Point &p){
	double t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
	return l.a + t * (l.b - l.a);
}

/**
 *  @brief 直線を挟んで対称な位置にある点の計算
 *  @param[in] l  中心とする直線
 *  @param[in] p  変換する点
 *  @return    直線l上を挟んで点pと対称な点
 */
inline Point reflection(const Line &l, const Point &p){
	return p + 2.0 * (projection(l, p) - p);
}

/**
 *  @}
 */

}
}

