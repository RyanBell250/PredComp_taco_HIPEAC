#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int n, m, x, y, vx, vy;
int vis[5 * MAXN];
int get(int x, int y) {
  if (x == 1) return y;
  if (y == m) return m + x - 1;
  if (x == n) return m + m + n - 1 - y;
  return m + m + n + n - 2 - x;
}
int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }
int main() {
  scanf("%d%d", &n, &m);
  scanf("%d%d", &x, &y);
  char str[5];
  scanf("%s", str);
  if (str[0] == 'D')
    vx = 1;
  else
    vx = -1;
  if (str[1] == 'R')
    vy = 1;
  else
    vy = -1;
  long long ans = 1, now = 0;
  memset(vis, 0, sizeof(vis));
  if (x == 1 || y == 1 || x == n || y == m) {
    now = 1;
    vis[get(x, y)] = 1;
  }
  while (now < m + n - 2) {
    if (x + vx <= 0 || x + vx > n) vx = -vx;
    if (y + vy <= 0 || y + vy > m) vy = -vy;
    int t =
        min(max((1 - x) / vx, (n - x) / vx), max((1 - y) / vy, (m - y) / vy));
    x = x + vx * t;
    y = y + vy * t;
    ans += t;
    int pos = get(x, y);
    if (!vis[pos])
      now++;
    else if (vis[pos] >= 2) {
      printf("-1");
      return 0;
    }
    vis[pos]++;
  }
  printf("%lld\n", ans);
}
