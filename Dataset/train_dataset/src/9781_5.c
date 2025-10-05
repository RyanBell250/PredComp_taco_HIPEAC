#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const long long INFF = 0x3f3f3f3f3f3f3f3fll;
const long long M = 1e9 + 7;
const long long maxn = 3e6 + 7;
const double eps = 0.00000001;
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
template <typename T>
inline T abs(T a) {
  return a > 0 ? a : -a;
}
template <typename T>
inline T powMM(T a, T b) {
  T ret = 1;
  for (; b; b >>= 1ll, a = a * a % M) ret = 1ll * ret * a % M;
  return ret;
}
int n, m, len;
int i, j, t;
char a[maxn], ans[maxn];
int b[maxn];
int fa[maxn];
int mx;
inline int getfa(int x) {
  if (fa[x] == x) return x;
  return fa[x] = getfa(fa[x]);
}
int main() {
  scanf("%d", &n);
  for (i = 1; i <= 3e6; i++) fa[i] = i;
  while (n--) {
    scanf("%s", a);
    len = strlen(a);
    scanf("%d", &m);
    while (m--) {
      scanf("%d", &t);
      for (j = getfa(t); j < t + len; j = fa[j] = getfa(j + 1)) {
        ans[j] = a[j - t];
        if (j > mx) mx = j;
      }
    }
  }
  for (i = 1; i <= mx; i++) {
    if (ans[i])
      putchar(ans[i]);
    else
      putchar('a');
  }
}
