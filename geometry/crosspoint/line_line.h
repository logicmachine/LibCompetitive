/**
 *  @file geometry/crosspoint/line_line.h
 */
#pragma once
#include "../essential/line.h"

namespace libcomp {
namespace geometry {

/**
 *  @defgroup crosspoint_line_lien Crossing point (line, line)
 *  @ingroup  geometry
 *  @{
 */

/**
 *  @brief 2直線の交点
 *  @param[in] a  直線1
 *  @param[in] b  直線2
 *  @return    直線a, bの交点。a, bが平行な場合はPoint::invalid()。
 */
Point crosspoint(const Line &a, const Line &b){
	const Point va = a.b - a.a, vb = b.b - b.a;
	const double c = cross(va, vb);
	const double d = cross(va, a.b - b.a);
	if(::std::abs(c) < EPS){ return Point::invalid(); }
	return b.a + d / c * vb;
}

/**
 *  @}
 */

}
}

