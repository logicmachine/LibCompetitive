#pragma once
#include "../essential/line.h"
#include "../essential/circle.h"
#include "../distance/point_line.h"

bool intersect(const Line &a, const Circle &b){
	return dist(b.c, a) <= b.r;
}
bool intersect(const Circle &a, const Line &b){ return intersect(b, a); }

