#pragma once
#include "../essential/segment.h"

bool intersect(const Segment &a, const Segment &b){
	if(ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) > 0){ return false; }
	if(ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) > 0){ return false; }
	return true;
}

