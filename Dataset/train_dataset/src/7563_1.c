#include <bits/stdc++.h>
using namespace std;
const int maxn = 20 + 2;
const int INF = 0x3f3f3f3f;
int n, m;
int a[maxn][maxn];
string str[maxn];
int dp[1 << maxn];
void DP() {
  memset(dp, INF, sizeof(dp));
  dp[0] = 0;
  for (int i = 0; i < (1 << n); i++) {
    int pos;
    for (int j = 0; j < n; j++)
      if (!((i >> j) & 1)) {
        pos = j;
        break;
      }
    for (int j = 0; j < m; j++) {
      int cur = i + (1 << pos);
      dp[cur] = min(dp[cur], dp[i] + a[pos][j]);
      int now = cur, sum = 0, mx = 0;
      for (int k = 0; k < n; k++)
        if (str[pos][j] == str[k][j]) {
          now |= 1 << k;
          sum += a[k][j];
          mx = max(mx, a[k][j]);
        }
      dp[now] = min(dp[now], dp[i] + sum - mx);
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) cin >> str[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) scanf("%d", &a[i][j]);
  DP();
  printf("%d", dp[(1 << n) - 1]);
  return 0;
}
