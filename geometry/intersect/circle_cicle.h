#pragma once
#include "../essential/circle.h"

bool intersect(const Circle &a, const Circle &b){
	double d = abs(a.c - b.c);
	return (a.r - d < b.r + EPS) && (a.r + d > b.r - EPS);
}

