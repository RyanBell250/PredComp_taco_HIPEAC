#include <bits/stdc++.h>
const int inf = (1ll << 30) - 1;
const int maxn = (int)1e5 + 10;
const int mod = (int)1e9 + 7;
using namespace std;
int n;
long long k;
pair<long long, long long> a[100100];
long long b[100100];
long long lim = 2 * (long long)(1e18) + 1;
long long M = lim;
vector<long long> d, c;
long long L[2000100], R[2000100];
void precalcleft() {
  for (int i = 0; i < n; i++) {
    b[i] = a[i].first;
  }
  sort(b, b + n);
  int r = n - 1;
  for (int i = 0; i < c.size(); i++) {
    L[i] = k + 1;
  }
  long long second = 0;
  for (int i = (int)c.size() - 1; i >= 0 && second <= k; i--) {
    if (i + 1 < c.size() && n != r + 1) {
      long long a = n - r - 1;
      long long b = c[i + 1] - c[i];
      if ((k + 1) / b >= a) {
        second += a * b;
      } else
        second = k + 1;
    }
    while (second <= k && r >= 0 && c[i] < b[r]) {
      second += b[r] - c[i];
      r--;
    }
    L[i] = min(second, k + 1);
  }
}
void precalcright() {
  for (int i = 0; i < n; i++) {
    b[i] = a[i].second;
  }
  sort(b, b + n);
  int r = 0;
  for (int i = 0; i < c.size(); i++) {
    R[i] = k + 1;
  }
  long long second = 0;
  for (int i = 0; i < c.size(); i++) {
    if (i > 0 && r > 0) {
      long long a = r;
      long long b = c[i] - c[i - 1];
      if ((k + 1) / b >= a) {
        second += a * b;
      } else
        second = k + 1;
    }
    while (second <= k && r < n && c[i] > b[r]) {
      second += c[i] - b[r];
      r++;
    }
    R[i] = min(second, k + 1);
  }
}
bool can(int l) {
  for (int i = l - 1; i < c.size(); i++) {
    if (c[i] - c[i - l + 1] > M) continue;
    if (L[i - l + 1] + R[i] <= k) {
      return 1;
    }
  }
  return 0;
}
void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
    M = min(a[i].second - a[i].first, M);
  }
  d.push_back(4);
  d.push_back(7);
  while (d.size() > 0) {
    vector<long long> dd;
    for (int i = 0; i < d.size(); i++) {
      c.push_back(d[i]);
      if ((lim - 4) / 10 >= d[i] && d[i] * 10 + 4 <= lim)
        dd.push_back(d[i] * 10 + 4);
      if ((lim - 7) / 10 >= d[i] && d[i] * 10 + 7 <= lim)
        dd.push_back(d[i] * 10 + 7);
    }
    d = dd;
  }
  precalcleft();
  precalcright();
  int l = 1, r = c.size();
  int res = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (can(mid)) {
      res = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }
  cout << res << "\n";
}
int main() {
  int t = 1;
  for (int i = 1; i <= t; i++) {
    solve();
  }
  return 0;
}
