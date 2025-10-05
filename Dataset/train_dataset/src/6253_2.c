#include <bits/stdc++.h>
using namespace std;
int a[30], b[30];
long long dp[30][30][30];
long long inf = 123456789012345LL;
map<int, vector<vector<long long> > > me;
vector<vector<long long> > tmp, one, ret;
vector<long long> cl;
vector<vector<long long> > rec(int a) {
  if (me[a].size() > 0) return me[a];
  vector<vector<long long> > ret = tmp, mae = rec(a / 2), ato = rec(a - a / 2);
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      for (int k = 0; k < 50; k++) {
        ret[i][j] = min(ret[i][j], mae[i][k] + ato[k][j]);
      }
  return me[a] = ret;
}
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  for (int i = 0; i < 30; i++)
    for (int j = 0; j < 30; j++)
      for (int k = 0; k < 30; k++) dp[i][j][k] = inf;
  dp[0][0][0] = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n + 1; j++)
      for (int k = 0; k < n + 1; k++) {
        dp[i + 1][j + 1][k] = min(dp[i + 1][j + 1][k], dp[i][j][k] + a[i]);
        if (j < 1)
          dp[i + 1][j][k + 1] = min(dp[i + 1][j][k + 1], dp[i][j][k] + b[i]);
        else
          dp[i + 1][j - 1][k] = min(dp[i + 1][j - 1][k], dp[i][j][k] + b[i]);
      }
  for (int i = 0; i < 50; i++) cl.push_back(inf);
  for (int i = 0; i < 50; i++) tmp.push_back(cl);
  one = tmp;
  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      for (int k = 0; k < 50; k++) {
        if (i - k <= n && j - k <= n && i >= k && j >= k)
          one[i][j] = min(one[i][j], dp[n][j - k][i - k]);
      }
  me[1] = one;
  ret = rec(m);
  cout << ret[0][0] << endl;
  return 0;
}
