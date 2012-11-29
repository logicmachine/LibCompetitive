#pragma once
#include "../essential/circle.h"

bool intersect(const Point &a, const Circle &b){
	return tolerant_eq(abs(a - b.c), b.r);
}
bool intersect(const Circle &a, const Point &b){ return intersect(b, a); }

