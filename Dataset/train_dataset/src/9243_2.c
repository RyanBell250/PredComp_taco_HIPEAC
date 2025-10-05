#include <bits/stdc++.h>
using namespace std;
int n, m, k;
bool debug = false;
long long r;
bool ch(long long x, long long y) { return x * x + 3 * y * y <= 4 * r * r; }
int main() {
  cin >> r;
  long long ans = 0;
  long long mm = (long long)(r * 2.0 / sqrt(3.0)) + 2;
  for (long long x = 1, y = 1; ch(x, y); x += 3, y++) {
    long long l = y, r = mm;
    while (l + 1 < r) {
      long long mi = (l + r) / 2;
      if (ch(x, mi))
        l = mi;
      else
        r = mi;
    }
    ans += (l - y) / 2;
  }
  cout << ans * 6 + 1 << endl;
  return 0;
}
