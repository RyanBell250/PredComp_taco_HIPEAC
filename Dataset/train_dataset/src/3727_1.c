#include <bits/stdc++.h>
using namespace std;
template <class T>
bool uin(T &a, T b) {
  return a > b ? (a = b, true) : false;
}
template <class T>
bool uax(T &a, T b) {
  return a < b ? (a = b, true) : false;
}
const int maxn = 301;
string s[maxn][maxn], t[maxn][maxn];
string ss[maxn][maxn];
vector<pair<pair<int, int>, pair<int, int> > > q1, q2;
bool DEBUG = 0;
int n, m;
void debug_transfer(int x1, int y1, int x2, int y2) {
  assert(x1 == x2 || y1 == y2);
  assert(x1 != x2 || y1 != y2);
  assert(!ss[x1][y1].empty());
  char c = ss[x1][y1].back();
  ss[x1][y1].resize(ss[x1][y1].size() - 1);
  ss[x2][y2] = c + ss[x2][y2];
  for (int i = 0; i < (int)(n); ++i) {
    for (int j = 0; j < (int)(m); ++j) cerr << ss[i][j] << ' ';
    cerr << '\n';
  }
  cerr << '\n';
}
void transfer(int x1, int y1, int x2, int y2, bool rev = false) {
  if (x1 == x2 && y1 == y2) return;
  if (x1 == x2 || y1 == y2) {
    if (!rev)
      q1.push_back({{x1, y1}, {x2, y2}});
    else
      q2.push_back({{x2, y2}, {x1, y1}});
    return;
  }
  transfer(x1, y1, x1, y2, rev);
  transfer(x1, y2, x2, y2, rev);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);
  cout << fixed;
  cin >> n >> m;
  for (int i = 0; i < (int)(n); ++i)
    for (int j = 0; j < (int)(m); ++j) {
      cin >> s[i][j];
      ss[i][j] = s[i][j];
      reverse((s[i][j]).begin(), (s[i][j]).end());
    }
  for (int i = 0; i < (int)(n); ++i)
    for (int j = 0; j < (int)(m); ++j) cin >> t[i][j];
  for (int i = 1; i <= (int)(n - 1); ++i) {
    int c0 = 0, c1 = 0;
    for (int j = 0; j < (int)(2); ++j)
      for (auto w : s[i][j]) {
        if (j == w - '0')
          transfer(i, j, 0, j);
        else
          transfer(i, j, i, w - '0'), ++(j ? c0 : c1);
      }
    for (int j = 0; j < (int)(c0); ++j) transfer(i, 0, 0, 0);
    for (int j = 0; j < (int)(c1); ++j) transfer(i, 1, 0, 1);
  }
  {
    int c00 = 0, c11 = 0;
    for (int j = 0; j < (int)(2); ++j)
      for (auto w : s[0][j]) {
        if (j == w - '0') {
          ++(j ? c11 : c00);
          transfer(0, j, 1, j);
        } else
          transfer(0, j, 0, w - '0');
      }
    for (int j = 0; j < (int)(c00); ++j) transfer(1, 0, 0, 0);
    for (int j = 0; j < (int)(c11); ++j) transfer(1, 1, 0, 1);
  }
  for (int i = 0; i < (int)(n); ++i)
    for (int j = (int)(2); j <= (int)(m - 1); ++j) {
      for (auto w : s[i][j]) transfer(i, j, 0, w - '0');
    }
  for (int i = 1; i <= (int)(n - 1); ++i) {
    int c0 = 0, c1 = 0;
    for (int j = 0; j < (int)(2); ++j)
      for (auto w : t[i][j]) {
        if (j == w - '0')
          transfer(i, j, 0, j, 1);
        else
          transfer(i, j, i, w - '0', 1), ++(j ? c0 : c1);
      }
    for (int j = 0; j < (int)(c0); ++j) transfer(i, 0, 0, 0, 1);
    for (int j = 0; j < (int)(c1); ++j) transfer(i, 1, 0, 1, 1);
  }
  {
    int c00 = 0, c11 = 0;
    for (int j = 0; j < (int)(2); ++j)
      for (auto w : t[0][j]) {
        if (j == w - '0') {
          ++(j ? c11 : c00);
          transfer(0, j, 1, j, 1);
        } else
          transfer(0, j, 0, w - '0', 1);
      }
    for (int j = 0; j < (int)(c00); ++j) transfer(1, 0, 0, 0, 1);
    for (int j = 0; j < (int)(c11); ++j) transfer(1, 1, 0, 1, 1);
  }
  for (int i = 0; i < (int)(n); ++i)
    for (int j = (int)(2); j <= (int)(m - 1); ++j) {
      for (auto w : t[i][j]) transfer(i, j, 0, w - '0', 1);
    }
  cout << q1.size() + q2.size() << '\n';
  reverse((q2).begin(), (q2).end());
  for (auto w : q1) {
    cout << w.first.first + 1 << ' ' << w.first.second + 1 << ' '
         << w.second.first + 1 << ' ' << w.second.second + 1 << '\n';
    if (DEBUG)
      debug_transfer(w.first.first, w.first.second, w.second.first,
                     w.second.second);
  }
  for (auto w : q2) {
    cout << w.first.first + 1 << ' ' << w.first.second + 1 << ' '
         << w.second.first + 1 << ' ' << w.second.second + 1 << '\n';
    if (DEBUG)
      debug_transfer(w.first.first, w.first.second, w.second.first,
                     w.second.second);
  }
  if (DEBUG)
    for (int i = 0; i < (int)(n); ++i)
      for (int j = 0; j < (int)(m); ++j) assert(ss[i][j] == t[i][j]);
  return 0;
}
