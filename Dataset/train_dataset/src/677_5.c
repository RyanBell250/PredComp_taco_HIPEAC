#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<long long> v(100001);
vector<long long> c(100001);
vector<long long> dp(100001);
const long long INF = 1e15;
void input() {
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> v[i];
  for (int i = 0; i < n; i++) cin >> c[i];
}
void solve(long long a, long long b) {
  fill(dp.begin(), dp.end(), -INF);
  long long m1 = 0, m2 = 0;
  for (int i = 0; i < n; i++) {
    long long m = v[i] * b;
    if (m1 != c[i]) {
      m = max(m, dp[m1] + v[i] * b);
    }
    if (m2 != c[i]) {
      m = max(m, dp[m2] + v[i] * b);
    }
    m = max(m, dp[c[i]] + v[i] * a);
    dp[c[i]] = max(dp[c[i]], m);
    if (i == 0) {
      m1 = c[i];
    } else if (m1 == m2 && c[i] != m1) {
      if (m > dp[m1]) {
        m1 = c[i];
      } else {
        m2 = c[i];
      }
    } else {
      if (m > dp[m1]) {
        if (m1 != c[i]) m2 = m1;
        m1 = c[i];
      } else if (m > dp[m2] && m1 != c[i]) {
        m2 = c[i];
      }
    }
  }
  cout << max(0LL, *max_element(dp.begin(), dp.end())) << '\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  input();
  while (q--) {
    long long a, b;
    cin >> a >> b;
    solve(a, b);
  }
  return 0;
}
