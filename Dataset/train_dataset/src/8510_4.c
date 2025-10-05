#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int n, m, k, a[15][15], b[15][15], arrange[15][15];
unsigned int mask[15][15];
inline bool getbit(unsigned int x, int pos) { return (x >> pos) & 1; }
inline void flipbit(unsigned int& x, int pos) { x ^= 1 << pos; }
int count(int used) {
  static int ai[15], bi[15];
  int cnt = 0;
  memset(ai, -1, sizeof(ai));
  memset(bi, -1, sizeof(bi));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (a[i][j] != 0) {
        if (ai[a[i][j]] != -1 && ai[a[i][j]] != b[i][j]) return 0;
        if (bi[b[i][j]] != -1 && bi[b[i][j]] != a[i][j]) return 0;
        if (ai[a[i][j]] == -1) {
          cnt++;
          ai[a[i][j]] = b[i][j];
          bi[b[i][j]] = a[i][j];
        }
      }
    }
  assert(used >= cnt);
  return arrange[k - cnt][used - cnt];
}
int res;
void dfs(int r, int c, int used) {
  if (used > k) return;
  if (r >= n) {
    res += count(used);
    if (res > MOD) res -= MOD;
    return;
  }
  if (c >= m) {
    dfs(r + 1, 0, used);
    return;
  }
  unsigned int curr = 0u;
  if (r != 0) curr |= mask[r - 1][c];
  if (c != 0) curr |= mask[r][c - 1];
  mask[r][c] = curr;
  for (int i = 1; i <= used + 1; i++)
    if (!getbit(curr, i)) {
      b[r][c] = i;
      flipbit(mask[r][c], i);
      dfs(r, c + 1, max(used, i));
      flipbit(mask[r][c], i);
    }
}
int main() {
  for (int i = 0; i <= 10; i++) {
    arrange[i][0] = 1;
    for (int j = 1; j <= i; j++)
      arrange[i][j] = arrange[i][j - 1] * (i - j + 1);
  }
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      scanf("%d", a[i] + j);
    }
  if (n + m > k + 1) {
    printf("%d\n", 0);
    return 0;
  }
  dfs(0, 0, 0);
  printf("%d\n", res);
  return 0;
}
