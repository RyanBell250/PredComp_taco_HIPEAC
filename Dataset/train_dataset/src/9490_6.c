#include <bits/stdc++.h>
using namespace std;
long long dpst[1100000], dpend[1100000];
int prevw[1100000], prevb[1100000];
string s;
int n, k;
bool chc(int bit, int n, int tar, int am) {
  if (am == k) return chc(bit, n, tar + 1, 0);
  if (n == 0) {
    if (tar >= 2) return true;
    return false;
  }
  if (s[n - 1] != 'X') {
    if (s[n - 1] == 'B' && (bit % 2)) return false;
    if (s[n - 1] == 'W' && ((bit % 2) == 0)) return false;
  }
  if (bit % 2 == (tar + 1) % 2) return chc(bit / 2, n - 1, tar, am + 1);
  return chc(bit / 2, n - 1, tar, 0);
}
void printing(int bit, int in) {
  if (in == 0) return;
  printing(bit / 2, in - 1);
  printf("%d", bit % 2);
}
int print(int n, int k) {
  int i;
  int ans = 0;
  for (i = 0; i < (1LL << n); i++) {
    if (!chc(i, n, 0, 0)) continue;
    cout << i << endl;
    printing(i, n);
    printf("\n");
    ans++;
  }
  return ans;
}
int main() {
  while (cin >> n >> k) {
    cin >> s;
    int i;
    int pw = -1, push_back = -1;
    for (i = 0; i < n; i++) {
      if (s[i] == 'W') pw = i;
      prevw[i] = pw;
    }
    dpst[0] = 1;
    long long cnt;
    for (i = 1; i <= n; i++) {
      if (s[i - 1] == 'X')
        cnt = 2;
      else
        cnt = 1;
      dpst[i] = (dpst[i - 1] * cnt) % 1000000007;
      if (prevw[i - 1] >= i - k) continue;
      if (i - 1 - k >= 0 && s[i - 1 - k] == 'B') continue;
      long long sub = 1;
      if (i - 1 - k >= 0) sub = dpst[i - k - 1];
      dpst[i] = (dpst[i] + 1000000007 - sub) % 1000000007;
    }
    reverse(s.begin(), s.end());
    ;
    for (i = 0; i < n; i++) {
      if (s[i] == 'B') push_back = i;
      prevb[i] = push_back;
    }
    dpend[0] = 1;
    cnt;
    for (i = 1; i <= n; i++) {
      if (s[i - 1] == 'X')
        cnt = 2;
      else
        cnt = 1;
      dpend[i] = (dpend[i - 1] * cnt) % 1000000007;
      if (prevb[i - 1] >= i - k) continue;
      if (i - 1 - k >= 0 && s[i - 1 - k] == 'W') continue;
      long long sub = 1;
      if (i - 1 - k >= 0) sub = dpend[i - k - 1];
      dpend[i] = (dpend[i] + 1000000007 - sub) % 1000000007;
    }
    long long pow2 = 1;
    dpend[0] = 0;
    for (i = 1; i <= n; i++) {
      if (s[i - 1] == 'X') pow2 = (pow2 * 2) % 1000000007;
      dpend[i] = (pow2 + 1000000007 - dpend[i]) % 1000000007;
    }
    long long ans = 0;
    reverse(s.begin(), s.end());
    ;
    if (prevw[k - 1] <= -1) ans = dpend[n - k];
    for (i = -1; i < n; i++) {
      if (i + 1 + k >= n) break;
      if (s[i + 1] == 'B') continue;
      if (prevw[i + 1 + k] > i + 1) continue;
      ans += (dpst[i + 1] * dpend[n - i - 2 - k]) % 1000000007;
      ans %= 1000000007;
    }
    cout << ans << endl;
  }
  return 0;
}
