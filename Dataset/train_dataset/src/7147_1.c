#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
const int mod = 1e9 + 7;
int n, a[N], pw[N];
long long ans;
int main() {
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = (pw[i - 1] * 2ll) % mod;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    a[x]++;
  }
  for (int j = 0; j < 20; j++) {
    for (int i = (1 << 20) - 1; i >= 0; i--) {
      if (i & (1 << j)) {
        a[i - (1 << j)] += a[i];
      }
    }
  }
  for (int i = 0; i < pw[20]; i++) {
    int bit = __builtin_popcount(i);
    if (bit & 1)
      ans -= pw[a[i]], ans = (ans + mod) % mod;
    else
      ans += pw[a[i]], ans = (ans + mod) % mod;
  }
  cout << ans << endl;
}
