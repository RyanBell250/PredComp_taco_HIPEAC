#include <bits/stdc++.h>
using namespace std;
long long sum[500005], mx[500005];
long long n, p, q, r;
long long ans;
struct note {
  int a, b, c;
} a[500005];
bool cmp(note i, note j) { return i.c > j.c; }
int main() {
  scanf("%I64d%I64d%I64d%I64d", &n, &p, &q, &r);
  for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
  for (int i = 1; i <= n; i++)
    mx[a[i].a] = max(mx[a[i].a], (long long)a[i].b + 1);
  for (int i = p; i >= 1; i--) mx[i] = max(mx[i + 1], mx[i]);
  for (int i = 1; i <= p; i++) sum[i] = sum[i - 1] + (q - mx[i]) + 1;
  long long ma = 1, mb = 1;
  sort(a + 1, a + n + 1, cmp);
  int wz = 1;
  for (int i = r; i >= 1; i--) {
    while (wz <= n && a[wz].c == i) {
      ma = max(ma, a[wz].a + 1ll);
      mb = max(mb, a[wz].b + 1ll);
      wz++;
    }
    if (ma > p || mb > q) break;
    int x = ma, y = p, ret = ma - 1;
    while (x <= y) {
      int mid = (x + y) >> 1;
      if (mx[mid] >= mb) {
        x = mid + 1;
        ret = mid;
      } else
        y = mid - 1;
    }
    ans += sum[ret] - sum[ma - 1] + 1ll * (p - ret) * (q - mb + 1);
  }
  cout << ans;
  return 0;
}
