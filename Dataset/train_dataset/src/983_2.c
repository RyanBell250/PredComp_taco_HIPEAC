#include <bits/stdc++.h>
using namespace std;
vector<pair<pair<int, int>, int> > v(200005);
vector<vector<pair<int, int> > > v1(200005);
bool dfs(int root, vector<int>& x) {
  int l = v1[root].size();
  int dest, w;
  for (int i = 0; i < l; i++) {
    dest = v1[root][i].first;
    w = v1[root][i].second;
    if (x[dest] == -1) {
      x[dest] = x[root] ^ w;
      bool ans = dfs(dest, x);
      if (!ans) return false;
    } else {
      if (x[dest] != x[root] ^ w) return false;
    }
  }
  return true;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    int a, b, c;
    v.clear();
    for (int i = 0; i <= n; i++) {
      v1[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
      cin >> a >> b >> c;
      v.push_back(make_pair(make_pair(a, b), c));
      if (c != -1) {
        c = __builtin_parity(c);
        v1[a].emplace_back(b, c);
        v1[b].emplace_back(a, c);
      }
    }
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      v1[a].emplace_back(b, c);
      v1[b].emplace_back(a, c);
    }
    vector<int> x(n + 1, -1);
    int root, ii;
    for (ii = 1; ii <= n; ii++) {
      if (x[ii] == -1) {
        root = ii;
        x[root] = 0;
        bool ans = dfs(root, x);
        if (!ans) {
          cout << "NO\n";
          break;
        }
      }
    }
    if (ii == n + 1) {
      cout << "YES\n";
      for (int i = 0; i < n - 1; i++) {
        if (v[i].second == -1) {
          v[i].second = x[v[i].first.first] ^ x[v[i].first.second];
        }
        cout << v[i].first.first << ' ' << v[i].first.second << ' '
             << v[i].second << '\n';
      }
    }
  }
  return 0;
}
