#include <bits/stdc++.h>
using namespace std;
int k, N, j, i;
int mod(int x, int MOD) {
  if (x % MOD == 0) return MOD;
  return x % MOD;
}
int main() {
  cin >> N >> k;
  if (2 * k >= N) {
    cout << "-1";
    return 0;
  }
  cout << k * N << '\n';
  for (i = 1; i <= N; i++) {
    for (j = i + 1; j <= i + k; j++) cout << i << " " << mod(j, N) << '\n';
  }
  return 0;
}
