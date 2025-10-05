#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e7 + 1;
bool p[N / 1000];
int i, j, prime[N / 1000], sz;
long long d[N];
int n, m, x, l, r;
int main() {
  int T = sqrt((double)N);
  for (i = 2; i <= T; i++)
    for (j = 2; j * i <= T; j++) p[j * i] = 1;
  for (i = 2; i <= T; i++)
    if (!p[i]) prime[sz++] = i;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &x);
    int tmp = x;
    for (j = 0; j < sz && prime[j] * prime[j] <= tmp; j++) {
      if (tmp % prime[j] == 0) {
        d[prime[j]]++;
        while (tmp % prime[j] == 0) tmp /= prime[j];
      }
    }
    if (tmp > 1) d[tmp]++;
  }
  for (i = 1; i < N; i++) d[i] += d[i - 1];
  scanf("%d", &m);
  while (m--) {
    scanf("%d %d", &l, &r);
    r = min(N - 1, r);
    l = min(l, r);
    printf("%d\n", d[r] - d[l - 1]);
  }
  return 0;
}
