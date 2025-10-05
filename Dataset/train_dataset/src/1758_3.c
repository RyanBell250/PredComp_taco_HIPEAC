#include <bits/stdc++.h>
using namespace std;
int dp[2][110][10010];
int main() {
  map<int, int> mp;
  int n;
  scanf("%d", &n);
  while (n--) {
    int x;
    scanf("%d", &x);
    mp[x]++;
  }
  dp[0][0][0] = 1;
  int r = 0;
  for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
    int flag = r & 1;
    memset(dp[flag ^ 1], false, sizeof(dp[flag ^ 1]));
    for (int i = 0; i <= 100; i++)
      for (int k = 10000; k >= 0; k--) {
        if (!dp[flag][i][k]) continue;
        for (int p = 0; p <= it->second; p++) {
          dp[flag ^ 1][i + p][k + p * it->first] += dp[flag][i][k];
          if (dp[flag ^ 1][i + p][k + p * it->first] > 1)
            dp[flag ^ 1][i + p][k + p * it->first] = 2;
        }
      }
    r++;
  }
  int ans = 0;
  for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
    for (int i = 1; i <= it->second; i++)
      if (dp[r & 1][i][i * it->first] == 1) ans = max(ans, i);
  }
  if (mp.size() == 1) {
    cout << mp.begin()->second << endl;
  } else if (mp.size() == 2) {
    cout << mp.begin()->second + mp.rbegin()->second << endl;
  } else
    cout << ans << endl;
  return 0;
}
