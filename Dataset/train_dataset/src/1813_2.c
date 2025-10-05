#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
void exgcd(long long a, long long b, long long& d, long long& x, long long& y) {
  if (!b) {
    d = a, x = 1, y = 0;
  } else {
    exgcd(b, a % b, d, y, x);
    y -= (a / b) * x;
  }
}
long long add(long long a, long long b, long long Mod) {
  return ((a += b) >= Mod) ? (a - Mod) : (a);
}
long long mul(long long a, long long b, long long Mod) {
  long long rt = 0, pa = a;
  for (; b; pa = add(pa, pa, Mod), b >>= 1) {
    if (b & 1) {
      rt = add(rt, pa, Mod);
    }
  }
  return rt;
}
long long qpow(long long a, long long pos, long long Mod) {
  long long rt = 1;
  for (; pos; a = mul(a, a, Mod), pos >>= 1) {
    if (pos & 1) {
      rt = mul(rt, a, Mod);
    }
  }
  return rt;
}
long long ind(long long a, int g, int p, int c) {
  long long P = p, phi = p - 1;
  long long x0 = 0, tmp = 1, yb;
  while (tmp ^ (a % P)) x0++, tmp = tmp * g % P;
  for (int t = 2; t <= c; t++, phi *= p) {
    P *= p;
    tmp = qpow(g, x0, P);
    yb = qpow(g, phi, P);
    while (tmp ^ (a % P)) x0 += phi, tmp = mul(tmp, yb, P);
  }
  return x0;
}
int T, n;
long long a;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%lld", &a);
    long long b = a;
    for (n = 0; b; b /= 10, n++)
      ;
    long long M = 1ll << (n + 6);
    b = (((-1000000 * a) % M) + M) % M;
    if (!(b % 5)) b += M;
    b = (b + 1000000 * a) / M;
    long long ans = ind(b, 2, 5, 6 + n) + n + 6;
    printf("%lld\n", ans);
  }
  return 0;
}
