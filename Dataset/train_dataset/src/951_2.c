#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = (long long int)1e9 + 1;
const int mod = 998244353, sz = 5, MAX = (long long int)1e6 + 10;
string fir = "Monocarp", sec = "Bicarp";
void precom() {}
void result(long long int n, vector<long long int> a) {
  vector<long long int> l(n), r(n);
  for (long long int i = 0; i < n; i++) l[i] = r[i] = i;
  for (long long int i = 1; i < n; i++) {
    long long int st = i;
    while (st && a[i] >= a[st - 1]) {
      st = l[st - 1];
      l[i] = st;
    }
  }
  for (long long int i = n - 2; i >= 0; i--) {
    long long int st = i;
    while (st < n - 1 && a[i] > a[st + 1]) {
      st = r[st + 1];
      r[i] = st;
    }
  }
  long long int ans = 0;
  for (long long int i = 0; i < n; i++) {
    ans += a[i] * (i - l[i] + 1) * (r[i] - i + 1);
  }
  cout << ans << "\n";
  return;
}
void work() {
  long long int n, q;
  cin >> n >> q;
  vector<long long int> a(N, 0ll);
  for (long long int i = 0; i < n; i++) cin >> a[i];
  vector<long long int> b(n - 1);
  for (long long int i = 0; i + 1 < n; i++) b[i] = abs(a[i] - a[i + 1]);
  while (q--) {
    long long int x, y;
    cin >> x >> y;
    x--, y--;
    result(y - x, vector<long long int>(b.begin() + x, b.begin() + y));
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long long int t;
  t = 1;
  while (t--) {
    work();
  }
  return 0;
}
