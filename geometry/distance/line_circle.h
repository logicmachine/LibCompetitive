#pragma once
#include <algorithm>
#include "point_line.h"

double dist(const Line &a, const Circle &b){
	return max(0.0, dist(b.c, a) - b.r);
}
double dist(const Circle &a, const Line &b){ return dist(b, a); }

