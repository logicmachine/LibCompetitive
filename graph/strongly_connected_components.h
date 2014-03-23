/**
 *  @file graph/strongly_connected_components.h
 */
#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
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
	typedef pair<int, int> pii;
	const int n = conn.size();
	vector< vector<int> > rconn(n);
	for(int i = 0; i < conn.size(); ++i){
		for(int j = 0; j < conn[i].size(); ++j){
			rconn[conn[i][j].to].push_back(i);
		}
	}
	vector<int> used(n), vs;
	for(int i = 0; i < n; ++i){
		if(used[i]){ continue; }
		stack<pii> st;
		st.push(pii(i, 0));
		while(!st.empty()){
			const int v = st.top().first, j = st.top().second;
			st.pop();
			if(j == 0){ used[v] = 1; }
			if(j == conn[v].size()){
				vs.push_back(v);
			}else{
				st.push(pii(v, j + 1));
				if(!used[conn[v][j].to]){ st.push(pii(conn[v][j].to, 0)); }
			}
		}
	}
	vector<int> result(n, -1);
	for(int i = n - 1; i >= 0; --i){
		if(result[vs[i]] >= 0){ continue; }
		stack<pii> st;
		st.push(pii(vs[i], 0));
		while(!st.empty()){
			const int v = st.top().first, j = st.top().second;
			st.pop();
			if(j == 0){ result[v] = vs[i]; }
			if(j == rconn[v].size()){ continue; }
			st.push(pii(v, j + 1));
			if(result[rconn[v][j]] < 0){ st.push(pii(rconn[v][j], 0)); }
		}
	}
	return result;
}

/**
 *  @}
 */

}
}

