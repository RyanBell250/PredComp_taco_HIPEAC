#include <bits/stdc++.h>

using namespace std;

int main() {
  long long n, a;
  cin >> n >> a;
  long long ans = n;
  for (int k = 2; k <= 200; k++) {
    long long a1 = 2;
    while (true) {
      long long prod = 1;
      for (int i = 0; i < k; i++) {
        prod *= a1;
        if (prod >= n) {
          break;
        }
      }
      if (prod >= n) {
        long long add = (a1 - 1) * k;
        prod = 1;
        for (int i = 0; i < k; i++) {
          prod *= a1 - 1;
        }
        while (prod < n) {
          prod /= a1 - 1;
          prod *= a1;
          add++;
        }
        ans = min(ans, add + a * (k - 1));
        break;
      }
      a1++;
    }
  }
  cout << ans << endl;
  return 0;
}
