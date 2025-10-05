#include <bits/stdc++.h>
using namespace std;
const long long mod = (long long)1e9 + 7;
const long long nmax = (long long)2e6 + 10;
long long cnt[nmax];
long long sum[nmax];
long long pre[nmax];
void solve() {
  cnt[0] = 0;
  cnt[1] = 1;
  cnt[2] = 1;
  sum[0] = 0;
  sum[1] = 0;
  sum[2] = 0;
  pre[0] = 0;
  pre[1] = 4;
  pre[2] = 4;
  for (long long i = 3; i < nmax - 9; i++) {
    cnt[i] = (cnt[i - 1] + (cnt[i - 2] * 2) % mod) % mod;
    pre[i] = (pre[i - 3] + (cnt[i] * 4) % mod) % mod;
    sum[i] = pre[i - 2];
  }
}
signed main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(0);
  solve();
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    cout << sum[n] << endl;
  }
  return 0;
}
