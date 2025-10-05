#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
long long lcm(long long a, long long b) { return a * b / gcd(a, b); }
int main() {
  cin.sync_with_stdio(false);
  long long a, b;
  cin >> a >> b;
  bool reversed = false;
  if (b < a) {
    reversed = true;
    swap(b, a);
  }
  long long l = lcm(a, b);
  long long i = 0;
  long long ca = 0, cb = 0;
  long long fa = 1, fb = 1;
  while (i <= l) {
    long long nexta = fa * a, nextb = fb * b;
    if (nextb <= nexta) {
      cb += min(l, nextb) - i;
      fb++;
      i = nextb;
    } else {
      ca += min(l, nexta) - i;
      fa++;
      i = nexta;
    }
  }
  if (reversed) {
    swap(ca, cb);
  }
  if (ca > cb) {
    cout << "Dasha\n";
  } else if (ca < cb) {
    cout << "Masha\n";
  } else {
    cout << "Equal\n";
  }
  return 0;
}
