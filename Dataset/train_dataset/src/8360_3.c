#include <bits/stdc++.h>
using namespace std;
const int maxN = 100000 + 5, inf = 2005120699;
const long long INF = 9200512069999999999ll;
int reads() {
  int ans = 0;
  bool fu = 0;
  char ch = getchar();
  while ((ch > '9' || ch < '0') && ch != '-') ch = getchar();
  if (ch == '-') fu = 1, ch = getchar();
  while (ch <= '9' && ch >= '0')
    ans = (ans << 3) + (ans << 1) + (ch ^ 48), ch = getchar();
  if (fu) ans *= -1;
  return ans;
}
long long a[maxN];
inline long long abss(long long x) { return x < 0 ? -x : x; }
int main() {
  int n, c;
  long long ans = INF, tem, o;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
  }
  sort(a + 1, a + 1 + n);
  c = (int)pow((((1ll << 62) - 1) << 1) + 1, 1.0 / n);
  for (long long i = 0ll; i <= c; ++i) {
    tem = 0;
    o = 1ll;
    for (int j = 1; j <= n; ++j) {
      tem += abss(a[j] - o);
      o *= i;
      if (o > (1ll << 50)) {
        tem = INF;
        break;
      }
    }
    ans = min(ans, tem);
  }
  printf("%lld", ans);
}
