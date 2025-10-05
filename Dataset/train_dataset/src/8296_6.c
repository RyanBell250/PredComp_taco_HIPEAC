#include <bits/stdc++.h>
const int maxn = 1005;
const double INF = 2e9;
using namespace std;
double p[maxn][maxn], c[maxn], dp[maxn];
bool mark[maxn];
int main() {
  int n, x;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      scanf("%d", &x);
      p[i][j] = 0.01 * x;
    }
  fill(dp, dp + n, INF);
  dp[n - 1] = 0;
  fill(c, c + n, 1);
  priority_queue<pair<double, int>, vector<pair<double, int> >,
                 greater<pair<double, int> > >
      pq;
  pq.push({dp[n - 1], n - 1});
  while (!pq.empty()) {
    int x = pq.top().second;
    pq.pop();
    if (mark[x]) continue;
    mark[x] = true;
    for (int i = 0; i < n; i++) {
      if (mark[i] || p[i][x] == 0) continue;
      if (dp[i] == INF) {
        dp[i] = (p[i][x] * (dp[x] + 1) + (1 - p[i][x])) / (p[i][x]);
        c[i] = (1 - p[i][x]);
      } else {
        dp[i] = (dp[i] * (1 - c[i]) - c[i] + c[i] * p[i][x] * (dp[x] + 1));
        c[i] = c[i] * (1 - p[i][x]);
        dp[i] += c[i];
        dp[i] /= (1 - c[i]);
      }
      pq.push({dp[i], i});
    }
  }
  if (dp[0] == INF)
    cout << -1 << '\n';
  else
    cout << setprecision(10) << fixed << dp[0] << '\n';
  return 0;
}
