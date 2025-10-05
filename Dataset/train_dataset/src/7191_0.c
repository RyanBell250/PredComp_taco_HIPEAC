#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (a == 0LL) return b;
  if (b == 0LL) return a;
  return gcd(b, a % b);
}
const int N = 51;
const int M = 2501;
int dp[N][M], type[N], R[N];
priority_queue<pair<int, pair<int, int>>> pq;
bool visited[N][M];
void solve() {
  int n, s, k;
  cin >> n >> s >> k;
  for (int i = 1; i <= n; i++) cin >> R[i];
  char c;
  for (int i = 1; i <= n; i++) {
    cin >> c;
    if (c == 'R')
      type[i] = 0;
    else if (c == 'G')
      type[i] = 1;
    else
      type[i] = 2;
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      dp[i][j] = 1000000007LL;
      visited[i][j] = false;
    }
  while (!pq.empty()) pq.pop();
  for (int i = 1; i <= n; i++) {
    dp[i][R[i]] = abs(i - s);
    pq.push(make_pair(-1 * R[i], make_pair(i, R[i])));
  }
  pair<int, pair<int, int>> tp;
  while (!pq.empty()) {
    tp = pq.top();
    pq.pop();
    int thres = -1 * tp.first;
    int ind = tp.second.first;
    int sum = tp.second.second;
    if (visited[ind][sum]) continue;
    visited[ind][sum] = true;
    for (int i = 1; i <= n; i++)
      if (type[i] != type[ind] && R[i] > thres &&
          dp[i][R[i] + sum] > dp[ind][sum] + abs(ind - i)) {
        dp[i][R[i] + sum] = dp[ind][sum] + abs(ind - i);
        pq.push(make_pair(-1 * R[i], make_pair(i, R[i] + sum)));
      }
  }
  int ans = 1000000007LL;
  for (int i = 1; i <= n; i++)
    for (int j = k; j < M; j++) ans = min(ans, dp[i][j]);
  if (ans == 1000000007LL)
    cout << "-1\n";
  else
    cout << ans << "\n";
  return;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  clock_t clk = clock();
  int t = 1;
  for (int tests = 1; tests <= t; tests++) {
    solve();
  }
  clk = clock() - clk;
  cerr << "Time Elapsed: " << fixed << setprecision(10)
       << ((long double)clk) / CLOCKS_PER_SEC << "\n";
  return 0;
}
