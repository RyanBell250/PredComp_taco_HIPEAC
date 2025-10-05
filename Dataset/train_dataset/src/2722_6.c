#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, x1, y1, x2, y2, cs = 0, a, b, c, v1, v2;
  scanf("%lld %lld", &x1, &y1);
  scanf("%lld %lld", &x2, &y2);
  scanf("%lld", &n);
  while (n--) {
    scanf("%lld %lld %lld", &a, &b, &c);
    v1 = x1 * a + y1 * b + c;
    v2 = x2 * a + y2 * b + c;
    if ((v1 > 0 && v2 < 0) || (v1 < 0 && v2 > 0)) ++cs;
  }
  printf("%lld\n", cs);
}
