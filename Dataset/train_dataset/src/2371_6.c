#include <bits/stdc++.h>
using namespace std;
int n, m, a[25], b[25];
struct Mat {
  long long a[45][45];
  Mat() { memset(a, 10, sizeof(a)); }
  Mat operator*(const Mat &b) const {
    Mat ans;
    for (int i = (int)(0); i <= (int)(2 * n); i++)
      for (int j = (int)(0); j <= (int)(2 * n); j++)
        for (int k = (int)(0); k <= (int)(2 * n); k++)
          ans.a[i][j] = min(ans.a[i][j], a[i][k] + b.a[k][j]);
    return ans;
  }
};
Mat power(Mat a, int b) {
  Mat s;
  for (int i = (int)(0); i <= (int)(2 * n); i++) s.a[i][i] = 0;
  for (; b; b /= 2, a = a * a)
    if (b & 1) s = s * a;
  return s;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = (int)(1); i <= (int)(n); i++) scanf("%d", &a[i]);
  for (int i = (int)(1); i <= (int)(n); i++) scanf("%d", &b[i]);
  Mat ans;
  for (int i = (int)(0); i <= (int)(2 * n); i++) ans.a[i][i] = 0;
  for (int i = (int)(1); i <= (int)(n); i++) {
    Mat tmp;
    for (int j = (int)(1); j <= (int)(2 * n); j++) {
      tmp.a[j - 1][j] = a[i];
      tmp.a[j][j - 1] = b[i];
    }
    ans = ans * tmp;
  }
  ans = power(ans, m);
  printf("%lld ", ans.a[0][0]);
}
