#pragma once
#include <limits>
#include "common.h"

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
double norm(const Point &p){ return p.x * p.x + p.y * p.y; }
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

