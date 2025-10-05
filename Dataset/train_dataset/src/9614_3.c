#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const long long inf = 0x3f3f3f3f;
const long long INF = 0x3f3f3f3f3f3f3f3f;
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline long long gc() {
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline long long read() {
  long long ret = 0, f = 0;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    ret = ret * 10 + c - 48;
    c = gc();
  }
  if (f) return -ret;
  return ret;
}
const long long maxn = 2e5 + 10;
const long long mod = 1e9 + 7;
long long qpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
long long inv(long long a) { return qpow(a, mod - 2); }
signed main() {
  long long T;
  cin >> T;
  while (T--) {
    long long n, m, rb, cb, rd, cd;
    long long p;
    cin >> n >> m;
    cin >> rb >> cb;
    cin >> rd >> cd;
    cin >> p;
    p = (1 - p * inv(100) % mod + mod) % mod;
    long long dx = -1, dy = -1;
    long long u = 0, v = 1;
    for (long long i = (1); i <= (4 * (n - 1) * (m - 1)); i++) {
      if (rb + dx < 1 || rb + dx > n) dx *= -1;
      if (cb + dy < 1 || cb + dy > m) dy *= -1;
      rb += dx;
      cb += dy;
      u++;
      if (rb == rd || cb == cd) {
        u = u * p % mod;
        v = v * p % mod;
      }
    }
    cout << (u * inv(1 - v) % mod + mod) % mod << "\n";
  }
  return 0;
}
