/**
 *  @file geometry/intersect.h
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
 *  @defgroup intersect Intersect
 *  @ingroup  geometry
 *  @{
 */

#if defined(LIBCOMP_GEOMETRY_POINT)
/**
 *  @brief 点と点の交差判定
 *  @param[in] a      判定する点
 *  @param[in] b      判定する点
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Point &a, const Point &b){
	return tolerant_eq(a, b);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_LINE)
/**
 *  @brief 点と直線の交差判定
 *  @param[in] a      判定する点
 *  @param[in] b      判定する直線
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Point &a, const Line &b){
	return abs(cross(b.b - a, b.a - a)) < EPS;
}

/**
 *  @brief 直線と点の交差判定
 *  @param[in] a      判定する直線
 *  @param[in] b      判定する点
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Line &a, const Point &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 点と線分の交差判定
 *  @param[in] a      判定する点
 *  @param[in] b      判定する線分
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Point &a, const Segment &b){
	return abs(b.a - a) + abs(b.b - a) - abs(b.b - b.a) < EPS;
}

/**
 *  @brief 線分と点の交差判定
 *  @param[in] a      判定する線分
 *  @param[in] b      判定する点
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Segment &a, const Point &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_POINT) && defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 点と円の交差判定
 *  @param[in] a      判定する点
 *  @param[in] b      判定する円
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Point &a, const Circle &b){
	return tolerant_eq(abs(a - b.c), b.r);
}

/**
 *  @brief 円と点の交差判定
 *  @param[in] a      判定する円
 *  @param[in] b      判定する点
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Circle &a, const Point &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE)
/**
 *  @brief 直線と直線の交差判定
 *  @param[in] a      判定する直線
 *  @param[in] b      判定する直線
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Line &a, const Line &b){
	if(abs(cross(a.b - a.a, b.b - b.a)) > EPS){ return true; }
	return tolerant_eq(a, b);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE) && defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 直線と線分の交差判定
 *  @param[in] a      判定する直線
 *  @param[in] b      判定する線分
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Line &a, const Segment &b){
	return cross(a.b - a.a, b.a - a.a) * cross(a.b - a.a, b.b - a.a) < EPS;
}

/**
 *  @brief 線分と直線の交差判定
 *  @param[in] a      判定する線分
 *  @param[in] b      判定する直線
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Segment &a, const Line &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_LINE) && defined(LIBCOMP_GEOMETRY_CIRCLE)
inline double distance(const Point &, const Line &);
/**
 *  @brief 直線と円の交差判定
 *  @param[in] a      判定する直線
 *  @param[in] b      判定する円
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Line &a, const Circle &b){
	return distance(b.c, a) <= b.r;
}
/**
 *  @brief 円と直線の交差判定
 *  @param[in] a      判定する円
 *  @param[in] b      判定する直線
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Circle &a, const Line &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_SEGMENT)
/**
 *  @brief 線分と線分の交差判定
 *  @param[in] a      判定する線分
 *  @param[in] b      判定する線分
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Segment &a, const Segment &b){
	if(ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) > 0.0){ return false; }
	if(ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) > 0.0){ return false; }
	return true;
}
#endif

#if defined(LIBCOMP_GEOMETRY_SEGMENT) && defined(LIBCOMP_GEOMETRY_CIRCLE)
inline double distance(const Point &, const Segment &);
/**
 *  @brief 線分と円の交差判定
 *  @param[in] a      判定する線分
 *  @param[in] b      判定する円
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Segment &a, const Circle &b){
	const double d = distance(b.c, a);
	if(d > b.r){ return false; }
	return abs(a.a - b.c) >= b.r || abs(a.b - b.c) >= b.r;
}

/**
 *  @brief 円と線分の交差判定
 *  @param[in] a      判定する円
 *  @param[in] b      判定する線分
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Circle &a, const Segment &b){
	return intersect(b, a);
}
#endif

#if defined(LIBCOMP_GEOMETRY_CIRCLE)
/**
 *  @brief 円と円の交差判定
 *  @param[in] a      判定する円
 *  @param[in] b      判定する円
 *  @retval    true   aとbが交差している
 *  @retval    false  aとbが交差していない
 */
inline bool intersect(const Circle &a, const Circle &b){
	const double d = abs(a.c - b.c);
	return (a.r - d < b.r * EPS) && (a.r + d > b.r - EPS);
}
#endif

/**
 *  @}
 */

}
}

