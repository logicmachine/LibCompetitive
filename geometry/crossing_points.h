/**
 *  @file geometry/crossing_points.h
 */
#pragma once

#ifdef DOXYGEN_DOCUMENTATION
#include "point.h"
#include "line.h"
#include "segment.h"
#include "circle.h"
#include "polygon.h"
#endif

namespace libcomp {
namespace geometry {

/**
 *  @defgroup crossing_points Crossing points
 *  @ingroup  geometry
 *  @{
 */

#if defined(LIBCOMP_GEOMETRY_LINE)
/**
 *  @brief 直線と直線の交点
 *  @param[in] a  片方の直線
 *  @param[in] b  片方の直線
 *  @return    aとbの交点の座標
 *  @note aとbが等しい場合は代表として2点を返す
 */
inline vector<Point> crossing_points(const Line &a, const Line &b){
	vector<Point> ret;
	if(tolerant_eq(a, b)){
		ret.push_back(a.a);
		ret.push_back(a.b);
	}else{
		const double x = cross(a.b - a.a, b.b - b.a);
		const double y = cross(a.b - a.a, a.b - b.a);
		if(abs(x) >= EPS){ ret.push_back(b.a + y / x * (b.b - b.a)); }
	}
	return ret;
}
#endif

#if defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 円と円の交点
 *  @param[in] a  片方の円
 *  @param[in] b  片方の円
 *  @return    aとbの交点の座標
 *  @note aとbが等しい場合は代表として3点を返す
 */
inline vector<Point> crossing_points(const Circle &a, const Circle &b){
	vector<Point> ret;
	if(tolerant_eq(a, b)){
		ret.push_back(a.c + Point(a.r, 0.0));
		ret.push_back(a.c + Point(-a.r, 0.0));
		ret.push_back(a.c + Point(0.0, a.r));
	}else{
		const double l = abs(b.c - a.c);
		const double s = (l + a.r + b.r) / 2.0;
		const double S = sqrt(s * (s - l) * (s - a.r) * (s - b.r));
		const double d = (S * 2.0) / l;
		const double t = sqrt(a.r * a.r - d * d);
		const Point v = t * unit(b.c - a.c);
		const Point w = d * unit(ortho(v));
		const Point x = a.c + v + w, y = a.c + v - w;
		ret.push_back(x);
		if(!tolerant_eq(x, y)){ ret.push_back(y); }
	}
	return ret;
}
#endif

/**
 *  @}
 */

}
}

