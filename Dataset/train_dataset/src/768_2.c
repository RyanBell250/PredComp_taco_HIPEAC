#include <bits/stdc++.h>
using namespace std;
bool je[7];
int n, reza;
int d1, d2, t, t1, t2, i, b, ok, m;
void klir() {
  for (int i = 0; i < 7; i++) je[i] = false;
}
int dul(int x) {
  int ret = 0;
  while (x) ret++, x /= 7;
  return ret;
}
void check(int x, int de) {
  if (dul(x) + 1 == de) {
    if (je[0]) {
      ok = 0;
      return;
    }
    je[0] = true;
  }
  if (dul(x) + 1 < de) {
    ok = 0;
    return;
  }
  while (x) {
    if (je[x % 7]) {
      ok = 0;
      return;
    }
    je[x % 7] = true;
    x /= 7;
  }
}
int main() {
  cin >> n >> m;
  n--, m--;
  d1 = dul(n);
  d2 = dul(m);
  if (n == 0) d1++;
  if (m == 0) d2++;
  klir();
  if (d1 + d2 > 7) {
    cout << 0 << endl;
    return 0;
  }
  for (i = n; i >= 0; i--) {
    for (b = m; b >= 0; b--) {
      ok = 1;
      check(i, d1);
      check(b, d2);
      if (ok) reza++;
      klir();
    }
  }
  cout << reza << endl;
  return 0;
}
