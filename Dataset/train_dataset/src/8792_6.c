#include <bits/stdc++.h>
using namespace std;
int n;
int ans;
int step;
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
int main() {
  while (scanf("%d", &n) == 1) {
    ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
      step = 0;
      if (gcd(i, n) != 1) continue;
      int a = i, b = n;
      while (1) {
        if (a == 1 && b == 1) break;
        if (a > b) {
          a = a - b;
        } else {
          b = b - a;
        }
        step++;
      }
      ans = min(ans, step);
    }
    printf("%d\n", ans);
  }
  return 0;
}
