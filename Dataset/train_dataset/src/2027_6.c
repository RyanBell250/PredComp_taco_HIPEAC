#include <bits/stdc++.h>
using namespace std;
const int N = 2 * 1e5 + 10;
const long long inf = 1e18 + 100;
const long long mod = 1e9 + 7;
void solve() {
  long long n;
  cin >> n;
  vector<long long> arr(1001000, 0);
  for (int i = 0; i < n; i++) {
    long long id, pp;
    cin >> id >> pp;
    arr[id] = pp;
  }
  vector<long long> dp(1001000, 0);
  long long pow = 0;
  for (int i = 0; i < 1001000; i++) {
    if (i == 0 && arr[i] == 0) {
      continue;
    }
    if (arr[i] == 0) {
      dp[i] = dp[i - 1];
    } else {
      if (arr[i] >= i) {
        dp[i] = 1;
      } else {
        dp[i] = dp[i - arr[i] - 1] + 1;
      }
    }
    pow = max(pow, dp[i]);
  }
  cout << n - pow << "\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
