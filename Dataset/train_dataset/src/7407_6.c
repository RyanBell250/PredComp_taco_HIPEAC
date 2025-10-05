#include <bits/stdc++.h>
using namespace std;
long long t, a, b, luu[300010];
int main() {
  luu[0] = 0;
  for (int i = 1; i <= 300000; i++) {
    luu[i] = luu[i - 1] ^ i;
  }
  cin >> t;
  for (int x = 1; x <= t; x++) {
    cin >> a >> b;
    if (a == 1 && b == 1) {
      cout << "3" << endl;
      continue;
    }
    long long tam = 0;
    if (luu[a - 1] != b) {
      if (luu[a] != b) {
        cout << a + 1 << endl;
      } else {
        cout << a + 2 << endl;
      }
    } else
      cout << a << endl;
  }
  return 0;
}
