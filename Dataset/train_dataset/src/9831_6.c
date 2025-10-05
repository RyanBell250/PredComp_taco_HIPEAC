#include <bits/stdc++.h>
using namespace std;
const long long mo = 998244353;
const int maxi = 5100;
int a, b, c;
long long d[maxi][maxi];
long long calc(int a, int b) {
  d[0][0] = 1;
  for (int i = 1; i <= a; i++) {
    for (int j = 0; j <= min(a, b); j++)
      if (j == 0) {
        d[i][j] = d[i - 1][j];
      } else
        d[i][j] = (d[i - 1][j] + d[i - 1][j - 1] * (b - j + 1)) % mo;
  }
  long long ans = 0;
  for (int i = 0; i <= min(a, b); i++) ans += d[a][i];
  return ans % mo;
}
int main() {
  cin >> a >> b >> c;
  long long ans = calc(a, b) * calc(a, c) % mo * calc(b, c) % mo;
  cout << ans << endl;
  return 0;
}
