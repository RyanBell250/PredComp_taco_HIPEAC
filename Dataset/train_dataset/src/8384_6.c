#include <bits/stdc++.h>
using namespace std;
long long int mod = 1e9 + 7;
long long int mul(long long int a, long long int b) {
  return ((a % mod) * (b % mod)) % mod;
}
long long int add(long long int a, long long int b) {
  return ((a % mod) + (b % mod)) % mod;
}
long long int sub(long long int a, long long int b) {
  return ((a % mod) - (b % mod) + mod) % mod;
}
long long int gcdExtended(long long int a, long long int b, long long int *x,
                          long long int *y) {
  if (a == 0) {
    *x = 0, *y = 1;
    return b;
  }
  long long int x1, y1;
  long long int gcd = gcdExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}
long long int modInverse(long long int b) {
  long long int x, y;
  long long int g = gcdExtended(b, mod, &x, &y);
  if (g != 1) return -1;
  return (x % mod + mod) % mod;
}
long long int modDivide(long long int a, long long int b) {
  a = a % mod;
  long long int inv = modInverse(b);
  if (inv == -1)
    return -1;
  else
    return (inv * a) % mod;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int i, t, j, inp, n, n1, n0;
  cin >> n;
  string str;
  cin >> str;
  vector<long long int> zeros(n, 0);
  vector<long long int> ones(n, 0);
  if (str[0] == '0')
    zeros[0] = 1;
  else
    ones[0] = 1;
  for (j = 1; j < n; j++) {
    if (str[j] == '0') {
      zeros[j] = zeros[j - 1] + 1;
      ones[j] = ones[j - 1];
    } else {
      zeros[j] = zeros[j - 1];
      ones[j] = ones[j - 1] + 1;
    }
  }
  map<long long int, long long int> mp;
  long long int ans = 0;
  mp[0] = -1;
  for (j = 0; j < n; j++) {
    long long int del = ones[j] - zeros[j];
    if (mp.find(del) != mp.end()) {
      ans = max(ans, j - mp[del]);
    } else {
      mp[del] = j;
    }
  }
  cout << ans << endl;
  return 0;
}
