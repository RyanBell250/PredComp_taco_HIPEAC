#include <bits/stdc++.h>
using namespace std;
int main() {
  int k;
  cin >> k;
  int len = k;
  int cnt = 0;
  int x = 0;
  long long res = 0;
  while (x <= 2 * k) {
    if (!(cnt & 1)) {
      int best = 0;
      int l = 1, r = k;
      while (l <= r) {
        int m = (l + r) / 2;
        if ((((x + 2) * 1ll * (x + 2)) + ((m - 1) * 1ll * (m - 1)) * 12 <=
             ((k)*1ll * (k)) * 4) &&
            (((x + 1) * 1ll * (x + 1)) +
                 ((2 * m - 1) * 1ll * (2 * m - 1)) * 3 <=
             ((k)*1ll * (k)) * 4)) {
          best = m;
          l = m + 1;
        } else
          r = m - 1;
      }
      if (best) {
        if (x) res += best * 2 - 1;
        res += best * 2 - 1;
      }
    } else {
      int best = 0;
      int l = 1, r = k;
      while (l <= r) {
        int m = (l + r) / 2;
        if ((((x + 2) * 1ll * (x + 2)) +
                 ((2 * m - 1) * 1ll * (2 * m - 1)) * 3 <=
             ((k)*1ll * (k)) * 4) &&
            (((x + 1) * 1ll * (x + 1)) + ((m)*1ll * (m)) * 12 <=
             ((k)*1ll * (k)) * 4)) {
          best = m;
          l = m + 1;
        } else
          r = m - 1;
      }
      if (x) res += best * 2;
      res += best * 2;
    }
    x += 3;
    cnt++;
  }
  cout << res << endl;
  return 0;
}
