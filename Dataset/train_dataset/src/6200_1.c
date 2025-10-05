#include <bits/stdc++.h>
using namespace std;
string itos(int x) {
  stringstream ss;
  ss << x;
  return ss.str();
}
struct edge {
  int u, v, cost;
  edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
  edge() { u = v = cost = 0; }
};
int n, k, t, a[85], cost[85];
vector<int> near[200];
edge e[7000];
long long dist[200];
int prv[200];
void SPFA(int s = 0) {
  fill(dist, dist + 200, (1LL << 60));
  dist[s] = 0;
  for (int i = 0; i < 2 * n + 1; i++)
    for (int j = 0; j <= 2 * n + 1; j++) {
      for (auto x : near[j]) {
        if (e[x].u == j) {
          if (dist[e[x].v] > dist[e[x].u] + e[x].cost) {
            dist[e[x].v] = dist[e[x].u] + e[x].cost;
            prv[e[x].v] = x;
          }
        }
      }
    }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> cost[i];
  for (int i = 1; i <= n; i++) {
    near[0].push_back((t)), near[2 * i - 1].push_back((t));
    e[t++] = edge(0, 2 * i - 1, cost[a[i]]);
    near[2 * i - 1].push_back((t)), near[2 * i].push_back((t));
    e[t++] = edge(2 * i - 1, 2 * i, -1000000007);
    near[2 * i].push_back((t)), near[2 * n + 1].push_back((t));
    e[t++] = edge(2 * i, 2 * n + 1, 0);
  }
  for (int i = 1; i < n; i++)
    for (int j = i + 1; j <= n; j++) {
      near[2 * i].push_back((t)), near[2 * j - 1].push_back((t));
      e[t++] = edge(2 * i, 2 * j - 1, cost[a[j]] * (a[i] != a[j]));
    }
  long long res = 1LL * n * 1000000007;
  for (int i = 0; i < k; i++) {
    SPFA();
    if (dist[2 * n + 1] == (1LL << 60)) break;
    long long tt = 0;
    for (int pos = 2 * n + 1; pos != 0;) {
      int x = prv[pos];
      tt += e[x].cost;
      e[x].cost *= -1;
      swap(e[x].u, e[x].v);
      pos = e[x].v;
    }
    if (tt >= 0) break;
    res += tt;
  }
  cout << res << endl;
  return 0;
}
