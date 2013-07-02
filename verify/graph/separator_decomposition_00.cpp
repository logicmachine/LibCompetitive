// Codeforces Round #190 (Div. 1) C - Ciel the Commander
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "common/header.h"
#include "graph/edge.h"
#include "graph/separator_decomposition.h"

int main(){
	using libcomp::graph::Edge;
	using libcomp::graph::separator_decomposition;
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector< vector<Edge> > conn(n);
	for(int i = 1; i < n; ++i){
		int a, b;
		cin >> a >> b;
		--a; --b;
		conn[a].push_back(Edge(b));
		conn[b].push_back(Edge(a));
	}
	vector<int> decomp = separator_decomposition(conn);
	string answer(n * 2 - 1, ' ');
	vector<int> degrees(n);
	for(int i = 0; i < n; ++i){
		answer[i * 2] = 'Z';
		if(i != decomp[i]){ ++degrees[decomp[i]]; }
	}
	queue<int> q;
	for(int i = 0; i < n; ++i){
		if(degrees[i] == 0){
			answer[i * 2] = 'Z';
			q.push(i);
		}
	}
	while(!q.empty()){
		const int u = q.front();
		q.pop();
		const int v = decomp[u];
		if(u == v){ continue; }
		answer[v * 2] = min<char>(answer[v * 2], answer[u * 2] - 1);
		if(--degrees[v] == 0){ q.push(v); }
	}
	cout << answer << endl;
	return 0;
}

