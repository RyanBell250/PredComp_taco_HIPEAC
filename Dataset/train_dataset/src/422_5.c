#include <bits/stdc++.h>
using namespace std;
struct num {
  string x;
  string y;
};
long long pow(long long base, long long os) {
  if (os == 0) return 1;
  long long z = pow(base, os / 2);
  z *= z;
  return (os % 2 ? z * base : z);
}
long long mod = 1e9 + 7;
long long powm(long long base, long long os) {
  if (os == 0) return 1;
  long long z = powm(base, os / 2);
  z = ((z % mod) * (z % mod)) % mod;
  return (os % 2 ? ((z % mod) * (base % mod)) % mod : z % mod);
}
bool isprime(int x) {
  for (long long i = 2; i * i <= x; i += 1 + (1 & i)) {
    if (x % i == 0) return false;
  }
  return true;
}
long long n, a, b;
void run_case() {}
long long inv(long long x) { return powm(x, mod - 2) % mod; }
long long fact[1000021];
long long choos(long long r) {
  return ((fact[n] % mod) *
          (inv((fact[n - r] % mod) * (fact[r] % mod) % mod) % mod)) %
         mod;
}
bool good(long long sum) {
  while (sum) {
    long long s = sum % 10;
    if (s != a && s != b) return false;
    sum /= 10;
  }
  return true;
}
int main() {
  cin >> a >> b >> n;
  fact[0] = 1;
  for (long long i = 1; i <= n; i++)
    fact[i] = ((i % mod) * (fact[i - 1] % mod)) % mod;
  long long ans = 0;
  for (int i = 0; i <= n; i++) {
    long long sum = a * (i) + (n - i) * b;
    if (good(sum)) {
      ans = ((ans % mod) + (choos(i) % mod)) % mod;
    }
  }
  cout << ans;
}
