#include <bits/stdc++.h>
using namespace std;
long long n;
inline bool check2(long long x, long long y3) {
  return (x * x + y3 * y3 * 3 <= n * n);
}
inline bool check(long long x, long long y3) {
  return check2(x - 2, y3) & check2(x - 1, y3 - 1) & check2(x + 1, y3 - 1) &
         check2(x + 2, y3) & check2(x + 1, y3 + 1) & check2(x - 1, y3 + 1);
}
long long calc(long long x, long long d) {
  long long l = 0, r = 3e6;
  while (l < r) {
    long long mid = (l + r + 1) / 2;
    long long y3 = d + mid * 2;
    if (check(x, y3))
      l = mid;
    else
      r = mid - 1;
  }
  long long ret = r * 2;
  if (d == 0 && check(x, 0)) ret += 1;
  if (d == 1 && check(x, d)) ret += 2;
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  n *= 2;
  long long s = 0;
  int x = 3, d = 1;
  while (true) {
    long long t = calc(x, d);
    if (t == 0) break;
    s += t;
    x += 3, d ^= 1;
  }
  s *= 2;
  s += calc(0, 0);
  cout << s << endl;
}
