#include <bits/stdc++.h>
const double pi = acos(-1);
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e5 + 5;
const double eps = 1e-9;
using namespace std;
int a[3], b[3], c[3];
int main() {
  for (int i = 0; i < (3); i++) scanf("%d", &(a)[i]);
  for (int i = 0; i < (3); i++) scanf("%d", &(b)[i]);
  for (int i = 0; i < (3); i++) scanf("%d", &(c)[i]);
  int ans = INF;
  for (int i = 0; i <= 1000; i++) {
    for (int j = a[1]; j <= max(b[0] + b[2] + 1, a[1]); j++) {
      for (int k = a[2]; k <= max(b[1] + 1, a[2]); k++) {
        int t1 = 0, t2 = 0;
        if (j - b[2] <= 0)
          t1 = INF;
        else
          t1 = b[0] / (j - b[2]);
        if (b[1] - k <= 0)
          t2 = INF;
        else
          t2 = (a[0] + i) / (b[1] - k);
        if (t1 != INF && b[0] % (j - b[2]) != 0) t1++;
        if (t2 != INF && (a[0] + i) % (b[1] - k) != 0) t2++;
        if (t1 < t2)
          ans = min(ans, i * c[0] + (j - a[1]) * c[1] + (k - a[2]) * c[2]);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
