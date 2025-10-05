#include <bits/stdc++.h>
using namespace std;
const int mn = 1e6 + 5;
int n;
int a[mn];
bool isNotPrime[mn + 1];
int mu[mn + 1], phi[mn + 1], cnt;
long long primes[mn + 1];
inline void euler() {
  isNotPrime[0] = isNotPrime[1] = true;
  mu[1] = 1;
  phi[1] = 1;
  for (int i = 2; i <= mn; i++) {
    if (!isNotPrime[i]) {
      primes[++cnt] = i;
      mu[i] = -1;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= cnt; j++) {
      int t = i * primes[j];
      if (t > mn) break;
      isNotPrime[t] = true;
      if (i % primes[j] == 0) {
        mu[t] = 0;
        phi[t] = phi[i] * primes[j];
        break;
      } else {
        mu[t] = -mu[i];
        phi[t] = phi[i] * (primes[j] - 1);
      }
    }
  }
}
bool isprime(long long x) {
  if (x == 1) return 0;
  for (long long i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}
int main() {
  euler();
  scanf("%d", &n);
  long long sum = 0;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
  long long ans = 9e18;
  if (isprime(sum)) primes[++cnt] = sum;
  for (int i = 1; i <= cnt; i++) {
    if (sum % primes[i] == 0) {
      long long rans = 0;
      long long t = 0;
      for (int j = 1; j <= n; j++) {
        rans += abs(t);
        t = (t + a[j]) % primes[i];
        if (t > primes[i] / 2) t = -primes[i] + t;
      }
      ans = min(rans, ans);
    }
  }
  if (ans == 9e18)
    puts("-1");
  else
    printf("%lld\n", ans);
  return 0;
}
