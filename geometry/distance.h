/**
 *  @file geometry/distance.h
 */
#pragma once
#include <algorithm>

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
 *  @defgroup distance Distance
 *  @ingroup  geometry
 *  @{
 */

#if defined(LIBCOMP_GEOMETRY_POINT)
/**
 *  @brief 点と点の距離
 *  @param[in] a  片方の点
 *  @param[in] b  片方の点
 *  @return    aとbの距離
 */
inline double distance(const Point &a, const Point &b){
	return abs(a - b);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_LINE)
/**
 *  @brief 点と直線の距離
 *  @param[in] a  片方の点
 *  @param[in] b  片方の直線
 *  @return    aとbの距離
 */
inline double distance(const Point &a, const Line &b){
	return abs(a - projection(b, a));
}

/**
 *  @brief 直線と点の距離
 *  @param[in] a  片方の直線
 *  @param[in] b  片方の点
 *  @return    aとbの距離
 */
inline double distance(const Line &a, const Point &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 点と線分の距離
 *  @param[in] a  片方の点
 *  @param[in] b  片方の線分
 *  @return    aとbの距離
 */
inline double distance(const Point &a, const Segment &b){
	const Point r = projection(Line(b.a, b.b), a);
	if(intersect(b, r)){ return abs(r - a); }
	return min(abs(b.a - a), abs(b.b - a));
}

/**
 *  @brief 線分と点の距離
 *  @param[in] a  片方の線分
 *  @param[in] b  片方の点
 *  @return    aとbの距離
 */
inline double distance(const Segment &a, const Point &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 点と円の距離
 *  @param[in] a  片方の点
 *  @param[in] b  片方の円
 *  @return    aとbの距離
 */
inline double distance(const Point &a, const Circle &b){
	return abs(abs(a - b.c) - b.r);
}

/**
 *  @brief 円と点の距離
 *  @param[in] a  片方の円
 *  @param[in] b  片方の点
 *  @return    aとbの距離
 */
inline double distance(const Circle &a, const Point &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE)
/**
 *  @brief 直線と直線の距離
 *  @param[in] a  片方の直線
 *  @param[in] b  片方の直線
 *  @return    aとbの距離
 */
inline double distance(const Line &a, const Line &b){
	return intersect(a, b) ? 0.0 : distance(a, b.a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE) && defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 直線と線分の距離
 *  @param[in] a  片方の直線
 *  @param[in] b  片方の線分
 *  @return    aとbの距離
 */
inline double distance(const Line &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	return min(distance(a, b.a), distance(a, b.b));
}

/**
 *  @brief 線分と直線の距離
 *  @param[in] a  片方の線分
 *  @param[in] b  片方の直線
 *  @return    aとbの距離
 */
inline double distance(const Segment &a, const Line &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE) && defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 直線と円の距離
 *  @param[in] a  片方の直線
 *  @param[in] b  片方の円
 *  @return    aとbの距離
 */
inline double distance(const Line &a, const Circle &b){
	return max(0.0, distance(b.c, a) - b.r);
}

/**
 *  @brief 円と直線の距離
 *  @param[in] a  片方の円
 *  @param[in] b  片方の直線
 *  @return    aとbの距離
 */
inline double distance(const Circle &a, const Line &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 線分と線分の距離
 *  @param[in] a  片方の線分
 *  @param[in] b  片方の線分
 *  @return    aとbの距離
 */
inline double distance(const Segment &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	const double x = min(distance(a.a, b), distance(a.b, b));
	const double y = min(distance(b.a, a), distance(b.b, a));
	return min(x, y);
}
#endif

#if defined(LIBCOMP_GEOMETRY_SEGMENT) && defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 線分と円の距離
 *  @param[in] a  片方の線分
 *  @param[in] b  片方の円
 *  @return    aとbの距離
 */
inline double distance(const Segment &a, const Circle &b){
	if(intersect(a, b)){ return 0.0; }
	const double d = abs(distance(a, b.c) - b.r);
	return min(min(distance(a.a, b), distance(a.b, b)), d);
}

/**
 *  @brief 円と線分の距離
 *  @param[in] a  片方の円
 *  @param[in] b  片方の線分
 *  @return    aとbの距離
 */
inline double distance(const Circle &a, const Segment &b){
	return distance(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 円と円の距離
 *  @param[in] a  片方の円
 *  @param[in] b  片方の円
 *  @return    aとbの距離
 */
inline double distance(const Circle &a, const Circle &b){
	const double d = distance(a.c, b.c);
	const double ra = max(a.r, b.r), rb = min(a.r, b.r);
	if(d >= ra + rb){ return d - ra - rb; }
	return ra - d - rb;
}
#endif

/**
 *  @}
 */

}
}

