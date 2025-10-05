#include <bits/stdc++.h>
using namespace std;
int le[100], ri[100];
int dp[100005];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int x, s;
    cin >> x >> s;
    le[i] = max(x - s, 0);
    ri[i] = min(x + s, m);
  }
  for (int i = 0; i <= m; i++) {
    dp[i] = i;
    for (int j = 0; j < n; j++) {
      if (le[j] <= i && i <= ri[j])
        dp[i] = min(dp[i - 1], dp[i]);
      else if (i > ri[j])
        dp[i] = min(dp[i], i - ri[j] + dp[max(0, le[j] - i + ri[j] - 1)]);
    }
  }
  cout << dp[m];
}
