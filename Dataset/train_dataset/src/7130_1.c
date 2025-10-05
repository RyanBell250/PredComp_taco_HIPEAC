#include <bits/stdc++.h>
using namespace std;
const int N = 605;
long long A[N][N], M[N][N], P;
int n, m, msize, vis[N][N], G[N][N], inDeg[N], outDeg[N], src[N], tmn[N];
long long dfs(int x, int id) {
  if (vis[id][x]) return A[id][x];
  vis[id][x] = 1;
  for (int i = 1; i <= n; ++i)
    if (G[i][x]) A[id][x] += dfs(i, id) * G[i][x], A[id][x] %= P;
  return A[id][x];
}
int main() {
  scanf("%d%d%I64d", &n, &m, &P);
  for (int i = 1, a, b; i <= m; ++i) {
    scanf("%d%d", &a, &b), ++G[a][b];
    ++inDeg[b];
    ++outDeg[a];
  }
  for (int i = 1, nsize = 0; i <= n; ++i) {
    if (!inDeg[i]) src[++msize] = i;
    if (!outDeg[i]) tmn[++nsize] = i;
  }
  for (int i = 1, u; i <= msize; ++i) {
    u = src[i];
    A[u][u] = 1;
    for (int j = 1; j <= msize; ++j) dfs(tmn[j], u);
  }
  for (int i = 1; i <= msize; ++i)
    for (int j = 1; j <= msize; ++j) M[i][j] = A[src[i]][tmn[j]] % P;
  long long res(1);
  for (int i = 1; i <= msize; ++i) {
    for (int j = i + 1; j <= msize; ++j)
      while (M[j][i] != 0) {
        long long dv = M[i][i] ? M[j][i] / M[i][i] : 0;
        for (int k = 1; k <= msize; ++k) M[j][k] = (M[j][k] - dv * M[i][k]) % P;
        for (int k = 1; k <= msize; ++k) swap(M[i][k], M[j][k]);
        res *= -1;
      }
    res = res * M[i][i] % P;
  }
  res = (res + P) % P;
  printf("%I64d\n", res);
  return 0;
}
