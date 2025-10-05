#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, m, k, l, i, j, p, q, ans, u, v;
  while (cin >> n >> m >> k >> l) {
    if (m > n) {
      cout << -1 << endl;
      return 0;
    }
    if ((n / m) * m - k < l) {
      cout << -1 << endl;
      return 0;
    }
    p = n / m;
    ans = 1;
    long long lo = 1, hi = n / m, mid;
    while (lo <= hi) {
      mid = (lo + hi) / 2;
      if ((mid * m) > n) {
        hi = mid - 1;
        continue;
      } else {
        if ((mid * m) - k < l) {
          lo = mid + 1;
          continue;
        } else if ((mid * m) - k > l) {
          hi = mid - 1;
          continue;
        } else
          break;
      }
    }
    while (mid * m > n) {
      mid--;
    }
    while ((mid * m) - k < l && mid * m < n) {
      mid++;
    }
    cout << mid << endl;
  }
  return 0;
}
