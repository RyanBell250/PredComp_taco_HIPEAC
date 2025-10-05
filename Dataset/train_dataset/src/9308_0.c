#include <bits/stdc++.h>
using namespace std;
const int INF = (1 << 31) - 1;
const long long int LINF = (1LL << 63) - 1;
const int NMAX = 100000 + 5;
const int MMAX = 100000 + 5;
const int KMAX = 100000 + 5;
const int PMAX = 100000 + 5;
const int LMAX = 100000 + 5;
const int VMAX = 100000 + 5;
int N[4], T[4], K;
long long int start, maxstart;
long long int V[4][1005];
long long int m1, m2, m3;
int main() {
  int i, j, k, p, q, r;
  scanf("%d", &K);
  for (i = 1; i <= 3; i++) scanf("%d", &N[i]);
  for (i = 1; i <= 3; i++) scanf("%d", &T[i]);
  for (i = 1; i <= K; i++) {
    m1 = m2 = m3 = LINF;
    for (j = 1; j <= N[1]; j++)
      if (m1 >= V[1][j]) {
        m1 = V[1][j];
        p = j;
      }
    for (j = 1; j <= N[2]; j++)
      if (m2 >= V[2][j]) {
        m2 = V[2][j];
        q = j;
      }
    for (j = 1; j <= N[3]; j++)
      if (m3 >= V[3][j]) {
        m3 = V[3][j];
        r = j;
      }
    start = max(0LL, max(m1, max(m2 - T[1], m3 - T[1] - T[2])));
    V[1][p] = start + T[1];
    V[2][q] = start + T[1] + T[2];
    V[3][r] = start + T[1] + T[2] + T[3];
    maxstart = max(start, maxstart);
  }
  printf("%lld\n", maxstart + T[1] + T[2] + T[3]);
  return 0;
}
