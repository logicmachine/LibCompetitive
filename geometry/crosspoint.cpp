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

vector<Point> crosspoint(const Circle &a, const Circle &b){
	if(!intersect(a, b)){ return vector<Point>(); }
	double l = abs(b.c - a.c), s = (l + a.r + b.r) / 2.0;
	double S = sqrt(s * (s - l) * (s - a.r) * (s - b.r));
	double d = (S * 2) / l, t = sqrt(a.r * a.r - d * d);
	Point v = t * unit(b.c - a.c);
	Point w = d * unit(ortho(v));
	Point x = a.c + v + w, y = a.c + v - w;
	if(tolerant_eq(x, y)){ return vector<Point>(1, x); }
	vector<Point> ans(2); ans[0] = x; ans[1] = y;
	return ans;
}

