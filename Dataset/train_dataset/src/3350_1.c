#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = 1e9 + 7;
int n;
long long a[N];
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  long long cnt = 1;
  long long lm = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] % (i + 1) != 0) {
      cnt++;
      lm = lcm(cnt, lm);
    } else {
      if (a[i] % lm == 0) {
        cout << "NO"
             << "\n";
        return;
      }
      cnt++;
      lm = lcm(cnt, lm);
    }
  }
  cout << "YES"
       << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int _ = 1;
  cin >> _;
  while (_--) solve();
  return 0;
}
