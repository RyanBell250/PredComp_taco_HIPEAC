#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int n;
int dp[102][2602];
char s[102];
int main() {
  dp[0][0] = 1;
  for (int i = 1; i <= 100; i++)
    for (int sum = 1; sum <= 2600; sum++)
      for (int j = 1; j <= 26 && j <= sum; j++) {
        dp[i][sum] += dp[i - 1][sum - j];
        if (dp[i][sum] >= mod) dp[i][sum] -= mod;
      }
  int test, res;
  scanf("%d", &test);
  while (test--) {
    scanf("%s", s);
    n = strlen(s);
    int sum = 0;
    for (int i = 0; i < n; i++) sum += s[i] - 'a' + 1;
    res = dp[n][sum] - 1;
    if (res < 0) res += mod;
    printf("%d\n", res);
  }
  return 0;
}
