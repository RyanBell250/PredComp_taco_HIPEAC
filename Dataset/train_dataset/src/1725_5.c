#include <bits/stdc++.h>
using namespace std;
long long int C[18000][501];
map<long long int, long long int> mp;
void factorize(long long int n) {
  for (long long int i = 2; i * i <= n; i++)
    while (n % i == 0) mp[i]++, n /= i;
  if (n > 1) mp[n]++;
}
void solve() {
  for (long long int i = 0; i < 18000; i++) {
    for (long long int j = 0; j <= min(i, 500LL); j++) {
      if (j == 0 || j == i)
        C[i][j] = 1;
      else
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % 1000000007;
      ;
    }
  }
  long long int n, x, ans = 1;
  cin >> n;
  for (long long int i = 0; i < n; i++) {
    cin >> x;
    factorize(x);
  }
  for (auto m : mp) {
    ans *= C[m.second + n - 1][n - 1];
    ans %= 1000000007;
    ;
  }
  cout << ans;
}
int main() {
  std::ios_base::sync_with_stdio(NULL);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
