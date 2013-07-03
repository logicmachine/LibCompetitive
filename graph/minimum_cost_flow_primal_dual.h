/**
 *  @file graph/minimum_cost_flow_primal_dual.h
 */
#pragma once
#include <vector>
#include <queue>
#include <utility>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup minimum_cost_flow_primal_dual Minimum cost flow (Primal-Dual)
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 最小費用流を求める際に内部で利用する辺の型
 */
struct MinimumCostFlowEdge {
	/// 辺の反対側の端点
	int to;
	/// 辺の容量
	ll capacity;
	/// 辺にフローを1流す際にかかるコスト
	ll cost;
	/// 逆辺のインデックス
	int rev;
	/**
	 *  @brief コンストラクタ
	 *  @param[in] to        辺の反対側の端点
	 *  @param[in] capacity  辺の容量
	 *  @param[in] cost      辺にフローを1流す際にかかるコスト
	 *  @param[in] rev       逆辺のインデックス
	 */
	explicit MinimumCostFlowEdge(
		int to = 0, ll capacity = 0, ll cost = 0, int rev = 0) :
		to(to), capacity(capacity), cost(cost), rev(rev)
	{ }
};

/**
 *  @brief 最小費用流 (Primal-Dual法)
 *
 *  Primal-Dual法による最小費用流。
 *  計算量は \f$ \mathcal{O}(F |E| \log{|V|}) \f$。
 *
 *  @tparam    EDGE_TYPE  辺データ型。to, weight, capacity を持つもの。
 *  @param[in] source     ソースになる頂点
 *  @param[in] sink       シンクになる頂点
 *  @param[in] flow       流したい流量
 *  @param[in] conn       グラフデータ
 *  @return    sourceからsinkへflowだけフローを流す場合の最小コスト。
 *             フローを流しきることができなかった場合は-1。
 */
template <typename EDGE_TYPE>
ll minimum_cost_flow_primal_dual(
	int source, int sink, ll flow, const vector< vector<EDGE_TYPE> > &conn)
{
	typedef pair<int, int> pii;
	typedef MinimumCostFlowEdge MCFEdge;
	const ll INF = 1000000000000000000ll;
	// Convert graph format
	const int n = conn.size();
	vector< vector<MCFEdge> > iconn(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < conn[i].size(); ++j){
			const int to = conn[i][j].to;
			const ll cap = conn[i][j].capacity;
			const ll cost = conn[i][j].weight;
			iconn[i].push_back(MCFEdge(to, cap, cost, iconn[to].size()));
			iconn[to].push_back(MCFEdge(i, 0, -cost, iconn[i].size() - 1));
		}
	}
	// Primal-Dual
	ll res = 0;
	vector<ll> h(n);
	vector<int> prevv(n), preve(n);
	while(flow > 0){
		priority_queue< pii, vector<pii>, greater<pii> > pq;
		vector<ll> dist(n, INF);
		dist[source] = 0;
		pq.push(pii(0, source));
		while(!pq.empty()){
			pii p = pq.top();
			pq.pop();
			int v = p.second;
			if(dist[v] < p.first){ continue; }
			for(int i = 0; i < iconn[v].size(); ++i){
				MCFEdge &e = iconn[v][i];
				if(e.capacity > 0 &&
				   dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
				{
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					pq.push(pii(dist[e.to], e.to));
				}
			}
		}
		if(dist[sink] == INF){ return -1; }
		for(int v = 0; v < n; ++v){ h[v] += dist[v]; }
		ll d = flow;
		for(int v = sink; v != source; v = prevv[v]){
			d = min(d, iconn[prevv[v]][preve[v]].capacity);
		}
		flow -= d;
		res += d * h[sink];
		for(int v = sink; v != source; v = prevv[v]){
			MCFEdge &e = iconn[prevv[v]][preve[v]];
			e.capacity -= d;
			iconn[v][e.rev].capacity += d;
		}
	}
	return res;
}

/**
 *  @}
 */

}
}

