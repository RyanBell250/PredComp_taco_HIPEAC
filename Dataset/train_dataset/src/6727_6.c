#include <bits/stdc++.h>
using namespace std;
void Genawy() {
  std::ios_base::sync_with_stdio(0);
  cin.tie(NULL), cout.tie(NULL);
}
const int MAX = 4 * 100000 + 5;
pair<long long, int> g[MAX];
struct SegmentTree {
  pair<long long, int> tree[4 * MAX];
  SegmentTree() {
    for (int i = 0; i < 4 * MAX; i++) {
      tree[i] = {1e18, 1e9};
    }
  }
  void build(int cur, int l, int r) {
    if (l == r) {
      tree[cur] = {g[l].first, g[l].second};
      return;
    }
    int m = (l + r) >> 1;
    build(cur * 2, l, m);
    build(cur * 2 + 1, m + 1, r);
    tree[cur] = min(tree[cur * 2], tree[cur * 2 + 1]);
  }
  pair<long long, int> get(int cur, int l, int r, int x, int y) {
    if (l > y || r < x) return {1e18, 1e9};
    if (l >= x && r <= y) return tree[cur];
    int m = (l + r) >> 1;
    return min(get(cur * 2, l, m, x, y), get(cur * 2 + 1, m + 1, r, x, y));
  }
};
SegmentTree ST = SegmentTree();
bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
  if (a.first.first < b.first.first)
    return true;
  else if (a.first.first == b.first.first && a.first.second > b.first.second)
    return true;
  else
    return false;
}
int main() {
  Genawy();
  int n;
  cin >> n;
  vector<pair<pair<long long, long long>, int>> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].first.first >> v[i].first.second;
    v[i].second = i + 1;
  }
  sort(v.begin(), v.end(), cmp);
  for (int i = 1; i <= n; i++) {
    g[i].first = v[i - 1].first.second;
    g[i].second = v[i - 1].second;
  }
  ST.build(1, 1, n);
  for (int i = 0; i < n; i++) {
    int to = -1;
    int l = i + 1, h = n - 1;
    while (l <= h) {
      int md = (l + h) / 2;
      if (v[md].first.first <= v[i].first.second)
        to = md, l = md + 1;
      else
        h = md - 1;
    }
    if (to != -1) {
      pair<long long, int> p = ST.get(1, 1, n, i + 2, to + 1);
      if (p.first <= v[i].first.second) {
        cout << p.second << " " << v[i].second << endl;
        return 0;
      }
    }
  }
  cout << "-1 -1" << endl;
  return 0;
}
