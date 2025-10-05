#include <bits/stdc++.h>
using namespace std;
vector<long long int> p[200005], q[200005], f(500005, 0),
    b(100005, 0), a, d[30];
map<pair<long long int, long long int>, long long int> mp;
long long int gcd(long long int a, long long int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
long long int bpow(long long int a, long long int b) {
  long long int res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % 998244353;
    a = (a * a) % 998244353;
    b >>= 1;
  }
  return res % 998244353;
}
void fact(long long int i) {
  f[0] = 1;
  for (long long int k = 1; k <= i; k++) {
    (f[k] = f[k - 1] * k) %= 998244353;
  }
}
long long int isprime(long long int n) {
  if (n == 1) return 0;
  for (long long int i = 2; i <= sqrt(n); i++)
    if (n % i == 0) return 0;
  return 1;
}
long long int find(long long int x) {
  if (f[x] == x)
    return x;
  else
    return f[x] = find(f[x]);
}
bool cmp(long long int x, long long int y) { return x < y; }
long long int comb(long long int i, long long int j) {
  long long int k = f[i];
  long long int g = (f[j] * (f[i - j])) % 998244353;
  long long int h = bpow(g, 998244353 - 2);
  return (k * h) % 998244353;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int n, x;
  cin >> n >> x;
  vector<long long int> a(n);
  for (long long int i = 0; i < n; i++) {
    cin >> a[i];
  }
  long long int dp[n + 1][3][3];
  for (long long int i = 0; i <= n; i++) {
    for (long long int j = 0; j < 3; j++) {
      for (long long int k = 0; k < 3; k++) {
        dp[i][j][k] = -1e18;
      }
    }
  }
  dp[0][0][0] = 0;
  for (long long int i = 0; i <= n; i++) {
    for (long long int j = 0; j < 3; j++) {
      for (long long int k = 0; k < 3; k++) {
        if (k < 2) {
          dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i][j][k]);
        }
        if (j < 2) {
          dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k]);
        }
        if (i < n) {
          dp[i + 1][j][k] =
              max(dp[i + 1][j][k],
                  dp[i][j][k] + (j == 1) * (a[i]) * (k == 1 ? x : 1));
        }
      }
      cout << "\n";
    }
    cout << "\n";
  }
  cout << dp[n][2][2] << "\n";
}
