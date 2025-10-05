#include <bits/stdc++.h>
using namespace std;
const long long MOD = (119 << 23) + 1;
long long add(long long a, long long b) {
  a += b;
  if (a < 0) {
    a += MOD;
  }
  if (a >= MOD) {
    a -= MOD;
  }
  return a;
}
long long sub(long long a, long long b) {
  a -= b;
  if (a < 0) a += MOD;
  return a;
}
long long mult(long long a, long long b) { return (a * b) % MOD; }
const long long mxN = 300000;
vector<long long> adj[mxN];
long long dp[mxN][3];
void dfs(long long v, long long p) {
  dp[v][0] = dp[v][1] = dp[v][2] = 1;
  for (long long i : adj[v]) {
    if (i == p) continue;
    dfs(i, v);
    dp[v][0] = mult(dp[v][0], add(add(dp[i][0], dp[i][1]), dp[i][2]));
    dp[v][1] = mult(dp[v][1], add(add(mult(3, dp[i][0]), mult(2, dp[i][1])),
                                  mult(2, dp[i][2])));
    dp[v][2] = mult(dp[v][2],
                    add(add(mult(2, dp[i][0]), mult(2, dp[i][1])), dp[i][2]));
  }
  dp[v][1] = sub(dp[v][1], dp[v][0]);
  dp[v][2] = sub(dp[v][2], dp[v][0]);
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long long n;
  cin >> n;
  for (long long i = 0; i < n - 1; ++i) {
    long long a, b;
    cin >> a >> b;
    --a;
    --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(0, -1);
  cout << add(add(dp[0][0], dp[0][1]), sub(dp[0][2], 1)) << "\n";
}
