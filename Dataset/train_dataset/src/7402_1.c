#include <bits/stdc++.h>
using namespace std;
const int N = 105, M = 1e9 + 7;
int tc;
long long dp[N][26 * N];
long long solve(int i, int sum) {
  if (!i) return (!sum);
  if (~dp[i][sum]) return dp[i][sum];
  long long ans = 0;
  for (int j = 0; j <= min(25, sum); ++j) (ans += solve(i - 1, sum - j)) %= M;
  return dp[i][sum] = ans;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  memset(dp, -1, sizeof dp);
  while (tc--) {
    string s;
    cin >> s;
    int sum = 0;
    for (auto &it : s) sum += it - 'a';
    cout << (solve(s.size(), sum) - 1 + M) % M << '\n';
  }
  return 0;
}
