#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int M = 100005;
struct Point {
  int x, y;
};
int n, m, k;
char G[N][N];
int L[N][N], R[N][N], U[N][N], D[N][N];
char dir[M];
int len[M];
bool flag[26];
Point pos[26];
string res;
void Test(int K[N][N]) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (K[i][j] != -1) cout << ' ';
      cout << K[i][j] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
bool test(Point p) {
  int i;
  for (i = 0; i < k; i++) {
    switch (dir[i]) {
      case 'N':
        if (p.x - U[p.x][p.y] < len[i]) return false;
        p.x -= len[i];
        break;
      case 'S':
        if (D[p.x][p.y] - p.x < len[i]) return false;
        p.x += len[i];
        break;
      case 'W':
        if (p.y - L[p.x][p.y] < len[i]) return false;
        p.y -= len[i];
        break;
      case 'E':
        if (R[p.x][p.y] - p.y < len[i]) return false;
        p.y += len[i];
        break;
    }
  }
  return true;
}
int main() {
  int i, j, x, y;
  cin >> n >> m;
  for (i = 0; i < n; i++) cin >> G[i];
  memset(L, -1, sizeof(L));
  memset(R, -1, sizeof(R));
  memset(U, -1, sizeof(U));
  memset(D, -1, sizeof(D));
  memset(flag, 0, sizeof(flag));
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (G[i][j] >= 'A' && G[i][j] <= 'Z') {
        flag[G[i][j] - 'A'] = 1;
        pos[G[i][j] - 'A'].x = i;
        pos[G[i][j] - 'A'].y = j;
      }
      if (G[i][j] != '#') {
        if (L[i][j] == -1) {
          for (y = j; y < m && G[i][y] != '#'; y++) L[i][y] = j;
        }
        if (U[i][j] == -1) {
          for (x = i; x < n && G[x][j] != '#'; x++) U[x][j] = i;
        }
        if (j + 1 == m || G[i][j + 1] == '#') {
          for (y = j; y >= 0 && G[i][y] != '#'; y--) R[i][y] = j;
        }
        if (i + 1 == n || G[i + 1][j] == '#') {
          for (x = i; x >= 0 && G[x][j] != '#'; x--) D[x][j] = i;
        }
      }
    }
  }
  cin >> k;
  for (i = 0; i < k; i++) cin >> dir[i] >> len[i];
  for (i = 0; i < 26; i++) {
    if (flag[i] && test(pos[i])) res.push_back('A' + i);
  }
  if (res.size())
    cout << res << endl;
  else
    cout << "no solution" << endl;
  return 0;
}
