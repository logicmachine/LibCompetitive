#pragma once
#include <algorithm>
#include "../interserct/line_segment.h"

double dist(const Line &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	return min(dist(a, b.a), dist(a, b.b));
}
double dist(const Segment &a, const Line &b){ return dist(b, a); }

