#include <bits/stdc++.h>
using namespace std;
int32_t main() {
  long long x, y;
  cin >> x >> y;
  long long a = max(x, y);
  long long b = min(x, y);
  long long count = 0, i;
  long long ans;
  long long x1;
  for (i = 1; i <= b; i++) {
    long long z = i % 5;
    if (z) {
      if (z == 1) {
        if ((a - 4) < 0) {
          continue;
        }
        ans = (a - 4) / 5 + 1;
        count += ans;
      }
      if (z == 2) {
        if ((a - 3) < 0) {
          continue;
        }
        ans = (a - 3) / 5 + 1;
        count += ans;
      }
      if (z == 3) {
        if ((a - 2) < 0) {
          continue;
        }
        ans = (a - 2) / 5 + 1;
        count += ans;
      }
      if (z == 4) {
        if ((a - 1) < 0) {
          continue;
        }
        ans = (a - 1) / 5 + 1;
        count += ans;
      }
    } else {
      ans = a / 5;
      count += ans;
    }
  }
  cout << count << endl;
  return 0;
}
