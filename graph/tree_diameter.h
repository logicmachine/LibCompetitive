/**
 *  @file graph/tree_diameter.h
 */
#pragma once
#include <functional>
#include <utility>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup tree_diaeter Diameter of tree
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 木の直径
 *
 *  計算量は \f$ \mathcal{O}(|E|) \f$。
 *
 *  @tparam    EDGE_TYPE  辺データ型。to を持つもの。
 *  @param[in] conn       グラフデータ
 *  @param[in] root       木の中の頂点
 *  @return    rootを含む木の直径
 */
template <typename EDGE_TYPE>
inline int tree_diameter(
	const vector< vector<EDGE_TYPE> > &conn, int root = 0)
{
	typedef pair<int, int> pii;
	function<pii(int, int)> recur;
	recur = [&](int u, int p) -> pii {
		pii r(0, u);
		for(int i = 0; i < conn[u].size(); ++i){
			const int v = conn[u][i].to;
			if(v == p){ continue; }
			pii t = recur(v, u);
			++t.first;
			r = max(r, t);
		}
		return r;
	};
	const pii r = recur(root, -1);
	const pii t = recur(r.second, -1);
	return t.first;
}

/**
 *  @}
 */

}
}

