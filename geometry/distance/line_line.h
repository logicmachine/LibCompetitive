#pragma once
#include "../intersect/line_line.h"

double dist(const Line &a, const Line &b){
	return intersect(a, b) ? 0.0 : dist(a, b.a);
}

