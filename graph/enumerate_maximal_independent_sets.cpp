#include <vector>

using namespace std;
typedef long long ll;

template <typename _Func>
void enumerate_maximal_independent_sets_recur(
	const vector<ll> &conn, const vector<ll> &iconn, _Func &func,
	int i = 0, ll picked = 0, ll eliminated = 0)
{
	int n = conn.size();
	if(i == n){
		func(picked);
	}else if(!((iconn[i + 1] | eliminated) & (1ll << i))){
		enumerate_maximal_independent_sets_recur(
			conn, iconn, func, i + 1,
			picked | (1ll << i), eliminated | conn[i]);
	}else{
		enumerate_maximal_independent_sets_recur(
			conn, iconn, func, i + 1, picked, eliminated);
		if(!(eliminated & (1ll << i))){
			enumerate_maximal_independent_sets_recur(
				conn, iconn, func, i + 1,
				picked | (1ll << i), eliminated | conn[i]);
		}
	}
}

template <typename _Func>
void enumerate_maximal_independent_sets(
	const vector< vector<int> > &conn, _Func &func)
{
	int n = conn.size();
	vector<ll> bitconn(n), ibitconn(n + 1);
	for(int i = n - 1; i >= 0; --i){
		ll mask = 0;
		for(int j = 0; j < conn[i].size(); ++j){
			mask |= (1ll << conn[i][j]);
		}
		bitconn[i] = mask;
		ibitconn[i] = mask | ibitconn[i + 1];
	}
	enumerate_maximal_independent_sets_recur(bitconn, ibitconn, func);
}

#include <iostream>

void func(ll picked){
	for(int i = 0; i < 64; ++i){
		if(picked & (1ll << i)){ cout << i << " "; }
	}
	cout << endl;
}

int main(){
	/*   0   4
     *  /|\  |
     * 1-+-2 5
     *  \|
     *   3   6
	 */
	vector< vector<int> > conn(7);
#define ADD_EDGE(a, b) conn[a].push_back(b); conn[b].push_back(a);
	ADD_EDGE(0, 1);
	ADD_EDGE(0, 2);
	ADD_EDGE(0, 3);
	ADD_EDGE(1, 2);
	ADD_EDGE(1, 3);
	ADD_EDGE(4, 5);
	enumerate_maximal_independent_sets(conn, func);
	return 0;
}

