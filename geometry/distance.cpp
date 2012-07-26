#pragma once
#include "geometry.cpp"
#include "intersect.cpp"

double dist(const Point &a, const Point &b){
	return abs(a - b);
}
double dist(const Point &a, const Line &b){
	return abs(a - projection(b, a));
}
double dist(const Point &a, const Segment &b){
	const Point r = projection(Line(b.a, b.b), a);
	if(intersect(b, r)){ return abs(r - a); }
	return min(abs(b.a - a), abs(b.b - a));
}
double dist(const Point &a, const Circle &b){
	return abs(abs(a - b.c) - b.r);
}

double dist(const Line &a, const Point &b){ return dist(b, a); }
double dist(const Line &a, const Line &b){
	return intersect(a, b) ? 0.0 : dist(a, b.a);
}
double dist(const Line &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	return min(dist(a, b.a), dist(a, b.b));
}
double dist(const Line &a, const Circle &b){
	return max(0.0, dist(a, b.c) - b.r);
}

double dist(const Segment &a, const Point &b){ return dist(b, a); }
double dist(const Segment &a, const Line &b){ return dist(b, a); }
double dist(const Segment &a, const Segment &b){
	if(intersect(a, b)){ return 0.0; }
	double x = min(dist(a, b.a), dist(a, b.b));
	double y = min(dist(b, a.a), dist(b, a.b));
	return min(x, y);
}
double dist(const Segment &a, const Circle &b){
	if(intersect(a, b)){ return 0.0; }
	double d = abs(dist(a, b.c) - b.r);
	return min(min(dist(a.a, b), dist(a.b, b)), d);
}

double dist(const Circle &a, const Point &b){ return dist(b, a); }
double dist(const Circle &a, const Line &b){ return dist(b, a); }
double dist(const Circle &a, const Segment &b){ return dist(b, a); }
double dist(const Circle &a, const Circle &b){
	if(intersect(a, b)){ return 0.0; }
	return dist(a.c, b.c) - a.r - b.r;
}

