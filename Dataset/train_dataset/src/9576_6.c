#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e4 + 5;
const long long MOD = 1e9 + 7;
int n, b, K, x, a[MAX];
struct Mat {
  long long m[101][101];
  Mat() { memset(m, 0, sizeof(m)); }
};
Mat multi(const Mat &a, const Mat &b) {
  Mat c;
  for (int i = 0; i < x; i++)
    for (int j = 0; j < x; j++)
      if (a.m[j][i] != 0)
        for (int k = 0; k < x; k++)
          if (b.m[i][k] != 0)
            c.m[j][k] = (c.m[j][k] + a.m[j][i] * b.m[i][k] % MOD) % MOD;
  return c;
}
Mat pow(Mat &a, int k) {
  Mat b;
  for (int i = 0; i < x; i++) b.m[i][i] = 1;
  while (k) {
    if (k & 1) b = multi(b, a);
    a = multi(a, a);
    k >>= 1;
  }
  return b;
}
int main() {
  while (~scanf("%d%d%d%d", &n, &b, &K, &x)) {
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    Mat A;
    for (int i = 0; i < x; ++i)
      for (int j = 0; j < n; ++j) ++A.m[i][(i * 10 + a[j]) % x];
    A = pow(A, b);
    printf("%lld\n", A.m[0][K]);
  }
  return 0;
}
