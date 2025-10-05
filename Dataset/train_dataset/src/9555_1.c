#include <bits/stdc++.h>
using namespace std;
const int64_t maxn = 5e5 + 42;
const int64_t mod = 1e9 + 7;
int64_t bpow(int64_t x, int64_t n) {
  return n ? n % 2 ? x * bpow(x, n - 1) % mod : bpow(x * x % mod, n / 2) : 1;
}
int64_t inv(int64_t x) { return bpow(x, mod - 2); }
map<tuple<int64_t, int64_t, int64_t>, int64_t> prec;
int64_t get(int64_t r, int64_t n, int64_t k) {
  if (k == 1) {
    return inv(n + 1);
  } else if (prec.count(make_tuple(r, n, k))) {
    return prec[{r, n, k}];
  } else {
    int64_t t = k / 2;
    int64_t ans = 0;
    for (int64_t i = r; i <= n; i++) {
      ans += get(i, n, t) * get(r, i, k - t);
      ans %= mod;
    }
    return prec[{r, n, k}] = ans;
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int64_t n, k;
  cin >> n >> k;
  vector<pair<int64_t, int64_t>> divs;
  for (int64_t i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      int64_t cnt = 0;
      while (n % i == 0) {
        cnt++;
        n /= i;
      }
      divs.emplace_back(i, cnt);
    }
  }
  if (n != 1) {
    divs.emplace_back(n, 1);
  }
  int64_t ans = 1;
  for (auto it : divs) {
    int64_t cur = 0;
    for (int64_t i = 0; i <= it.second; i++) {
      cur += bpow(it.first, i) * get(i, it.second, k);
      cur %= mod;
    }
    ans = ans * cur % mod;
  }
  cout << ans << endl;
  return 0;
}
