#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000006;
const int T = 1000000;
int n, m, x, cnt, num;
int p[maxn], com[maxn], id[maxn];
long long t;
long long a[maxn], k[maxn], sos[maxn];
bool flag;
void ols(int n) {
  for ( int i = 2; i <= n; ++i) {
    if (!com[i]) p[++cnt] = com[i] = i, id[i] = cnt;
    for ( int j = 1; j <= cnt && i * p[j] <= n; ++j) {
      com[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}
int main() {
  ols(T);
  scanf("%d", &m);
  while (m--) scanf("%d", &x), scanf("%I64d", &a[id[x]]);
  scanf("%I64d", &t);
  for ( int i = 1; i <= cnt; ++i) k[i] = t;
  flag = true;
  while (flag) {
    flag = false;
    for ( int i = 1; i <= cnt; ++i)
      if (a[i]) {
        if (!k[i]) continue;
        t = min(a[i], k[i]);
        a[i] -= t, k[i] -= t;
        sos[i] += t - 1, flag = true;
        int tmp = p[i] - 1;
        while (tmp != 1) {
          int cur = id[com[tmp]];
          a[cur] += t;
          tmp /= com[tmp];
        }
      } else if (sos[i])
        --sos[i];
      else if (k[i])
        --k[i];
  }
  for ( int i = 1; i <= cnt; ++i) num += (bool)a[i];
  printf("%d\n", num);
  for ( int i = 1; i <= cnt; ++i)
    if (a[i]) printf("%d %I64d\n", p[i], a[i]);
  return 0;
}
