// UVa 10594 - Data flow
#include <iostream>
#include <vector>
#include "common/header.h"
#include "graph/edge.h"
#include "graph/minimum_cost_flow_primal_dual.h"

int main(){
	using libcomp::graph::Edge;
	using libcomp::graph::minimum_cost_flow_primal_dual;
	ios_base::sync_with_stdio(false);
	int n, m;
	while(cin >> n >> m){
		vector<ll> a(m), b(m), c(m);
		for(int i = 0; i < m; ++i){
			cin >> a[i] >> b[i] >> c[i];
			--a[i]; --b[i];
		}
		ll d, k;
		cin >> d >> k;
		vector< vector<Edge> > conn(n);
		for(int i = 0; i < m; ++i){
			conn[a[i]].push_back(Edge(b[i], c[i], k));
			conn[b[i]].push_back(Edge(a[i], c[i], k));
		}
		const ll answer = minimum_cost_flow_primal_dual(0, n - 1, d, conn);
		if(answer < 0){
			cout << "Impossible." << endl;
		}else{
			cout << answer << endl;
		}
	}
	return 0;
}

