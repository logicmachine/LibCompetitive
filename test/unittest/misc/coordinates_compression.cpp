#include <gtest/gtest.h>
#include "misc/coordinates_compression.cpp"

TEST(MiscCoordinatesCompression, TestCorrectness){
	int a0[] = { -47, -19,   9,  76, -27,  65, -74,   9, -41,  76 };
	int b0[] = {   1,   4,   5,   7,   3,   6,   0,   5,   2,   7 };
	int n0 = sizeof(a0) / sizeof(int);
	coordinates_compression(a0, a0 + n0, a0);
	for(int i = 0; i < n0; ++i){ EXPECT_EQ(b0[i], a0[i]); }

	double a1[] = { -47, -19,   9,  76, -27,  65, -74,   9, -41,  76 };
	int    b1[] = {   1,   4,   5,   7,   3,   6,   0,   5,   2,   7 };
	int    c1[] = {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	int    n1 = sizeof(a1) / sizeof(double);
	coordinates_compression(a1, a1 + n1, c1);
	for(int i = 0; i < n1; ++i){ EXPECT_EQ(b1[i], c1[i]); }
}

