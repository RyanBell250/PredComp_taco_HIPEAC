#include <bits/stdc++.h>
using namespace std;
const int MAX = 509;
int dp[MAX][27][27];
pair<int, int> par[MAX][27][27];
string s, ans[MAX];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s, ans[i] = s;
    for (int j = 0; j < 26; j++)
      for (int k = 0; k < 26; k++)
        if (k != j) {
          for (int p = 0; p < m; p++) {
            if (p % 2 == 1 && s[p] - 'a' != k) dp[i][j][k]++;
            if (p % 2 == 0 && s[p] - 'a' != j) dp[i][j][k]++;
          }
          int res = 1e9;
          for (int jj = 0; jj < 26; jj++)
            if (jj != j)
              for (int kk = 0; kk < 26; kk++)
                if (kk != k && kk != jj)
                  if (res > dp[i - 1][jj][kk])
                    res = dp[i - 1][jj][kk], par[i][j][k] = {jj, kk};
          dp[i][j][k] += res;
        }
  }
  int mj = 0, mk = 1;
  for (int j = 0; j < 26; j++)
    for (int k = 0; k < 26; k++)
      if (j != k && dp[n][j][k] < dp[n][mj][mk]) mj = j, mk = k;
  cout << dp[n][mj][mk] << '\n';
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j < m; j++)
      if (j & 1)
        ans[i][j] = 'a' + mk;
      else
        ans[i][j] = 'a' + mj;
    int sj = mj, sk = mk;
    mj = par[i][sj][sk].first;
    mk = par[i][sj][sk].second;
  }
  for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
