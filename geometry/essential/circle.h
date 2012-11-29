#pragma once
#include "point.h"

struct Circle {
	Point c;
	double r;
	explicit Circle(const Point &c = Point(), double r = 0.0) :
		c(c), r(r)
	{ }

	static Circle invalid(){
		double qnan = numeric_limits<double>::quiet_NaN();
		return Circle(Point::invalid(), qnan);
	}
	bool is_valid() const { return c.is_valid() && !isnan(r); }

	bool operator<(const Circle &i) const {
		return (r == i.r) ? (c < i.c) : (r < i.r);
	}
};

bool tolerant_eq(const Circle &a, const Circle &b){
	return tolerant_eq(a.c, b.c) && tolerant_eq(a.r, b.r);
}

