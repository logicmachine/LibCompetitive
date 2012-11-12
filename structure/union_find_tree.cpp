#include <vector>

using namespace std;

class UnionFindTree {

private:
	vector<int> parent;
	vector<int> rank;

public:
	explicit UnionFindTree(int n = 0) :
		parent(n), rank(n)
	{
		for(int i = 0; i < n; ++i){ parent[i] = i; }
	}

	int find(int x){
		if(parent[x] == x){ return x; }
		parent[x] = find(parent[x]);
		return parent[x];
	}
	int unite(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y){ return x; }
		if(rank[x] < rank[y]){
			parent[x] = y;
			return y;
		}else if(rank[x] > rank[y]){
			parent[y] = x;
			return x;
		}else{
			parent[y] = x;
			++rank[x];
			return x;
		}
	}

	bool same(int x, int y){
		return find(x) == find(y);
	}

};

