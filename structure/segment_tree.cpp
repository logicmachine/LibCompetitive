#include <vector>
#include <algorithm>
#include <functional>
#include <climits>

using namespace std;

template <typename T, T _Default, typename _Func>
class SegmentTree {
public:
	SegmentTree(int n, const _Func &func = _Func()) :
		m_func(func)
	{
		int m = 1;
		while(m < n){ m *= 2; }
		m_size = m;
		m_data.resize(m * 2 - 1);
		for(int i = m_size - 1; i < m_data.size(); ++i){ m_data[i] = _Default; }
		init();
	}
	template <typename _Iter>
	SegmentTree(_Iter begin, _Iter end, const _Func &func = _Func()) :
		m_func(func)
	{
		int n = distance(begin, end), m = 1;
		while(m < n){ m *= 2; }
		m_size = m;
		m_data.resize(m * 2 - 1);
		for(int i = m_size - 1; i < m_data.size(); ++i){
			m_data[i] = (begin == end) ? _Default : *(begin++);
		}
		init();
	}
	void update(int i, int x){
		i += m_size - 1;
		m_data[i] = x;
		while(i > 0){
			i = (i - 1) / 2;
			m_data[i] = m_func(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}
	int query(int a, int b){ return query(a, b, 0, 0, m_size); }
private:
	int query(int a, int b, int k, int l, int r){
		if(r <= a || b <= l){ return _Default; }
		if(a <= l && r <= b){ return m_data[k]; }
		int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return m_func(vl, vr);
	}
	void init(){
		for(int i = m_size - 2; i >= 0; --i){
			m_data[i] = m_func(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}

	vector<T> m_data;
	int m_size;
	_Func m_func;
};

#define SEGTREE_PTR_FUN(T, _Default) \
	SegmentTree< \
		T, _Default, \
		pointer_to_binary_function<const T &, const T &, const T &> >

#include <iostream>

int main(){
	int a, b, c;
	SEGTREE_PTR_FUN(int, INT_MAX) st(256, ptr_fun(min<int>));
	while(cin >> a >> b >> c){
		if(a == 0){
			st.update(b, c);
		}else{
			cout << st.query(b, c) << endl;
		}
	}
	return 0;
}

