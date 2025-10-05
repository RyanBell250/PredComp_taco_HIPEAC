#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int N = 1000100;
long long po(long long x, long long y) {
  if (y == 0) return 1;
  long long ret = po(x, y / 2);
  ret *= ret;
  if (y % 2) ret *= x;
  return ret;
}
long long n;
bool f;
void solve() {
  cin >> n;
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < n; j++) {
      if (f) {
        cout << 'W';
      } else {
        cout << 'B';
      }
      f = !f;
    }
    cout << '\n';
    if (n % 2 == 0) f = !f;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long t = 1;
  while (t--) {
    solve();
  }
}
