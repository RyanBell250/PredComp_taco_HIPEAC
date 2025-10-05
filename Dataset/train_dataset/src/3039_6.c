#include <bits/stdc++.h>
using namespace std;
int joa(int k) {
  int p = 1;
  if (k < 10)
    return k;
  else {
    while (k) {
      if (k % 10 != 0) p *= (k % 10);
      k /= 10;
    }
  }
  return joa(p);
}
int dp[12][1000010];
int ps[12][1000010];
int main() {
  memset(dp, 0, sizeof(dp));
  memset(ps, 0, sizeof(ps));
  for (int i = 1; i <= 1000000; i++) dp[joa(i)][i]++;
  for (int i = 1; i <= 10; i++)
    for (int j = 1; j <= 1000000; j++) ps[i][j] = dp[i][j] + ps[i][j - 1];
  int q;
  scanf("%d", &q);
  while (q-- > 0) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    cout << ps[k][r] - ps[k][l - 1] << endl;
  }
  return 0;
}
