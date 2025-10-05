#include <bits/stdc++.h>
using namespace std;
const int N = 22, mod = 1e9 + 7;
const long long inf = 1e15;
int n, m, a[N][N], faa[N][N], famask[N][N];
string s[N];
long long dp[1 << 20];
inline void smin(long long &a, long long b) {
  if (a > b) a = b;
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> s[i];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) cin >> a[i][j];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int faval = 0, ma = 0;
      for (int k = 0; k < n; ++k)
        if (s[i][j] == s[k][j]) {
          faval += a[k][j];
          ma = max(ma, a[k][j]);
          famask[i][j] |= (1 << k);
        }
      faval -= ma;
      faa[i][j] = faval;
    }
  }
  fill(&dp[0], &dp[0] + (1 << 20), inf);
  dp[0] = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int j = 0; j < n; ++j) {
      if ((mask >> j) & 1) continue;
      for (int k = 0; k < m; ++k) {
        smin(dp[mask | (1 << j)], dp[mask] + a[j][k]);
        smin(dp[mask | (famask[j][k])], dp[mask] + faa[j][k]);
      }
    }
  }
  cout << dp[(1 << n) - 1] << '\n';
}
