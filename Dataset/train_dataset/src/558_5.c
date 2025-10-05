#include <bits/stdc++.h>
using namespace std;
char buf[1 << 21], *p1 = buf, *p2 = buf;
template <class T>
void read(T &x) {
  x = 0;
  int c = getchar();
  int flag = 0;
  while (c < '0' || c > '9') flag |= (c == '-'), c = getchar();
  while (c >= '0' && c <= '9')
    x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
  if (flag) x = -x;
}
template <class T>
T _max(T a, T b) {
  return b < a ? a : b;
}
template <class T>
T _min(T a, T b) {
  return a < b ? a : b;
}
template <class T>
bool checkmax(T &a, T b) {
  return a < b ? a = b, 1 : 0;
}
template <class T>
bool checkmin(T &a, T b) {
  return b < a ? a = b, 1 : 0;
}
const int mod = 998244353;
int n, m, B;
int x[5], y[5];
int px[32], py[32], nx[32], ny[32];
int dp[31][20][20][20][20][2][2];
void add(int &a, int b) {
  a += b;
  (a >= mod) && (a -= mod);
}
void init() {
  read(n);
  read(m);
  for (int i = 0;; ++i)
    if ((1 << i) > m) {
      B = i;
      break;
    }
  for (int i = 0; i < n; ++i) read(x[i]), read(y[i]);
  for (int S = 0; S < (1 << n); ++S) {
    for (int i = 0; i < n; ++i)
      if (S >> i & 1) {
        if (x[i] < 0)
          nx[S] -= x[i];
        else
          px[S] += x[i];
        if (y[i] < 0)
          ny[S] -= y[i];
        else
          py[S] += y[i];
      }
  }
}
void solve() {
  int full = (1 << n) - 1;
  int lim_px = _max(1, px[full]);
  int lim_py = _max(1, py[full]);
  int lim_nx = _max(1, nx[full]);
  int lim_ny = _max(1, ny[full]);
  dp[0][0][0][0][0][0][0] = 1;
  for (int i = 0; i < B; ++i) {
    for (int pxc = 0; pxc < lim_px; ++pxc) {
      for (int pyc = 0; pyc < lim_py; ++pyc) {
        for (int nxc = 0; nxc < lim_nx; ++nxc) {
          for (int nyc = 0; nyc < lim_ny; ++nyc) {
            for (int gx = 0; gx < 2; ++gx) {
              for (int gy = 0; gy < 2; ++gy) {
                for (int S = 0; S <= full; ++S) {
                  int pxcc = pxc + px[S];
                  int pycc = pyc + py[S];
                  int nxcc = nxc + nx[S];
                  int nycc = nyc + ny[S];
                  if ((pxcc + nxcc) & 1) continue;
                  if ((pycc + nycc) & 1) continue;
                  int bit = m >> i & 1, xx = pxcc & 1, yy = pycc & 1;
                  int Newgx = gx, Newgy = gy;
                  if (xx == 0 && bit == 1) Newgx = 0;
                  if (xx == 1 && bit == 0) Newgx = 1;
                  if (yy == 0 && bit == 1) Newgy = 0;
                  if (yy == 1 && bit == 0) Newgy = 1;
                  pxcc >>= 1;
                  nxcc >>= 1;
                  pycc >>= 1;
                  nycc >>= 1;
                  add(dp[i + 1][pxcc][pycc][nxcc][nycc][Newgx][Newgy],
                      dp[i][pxc][pyc][nxc][nyc][gx][gy]);
                }
              }
            }
          }
        }
      }
    }
  }
  int ans = dp[B][0][0][0][0][0][0];
  add(ans, mod - 1);
  printf("%d\n", ans);
}
int main() {
  init();
  solve();
  return 0;
}
