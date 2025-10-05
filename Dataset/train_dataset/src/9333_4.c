#include <bits/stdc++.h>
using namespace std;
void solve() {
  long long n, a, b, c, ct = 0;
  cin >> n >> a >> b >> c;
  for (long long i = 0; i <= a; i += 2) {
    for (long long j = 0; j < b + 1; j++) {
      long long d = (n - (i / 2) - j);
      if (d % 2 == 0 && c >= (d / 2) && (d / 2) >= 0) ct++;
    }
  }
  cout << ct << "\n";
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  long long t = 1;
  while (t--) {
    solve();
  }
}
