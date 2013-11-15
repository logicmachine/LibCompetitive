// AOJ 2257 - Sakura Poetry
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cstring>
#include "common/header.h"
#include "string/aho_corasick.h"

const int MOD = 1000000007;

map<int, int> dp[21][501][2];

int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		int N, M, K;
		cin >> N >> M >> K;
		if(N == 0 && M == 0 && K == 0){ break; }
		vector<int> next_words[501];
		map<string, int> word_map;
		vector<string> words(1);
		word_map.insert(pair<string, int>("", 0));
		for(int i = 0; i < N; ++i){
			string from, to;
			cin >> from >> to;
			int from_index = 0, to_index = 0;
			if(word_map.find(from) != word_map.end()){
				from_index = word_map[from];
			}else{
				from_index = word_map.size();
				word_map[from] = from_index;
				words.push_back(from);
				next_words[0].push_back(from_index);
			}
			if(word_map.find(to) != word_map.end()){
				to_index = word_map[to];
			}else{
				to_index = word_map.size();
				word_map[to] = to_index;
				words.push_back(to);
				next_words[0].push_back(to_index);
			}
			next_words[from_index].push_back(to_index);
		}
		vector<string> season_words(K);
		for(int i = 0; i < K; ++i){ cin >> season_words[i]; }
		libcomp::string::AhoCorasick ac(season_words);
		int state_num = ac.size();
		for(int i = 0; i < 21; ++i){
			for(int j = 0; j < 501; ++j){
				for(int k = 0; k < 2; ++k){ dp[i][j][k].clear(); }
			}
		}
		dp[0][0][0][0] = 1;
		vector<int> result(K);
		for(int i = 0; i < M; ++i){
			for(int j = 0; j < words.size(); ++j){
				for(int k = 0; k < 2; ++k){
					for(
						map<int, int>::iterator it = dp[i % 21][j][k].begin();
						it != dp[i % 21][j][k].end(); ++it)
					{
						for(int n = 0; n < next_words[j].size(); ++n){
							int next = next_words[j][n];
							string &word = words[next];
							if(i + word.size() > M){ continue; }
							fill(result.begin(), result.end(), 0);
							int s = ac.match(word, result, it->first);
							int m = k + accumulate(result.begin(), result.end(), 0);
							if(m >= 2){ continue; }
							dp[(i + word.size()) % 21][next][m][s] += it->second;
							dp[(i + word.size()) % 21][next][m][s] %= MOD;
						}
					}
					dp[i % 21][j][k].clear();
				}
			}
		}
		int answer = 0;
		for(int i = 0; i < words.size(); ++i){
			for(int j = 0; j < state_num; ++j){
				answer += dp[M % 21][i][1][j];
				answer %= MOD;
			}
		}
		cout << answer << endl;
	}
	return 0;
}

