/**
 *  @file geometry/debug.h
 */
#pragma once
#include <iostream>

#ifdef LIBCOMP_GEOMETRY_POINT
/**
 *  @brief 点情報の出力
 *  @param[in, out] os  出力先ストリーム
 *  @param[in]      p   出力する値
 *  @return         出力先ストリーム
 */
ostream &operator<<(ostream &os, const libcomp::geometry::Point &p){
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}
#endif

#ifdef LIBCOMP_GEOMETRY_LINE
/**
 *  @brief 直線情報の出力
 *  @param[in, out] os  出力先ストリーム
 *  @param[in]      l   出力する値
 *  @return         出力先ストリーム
 */
ostream &operator<<(ostream &os, const libcomp::geometry::Line &l){
	os << "(" << l.a << ", " << l.b << ")";
	return os;
}
#endif

#ifdef LIBCOMP_GEOMETRY_SEGMENT
/**
 *  @brief 線分情報の出力
 *  @param[in, out] os  出力先ストリーム
 *  @param[in]      s   出力する値
 *  @return         出力先ストリーム
 */
ostream &operator<<(ostream &os, const libcomp::geometry::Segment &s){
	os << "(" << s.a << ", " << s.b << ")";
	return os;
}
#endif

#ifdef LIBCOMP_GEOMETRY_CIRCLE
/**
 *  @brief 円情報の出力
 *  @param[in, out] os  出力先ストリーム
 *  @param[in]      c   出力する値
 *  @return         出力先ストリーム
 */
ostream &operator<<(ostream &os, const libcomp::geometry::Circle &c){
	os << "(" << c.c << ", " << c.r << ")";
	return os;
}
#endif

