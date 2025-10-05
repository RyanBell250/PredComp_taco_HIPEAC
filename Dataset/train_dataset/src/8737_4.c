#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
const int n_ = 1e5 + 5;
string s;
int dp[1000005][2];
int solve(int i = s.size() - 1, int f = 0) {
  if (i == -1) return 0;
  int &ret = dp[i][f];
  if (~ret) return ret;
  if (s[i] == ('0' + f)) return ret = solve(i - 1, f);
  return ret = 1 + min(solve(i - 1, f), solve(i - 1, !f));
}
int main() {
  cin >> s;
  reverse(s.begin(), s.end());
  s.push_back('0');
  reverse(s.begin(), s.end());
  memset(dp, -1, sizeof dp);
  cout << solve();
  return 0;
}
