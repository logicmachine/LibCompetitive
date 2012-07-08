#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

template <typename T>
class Matrix {

private:
	int N, M;
	vector< vector<T> > data;

	template <typename _Func>
	Matrix<T> apply(_Func f) const {
		Matrix<T> ret(N, M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j]); }
		}
		return ret;
	}

	template <typename _Func>
	Matrix<T> apply_scalar(const T &s, _Func f) const { return apply(bind2nd(f, s)); }

	template <typename _Func>
	Matrix<T> apply_mat(const Matrix<T> &m, _Func f) const {
		assert(N == m.N && M == m.M);
		Matrix<T> ret(N, M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j], m(i, j)); }
		}
		return ret;
	}

public:
	Matrix(int N, int M) : N(N), M(M), data(N, vector<T>(M)) { }


	int rows() const { return N; }
	int columns() const { return M; }


	const T &operator()(int i, int j) const { return data[i][j]; }
	T &operator()(int i, int j){ return data[i][j]; }


	Matrix<T> operator-() const { return apply(negate<T>()); }


	Matrix<T> operator+(const T &s) const { return apply_scalar(s, plus<T>()); }
	Matrix<T> &operator+=(const T &s){ return *this = *this + s; }

	Matrix<T> operator-(const T &s) const { return apply_scalar(s, minus<T>()); }
	Matrix<T> &operator-=(const T &s){ return *this = *this - s; }

	Matrix<T> operator*(const T &s) const { return apply_scalar(s, multiplies<T>()); }
	Matrix<T> &operator*=(const T &s){ return *this = *this * s; }

	Matrix<T> operator/(const T &s) const { return apply_scalar(s, divides<T>()); }
	Matrix<T> &operator/=(const T &s){ return *this = *this / s; }

	Matrix<T> operator%(const T &s) const { return apply_scalar(s, modulus<T>()); }
	Matrix<T> &operator%=(const T &s){ return *this = *this % s; }


	Matrix<T> operator+(const Matrix<T> &m) const { return apply_mat(m, plus<T>()); }
	Matrix<T> &operator+=(const Matrix<T> &m){ return *this = *this + m; }

	Matrix<T> operator-(const Matrix<T> &m) const { return apply_mat(m, minus<T>()); }
	Matrix<T> &operator-=(const Matrix<T> &m){ return *this = *this - m; }

	Matrix<T> operator*(const Matrix<T> &m) const {
		assert(M == m.N);
		Matrix<T> ret(N, m.M);
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < m.M; ++j){
				for(int k = 0; k < M; ++k){ ret(i, j) += data[i][k] * m(k, j); }
			}
		}
		return ret;
	}
	Matrix<T> &operator*=(const Matrix<T> &m){ return *this = *this * m; }

};

template <typename T>
ostream &operator<<(ostream &os, const Matrix<T> &m){
	for(int i = 0; i < m.rows(); ++i){
		for(int j = 0; j < m.columns(); ++j){ os << m(i, j) << "\t"; }
		os << endl;
	}
	return os;
}

int main(){
	int N, M, s;
	cin >> N >> M >> s;
	Matrix<int> A(N, M), B(N, M);
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < M; ++j){ cin >> A(i, j); }
	}
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < M; ++j){ cin >> B(i, j); }
	}
	cout << "-A =" << endl << -A << endl;
	cout << "A + s =" << endl << A + s << endl;
	cout << "A - s =" << endl << A - s << endl;
	cout << "A * s =" << endl << A * s << endl;
	cout << "A / s =" << endl << A / s << endl;
	cout << "A % s =" << endl << A % s << endl;
	cout << "A + B =" << endl << A + B << endl;
	cout << "A - B =" << endl << A - B << endl;
	cout << "A * B =" << endl << A * B << endl;
	return 0;
}

