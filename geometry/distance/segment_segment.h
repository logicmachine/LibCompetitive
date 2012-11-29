#pragma once
#include <algorithm>
#include "../intersect/segment_segment.h"
#include "point_segment.h"

double dist(const Segment &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	double x = min(dist(a, b.a), dist(a, b.b));
	double y = min(dist(b, a.a), dist(b, a.b));
	return min(x, y);
}

