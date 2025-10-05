#include <bits/stdc++.h>
using namespace std;
long long ara[500005], pri[500005];
long long n, r, k;
bool cck(long long val) {
  long long i, j, p, q, x, y;
  long long tot = 0;
  memset(pri, 0, sizeof(pri));
  for (i = 1; i <= n; i++) {
    pri[max(1LL, i - r)] += ara[i];
    pri[min(n + 1, i + r + 1)] -= ara[i];
  }
  for (i = 1; i <= n; i++) {
    pri[i] += pri[i - 1];
    if (pri[i] < val) {
      x = val - pri[i];
      pri[i] += x;
      pri[min(n + 1, i + 2 * r + 1)] -= x;
      tot += x;
    }
    if (tot > k) return false;
  }
  return true;
}
int main() {
  long long i, j, p, q, x, y;
  cin >> n >> r >> k;
  for (i = 1; i <= n; i++) scanf("%lld", ara + i);
  long long st = 0, ed = 2000000000000000000LL, mid;
  while (st + 1 != ed) {
    mid = (st + ed) >> 1;
    if (cck(mid))
      st = mid;
    else
      ed = mid;
  }
  printf("%lld\n", st);
  return 0;
}
