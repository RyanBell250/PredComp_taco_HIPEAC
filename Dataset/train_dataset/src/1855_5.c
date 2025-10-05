#include <bits/stdc++.h>
int n, d, c[55], f[500010];
int main() {
  int i, j, sum, ans1, ans2;
  scanf("%d%d", &n, &d);
  sum = 0;
  for (i = 1; i <= n; ++i) {
    scanf("%d", c + i);
    sum += c[i];
  }
  memset(f, 0, sizeof f);
  f[0] = 1;
  for (i = 1; i <= n; ++i)
    for (j = sum; j >= c[i]; --j) f[j] |= f[j - c[i]];
  ans1 = 0;
  ans2 = 0;
  while (ans1 < sum) {
    for (j = ans1 + d <= sum ? ans1 + d : sum; j > ans1; --j)
      if (f[j]) break;
    if (j <= ans1) break;
    ans1 = j;
    ++ans2;
  }
  printf("%d %d", ans1, ans2);
  fclose(stdin);
  fclose(stdout);
  return 0;
}
