#include <bits/stdc++.h>
const long double Pi = acosl(-1.0);
using namespace std;
int n, m, q, lim, len, a[100010], b[100010], N = 0, M = 0;
int A[100010], B[100010], C[100010], D[100010], E[100010], F[100010],
    rev[300010];
long long U[200010], V[200010];
struct Com {
  long double x, y;
  Com(long double _x = 0, long double _y = 0) { x = _x, y = _y; }
  Com operator+(const Com &b) const { return Com(x + b.x, y + b.y); }
  Com operator-(const Com &b) const { return Com(x - b.x, y - b.y); }
  Com operator*(const Com &b) const {
    return Com(x * b.x - y * b.y, x * b.y + y * b.x);
  }
} G[300000], H[300000], L[300000];
void init(int N) {
  lim = 1, len = 0;
  while (lim <= N) lim <<= 1, len++;
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (len - 1));
}
void FFT(Com *f, int ty) {
  for (int i = 0; i < lim; i++)
    if (i < rev[i]) swap(f[rev[i]], f[i]);
  for (int mid = 1; mid < lim; mid <<= 1) {
    Com Wn(cos(Pi / mid), ty * sin(Pi / mid));
    for (int R = mid << 1, j = 0; j < lim; j += R) {
      Com w(1, 0);
      for (int k = 0; k < mid; k++, w = w * Wn) {
        Com x = f[j + k], y = w * f[j + k + mid];
        f[j + k] = x + y;
        f[j + mid + k] = x - y;
      }
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]), N = max(N, a[i]), A[a[i]]++;
  for (int i = 1; i <= m; i++) scanf("%d", &b[i]), M = max(M, b[i]), B[b[i]]++;
  for (int i = 1; i < n; i++)
    C[max(a[i], a[i + 1])]++, D[min(a[i], a[i + 1])]++;
  for (int i = 1; i < m; i++)
    E[max(b[i], b[i + 1])]++, F[min(b[i], b[i + 1])]++;
  for (int i = 1; i <= N; i++) G[i] = Com(A[i] - C[i], A[i] - D[i]);
  for (int i = 1; i <= M; i++) H[i] = Com(B[i] - E[i], B[i] - F[i]);
  init(N + M);
  FFT(G, 1), FFT(H, 1);
  for (int i = 0; i < lim; i++) {
    int j = (lim - i) & (lim - 1);
    if (i > j) continue;
    Com J, K;
    J = Com(0.25) * Com(G[i].x + G[j].x, G[i].y - G[j].y) *
        Com(H[i].x + H[j].x, H[i].y - H[j].y);
    K = Com(0.25) * Com(G[i].y + G[j].y, G[j].x - G[i].x) *
        Com(H[i].y + H[j].y, H[j].x - H[i].x);
    L[i] = Com(J.x - K.y, K.x + J.y);
    if (i ^ j) L[j] = Com(J.x + K.y, K.x - J.y);
  }
  FFT(L, -1);
  for (int i = 2; i <= N + M; i++)
    U[i] = roundl(L[i].x / lim), V[i] = roundl(L[i].y / lim);
  lim = N + M + 1;
  for (int i = 1; i <= lim; i++) U[i] += U[i - 1];
  for (int i = lim - 1; i >= 0; i--) V[i] += V[i + 1];
  int x;
  while (q--) {
    scanf("%d", &x), x = min(x, lim);
    printf("%lld\n", V[x] - U[x - 1]);
  }
}
