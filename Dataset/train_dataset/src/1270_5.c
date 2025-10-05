#include <bits/stdc++.h>
using namespace std;
static inline void canhazfast() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}
template <typename T>
T gcd(T a, T b) {
  return b == 0 ? a : gcd(b, a % b);
}
template <typename T>
T extgcd(T a, T b, T &x, T &y) {
  T x0 = 1, y0 = 0, x1 = 0, y1 = 1;
  while (b) {
    T q = a / b;
    a %= b;
    swap(a, b);
    x0 -= q * x1;
    swap(x0, x1);
    y0 -= q * y1;
    swap(y0, y1);
  }
  x = x0;
  y = y0;
  return a;
}
void gen(const char s[], int a[], int b[]) {
  for (int i = 0; s[i]; ++i) {
    if (s[i] == 'A') {
      b[i + 1] = b[i];
      a[i + 1] = a[i] + 1;
    } else {
      b[i + 1] = b[i] + 1;
    }
  }
}
bool check(int sa, int sb, int ta, int tb) {
  if (sb == tb) return sa >= ta && (sa - ta) % 3 == 0;
  if (sb == 0) return sa > ta && tb % 2 == 0;
  if (tb < sb) return false;
  return sa >= ta && (tb - sb) % 2 == 0;
}
int main() {
  canhazfast();
  static char s[100016], t[100016], ans[100016];
  static int sa[100016], sb[100016];
  static int ta[100016], tb[100016];
  int q;
  cin >> s >> t >> q;
  gen(s, sa, sb);
  gen(t, ta, tb);
  for (int i = 0; i < q; ++i) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    ans[i] = '0' + check(min(sa[b], b - a + 1), sb[b] - sb[a - 1],
                         min(ta[d], d - c + 1), tb[d] - tb[c - 1]);
  }
  cout << ans << '\n';
  return 0;
}
