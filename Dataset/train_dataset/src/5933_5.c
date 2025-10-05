#include <bits/stdc++.h>
using namespace std;
int parent[1001], parent1[1001], sz[1001], sz1[1001];
int find_set(int p) {
  if (parent[p] != p) parent[p] = find_set(parent[p]);
  return parent[p];
}
void union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (sz[a] > sz[b]) swap(a, b);
  if (a == b) return;
  sz[b] += sz[a];
  sz[a] = 0;
  parent[a] = b;
}
int find_set1(int p) {
  if (parent1[p] != p) parent1[p] = find_set1(parent1[p]);
  return parent1[p];
}
void union_set1(int a, int b) {
  a = find_set1(a);
  b = find_set1(b);
  if (sz1[a] > sz1[b]) swap(a, b);
  if (a == b) return;
  sz1[b] += sz1[a];
  sz1[a] = 0;
  parent1[a] = b;
}
int main() {
  int n, m, m1;
  cin >> n >> m >> m1;
  for (int i = 1; i <= n; i++) {
    sz[i] = sz1[i] = 1;
    parent[i] = parent1[i] = i;
  }
  while (m--) {
    int a, b;
    cin >> a >> b;
    union_set(a, b);
  }
  while (m1--) {
    int a, b;
    cin >> a >> b;
    union_set1(a, b);
  }
  vector<pair<int, int> > ans;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (find_set(i) != find_set(j) && find_set1(i) != find_set1(j)) {
        ans.push_back(make_pair(i, j));
        union_set(i, j);
        union_set1(i, j);
      }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i].first << " " << ans[i].second << endl;
}
