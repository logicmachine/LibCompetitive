#include <gtest/gtest.h>
#include "math/mod_inverse.cpp"
#include "../../utility/random.h"

TEST(MathModInverseTest, Randomized){
	ll primes[] = { 65521, 1000000007, 2147483647 };
	int num_primes = sizeof(primes) / sizeof(ll);
	for(int i = 0; i < num_primes; ++i){
		ll mod = primes[i];
		for(int j = 0; j < 10000; ++j){
			ll x = testtool::random() % (mod - 1) + 1;
			ll y = mod_inverse(x, mod);
			EXPECT_EQ(1, x * y % mod) << "a=" << x << ", m=" << mod;
		}
	}
}
