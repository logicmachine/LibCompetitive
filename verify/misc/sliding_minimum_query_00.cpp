// Codeforces 372 C - Watching Fireworks is Fun
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "common/header.h"
#include "misc/sliding_minimum_query.h"

int main(){
	using libcomp::misc::SlidingMinimumQuery;
	ios_base::sync_with_stdio(false);
	int n, m, d;
	cin >> n >> m >> d;
	vector<ll> a(m), b(m), t(m);
	for(int i = 0; i < m; ++i){
		cin >> a[i] >> b[i] >> t[i];
		--a[i];
	}
	vector<ll> dp(n);
	ll prev = t[0];
	for(int i = 0; i < m; ++i){
		const ll lim = (t[i] - prev) * d;
		ll head = lim + 1, tail = -lim;
		SlidingMinimumQuery< ll, greater<ll> > smq;
		for(int j = 0; j < n && j < head; ++j){ smq.push(dp[j]); }
		for(int j = 0; j < n; ++j){
			const ll c = b[i] - llabs(a[i] - j);
			dp[j] = smq.query() + c;
			if(head <  n){ smq.push(dp[head]); }
			if(tail >= 0){ smq.pop(); }
			++head; ++tail;
		}
		prev = t[i];
	}
	cout << *max_element(dp.begin(), dp.end()) << endl;
	return 0;
}

