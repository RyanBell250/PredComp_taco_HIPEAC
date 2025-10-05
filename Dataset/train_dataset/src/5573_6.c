#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
long long ex[15];
char str[16];
int len, bs[15];
long long g[1 << 14];
int su[1 << 14];
long long ans;
int change(char ch) {
  if (ch <= '9' && ch >= '0') return ch - '0';
  return ch - 'a' + 10;
}
int main() {
  int i, j, s, p, q;
  for (i = 0; i <= 14; i++) {
    if (i == 0)
      ex[i] = 1;
    else
      ex[i] = ex[i - 1] * 16;
  }
  scanf("%s", str);
  len = strlen(str);
  ans = inf;
  for (i = (1 << len) - 1; i >= 0; i--) {
    if (i & 1) continue;
    int sum = 0;
    for (j = 0; j < len; j++) bs[j] = change(str[j]);
    for (j = len - 1; j >= 0; j--) {
      if (i & (1 << j)) {
        bs[j - 1]++;
        bs[j] -= 16;
      }
      sum = sum + bs[j];
    }
    bool ok = (sum == 0);
    if (ok) {
      for (j = 0; j < len; j++) {
        if (bs[j] <= -16 || bs[j] >= 16) ok = false;
      }
    }
    if (ok) {
      if (ans < inf) {
        int bw;
        for (j = 0; j < len; j++) {
          bw = -bs[j];
          if (bw < 0) bw = 0;
          if (bw != ans / ex[len - 1 - j] % 16) break;
        }
        if (j >= len || bw > ans / ex[len - 1 - j] % 16) continue;
      }
      for (j = 0; j < (1 << len); j++) g[j] = inf;
      g[0] = su[0] = 0;
      for (j = 0; j < (1 << len); j++) {
        if (g[j] >= ans) continue;
        for (s = 0; s < len; s++) {
          if (!(j & (1 << s))) {
            su[j | (1 << s)] = su[j] + bs[s];
            if (su[j] >= 16 || su[j] < 0) continue;
            if (g[j | (1 << s)] > g[j] + ex[len - 1 - s] * su[j])
              g[j | (1 << s)] = g[j] + ex[len - 1 - s] * su[j];
          }
        }
      }
      if (ans > g[(1 << len) - 1]) ans = g[(1 << len) - 1];
    }
  }
  if (ans < inf) {
    for (i = 0; i < len; i++) {
      int vl = (ans / ex[len - 1 - i]) % 16;
      if (vl < 10)
        printf("%d", vl);
      else
        putchar(vl - 10 + 'a');
    }
    printf("\n");
  } else
    puts("NO");
  return 0;
}
