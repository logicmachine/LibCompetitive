// Codeforces 343D - Water Tree
#include <iostream>
#include "graph/heavy_light_decomposition.h"

struct Edge {
	int to;
	explicit Edge(int to = 0) : to(to) { }
};

template <typename T>
class BinaryIndexedTree {
private:
	vector<T> data;
public:
	BinaryIndexedTree(int n = 0) : data(n + 1) { }
	T query(int i){
		T s = T();
		for(; i > 0; i -= i & -i){ s = max(s, data[i]); }
		return s;
	}
	void update(int i, const T &x){
		for(++i; i < static_cast<int>(data.size()); i += i & -i){
			data[i] = max(data[i], x);
		}
	}

};

int main(){
	using libcomp::graph::HeavyLightDecomposer;
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
	const HeavyLightDecomposer decomp(conn);
	const int m = decomp.path_count();
	vector< BinaryIndexedTree<int> > fill_bits(m);
	vector< BinaryIndexedTree<int> > empty_bits(m);
	for(int i = 0; i < m; ++i){
		fill_bits[i] = BinaryIndexedTree<int>(decomp.path_length(i));
		empty_bits[i] = BinaryIndexedTree<int>(decomp.path_length(i));
	}
	int q;
	cin >> q;
	for(int ts = 1; ts <= q; ++ts){
		int c, v;
		cin >> c >> v;
		--v;
		if(c == 1){
			const int dn = decomp.path_id(v);
			const int dl = decomp.local_index(v);
			fill_bits[dn].update(dl, ts);
		}else if(c == 2){
			int cur = v;
			while(cur >= 0){
				const int dn = decomp.path_id(cur);
				const int dl = decomp.local_index(cur);
				const int ln = decomp.path_length(dn);
				empty_bits[dn].update(ln - dl - 1, ts);
				cur = decomp.parent_vertex_id(dn);
			}
		}else if(c == 3){
			int empty_ts = 0, fill_ts = 0;
			{
				const int dn = decomp.path_id(v);
				const int dl = decomp.local_index(v);
				const int ln = decomp.path_length(dn);
				empty_ts = empty_bits[dn].query(ln - dl);
			}
			int cur = v;
			while(cur >= 0){
				const int dn = decomp.path_id(cur);
				const int dl = decomp.local_index(cur);
				fill_ts = max(fill_ts, fill_bits[dn].query(dl + 1));
				cur = decomp.parent_vertex_id(dn);
			}
			cout << (empty_ts >= fill_ts ? "0" : "1") << endl;
		}
	}
	return 0;
}

