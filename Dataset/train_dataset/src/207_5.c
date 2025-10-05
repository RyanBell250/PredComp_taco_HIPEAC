#include <bits/stdc++.h>
using namespace std;
static long long int mod = (long long)(1e9) + 7;
long long power(long long x, long long y, long long p) {
  long long res = 1;
  x = x % p;
  if (x == 0) return 0;
  while (y > 0) {
    if (y & 1) res = (res * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}
vector<int> prime((long long)(1e7), 1);
void seive(long long n) {
  long long i, j;
  prime[0] = prime[1] = 0;
  for (i = 2; i * i <= n; i++) {
    if (prime[i] == 1) {
      for (j = i * i; j <= n; j += i) prime[j] = 0;
    }
  }
}
void solve() {
  char ch[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int n;
  cin >> n;
  string str1, str2;
  cin >> str1;
  cin >> str2;
  int i, ans = 0, zeros = 0;
  map<char, int> m1;
  for (i = 0; i < n - 1; i++) {
    map<char, int> m1;
    m1[str1[i]]++;
    m1[str2[i]]++;
    if (m1['0'] > 0 && m1['1'] > 0)
      ans += 2;
    else {
      m1.clear();
      m1[str1[i + 1]]++;
      m1[str2[i + 1]]++;
      if (str1[i] == '0' && str2[i] == '0' && m1['1'] == 2) {
        ans += 2;
        i++;
      } else if (str1[i] == '1' && str2[i] == '1' &&
                 (str1[i + 1] == '0' || str2[i + 1] == '0')) {
        ans += 2;
        i++;
      } else if (str1[i] == '0' && str2[i] == '0')
        ans++;
    }
  }
  if (i == n)
    ;
  else {
    map<char, int> m1;
    m1[str1[i]]++;
    m1[str2[i]]++;
    if (m1['0'] > 0 && m1['1'] > 0)
      ans += 2;
    else if (m1['0'] > 0)
      ans++;
  }
  cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long t;
  cin >> t;
  while (t--) solve();
  return 0;
}
