#include <bits/stdc++.h>
using namespace std;
short lastrow[1002];
int main() {
  int n, r, c, p, remember;
  cin >> n;
  lastrow[0] = n - 1;
  lastrow[n - 1] = 0;
  for (r = 0; r < n - 1; r++) {
    for (p = 0, c = r; c < r + n; c++, p++) {
      if (p == r) {
        cout << "0 ";
        if (c < n)
          remember = c;
        else
          remember = c - n + 1;
      } else if (p == n - 1 && r > 0) {
        cout << remember;
        lastrow[r] = remember;
      } else {
        if (c < n)
          cout << c << ' ';
        else
          cout << c - n + 1 << ' ';
      }
    }
    cout << '\n';
  }
  for (c = 0; c < n; c++) cout << lastrow[c] << ' ';
  cout << '\n';
  return 0;
}
