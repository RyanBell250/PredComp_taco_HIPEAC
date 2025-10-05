#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int p1[100005], sz1[100005];
int p[100005], sz[100005];
vector<pair<int, int>> ansv;
void make_set(int i) {
  p[i] = i;
  sz[i] = 1;
  p1[i] = i;
  sz1[i] = i;
}
int find_set(int i) {
  if (p[i] == i) return i;
  return p[i] = find_set(p[i]);
}
int find_set1(int i) {
  if (p1[i] == i) return i;
  return p1[i] = find_set1(p1[i]);
}
void union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a == b) return;
  if (sz[a] < sz[b]) swap(a, b);
  p[b] = a;
  sz[a] += sz[b];
}
void union_set1(int a, int b) {
  a = find_set1(a);
  b = find_set1(b);
  if (a == b) return;
  if (sz1[a] < sz1[b]) swap(a, b);
  p1[b] = a;
  sz1[a] += sz1[b];
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, m1, i, j;
  cin >> n >> m >> m1;
  for (i = 0; i < n; i++) {
    make_set(i);
  }
  for (i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    union_set(x, y);
  }
  for (i = 0; i < m1; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    union_set1(x, y);
  }
  int ans = 0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (find_set(i) != find_set(j) && find_set1(i) != find_set1(j)) {
        ans++;
        union_set(i, j);
        union_set1(i, j);
        ansv.push_back({i, j});
      }
    }
  }
  cout << ans << '\n';
  for (i = 0; i < ansv.size(); i++) {
    cout << ansv[i].first + 1 << ' ' << ansv[i].second + 1 << '\n';
  }
  return 0;
}
