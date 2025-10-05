#include <bits/stdc++.h>
using namespace std;
vector<long long int> prime(1e6 + 3, 1);
vector<long long int> dp(1e6 + 1, 0);
void getPrime() {
  long long int n = 4;
  prime[0] = 0;
  prime[1] = 0;
  while (n <= 1e6 + 2) {
    prime[n] = 0;
    n += 2;
  }
  for (long long int i = 3; i * i <= 1e6; i += 2) {
    if (prime[i] == 0) continue;
    long long int temp = i + i;
    while (temp <= 1e6 + 2) {
      prime[temp] = 0;
      temp += i;
    }
  }
}
void getDP() {
  dp[1] = 1;
  for (long long int i = 2; i <= 1e6; ++i) {
    if (prime[i])
      dp[i] = dp[i - 1] + 1;
    else if (sqrt(i) == (long long int)sqrt(i)) {
      if (prime[(long long int)sqrt(i)])
        dp[i] = dp[i - 1] - 1;
      else
        dp[i] = dp[i - 1];
    } else
      dp[i] = dp[i - 1];
  }
}
void solve() {
  long long int n;
  cin >> n;
  cout << dp[n] << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  getPrime();
  getDP();
  while (t--) {
    solve();
  }
  return 0;
}
