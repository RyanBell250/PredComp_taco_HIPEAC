#include <bits/stdc++.h>
using namespace std;
long long int modulo = 1000000007;
int main(int argc, char** argv) {
  int n, t;
  double p;
  cin >> n >> p >> t;
  vector<vector<double> > dp(t + 1, vector<double>(n + 1, 0.0));
  dp[0][0] = 1.0;
  for (int i = 0; i <= t - 1; ++i) {
    for (int j = 0; j <= n - 1; ++j) {
      dp[i + 1][j + 1] += p * dp[i][j];
      dp[i + 1][j] += (1 - p) * dp[i][j];
    }
    dp[i + 1][n] += dp[i][n];
  }
  double ans = 0.0;
  for (int i = 0; i <= n; ++i) {
    ans += dp[t][i] * i;
  }
  cout.precision(9);
  cout << fixed << ans << "\n";
  return 0;
}
