#include <gtest/gtest.h>
#include <cstring>
#include "string/longest_common_prefix.h"
#include "../../utility/random.h"
#include "../../utility/stopwatch.h"

using libcomp::string::SuffixArray;

static string generate_random_string(int n){
	string s(n, ' ');
	for(int i = 0; i < n; ++i){
		s[i] = static_cast<char>(testtool::random() % (0x7f - 0x20) + 0x20);
	}
	return s;
}

TEST(StringLongestCommonPrefix, TestCorrectnessRandom){
	int N[] = { 10, 15, 16, 100, 254, 255, 256, 257 };
	int nN = sizeof(N) / sizeof(int);
	for(int i = 0; i < nN; ++i){
		int n = N[i];
		string s = generate_random_string(n);
		SuffixArray sa(s);
		vector<int> lcp = libcomp::string::longest_common_prefix(sa);
		ASSERT_EQ(n, static_cast<int>(lcp.size()));
		for(size_t j = 0; j < lcp.size(); ++j){
			int length = 0;
			while(sa[j][length] == sa[j + 1][length]){ ++length; }
			EXPECT_EQ(length, lcp[j]);
		}
	}
}

TEST(StringLongestCommonPrefix, TestCorrectnessRepeat){
	int N[] = { 10, 15, 16, 100, 254, 255, 256, 257 };
	int nN = sizeof(N) / sizeof(int);
	for(int i = 0; i < nN; ++i){
		int n = N[i];
		string s(n, 'a');
		SuffixArray sa(s);
		vector<int> lcp = libcomp::string::longest_common_prefix(sa);
		ASSERT_EQ(n, static_cast<int>(lcp.size()));
		for(size_t j = 0; j < lcp.size(); ++j){
			int length = 0;
			while(sa[j][length] == sa[j + 1][length]){ ++length; }
			EXPECT_EQ(length, lcp[j]);
		}
	}
}

TEST(StringLongestCommonPrefix, TestPerformance){
	const int N = 50000;
	string s = generate_random_string(N);
	SuffixArray sa(s);
	testtool::StopWatch stopwatch;
	vector<int> lcp = libcomp::string::longest_common_prefix(sa);
	ASSERT_LE(stopwatch.get(), 500u);
}

