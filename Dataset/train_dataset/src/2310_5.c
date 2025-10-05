#include <bits/stdc++.h>
using namespace std;
const long long N = 2e5 + 5;
long long MOD = (long long)(1e9 + 7);
long long int dp[1005][1005][2];
vector<long long int> cnt(1005);
long long int n, m, x, y;
long long int solve(long long int index, long long int con,
                    long long int type) {
  if (index > m) {
    if (x <= con && con <= y) return 0;
    return INT_MAX;
  }
  if (con > y) return INT_MAX;
  if (dp[index][con][type] != -1) return dp[index][con][type];
  long long int &ans = dp[index][con][type];
  if (con == 0) {
    ans = min(cnt[index] + solve(index + 1, 1, 1),
              n - cnt[index] + solve(index + 1, 1, 0));
  } else if (type == 1) {
    ans = cnt[index] + solve(index + 1, con + 1, 1);
    if (x <= con && con <= y) {
      ans = min(ans, n - cnt[index] + solve(index + 1, 1, 0));
    }
  } else {
    ans = n - cnt[index] + solve(index + 1, con + 1, 0);
    if (x <= con && con <= y) {
      ans = min(ans, cnt[index] + solve(index + 1, 1, 1));
    }
  }
  return ans;
}
void solve() {
  cin >> n >> m >> x >> y;
  memset(dp, -1, sizeof dp);
  for (long long int i = 0; i <= m; i++) {
    cnt[i] = 0;
  }
  for (long long int i = 1; i <= n; i++) {
    for (long long int j = 1; j <= m; j++) {
      char c;
      cin >> c;
      if (c == '#') cnt[j]++;
    }
  }
  cout << solve(1, 0, 0) << "\n";
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long int t = 1;
  while (t--) solve();
  cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC
       << "ms\n";
  return 0;
}
