#include <bits/stdc++.h>
using namespace std;
int N, cnt;
bool comp[100005];
int primes[100005], mu[100005], smu[100005];
void euler() {
  comp[1] = mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!comp[i]) {
      primes[++cnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * primes[j] <= N; j++) {
      comp[i * primes[j]] = 1;
      if (i % primes[j] == 0) {
        mu[i * primes[j]] = 0;
        break;
      } else
        mu[i * primes[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= N; i++) smu[i] = smu[i - 1] + mu[i];
}
long long qpow(long long x, int n) {
  long long res = 1;
  while (n) {
    if (n & 1) res = res * x % int(1e9 + 7);
    x = x * x % int(1e9 + 7);
    n /= 2;
  }
  return res;
}
int main() {
  cin >> N;
  euler();
  long long ans = 1, p;
  int m;
  for (int d = 2; d <= N; d++) {
    m = N / d;
    p = m * qpow(N, int(1e9 + 7) - 2) % int(1e9 + 7);
    ans = (ans -
           mu[d] * p * qpow(1 - p + int(1e9 + 7), int(1e9 + 7) - 2) %
               int(1e9 + 7) +
           int(1e9 + 7)) %
          int(1e9 + 7);
  }
  cout << ans << endl;
  return 0;
}
