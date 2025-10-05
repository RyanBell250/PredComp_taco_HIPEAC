#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int n, p[N], mn[N];
long long a[N];
void down(int x, long long v) {
  a[x] -= v;
  for (x--; x != 1; x /= mn[x]) a[mn[x]] += v;
}
int main() {
  for (int i = (int)(2); i <= (int)(N - 1); i++)
    if (!mn[i])
      for (int j = (int)(1); j <= (int)((N - 1) / i); j++)
        if (!mn[i * j]) mn[i * j] = i;
  scanf("%d", &n);
  for (int i = (int)(1); i <= (int)(n); i++) {
    scanf("%d", &p[i]);
    scanf("%lld", &a[p[i]]);
  }
  long long T, mn;
  scanf("%lld", &T);
  mn = min(20ll, T);
  T -= mn;
  for (int j = (int)(1); j <= (int)(mn); j++)
    for (int i = (int)(2); i <= (int)(N - 1); i++)
      if (a[i]) down(i, 1);
  for (int i = (int)(N - 1); i >= (int)(2); i--)
    if (a[i]) down(i, min(a[i], T));
  int cnt = 0;
  for (int i = (int)(2); i <= (int)(N - 1); i++)
    if (a[i]) cnt++;
  printf("%d\n", cnt);
  for (int i = (int)(2); i <= (int)(N - 1); i++)
    if (a[i]) printf("%d %lld\n", i, a[i]);
}
