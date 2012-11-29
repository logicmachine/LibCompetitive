#pragma once
#include "../essential/segment.h"

bool intersect(const Point &a, const Segment &b){
	return abs(b.a - a) + abs(b.b - a) - abs(b.b - b.a) < EPS;
}
bool intersect(const Segment &a, const Point &b){ return intersect(b, a); }

