#include <bits/stdc++.h>
using namespace std;
const long long Nfact = 200005;
const long long mod = 1000000007;
const long long Nsieve = 1000005;
vector<bool> is_prime(Nsieve, true);
void sieve() {
  is_prime[0] = is_prime[1] = false;
  for (long long i = 2; i * i <= Nsieve; i++) {
    if (is_prime[i]) {
      for (long long j = i * i; j <= Nsieve; j += i) is_prime[j] = false;
    }
  }
}
long long bSearch(long long l, long long r, long long x,
                  vector<long long> arr) {
  while (l <= r) {
    long long m = l + (r - l) / 2;
    if (arr[m] == x) return m;
    if (arr[m] < x)
      l = m + 1;
    else
      r = m - 1;
  }
  return -1;
}
void primeFactors(long long n) {
  while (n % 2 == 0) {
    n = n / 2;
  }
  for (long long i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      n = n / i;
    }
  }
  if (n > 2) cout << n << " ";
}
long long power(long long x, long long y, long long p) {
  long long res = 1;
  x = x % p;
  while (y > 0) {
    if (y & 1) res = (res * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}
long long modulo(long long a, long long b) {
  long long c = a % b;
  return (c < 0) ? c + b : c;
}
long long mul(long long x, long long y) { return (x * y) % mod; }
long long inv(long long x) { return power(x, mod - 2, mod); }
long long divide(long long x, long long y) { return mul(x, inv(y)); }
long long fact[Nfact];
void precalc() {
  fact[0] = 1;
  for (long long i = 1; i < Nfact; i++) fact[i] = mul(fact[i - 1], i);
}
long long nCr(long long n, long long k) {
  if (n < k) return 0;
  return divide(fact[n], mul(fact[k], fact[n - k]));
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long t = 1;
  while (t--) {
    long long n, w;
    cin >> n >> w;
    vector<pair<long long, long long> > vec(n), ans(n);
    for (long long i = 0; i < n; i++) {
      cin >> vec[i].first;
      vec[i].second = i;
    }
    sort(vec.rbegin(), vec.rend());
    for (long long i = 0; i < n; i++) {
      if (w - (vec[i].first + 1) / 2 >= 0) {
        w -= (vec[i].first + 1) / 2;
        ans[i].second = (vec[i].first + 1) / 2;
        ans[i].first = vec[i].second;
      } else {
        cout << -1 << endl;
        return 0;
      }
    }
    long long i = 0, mini;
    while (w) {
      mini = min(w, vec[i].first - ans[i].second);
      ans[i].second += mini;
      w -= mini;
      i++;
    }
    sort(ans.begin(), ans.end());
    ;
    for (long long i = 0; i < n; i++) {
      cout << ans[i].second << " ";
    }
  }
  cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
  return 0;
}
