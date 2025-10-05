#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;

const long long mod = 1000000007;
long long inv[1001001] = { 0,1 }, fact[1001001] = { 1,1 }, ifact[1001001] = { 1,1,1 };

int main()
{
	for (int i = 2; i < 1001001; i++) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		fact[i] = fact[i - 1] * i % mod;
		ifact[i] = ifact[i - 1] * inv[i] % mod;
	}

	int N; scanf("%d", &N);
	long long ans = N * fact[N-1] % mod;
	for (int p = 1; p < N; p++) {
		int u = 2 * p;
		if (u < N) continue;
		int h = N-1-p;
		if (h > p - 1) continue;
		long long v = fact[p] * fact[p - 1] % mod * ifact[p - 1 - h] % mod;
		ans = (ans + mod -  v) % mod;
	}

	printf("%lld\n", ans);

	return 0;
}