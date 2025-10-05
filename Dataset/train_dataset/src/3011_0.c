#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (b == 0LL) return a;
  return gcd(b, a % b);
}
long long bigmod(long long a, long long b, long long mod) {
  if (b == 0LL) return 1LL;
  long long sq = bigmod(a, b / 2LL, mod);
  sq = (sq * sq) % mod;
  if (b & 1LL) return (sq * (a % mod)) % mod;
  return sq;
}
const int SIZE = 1000010;
vector<int> prime(SIZE + 1, 0);
vector<int> primes;
void sieve(const int n) {
  prime[1] = 1;
  for (int p = 2; p * p <= n; p++) {
    if (!prime[p]) {
      for (int i = p * p; i <= n; i += p) prime[i] = p;
    }
  }
  for (int i = 2; i <= n; i++)
    if (!prime[i]) primes.push_back(i);
}
void solve() {
  int n;
  scanf("%d", &n);
  sieve(SIZE);
  vector<int> a(n);
  vector<int> fr(SIZE, 0);
  for (int i = 1; i <= SIZE - 2; i++) {
    fr[i] = fr[i - 1] + (!prime[i]);
  }
  vector<int> sq(SIZE + 2, 0);
  for (int i = 1; i * i <= (int)(sq).size(); i++) {
    sq[i * i] = i;
  }
  for (int i = 3; i < (int)(sq).size(); i++) {
    if (sq[i] == 0) sq[i] = sq[i - 1];
  }
  for (auto &x : (a)) {
    scanf("%d", &x);
    int ans = fr[x] - fr[sq[x]];
    if (x <= 3) ans = x - 1;
    ans += 1;
    printf("%d\n", ans);
  }
}
int main() {
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
