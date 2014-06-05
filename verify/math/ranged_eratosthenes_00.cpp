// SPOJ 2 - Prime Generator
#include <iostream>
#include "math/ranged_eratosthenes.h"

int main(){
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		ll n, m;
		cin >> n >> m;
		vector<ll> primes = libcomp::math::ranged_eratosthenes(n, m + 1);
		for(int i = 0; i < primes.size(); ++i){
			cout << primes[i] << endl;
		}
		if(T > 0){ cout << endl; }
	}
	return 0;
}

