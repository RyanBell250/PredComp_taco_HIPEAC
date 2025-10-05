#include <bits/stdc++.h>
using namespace std;
template <typename T>
void maxtt(T &t1, T t2) {
  t1 = max(t1, t2);
}
template <typename T>
void mintt(T &t1, T t2) {
  t1 = min(t1, t2);
}
bool debug = 0;
int n, m, k;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
string direc = "URDL";
long long ln, lk, lm;
void etp(bool f = 0) {
  puts(f ? "YES" : "NO");
  exit(0);
}
void addmod(int &x, int y, int mod = 1000000007) {
  assert(y >= 0);
  x += y;
  if (x >= mod) x -= mod;
  assert(x >= 0 && x < mod);
}
void et(int x = -1) {
  printf("%d\n", x);
  exit(0);
}
long long fastPow(long long x, long long y, int mod = 1000000007) {
  long long ans = 1;
  while (y > 0) {
    if (y & 1) ans = (x * ans) % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ans;
}
long long gcd1(long long x, long long y) { return y ? gcd1(y, x % y) : x; }
int d, gen[33], B[30135];
bitset<30135> all;
struct nd {
  long long len, num;
  bitset<30135> pre, suf;
  nd() {
    len = num = 0;
    pre.reset();
    suf.reset();
  }
  friend nd operator+(const nd &a, const nd &b) {
    if (a.len == 0) return b;
    nd res;
    res.len = a.len + b.len;
    res.num = a.num + b.num;
    res.pre = a.pre;
    res.suf = b.suf;
    if (a.len < n - 1) {
      res.pre &= (b.pre >> a.len) | all << (n - 1 - a.len);
    }
    if (b.len < n - 1) {
      res.suf &= (a.suf << b.len) | all >> (n - 1 - b.len);
    }
    if (res.len >= n) {
      bitset<30135> tmp = a.suf & b.pre;
      if (a.len < n - 1) tmp &= all >> (n - 1 - a.len);
      if (b.len < n - 1) tmp &= all << (n - 1 - b.len);
      res.num += tmp.count();
    }
    return res;
  }
} f[70][65];
long long pw[77], l, r;
void init() {
  pw[0] = 1;
  for (int(i) = 1; (i) <= (int)(70); (i)++) pw[i] = pw[i - 1] * d;
  int c = 0;
  while (pw[c + 1] < r) c++;
  for (int(i) = 1; (i) <= (int)(n - 1); (i)++) all[i] = 1;
  for (int(j) = 0; (j) < (int)(m + 1); (j)++) {
    f[0][j].len = 1;
    if (n == 1)
      f[0][j].num = j <= B[1];
    else {
      for (int i = 1; i <= n; i++) {
        f[0][j].pre[i - 1] = j <= B[i];
        f[0][j].suf[i] = j <= B[i];
      }
    }
  }
  for (int(i) = 1; (i) <= (int)(c); (i)++) {
    for (int(j) = 0; (j) < (int)(m + 1); (j)++) {
      for (int(k) = 0; (k) < (int)(d); (k)++) {
        f[i][j] = f[i][j] + f[i - 1][(j + gen[k]) % m];
      }
    }
  }
}
long long cal(long long x) {
  int c = 0;
  while (pw[c + 1] < x) c++;
  nd res;
  int add = 0;
  for (int i = c; i >= 0; i--) {
    for (int(j) = 0; (j) < (int)(d); (j)++) {
      if (x >= pw[i]) {
        x -= pw[i];
        res = res + f[i][(add + gen[j]) % m];
      } else {
        add += gen[j];
        break;
      }
    }
  }
  return res.num;
}
void fmain(int tid) {
  scanf("%d%d", &d, &m);
  for (int(i) = 0; (i) < (int)(d); (i)++) scanf("%d", gen + i);
  scanf("%d", &n);
  for (int(i) = 1; (i) <= (int)(n); (i)++) scanf("%d", B + i);
  scanf("%lld%lld", &l, &r);
  init();
  printf("%lld\n", cal(r) - cal(l + n - 1 - 1));
}
int main() {
  int t = 1;
  for (int(i) = 1; (i) <= (int)(t); (i)++) {
    fmain(i);
  }
  return 0;
}
