#include <gtest/gtest.h>
#include <cstring>
#include "string/suffix_array.cpp"
#include "../../utility/random.h"
#include "../../utility/stopwatch.h"

static string generate_random_string(int n){
	string s(n, ' ');
	for(int i = 0; i < n; ++i){
		s[i] = static_cast<char>(testtool::random() % (0x7f - 0x20) + 0x20);
	}
	return s;
}

TEST(StringSuffixArray, TestCorrectnessRandom){
	int N[] = { 10, 15, 16, 100, 254, 255, 256, 257 };
	int nN = sizeof(N) / sizeof(int);
	for(int i = 0; i < nN; ++i){
		int n = N[i];
		string s = generate_random_string(n);
		SuffixArray sa(s);
		ASSERT_EQ(n + 1, static_cast<int>(sa.size()));
		for(size_t j = 0; j + 1 < sa.size(); ++j){
			EXPECT_LT(strcmp(sa[j], sa[j + 1]), 0);
		}
	}
}

TEST(StringSuffixArray, TestCorrectnessRepeat){
	int N[] = { 10, 15, 16, 100, 254, 255, 256, 257 };
	int nN = sizeof(N) / sizeof(int);
	for(int i = 0; i < nN; ++i){
		int n = N[i];
		string s(n, 'a');
		SuffixArray sa(s);
		ASSERT_EQ(n + 1, static_cast<int>(sa.size()));
		for(size_t j = 0; j + 1 < sa.size(); ++j){
			EXPECT_LT(strcmp(sa[j], sa[j + 1]), 0);
		}
	}
}

TEST(StringSuffixArray, TestPerformance){
	testtool::StopWatch stopwatch;
	const int N = 50000;
	string s = generate_random_string(N);
	SuffixArray sa(s);
	ASSERT_LE(stopwatch.get(), 1000u);
}

