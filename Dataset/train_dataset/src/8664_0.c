#include <bits/stdc++.h>
using namespace std;
long long a, b, l, r;
bool can(long long x) {
  if (x * (a + b) < l) return 1;
  return 0;
}
int get() {
  long long L = 0, R = (long long)(1e9 + 7), mid;
  while (R - L > 5) {
    mid = (L + R) / 2;
    if (can(mid))
      L = mid;
    else
      R = mid - 1;
  }
  for (long long i = L; i <= R; i++)
    if (can(i) == 0) return i - 1;
  return R;
}
int xx[100];
bool not_ok(int tt) {
  for (int i = 0; i < a; i++) {
    if (xx[i] == tt) return 1;
  }
  return 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> a >> b >> l >> r;
  long long idx = (a + b) * get();
  int res = 50;
  for (int i6 = 0; i6 < 26; i6++) {
    int aa[200000];
    for (int i = 1; i <= a; i++) aa[i] = i - 1;
    for (int i = a + 1; i <= a + b; i++) aa[i] = i6;
    for (int i = 0; i < a; i++) xx[i] = aa[a + b - i];
    int x = 0, j = a + b + 1;
    while (x < 100000) {
      int tt = 0;
      for (int i = 0; i < a; i++) {
        while (not_ok(tt)) tt++;
        aa[j++] = tt++;
      }
      for (int i = 0; i < b; i++) {
        aa[j] = aa[j - 1];
        j++;
      }
      for (int i = 0; i < a; i++) {
        xx[i] = aa[j - 1 - i];
      }
      x += (a + b);
    }
    bool is[26];
    memset(is, 0, sizeof is);
    for (int i = l - idx; i <= min(r - idx, 10000LL); i++) is[aa[i]] = 1;
    int ans = 0;
    for (int i = 0; i < 26; i++) ans += is[i];
    res = min(res, ans);
  }
  cout << res << '\n';
  return 0;
}
