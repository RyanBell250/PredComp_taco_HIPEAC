#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  for (; b; a %= b, swap(a, b))
    ;
  return a;
}
long long mpow(long long a, long long x) {
  if (x == 0) return 1;
  long long res = (mpow(a, x / 2) % 1000000007) * (mpow(a, x / 2) % 1000000007);
  res %= 1000000007;
  if (x % 2) res = (res % 1000000007) * (a % 1000000007);
  return res % 1000000007;
}
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  string s;
  cin >> s;
  long long n = s.size();
  long long ans = 0, sum = 0;
  for (long long i = 0; i < n; i++) {
    ans += mpow(10, n - 1 - i) * (i * (i + 1) / 2) % 1000000007 * (s[i] - '0') %
           1000000007;
    ans %= 1000000007;
    sum += (s[i] - '0');
    if (i != n - 1)
      ans += mpow(10, n - 2 - i) * (n - 1 - i) % 1000000007 * sum % 1000000007;
    ans %= 1000000007;
  }
  cout << ans;
}
