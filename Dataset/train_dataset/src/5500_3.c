#include <bits/stdc++.h>
using namespace std;
const long long Mod = 1000000007LL;
const int N = 3e5 + 10;
const long long Inf = 2242545357980376863LL;
const long long Log = 30;
map<int, vector<int>> mp;
int C[Log];
long long mul(long long a, long long b) { return (a * b) % Mod; }
long long bin_pow(long long b, long long p) {
  long long res = 1;
  for (long long j = 1, pw = b; j <= p; j += j, pw = mul(pw, pw))
    if (j & p) res = mul(res, pw);
  return res;
}
long long inv(long long x) { return bin_pow(x, Mod - 2); }
long long f[N], iv[N];
long long nCr(long long n, long long r) {
  if (r < 0 || n < 0 || n < r) return 0;
  return mul(f[n], mul(iv[r], iv[n - r]));
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  f[0] = 1;
  for (int i = 1; i < N; i++) f[i] = mul(f[i - 1], i);
  for (int i = 0; i < N; i++) iv[i] = inv(f[i]);
  int n;
  cin >> n;
  int v;
  for (int i = 1; i <= n; i++) {
    cin >> v;
    int d = 2;
    int cnt = 0;
    while (d * d <= v) {
      cnt = 0;
      while (v % d == 0) {
        v /= d;
        cnt++;
      }
      if (cnt) mp[d].push_back(cnt);
      d++;
    }
    if (v > 1) mp[v].push_back(1);
  }
  long long ans = 0;
  for (auto [prime, vec] : mp) {
    memset(C, 0, sizeof C);
    for (auto x : vec) C[x]++;
    C[0] = n - ((int)vec.size());
    int sum = n;
    int nw = 0;
    for (int i = 0; i < Log; i++) {
      nw += C[i];
      sum -= C[i];
      long long ps = 0;
      for (int j = sum; j >= 0; j--) {
        ans += mul(mul(j, nCr(nw, j)), ps);
        ps += nCr(sum, j);
        ps %= Mod;
      }
      ps = bin_pow(2, nw);
      for (int j = 0; j <= sum; j++) {
        ans += mul(mul(j, nCr(sum, j)), ps);
        ps -= nCr(nw, j);
        ps %= Mod;
      }
    }
  }
  ans %= Mod;
  ans += Mod;
  cout << ans % Mod << '\n';
  return 0;
}
