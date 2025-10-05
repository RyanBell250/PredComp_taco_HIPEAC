#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
const int N = 505;
void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}
int b[N], f[N][N];
int MAIN() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < n; ++i) {
    f[i][i] = 1;
    f[i][i + 1] = 1;
  }
  for (int k = 3; k <= n; ++k) {
    for (int start = 0; start + k - 1 < n; ++start) {
      int end = start + k - 1;
      for (int i = start + 2; i <= end; ++i) {
        if (b[start + 1] < b[i]) {
          add(f[start][end], 1ll * f[start + 1][i - 1] * f[i - 1][end] % mod);
        }
      }
      add(f[start][end], f[start + 1][end]);
    }
  }
  cout << f[0][n - 1] << endl;
  return 0;
}
int main() {
  ios ::sync_with_stdio(false);
  cout << fixed << setprecision(16);
  return MAIN();
}
