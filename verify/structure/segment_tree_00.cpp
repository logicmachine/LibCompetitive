// AOJ 2431 - House Moving
#include <iostream>
#include "structure/segment_tree.h"

int main(){
	using libcomp::structure::MaxSegmentTreeTraits;
	using libcomp::structure::SegmentTree;
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> x(n);
	for(int i = 0; i < n; ++i){ cin >> x[i]; }
	SegmentTree< MaxSegmentTreeTraits<ll> > st(n + 1);
	ll max_sum = 0;
	for(int i = 0; i < n; ++i){
		const ll y = max(0ll, st.query(0, x[i])) + x[i];
		max_sum = max(max_sum, y);
		st.update(x[i], y);
	}
	cout << (static_cast<ll>(n) * (n + 1)) / 2 - max_sum << endl;
	return 0;
}

