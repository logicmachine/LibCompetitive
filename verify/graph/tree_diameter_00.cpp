// Codeforces 455C - Civilization
#include <iostream>
#include <vector>
#include "structure/union_find_tree.h"
#include "graph/tree_diameter.h"

struct Edge {
	int to;
	explicit Edge(int to) : to(to) { }
};

int main(){
	using libcomp::structure::UnionFindTree;
	using libcomp::graph::tree_diameter;
	ios_base::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> q;
	vector< vector<Edge> > conn(n);
	UnionFindTree uft(n);
	for(int i = 0; i < m; ++i){
		int a, b;
		cin >> a >> b;
		--a; --b;
		uft.unite(a, b);
		conn[a].emplace_back(b);
		conn[b].emplace_back(a);
	}
	vector<int> diameters(n);
	for(int i = 0; i < n; ++i){
		if(uft.find(i) != i){ continue; }
		diameters[i] = tree_diameter(conn, i);
	}
	while(q--){
		int t;
		cin >> t;
		if(t == 1){
			int a;
			cin >> a;
			--a;
			cout << diameters[uft.find(a)] << endl;
		}else{
			int a, b;
			cin >> a >> b;
			--a; --b;
			if(uft.same(a, b)){ continue; }
			const int x = diameters[uft.find(a)];
			const int y = diameters[uft.find(b)];
			const int c = uft.unite(a, b);
			diameters[c] = max(max(x, y), (x + 1) / 2 + (y + 1) / 2 + 1);
		}
	}
	return 0;
}

