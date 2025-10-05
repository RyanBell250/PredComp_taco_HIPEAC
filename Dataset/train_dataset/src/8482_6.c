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
string direc = "URDL";
const long long MOD2 = (long long)998244353 * (long long)998244353;
long long ln, lk, lm;
void etp(bool f = 0) {
  puts(f ? "YES" : "NO");
  exit(0);
}
void addmod(int &x, int y, int mod = 998244353) {
  x += y;
  if (x >= mod) x -= mod;
  if (x < 0) x += mod;
  assert(x >= 0 && x < mod);
}
void et(int x = -1) {
  printf("%d\n", x);
  exit(0);
}
long long fastPow(long long x, long long y, int mod = 998244353) {
  long long ans = 1;
  while (y > 0) {
    if (y & 1) ans = (x * ans) % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ans;
}
long long gcd1(long long x, long long y) { return y ? gcd1(y, x % y) : x; }
int fac[600135], inv[600135];
void initfac(int n) {
  fac[0] = inv[0] = 1;
  for (int(i) = 1; (i) <= (int)(n); (i)++) {
    fac[i] = (long long)fac[i - 1] * i % 998244353;
    inv[i] = fastPow(fac[i], 998244353 - 2);
  }
}
int C(int n, int m) {
  if (n < m) return 0;
  return (long long)fac[n] * inv[m] % 998244353 * inv[n - m] % 998244353;
}
const int P = 998244353, G = 3, Gi = 332748118;
int r[600135], L, limit = 1, Inv;
int k1[600135], k2[600135];
void init(int n, int m) {
  limit = 1;
  L = 0;
  while (limit <= n + m) {
    limit <<= 1;
    L++;
  }
  Inv = fastPow(limit, P - 2, P);
  for (int(i) = 0; (i) < (int)(limit); (i)++)
    r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
}
void NTT(int *A, int type) {
  for (int i = 0; i < limit; i++)
    if (i < r[i]) swap(A[i], A[r[i]]);
  for (int mid = 1; mid < limit; mid <<= 1) {
    long long Wn = fastPow(type == 1 ? G : Gi, (P - 1) / (mid << 1), P);
    for (int j = 0; j < limit; j += (mid << 1)) {
      long long w = 1;
      for (int k = 0; k < mid; k++, w = (w * Wn) % P) {
        int x = A[j + k], y = w * A[j + k + mid] % P;
        A[j + k] = (x + y) % P;
        A[j + k + mid] = (x - y + P) % P;
      }
    }
  }
}
vector<int> mul(const vector<int> &a, const vector<int> &b) {
  int n1 = a.size() - 1, n2 = b.size() - 1;
  init(n1, n2);
  for (int(i) = 0; (i) < (int)(limit); (i)++) k1[i] = k2[i] = 0;
  for (int i = 0; i <= n1; i++) k1[i] = a[i];
  for (int i = 0; i <= n2; i++) k2[i] = b[i];
  NTT(k1, 1);
  NTT(k2, 1);
  for (int(i) = 0; (i) < (int)(limit); (i)++)
    k1[i] = (long long)k1[i] * k2[i] % P;
  NTT(k1, -1);
  vector<int> ret(n1 + n2 + 1);
  for (int i = 0; i <= n1 + n2; i++) ret[i] = (long long)k1[i] * Inv % P;
  return ret;
}
int a[600135], c[600135], b[10], q[600135], Ans[600135];
int Q;
void cal(int bb) {
  memset(c, 0, sizeof c);
  int N = 0, M = 0;
  for (int(i) = 1; (i) <= (int)(n); (i)++)
    if (a[i] < bb) {
      c[a[i]]++;
      if (c[a[i]] == 1)
        N++;
      else if (c[a[i]] == 2) {
        N--;
        M++;
      }
    }
  vector<int> A(N + 1, 0);
  int p2 = 1;
  for (int(i) = 0; (i) < (int)(N + 1); (i)++) {
    A[i] = (long long)C(N, i) * p2 % 998244353;
    addmod(p2, p2);
  }
  vector<int> B(M + M + 1, 0);
  for (int(i) = 0; (i) < (int)(M + M + 1); (i)++) {
    B[i] = C(M + M, i);
  }
  vector<int> ret = mul(A, B);
  for (int(i) = 1; (i) <= (int)(Q); (i)++) {
    int tar = q[i] / 2 - bb - 1;
    if (tar >= 0 && tar < ret.size()) addmod(Ans[i], ret[tar]);
  }
}
void fmain(int tid) {
  scanf("%d%d", &n, &k);
  for (int(i) = 1; (i) <= (int)(n); (i)++) scanf("%d", a + i);
  for (int(i) = 1; (i) <= (int)(k); (i)++) scanf("%d", b + i);
  scanf("%d", &Q);
  for (int(i) = 1; (i) <= (int)(Q); (i)++) scanf("%d", q + i);
  initfac(600135 - 1);
  for (int(i) = 1; (i) <= (int)(k); (i)++) {
    cal(b[i]);
  }
  for (int(i) = 1; (i) <= (int)(Q); (i)++) printf("%d ", Ans[i]);
}
int main() {
  int t = 1;
  for (int(i) = 1; (i) <= (int)(t); (i)++) {
    fmain(i);
  }
  return 0;
}
