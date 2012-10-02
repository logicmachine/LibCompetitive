#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include <cstring>

using namespace std;

template <typename T, int N, int M>
class Matrix {

private:
	int data[N][M];

	template <typename _Func>
	Matrix<T, N, M> apply(_Func f) const {
		Matrix<T, N, M> ret;
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j]); }
		}
		return ret;
	}

	template <typename _Func>
	Matrix<T, N, M> apply_scalar(const T &s, _Func f) const {
		return apply(bind2nd(f, s));
	}

	template <typename _Func>
	Matrix<T, N, M> apply_mat(const Matrix<T, N, M> &m, _Func f) const {
		Matrix<T, N, M> ret;
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < M; ++j){ ret(i, j) = f(data[i][j], m(i, j)); }
		}
		return ret;
	}

public:
	Matrix(){ memset(data, 0, sizeof(data)); }


	int rows() const { return N; }
	int columns() const { return M; }


	const T &operator()(int i, int j) const { return data[i][j]; }
	T &operator()(int i, int j){ return data[i][j]; }


	Matrix<T, N, M> operator-() const { return apply(negate<T>()); }


	Matrix<T, N, M> operator+(const T &s) const { return apply_scalar(s, plus<T>()); }
	Matrix<T, N, M> &operator+=(const T &s){ return *this = *this + s; }

	Matrix<T, N, M> operator-(const T &s) const { return apply_scalar(s, minus<T>()); }
	Matrix<T, N, M> &operator-=(const T &s){ return *this = *this - s; }

	Matrix<T, N, M> operator*(const T &s) const { return apply_scalar(s, multiplies<T>()); }
	Matrix<T, N, M> &operator*=(const T &s){ return *this = *this * s; }

	Matrix<T, N, M> operator/(const T &s) const { return apply_scalar(s, divides<T>()); }
	Matrix<T, N, M> &operator/=(const T &s){ return *this = *this / s; }

	Matrix<T, N, M> operator%(const T &s) const { return apply_scalar(s, modulus<T>()); }
	Matrix<T, N, M> &operator%=(const T &s){ return *this = *this % s; }


	Matrix<T, N, M> operator+(const Matrix<T, N, M> &m) const { return apply_mat(m, plus<T>()); }
	Matrix<T, N, M> &operator+=(const Matrix<T, N, M> &m){ return *this = *this + m; }

	Matrix<T, N, M> operator-(const Matrix<T, N, M> &m) const { return apply_mat(m, minus<T>()); }
	Matrix<T, N, M> &operator-=(const Matrix<T, N, M> &m){ return *this = *this - m; }

	template <int L>
	Matrix<T, N, L> operator*(const Matrix<T, M, L> &m) const {
		Matrix<T, N, L> ret;
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < L; ++j){
				for(int k = 0; k < M; ++k){ ret(i, j) += data[i][k] * m(k, j); }
			}
		}
		return ret;
	}
	template <int L>
	Matrix<T, N, L> &operator*=(const Matrix<T, M, L> &m){ return *this = *this * m; }

};

template <typename T, int N, int M>
ostream &operator<<(ostream &os, const Matrix<T, N, M> &m){
	for(int i = 0; i < m.rows(); ++i){
		for(int j = 0; j < m.columns(); ++j){ os << m(i, j) << "\t"; }
		os << endl;
	}
	return os;
}

int main(){
	int N = 3, M = 3, s = 10;
	Matrix<int, 3, 3> A, B;
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

