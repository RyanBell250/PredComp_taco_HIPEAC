#include <bits/stdc++.h>
using namespace std;
const long double INF = 1000000000;
const long long INFll = 1ll * INF * INF;
const long double ldINF = 1e+018;
const long double EPS = 0.000000001;
const int sdx[4] = {-1, 0, 1, 0};
const int sdy[4] = {0, 1, 0, -1};
const int MOD = 1000000007;
map<pair<char, char>, int> m;
int dp[120][300][120];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  int k;
  cin >> s >> k;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x, y;
    int z;
    cin >> x >> y >> z;
    m[make_pair(x, y)] = z;
  }
  for (int i = 0; i <= s.length(); i++)
    for (int j = 0; j <= k + 2; j++)
      for (char c = 'a'; c <= 'z'; c++) dp[i][c][j] = -INF;
  for (char c = 'a'; c <= 'z'; c++) dp[0][c][s[0] != c] = 0;
  for (int i = 0; i < s.length() - 1; i++)
    for (int j = 0; j <= k; j++)
      for (char t = 'a'; t <= 'z'; t++)
        for (char p = 'a'; p <= 'z'; p++) {
          int z = (t != s[i + 1]);
          dp[i + 1][t][j + z] =
              max(dp[i + 1][t][j + z], dp[i][p][j] + m[make_pair(p, t)]);
        }
  int ans = -INF;
  for (int i = 0; i <= k; i++)
    for (char c = 'a'; c <= 'z'; c++) ans = max(ans, dp[s.length() - 1][c][i]);
  cout << ans << endl;
  return 0;
}
