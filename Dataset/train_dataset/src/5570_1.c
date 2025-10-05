#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
map<int, int> mp[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int x, y, n, m, dx, dy;
  string s;
  cin >> n >> m >> x >> y;
  cin >> s;
  if (s[0] == 'U')
    dx = -1;
  else
    dx = 1;
  if (s[1] == 'L')
    dy = -1;
  else
    dy = 1;
  int tot = n + m - 2;
  int cnt = 0;
  long long ans = 1;
  if (x == 1 || x == n || y == 1 || y == m) {
    tot--;
    mp[x][y] = 1;
  }
  while (true) {
    cnt++;
    if (cnt >= 5e5) return 0 * puts("-1");
    int dis = INF;
    if (dx == 1)
      dis = min(dis, n - x);
    else
      dis = min(dis, x - 1);
    if (dy == 1)
      dis = min(dis, m - y);
    else
      dis = min(dis, y - 1);
    ans += dis;
    x += dx * dis;
    y += dy * dis;
    if (x == 1)
      dx = 1;
    else if (x == n)
      dx = -1;
    if (y == 1)
      dy = 1;
    else if (y == m)
      dy = -1;
    if (!mp[x][y]) {
      tot--;
      mp[x][y] = 1;
    }
    if (!tot) {
      cout << ans << endl;
      return 0;
    }
  }
  return 0;
}
