#include <bits/stdc++.h>
#define N (long long)(998244353)
#define MAX 500000
using namespace std;
long long factorial[MAX] = {0}, finverse[MAX] = {0},
          inverse[MAX] = {0};
void smodfact() {
  factorial[0] = factorial[1] = 1;
  finverse[0] = finverse[1] = 1;
  inverse[1] = 1;
  for(int i = 2; i < MAX; ++i) {
    factorial[i] = factorial[i - 1] * i % N;
    inverse[i] = N - (inverse[N % i] * (N / i)) % N;
    finverse[i] = finverse[i - 1] * inverse[i] % N;
  }
}
long long calccomb(long long n, long long k) {
  if(n == k && n == 0) return 1;
  if(n < 0 || k < 0 || n < k) return 0;
  return factorial[n] * finverse[k] % N * finverse[n - k] %
         N;
}
long long n, k, a;
long long dp[200005] = {0}, sum[200005] = {0};
long long solve();
int main() {
  cin >> n >> k >> a;
  cout << solve() << endl;
  return 0;
}
long long solve() {
  smodfact();
  for(int i = 0; i <= n; ++i)
    dp[k + i] = 100 * inverse[a] % N;
  a *= inverse[100];
  a %= N;
  sum[k] = n;
  for(int i = k - 1; i >= 0; --i) {
    dp[i] = sum[i + 1] * inverse[n] % N;
    sum[i] = sum[i + 1] + dp[i] * a % N;
    sum[i] %= N;
    sum[i] -= dp[i + n] * a % N;
    sum[i] += N;
    sum[i] %= N;
  }
  return dp[0];
}
