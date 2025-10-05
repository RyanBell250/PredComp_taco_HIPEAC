#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
template <class T>
void chkmax(T& x, T y) {
  x = max(x, y);
}
int n, K, Mx;
int a[N * 2 + 40], tot[N * 2 + 40], pre[N * 2 + 40];
int sum[N * 2 + 40];
pair<long long, long long> tmp;
long long getSum(int l, int r) { return sum[r] - sum[l - 1]; }
void update(long long x) {
  if (tmp.first <= x) {
    tmp.second = tmp.first;
    tmp.first = x;
  } else
    chkmax(tmp.second, x);
}
bool check(long long x) {
  for (int y = 2; y <= Mx; y++) {
    long long mx = max(2ll, (x + y - 1) / y);
    if (mx > Mx) continue;
    tmp = {-1e17, -1e17};
    long long xcnt = 0, best2 = -1e17;
    for (int i = 0; i * y <= Mx; i++) {
      int a = y * i, b = y * i + y - 1;
      xcnt += getSum(a, b) * i;
      int j = pre[b];
      if (j && j >= a) {
        if (mx * 2 <= j) chkmax(best2, (j - 2 * mx) / y - i);
        if (mx <= j) {
          update((j - mx) / y - i);
          if (tot[j] > 1)
            update((j - mx) / y - i);
          else {
            j = pre[j - 1];
            if (j && j >= a && j >= mx) update((j - mx) / y - i);
          }
        }
      }
    }
    if (xcnt + max(best2, tmp.first + tmp.second) >= mx) return 1;
  }
  return 0;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    tot[a[i]]++;
    chkmax(Mx, a[i]);
  }
  for (int i = 1; i < N * 2 + 40; i++) {
    sum[i] = sum[i - 1] + tot[i];
    if (tot[i])
      pre[i] = i;
    else
      pre[i] = pre[i - 1];
  }
  long long ans = 4, l = 4, r = 1e17;
  while (l <= r) {
    long long mid = (l + r) >> 1;
    if (check(mid))
      l = mid + 1, ans = mid;
    else
      r = mid - 1;
  }
  printf("%lld\n", ans);
  return 0;
}
