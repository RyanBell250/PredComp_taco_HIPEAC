#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const long long INF = 0x3f3f3f3f3f3f3f3f;
string s[maxn];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m;
int cal(int x, int y) {
  int cnt = 0;
  for (int i = 0; i < 4; i++) {
    int nxtx = x + dx[i], nxty = y + dy[i];
    if (nxtx < 1 || nxtx > n || nxty < 1 || nxty > m) continue;
    if (s[nxtx][nxty] == '.') cnt++;
  }
  return cnt;
}
bool ck(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > m) return false;
  if (s[x][y] != '.') return false;
  int cnt = cal(x, y);
  if (cnt > 1) return false;
  return true;
}
void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    s[i] = ' ' + s[i];
  }
  pair<int, int> st;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == 'L') {
        st = {i, j};
        break;
      }
    }
  }
  queue<pair<int, int> > q;
  q.push({st});
  while (!q.empty()) {
    pair<int, int> u = q.front();
    q.pop();
    int x = u.first, y = u.second;
    for (int i = 0; i < 4; i++) {
      int nxtx = x + dx[i], nxty = y + dy[i];
      if (ck(nxtx, nxty)) {
        s[nxtx][nxty] = '+';
        q.push({nxtx, nxty});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%c", s[i][j]);
    }
    puts("");
  }
}
int main() {
  clock_t t1 = clock();
  int T;
  scanf("%d", &T);
  while (T--) solve();
end:
  cerr << "Time used " << clock() - t1 << " ms" << endl;
  return 0;
}
