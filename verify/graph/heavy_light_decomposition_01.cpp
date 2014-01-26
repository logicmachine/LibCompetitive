// CodeChef DGCD - Dynamic GCD
#include <cstdio>
#include <string>
#include <cmath>
#include "structure/segment_tree.h"
#include "structure/binary_indexed_tree.h"
#include "graph/heavy_light_decomposition.h"

using libcomp::structure::SegmentTree;
using libcomp::structure::BinaryIndexedTree;
using libcomp::graph::HeavyLightDecomposer;

struct GCDSegmentTreeTraits {
	typedef int value_type;
	int default_value() const { return 0; }
	int operator()(ll a, ll b) const {
		if(a == 0){ return b; }
		if(b == 0){ return a; }
		return __gcd(abs(a), abs(b));
	}
};

struct Edge {
	int to;
	explicit Edge(int to = 0) : to(to) { }
};

typedef SegmentTree<GCDSegmentTreeTraits> GCDSegmentTree;
typedef HeavyLightDecomposer::Segment Segment;

int main(){
	int n;
	scanf("%d", &n);
	vector< vector<Edge> > conn(n);
	for(int i = 1; i < n; ++i){
		int a, b;
		scanf("%d%d", &a, &b);
		conn[a].push_back(Edge(b));
		conn[b].push_back(Edge(a));
	}
	vector<int> v(n);
	for(int i = 0; i < n; ++i){ scanf("%d", &v[i]); }
	const HeavyLightDecomposer decomp(conn);
	const int m = decomp.path_count();
	vector<GCDSegmentTree> segtrees(m);
	vector< BinaryIndexedTree<int> > bits(m);
	vector< vector<int> > diffs(m);
	for(int i = 0; i < m; ++i){
		const int len = decomp.path_length(i);
		vector<int> init(len + 1);
		for(int j = 0; j < len; ++j){
			init[j] = v[decomp.vertex_id(i, j)];
		}
		bits[i] = BinaryIndexedTree<int>(len + 1);
		for(int j = len - 1; j >= 0; --j){
			const ll p = (j == 0 ? 0 : init[j - 1]);
			init[j] = init[j] - p;
			bits[i].add(j, init[j]);
		}
		segtrees[i] = GCDSegmentTree(init.begin(), init.end());
		diffs[i] = init;
	}
	int q;
	scanf("%d", &q);
	while(q--){
		char t[16];
		scanf("%s", t);
		if(t[0] == 'F'){
			int a, b;
			scanf("%d%d", &a, &b);
			vector<Segment> route = decomp.shortest_path(a, b);
			int answer = 0;
			for(int i = 0; i < route.size(); ++i){
				Segment &s = route[i];
				if(s.first > s.last){
					swap(s.first, s.last);
					++s.first; ++s.last;
				}
				const int p = s.path;
				const int x = s.first, y = s.last;
				const int z = abs(segtrees[p].query(x + 1, y));
				const int w = abs(bits[p].sum(x + 1));
				int local = 0;
				if(z != 0 && w != 0){
					local = __gcd(z, w);
				}else if(z == 0){
					local = w;
				}else{
					local = z;
				}
				if(local > 0){
					answer = (answer == 0 ? local : __gcd(answer, local));
				}
			}
			printf("%d\n", answer);
		}else{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vector<Segment> route = decomp.shortest_path(a, b);
			ll answer = -1;
			for(int i = 0; i < route.size(); ++i){
				Segment &s = route[i];
				if(s.first > s.last){
					swap(s.first, s.last);
					++s.first; ++s.last;
				}
				const int p = s.path;
				const int x = s.first, y = s.last;
				bits[p].add(x, c);
				bits[p].add(y, -c);
				diffs[p][x] += c;
				diffs[p][y] -= c;
				segtrees[p].update(x, diffs[p][x]);
				segtrees[p].update(y, diffs[p][y]);
				
			}
		}
	}
	return 0;
}

