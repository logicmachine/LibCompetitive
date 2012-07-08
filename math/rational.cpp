#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;
typedef long long ll;

class Rational {

private:
	ll n, d;

	void reduce(){
		ll gcd = __gcd(llabs(n), llabs(d));
		n /= gcd; d /= gcd;
		if(d < 0){ n = -n; d = -d; }
	}

public:
	Rational(ll nume = 0, ll deno = 1) : n(nume), d(deno) { reduce(); }

	int nume() const { return n; }
	int deno() const { return d; }

	Rational operator+(const Rational &r) const {
		return Rational(n * r.d + r.n * d, d * r.d);
	}
	Rational &operator+=(const Rational &r){ return *this = *this + r; }

	Rational operator-(const Rational &r) const {
		return Rational(n * r.d - r.n * d, d * r.d);
	}
	Rational &operator-=(const Rational &r){ return *this = *this - r; }

	Rational operator*(const Rational &r) const {
		return Rational(n * r.n, d * r.d);
	}
	Rational &operator*=(const Rational &r){ return *this = *this * r; }

	Rational operator/(const Rational &r) const {
		return Rational(n * r.d, d * r.n);
	}
	Rational &operator/=(const Rational &r){ return *this = *this / r; }

	bool operator<(const Rational &r) const { return n * r.d < r.n * d; }
	bool operator<=(const Rational &r) const { return n * r.d <= r.n * d; }
	bool operator>(const Rational &r) const { return n * r.d > r.n * d; }
	bool operator>=(const Rational &r) const { return n * r.d >= r.n * d; }

};

ostream &operator<<(ostream &os, const Rational &r){
	os << r.nume() << "/" << r.deno();
	return os;
}

int main(){
	ll a, b, c, d;
	cin >> a >> b >> c >> d;
	Rational A(a, b), B(c, d);
	cout << "A +  B = " << A + B << endl;
	cout << "A -  B = " << A - B << endl;
	cout << "A *  B = " << A * B << endl;
	cout << "A /  B = " << A / B << endl;
	cout << "A <  B = " << (A < B) << endl;
	cout << "A <= B = " << (A <= B) << endl;
	cout << "A >  B = " << (A > B) << endl;
	cout << "A >= B = " << (A >= B) << endl;
	return 0;
}

