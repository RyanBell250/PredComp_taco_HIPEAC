#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
bitset<N> A[N];
int n, m;
int ans[N], deg[N];
void init() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= n; ++j) A[i].reset(j);
  }
}
void print() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= n; ++j)
      if (A[i][j])
        putchar('1');
      else
        putchar('0');
    puts("");
  }
  puts("");
}
void Gauss() {
  for (int i = 0; i < n; ++i) {
    int k = i;
    for (int j = i; j < n; ++j) {
      if (A[j][i]) {
        k = j;
        break;
      }
    }
    if (A[k][i] == 0) continue;
    swap(A[i], A[k]);
    for (int k = 0; k < n; ++k)
      if (k != i && A[k][i]) A[k] ^= A[i];
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    init();
    for (int i = 0; i < n; ++i) deg[i] = 0;
    for (int i = 1; i <= m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      x--;
      y--;
      deg[x]++;
      deg[y]++;
      A[x].flip(x);
      A[x].flip(y);
      A[x].flip(n);
      A[y].flip(x);
      A[y].flip(y);
      A[y].flip(n);
    }
    bool flag = 1;
    for (int i = 0; i < n; ++i)
      if (deg[i] & 1) flag = 0;
    if (flag) {
      puts("1");
      for (int i = 1; i <= n; ++i) printf("1%c", (i == n) ? '\n' : ' ');
      continue;
    }
    Gauss();
    puts("2");
    for (int i = 0; i < n; ++i) ans[i] = 1;
    for (int i = 0; i < n; ++i)
      if (A[i][n]) ans[i] = 2;
    for (int i = 0; i < n; ++i)
      printf("%d%c", ans[i], (i == n - 1) ? '\n' : ' ');
  }
  return 0;
}
