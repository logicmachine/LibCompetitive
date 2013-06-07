#include <gtest/gtest.h>
#include "structure/segment_tree.cpp"
#include "../../utility/random.h"
#include "../../utility/stopwatch.h"
#include <climits>

TEST(StructureSegmentTree, TestCorrectness){
	const int N = 100;
	vector<int> naive_vector(N);
	SegmentTree< int, INT_MIN, MaxFuncObject<int> > st_max(N);
	for(int i = 0; i < 1000; ++i){
		int p = testtool::random() % N;
		int v = static_cast<int>(testtool::random() & 0xffff) - 0x8000;
		naive_vector[p] = v;
		st_max.update(p, v);
		int a = testtool::random() % (N + 1);
		int b = testtool::random() % (N + 1);
		if(a < b){ swap(a, b); }
		int naive_answer = INT_MIN;
		for(int j = a; j < b; ++j){
			naive_answer = max(naive_answer, naive_vector[j]);
		}
		EXPECT_EQ(naive_answer, st_max.query(a, b));
	}
}

TEST(StructureSegmentTree, TestPerformance){
	testtool::StopWatch stopwatch;
	const int N = 100000;
	SegmentTree< int, INT_MIN, MaxFuncObject<int> > st_max(N);
	volatile int answer = 0; // avoiding optimization
	for(int i = 0; i < 100000; ++i){
		int p = testtool::random() % N;
		int v = static_cast<int>(testtool::random() & 0xffff) - 0x8000;
		st_max.update(p, v);
		int a = testtool::random() % (N + 1);
		int b = testtool::random() % (N + 1);
		if(a < b){ swap(a, b); }
		answer += st_max.query(a, b);
	}
	ASSERT_LE(stopwatch.get(), 500);
}

