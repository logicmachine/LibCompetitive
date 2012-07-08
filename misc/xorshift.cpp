using namespace std;

unsigned int xorshift(){
	static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
	unsigned int t = (x ^ (x << 11));
	x = y; y = z; z = w;
	return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

#include <iostream>

int main(){
	for(int i = 0; i < 20; ++i){ cout << xorshift() << endl; }
	return 0;
}

