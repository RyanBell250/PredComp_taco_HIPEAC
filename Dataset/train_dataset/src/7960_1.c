#include <bits/stdc++.h>
using namespace std;
template <typename Tleaf>
void print(Tleaf &&leaf, long long n) {
  for (long long i = 1; i <= n; i++) cout << leaf[i] << " \n"[i == n];
}
template <typename Tleaf>
void print(Tleaf &&leaf, long long n, long long m) {
  for (long long i = 1; i <= n; i++) print(leaf[i], m);
}
const long long MOD = 1000 * 1000 * 1000 + 7;
long long mod_expo(long long x, long long p) {
  long long res = 1;
  x = ((x % MOD) + MOD) % MOD;
  while (p > 0) {
    if (p & 1) res = (res * x) % MOD;
    x = (x * x) % MOD;
    p /= 2;
  }
  return res;
}
long long mod_inv(long long x) { return mod_expo(x, MOD - 2); }
vector<long long> fact, inv_fact;
void precalculate_factorials(long long MAX_FACT) {
  fact.resize(MAX_FACT + 1);
  inv_fact.resize(MAX_FACT + 1);
  fact[0] = 1;
  for (long long i = 1; i <= MAX_FACT; i++) fact[i] = (fact[i - 1] * i) % MOD;
  inv_fact[MAX_FACT] = mod_inv(fact[MAX_FACT]);
  for (long long i = MAX_FACT - 1; i >= 0; i--)
    inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
}
long long nPr(long long n, long long r) {
  return (n < r) ? 0 : (fact[n] * inv_fact[n - r]) % MOD;
}
long long nCr(long long n, long long r) {
  if (n < 0) return 0;
  return (n < r) ? 0 : (nPr(n, r) * inv_fact[r]) % MOD;
}
long long starsAndBars(long long stars, long long bars) {
  if (bars == -1 && stars == 0)
    return 1;
  else if (bars == -1)
    return 0;
  long long ways = 0;
  if (stars >= 0 && bars >= 0) ways = nCr(stars + bars, bars);
  return ways;
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  precalculate_factorials(1000005);
  long long f, w, h;
  cin >> f >> w >> h;
  h++;
  long long totways = 0, goodways = 0;
  for (long long i = 1; i <= f + w; i++) {
    {
      long long food = (i + 1) / 2, wine = i / 2;
      long long gways = 0, tways = 0;
      tways = (starsAndBars(w - wine, wine - 1) *
               starsAndBars(f - food, food - 1)) %
              MOD;
      gways = (starsAndBars(f - food, food - 1) *
               starsAndBars(w - (wine * h), wine - 1)) %
              MOD;
      totways += tways;
      totways %= MOD;
      goodways += gways;
      goodways %= MOD;
    }
    {
      long long food = i / 2, wine = (i + 1) / 2;
      long long gways = 0, tways = 0;
      tways = (starsAndBars(w - wine, wine - 1) *
               starsAndBars(f - food, food - 1)) %
              MOD;
      gways = (starsAndBars(f - food, food - 1) *
               starsAndBars(w - (wine * h), wine - 1)) %
              MOD;
      totways += tways;
      totways %= MOD;
      goodways += gways;
      goodways %= MOD;
    }
  }
  cout << (goodways * mod_inv(totways)) % MOD << "\n";
}
