#include <gtest/gtest.h>
#include <functional>
#include <climits>
#include "misc/binary_search_integer.h"
#include "misc/binary_search_real.h"

TEST(MiscBinarySearchInteger, TestCorrectness){
	using libcomp::misc::binary_search;
	EXPECT_EQ(51, binary_search(10, 100, bind2nd(greater<int>(), 50)));
	EXPECT_EQ(51, binary_search(-100, 100, bind2nd(greater<int>(), 50)));
	EXPECT_EQ(10, binary_search(10, 100, bind2nd(greater<int>(), 0)));
	EXPECT_EQ(100, binary_search(10, 100, bind2nd(greater<int>(), 200)));
	EXPECT_EQ(1000, binary_search(100, INT_MAX, bind2nd(greater<int>(), 999)));
}

TEST(MiscBinarySearchReal, TestCorrectness){
	using libcomp::misc::binary_search;
	EXPECT_DOUBLE_EQ(
		50.0,
		binary_search(10.0, 100.0, bind2nd(greater<double>(), 50.0)));
	EXPECT_DOUBLE_EQ(
		50.0,
		binary_search(-100.0, 100.0, bind2nd(greater<double>(), 50.0)));
	EXPECT_DOUBLE_EQ(
		10.0,
		binary_search(10.0, 100.0, bind2nd(greater<double>(), 0.0)));
	EXPECT_DOUBLE_EQ(
		100.0,
		binary_search(10.0, 100.0, bind2nd(greater<double>(), 200.0)));
	EXPECT_DOUBLE_EQ(
		200.0,
		binary_search(10.0, 1e100, bind2nd(greater<double>(), 200.0)));
}

