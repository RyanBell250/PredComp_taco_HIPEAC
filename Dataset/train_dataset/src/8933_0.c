#include <bits/stdc++.h>
using namespace std;
long long int dp[105][105][105];
long long int col[105][105];
int main() {
  long long int n, m, k;
  cin >> n >> m >> k;
  vector<long long int> q;
  for (long long int i = 0; i < n; i++) {
    long long int temp;
    cin >> temp;
    temp--;
    q.push_back(temp);
  }
  for (long long int i = 0; i < n; i++) {
    for (long long int j = 0; j < m; j++) {
      long long int te;
      cin >> te;
      col[i][j] = te;
    }
  }
  for (long long int i = 0; i < 105; i++)
    for (long long int j = 0; j < 105; j++)
      for (long long int c = 0; c < 105; c++) dp[i][j][c] = 1000000000000;
  if (q[0] == -1) {
    for (long long int i = 0; i < m; i++) dp[0][i][0] = 1000000000000;
    for (long long int i = 0; i < m; i++) dp[0][i][1] = col[0][i];
  } else if (q[0] != -1) {
    for (long long int i = 0; i < m; i++)
      for (long long int i = 2; i <= k; i++) dp[0][m][k] = 1000000000000;
    dp[0][q[0]][1] = 0;
  }
  for (long long int i = 1; i < n; i++) {
    if (q[i] != -1) {
      for (long long int j = 0; j < m; j++) {
        for (long long int r = 1; r <= k; r++) {
          if (j == q[i]) {
            long long int t = 1000000000000;
            for (long long int second = 0; second < m; second++) {
              if (second == j)
                t = min(t, dp[i - 1][second][r]);
              else if (second != j) {
                t = min(t, dp[i - 1][second][r - 1]);
              }
            }
            dp[i][j][r] = t;
          } else
            dp[i][j][r] = 1000000000000;
        }
      }
    } else {
      for (long long int j = 0; j < m; j++) {
        for (long long int r = 1; r <= k; r++) {
          long long int t = 1000000000000;
          for (long long int second = 0; second < m; second++) {
            if (second == j) {
              t = min(t, dp[i - 1][second][r] + col[i][j]);
            } else if (second != j) {
              t = min(t, dp[i - 1][second][r - 1] + col[i][j]);
            }
          }
          dp[i][j][r] = t;
        }
      }
    }
  }
  long long int ans = 1000000000000;
  for (long long int i = 0; i < m; i++) {
    ans = min(ans, dp[n - 1][i][k]);
  }
  if (ans != 1000000000000)
    cout << ans << endl;
  else
    cout << -1 << endl;
}
