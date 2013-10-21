/**
 *  @file graph/strongly_connected_components.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup strongly_connected_components Strongly connected components
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 強連結成分分解
 *
 *  計算量は \f$ \mathcal{O}(|V|+|E|) \f$。
 *
 * @tparam    EDGE_TYPE  辺データ型。to を持つもの。
 * @param[in] conn       グラフデータ。
 * @return    各頂点がどの強連結成分に属しているかを示すテーブル。
 *            強連結成分を示す番号はそれに属するいずれかの頂点の番号となる。
 */
template <typename EDGE_TYPE>
vector<int> strongly_connected_components(
	const vector< vector<EDGE_TYPE> > &conn)
{
	const int n = conn.size();
	vector< vector<int> > rconn(n);
	for(int i = 0; i < conn.size(); ++i){
		for(int j = 0; j < conn[i].size(); ++j){
			rconn[conn[i][j].to].push_back(i);
		}
	}
	// Forward DFS
	struct {
		void operator()(
			int v, const vector< vector<EDGE_TYPE> > &conn,
			vector<bool> &used, vector<int> &vs)
		{
			used[v] = true;
			for(int i = 0; i < conn[v].size(); ++i){
				if(used[conn[v][i].to]){ continue; }
				(*this)(conn[v][i].to, conn, used, vs);
			}
			vs.push_back(v);
		}
	} scc_forward_dfs;
	vector<bool> used(n);
	vector<int> vs;
	for(int i = 0; i < n; ++i){
		if(!used[i]){ scc_forward_dfs(i, conn, used, vs); }
	}
	// Backward DFS
	struct {
		void operator()(
			int v, int k, const vector< vector<int> > &rconn,
			vector<bool> &used, vector<int> &comp)
		{
			used[v] = true;
			comp[v] = k;
			for(int i = 0; i < rconn[v].size(); ++i){
				if(used[rconn[v][i]]){ continue; }
				(*this)(rconn[v][i], k, rconn, used, comp);
			}
		}
	} scc_backward_dfs;
	fill(used.begin(), used.end(), 0);
	vector<int> result(n);
	for(int i = vs.size() - 1, k = 0; i >= 0; --i){
		if(!used[vs[i]]){
			scc_backward_dfs(vs[i], vs[i], rconn, used, result);
		}
	}
	return result;
}

/**
 *  @}
 */

}
}

