#include <bits/stdc++.h>
using namespace std;
int base[100005], s, a[100005];
int find(int a, int b) {
  if (a == b) return a;
  if (a >= b * 2)
    return find(a / 2, b);
  else if (b >= a * 2)
    return find(a, b / 2);
  else
    return find(a / 2, b / 2);
}
int cal(int x, int y) {
  int l = 0, r = 20, mid, t;
  while (l < r) {
    mid = (l + r) >> 1;
    if (base[x >> mid] > base[y])
      l = mid + 1;
    else
      r = mid;
  }
  x >>= l;
  return l + (int)log2(max(x, y) / min(x, y));
}
int n, i, ans, sum;
int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if (i == 1)
      s = a[1];
    else
      s = find(s, a[i]);
  }
  for (i = 1; i <= 100000; i++)
    if (i % 2 == 1)
      base[i] = i;
    else
      base[i] = base[i / 2];
  ans = 1000000000;
  while (s <= 100000) {
    sum = 0;
    for (i = 1; i <= n; i++) sum += cal(a[i], s);
    if (sum < ans) ans = sum;
    s <<= 1;
  }
  printf("%d\n", ans);
}
