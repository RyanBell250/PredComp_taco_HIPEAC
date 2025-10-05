#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline bool cmax(T &x, T y) {
  return y > x ? x = y, true : false;
}
template <typename T>
inline bool cmin(T &x, T y) {
  return y < x ? x = y, true : false;
}
const int mod = 998244353;
const int MAXN = 3e5 + 5;
const int inv2 = (mod + 1) / 2;
void out_arr(int *a, int le, int ri) {
  for (int i = le; i <= ri; i++) printf("%d ", a[i]);
  puts("");
}
inline int add(int a, int b) {
  a += b;
  return a >= mod ? a - mod : a;
}
inline int pop(int a, int b) {
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul(int a, int b) { return 1LL * a * b % mod; }
int qpow(int a, int b) {
  int c = 1;
  while (b) {
    if (b & 1) c = mul(c, a);
    a = mul(a, a);
    b >>= 1;
  }
  return c;
}
int N, M;
int A[MAXN], B[MAXN], C[MAXN], D[MAXN], tmp[3][MAXN], pos[MAXN], inv[MAXN],
    omega[MAXN];
void Work(int n) {
  for (int i = 0; i <= n - 1; i++) {
    pos[i] = (pos[i >> 1] >> 1);
    if (i & 1) pos[i] |= (n >> 1);
  }
  int x = qpow(3, (mod - 1) / n), y = qpow(x, mod - 2);
  omega[0] = inv[0] = 1;
  for (int i = 1; i <= n - 1; i++) {
    omega[i] = mul(omega[i - 1], x);
    inv[i] = mul(inv[i - 1], y);
  }
}
void FFT(int n, int *a, bool idft) {
  for (int i = 0; i <= n - 1; i++)
    if (pos[i] < i) swap(a[pos[i]], a[i]);
  int *w = idft ? inv : omega;
  for (int len = 2; len <= n; len <<= 1) {
    int m = len >> 1;
    for (int j = 0; j < n; j += len)
      for (int k = 0; k <= m - 1; k++) {
        int z = mul(a[j + m + k], w[n / len * k]);
        a[j + m + k] = pop(a[j + k], z);
        a[j + k] = add(a[j + k], z);
      }
  }
  if (!idft) return;
  int x = qpow(n, mod - 2);
  for (int i = 0; i <= n - 1; i++) a[i] = mul(a[i], x);
}
void Inv(int deg, int *a, int *b) {
  if (!deg) {
    b[0] = qpow(a[0], mod - 2);
    return;
  }
  int m = deg >> 1;
  Inv(m, a, b);
  int n = 1;
  while (n < (deg + deg + 1)) n <<= 1;
  Work(n);
  copy(a, a + deg + 1, tmp[0]);
  FFT(n, tmp[0], 0);
  FFT(n, b, 0);
  for (int i = 0; i <= n - 1; i++)
    b[i] = pop(add(b[i], b[i]), mul(tmp[0][i], mul(b[i], b[i])));
  FFT(n, b, 1);
  fill(tmp[0], tmp[0] + n, 0);
  fill(b + deg + 1, b + n, 0);
}
void Sqrt(int deg, int *a, int *b) {
  if (!deg) {
    b[0] = a[0];
    return;
  }
  int m = deg >> 1;
  Sqrt(m, a, b);
  int n = 1;
  while (n < (deg + deg + 1)) n <<= 1;
  copy(a, a + deg + 1, tmp[1]);
  Inv(deg, b, tmp[2]);
  FFT(n, b, 0);
  FFT(n, tmp[1], 0);
  FFT(n, tmp[2], 0);
  for (int i = 0; i <= n - 1; i++)
    b[i] = mul(add(tmp[1][i], mul(b[i], b[i])), mul(tmp[2][i], inv2));
  FFT(n, b, 1);
  fill(tmp[1], tmp[1] + n, 0);
  fill(tmp[2], tmp[2] + n, 0);
  fill(b + deg + 1, b + n, 0);
}
int main() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) {
    int o;
    scanf("%d", &o);
    if (o <= M) C[o] = 1;
  }
  int n = 1;
  while (n < (M + M + 1)) n <<= 1;
  D[0] = 1;
  for (int i = 1; i <= n - 1; i++) D[i] = pop(0, mul(4, C[i]));
  Sqrt(M, D, B);
  B[0] = add(B[0], 1);
  Inv(M, B, A);
  for (int i = 1; i <= M; i++) printf("%d\n", add(A[i], A[i]));
  return 0;
}
