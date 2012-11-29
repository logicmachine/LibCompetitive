#pragma once
#include "../essential/circle.h"

double dist(const Point &a, const Circle &b){
	return abs(abs(a - b.c) - b.r);
}
double dist(const Circle &a, const Point &b){ return dist(b, a); }

