#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
const int maxn = 1e5 + 100;
double x[maxn], y[maxn];
int n;
bool check(double d) {
  double l = -1e20, r = 1e20;
  for (int i = 1; i <= n; i++) {
    if (y[i] > 2 * d) return 0;
    double k = sqrt(2 * d * y[i] - y[i] * y[i]);
    double X = x[i] - k, Y = x[i] + k;
    l = max(l, X), r = min(r, Y);
  }
  return l <= r;
}
int main() {
  scanf("%d", &n);
  bool bb1 = 0, bb2 = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf", &x[i], &y[i]);
    if (y[i] > 0) bb1 = 1;
    if (y[i] < 0) y[i] = -y[i], bb2 = 1;
  }
  if (bb1 && bb2) {
    printf("-1\n");
    return 0;
  }
  double l = 0.000000001, r = 1e20;
  int Q = 100;
  while (Q--) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  printf("%.9lf\n", l);
  return 0;
}
