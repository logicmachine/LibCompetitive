#pragma once
#include "point.h"

struct Segment {
	Point a, b;
	explicit Segment(const Point &a = Point(), const Point &b = Point()) :
		a(a), b(b)
	{ }

	static Segment invalid(){
		Point inv = Point::invalid();
		return Segment(inv, inv);
	}
	bool is_valid() const { return a.is_valid() && b.is_valid(); }

	bool operator<(const Segment &s) const {
		return (a == s.a) ? (b < s.b) : (a < s.a);
	}
};

bool tolerant_eq(const Segment &a, const Segment &b){
	if(tolerant_eq(a.a, b.a) && tolerant_eq(a.b, b.b)){ return true; }
	if(tolerant_eq(a.a, b.b) && tolerant_eq(a.b, b.a)){ return true; }
	return false;
}

