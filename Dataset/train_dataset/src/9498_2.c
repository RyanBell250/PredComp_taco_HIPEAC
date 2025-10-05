#include <bits/stdc++.h>
using namespace std;
int f(int c3, int k3, int c4, int k4, int c5, int k5) {
  return abs(c3 * k3 - c4 * k4) + abs(c4 * k4 - c5 * k5);
}
int main() {
  int n, s;
  int c3 = 0, c4 = 0, c5 = 0;
  int k3 = -1, k4 = -1, k5 = -1;
  int bk3 = -1, bk4 = -1, bk5 = -1;
  int minval = 100000000;
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    int val;
    cin >> val;
    if (val == 3) {
      ++c3;
    } else if (val == 4) {
      ++c4;
    } else if (val == 5) {
      ++c5;
    }
  }
  for (k4 = 0; k4 <= s; ++k4) {
    k3 = (int)floor(((double)c4 / c3) * k4);
    if (k3 > k4) {
      k3 = k4;
    }
    int i;
    int d = max(c3, max(c4, c5)) + 1;
    for (i = k3 - d; i <= k3 + d; ++i) {
      int k5 = s - c3 * i - c4 * k4;
      int val;
      if (k5 < 0 || k5 % c5 != 0) {
        continue;
      }
      k5 /= c5;
      if (0 <= i && i <= k4 && k4 <= k5 &&
          (val = f(c3, i, c4, k4, c5, k5)) < minval) {
        minval = val;
        bk3 = i;
        bk4 = k4;
        bk5 = k5;
      }
    }
    k5 = (int)ceil(((double)c4 / c5) * k4);
    if (k5 < k4) {
      k5 = k4;
    }
    k5 = min(s / c5 + 1, k5);
    d = max(c3, max(c4, c5)) + 1;
    for (i = k5 - d; i <= k5 + d; ++i) {
      int k3 = s - c5 * i - c4 * k4;
      int val;
      if (k3 < 0 || k3 % c3 != 0) {
        continue;
      }
      k3 /= c3;
      if (0 <= k3 && k3 <= k4 && k4 <= i &&
          (val = f(c3, k3, c4, k4, c5, i)) < minval) {
        minval = val;
        bk3 = k3;
        bk4 = k4;
        bk5 = i;
      }
    }
  }
  if (bk3 == -1) {
    cout << -1 << endl;
  } else {
    printf("%d %d %d\n", bk3, bk4, bk5);
  }
  return 0;
}
