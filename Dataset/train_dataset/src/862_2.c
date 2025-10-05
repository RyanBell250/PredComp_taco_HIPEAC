#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a, b;
  cin >> n >> a >> b;
  if (n > a * b) {
    cout << -1 << endl;
    return 0;
  }
  int c[105][105];
  memset(c, 0, sizeof(c));
  for (int i = 0; i < a; i++)
    for (int j = 0; j < b; j++, n -= (n > 0) ? 1 : 0)
      if (i & 1)
        c[i][b - j - 1] = n;
      else
        c[i][j] = n;
  for (int i = 0; i < a; i++)
    for (int j = 0; j < b; j++) cout << c[i][j] << " \n"[j == b - 1];
  return 0;
}
