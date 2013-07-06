/**
 *  @file geometry/essential/common.h
 */
#pragma once
#include <cmath>
#include "common/header.h"

namespace libcomp {
namespace geometry {

/**
 *  @defgroup common Common
 *  @ingroup  geometry
 *  @{
 */

/**
 *  @brief 許容誤差
 */
const double EPS = 1e-9;

/**
 *  @brief 誤差を許容する比較 (実数)
 *
 *  @param[in] a      比較する数値
 *  @param[in] b      比較する数値
 *  @retval    true   aとbの差の絶対値がEPS未満
 *  @retval    false  aとbの差の絶対値がEPS以上
 */
bool tolerant_eq(double a, double b){ return abs(a - b) < EPS; }

/**
 *  @}
 */

}
}

