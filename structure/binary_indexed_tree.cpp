#include <vector>

using namespace std;

template <typename T>
class BinaryIndexedTree {

private:
	vector<T> data;

public:
	BinaryIndexedTree(int N) : data(N + 1) { }
	// calculate sum of a[0, i)
	T sum(int i){
		T s = T();
		for(; i > 0; i -= i & -i){ s += data[i]; }
		return s;
	}
	// add x to a[i]
	void add(int i, const T &x){
		for(++i; i < data.size(); i += i & -i){ data[i] += x; }
	}

};

#include <iostream>

int main(){
	int n, m;
	cin >> n >> m;
	BinaryIndexedTree<int> bit(n);
	while(m--){
		int c, i, x;
		cin >> c >> i >> x;
		if(c == 0){
			cout << bit.sum(i) << endl;
		}else{
			bit.add(i, x);
		}
	}
	return 0;
}

