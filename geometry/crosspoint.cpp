#include "geometry.cpp"
#include "intersect.cpp"
#include "distance.cpp"

Point crosspoint(const Line &a, const Line &b){
	double x = cross(a.b - a.a, b.b - b.a);
	double y = cross(a.b - a.a, a.b - b.a);
	if(abs(x) < EPS && abs(y) < EPS){
		return b.a;
	}else if(abs(x) < EPS){
		return Point::invalid();
	}else{
		return b.a + y / x * (b.b - b.a);
	}
}

