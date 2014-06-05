/**
 *  @file structure/segment_tree/min.h
 */
#pragma once
#include <vector>
#include <algorithm>
#include <limits>
#include "common/header.h"

namespace libcomp {
namespace structure {

/**
 *  @addtogroup segment_tree
 *  @{
 */

/**
 *  @brief  セグメント木による区間最小クエリ
 *  @tparam T  値の型
 */
template <typename T>
struct MinSegmentTreeTraits {
	/// 値型
	typedef T value_type;
	/// 各ノードのデフォルト値
	T default_value() const { return numeric_limits<T>::max(); }
	/// 二項演算を行う関数
	T operator()(const T &a, const T &b) const { return min(a, b); }
};

/**
 *  @}
 */

}
}

