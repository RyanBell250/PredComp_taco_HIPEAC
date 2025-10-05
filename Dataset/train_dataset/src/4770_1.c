#include <bits/stdc++.h>
using namespace std;
const int mo = 1000000007;
int q[65], k;
long long n;
struct Mat {
  int a[32][32];
  Mat() { memset(a, 0, sizeof(a)); }
  Mat operator*(const Mat &b) const {
    Mat c;
    for (int i = (int)(0); i <= (int)(::k); i++)
      for (int j = (int)(0); j <= (int)(::k); j++)
        for (int k = (int)(0); k <= (int)(::k); k++)
          c.a[i][k] = (c.a[i][k] + 1ll * a[i][j] * b.a[j][k]) % mo;
    return c;
  }
};
Mat pre[32], suf[32];
Mat f[65][32], ans;
int main() {
  scanf("%lld%d", &n, &k);
  ans.a[0][k] = 1;
  for (; n; n /= k) q[++*q] = n % k;
  for (int i = (int)(0); i <= (int)(k - 1); i++)
    for (int j = (int)(0); j <= (int)(k); j++)
      f[1][i].a[j][i] = f[1][i].a[j][j] = 1;
  for (int i = (int)(2); i <= (int)(*q); i++) {
    pre[0] = f[i - 1][0];
    suf[k - 1] = f[i - 1][k - 1];
    for (int j = (int)(1); j <= (int)(k - 1); j++)
      pre[j] = pre[j - 1] * f[i - 1][j];
    for (int j = (int)(k - 2); j >= (int)(0); j--)
      suf[j] = f[i - 1][j] * suf[j + 1];
    f[i][0] = suf[0];
    for (int j = (int)(1); j <= (int)(k - 1); j++)
      f[i][j] = suf[j] * pre[j - 1];
  }
  int sum = 0;
  for (int i = (int)(*q); i >= (int)(1); i--) {
    for (int j = (int)(0); j <= (int)(q[i] - 1); j++)
      ans = ans * f[i][(sum + j) % k];
    sum = (sum + q[i]) % mo;
  }
  sum = 0;
  for (int i = (int)(0); i <= (int)(k); i++)
    sum = (sum + 1ll * ans.a[0][i]) % mo;
  printf("%d\n", sum);
}
