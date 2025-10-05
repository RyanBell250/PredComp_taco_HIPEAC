#include <bits/stdc++.h>
using namespace std;
int n, m;
int rows[7];
int cols[22];
vector<int> pop[32];
char dp[32][22][11][11][11][11][11];
int xx[5];
int arr[6][22];
char solve1(int lmsk, int ccol, int a, int b, int c, int d, int e) {
  if (dp[lmsk][ccol][a][b][c][d][e] != 0) return dp[lmsk][ccol][a][b][c][d][e];
  if (ccol == m + 1) {
    if (a == rows[1] && b == rows[2] && c == rows[3] && d == rows[4] &&
        e == rows[5]) {
      return dp[lmsk][ccol][a][b][c][d][e] = 'a';
    }
    return dp[lmsk][ccol][a][b][c][d][e] = 'b';
  }
  int X = cols[ccol];
  for (int t : pop[X]) {
    memset(xx, 0, sizeof(xx));
    xx[0] = a;
    xx[1] = b;
    xx[2] = c;
    xx[3] = d;
    xx[4] = e;
    for (int z = 0; z < n; z++) {
      if (!((1 << z) & t)) continue;
      if ((((1 << z) & t) > 0) != (((1 << z) & lmsk) > 0)) {
        xx[z]++;
      }
    }
    int R = solve1(t, ccol + 1, xx[0], xx[1], xx[2], xx[3], xx[4]);
    if (R != 'b') {
      for (int r = 0; r < n; r++) {
        arr[r + 1][ccol] = ((t & (1 << r)) > 0);
      }
      return dp[lmsk][ccol][a][b][c][d][e] = 'a';
    }
  }
  return dp[lmsk][ccol][a][b][c][d][e] = 'b';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  for (int g = 0; g < (1 << n); g++) {
    int cn = 0;
    for (int t = 0; t < n; t++) {
      if (!((1 << t) & g)) continue;
      cn++;
      while (t < n && ((1 << t) & g)) t++;
    }
    pop[cn].push_back(g);
  }
  for (int g = 1; g <= n; g++) cin >> rows[g];
  for (int g = 1; g <= m; g++) cin >> cols[g];
  solve1(0, 1, 0, 0, 0, 0, 0);
  for (int g = 1; g <= n; g++) {
    for (int y = 1; y <= m; y++) {
      if (arr[g][y] == 1)
        cout << '*';
      else
        cout << '.';
    }
    cout << '\n';
  }
  return 0;
}
