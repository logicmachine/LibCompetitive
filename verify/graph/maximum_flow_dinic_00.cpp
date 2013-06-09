// UVa 820 - Internet Bandwidth
#include <iostream>
#include <vector>
#include "common/header.h"
#include "graph/edge.h"
#include "graph/maximum_flow_dinic.h"

int main(){
	using libcomp::graph::Edge;
	using libcomp::graph::maximum_flow_dinic;
	ios_base::sync_with_stdio(false);
	for(int caseNum = 1; true; ++caseNum){
		int n;
		cin >> n;
		if(n == 0){ break; }
		int source, sink, m;
		cin >> source >> sink >> m;
		--source; --sink;
		vector< vector<Edge> > conn(n);
		while(m--){
			int a, b, c;
			cin >> a >> b >> c;
			--a; --b;
			conn[a].push_back(Edge(b, 0, c));
			conn[b].push_back(Edge(a, 0, c));
		}
		const ll answer = maximum_flow_dinic(source, sink, conn);
		cout << "Network " << caseNum << endl;
		cout << "The bandwidth is " << answer << "." << endl << endl;
	}
	return 0;
}

