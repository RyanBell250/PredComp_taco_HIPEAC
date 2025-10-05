#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long int x, y, x1, y1;
    cin >> x >> y >> x1 >> y1;
    long long int p = abs(x - x1);
    long long int p1 = abs(y - y1);
    long long int ans = p1 + p + 2;
    if (p1 == 0 || p == 0) ans -= 2;
    cout << ans << '\n';
  }
}
