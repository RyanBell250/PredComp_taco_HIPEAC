#include <bits/stdc++.h>
using namespace std;
const int MAX = 100010;
int n, m, x, y;
int k;
bool top[MAX], bottom[MAX], lft[MAX], rgt[MAX];
int getCnt() {
  bool res = x % 2 == y % 2;
  int ret = 0;
  for (int i = 0; i < (int)(m); i++) ret += (0 == i % 2) == res;
  for (int i = 0; i < (int)(m); i++) ret += ((n - 1) % 2 == i % 2) == res;
  for (int i = (int)(1); i < (int)(n - 1); i++) ret += (0 == i % 2) == res;
  for (int i = (int)(1); i < (int)(n - 1); i++)
    ret += ((m - 1) % 2 == i % 2) == res;
  return ret;
}
long long solve() {
  int cnt = getCnt();
  long long ret = 0;
  for (int _ = 0; _ < (int)(3000000); _++) {
    if (x == 0) {
      if (!top[y]) --cnt;
      top[y] = true;
    } else if (x == n - 1) {
      if (!bottom[y]) --cnt;
      bottom[y] = true;
    } else if (y == 0) {
      if (!lft[x]) --cnt;
      lft[x] = true;
    } else {
      if (!rgt[x]) --cnt;
      rgt[x] = true;
    }
    if (cnt == 0) break;
    if (k == 0) {
      if (x == n - 1 && y == m - 1)
        k = 3;
      else if (x == n - 1)
        k = 2;
      else if (y == m - 1)
        k = 1;
    } else if (k == 1) {
      if (x == n - 1 && y == 0)
        k = 2;
      else if (x == n - 1)
        k = 3;
      else if (y == 0)
        k = 0;
    } else if (k == 2) {
      if (x == 0 && y == m - 1)
        k = 1;
      else if (x == 0)
        k = 0;
      else if (y == m - 1)
        k = 3;
    } else {
      if (x == 0 && y == 0)
        k = 0;
      else if (x == 0)
        k = 1;
      else if (y == 0)
        k = 2;
    }
    if (k == 0) {
      int d = min(n - 1 - x, m - 1 - y);
      ret += d;
      x += d;
      y += d;
    } else if (k == 1) {
      int d = min(n - 1 - x, y);
      ret += d;
      x += d;
      y -= d;
    } else if (k == 2) {
      int d = min(x, m - 1 - y);
      ret += d;
      x -= d;
      y += d;
    } else {
      int d = min(x, y);
      ret += d;
      x -= d;
      y -= d;
    }
  }
  if (cnt) return -1;
  return ret;
}
int main() {
  cin >> n >> m >> x >> y;
  string dir;
  cin >> dir;
  if (dir[0] == 'U') k = 1;
  k <<= 1;
  if (dir[1] == 'L') k |= 1;
  --x, --y;
  long long ret = solve();
  if (ret != -1) ++ret;
  cout << ret << endl;
  return 0;
}
