#pragma once
#include "../essential/line.h"

double dist(const Point &a, const Line &b){
	return abs(a - projection(b, a));
}
double dist(const Line &a, const Point &b){ return dist(b, a); }

