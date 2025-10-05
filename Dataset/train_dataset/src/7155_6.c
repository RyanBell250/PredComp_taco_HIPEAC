#include <bits/stdc++.h>
using namespace std;
int count(int S) {
  int ret = 0;
  while (S) {
    ret += S & 1;
    S >>= 1;
  }
  return ret;
}
int n, m, d, cnt[30], a[100010], mark[1 << 21];
int main() {
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 0; i < m; i++) {
    int k;
    scanf("%d", &k);
    while (k--) {
      int t;
      scanf("%d", &t);
      a[t] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]++;
    if (i < d) continue;
    if (i > d) cnt[a[i - d]]--;
    int S = 0;
    for (int j = 0; j < m; j++)
      if (!cnt[j]) S += 1 << j;
    mark[S] = 1;
  }
  int ans = 1 << 30;
  for (int S = (1 << m) - 1; S; S--) {
    if (!mark[S]) {
      ans = min(ans, count(S));
      continue;
    }
    for (int i = 0; i < m; i++)
      if ((S >> i) & 1) mark[S ^ (1 << i)] = 1;
  }
  printf("%d\n", ans);
  return 0;
}
