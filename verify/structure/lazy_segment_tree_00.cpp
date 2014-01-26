#include <iostream>
#include <vector>
#include "common/header.h"
#include "structure/lazy_segment_tree.h"
#include "graph/heavy_light_decomposition.h"

using libcomp::structure::LazySegmentTree;
using libcomp::graph::HeavyLightDecomposer;

const ll INF = 1000000000000000000ll;;

struct Edge {
	int to;
	explicit Edge(int to = 0) : to(to) { }
};

struct STValue {
	ll left, right, partial, all;
	explicit STValue(ll l = 0, ll r = 0, ll p = 0, ll a = 0) :
		left(l), right(r), partial(p), all(a)
	{ }
};
struct STModifier {
	ll time_stamp, value;
	explicit STModifier(ll t = 0, ll v = 0) :
		time_stamp(t), value(v)
	{ }
};
struct STTraits {
	typedef STValue value_type;
	typedef STModifier modifier_type;

	value_type default_value() const { return STValue(0, 0, -INF, 0); }
	modifier_type default_modifier() const { return STModifier(-1, 0); }

	STValue merge_value(const STValue &a, const STValue &b) const {
		STValue result;
		if(a.partial < a.all){ return b; }
		if(b.partial < b.all){ return a; }
		result.left = max(a.left, a.all + b.left);
		result.right = max(a.right + b.all, b.right);
		result.partial = max(max(a.partial, b.partial), a.right + b.left);
		result.all = a.all + b.all;
		return result;
	}
	STModifier merge_modifier(const STModifier &a, const STModifier &b) const {
		return (a.time_stamp >= b.time_stamp ? a : b);
	}
	STValue resolve(
		int a, int b, const STValue &val, const STModifier &mod) const
	{
		if(mod.time_stamp < 0){ return val; }
		STValue result;
		if(mod.value > 0){
			result.left = mod.value * (b - a);
			result.right = mod.value * (b - a);
			result.partial = mod.value * (b - a);
			result.all = mod.value * (b - a);
		}else{
			result.left = mod.value;
			result.right = mod.value;
			result.partial = mod.value;
			result.all = mod.value * (b - a);
		}
		return result;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	vector<int> w(n);
	for(int i = 0; i < n; ++i){ cin >> w[i]; }
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
	vector< LazySegmentTree<STTraits> > segtrees(m);
	for(int i = 0; i < m; ++i){
		const int len = decomp.path_length(i);
		vector<STValue> values(len);
		for(int j = 0; j < len; ++j){
			const int x = w[decomp.vertex_id(i, j)];
			values[j] = STValue(x, x, x, x);
		}
		segtrees[i] = LazySegmentTree<STTraits>(values.begin(), values.end());
	}
	for(int ts = 0; ts < q; ++ts){
		int t, a, b, c;
		cin >> t >> a >> b >> c;
		--a; --b;
		const vector<HeavyLightDecomposer::Segment> route =
			decomp.shortest_path(a, b);
		if(t == 1){
			for(int i = 0; i < route.size(); ++i){
				const int p = route[i].path;
				int first = route[i].first, last = route[i].last;
				if(first > last){
					swap(first, last);
					++first; ++last;
				}
				segtrees[p].modify(first, last, STModifier(ts, c));
			}
		}else if(t == 2){
			const int len = route.size();
			vector<STValue> values(len);
			vector<ll> integral(len + 1);
			ll answer = -INF;
			for(int i = 0; i < len; ++i){
				const int p = route[i].path;
				int first = route[i].first, last = route[i].last;
				if(first > last){
					const STValue v = segtrees[p].query(last + 1, first + 1);
					values[i] = STValue(v.right, v.left, v.partial, v.all);
				}else{
					const STValue v = segtrees[p].query(first, last);
					values[i] = v;
				}
				integral[i] = values[i].all;
				answer = max(answer, values[i].partial);
			}
			ll sum = 0;
			for(int i = 0; i < len; ++i){
				const ll t = integral[i];
				integral[i] = sum;
				sum += t;
			}
			integral.back() = sum;
			for(int l = 0; l < len; ++l){
				for(int r = l + 1; r < len; ++r){
					const ll x = integral[r] - integral[l + 1];
					answer = max(
						answer, values[l].right + values[r].left + x);
				}
			}
			cout << answer << endl;
		}
	}
	return 0;
}

