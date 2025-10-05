#include <bits/stdc++.h>
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
using namespace std;
const long long MOD = 1e+9 + 7;
const long long INF = LLONG_MAX;
const int INFi = INT_MAX;
const long long N = 2e+5 + 8;
vector<long long> adj[N];
long long vis[N];
long long dx4[] = {0, 1, 0, -1}, dy4[] = {1, 0, -1, 0};
long long test_cases = 1;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
;
long long n, m, u, v, cnt[N][2], level[N][2], contrib[N];
void bfs(long long st, long long j) {
  for (long long i = (0); i <= n + 1; i++)
    vis[i] = 0, cnt[i][j] = 0, level[i][j] = INF;
  queue<long long> q;
  q.push(st);
  vis[st] = 1;
  cnt[st][j] = 1;
  level[st][j] = 0;
  while (q.size()) {
    long long v = q.front();
    q.pop();
    for (auto to : adj[v]) {
      if (level[to][j] == INF) {
        level[to][j] = level[v][j] + 1;
      }
      if (level[to][j] > level[v][j]) {
        cnt[to][j] += cnt[v][j];
      }
      if (vis[to] == 0) {
        vis[to] = 1;
        q.push(to);
      }
    }
  }
}
void MAIN(long long tc) {
  cin >> n >> m;
  for (long long i = (1); i <= m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  bfs(1, 0);
  bfs(n, 1);
  for (long long v = (1); v <= n; v++) {
    for (auto to : adj[v]) {
      if (level[v][0] + level[to][1] + 1 == level[n][0]) {
        contrib[v] += cnt[v][0] * cnt[to][1];
        contrib[to] += cnt[v][0] * cnt[to][1];
      }
    }
  }
  long long res = 0;
  for (long long i = (1); i <= n; i++) res = max(res, contrib[i]);
  cout << (long double)res / cnt[n][0];
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed;
  cout << setprecision(12);
  ;
  for (long long i = (1); i <= test_cases; i++) {
    MAIN(i);
  }
}
