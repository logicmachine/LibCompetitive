#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "common/header.h"
#include "misc/three_sat_pruning.h"

int c2c(char c){
	const int key = toupper(c) - 'A';
	return isupper(c) ? ~key : key;
}

int main(){
	using libcomp::misc::ThreeSatClause;
	using libcomp::misc::three_sat_pruning;
	ios_base::sync_with_stdio(false);
	while(true){
		int n;
		cin >> n;
		if(n == 0){ break; }
		vector<string> field(3);
		for(int i = 0; i < 3; ++i){ cin >> field[i]; }
		const int m = field[0].size();
		vector<ThreeSatClause> clauses;
		for(int i = 1; i < m; i += 3){
			ThreeSatClause c;
			c.count = 3;
			// 00 or 10 or 20
			c.conditions[0] = c2c(field[0][i]);
			c.conditions[1] = c2c(field[1][i]);
			c.conditions[2] = c2c(field[2][i]);
			clauses.push_back(c);
			// 00 or 10 or 21
			c.conditions[2] = c2c(field[2][i + 1]);
			clauses.push_back(c);
			// 00 or 11 or 20
			c.conditions[1] = c2c(field[1][i + 1]);
			c.conditions[2] = c2c(field[2][i]);
			clauses.push_back(c);
			// 00 or 11 or 21
			c.conditions[2] = c2c(field[2][i + 1]);
			clauses.push_back(c);
			// 01 or 10 or 20
			c.conditions[0] = c2c(field[0][i + 1]);
			c.conditions[1] = c2c(field[1][i]);
			c.conditions[2] = c2c(field[2][i]);
			clauses.push_back(c);
			// 01 or 10 or 21
			c.conditions[2] = c2c(field[2][i + 1]);
			clauses.push_back(c);
			// 01 or 11 or 20
			c.conditions[1] = c2c(field[1][i + 1]);
			c.conditions[2] = c2c(field[2][i]);
			clauses.push_back(c);
			// 01 or 11 or 21
			c.conditions[2] = c2c(field[2][i + 1]);
			clauses.push_back(c);
		}
		const ull s = three_sat_pruning(clauses);
		if(s == ~0ull){
			cout << -1 << endl;
			continue;
		}
		const int count = __builtin_popcountll(s);
		cout << count;
		for(int i = 0; i < 26; ++i){
			if(s & (1ull << i)){ cout << " " << static_cast<char>('A' + i); }
		}
		cout << endl;
	}
	return 0;
}

