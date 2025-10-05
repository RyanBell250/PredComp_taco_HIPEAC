#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
struct edge {
  int from, to;
  long long cost;
  int id;
};
vector<vector<edge> > g;
vector<char> used;
int n, k;
vector<vector<long long> > dp;
vector<vector<long long> > dist;
void dfs(int v, int p, int root, long long curr) {
  dist[root][v] = curr;
  for (edge& e : g[v]) {
    if (e.to == p) {
      continue;
    }
    dfs(e.to, v, root, curr + e.cost);
  }
}
vector<int> subtreeId;
int cnt = -1;
void dfsSubtree(int v, int p) {
  subtreeId[v] = cnt;
  for (edge& e : g[v]) {
    if (e.to == p) {
      continue;
    }
    if (v == p) {
      ++cnt;
    }
    dfsSubtree(e.to, v);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  g.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    long long c;
    cin >> u >> v >> c;
    --u, --v;
    g[u].push_back({u, v, c, i});
    g[v].push_back({v, u, c, i});
  }
  dist = vector<vector<long long> >(n, vector<long long>(n));
  for (int v = 0; v < n; ++v) {
    dfs(v, v, v, 0);
  }
  int start;
  cin >> start;
  --start;
  cin >> k;
  vector<int> criminals(k);
  for (int i = 0; i < k; ++i) {
    cin >> criminals[i];
    --criminals[i];
  }
  dp = vector<vector<long long> >(n, vector<long long>(k + 1));
  for (int v = 0; v < n; ++v) {
    if ((int)(g[v]).size() == 1) {
      dp[v][0] = 0;
    }
  }
  for (int j = 1; j <= k; ++j) {
    for (int v = 0; v < n; ++v) {
      if ((int)(g[v]).size() == 1) {
        long long lf = 0, rg = inf;
        while (rg - lf > 1) {
          long long md = (lf + rg) >> 1;
          int maxSum = 0;
          for (int u = 0; u < n; ++u) {
            if (u == v || (int)(g[u]).size() != 1) {
              continue;
            }
            int maxx = -1;
            for (int i = 0; i < j; ++i) {
              if (dp[u][i] + dist[v][u] >= md) {
                maxx = i;
                break;
              }
            }
            if (maxx >= 0) {
              maxSum += j - maxx;
            }
          }
          if (maxSum >= j) {
            lf = md;
          } else {
            rg = md;
          }
        }
        dp[v][j] = lf;
      }
    }
  }
  if ((int)(g[start]).size() == 1) {
    cout << dp[start][k] << "\n";
    return 0;
  }
  subtreeId.resize(n);
  dfsSubtree(start, start);
  vector<int> num(cnt + 1);
  for (int i = 0; i < k; ++i) {
    ++num[subtreeId[criminals[i]]];
  }
  long long lf = 0, rg = inf;
  while (rg - lf > 1) {
    long long md = (lf + rg) >> 1;
    vector<int> total(cnt + 1);
    for (int u = 0; u < n; ++u) {
      if (u == start || (int)(g[u]).size() != 1) {
        continue;
      }
      int maxx = -1;
      for (int i = 0; i <= k; ++i) {
        if (dp[u][i] + dist[start][u] >= md) {
          maxx = i;
          break;
        }
      }
      if (maxx >= 0) {
        total[subtreeId[u]] += k - maxx;
      }
    }
    bool ok = true;
    for (int i = 0; i <= cnt; ++i) {
      if (total[i] < num[i]) {
        ok = false;
      }
    }
    if (ok) {
      lf = md;
    } else {
      rg = md;
    }
  }
  cout << lf << "\n";
}
