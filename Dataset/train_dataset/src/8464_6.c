#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 7;
int r, g;
int f[2][200200];
int maxSum(int x, int h) {
  int res = 0;
  for (int i = (h), _a = (1); i >= _a; i = i - 1)
    if (x >= i) {
      res += i;
      x -= i;
    }
  return (res);
}
bool canHave(int r, int g, int h) {
  if (h * (h + 1) / 2 - maxSum(r, h) <= g) return (true);
  if (h * (h + 1) / 2 - maxSum(g, h) <= r) return (true);
  return (false);
}
void init(void) { cin >> r >> g; }
int findH(void) {
  int L = 1;
  int R = 1010;
  while (true) {
    if (L == R) return (R);
    if (R - L == 1) return (canHave(r, g, R) ? R : L);
    int M = (L + R) >> 1;
    if (canHave(r, g, M))
      L = M;
    else
      R = M - 1;
  }
}
inline void add(int &x, const int &y) {
  x += y;
  if (x >= mod) x -= mod;
}
void process(void) {
  int h = findH();
  cerr << h << endl;
  f[0][0] = 1;
  for (int i = 0, _n = (h); i < _n; i = i + 1) {
    int cur = i & 1;
    int next = cur ^ 1;
    memset(f[next], 0, sizeof f[next]);
    for (int j = 0, _n = (r + 1); j < _n; j = j + 1)
      if (f[cur][j] > 0) {
        add(f[next][j], f[cur][j]);
        if (j + i + 1 <= r) add(f[next][j + i + 1], f[cur][j]);
      }
  }
  int res = 0;
  for (int j = 0, _n = (r + 1); j < _n; j = j + 1)
    if (h * (h + 1) / 2 - j <= g) add(res, f[h & 1][j]);
  printf("%d", res);
}
int main(void) {
  init();
  process();
  return 0;
}
