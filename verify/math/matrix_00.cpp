// AtCoder jag2013spring J - Tree Reconstruction
#include <iostream>
#include "math/matrix.h"

int main(){
	using libcomp::math::Matrix;
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	Matrix<int> mat(n, m);
	for(int i = 0; i < m; ++i){
		int a, b;
		cin >> a >> b;
		--a; --b;
		mat(a, i) = 1;
		mat(b, i) = -1;
	}
	cout << (m - mat.rank()) << endl;
	return 0;
}

