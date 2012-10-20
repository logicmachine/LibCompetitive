#include <utility>

typedef long long ll;

pair<ll, ll> extgcd(ll a, ll b){
	ll g = a, x = 1, y = 0;
	if(b != 0){
		pair<ll, ll> p = extgcd(b, a % b);
		x = p.second;
		y = p.first - (a / b) * x;
	}
	return make_pair(x, y);
}

ll mod_inverse(ll a, ll m){
	pair<ll, ll> p = extgcd(a, m);
	return (m + p.first % m) % m;
}

