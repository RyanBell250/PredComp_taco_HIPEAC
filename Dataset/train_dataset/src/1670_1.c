#include <bits/stdc++.h>
using namespace std;
int a[1000005], tot;
int main() {
  a[1] = 2;
  a[2] = 7;
  for (int i = 3; a[i - 1] <= 1e9; i++) {
    a[i] = a[i - 1] + 2 + (i - 1) * 3;
    tot = i - 1;
  }
  int T;
  cin >> T;
  while (T--) {
    int n, cnt = 0;
    cin >> n;
    for (int i = tot; i >= 1; i--)
      while (a[i] <= n) {
        n -= a[i];
        cnt++;
      }
    cout << cnt << endl;
  }
}
