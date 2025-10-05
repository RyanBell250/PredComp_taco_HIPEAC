#include <bits/stdc++.h>
using namespace std;
double ax, ay, bx, by;
double dx, dy;
double v, t;
double vx, vy, wx, wy;
bool check(double x) {
  double ddx = dx, ddy = dy;
  if (x <= t) {
    ddx -= vx * x;
    ddy -= vy * x;
  } else {
    ddx -= vx * t;
    ddy -= vy * t;
    ddx -= wx * (x - t);
    ddy -= wy * (x - t);
  }
  double len = sqrt(ddx * ddx + ddy * ddy);
  return v * x > len;
}
int main() {
  scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
  scanf("%lf %lf", &v, &t);
  scanf("%lf %lf %lf %lf", &vx, &vy, &wx, &wy);
  dx = bx - ax;
  dy = by - ay;
  double l = 0, r = 1000000000.0;
  for (int i = 0; i < 2000; i++) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  printf("%.20f\n", r);
  return 0;
}
