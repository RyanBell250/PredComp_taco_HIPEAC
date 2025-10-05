#include <bits/stdc++.h>
using namespace std;
const int oo = 0x7fffffff;
const long long OO = 0x7fffffffffffffff;
const int NX = 1123;
const long long MOD = 998244353;
long long dp[NX], arr[NX], bin[NX][NX];
int main() {
  ios_base::sync_with_stdio(false);
  for (int i = 0; i < NX; i++) {
    bin[i][i] = bin[i][0] = 1;
    for (int j = 1; j < i; j++)
      bin[i][j] = (bin[i - 1][j - 1] + bin[i - 1][j]) % MOD;
  }
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> arr[i];
  dp[N] = 1;
  for (int i = N - 1; i >= 0; i--) {
    dp[i] = dp[i + 1];
    if (arr[i] > 0)
      for (int j = i + arr[i], l = 0; j < N; j++, l++)
        dp[i] = (bin[l + arr[i] - 1][arr[i] - 1] * dp[j + 1] + dp[i]) % MOD;
  }
  cout << (dp[0] - 1 + MOD) % MOD << endl;
  return 0;
}
