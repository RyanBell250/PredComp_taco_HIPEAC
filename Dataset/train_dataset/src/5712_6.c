#include <bits/stdc++.h>
using namespace std;
const int LG = 23, N = 1e6 + 20, mod = 1e9 + 7;
int q, f[N][LG], res[N], d[N];
inline int sum(int a, int b) {
  int res = a + b;
  if (res >= mod) res -= mod;
  return res;
}
void pre() {
  f[0][0] = 1;
  for (int i = 1; i < LG; i++) f[0][i] = 2;
  for (int i = 1; i < N; i++) {
    f[i][0] = f[i - 1][0];
    for (int j = 1; j < LG; j++) f[i][j] = sum(f[i - 1][j], f[i][j - 1]);
  }
  memset(d, -1, sizeof d);
  for (int i = 2; i < N; i++)
    for (int j = i + i; j < N; j += i)
      if (d[j] == -1) d[j] = i;
}
int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  pre();
  cin >> q;
  while (q--) {
    int r, n, res = 1;
    cin >> r >> n;
    while (n > 1) {
      int k = d[n], cnt = 0;
      if (k == -1)
        n = 1, cnt = 1;
      else
        while (n % k == 0) n /= k, cnt++;
      res = res * 1ll * f[r][cnt] % mod;
    }
    cout << res << '\n';
  }
}
