#include <bits/stdc++.h>
using namespace std;
const int N = 501;
bool dp[N][N][N];
int c[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, s;
  cin >> n >> s;
  for (int i = 1; i <= n; i++) cin >> c[i];
  dp[0][0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= s; j++)
      for (int k = 0; k <= s; k++)
        dp[i][j][k] =
            dp[i - 1][j][k] |
            (j - c[i] >= 0 && k - c[i] >= 0 ? dp[i - 1][j - c[i]][k - c[i]]
                                            : false) |
            (j - c[i] >= 0 ? dp[i - 1][j - c[i]][k] : false);
  vector<int> ans;
  for (int k = 0; k <= s; k++)
    if (dp[n][s][k]) ans.push_back(k);
  cout << ans.size() << "\n";
  for (auto i : ans) cout << i << ' ';
}
