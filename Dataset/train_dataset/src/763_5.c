#include <bits/stdc++.h>
int iscomp[1000020];
int main() {
  int i, j;
  iscomp[0] = iscomp[1] = 1;
  for (i = 2; i < 1000020; ++i)
    if (!iscomp[i])
      for (j = i + i; j < 1000020; j += i) iscomp[j] = 1;
  int primesto[1000020];
  primesto[0] = primesto[1] = 0;
  for (i = 2; i < 1000020; ++i)
    if (!iscomp[i])
      primesto[i] = 1 + primesto[i - 1];
    else
      primesto[i] = primesto[i - 1];
  int a, b, k;
  int l, p, x;
  scanf("%d %d %d", &a, &b, &k);
  if (primesto[b] - primesto[a - 1] < k) {
    printf("-1\n");
    return 0;
  }
  int lo = k - 1, hi = b - a + 2;
  int poz = -1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    int flag = 1;
    for (p = a; p <= b - mid + 1 && flag; ++p)
      if (primesto[p + mid - 1] - primesto[p - 1] < k) {
        flag = 0;
        lo = mid + 1;
      }
    if (flag) {
      poz = mid;
      hi = mid;
    }
  }
  printf("%d\n", poz);
  return 0;
}
