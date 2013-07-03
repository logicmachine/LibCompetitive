/**
 *  @file graph/maximum_flow_dinic.h
 */
#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup maximum_flow_dinic Maximum flow (Dinic)
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 最大流を求める際に内部で利用する辺の型
 */
struct MaximumFlowEdge {
	/// 辺の反対側の端点
	int to;
	/// 辺の容量
	ll capacity;
	/// 逆辺のインデックス
	int rev;
	/**
	 *  @brief コンストラクタ
	 *  @param[in] to        辺の反対側の端点
	 *  @param[in] capacity  辺の容量
	 *  @param[in] rev       逆辺のインデックス
	 */
	explicit MaximumFlowEdge(int to = 0, ll capacity = 0, int rev = 0) :
		to(to), capacity(capacity), rev(rev)
	{ }
};

/**
 *  @brief 最大流 (Dinic法)
 *
 *  Dinic法による最大流。
 *  計算量は \f$ \mathcal{O}(|E| |V|^2) \f$。
 *
 *  @tparam    EDGE_TYPE  辺データ型。to, capacity を持つもの。
 *  @param[in] source     ソースになる頂点
 *  @param[in] sink       シンクになる頂点
 *  @param[in] conn       グラフデータ
 *  @return    sourceからsinkへ流すことができる流量の最大値。
 */
template <typename EDGE_TYPE>
ll maximum_flow_dinic(
	int source, int sink, const vector< vector<EDGE_TYPE> > &conn)
{
	typedef MaximumFlowEdge MFEdge;
	const ll INF = 1000000000000000000ll;
	// Convert graph format
	const int n = conn.size();
	vector< vector<MFEdge> > iconn(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < conn[i].size(); ++j){
			const int to = conn[i][j].to;
			const ll cap = conn[i][j].capacity;
			iconn[i].push_back(MFEdge(to, cap, iconn[to].size()));
			iconn[to].push_back(MFEdge(i, 0, iconn[i].size() - 1));
		}
	}
	// DFS function
	struct {
		typedef MaximumFlowEdge MFEdge;
		ll operator()(
			int v, int sink, ll f, const vector<int> &level,
			vector<int> &iter, vector< vector<MFEdge> > &conn)
		{
			if(v == sink){ return f; }
			for(; iter[v] < conn[v].size(); ++iter[v]){
				MFEdge &e = conn[v][iter[v]];
				if(e.capacity > 0 && level[v] < level[e.to]){
					ll d = (*this)(
						e.to, sink, min(f, e.capacity), level, iter, conn);
					if(d > 0){
						e.capacity -= d;
						conn[e.to][e.rev].capacity += d;
						return d;
					}
				}
			}
			return 0;
		}
	} dinic_dfs;
	// Dinic
	ll flow = 0;
	while(true){
		vector<int> level(n, -1);
		queue<int> q;
		level[source] = 0;
		q.push(source);
		while(!q.empty()){
			const int v = q.front();
			q.pop();
			for(int i = 0; i < iconn[v].size(); ++i){
				const MFEdge &e = iconn[v][i];
				if(e.capacity > 0 && level[e.to] < 0){
					level[e.to] = level[v] + 1;
					q.push(e.to);
				}
			}
		}
		if(level[sink] < 0){ break; }
		vector<int> iter(n, 0);
		while(true){
			const ll f = dinic_dfs(
				source, sink, INF, level, iter, iconn);
			if(f <= 0){ break; }
			flow += f;
		}
	}
	return flow;
}

/**
 *  @}
 */

}
}

