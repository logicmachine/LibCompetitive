/**
 *  @file graph/edge.h
 */
#pragma once
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup graph libcomp::graph
 *  @{
 */

/**
 *  @brief 辺
 *
 *  不要な要素は適宜削って利用する。
 */
struct Edge {
	/// 反対端の頂点
	int to;
	/// 辺の重み
	ll weight;
	/// 辺の容量
	ll capacity;

	/**
	 *  @brief コンストラクタ
	 */
	explicit Edge(int to, ll weight = 0, ll capacity = 0) :
		to(to), weight(weight), capacity(capacity)
	{ }
};

/**
 *  @}
 */

}
}


