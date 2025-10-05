#include <bits/stdc++.h>
using namespace std;
const long long inft = 1000000009LL * 12324;
const int mod = 1000000007;
const int MAXN = 42;
int a[MAXN], b[MAXN];
long long M[MAXN][MAXN], A[MAXN][MAXN], T[MAXN][MAXN];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < (n); ++i) scanf("%d", &a[i]);
  for (int i = 0; i < (n); ++i) scanf("%d", &b[i]);
  int bil, mi, co;
  for (int i = 0; i < (MAXN); ++i)
    for (int j = 0; j < (MAXN); ++j) M[i][j] = inft;
  for (int i = 0; i < (MAXN); ++i)
    for (int j = 0; j < (MAXN); ++j) A[i][j] = (i == j ? 0 : inft);
  for (int mask = 0; mask < (1 << n); ++mask) {
    bil = 0;
    mi = 0;
    co = 0;
    for (int j = 0; j < (n); ++j) {
      if ((1 << j) & mask) {
        bil++;
        co += a[j];
      } else {
        bil--;
        co += b[j];
      }
      mi = min(mi, bil);
    }
    for (int bb = 0; bb < (MAXN); ++bb)
      if (bb + mi >= 0 && bb + bil < MAXN) {
        M[bb][bb + bil] = min(M[bb][bb + bil], 1LL * co);
      }
  }
  while (m) {
    if (m % 2) {
      for (int i = 0; i < (MAXN); ++i)
        for (int j = 0; j < (MAXN); ++j) T[i][j] = inft;
      for (int i = 0; i < (MAXN); ++i)
        for (int j = 0; j < (MAXN); ++j)
          for (int k = 0; k < (MAXN); ++k)
            T[i][j] = min(T[i][j], A[i][k] + M[k][j]);
      for (int i = 0; i < (MAXN); ++i)
        for (int j = 0; j < (MAXN); ++j) A[i][j] = T[i][j];
    }
    m /= 2;
    for (int i = 0; i < (MAXN); ++i)
      for (int j = 0; j < (MAXN); ++j) T[i][j] = inft;
    for (int i = 0; i < (MAXN); ++i)
      for (int j = 0; j < (MAXN); ++j)
        for (int k = 0; k < (MAXN); ++k)
          T[i][j] = min(T[i][j], M[i][k] + M[k][j]);
    for (int i = 0; i < (MAXN); ++i)
      for (int j = 0; j < (MAXN); ++j) M[i][j] = T[i][j];
  }
  printf("%d\n", (int)A[0][0]);
}
int main() {
  int te = 1;
  for (int ti = 0; ti < (te); ++ti) solve();
  return 0;
}
