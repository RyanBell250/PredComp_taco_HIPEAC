#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const int maxn = 5e5 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
int t;
int n, m;
int a[maxn], ans1[maxn], ans2[maxn];
int v[10000007];
int prime[10000007];
int cnt = 0;
void primes(int n) {
  memset(v, 0, sizeof v);
  for (int i = 2; i <= n; ++i) {
    if (!v[i]) {
      v[i] = i;
      prime[++cnt] = i;
    }
    for (int j = 1; j <= cnt; ++j) {
      if (prime[j] > v[i] || prime[j] > n / i) break;
      v[i * prime[j]] = prime[j];
    }
  }
}
int main() {
  primes(10000000);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    ans1[i] = ans2[i] = -1;
    int tmp1 = a[i], tmp2 = v[a[i]];
    while (tmp1 % tmp2 == 0) tmp1 /= tmp2;
    if (tmp1 != 1) {
      ans1[i] = tmp1;
      ans2[i] = a[i] / tmp1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d ", ans1[i]);
  }
  puts("");
  for (int i = 1; i <= n; ++i) {
    printf("%d ", ans2[i]);
  }
  puts("");
  return 0;
}
