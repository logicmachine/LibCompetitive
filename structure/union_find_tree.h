/**
 *  @file structure/union_find_tree.h
 */
#pragma once
#include <vector>
#include "common/header.h"

namespace libcomp {
namespace structure {

/**
 *  @defgroup union_find_tree Union-find tree
 *  @ingroup  structure
 *  @{
 */

/**
 *  @brief Union-Find木
 */
class UnionFindTree {

private:
	vector<int> parent;
	vector<int> rank;

public:
	/**
	 *  @brief コンストラクタ
	 *
	 *  全要素が独立な状態でUnion-Find木を初期化する。
	 *
	 *  @param[in] n  Union-Find木の要素数
	 */
	explicit UnionFindTree(int n = 0) :
		parent(n), rank(n)
	{
		for(int i = 0; i < n; ++i){ parent[i] = i; }
	}

	/**
	 *  @brief 要素の属する集合のインデックスを取得
	 *
	 *  要素xの属している集合を示す値を取得する
	 *  計算量は \f$ \mathcal{O}(\alpha(n)) \f$。
	 *
	 *  @param[in] x  対象とする要素のインデックス
	 *  @return   要素xが属する集合を示すインデックス
	 */
	int find(int x){
		if(parent[x] == x){ return x; }
		parent[x] = find(parent[x]);
		return parent[x];
	}

	/**
	 *  @brief 2つの集合を併合する
	 *
	 *  要素xの属する集合と要素yの属する集合を併合する。
	 *  計算量は \f$ \mathcal{O}(\alpha(n)) \f$。
	 *
	 *  @param[in] x  片方の集合に含まれる要素
	 *  @param[in] y  他方の集合に含まれる要素
	 *  @return    併合後の集合を示すインデックス
	 */
	int unite(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y){ return x; }
		if(rank[x] < rank[y]){
			parent[x] = y;
			return y;
		}else if(rank[x] > rank[y]){
			parent[y] = x;
			return x;
		}else{
			parent[y] = x;
			++rank[x];
			return x;
		}
	}

	/**
	 *  @brief 2つの要素が同じ集合に属しているかの判定
	 *
	 *  要素xと要素yが同じ集合に属しているかを判定する。
	 *  計算量は \f$ \mathcal{O}(\alpha(n)) \f$。
	 *
	 *  @param[in] x      片方の要素
	 *  @param[in] y      他方の要素
	 *  @retval    true   xとyが同じ集合に属している
	 *  @retval    false  xとyが同じ集合に属していない
	 */
	bool same(int x, int y){
		return find(x) == find(y);
	}

};

/**
 *  @}
 */

}
}

