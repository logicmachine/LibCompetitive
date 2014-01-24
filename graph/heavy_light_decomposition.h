/**
 *  @file graph/heavy_light_decomposition.h
 */
#pragma once
#include <vector>
#include <stack>
#include <utility>
#include "common/header.h"

namespace libcomp {
namespace graph {

/**
 *  @defgroup heavy_light_decomposition Heavy-light decomposition
 *  @ingroup  graph
 *  @{
 */

/**
 *  @brief Heavy-light decomposition
 */
class HeavyLightDecomposer {

public:
	/**
	 *  @brief パス同士の接続関係
	 */
	struct Connection {
		/// 親頂点のパス内位置
		int local_index;
		/// 子のパス番号
		int child_path;

		/**
		 *  @brief コンストラクタ
		 *  @param[in] li  親頂点のパス内位置
		 *  @param[in] cp  子のパス番号
		 */
		explicit Connection(int li = -1, int cp = -1) :
			local_index(li), child_path(cp)
		{ }
	};

private:
	typedef pair<int, int> pii;

	struct Path {
		int parent_vertex;
		vector<Connection> children;
		vector<int> vertices;
		int depth;
	};

	vector<Path> m_paths;
	vector<int> m_path_ids;
	vector<int> m_local_indices;

	template <typename EDGE_TYPE>
	vector<int> compute_subtree_size(
		const vector< vector<EDGE_TYPE> > &conn, int root) const
	{
		const int n = conn.size();
		vector<int> subtree_size(n);
		vector<bool> passed(n), gathered(n);
		stack<pii> count_stack;
		count_stack.push(pii(root, 0));
		while(!count_stack.empty()){
			const pii p = count_stack.top();
			count_stack.pop();
			const int u = p.first, i = p.second;
			if(i == 0){
				passed[u] = true;
				count_stack.push(pii(u, 1));
				for(int j = 0; j < conn[u].size(); ++j){
					const int v = conn[u][j].to;
					if(passed[v]){ continue; }
					count_stack.push(pii(v, 0));
				}
			}else{
				int sum = 1;
				gathered[u] = true;
				for(int j = 0; j < conn[u].size(); ++j){
					const int v = conn[u][j].to;
					if(!gathered[v]){ continue; }
					sum += subtree_size[v];
				}
				subtree_size[u] = sum;
			}
		}
		return subtree_size;
	}

public:
	/**
	 *  @brief デフォルトコンストラクタ
	 */
	HeavyLightDecomposer() :
		m_paths(0), m_path_ids(0), m_local_indices(0)
	{ }

	/**
	 *  @brief コンストラクタ
	 *
	 *  root を根とした木 conn を Heavy-light decomposition する。
	 *  計算量は \f$ \mathcal{O}(|V|) \f$。
	 *
	 *  @tparam    EDGE_TYPE  辺データの型。to を持つもの。
	 *  @param[in] conn       グラフデータ
	 *  @param[in] root       木の根となる頂点
	 */
	template <typename EDGE_TYPE>
	explicit HeavyLightDecomposer(
		const vector< vector<EDGE_TYPE> > &conn, int root = 0) :
		m_paths(0), m_path_ids(conn.size(), -1),
		m_local_indices(conn.size(), -1)
	{
		const int n = conn.size();
		const vector<int> subtree_size = compute_subtree_size(conn, root);
		stack<pii> decompose_stack;
		decompose_stack.push(pii(root, -1));
		while(!decompose_stack.empty()){
			const pii p = decompose_stack.top();
			decompose_stack.pop();
			const int parent_vertex = p.second;
			const int pid = m_paths.size();
			m_paths.push_back(Path());
			Path &path = m_paths.back();
			path.parent_vertex = parent_vertex;
			if(parent_vertex >= 0){
				const int parent_pid = m_path_ids[parent_vertex];
				const int parent_index = m_local_indices[parent_vertex];
				m_paths[parent_pid].children.push_back(
					Connection(parent_index, pid));
				path.depth = m_paths[parent_pid].depth + 1;
			}else{
				path.depth = 0;
			}
			int cur = p.first;
			while(cur >= 0){
				const int st_size = subtree_size[cur], threshold = st_size / 2;
				m_path_ids[cur] = pid;
				m_local_indices[cur] = path.vertices.size();
				path.vertices.push_back(cur);
				int heavy_edge = -1;
				for(int i = 0; i < conn[cur].size(); ++i){
					const int v = conn[cur][i].to;
					if(subtree_size[v] > subtree_size[cur]){ continue; }
					if(heavy_edge < 0 && subtree_size[v] >= threshold){
						heavy_edge = v;
					}else{
						decompose_stack.push(pii(v, cur));
					}
				}
				cur = heavy_edge;
			}
		}
	}

	/**
	 *  @brief  分解結果のパス数の取得
	 *  @return 分解された木に含まれる Heavy path の総数。
	 */
	int path_count() const { return m_paths.size(); }

	/**
	 *  @brief パスに含まれる頂点数の取得
	 *  @param[in] p  頂点数を取得したいパスのインデックス
	 *  @return    パス p に含まれる頂点の数
	 */
	int path_length(int p) const { return m_paths[p].vertices.size(); }

	/**
	 *  @brief パスから子に向かう接続関係の列挙
	 *  @param[in] p  接続関係を取得したいパスのインデックス
	 *  @return    パス p から子に向かう接続関係の集合
	 */
	const vector<Connection> &path_children(int p) const {
		return m_paths[p].children;
	}

	/**
	 *  @brief 根を含むパスからの距離の取得
	 *  @param[in] p  距離を取得したいパスのインデックス
	 *  @return    根を含むパスからパス p までの距離
	 */
	int path_depth(int p) const { return m_paths[p].depth; }

	/**
	 *  @brief パスの親となる頂点の取得
	 *  @param[in] p  親頂点を取得したいパスのインデックス
	 *  @return    パス p の親にあたる頂点の頂点番号。
	 *             パス p が根を含む場合は -1 を返す。
	 */
	int parent_vertex_id(int p) const {
		return m_paths[p].parent_vertex;
	}

	/**
	 *  @brief パスの親となるパスの取得
	 *  @param[in] p  親パスを取得したいパスのインデックス
	 *  @return    パス p の親にあたるパスのインデックス。
	 *             パス p が根を含む場合は -1 を返す。
	 */
	int parent_path_id(int p) const {
		if(m_paths[p].parent_vertex < 0){ return -1; }
		return m_path_ids[m_paths[p].parent_vertex];
	}

	/**
	 *  @brief パスの親となる頂点のパス内位置の取得
	 *  @param[in] p  位置を取得したいパスのインデックス
	 *  @return    パス p の親にあたる頂点のパス内位置。
	 *             パス p が根を含む場合は -1 を返す。
	 */
	int parent_local_index(int p) const {
		if(m_paths[p].parent_vertex < 0){ return -1; }
		return m_local_indices[m_paths[p].parent_vertex];
	}

	/**
	 *  @brief 頂点の属するパスの取得
	 *  @param[in] v  パスを取得したい頂点の番号
	 *  @return    頂点 v を含むパスのインデックス
	 */
	int path_id(int v) const { return m_path_ids[v]; }

	/**
	 *  @brief 頂点のパス内位置の取得
	 *  @param[in] v  位置を取得したい頂点の番号
	 *  @return    頂点 v を含むパス内での頂点 v の位置
	 */
	int local_index(int v) const { return m_local_indices[v]; }

	/**
	 *  @brief パス上の頂点の元グラフでの頂点番号の取得
	 *  @param[in] p  頂点番号を得たい頂点が属するパスのインデックス
	 *  @param[in] i  頂点番号を得たい頂点のパス内位置
	 *  @return    パス p の i 番目の頂点の頂点番号
	 */
	int vertex_id(int p, int i) const { return m_paths[p].vertices[i]; }

};

/**
 *  @}
 */

}
}

