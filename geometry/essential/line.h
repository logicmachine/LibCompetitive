#pragma once
#include "point.h"

struct Line {
	Point a, b;
	explicit Line(const Point &a = Point(), const Point &b = Point()) :
		a(a), b(b)
	{ }

	static Line invalid(){
		Point inv = Point::invalid();
		return Line(inv, inv);
	}
	bool is_valid() const { return a.is_valid() && b.is_valid(); }

	bool operator<(const Line &l) const {
		return (a == l.a) ? (b < l.b) : (a < l.a);
	}
};

bool tolerant_eq(const Line &a, const Line &b){
	return abs(cross(a.b - a.a, b.a - a.a)) < EPS;
}
Point projection(const Line &l, const Point &p){
	double t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
	return l.a + t * (l.b - l.a);
}
Point reflection(const Line &l, const Point &p){
	return p + 2.0 * (projection(l, p) - p);
}

