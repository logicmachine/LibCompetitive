#include <vector>
#include <algorithm>

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
		fill(m_data.begin() + m_size - 1, m_data.end(), _Default);
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
	void update(int i, const T &x){
		i += m_size - 1;
		m_data[i] = x;
		while(i > 0){
			i = (i - 1) / 2;
			m_data[i] = m_func(m_data[i * 2 + 1], m_data[i * 2 + 2]);
		}
	}
	T query(int a, int b){ return query(a, b, 0, 0, m_size); }

private:
	T query(int a, int b, int k, int l, int r){
		if(r <= a || b <= l){ return _Default; }
		if(a <= l && r <= b){ return m_data[k]; }
		T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
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

template <typename T>
struct MinFuncObject {
	T operator()(const T &a, const T &b) const { return min(a, b); }
};

template <typename T>
struct MaxFuncObject {
	T operator()(const T &a, const T &b) const { return max(a, b); }
};

