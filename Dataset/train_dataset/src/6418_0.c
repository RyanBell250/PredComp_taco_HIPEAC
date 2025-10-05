#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 1000000007;
ll jou2(ll x) {
	ll ans = 1, a = 2;
	while (x) {
		if (x % 2)ans *= a;
		a *= a;
		ans %= MOD;
		a %= MOD;
		x /= 2;
	}
	return ans;
}
int main(){
	int N;
	cin >> N;
	vector<ll> A(N), ZC(1048577, 1), PC(1048577, 0), La = PC;
	for (int i = 0;i < N;i++) {
		cin >> A[i];
		if (i)A[i] ^= A[i - 1];
	}
	ll zc, pc = 0, ans = 0;
	if (A[N - 1]) {
		zc = 1;
		for (int i = 0;i < N - 1;i++) {
			if (A[i] == 0)
				zc += pc;
			if (A[i] == A[N - 1])
				pc += zc;
			zc %= MOD;
			pc %= MOD;
		}
		ans = zc;
	}
	else {
		zc = 0;
		
		for (int i = 0;i < N - 1;i++) {
			if (A[i]) {
				ZC[A[i]] += (zc - La[A[i]])*PC[A[i]];
				ZC[A[i]] %= MOD;
				PC[A[i]] += ZC[A[i]];
				PC[A[i]] %= MOD;
				La[A[i]] = zc;
			}
			else
				zc++;
		}
		for (ll i : PC) {
			ans += i;
			ans %= MOD;
		}
		
		ans += jou2(zc);
		ans %= MOD;
	}
	cout << ans << endl;
}
