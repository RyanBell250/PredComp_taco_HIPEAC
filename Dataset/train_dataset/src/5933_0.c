#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000;
vector<int> dis1(maxn), dis2(maxn);
void init() {
  for (int i = 0; i < maxn; i++) {
    dis1[i] = dis2[i] = i;
  }
}
int find_root(int w, int n) {
  if (w == 1)
    return dis1[n] == n ? n : dis1[n] = find_root(w, dis1[n]);
  else if (w == 2)
    return dis2[n] == n ? n : dis2[n] = find_root(w, dis2[n]);
}
void connect_dis(int w, int a, int b) {
  if (w == 1)
    dis1[find_root(w, a)] = find_root(w, b);
  else if (w == 2)
    dis2[find_root(w, a)] = find_root(w, b);
}
int main() {
  init();
  int n, m1, m2, a, b, num = 0;
  vector<pair<int, int>> ans;
  cin >> n >> m1 >> m2;
  for (int i = 0; i < m1; i++) {
    cin >> a >> b;
    connect_dis(1, a - 1, b - 1);
  }
  for (int i = 0; i < m2; i++) {
    cin >> a >> b;
    connect_dis(2, a - 1, b - 1);
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if ((find_root(1, i) != find_root(1, j)) &&
          (find_root(2, i) != find_root(2, j))) {
        num++;
        ans.push_back({i + 1, j + 1});
        connect_dis(1, i, j);
        connect_dis(2, i, j);
      }
    }
  }
  cout << num << '\n';
  for (auto i : ans) cout << i.first << ' ' << i.second << '\n';
}
