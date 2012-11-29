#pragma once
#include "../essential/line.h"

bool intersect(const Line &a, const Line &b){
	if(abs(cross(a.b - a.a, b.b - b.a)) > EPS){ return true; }
	return tolerant_eq(a, b);
}

