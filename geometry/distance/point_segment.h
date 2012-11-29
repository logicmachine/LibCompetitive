#pragma once
#include <algorithm>
#include "../essential/line.h"
#include "../intersect/point_segment.h"

double dist(const Point &a, const Segment &b){
	const Point r = projection(Line(b.a, b.b), a);
	if(intersect(b, r)){ return abs(r - a); }
	return min(abs(b.a - a), abs(b.b - a));
}
double dist(const Segment &a, const Point &b){ return dist(b, a); }

