// LiveArchive 6438 - Railroad
#include <iostream>
#include <string>
#include <vector>
#include "graph/edge.h"
#include "graph/topological_sort.h"

int main(){
	using libcomp::graph::Edge;
	using libcomp::graph::topological_sort;
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int caseNum = 1; caseNum <= T; ++caseNum){
		int n, k;
		cin >> n >> k;
		vector< vector<Edge> > h_conn(n), h_rconn(n);
		for(int i = 0; i < k; ++i){
			string t;
			int x, y, z;
			cin >> t >> x >> y >> z;
			--x; --y; --z;
			if(t == "F"){
				h_conn[x].push_back(Edge(y));
				h_conn[x].push_back(Edge(z));
				h_rconn[y].push_back(Edge(x));
				h_rconn[z].push_back(Edge(x));
			}else{
				h_conn[x].push_back(Edge(z));
				h_conn[y].push_back(Edge(z));
				h_rconn[z].push_back(Edge(x));
				h_rconn[z].push_back(Edge(y));
			}
		}
		const vector<int> h_order = topological_sort(h_conn);
		vector<int> upper(n, -1), lower(n, -1);
		upper[0] = 0;
		lower[0] = 1;
		int area_count = 2;
		for(int i = 0; i < n; ++i){
			const int u = h_order[i];
			if(h_conn[u].size() == 2){
				const int v0 = h_conn[u][0].to, v1 = h_conn[u][1].to;
				upper[v0] = upper[u];
				lower[v0] = area_count;
				upper[v1] = area_count;
				lower[v1] = lower[u];
				++area_count;
			}else if(h_conn[u].size() == 1){
				const int v = h_conn[u][0].to;
				const int u0 = h_rconn[v][0].to, u1 = h_rconn[v][1].to;
				upper[v] = upper[u0];
				lower[v] = lower[u1];
			}
		}
		vector< vector<Edge> > v_conn(area_count);
		for(int i = 0; i < n; ++i){
			const int u = upper[i], v = lower[i];
			v_conn[u].push_back(Edge(v));
		}
		const vector<int> v_order = topological_sort(v_conn);
		vector<int> dp(area_count, 0);
		for(int i = 0; i < area_count; ++i){
			const int u = v_order[i];
			for(int j = 0; j < v_conn[u].size(); ++j){
				const int v = v_conn[u][j].to;
				dp[v] = max(dp[v], dp[u] + 1);
			}
		}
		cout << "Case #" << caseNum << ": " << dp[1] << endl;
	}
	return 0;
}

