#include <bits/stdc++.h>

#define pb push_back
#define For(i, j, k) for(int i = j; i <= k; i++)

using namespace std;

typedef vector<unsigned char> vb;

const int N = 105;
const int Mod = 998244353;

map<vb, int> dp;

int work(vb o){
	if(!o.size()) return 1;

	int &ans = dp[o];
	if(ans) return ans;

	int n = int(o.size()) - 1;
	int coe = o[n] + 1;
	o.pop_back();
	ans = coe * work(o) % Mod;
	o.pb(coe - 1);

	For(x, 1, (n + 1) / 2){
		int l = n - x + 1, r = n;
		vb v, s = o;
		For(i, l, r) v.pb(o[i]), s.pop_back();

		l -= x, r -= x;
		for(; l >= 0; l -= x, r -= x){
			For(i, l, r) v[i - l] &= o[i], s.pop_back();
			ans = (ans + 1ll * work(v) * work(s)) % Mod;
		}
	}
	
	return ans;
}

char S[N];

int main(){

	scanf("%s", S);
	int n = strlen(S) - 1;
	vb o;
	For(i, 0, n) o.pb(S[i] - '0');
	printf("%d\n", work(o));

	return 0;
}