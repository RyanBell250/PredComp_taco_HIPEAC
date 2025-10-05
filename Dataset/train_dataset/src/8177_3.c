#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 1e9 + 7;
constexpr long long INFL = 1e18;
template <class L, class R>
ostream &operator<<(ostream &os, pair<L, R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &V) {
  os << "[";
  for (const auto &x : V) os << x << ", ";
  return os << "]";
}
const int N = 52;
int n, m, h, dp[N][N][N];
struct Restriction {
  int l, r, x, c;
  bool contain(int y, int h) { return l <= y and y <= r and x < h; }
} pen[N];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> h >> m;
  for (int i = 0; i < m; i++) {
    Restriction &R = pen[i];
    cin >> R.l >> R.r >> R.x >> R.c;
  }
  for (int len = 1; len <= n; len++) {
    for (int a = 1; a + len - 1 <= n; a++) {
      int b = a + len - 1;
      for (int _h = 0; _h <= h; _h++) {
        if (_h > 0) dp[a][b][_h] = dp[a][b][_h - 1];
        for (int piv = a; piv <= b; piv++) {
          int cost = 0;
          for (int i = 0; i < m; i++)
            if (a <= pen[i].l and pen[i].r <= b and pen[i].contain(piv, _h))
              cost += pen[i].c;
          dp[a][b][_h] =
              max(dp[a][b][_h],
                  dp[a][piv - 1][_h] + dp[piv + 1][b][_h] + _h * _h - cost);
        }
      }
    }
  }
  cout << dp[1][n][h] << "\n";
}
