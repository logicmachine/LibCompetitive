// SPOJ 439 - Not So Fast Multiplication
#include <iostream>
#include <string>
#include "common/header.h"
#include "math/fft.h"

static const int MAXSIZE = (1 << 14);
static const int DIGIT = 2, MOD = 100;
static const double EPS = 1e-4;
complex<double> vx[MAXSIZE], vy[MAXSIZE];
complex<double> vfx[MAXSIZE], vfy[MAXSIZE];

int convert(complex<double> *v, const string &s){
	fill(v, v + MAXSIZE, complex<double>());
	int written = 0, cur = 0;
	for(size_t i = 0, j = 1; i < s.size(); ++i){
		cur += (s[s.size() - 1 - i] - '0') * j;
		if(i % DIGIT == DIGIT - 1){
			v[written++] = complex<double>(cur, 0);
			cur = 0;
			j = 1;
		}else{
			j *= 10;
		}
	}
	v[written++] = complex<double>(cur, 0);
	return written;
}

string convert(const complex<double> *v, int size){
	string s(size * DIGIT, '0');
	double carry = 0.0;
	int last = 1;
	for(int i = 0; i < size; ++i){
		const double x = max(v[i].real() + carry, 0.0);
		int y = static_cast<int>(x + EPS) % MOD;
		for(int j = 0; j < DIGIT; ++j){
			s[i * DIGIT + j] = y % 10 + '0';
			if(y % 10 != 0){ last = i * DIGIT + j + 1; }
			y /= 10;
		}
		carry = floor(x / MOD + EPS);
	}
	s.resize(last);
	reverse(s.begin(), s.end());
	return s;
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while(n--){
		string sx, sy;
		cin >> sx >> sy;
		int maxlen = convert(vx, sx);
		maxlen = max(maxlen, convert(vy, sy));
		int size = 1;
		while(size < maxlen * 2){ size *= 2; }
		libcomp::math::fft(vfx, vx, size);
		libcomp::math::fft(vfy, vy, size);
		for(int i = 0; i < size; ++i){ vfx[i] *= vfy[i]; }
		libcomp::math::fft(vx, vfx, size, true);
		cout << convert(vx, size) << endl;
	}
	return 0;
}

