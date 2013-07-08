// AOJ 1328 - Find the Outlier
#include <iostream>
#include <cmath>
#include "math/sweep_out.h"

const double EPS = 1e-2;

bool tolerant_eq(const vector<double> &a, const vector<double> &b){
	const int n = a.size();
	for(int i = 0; i < n; ++i){
		if(abs(a[i] - b[i]) > EPS){ return false; }
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		int d;
		cin >> d;
		if(d == 0){ break; }
		++d;
		const int e = d + 2;
		vector<double> v(e);
		for(int i = 0; i < e; ++i){ cin >> v[i]; }
		vector< vector<double> > solutions(1 << e);
		vector<int> written;
		for(int i = 0; i < (1 << e); ++i){
			if(__builtin_popcount(i) != d){ continue; }
			vector< vector<double> > A(d, vector<double>(d));
			vector<double> b(d);
			for(int j = 0, k = 0; j < e; ++j){
				if((i & (1 << j)) == 0){ continue; }
				double p = 1.0, r = j;
				for(int l = 0; l < d; ++l){
					A[k][l] = p;
					p *= r;
				}
				b[k] = v[j];
				++k;
			}
			solutions[i] = libcomp::math::sweep_out(A, b);
			written.push_back(i);
		}
		int answer = -1;
		for(int i = 0; answer < 0 && i < e; ++i){
			vector<double> reference;
			bool failed = false;
			for(int j = 0; j < written.size(); ++j){
				const int k = written[j];
				if((k & (1 << i)) != 0){ continue; }
				if(reference.empty()){
					reference = solutions[k];
				}else if(!tolerant_eq(reference, solutions[k])){
					failed = true;
					break;
				}
			}
			if(!failed){ answer = i; }
		}
		cout << answer << endl;
	}
	return 0;
}

