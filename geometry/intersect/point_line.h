#pragma once
#include "../essential/line.h"

bool intersect(const Point &a, const Line &b){
	return abs(cross(b.b - a, b.a - a)) < EPS;
}
bool intersect(const Line &a, const Point &b){ return intersect(b, a); }

