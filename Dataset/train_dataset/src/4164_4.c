#include <bits/stdc++.h>
using namespace std;
template <typename T>
void dbg(T a) {}
template <typename T, typename... Arg>
void dbg(T a, Arg... arg) {}
const int maxn = (2e5) + 7;
const int maxlog = 20;
const int inf = (1e9) + 7;
const long long LLinf = (1e18) + 7;
const long double eps = 1e-9;
const long long mod = 1e9 + 7;
long long sil[maxn], odwsil[maxn];
long long pot(long long a, long long w) {
  if (w == 0) return 1;
  long long b = pot(a, w / 2);
  b *= b;
  b %= mod;
  if (w & 1) b = (b * a) % mod;
  return b;
}
long long net(int n, int k) {
  long long res = sil[n];
  res = (res * odwsil[k]) % mod;
  res = (res * odwsil[n - k]) % mod;
  return res;
}
int s(int n, int k) {
  long long res = 0LL;
  for (int j = 0; j <= k; j++) {
    res = (res + ((pot(-1, (j ^ k) & 1) * net(k, j)) % mod) * pot(j, n)) % mod;
  }
  res = (res * odwsil[k]) % mod;
  return res;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  sil[0] = 1;
  for (int i = 1; i < maxn; i++) sil[i] = (sil[i - 1] * (long long)i) % mod;
  for (int i = 0; i < maxn; i++) odwsil[i] = pot(sil[i], mod - 2);
  int n, k;
  cin >> n >> k;
  long long suma = 0LL;
  for (int i = 0; i < n; i++) {
    long long a;
    cin >> a;
    suma += a;
  }
  suma %= mod;
  suma *= (s(n, k) + (n - 1) * (long long)s(n - 1, k)) % mod;
  suma %= mod;
  suma = (suma + mod) % mod;
  cout << suma;
  return 0;
}
