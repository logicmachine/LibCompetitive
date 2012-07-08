#include <iostream>
#include <vector>

using namespace std;

bool bipartite_matching_dfs(
	int v, const vector< vector<int> > &conn,
	vector<bool> &used, vector<int> &match)
{
	used[v] = true;
	for(int i = 0; i < conn[v].size(); ++i){
		int u = conn[v][i], w = match[u];
		if(w < 0 || !used[w] && bipartite_matching_dfs(w, conn, used, match)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}
int bipartite_matching(const vector< vector<int> > &conn){
	int res = 0;
	vector<int> match(conn.size(), -1);
	vector<bool> used(conn.size(), false);
	for(int v = 0; v < conn.size(); ++v){
		if(match[v] < 0){
			fill(used.begin(), used.end(), false);
			if(bipartite_matching_dfs(v, conn, used, match)){ ++res; }
		}
	}
	return res;
}


int main(){
	vector< vector<int> > conn(6);
	// u1 -> v1
	conn[0].push_back(3); conn[3].push_back(0);
	// u1 -> v2
	conn[0].push_back(4); conn[4].push_back(0);
	// u2 -> v1
	conn[1].push_back(3); conn[3].push_back(1);
	// u2 -> v3
	conn[1].push_back(5); conn[5].push_back(1);
	// u3 -> v2
	conn[2].push_back(4); conn[4].push_back(2);

	cout << bipartite_matching(conn) << endl;
	return 0;
}
