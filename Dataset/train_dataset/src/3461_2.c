#include <bits/stdc++.h>
using namespace std;
vector<int> vi[200001], v[200001];
int d[200001];
int n, m;
vector<int> dij(int s) {
  set<pair<int, int> > ss;
  ss.insert({0, s});
  map<int, int> m;
  m[s] = 0;
  vector<int> vis(n + 1, -1);
  while (ss.size() > 0) {
    auto it = *ss.begin();
    ss.erase(ss.begin());
    int node = it.second, dis = it.first;
    vis[node] = dis;
    for (auto &i : vi[node]) {
      if (vis[i] != -1) continue;
      if (m.find(i) == m.end()) {
        m[i] = dis + 1;
        ss.insert({m[i], i});
      } else if (m[i] > dis + 1) {
        ss.erase({m[i], i});
        m[i] = dis + 1;
        ss.insert({m[i], i});
      }
    }
  }
  return vis;
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    vi[y].push_back(x);
    v[x].push_back(y);
  }
  int k;
  cin >> k;
  vector<int> p(k);
  for (int i = 0; i < k; i++) cin >> p[i];
  vector<int> d = dij(p.back());
  int mi = 0, ma = 0;
  for (int i = 0; i < k - 1; i++) {
    vector<int> tmp;
    int mii = 1e9;
    for (auto &i : v[p[i]]) {
      if (d[i] < mii) {
        mii = d[i];
        tmp.clear();
        tmp.push_back(i);
      } else if (d[i] == mii)
        tmp.push_back(i);
    }
    int fl = 0;
    for (auto &j : tmp)
      if (j == p[i + 1]) {
        if (tmp.size() > 1) ma++;
        fl = 1;
        break;
      }
    if (fl == 0) {
      mi++;
      ma++;
    }
  }
  cout << mi << ' ' << ma;
  return 0;
}
