/**
 *  @file misc/three_sat_pruning.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include "common/header.h"

namespace libcomp {
namespace misc {

/**
 *  @defgroup three_sat_pruning 3-SAT (pruning-based solver)
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief 3-SATの条件式の節
 */
struct ThreeSatClause {
	/// 節に含まれる変数の数
	int count;
	/// ORで繋がれる変数の集合 (Aの否定には~Aを使用する)
	int conditions[3];

	/**
	 *  @brief 比較演算子 (equals)
	 *
	 *  内部でuniqueを使用するために定義。
	 *  three_sat_pruning外からの使用は考慮していないので注意。
	 *
	 *  @param[in] t  比較対象のオブジェクト
	 *  @returns   (*this) == t であればtrue、そうでなければfalse。
	 */
	bool operator==(const ThreeSatClause &t) const {
		if(count != t.count){ return false; }
		for(int i = 0; i < count; ++i){
			if(conditions[i] != t.conditions[i]){ return false; }
		}
		return true;
	}
	/**
	 *  @brief 比較演算子 (less than)
	 *
	 *  内部でuniqueを使用するために定義。
	 *  three_sat_pruning外からの使用は考慮していないので注意。
	 *
	 *  @param[in] t  比較対象のオブジェクト
	 *  @returns   (*this) < t であればtrue、そうでなければfalse。
	 */
	bool operator<(const ThreeSatClause &t) const {
		if(count < t.count){ return true; }
		if(count > t.count){ return false; }
		for(int i = 0; i < count; ++i){
			if(conditions[i] < t.conditions[i]){ return true; }
			if(conditions[i] > t.conditions[i]){ return false; }
		}
		return false;
	}
};

/**
 *  @brief 枝刈りを用いた3-SATソルバ
 *
 *  枝刈りを用いて決定的に3-SATを解く。
 *  計算量は \f$ \mathcal{O}(1.84^n) \f$ (nは条件変数の数) よりは小さいはず。
 *
 *  詳細はICPC JAG模擬地区予選2013 J問題の解説を参照。
 *
 *  @param[in] clauses  条件式を示す節の集合
 *  @return    見つかった解を示すビット集合。解なしの場合は~0ullを返す。
 */
ull three_sat_pruning(vector<ThreeSatClause> clauses){
	int num_variables = 0;
	for(size_t i = 0; i < clauses.size(); ++i){
		ThreeSatClause &clause = clauses[i];
		sort(clause.conditions, clause.conditions + clause.count);
		clause.count =
			unique(clause.conditions, clause.conditions + clause.count) -
			clause.conditions;
		for(int j = 0; j < clause.count; ++j){
			const int c = clause.conditions[j];
			num_variables = max(num_variables, max(c, ~c) + 1);
		}
	}
	for(size_t i = 0; i < clauses.size(); ++i){
		ThreeSatClause &clause = clauses[i];
		ull positive = 0, negative = 0;
		for(int j = 0; j < clause.count; ++j){
			const int c = clause.conditions[j];
			if(c >= 0){
				positive |= (1ull << c);
			}else{
				negative |= (1ull << ~c);
			}
		}
		int k = 0;
		if((positive & negative) == 0){
			for(int j = 0; j < clause.count; ++j){
				const int c = clause.conditions[j];
				if(c >= 0){
					if((negative & (1ull << c)) == 0){
						clause.conditions[k++] = c;
					}
				}else{
					if((positive & (1ull << ~c)) == 0){
						clause.conditions[k++] = c;
					}
				}
			}
		}
		clause.count = k;
	}
	sort(clauses.begin(), clauses.end());
	clauses.erase(unique(clauses.begin(), clauses.end()), clauses.end());
	size_t m = 0;
	for(size_t i = 0; i < clauses.size(); ++i){
		if(clauses[i].count != 0){ clauses[m++] = clauses[i]; }
	}
	clauses.resize(m);

	struct {
		ull operator()(
			size_t i, const vector<ThreeSatClause> &clauses,
			ull decided = 0, ull current = 0) const
		{
			if(i == clauses.size()){ return current; }
			const ThreeSatClause &clause = clauses[i];
			for(int j = 0; j < clause.count; ++j){
				const int c = clause.conditions[j];
				const int key = max(c, ~c);
				const int value = ((current & (1ull << key)) != 0 ? 1 : 0);
				const int flag = (key == c ? 1 : 0);
				if((decided & (1ull << key)) && flag == value){
					return (*this)(i + 1, clauses, decided, current);
				}
			}
			for(int j = 0; j < clause.count; ++j){
				const int c = clause.conditions[j];
				const int key = max(c, ~c);
				const ull flag = (key == c ? 1 : 0);
				if((decided & (1ull << key)) == 0){
					decided |= (1ull << key);
					const ull p = (*this)(
						i + 1, clauses, decided, current | (flag << key));
					if(p != ~0ull){ return p; }
					current |= ((1 - flag) << key);
				}
			}
			return ~0ull;
		}
	} solve_recur;
	return solve_recur(0, clauses);
}

/**
 *  @}
 */

}
}

