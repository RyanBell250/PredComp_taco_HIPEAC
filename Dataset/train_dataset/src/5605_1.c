#include <bits/stdc++.h>
using namespace std;


const int MAXN = 100010;
const int MOD = 998244353;
char str[MAXN];
long long F[MAXN], rF[MAXN];
long long inv(long long a, long long m) {
	if (a == 1) return 1;
	return inv(m%a, m) * (m - m/a) % m;
}
int main() {
	int T;
	int n;
	F[0] = rF[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		F[i] = F[i-1] * i % MOD;
		rF[i] = rF[i-1] * inv(i, MOD) % MOD;
	}
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		scanf("%s", str);
		int cg = 0;
		int c0 = 0;
		int c1 = 0;
		for (int i = 0; i < n; i++) {
			if (str[i] == '0') {
				c0++;
			} else if (i+1 < n && str[i+1] == '1') {
				cg++;
				i++;
			} else {
				c1++;
			}
		}
		long long ans = F[cg + c0] * rF[c0] % MOD * rF[cg] % MOD;
		printf("%d\n", (int) ans);
	}
	return 0;
}