#include <bits/stdc++.h>
using namespace std;
const int mo = 998244353;
const int N = 1005, M = 65;
vector<pair<int, int> > vec[N];
int n, m, a[N], ava[5][5];
int tr[35][M][M];
int trco[M][5];
int f[2][M], g[2][5];
void work_trans(int dis) {
  for (int i = (int)(0); i <= (int)(29); i++)
    if (dis & (1 << i)) {
      for (int j = (int)(0); j <= (int)(63); j++) f[1][j] = 0;
      for (int j = (int)(0); j <= (int)(63); j++)
        for (int k = (int)(0); k <= (int)(63); k++)
          f[1][k] = (f[1][k] + 1ll * f[0][j] * tr[i][j][k]) % mo;
      for (int j = (int)(0); j <= (int)(63); j++) f[0][j] = f[1][j];
    }
}
int main() {
  scanf("%d", &n);
  for (int i = (int)(1); i <= (int)(n); i++) scanf("%d", &a[i]);
  scanf("%d", &m);
  for (int i = (int)(1); i <= (int)(m); i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    vec[x].push_back(pair<int, int>(y, c));
  }
  for (int i = (int)(0); i <= (int)(2); i++)
    for (int j = (int)(0); j <= (int)(2); j++) scanf("%d", &ava[i][j]);
  for (int i = (int)(0); i <= (int)(3); i++)
    for (int j = (int)(0); j <= (int)(3); j++)
      for (int k = (int)(0); k <= (int)(3); k++)
        for (int c = (int)(0); c <= (int)(2); c++) {
          int sta = 0, l = 0;
          if (ava[c][0]) sta |= 1 << k;
          if (ava[c][1]) sta |= 1 << j;
          if (ava[c][2]) sta |= 1 << i;
          for (; sta & (1 << l); l++)
            ;
          tr[0][i * 16 + j * 4 + k][j * 16 + k * 4 + l]++;
          trco[i * 16 + j * 4 + k][c] = j * 16 + k * 4 + l;
        }
  for (int T = (int)(1); T <= (int)(30); T++)
    for (int i = (int)(0); i <= (int)(63); i++)
      for (int j = (int)(0); j <= (int)(63); j++)
        for (int k = (int)(0); k <= (int)(63); k++)
          tr[T][i][k] =
              (tr[T][i][k] + 1ll * tr[T - 1][i][j] * tr[T - 1][j][k]) % mo;
  g[0][0] = 1;
  for (int i = (int)(1); i <= (int)(n); i++) {
    sort(vec[i].begin(), vec[i].end());
    for (int j = (int)(0); j <= (int)(63); j++) f[0][j] = (j == 63);
    int lasp = 0;
    for (int j = (int)(0); j <= (int)(vec[i].size() - 1); j++) {
      int dis = vec[i][j].first - lasp - 1;
      int co = vec[i][j].second - 1;
      work_trans(dis);
      for (int j = (int)(0); j <= (int)(63); j++) f[1][j] = 0;
      for (int j = (int)(0); j <= (int)(63); j++)
        f[1][trco[j][co]] = (f[1][trco[j][co]] + f[0][j]) % mo;
      for (int j = (int)(0); j <= (int)(63); j++) f[0][j] = f[1][j];
      lasp = vec[i][j].first;
    }
    work_trans(a[i] - lasp);
    for (int j = (int)(0); j <= (int)(3); j++) g[1][j] = 0;
    for (int j = (int)(0); j <= (int)(3); j++)
      for (int k = (int)(0); k <= (int)(63); k++)
        g[1][j ^ (k & 3)] = (g[1][j ^ (k & 3)] + 1ll * g[0][j] * f[0][k]) % mo;
    for (int j = (int)(0); j <= (int)(3); j++) g[0][j] = g[1][j];
  }
  printf("%d\n", g[0][0]);
}
