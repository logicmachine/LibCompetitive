#include <vector>
#include <algorithm>

using namespace std;

void strongly_connected_components_dfs(
	int v, const vector< vector<int> > &conn,
	vector<bool> &used, vector<int> &vs)
{
	used[v] = true;
	for(int i = 0; i < conn[v].size(); ++i){
		if(!used[conn[v][i]]){
			strongly_connected_components_dfs(conn[v][i], conn, used, vs);
		}
	}
	vs.push_back(v);
}
void strongly_connected_component_rdfs(
	int v, int k, const vector< vector<int> > &rconn,
	vector<bool> &used, vector<int> &comp)
{
	used[v] = true;
	comp[v] = k;
	for(int i = 0; i < rconn[v].size(); ++i){
		if(!used[rconn[v][i]]){
			strongly_connected_component_rdfs(
				rconn[v][i], k, rconn, used, comp);
		}
	}
}
vector<int> strongly_connected_components(const vector< vector<int> > &conn){
	int N = conn.size();
	vector< vector<int> > rconn(N);
	for(int i = 0; i < conn.size(); ++i){
		for(int j = 0; j < conn[i].size(); ++j){
			rconn[conn[i][j]].push_back(i);
		}
	}
	vector<bool> used(N);
	vector<int> vs;
	for(int i = 0; i < N; ++i){
		if(!used[i]){ strongly_connected_components_dfs(i, conn, used, vs); }
	}
	fill(used.begin(), used.end(), 0);
	vector<int> result(N);
	for(int i = vs.size() - 1, k = 0; i >= 0; --i){
		if(!used[vs[i]]){
			strongly_connected_component_rdfs(vs[i], k++, rconn, used, result);
		}
	}
	return result;
}
