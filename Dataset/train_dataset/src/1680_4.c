#include <bits/stdc++.h>
const int N = 1e9;
using namespace std;
int gcd(int a, int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}
int main() {
  int a, b, c, n, ans = 0;
  cin >> n >> a >> b >> c;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      int u = n - a * i - b * j;
      if (u >= 0 && u % c == 0) ans = max(ans, i + j + u / c);
    }
  }
  cout << ans << endl;
  return 0;
}
