#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:1000000000")
using namespace std;
const int maxn = (int)1e5 + 10;
long long dp[maxn];
const long long mod = (int)1e9 + 7;
long long my_pow(long long a, long long b) {
  if (b == 0) {
    return 1;
  }
  if (b % 2 == 0) {
    long long t = my_pow(a, b >> 1);
    return (t * t) % mod;
  }
  return (my_pow(a, b - 1) * a) % mod;
}
long long f[maxn], rf[maxn];
long long C(int n, int k) { return (((f[n] * rf[k]) % mod) * rf[n - k]) % mod; }
char s[maxn];
vector<pair<int, int> > z[maxn];
long long ans[maxn];
long long st[maxn];
int main() {
  f[0] = 1;
  rf[0] = 1;
  st[0] = 1;
  for (int i = 1; i < maxn; i++) {
    st[i] = st[i - 1] * 25;
    st[i] %= mod;
    f[i] = f[i - 1] * i;
    f[i] %= mod;
    rf[i] = my_pow(f[i], mod - 2);
  }
  int n;
  scanf("%d", &n);
  scanf("%s", s);
  vector<int> v;
  v.push_back(strlen(s));
  int now = strlen(s);
  int num = 0;
  for (int i = 0; i < n; i++) {
    int tp;
    scanf("%d", &tp);
    if (tp == 2) {
      int d;
      scanf("%d", &d);
      z[now].push_back(make_pair(d, num));
      num++;
    } else {
      scanf("%s", s);
      now = strlen(s);
      v.push_back(now);
    }
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  for (int i = 0; i < (int)v.size(); i++) {
    int len = v[i];
    for (int i = 0; i < len; i++) {
      dp[i] = 0;
    }
    dp[len] = 1;
    for (int i = len + 1; i < maxn; i++) {
      dp[i] = dp[i - 1] * 26 + st[i - len] * C(i - 1, len - 1);
      dp[i] %= mod;
    }
    for (int j = 0; j < (int)z[len].size(); j++) {
      ans[z[len][j].second] = dp[z[len][j].first];
    }
  }
  for (int i = 0; i < num; i++) {
    printf("%I64d\n", ans[i]);
  }
  return 0;
}
