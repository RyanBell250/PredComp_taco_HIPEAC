#include <bits/stdc++.h>
using namespace std;
double EPS = 1e-10;
double EQ(double a, double b) { return abs(a - b) < EPS; }
void fast_stream() { std::ios_base::sync_with_stdio(0); }
void solve() {
  int x, t, a, b, da, db;
  cin >> x >> t >> a >> b >> da >> db;
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < t; j++) {
      int sum = a + b - da * i - db * j;
      if (sum == x) {
        cout << "YES" << endl;
        return;
      }
    }
  }
  for (int i = 0; i < t; i++) {
    int sum = a - da * i;
    if (sum == x) {
      cout << "YES" << endl;
      return;
    }
  }
  for (int i = 0; i < t; i++) {
    int sum = b - db * i;
    if (sum == x) {
      cout << "YES" << endl;
      return;
    }
  }
  if (x == 0)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}
int main() {
  solve();
  return 0;
}
