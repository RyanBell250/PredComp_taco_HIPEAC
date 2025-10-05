#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, i, sr, ans, f = 0, t;
  cin >> n;
  sr = sqrt(n);
  t = n;
  for (i = 2; i <= sr; i++) {
    if (n % i == 0) ans = i, f++;
    while (n % i == 0) n /= i;
  }
  if (f == 1 && n == 1)
    cout << ans << endl;
  else if (t == n)
    cout << n << endl;
  else
    cout << 1 << endl;
  return 0;
}
