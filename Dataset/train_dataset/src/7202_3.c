#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;
const int n_ = 3e5 + 1000;
long long gcd(long long a, long long b) { return (a ? gcd(b % a, a) : b); }
long long power(long long a, long long n) {
  long long p = 1;
  while (n > 0) {
    if (n % 2) {
      p = p * a;
    }
    n >>= 1;
    a *= a;
  }
  return p;
}
long long power(long long a, long long n, long long mod) {
  long long p = 1;
  while (n > 0) {
    if (n % 2) {
      p = p * a;
      p %= mod;
    }
    n >>= 1;
    a *= a;
    a %= mod;
  }
  return p % mod;
}
int n, dp[n_], dp2[n_], x, u, v, l, m, ans;
vector<pair<int, int> > a[n_];
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  for (int(i) = 0; (i) < (m); (i)++) {
    cin >> u >> v >> l;
    a[l].push_back(make_pair(u, v));
  }
  for (int(w) = 0; (w) < (n_); (w)++) {
    for (int(i) = 0; (i) < ((int)(a[w]).size()); (i)++) dp2[a[w][i].second] = 0;
    for (int(i) = 0; (i) < ((int)(a[w]).size()); (i)++) {
      int u = a[w][i].first, v = a[w][i].second;
      dp2[v] = max(dp2[v], dp[u] + 1);
    }
    for (int(i) = 0; (i) < ((int)(a[w]).size()); (i)++) {
      int v = a[w][i].second;
      dp[v] = max(dp[v], dp2[v]);
    }
  }
  for (int(i) = 1; (i) <= (n); (i)++) ans = max(ans, dp[i]);
  cout << ans << "\n";
  return 0;
}
