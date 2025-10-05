#include <bits/stdc++.h>
using namespace std;
const int maxn = 102;
const long long MOD = 1000000007;
int N, K, a[202], b[202], F[202][5002], Res;
int main() {
  cin >> N >> K;
  memset(F, -1, sizeof(F));
  for (int i = 1; i <= N; i++) {
    long long tmp, x;
    cin >> x;
    tmp = x;
    while (tmp % 2 == 0 && tmp) a[i]++, tmp /= 2;
    tmp = x;
    while (tmp % 5 == 0 && tmp) b[i]++, tmp /= 5;
  }
  F[0][0] = 0;
  for (int i = 1; i <= N; i++) {
    for (int k = K; k >= 1; k--) {
      for (int j = 0; j <= 5000; j++)
        if (j >= b[i] && F[k - 1][j - b[i]] != -1) {
          F[k][j] = max(F[k][j], F[k - 1][j - b[i]] + a[i]);
        }
    }
  }
  for (int j = 1; j <= 5000; j++) Res = max(Res, min(j, F[K][j]));
  cout << Res;
  return 0;
}
