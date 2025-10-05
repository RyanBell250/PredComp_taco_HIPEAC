#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 50;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;
const long long lnf = 0x3f3f3f3f3f3f3f3f;
const long long mod = 998244353;
struct node {
  int a, b;
} p[105];
int dp[105][10050];
bool cmp(node A, node B) { return A.b > B.b; }
int main() {
  int n;
  int sum = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i].a);
    sum += p[i].a;
  }
  for (int i = 1; i <= n; i++) scanf("%d", &p[i].b);
  int cnt = 0;
  sort(p + 1, p + 1 + n, cmp);
  int temp = sum;
  for (int i = 1; i <= n; i++) {
    if (temp > 0) {
      temp -= p[i].b;
      cnt++;
    } else
      break;
  }
  memset(dp, -inf, sizeof(dp));
  dp[0][0] = 0;
  printf("%d ", cnt);
  for (int i = 1; i <= n; i++) {
    for (int j = sum; j >= p[i].a; j--) {
      for (int k = i; k >= 1; k--) {
        if (dp[k - 1][j - p[i].a] != -inf)
          dp[k][j] = max(dp[k][j], dp[k - 1][j - p[i].a] + p[i].b);
      }
    }
  }
  for (int i = sum; i >= 1; i--) {
    if (dp[cnt][i] >= sum) {
      printf("%d\n", sum - i);
      return 0;
    }
  }
  return 0;
}
