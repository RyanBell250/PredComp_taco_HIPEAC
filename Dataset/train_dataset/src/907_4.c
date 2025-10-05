#include <bits/stdc++.h>
using namespace std;
string a, b;
bool beats(char c, char d) {
  if (c == 'R' && d == 'S') return true;
  if (c == 'S' && d == 'P') return true;
  if (c == 'P' && d == 'R') return true;
  return false;
}
int main() {
  int n;
  cin >> n >> a >> b;
  int m = a.length(), k = b.length();
  int res1 = 0, res2 = 0;
  for (int i = 0; i < m * k; i++) {
    if (beats(a[i % m], b[i % k])) res2++;
    if (beats(b[i % k], a[i % m])) res1++;
  }
  res1 *= n / (m * k);
  res2 *= n / (m * k);
  n = n % (m * k);
  for (int i = 0; i < n; i++) {
    if (beats(a[i % m], b[i % k])) res2++;
    if (beats(b[i % k], a[i % m])) res1++;
  }
  cout << res1 << " " << res2;
  return 0;
}
