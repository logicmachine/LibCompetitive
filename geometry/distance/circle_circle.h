#pragma once
#include "../intersect/circle_circle.h"
#include "point_point.h"

double dist(const Circle &a, const Circle &b){
	if(intersect(a, b)){ return 0.0; }
	return dist(a.c, b.c) - a.r - b.r;
}

