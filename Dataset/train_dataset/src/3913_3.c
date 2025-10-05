#include <bits/stdc++.h>
using namespace std;
int a[105], n;
long long k, dm, mm;
void check(int dn) {
  int i;
  long long mn(n);
  for (i = 0; i < n; ++i) mn += a[i] / dn;
  if (dn * mn <= k) {
    dm = dn;
    mm = mn;
  }
}
int main() {
  int i, j, t(0);
  set<int> d;
  scanf("%d%I64d", &n, &k);
  for (i = 0; i < n; ++i) {
    scanf("%d", a + i);
    k += a[i];
    d.insert(a[i]--);
    if (t < a[i]) t = a[i];
    for (j = 1; j <= int(floor(sqrt(a[i] + 0.1)) + 0.1); ++j)
      d.insert(a[i] / j + 1);
  }
  for (i = 1; i <= int(floor(sqrt(a[i] + 0.1)) + 0.1) + 1; ++i) d.insert(i);
  for (const auto &x : d) check(x);
  if (dm == *d.rbegin())
    dm = k / mm;
  else
    dm = min(k / mm, *++d.find(dm) - 1ll);
  printf("%I64d\n", dm);
  return 0;
}
