#include <bits/stdc++.h>
const int mod = 1e9 + 7;
using namespace std;
inline int read() {
  int x = 0, y = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') y = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return y ? -x : x;
}
template <typename T>
inline T read() {
  T x = 0;
  int y = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') y = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return y ? -x : x;
}
int en[205], line[205], son[205][20], pre[205], L[205], R[205], s[205],
    f[2][2][2][205][505], cnt = 1, m, K;
void insert(int len, int v) {
  int node = 1;
  for ( int i = 1; i <= len; ++i) {
    if (!son[node][s[i]]) son[node][s[i]] = ++cnt;
    node = son[node][s[i]];
  }
  en[node] += v;
}
void build() {
  int head = 0, tail = 1;
  line[1] = 1;
  for ( int i = 0; i < m; ++i) son[0][i] = 1;
  while (head < tail) {
    int node = line[++head], x;
    en[node] += en[pre[node]];
    for ( int i = 0; i < m; ++i) {
      x = son[node][i];
      if (x)
        pre[x] = son[pre[node]][i], line[++tail] = x;
      else
        son[node][i] = son[pre[node]][i];
    }
  }
}
inline void add(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
int solve(int *tp) {
  int len = tp[0], ans = 0;
  memset(f, 0, sizeof f);
  f[len & 1][1][1][1][0] = 1;
  for ( int i = len; i; --i)
    for ( int j = 0; j < 2; ++j)
      for ( int k = 0; k < 2; ++k)
        for ( int l = 1; l <= cnt; ++l)
          for ( int p = 0; p <= K; ++p) {
            if (!f[i & 1][j][k][l][p]) continue;
            for ( int q = j ? tp[i] : m - 1; ~q; --q)
              if ((k && !q) || p + en[son[l][q]] <= K)
                add(f[i & 1 ^ 1][j && q == tp[i]][k && !q]
                     [(k && !q) ? l : son[l][q]]
                     [(k && !q) ? p : p + en[son[l][q]]],
                    f[i & 1][j][k][l][p]);
            f[i & 1][j][k][l][p] = 0;
          }
  for ( int i = 1; i <= cnt; ++i)
    for ( int j = 0; j <= K; ++j)
      add(ans, (f[0][0][0][i][j] + f[0][1][0][i][j]) % mod);
  return ans;
}
signed main() {
  int n = read();
  m = read(), K = read(), L[0] = read();
  for ( int i = 1; i <= L[0]; ++i) L[L[0] - i + 1] = read();
  R[0] = read();
  for ( int i = 1; i <= R[0]; ++i) R[R[0] - i + 1] = read();
  while (n--) {
    int len = read();
    for ( int i = 1; i <= len; ++i) s[i] = read();
    insert(len, read());
  }
  build();
  int node = 1, ans, sum = 0;
  for ( int i = L[0]; i; --i) node = son[node][L[i]], sum += en[node];
  ans = sum <= K;
  printf("%d\n", (solve(R) - solve(L) + ans + mod) % mod);
}
