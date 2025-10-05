#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9 + 7;
long long INF = 1e7;
double EPS = 1e-12;
double tick() {
  static clock_t oldt;
  clock_t newt = clock();
  double diff = 1.0 * (newt - oldt) / CLOCKS_PER_SEC;
  oldt = newt;
  return diff;
}
long long int powP(long long int a, long long int b) {
  if (b == 0) return 1 % mod;
  long long int k;
  k = powP(a, b / 2);
  k = k * k % mod;
  if (b % 2 == 0)
    return k;
  else
    return a * k % mod;
}
bool bitSet(long long int n, long long int i) {
  if ((n & (1LL << i)) != 0)
    return true;
  else
    return false;
}
long long int findGcd(long long int a, long long int b) {
  if (a == 0)
    return b;
  else
    return findGcd(b % a, a);
}
string S[300010];
long long int A[300010], B[300010], C[300010];
map<string, vector<long long int> > M;
bool dp[503][503];
long long int Next[503][503], Reduce[503][503], Total[503][503];
int main() {
  long long int T, i, p, j, l, n, e, r, b, c, k, m, q, a, d, w, x, y, u, v, z,
      t, curr, prev, sum, ans, pos, val, countA, indicator;
  scanf("%lld", &n);
  for (long long int i = (1); i <= (n); ++i) {
    cin >> S[i];
    A[i] = S[i].size();
    A[i] += A[i - 1];
    M[S[i]].push_back(i);
  }
  for (const auto& i : M) {
    for (const auto& a : i.second) {
      for (const auto& b : i.second) {
        dp[a][b] = dp[b][a] = true;
      }
    }
  }
  for (long long int i = (1); i <= (n); ++i)
    for (long long int j = (i + 1); j <= (n); ++j) {
      curr = 0;
      while (i + curr < j and j + curr <= n and dp[i + curr][j + curr]) {
        curr++;
        if (Next[i][curr] == 0) {
          Next[i][curr] = j;
          Reduce[i][curr] = (A[i + curr - 1] - A[i - 1] + curr - 1) - curr;
        }
      }
    }
  ans = 0;
  for (long long int i = (n); i >= (1); --i)
    for (long long int curr = (1); curr <= (n); ++curr) {
      if (Next[i][curr] == 0) continue;
      Total[i][curr] += 1 + Total[Next[i][curr]][curr];
      ans = max(ans, (1 + Total[i][curr]) * Reduce[i][curr]);
    }
  printf("%lld\n", A[n] + n - 1 - ans);
  return 0;
}
