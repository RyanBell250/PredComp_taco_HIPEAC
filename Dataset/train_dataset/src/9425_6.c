#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  long long solve(vector<vector<int>>& C, vector<pair<int, int>>& edges,
                  vector<int>& res) {
    res.clear();
    int n = C[0].size();
    res.resize(n, -1);
    vector<vector<int>> graph(n);
    for (auto& e : edges) {
      int u = e.first, v = e.second;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
      if (graph[i].size() > 2) {
        return -1;
      }
    }
    const long long INF = 1LL << 58;
    vector<int> pars(n, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
      pars[u] = p;
      for (auto v : graph[u]) {
        if (v == p) {
          continue;
        }
        dfs(v, u);
      }
    };
    int rt = 0;
    for (int i = 0; i < n; ++i) {
      if (graph[i].size() == 1) {
        rt = i;
        break;
      }
    }
    dfs(rt, -1);
    long long best = INF;
    vector<int> coloring(n, 0);
    function<void(int, int, long long&)> color = [&](int u, int used,
                                                     long long& cost) {
      int c = 0 + 1 + 2;
      c -= used >> 2;
      c -= used & 3;
      cost += C[c][u];
      coloring[u] = c;
      used >>= 2;
      used |= c << 2;
      for (auto v : graph[u]) {
        if (v == pars[u]) {
          continue;
        }
        color(v, used, cost);
      }
    };
    {
      assert(graph[rt].size() == 1);
      int u = graph[rt][0];
      assert(graph[u].size() > 1);
      int v = -1;
      for (auto x : graph[u]) {
        if (x == rt) {
          continue;
        }
        v = x;
      }
      assert(v >= 0);
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (i == j) {
            continue;
          }
          fill(coloring.begin(), coloring.end(), -1);
          long long cost = C[i][rt] + C[j][u];
          coloring[rt] = i;
          coloring[u] = j;
          color(v, j << 2 | i, cost);
          if (cost < best) {
            best = cost;
            res = coloring;
          }
        }
      }
    }
    return best;
  }
};
int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution sol;
  int n;
  cin >> n;
  vector<vector<int>> C(3, vector<int>(n, 0));
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> C[i][j];
    }
  }
  vector<pair<int, int>> edges;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    edges.emplace_back(u, v);
  }
  vector<int> res;
  auto ans = sol.solve(C, edges, res);
  cout << ans << '\n';
  if (ans >= 0) {
    for (auto x : res) {
      cout << x + 1 << ' ';
    }
    cout << '\n';
  }
  return 0;
}
