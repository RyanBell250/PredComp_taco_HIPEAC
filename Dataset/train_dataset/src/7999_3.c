#include <bits/stdc++.h>
using namespace std;
template <class T>
inline T read() {
  T x = 0, w = 1;
  char c = getchar();
  for (; !isdigit(c); c = getchar())
    if (c == '-') w = -w;
  for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
  return x * w;
}
template <class T>
inline T read(T& x) {
  return x = read<T>();
}
const int N = 18;
int e[N];
long long dp[1 << N][N], g[N + 1][1 << N];
long long d[1 << N], cur[N + 1][1 << N];
long long f[1 << N];
int main() {
  int n = read<int>();
  for (int i = 0; i < n; ++i) {
    static char s[N];
    scanf("%s", s);
    for (int j = 0; j < n; ++j)
      if (s[j] == '1') e[i] |= 1 << j;
  }
  for (int i = 0; i < n; ++i) dp[1 << i][i] = 1;
  for (int mask = 0; mask < 1 << n; ++mask)
    for (int i = 0; i < n; ++i)
      if (dp[mask][i]) {
        for (int j = 0; j < n; ++j)
          if (~mask >> j & 1 and e[i] >> j & 1)
            dp[mask | 1 << j][j] += dp[mask][i];
        g[__builtin_popcount(mask)][mask] += dp[mask][i];
      }
  for (int len = 1; len <= n; ++len) {
    for (int i = 0; i < n; ++i)
      for (int mask = 0; mask < 1 << n; ++mask)
        if (mask >> i & 1) g[len][mask] += g[len][mask ^ 1 << i];
  }
  map<vector<int>, vector<int> > ok;
  for (int mask = 0; mask < 1 << (n - 1); ++mask) {
    int x = 0;
    vector<int> t;
    for (; x < n; ++x) {
      int len = 1;
      while (mask >> x & 1) ++x, ++len;
      t.push_back(len);
    }
    sort(t.begin(), t.end());
    ok[t].push_back(mask);
  }
  vector<int> a;
  for (int mask = 0; mask < 1 << n; ++mask) d[mask] = 1;
  function<void(int, int)> dfs = [&](int s, int last) {
    if (s == n) {
      long long res = 0;
      int x = (1 << n) - 1;
      for (int mask = 0; mask < 1 << n; ++mask) {
        if (__builtin_popcount(mask) % 2 == 0)
          res += d[x ^ mask];
        else
          res -= d[x ^ mask];
      }
      for (int c : ok[a]) f[c] += res;
      return;
    }
    if (s + last > n) return;
    for (int mask = 0; mask < 1 << n; ++mask) cur[s][mask] = d[mask];
    for (int i = last; s + i <= n; ++i) {
      if (s + i != n and s + 2 * i > n) continue;
      a.push_back(i);
      for (int mask = 0; mask < 1 << n; ++mask) d[mask] *= g[i][mask];
      dfs(s + i, i);
      for (int mask = 0; mask < (1 << n); ++mask) d[mask] = cur[s][mask];
      a.pop_back();
    }
  };
  dfs(0, 1);
  for (int i = 0; i < n - 1; ++i)
    for (int mask = 0; mask < 1 << (n - 1); ++mask)
      if (~mask >> i & 1) f[mask] -= f[mask | 1 << i];
  for (int mask = 0; mask < 1 << (n - 1); ++mask)
    printf("%lld%c", f[mask], " \n"[mask == (1 << (n - 1)) - 1]);
  return 0;
}
