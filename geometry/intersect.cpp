#pragma once
#include "geometry.cpp"

bool intersect(const Point &a, const Point &b){
	return tolerant_eq(a, b);
}
bool intersect(const Point &a, const Line &b){
	return abs(cross(b.b - a, b.a - a)) < EPS;
}
bool intersect(const Point &a, const Segment &b){
	return abs(b.a - a) + abs(b.b - a) - abs(b.b - b.a) < EPS;
}
bool intersect(const Point &a, const Circle &b){
	return tolerant_eq(abs(a - b.c), b.r);
}

bool intersect(const Line &a, const Point &b){ return intersect(b, a); }
bool intersect(const Line &a, const Line &b){
	if(abs(cross(a.b - a.a, b.b - b.a)) > EPS){ return true; }
	return tolerant_eq(a, b);
}
bool intersect(const Line &a, const Segment &b){
	return cross(a.b - a.a, b.a - a.a) * cross(a.b - a.a, b.b - a.a) < EPS;
}
double dist(const Line &a, const Point &b);
bool intersect(const Line &a, const Circle &b){
	return dist(a, b.c) <= b.r;
}

bool intersect(const Segment &a, const Point &b){ return intersect(b, a); }
bool intersect(const Segment &a, const Line &b){ return intersect(b, a); }
bool intersect(const Segment &a, const Segment &b){
	if(ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) > 0.0){ return false; }
	if(ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) > 0.0){ return false; }
	return true;
}
double dist(const Segment &a, const Point &b);
bool intersect(const Segment &a, const Circle &b){
	double nearest = dist(a, b.c);
	if(nearest > b.r){ return false; }
	return abs(a.a - b.c) >= b.r || abs(a.b - b.c) >= b.r;
}

bool intersect(const Circle &a, const Point &b){ return intersect(b, a); }
bool intersect(const Circle &a, const Line &b){ return intersect(b, a); }
bool intersect(const Circle &a, const Segment &b){ return intersect(b, a); }
bool intersect(const Circle &a, const Circle &b){
	double d = abs(a.c - b.c);
	return (a.r - d < b.r + EPS) && (a.r + d > b.r - EPS);
}

