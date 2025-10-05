#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int r, g;
int memo[200005];
bool check(int k) {
  int rr = r, gg = g;
  for (int i = k; i; --i) {
    if (rr > gg) {
      if (rr < i) return 0;
      rr -= i;
    } else {
      if (gg < i) return 0;
      gg -= i;
    }
  }
  return 1;
}
inline void add(int& a, int& b) {
  a += b;
  if (a > mod) a -= mod;
}
int main() {
  ios_base::sync_with_stdio(0);
  while (cin >> r >> g) {
    if (r > g) swap(r, g);
    int lo = 1, hi = 1000, mi;
    while (lo < hi) {
      mi = (lo + hi + 1) >> 1;
      if (check(mi))
        lo = mi;
      else
        hi = mi - 1;
    }
    int total = hi * (hi + 1) / 2;
    int unused = r + g - total;
    memset(memo, 0, sizeof(memo));
    memo[0] = 1;
    for (int i = 1; i <= hi; ++i) {
      for (int j = r; j >= i; --j) {
        if (memo[j - i]) add(memo[j], memo[j - i]);
      }
    }
    int res = 0;
    for (int i = max(0, r - total); i <= min(r, unused); ++i)
      add(res, memo[r - i]);
    cout << res << "\n";
  }
  return 0;
}
