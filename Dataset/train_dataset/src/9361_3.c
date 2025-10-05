#include <bits/stdc++.h>
using namespace std;
long long fact[2000005];
long long tavan(long long a, int e) {
  if (e == 1) return a % 1000000007;
  long long ans = tavan(a, e / 2);
  ans = (ans * ans) % 1000000007;
  if (e % 2 == 1) ans = ans * a % 1000000007;
  return ans;
}
long long inv(int a) { return tavan(a, 1000000007 - 2); }
long long C(int n, int k) {
  if (k > n || k < 0) return 0;
  return fact[n] * (inv(fact[k] * fact[n - k] % 1000000007)) % 1000000007;
}
int main() {
  int n, m, g;
  cin >> n >> m >> g;
  fact[0] = 1;
  for (int i = 1; i <= n + m; i++) fact[i] = fact[i - 1] * i % 1000000007;
  if (g == 1) {
    if (n == 0) {
      if (m == 1)
        cout << 1 << endl;
      else
        cout << 0 << endl;
      return 0;
    }
    n--;
  }
  long long ans = 0;
  for (int i = 0; i < n + m; i += 2) {
    if (i < n + m - 1 && m >= 1 && n >= i)
      ans = (ans + C(n + m - i - 1, m - 1)) % 1000000007;
    if (i == n + m - 1) {
      if (n >= i + 1) ans++;
    }
    if (i == n + m - 2) {
      if (n >= i + 1 && m >= 1) ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
