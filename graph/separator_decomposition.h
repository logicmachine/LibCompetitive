/**
 *  @file graph/separator_decomposition.h
 */
#pragma once
#include <vector>
#include <stack>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup separator_decomposition Separator decomposition
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief 木の重心分解を行う際に疑似スタックフレームとして使用する型
 */
struct SeparatorDecompositionRecurFrame {
	/// 処理する部分木に含まれる任意の頂点
	int root;
	/// 処理する部分木に含まれる頂点の数
	int count;
	/// 処理する部分木の重心の親となる頂点
	int parent;

	/**
	 *  @brief コンストラクタ
	 *  @param[in] r  処理する部分木に含まれる任意の頂点
	 *  @param[in] c  処理する部分木に含まれる頂点の数
	 *  @param[in] p   処理する部分木の重心の親となる頂点
	 */
	explicit SeparatorDecompositionRecurFrame(
		int r = 0, int c = 0, int p = 0) :
		root(r), count(c), parent(p)
	{ }
};

/**
 *  @brief 木の重心分解を行う際に疑似スタックフレームとして使用する型
 */
struct SeparatorDecompositionDFSFrame {
	/// 処理対象となっている頂点
	int u;
	/// 処理した辺の数
	int i;
	/// 直前に通過した頂点
	int p;

	/**
	 *  @brief コンストラクタ
	 *  @param[in] vertex  処理対象となっている頂点
	 *  @param[in] index   処理した辺の数
	 *  @param[in] parent  直前に通過した頂点
	 */
	explicit SeparatorDecompositionDFSFrame(
		int vertex = 0, int index = 0, int parent = 0) :
		u(vertex), i(index), p(parent)
	{ }
};

/**
 *  @brief 木の重心分解 (Separator decomposition, Centroid decomposition)
 *
 *  計算量は \f$ \mathcal{O}(|V| \log{|V|}) \f$。
 *
 *  @tparam    EDGE_TYPE  辺データ型。to を持つもの。
 *  @param[in] conn       グラフデータ。木であること。
 *  @return    分解結果となる木。a[v]が頂点vの親となる。
 *             また、根をrとしたときa[r]==rとなる。
 */
template <typename EDGE_TYPE>
vector<int> separator_decomposition(const vector< vector<EDGE_TYPE> > &conn){
	const int n = conn.size();
	vector<bool> picked(n);
	vector<int> num_children(n), result(n);
	stack<SeparatorDecompositionRecurFrame> recur_stack;
	recur_stack.push(SeparatorDecompositionRecurFrame(0, n, -1));
	while(!recur_stack.empty()){
		const SeparatorDecompositionRecurFrame rf = recur_stack.top();
		const int threshold = rf.count / 2;
		recur_stack.pop();
		int separator = rf.root;
		stack<SeparatorDecompositionDFSFrame> dfs_stack;
		dfs_stack.push(SeparatorDecompositionDFSFrame(rf.root, 0, rf.root));
		while(!dfs_stack.empty()){
			SeparatorDecompositionDFSFrame df = dfs_stack.top();
			dfs_stack.pop();
			if(static_cast<size_t>(df.i) >= conn[df.u].size()){
				num_children[df.u] = 1;
				for(size_t i  = 0; i < conn[df.u].size(); ++i){
					const int v = conn[df.u][i].to;
					if(picked[v] || v == df.p){ continue; }
					num_children[df.u] += num_children[v];
				}
				if(num_children[df.u] > threshold){
					separator = df.u;
					num_children[df.p] =
						rf.count - num_children[df.u];
					break;
				}
			}else{
				dfs_stack.push(
					SeparatorDecompositionDFSFrame(df.u, df.i + 1, df.p));
				const int v = conn[df.u][df.i].to;
				if(!picked[v] && v != df.p){
					dfs_stack.push(
						SeparatorDecompositionDFSFrame(v, 0, df.u));
				}
			}
		}
		result[separator] = (rf.parent < 0 ? separator : rf.parent);
		picked[separator] = true;
		for(size_t i = 0; i < conn[separator].size(); ++i){
			const int v = conn[separator][i].to;
			if(picked[v]){ continue; }
			recur_stack.push(SeparatorDecompositionRecurFrame(
				v, num_children[v], separator));
		}
	}
	return result;
}

/**
 *  @}
 */

}
}

