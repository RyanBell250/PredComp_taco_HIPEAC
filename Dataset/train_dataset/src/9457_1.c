#include <bits/stdc++.h>
using namespace std;
void solve() {
  long long t1, t2, x1, x2, t0;
  cin >> t1 >> t2 >> x1 >> x2 >> t0;
  if (t1 == t2) {
    cout << x1 << ' ' << x2 << endl;
    return;
  }
  if (t0 == t1) {
    cout << x1 << ' ' << 0 << endl;
    return;
  }
  long long y1, y2;
  long long p = 1;
  long long q = 0;
  for (long long _y2 = x2; _y2 > 0; --_y2) {
    long long _y1 = _y2 * (t2 - t0) / (t0 - t1);
    if (_y1 > x1) _y1 = x1;
    long long den = (t0 + t1) * _y1 + (t0 + t2) * _y2;
    long long div = _y1 + _y2;
    if (p * div > den * q) {
      p = den;
      q = div;
      y1 = _y1;
      y2 = _y2;
    }
  }
  cout << y1 << ' ' << y2 << endl;
}
int main() {
  solve();
  return 0;
}
