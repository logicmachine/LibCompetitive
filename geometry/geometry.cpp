#pragma once
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

bool tolerant_eq(double a, double b){ return abs(a - b) < EPS; }

struct Point {
	double x, y;
	explicit Point(const double &x = 0.0, const double &y = 0.0) :
		x(x), y(y)
	{ }

	static Point invalid(){
		double qnan = numeric_limits<double>::quiet_NaN();
		return Point(qnan, qnan);
	}
	bool is_valid() const { return !(isnan(x) || isnan(y)); }

	Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
	Point &operator+=(const Point &p){ return *this = *this + p; }
	Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
	Point &operator-=(const Point &p){ return *this = *this - p; }
	Point operator*(double s) const { return Point(x * s, y * s); }
	Point &operator*=(double s){ return *this = *this * s; }
	Point operator/(double s) const { return Point(x / s, y / s); }
	Point &operator/=(double s){ return *this = *this / s; }

	bool operator==(const Point &p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point &p) const { return x != p.x || y != p.y; }
	bool operator<(const Point &p) const {
		return (x == p.x) ? (y < p.y) : (x < p.x);
	}
};

Point operator*(double s, const Point &p){ return p * s; }

bool tolerant_eq(const Point &a, const Point &b){
	return tolerant_eq(a.x, b.x) && tolerant_eq(a.y, b.y);
}
double abs(const Point &p){ return sqrt(p.x * p.x + p.y * p.y); }
Point unit(const Point &p){ return p / abs(p); }
Point ortho(const Point &p){ return Point(-p.y, p.x); }
double cross(const Point &a, const Point &b){ return a.x * b.y - a.y * b.x; }
double dot(const Point &a, const Point &b){ return a.x * b.x + a.y * b.y; }
int ccw(const Point &a, const Point &b, const Point &c){
	Point d = b - a, e = c - a;
	if(cross(d, e) > 0.0){ return 1; }
	if(cross(d, e) < 0.0){ return -1; }
	if(dot(d, e) < 0.0){ return 2; }
	if(abs(d) < abs(e)){ return -2; }
	return 0;
}

struct Line {
	Point a, b;
	explicit Line(const Point &a = Point(), const Point &b = Point()) :
		a(a), b(b)
	{ }

	static Line invalid(){
		Point inv = Point::invalid();
		return Line(inv, inv);
	}
	bool is_valid() const { return a.is_valid() && b.is_valid(); }

	bool operator<(const Line &l) const {
		return (a == l.a) ? (b < l.b) : (a < l.a);
	}
};

bool tolerant_eq(const Line &a, const Line &b){
	return abs(cross(a.b - a.a, b.a - a.a)) < EPS;
}
Point projection(const Line &l, const Point &p){
	double t = dot(p - l.a, l.a - l.b) / abs(l.a - l.b);
	return l.a + t * (l.a - l.b);
}
Point reflection(const Line &l, const Point &p){
	return p + 2.0 * (projection(l, p) - p);
}

struct Segment {
	Point a, b;
	explicit Segment(const Point &a = Point(), const Point &b = Point()) :
		a(a), b(b)
	{ }

	static Line invalid(){
		Point inv = Point::invalid();
		return Line(inv, inv);
	}
	bool is_valid() const { return a.is_valid() && b.is_valid(); }

	bool operator<(const Segment &s) const {
		return (a == s.a) ? (b < s.b) : (a < s.a);
	}
};

bool tolerant_eq(const Segment &a, const Segment &b){
	if(tolerant_eq(a.a, b.a) && tolerant_eq(a.b, b.b)){ return true; }
	if(tolerant_eq(a.a, b.b) && tolerant_eq(a.b, b.a)){ return true; }
	return false;
}

struct Circle {
	Point c;
	double r;
	explicit Circle(const Point &c = Point(), double r = 0.0) :
		c(c), r(r)
	{ }

	static Circle invalid(){
		double qnan = numeric_limits<double>::quiet_NaN();
		return Circle(Point::invalid(), qnan);
	}
	bool is_valid() const { return c.is_valid() && !isnan(r); }

	bool operator<(const Circle &i) const {
		return (r == i.r) ? (c < i.c) : (r < i.r);
	}
};

bool tolerant_eq(const Circle &a, const Circle &b){
	return tolerant_eq(a.c, b.c) && tolerant_eq(a.r, b.r);
}

struct Polygon : public vector<Point> {
	static Polygon invalid(){ return Polygon(); }
	bool is_valid() const { return size() > 0; }
};

