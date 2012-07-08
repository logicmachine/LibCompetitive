#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Matcher {
	struct PMA {
		int next[256];
		vector<int> accept;
		PMA(){ fill(next, next + 256, -1); }
	};
	vector<PMA> states;

public:
	Matcher(const vector<string> &patterns){
		states.push_back(PMA());
		for(int i = 0; i < patterns.size(); ++i){
			int cur = 0;
			for(size_t j = 0; j < patterns[i].size(); ++j){
				char c = patterns[i][j];
				if(states[cur].next[c] < 0){
					states[cur].next[c] = static_cast<int>(states.size());
					states.push_back(PMA());
				}
				cur = states[cur].next[c];
			}
			states[cur].accept.push_back(i);
		}
		queue<int> q;
		for(int c = 1; c < 256; ++c){
			if(states[0].next[c] >= 0){
				states[states[0].next[c]].next[0] = 0;
				q.push(states[0].next[c]);
			}else{
				states[0].next[c] = 0;
			}
		}
		while(!q.empty()){
			int t = q.front();
			q.pop();
			for(int c = 1; c < 256; ++c){
				if(states[t].next[c] >= 0){
					q.push(states[t].next[c]);
					int r = states[t].next[0];
					while(states[r].next[c] < 0){ r = states[r].next[0]; }
					states[states[t].next[c]].next[0] = states[r].next[c];
				}
			}
		}
		for(int i = 0; i < patterns.size(); ++i){
			const string &pat = patterns[i];
			for(int j = 1; j < states.size(); ++j){
				int current = j, k = 0;
				for(; k < pat.size(); ++k){
					if(states[current].next[pat[k]] < 0){ break; }
					current = states[current].next[pat[k]];
				}
				if(k == pat.size()){ states[current].accept.push_back(i); }
			}
		}
	}
	int match(const string &str, vector<int> &result, int state = 0){
		for(size_t i = 0; i < str.size(); ++i){
			char c = str[i];
			while(states[state].next[c] < 0){ state = states[state].next[0]; }
			state = states[state].next[c];
			for(size_t j = 0; j < states[state].accept.size(); ++j){
				++(result[states[state].accept[j]]);
			}
		}
		return state;
	}
	int stateNum() const { return static_cast<int>(states.size()); }
};

int main(){
	int n, m;
	cin >> n >> m;
	vector<string> patterns(n);
	for(int i = 0; i < n; ++i){ cin >> patterns[i]; }
	Matcher matcher(patterns);
	for(int i = 0; i < m; ++i){
		string input;
		cin >> input;
		vector<int> result(n);
		cout << matcher.match(input, result) << " { ";
		for(int j = 0; j < n; ++j){ cout << result[j] << " "; }
		cout << "}" << endl;
	}
	return 0;
}

