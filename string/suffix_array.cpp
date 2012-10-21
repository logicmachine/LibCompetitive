#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class SuffixArray {

private:
	struct FirstComparator {
		bool operator()(const char *a, const char *b){
			unsigned char ua = static_cast<unsigned char>(*a);
			unsigned char ub = static_cast<unsigned char>(*b);
			return ua < ub;
		}
	};

	string m_string;
	vector<int> m_pos;

public:
	explicit SuffixArray(const string &s = string()) :
		m_string(s), m_pos(s.size() + 1)
	{
		int n = s.size() + 1;
		const char *head = m_string.c_str();
		vector<const char *> ptrs(n);
		for(int i = 0; i < n; ++i){ ptrs[i] = head + i; }
		sort(ptrs.begin(), ptrs.end(), FirstComparator());
		vector<int> group(n);
		group[ptrs.back() - head] = n - 1;
		for(int i = n - 2; i >= 0; --i){
			int pp = ptrs[i + 1] - head, pc = ptrs[i] - head;
			group[pc] = (*(ptrs[i]) == *(ptrs[i + 1])) ? group[pp] : i;
		}
		vector<int> next_group(n);
		vector< pair<int, const char *> > buffer;
		buffer.reserve(n);
		for(int step = 1; step < n; step <<= 1){
			for(int begin = 0; begin < n; ){
				int end = begin;
				buffer.clear();
				for(; end < n; ++end){
					int pb = ptrs[begin] - head;
					int pe = ptrs[end] - head;
					if(group[pb] != group[pe]){ break; }
					buffer.push_back(make_pair(group[pe + step], ptrs[end]));
				}
				sort(buffer.begin(), buffer.end());
				next_group[buffer.back().second - head] = end - 1;
				ptrs[end - 1] = buffer.back().second;
				for(int i = end - begin - 2; i >= 0; --i){
					int pp = buffer[i + 1].second - head;
					int pc = buffer[i].second - head;
					ptrs[i + begin] = buffer[i].second;
					if(buffer[i].first == buffer[i + 1].first){
						next_group[pc] = next_group[pp];
					}else{
						next_group[pc] = i + begin;
					}
				}
				begin = end;
			}
			group.swap(next_group);
		}
		for(int i = 0; i < n; ++i){ m_pos[i] = ptrs[i] - head; }
	}

	const string &str() const { return m_string; }
	size_t size() const { return m_pos.size(); }
	int position(int i) const { return m_pos[i]; }
	const char *operator[](int i) const {
		return m_string.c_str() + m_pos[i];
	}

};

