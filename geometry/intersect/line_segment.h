#pragma once
#include "../essential/line.h"
#include "../essential/segment.h"

bool intersect(const Line &a, const Segment &b){
	return cross(a.b - a.a, b.a - a.a) * cross(a.b - a.a, b.b - a.a) < EPS;
}
bool intersect(const Segment &a, const Line &b){ return intersect(b, a); }

