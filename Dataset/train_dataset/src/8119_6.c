#include <bits/stdc++.h>
using namespace std;
int getBit(unsigned int, int);
void setBit(unsigned int &, int);
void clearBit(unsigned int &, int);
void reverseBit(unsigned int &, int);
int INF = 1e9;
int m, n, k;
int sx, sy;
string a[20];
int f[20][20][1 << 8][1 << 8];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
vector<pair<int, int> > bomb;
pair<int, int> treasure[8];
int v[8];
int res;
typedef struct _Element {
  int x;
  int y;
  unsigned int mb;
  unsigned int mt;
  _Element(int _x, int _y, unsigned int _mb, unsigned int _mt) {
    x = _x;
    y = _y;
    mb = _mb;
    mt = _mt;
  }
} Element;
void Solve();
int main() {
  cin >> m >> n;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
    for (int j = 0; j < n; j++) {
      if ('0' <= a[i][j] && a[i][j] <= '9') {
        k = max(k, a[i][j] - '0');
        a[i][j] = '0' + int(a[i][j] - '0' - 1);
        treasure[a[i][j] - '0'].first = i;
        treasure[a[i][j] - '0'].second = j;
      } else if (a[i][j] == 'S') {
        sx = i;
        sy = j;
        a[i][j] = '.';
      } else if (a[i][j] == 'B') {
        bomb.push_back(pair<int, int>(i, j));
      }
    }
  }
  for (int i = 0; i < k; i++) {
    cin >> v[i];
  }
  Solve();
  return 0;
}
int getBit(unsigned int x, int i) { return ((x & (1 << i)) != 0); }
void setBit(unsigned int &x, int i) { x = x | (1 << i); }
void clearBit(unsigned int &x, int i) { x = x & (~(1 << i)); }
void reverseBit(unsigned int &x, int i) {
  if (getBit(x, i)) {
    clearBit(x, i);
  } else {
    setBit(x, i);
  }
}
bool Intersect(int x0, int y0, int x1, int y1, int x2, int y2) {
  int x3 = x2 + 1;
  int y3 = n * 2;
  int A01, A23, B01, B23, C01, C23;
  A01 = y0 - y1;
  B01 = x1 - x0;
  C01 = (x0 * y1 - x1 * y0);
  A23 = y2 - y3;
  B23 = x3 - x2;
  C23 = (x2 * y3 - x3 * y2);
  int f01 = (A23 * x0 + B23 * y0 + C23) * (A23 * x1 + B23 * y1 + C23);
  int f23 = (A01 * x2 + B01 * y2 + C01) * (A01 * x3 + B01 * y3 + C01);
  return (f01 < 0 && f23 < 0);
}
void Solve() {
  queue<Element> q;
  Element s(sx, sy, 0, 0);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      for (int b1 = 0; b1 < (1 << 8); b1++)
        for (int b2 = 0; b2 < (1 << 8); b2++) {
          f[i][j][b1][b2] = INF;
        }
  f[sx][sy][0][0] = 0;
  q.push(s);
  while (!q.empty()) {
    Element tx = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      Element qx(tx.x + dx[i], tx.y + dy[i], tx.mb, tx.mt);
      if (!(0 <= qx.x && qx.x < m && 0 <= qx.y && qx.y < n)) continue;
      if (a[qx.x][qx.y] != '.') continue;
      for (int j = 0; j < k; j++) {
        if (Intersect(2 * tx.x, 2 * tx.y, 2 * qx.x, 2 * qx.y,
                      2 * treasure[j].first, 2 * treasure[j].second)) {
          reverseBit(qx.mt, j);
        }
      }
      for (int j = 0; j < bomb.size(); j++) {
        if (Intersect(2 * tx.x, 2 * tx.y, 2 * qx.x, 2 * qx.y, 2 * bomb[j].first,
                      2 * bomb[j].second)) {
          reverseBit(qx.mb, j);
        }
      }
      if (f[qx.x][qx.y][qx.mb][qx.mt] > f[tx.x][tx.y][tx.mb][tx.mt] + 1) {
        f[qx.x][qx.y][qx.mb][qx.mt] = f[tx.x][tx.y][tx.mb][tx.mt] + 1;
        q.push(qx);
      }
    }
  }
  int res = 0;
  for (int b2 = 1; b2 < (1 << k); b2++) {
    int total = 0;
    for (int t = 0; t < k; t++)
      if (getBit(b2, t)) {
        total += v[t];
      }
    res = max(res, total - f[sx][sy][0][b2]);
  }
  cout << res << endl;
}
