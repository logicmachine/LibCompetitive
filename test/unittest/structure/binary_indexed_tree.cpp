#include <gtest/gtest.h>
#include "structure/binary_indexed_tree.h"
#include "../../utility/random.h"
#include "../../utility/stopwatch.h"

TEST(StructureBinaryIndexedTree, TestCorrectness){
	const int N = 100;
	vector<int> naive_vector(N);
	libcomp::structure::BinaryIndexedTree<int> bit(N);
	for(int i = 0; i < 1000; ++i){
		int p = testtool::random() % N;
		int v = static_cast<int>(testtool::random() & 0xffff) - 0x8000;
		naive_vector[p] += v;
		bit.add(p, v);
		int q = testtool::random() % (N + 1);
		int naive_answer = 0;
		for(int j = 0; j < q; ++j){ naive_answer += naive_vector[j]; }
		EXPECT_EQ(naive_answer, bit.sum(q));
	}
}

TEST(StructureBinaryIndexedTree, TestPerformance){
	testtool::StopWatch stopwatch;
	const int N = 100000;
	libcomp::structure::BinaryIndexedTree<int> bit(N);
	volatile int answer = 0; // avoiding optimization
	for(int i = 0; i < 100000; ++i){
		int p = testtool::random() % N;
		int v = static_cast<int>(testtool::random() & 0xffff) - 0x8000;
		bit.add(p, v);
		int q = testtool::random() % (N + 1);
		answer += bit.sum(q);
	}
	ASSERT_LE(stopwatch.get(), 500u);
}

