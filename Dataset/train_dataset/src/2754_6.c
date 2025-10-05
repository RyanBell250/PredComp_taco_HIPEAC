#include <bits/stdc++.h>
using namespace std;
const int dim = 101;
const int modulo = 1000000007;
struct matrix {
  int mat[dim][dim];
  matrix() { memset(mat, 0, sizeof(mat)); }
  matrix operator*(matrix &A) {
    matrix ret;
    for (int i = 0; i < dim; i++) {
      for (int j = 0; j < dim; j++) {
        ret.mat[i][j] = 0;
        for (int k = 0; k < dim; k++) {
          ret.mat[i][j] =
              (ret.mat[i][j] + 1LL * mat[i][k] * A.mat[k][j]) % modulo;
        }
      }
    }
    return ret;
  }
};
matrix modpow(matrix &base, int P) {
  if (P == 1) return base;
  matrix half = modpow(base, P >> 1);
  half = half * half;
  if (P & 1) half = half * base;
  return half;
}
int cnt[dim];
int dp[dim];
int main() {
  dp[0] = 1;
  int n, x;
  scanf("%d", &n);
  scanf("%d", &x);
  for (int i = 1; i <= n; i++) {
    int d;
    scanf("%d", &d);
    cnt[d] += 1;
  }
  for (int i = 1; i < dim; i++)
    for (int j = 1; j <= i; j++)
      dp[i] = (dp[i] + 1LL * cnt[j] * dp[i - j]) % 1000000007;
  int sum = 0;
  for (int i = 0; i < dim; i++) sum = (sum + dp[i]) % 1000000007;
  matrix base;
  for (int i = 1; i <= 100; i++) base.mat[0][i] = base.mat[1][i] = cnt[i];
  base.mat[0][0] = 1;
  for (int i = 2; i < dim; i++) base.mat[i][i - 1] = 1;
  if (x <= 100) {
    sum = 0;
    while (x >= 0) {
      sum += dp[x];
      sum %= 1000000007;
      x--;
    }
    cout << sum << "\n";
    return 0;
  }
  matrix ans = modpow(base, x - 100);
  int total = (1LL * ans.mat[0][0] * sum) % 1000000007;
  for (int i = 1; i < dim; i++)
    total = (total + 1LL * ans.mat[0][i] * dp[dim - i]) % 1000000007;
  cout << total << "\n";
  return 0;
}
