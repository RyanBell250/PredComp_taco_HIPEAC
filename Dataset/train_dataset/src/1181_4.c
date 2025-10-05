#include <bits/stdc++.h>
using namespace std;
int a[1010][1010];
int main() {
  int n;
  scanf("%d", &n);
  int r = 0;
  for (int i = 1; i < n; i += 2) {
    int e = r, ee = r + 1;
    for (int j = 1; j <= n; j++) a[i][j] = e, e += 2;
    for (int j = 1; j <= n; j++) a[i + 1][j] = ee, ee += 2;
    r = e;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < n; j++) cout << a[i][j] << ' ';
    cout << a[i][n] << endl;
  }
  return 0;
}
