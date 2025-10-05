#include <bits/stdc++.h>
using namespace std;
int G[10][310][310];
int T[310][310];
int tmp[310][310];
int n, m;
int f(int k) {
  for (int j = 1; j <= n; j++)
    for (int l = 1; l <= n; l++) T[j][l] = G[0][j][l];
  k--;
  for (int i = 0; (1 << i) <= k; i++)
    if ((1 << i) & k) {
      for (int j = 1; j <= n; j++)
        for (int l = 1; l <= n; l++) tmp[j][l] = -1e8;
      for (int j = 1; j <= n; j++)
        for (int l = 1; l <= n; l++) {
          for (int r = 1; r <= n; r++) {
            tmp[j][l] = max(tmp[j][l], T[j][r] + G[i][r][l]);
          }
        }
      for (int j = 1; j <= n; j++)
        for (int l = 1; l <= n; l++) T[j][l] = tmp[j][l];
    }
  for (int i = 1; i <= n; i++) {
    if (T[i][i] > 0) return 1;
  }
  return 0;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int t = 0; 1 << t <= n; t++)
    for (int j = 1; j <= n; j++)
      for (int l = 1; l <= n; l++) G[t][j][l] = -1e8;
  for (int i = 1; i <= n; i++) G[0][i][i] = 0;
  for (int i = 1, a, b, c, d; i <= m; i++) {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    G[0][a][b] = c;
    G[0][b][a] = d;
  }
  for (int t = 1; 1 << t <= n; t++) {
    for (int j = 1; j <= n; j++)
      for (int l = 1; l <= n; l++) {
        for (int k = 1; k <= n; k++)
          G[t][j][l] = max(G[t][j][l], G[t - 1][j][k] + G[t - 1][k][l]);
      }
  }
  int lo = 0, hi = n + 2, mi;
  while (lo < hi) {
    mi = (lo + hi) / 2;
    if (f(mi))
      hi = mi;
    else
      lo = mi + 1;
  }
  if (lo > n)
    printf("0\n");
  else
    cout << lo << endl;
  return 0;
}
