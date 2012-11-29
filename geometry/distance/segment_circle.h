#pragma once
#include <algorithm>
#include "../intersect/segment_circle.h"

double dist(const Segment &a, const Circle &b){
	if(intersect(a, b)){ return 0.0; }
	double d = abs(dist(a, b.c) - b.r);
	return min(min(dist(a.a, b), dist(a.b, b)), d);
}
double dist(const Circle &a, const Segment &b){ return dist(b, a); }

