#include <bits/stdc++.h>
using namespace std;
const long long INF = 0x7f7f7f7f7f7f;
const long long mo = 998244353;
long long k, l, cnt, r, a[20], pw[20];
pair<long long, long long> dp[20][(1 << 10) + 5];
pair<long long, long long> dfs(long long pos, long long S, bool lead,
                               bool lim) {
  if (!~pos) return pair<long long, long long>(__builtin_popcount(S) <= k, 0);
  if (!lead && !lim && ~dp[pos][S].first) return dp[pos][S];
  long long up = lim ? a[pos] : 9;
  pair<long long, long long> ans = make_pair(0, 0);
  for (long long i = 0; i <= up; i++) {
    long long S1 = (lead && i == 0) ? S : (S | (1 << i));
    pair<long long, long long> nxt =
        dfs(pos - 1, S1, lead && i == 0, lim && i == up);
    ans = pair<long long, long long>(
        (ans.first + nxt.first) % mo,
        (nxt.first * pw[pos] % mo * i % mo + nxt.second + ans.second) % mo);
  }
  if (!lim && !lead) dp[pos][S] = ans;
  return ans;
}
long long calc(long long x) {
  memset(a, 0, sizeof(a));
  cnt = 0;
  while (x) a[cnt++] = x % 10, x /= 10;
  for (long long i = 0; i <= 18; i++)
    for (long long j = 0; j < (1 << 10); j++)
      dp[i][j].first = dp[i][j].second = -1;
  return dfs(cnt - 1, 0, 1, 1).second;
}
signed main() {
  pw[0] = 1;
  for (long long i = 1; i <= 18; i++) pw[i] = pw[i - 1] * 10ll % mo;
  scanf("%lld %lld %lld", &l, &r, &k);
  printf("%lld\n", (calc(r) - calc(l - 1) + mo) % mo);
  return 0;
}
