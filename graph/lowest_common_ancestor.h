/**
 *  @file graph/lowest_common_ancestor.h
 */
#pragma once
#include <vector>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup lowest_common_ancestor Lowest Common Ancestor
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 最小共通祖先クエリ処理
 */
class LowestCommonAncestor {

private:
	vector<int> depth_table;
	vector< vector<int> > double_table;

	template <typename EDGE_TYPE>
	void build_tables(
		int v, vector<int> &st, const vector< vector<EDGE_TYPE> > &conn)
	{
		if(depth_table[v] >= 0){ return; }
		const int m = double_table[v].size();
		for(int i = 0, j = 1; i < m && j <= st.size(); ++i, j += j){
			double_table[v][i] = st[st.size() - j];
		}
		depth_table[v] = st.size();
		st.push_back(v);
		for(int i = 0; i < conn[v].size(); ++i){
			build_tables(conn[v][i].to, st, conn);
		}
		st.pop_back();
	}

public:
	/**
	 *  @brief デフォルトコンストラクタ
	 */
	LowestCommonAncestor() : depth_table(), double_table() { }

	/**
	 *  @brief コンストラクタ
	 *
	 *  クエリ処理に必要なテーブルを求める。
	 *  計算量は \f$ \mathcal{O}(|V| \log |V|) \f$。
	 *
	 *  @tparam    EDGE_TYPE  辺データ型。to を持つもの。
	 *  @param[in] root       木の根となる頂点の番号。
	 *  @param[in] conn       グラフデータ。木であること。
	 */
	template <typename EDGE_TYPE>
	LowestCommonAncestor(
		int root, const vector< vector<EDGE_TYPE> > &conn) :
		depth_table(), double_table()
	{
		const int n = conn.size();
		const int m = 32 - __builtin_clz(n);
		depth_table.resize(n, -1);
		double_table.resize(n, vector<int>(m, -1));
		vector<int> st;
		build_tables(root, st, conn);
	}

	/**
	 *  @brief 最近共通祖先を求める
	 *
	 *  頂点 a, b の最近共通祖先を求める。
	 *  計算量は \f$ \mathcal{O}(\log |V|) \f$。
	 *
	 *  @param[in] a  頂点番号。
	 *  @param[in] b  頂点番号。
	 *  @return    a, b の最近共通先祖の頂点番号。
	 */
	int query(int a, int b) const {
		const int m = double_table[0].size();
		if(depth_table[a] < depth_table[b]){ swap(a, b); }
		for(int i = m - 1; i >= 0; --i){
			if(depth_table[a] - (1 << i) >= depth_table[b]){
				a = double_table[a][i];
			}
		}
		if(a == b){ return a; }
		for(int i = m - 1; i >= 0; --i){
			if(double_table[a][i] != double_table[b][i]){
				a = double_table[a][i];
				b = double_table[b][i];
			}
		}
		return double_table[a][0];
	}

	/**
	 *  @brief 頂点の根からの距離を求める
	 *
	 *  頂点 v の根からの距離を求める。
	 *  計算量は \f$ \mathcal{O}(1) \f$。
	 *
	 *  @param[in] v  頂点番号。
	 *  @return    v の根からの距離。
	 */
	int get_depth(int v) const {
		return depth_table[v];
	}

};

}
}

