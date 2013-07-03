// AOJ 2512 - Ononokomachi's Edit War
#include <iostream>
#include <cctype>
#include "common/header.h"
#include "misc/alpha_beta.h"

typedef pair<ll, int> pli;

#define LEX_DEF(name) pli lex_ ## name (const char *s, int p)

LEX_DEF(or);
LEX_DEF(xor);
LEX_DEF(and);
LEX_DEF(addsub);
LEX_DEF(mul);
LEX_DEF(term);
LEX_DEF(number);

LEX_DEF(or){
	pli r = lex_xor(s, p);
	if(r.second < 0){ return pli(0, -1); }
	while(s[r.second] == '|'){
		pli q = lex_xor(s, r.second + 1);
		if(q.second < 0){ return pli(0, -1); }
		r.first |= q.first;
		r.second = q.second;
	}
	return r;
}
LEX_DEF(xor){
	pli r = lex_and(s, p);
	if(r.second < 0){ return pli(0, -1); }
	while(s[r.second] == '^'){
		pli q = lex_and(s, r.second + 1);
		if(q.second < 0){ return pli(0, -1); }
		r.first ^= q.first;
		r.second = q.second;
	}
	return r;
}
LEX_DEF(and){
	pli r = lex_addsub(s, p);
	if(r.second < 0){ return pli(0, -1); }
	while(s[r.second] == '&'){
		pli q = lex_addsub(s, r.second + 1);
		if(q.second < 0){ return pli(0, -1); }
		r.first &= q.first;
		r.second = q.second;
	}
	return r;
}
LEX_DEF(addsub){
	pli r = lex_mul(s, p);
	if(r.second < 0){ return pli(0, -1); }
	while(s[r.second] == '+' || s[r.second] == '-'){
		pli q = lex_mul(s, r.second + 1);
		if(q.second < 0){ return pli(0, -1); }
		if(s[r.second] == '+'){
			r.first += q.first;
		}else if(s[r.second] == '-'){
			r.first -= q.first;
		}
		r.second = q.second;
	}
	return r;
}
LEX_DEF(mul){
	pli r = lex_term(s, p);
	if(r.second < 0){ return pli(0, -1); }
	while(s[r.second] == '*'){
		pli q = lex_term(s, r.second + 1);
		if(q.second < 0){ return pli(0, -1); }
		r.first *= q.first;
		r.second = q.second;
	}
	return r;
}
LEX_DEF(term){
	pli r(0, -1);
	if(s[p] == '('){
		r = lex_or(s, p + 1);
		if(r.second < 0 || s[r.second] != ')'){ return pli(0, -1); }
		++r.second;
	}else if(isdigit(s[p])){
		r = lex_number(s, p);
		if(r.second < 0){ return pli(0, -1); }
	}
	return r;
}
LEX_DEF(number){
	if(s[p] == '0'){ return pli(0, -1); }
	pli r(0, p);
	while(isdigit(s[r.second])){
		r.first = (r.first * 10) + (s[r.second] - '0');
		++r.second;
	}
	return r;
}

struct EditState {
	typedef EditState SelfType;
	typedef ll EvalType;

	int turn;
	ll eval_value;
	string formula;

	EditState(int t = 0, ll v = 0, string f = string()) :
		turn(t), eval_value(v), formula(f)
	{ }

	bool my_turn() const { return turn == 0; }
	EvalType evaluate() const { return eval_value; }
	vector<SelfType> children() const {
		const char *CHARACTERS = "0123456789|^&+-*()";
		vector<SelfType> ret;
		if(formula.size() > 1){
			for(size_t i = 0; i < formula.size(); ++i){
				string modified(formula);
				modified.erase(i, 1);
				pli p = lex_or(modified.c_str(), 0);
				if(p.second == static_cast<int>(modified.size())){
					ret.push_back(EditState(1 - turn, p.first, modified));
				}
			}
		}
		for(size_t i = 0; i <= formula.size(); ++i){
			string modified(formula);
			modified.insert(i, " ");
			for(int j = 0; CHARACTERS[j] != '\0'; ++j){
				modified[i] = CHARACTERS[j];
				pli p = lex_or(modified.c_str(), 0);
				if(p.second == static_cast<int>(modified.size())){
					ret.push_back(EditState(1 - turn, p.first, modified));
				}
			}
		}
		return ret;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		int n;
		string expression;
		cin >> n >> expression;
		if(n == 0 && expression == "#"){ break; }
		pli exp_lex = lex_or(expression.c_str(), 0);
		EditState init(0, exp_lex.first, expression);
		n = 2 - (n % 2);
		ll answer = libcomp::misc::alpha_beta(n, init);
		cout << answer << endl;
	}
	return 0;
}

