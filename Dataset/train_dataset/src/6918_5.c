#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int dep[N], fa[N], c[N], k[N];
signed main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, d;
    scanf("%d %d", &n, &d);
    if (d > n * (n - 1) / 2) {
      puts("NO");
      continue;
    }
    int tmp = n - 1, mn = 0;
    for (int i = 1;; ++i) {
      if (tmp < (1 << i)) {
        mn += i * tmp;
        break;
      }
      tmp -= (1 << i), mn += i * (1 << i);
    }
    if (d < mn) {
      puts("NO");
      continue;
    }
    puts("YES");
    for (int i = 1; i <= n; ++i)
      fa[i] = i - 1, dep[i] = i - 1, c[i] = 1, k[i] = 0;
    c[n] = 0;
    int now = n * (n - 1) / 2;
    while (now > d) {
      int p, ok = 0, tmp;
      for (int i = 1; i <= n; ++i)
        if (!k[i] && !c[i]) {
          p = i;
          break;
        }
      for (int i = 1; i <= n; ++i)
        if (c[i] < 2 && dep[i] == dep[p] - 2) {
          tmp = i;
          ok = 1;
          break;
        }
      if (!ok) {
        k[p] = 1;
        continue;
      }
      --c[fa[p]], ++c[tmp], --dep[p], fa[p] = tmp, --now;
    }
    for (int i = 2; i <= n; ++i) printf("%d ", fa[i]);
    puts("");
  }
  return 0;
}
