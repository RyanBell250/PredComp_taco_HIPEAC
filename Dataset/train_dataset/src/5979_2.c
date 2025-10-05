#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
long long powmod(long long a, long long b) {
  long long ans = 1;
  for (; b; b >>= 1) {
    if (b & 1) ans = (a * ans) % MOD;
    a = a * a % MOD;
  }
  return ans;
}
int fac[N], inv[N], p25[N];
void init() {
  inv[0] = fac[0] = p25[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = (long long)fac[i - 1] * i % MOD;
    inv[i] = powmod(fac[i], MOD - 2);
    p25[i] = (long long)p25[i - 1] * 25 % MOD;
  }
}
long long C(int n, int m) {
  return (long long)fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int a[N], ans[N];
vector<pair<int, int> > query[N];
void solve(int n) {
  a[n] = 1;
  for (int i = 0; i < n; i++) {
    a[i] = 0;
  }
  for (int i = n + 1; i < N; i++) {
    a[i] = (long long)a[i - 1] * 26 % MOD;
    a[i] = (a[i] + C(i - 1, n - 1) * p25[i - n]) % MOD;
  }
  for (auto q : query[n]) {
    ans[q.first] = a[q.second];
  }
}
char s[N];
int main() {
  init();
  int n, cur, q, x, cnt = 0;
  scanf("%d", &n);
  scanf("%s", s);
  cur = strlen(s);
  for (int i = 0; i < n; i++) {
    scanf("%d", &q);
    if (q == 1) {
      scanf("%s", s);
      cur = strlen(s);
    } else {
      scanf("%d", &x);
      query[cur].push_back(make_pair(cnt++, x));
    }
  }
  for (int i = 0; i < N; i++) {
    if (query[i].size() == 0) continue;
    solve(i);
  }
  for (int i = 0; i < cnt; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
