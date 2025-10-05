#include <bits/stdc++.h>
using namespace std;
int n, kk, xx;
int cnt = 0;
int n2b[75], b2n[265];
int bs[10];
long long dis[10];
int p[30];
long long dp[2][75];
map<int, long long> mp;
struct Mat {
  long long num[75][75];
  friend Mat operator*(Mat x1, Mat x2) {
    Mat ans;
    for (int i = 1; i <= cnt; i++)
      for (int j = 1; j <= cnt; j++) {
        ans.num[i][j] = 2LL * 1000000007 * 1000000007;
        for (int k = 1; k <= cnt; k++)
          ans.num[i][j] = min(x1.num[i][k] + x2.num[k][j], ans.num[i][j]);
      }
    return ans;
  }
} A;
queue<int> q;
Mat pows(Mat x, int y) {
  Mat ans;
  for (int i = 1; i <= cnt; i++)
    for (int j = 1; j <= cnt; j++) {
      if (i == j)
        ans.num[i][j] = 0;
      else
        ans.num[i][j] = 2LL * 1000000007 * 1000000007;
    }
  while (y) {
    if (y % 2) ans = ans * x;
    x = x * x;
    y >>= 1;
  }
  return ans;
}
void init(int f, int x, int s) {
  if (f == kk) {
    if (x == xx) {
      cnt++;
      b2n[s] = cnt;
      n2b[cnt] = s;
    }
    return;
  }
  init(f + 1, x + 1, s + bs[f]);
  init(f + 1, x, s);
}
void solve1(Mat x) {
  for (int i = 1; i <= cnt; i++) dp[1][i] = 2LL * 1000000007 * 1000000007;
  for (int i = 1; i <= cnt; i++)
    for (int j = 1; j <= cnt; j++)
      dp[1][j] = min(dp[0][i] + x.num[i][j], dp[1][j]);
  for (int i = 1; i <= cnt; i++) dp[0][i] = dp[1][i];
}
void solve2(int y) {
  for (int i = 1; i <= cnt; i++) dp[1][i] = 2LL * 1000000007 * 1000000007;
  for (int i = 1; i <= cnt; i++) {
    if (n2b[i] % 2) {
      for (int j = 1; j <= kk; j++) {
        if ((n2b[i] & bs[j]) == 0)
          dp[1][b2n[(n2b[i] + bs[j]) / 2]] =
              min(dp[1][b2n[(n2b[i] + bs[j]) / 2]],
                  dp[0][i] + A.num[i][b2n[(n2b[i] + bs[j]) / 2]] + mp[y + j]);
      }
    } else
      dp[1][b2n[n2b[i] / 2]] = min(dp[1][b2n[n2b[i] / 2]], dp[0][i]);
  }
  for (int i = 1; i <= cnt; i++) dp[0][i] = dp[1][i];
}
int main() {
  int qq;
  long long w;
  bs[0] = 1;
  for (int i = 1; i <= 8; i++) bs[i] = bs[i - 1] * 2;
  scanf("%d%d%d%d", &xx, &kk, &n, &qq);
  init(0, 0, 0);
  for (int i = 1; i <= kk; i++) scanf("%lld", &dis[i]);
  for (int i = 1; i <= cnt; i++) {
    for (int j = 1; j <= cnt; j++) A.num[i][j] = 2LL * 1000000007 * 1000000007;
    if (n2b[i] % 2) {
      for (int j = 1; j <= kk; j++) {
        if ((n2b[i] & bs[j]) == 0) A.num[i][b2n[(n2b[i] + bs[j]) / 2]] = dis[j];
      }
    } else
      A.num[i][b2n[n2b[i] / 2]] = 0;
  }
  for (int i = 0; i < qq; i++) {
    scanf("%d%lld", &p[i], &w);
    mp[p[i]] = w;
  }
  p[qq] = n - xx + 1;
  int now = 1;
  for (int i = 2; i <= cnt; i++) dp[0][i] = 2LL * 1000000007 * 1000000007;
  sort(p, p + qq);
  for (int i = 0; i <= qq; i++) {
    if (p[i] > p[qq]) p[i] = p[qq];
    if (now + kk < p[i]) {
      solve1(pows(A, p[i] - kk - now));
      now = p[i] - kk;
    }
    while (now < p[i]) {
      solve2(now);
      now++;
    }
  }
  printf("%lld\n", dp[0][1]);
  return 0;
}
