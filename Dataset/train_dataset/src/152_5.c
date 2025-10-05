#include <bits/stdc++.h>
using namespace std;
int dp[2000000 + 342];
int extra[2000000 + 342];
int main() {
  ios::sync_with_stdio(false);
  int n, m, k, tiempo;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    cin >> tiempo;
    dp[tiempo]++;
  }
  vector<int> rng;
  int count = 0;
  int tmp = 0;
  int window = 0;
  for (int i = 1; i <= 1000000; i++) {
    window += dp[i];
    if (i - m > 0 && dp[i - m] > 0) {
      window--;
    }
    if (window >= k) {
      count++;
      dp[i] = 0;
      window--;
    }
  }
  cout << count << "\n";
  return 0;
}
