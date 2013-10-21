// LiveArchive 6140 - Joining Couples
#include <iostream>
#include "graph/strongly_connected_components.h"
#include "graph/lowest_common_ancestor.h"

struct Edge {
	int to;
	Edge(int to) : to(to) { }
};

void write_recursive(
	int u, int k, vector<int> &destination,
	const vector< vector<Edge> > &conn)
{
	if(destination[u] >= 0){ return; }
	destination[u] = k;
	for(int i = 0; i < conn[u].size(); ++i){
		write_recursive(conn[u][i].to, k, destination, conn);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	while(cin >> n){
		vector< vector<Edge> > conn(n), rconn(n);
		for(int i = 0; i < n; ++i){
			int v;
			cin >> v;
			--v;
			conn[i].push_back(Edge(v));
			rconn[v].push_back(Edge(i));
		}
		const vector<int> scc =
			libcomp::graph::strongly_connected_components(conn);
		vector<int> ring_index(n, -1), tree_index(n, -1);
		vector<int> ring_length;
		int tree_count = 0;
		for(int i = 0; i < n; ++i){
			if(scc[i] == i || ring_index[i] >= 0){ continue; }
			int v = i, j = 0;
			do {
				ring_index[v] = j++;
				v = conn[v][0].to;
			} while(v != i);
			ring_length.push_back(j);
			write_recursive(i, tree_count++, tree_index, rconn);
			do {
				const int ri = ring_index[v];
				ring_index[v] = -1;
				write_recursive(v, ri, ring_index, rconn);
				v = conn[v][0].to;
			} while(v != i);
		}
		vector<int> local_count(tree_count), local_table(n);
		for(int i = 0; i < n; ++i){
			if(scc[i] != i){ continue; }
			local_table[i] = local_count[tree_index[i]]++;
		}
		vector< vector< vector<Edge> > > local_graph(tree_count);
		for(int i = 0; i < tree_count; ++i){
			local_graph[i].resize(local_count[i]);
		}
		vector<int> local_root(tree_count);
		for(int i = 0; i < n; ++i){
			const int u = local_table[scc[i]];
			const int tid = tree_index[scc[i]];
			for(int j = 0; j < rconn[i].size(); ++j){
				const int v = local_table[scc[rconn[i][j].to]];
				if(u == v){
					local_root[tid] = v;
				}else{
					local_graph[tid][u].push_back(Edge(v));
				}
			}
		}
		vector<libcomp::graph::LowestCommonAncestor> lca(tree_count);
		for(int i = 0; i < tree_count; ++i){
			lca[i] = libcomp::graph::LowestCommonAncestor(
				local_root[i], local_graph[i]);
		}
		int q;
		cin >> q;
		while(q--){
			int a, b;
			cin >> a >> b;
			--a; --b;
			if(tree_index[a] != tree_index[b]){
				cout << -1 << endl;
				continue;
			}
			const int tid = tree_index[a];
			const int la = local_table[scc[a]], lb = local_table[scc[b]];
			const int lc = lca[tid].query(la, lb);
			const int a_depth = lca[tid].get_depth(la);
			const int b_depth = lca[tid].get_depth(lb);
			const int c_depth = lca[tid].get_depth(lc);
			const int r_length = ring_length[tid];
			const int ri = min(ring_index[a], ring_index[b]);
			const int rj = max(ring_index[a], ring_index[b]);
			const int answer =
				min(rj - ri, ri + r_length - rj) +
				(a_depth - c_depth) + (b_depth - c_depth);
			cout << answer << endl;
		}
	}
	return 0;
}

