#pragma once
#include "../essential/segment.h"
#include "../essential/circle.h"
#include "../distance/point_segment.h"

bool intersect(const Segment &a, const Circle &b){
	double nearest = dist(b.c, a);
	if(nearest > b.r){ return false; }
	return abs(a.a - b.c) >= b.r || abs(a.b - b.c) >= b.r;
}
bool intersect(const Circle &a, const Segment &b){ return intersect(b, a); }

