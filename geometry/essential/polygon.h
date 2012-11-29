#pragma once
#include <vector>
#include "point.h"

struct Polygon : public vector<Point> {
	Polygon() : vector<Point>() { }
	explicit Polygon(size_t s, const Point &p = Point()) :
		vector<Point>(s, p)
	{ }

	static Polygon invalid(){ return Polygon(); }
	bool is_valid() const { return size() > 0; }
};

