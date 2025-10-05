#include <bits/stdc++.h>
using namespace std;
int len, base;
vector<long long> fmtOr(vector<long long> A, int nrev = 1) {
  for (int i = 0; i < base; ++i)
    for (int S = 0; S < len; ++S)
      if (~S >> i & 1) A[S | (1 << i)] += nrev * A[S];
  return A;
}
int n, ppc[1 << 18], full;
long long f[1 << 18][18], ppcPow[1 << 18][19];
vector<long long> dp[20], ans, cur;
vector<int> z;
map<deque<int>, vector<int> > mp;
char s[20][20];
deque<int> copt;
int dfsC = 0, cpy = 0;
void dfs(int left, int smallest) {
  dfsC++;
  for (int i = 0; i < left; ++i) copt.push_front(1);
  static long long cu = 0;
  cu = 0;
  for (int S = 0; S < full; ++S)
    cu += ((ppc[S ^ (full - 1)] & 1) ? -1 : 1) * (cur[S] * ppcPow[S][left]);
  z = mp[copt];
  for (auto g : z) ans[g] = cu;
  for (int i = 0; i < left; ++i) copt.pop_front();
  auto ori = cur;
  for (int cho = smallest; cho <= left; ++cho) {
    copt.push_back(cho);
    for (int i = 0; i < full; ++i) cur[i] *= dp[cho][i];
    dfs(left - cho, cho);
    copt.pop_back();
    cur = ori;
  }
}
int main() {
  for (int i = 1; i < 1 << 18; ++i) {
    ppc[i] = ppc[i >> 1] + (i & 1);
    ppcPow[i][0] = 1;
    for (int j = 1; j <= 18; ++j) ppcPow[i][j] = ppcPow[i][j - 1] * ppc[i];
  }
  scanf("%d", &n);
  len = 1 << n, base = n;
  full = 1 << n;
  for (int i = 0; i < 1 << (n - 1); ++i) {
    deque<int> mult;
    int ones = 0, sz = n;
    for (int j = 0; j < n - 1; ++j)
      if (i >> j & 1) {
        ones++;
      } else
        mult.push_back(ones + 1), sz -= ones + 1, ones = 0;
    mult.push_back(ones + 1);
    assert(sz == ones + 1);
    sort(mult.begin(), mult.end());
    mp[mult].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    dp[i].assign(full, 0);
  }
  dp[n].assign(full, 0);
  cur.assign(full, 1);
  ans.assign(full / 2, 0);
  for (int i = 0; i < n; ++i) f[1 << i][i] = 1;
  for (int used = 0; used < full; ++used) {
    for (int las = 0; las < n; ++las)
      if (f[used][las]) {
        for (int nxt = 0; nxt < n; ++nxt)
          if ((~used >> nxt & 1) && s[las][nxt] == '1')
            f[used | (1 << nxt)][nxt] += f[used][las];
      }
  }
  for (int used = 0; used < full; ++used)
    for (int las = 0; las < n; ++las) dp[ppc[used]][used] += f[used][las];
  for (int i = 1; i <= n; ++i) dp[i] = fmtOr(dp[i], 1);
  dfs(n, 2);
  for (int i = 0; i < n - 1; ++i)
    for (int S = 0; S < 1 << (n - 1); ++S)
      if (~S >> i & 1) ans[S] -= ans[S | (1 << i)];
  for (auto g : ans) printf("%lld ", g);
  return 0;
}
