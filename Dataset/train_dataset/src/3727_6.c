#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize( \
    "O3,Ofast,no-stack-protector,unroll-loops,fast-math,-ffp-contract=off")
int n, m;
vector<pair<pair<int, int>, pair<int, int>>> ans;
string grd[400][400];
void in();
void solve();
void out();
void rvr();
void solv();
int main() {
  in();
  solve();
  out();
}
void in() {
  ios::sync_with_stdio(false);
  cout.tie(0);
  cin.tie(0);
  cin >> n >> m;
}
void input() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) cin >> grd[i][j];
}
void solve() {
  input();
  rvr();
  solv();
  input();
  int tmp = ans.size();
  solv();
  reverse(ans.begin() + tmp, ans.end());
  for (int i = tmp; i < ans.size(); i++) swap(ans[i].first, ans[i].second);
}
void out() {
  cout << ans.size() << '\n';
  for (auto i : ans)
    cout << i.first.first + 1 << ' ' << i.first.second + 1 << ' '
         << i.second.first + 1 << ' ' << i.second.second + 1 << '\n';
}
void solv() {
  for (int i = 1; i < n; i++)
    for (auto j : grd[i][0]) ans.push_back({{i, 0}, {0, 0}});
  for (int i = 1; i < m; i++)
    for (auto j : grd[0][i]) ans.push_back({{0, i}, {0, 0}});
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      for (auto k : grd[i][j]) {
        if (k == '0') {
          ans.push_back({{i, j}, {0, j}});
          if (j != 1) ans.push_back({{0, j}, {0, 1}});
        } else {
          ans.push_back({{i, j}, {i, 0}});
          if (i != 1) ans.push_back({{i, 0}, {1, 0}});
        }
      }
    }
  }
  for (auto k : grd[0][0]) {
    if (k == '0')
      ans.push_back({{0, 0}, {0, 1}});
    else
      ans.push_back({{0, 0}, {1, 0}});
  }
  for (int i = 1; i < n; i++)
    for (auto j : grd[i][0])
      if (j == '0')
        ans.push_back({{0, 0}, {0, 1}});
      else
        ans.push_back({{0, 0}, {1, 0}});
  for (int i = 1; i < m; i++)
    for (auto j : grd[0][i])
      if (j == '0')
        ans.push_back({{0, 0}, {0, 1}});
      else
        ans.push_back({{0, 0}, {1, 0}});
}
void rvr() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) reverse(grd[i][j].begin(), grd[i][j].end());
}
