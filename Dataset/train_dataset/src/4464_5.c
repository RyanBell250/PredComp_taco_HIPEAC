#include <bits/stdc++.h>
using namespace std;
long long summation(long long x) {
  long long l = 0, r = 1e6;
  long long ans = 1e6;
  while (l <= r) {
    long long mid = (l + r) >> 1ll;
    if ((mid * (mid - 1ll) / 2ll) >= x)
      r = mid - 1ll, ans = min(ans, mid);
    else
      l = mid + 1ll;
  }
  if (ans * (ans - 1ll) / 2ll == x) return ans;
  return -1;
}
int main() {
  long long a, b, c, d;
  cin >> a >> b >> c >> d;
  if (summation(a) == -1 || summation(d) == -1)
    return cout << "Impossible\n", 0;
  if (a == 0 && b == 0 && c == 0 && d == 0) return cout << 0 << "\n", 0;
  int x = summation(a);
  int y = summation(d);
  if (x == 0 && (b > 0 || c > 0)) x++;
  if (y == 0 && (b > 0 || c > 0)) y++;
  if (x * y != b + c) return cout << "Impossible\n", 0;
  string s = "";
  int n = x + y;
  for (int i = 0; i < n; ++i) {
    if (x == 0 || b < y) {
      s += '1';
      c -= x;
      y--;
    } else {
      s += '0';
      b -= y;
      x--;
    }
  }
  return cout << s << "\n", 0;
}
