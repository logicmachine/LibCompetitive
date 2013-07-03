/**
 *  @file misc/alpha_beta.h
 */
#pragma once
#include <vector>
#include <limits>
#include "common/header.h"

namespace libcomp {
namespace misc {

/**
 *  @defgroup alpha_beta Alpha-beta pruning
 *  @ingroup  misc
 *  @{
 */

/**
 *  @brief αβ法によるゲーム木探索で用いる状態型
 */
struct AlphaBetaStateSkelton {
	/// 自身の型
	typedef AlphaBetaStateSkelton SelfType;
	/// 評価値の型
	typedef int EvalType;

	/**
	 *  @brief 次に行動を行うプレイヤーの取得
	 *  @retval true   次に行動を行うプレイヤーが自分の場合
	 *  @retval false  次に行動を行うプレイヤーが相手の場合
	 */
	bool my_turn() const { return true; }

	/**
	 *  @brief 状態の評価値を取得する
	 *  @return 状態を評価した値
	 */
	EvalType evaluate() const { return 0; }

	/**
	 *  @brief 1手の行動でたどり着くことができる状態の取得
	 *  @return 1手行動を追加することでたどり着くことができる状態のリスト
	 */
	vector<SelfType> children() const { return vector<SelfType>(); }
};

/**
 *  @brief αβ法によるゲーム木探索
 *  @sa AlphaBetaStateSkelton
 *
 *  αβ法による枝刈りを行いつつゲーム木を探索する。
 *  自分は評価値を大きくしようとし、相手は評価値を小さくしようとする。
 *
 *  @tparam    State  状態を表す型
 *  @param[in] depth  探索の深さの最大値
 *  @param[in] state  根とする状態
 *  @param[in] alpha  関心のある範囲の下限
 *  @param[in] beta   関心のある範囲の上限
 *  @return    depth手先読みした場合のstateの評価値
 */
template <typename State>
typename State::EvalType alpha_beta(
	int depth, const State &state,
	typename State::EvalType alpha =
		-numeric_limits<typename State::EvalType>::max(),
	typename State::EvalType beta =
		numeric_limits<typename State::EvalType>::max())
{
	typedef typename State::EvalType EvalType;
	if(depth == 0){ return state.evaluate(); }
	vector<State> children = state.children();
	if(children.empty()){ return state.evaluate(); }
	if(state.my_turn()){
		for(size_t i = 0; i < children.size(); ++i){
			alpha = max(alpha, alpha_beta(
				depth - 1, children[i], alpha, beta));
			if(alpha >= beta){ return beta; }
		}
		return alpha;
	}else{
		for(size_t i = 0; i < children.size(); ++i){
			beta = min(beta, alpha_beta(
				depth - 1, children[i], alpha, beta));
			if(alpha >= beta){ return alpha; }
		}
		return beta;
	}
}

/**
 *  @}
 */

}
}

