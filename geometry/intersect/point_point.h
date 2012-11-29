#pragma once
#include "../essential/point.h"

bool intersect(const Point &a, const Point &b){
	return tolerant_eq(a, b);
}

