/**
 *  @file graph/topological_sort.h
 */
#pragma once
#include <vector>
#include <queue>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup topological_sort Topological sort
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief トポロジカルソート
 *
 *  グラフ中の各頂点のトポロジカル順序を求める。
 *  計算量は \f$ \mathcal{O}(|V| + |E|) \f$。
 *
 *  @tparam    EDGE_TYPE  辺データ型。to を持つもの。
 *  @param[in] conn       グラフデータ
 *  @return    トポロジカル順に並べた頂点番号の列。
 *             ソートできない場合は空の列。
 */
template <typename EDGE_TYPE>
vector<int> topological_sort(const vector< vector<EDGE_TYPE> > &conn){
	const int n = conn.size();
	vector<int> degrees(n);
	for(int u = 0; u < n; ++u){
		for(int i = 0; i < conn[u].size(); ++i){
			const int v = conn[u][i].to;
			++degrees[v];
		}
	}
	queue<int> q;
	for(int v = 0; v < n; ++v){
		if(degrees[v] == 0){ q.push(v); }
	}
	vector<int> result;
	result.reserve(n);
	while(!q.empty()){
		const int u = q.front();
		q.pop();
		result.push_back(u);
		for(int i = 0; i < conn[u].size(); ++i){
			const int v = conn[u][i].to;
			if(--degrees[v] == 0){ q.push(v); }
		}
	}
	if(result.size() != n){ return vector<int>(); }
	return result;
}

/**
 *  @}
 */

}
}

