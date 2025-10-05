#include <bits/stdc++.h>
using namespace std;
double a1, a2, b1, b2, vm, t, vx, vy, wx, wy;
bool judge(double T) {
  if (T < t) {
    double xo = a1 + vx * T, yo = a2 + vy * T;
    double d = sqrt((xo - b1) * (xo - b1) + (yo - b2) * (yo - b2));
    if (d / vm > T) return 0;
    return 1;
  } else {
    double xo = a1 + vx * t, yo = a2 + vy * t;
    xo += wx * (T - t);
    yo += wy * (T - t);
    double d = sqrt((xo - b1) * (xo - b1) + (yo - b2) * (yo - b2));
    if (d / vm > T) return 0;
    return 1;
  }
}
int main() {
  scanf("%lf%lf%lf%lf", &a1, &a2, &b1, &b2);
  scanf("%lf%lf%lf%lf", &vm, &t, &vx, &vy);
  scanf("%lf%lf", &wx, &wy);
  double l = 0.0, r = 1e50;
  for (int i = 1; i <= 10000; i++) {
    double mid = (l + r) / 2;
    if (judge(mid))
      r = mid;
    else
      l = mid;
  }
  printf("%.15f", l);
  return 0;
}
