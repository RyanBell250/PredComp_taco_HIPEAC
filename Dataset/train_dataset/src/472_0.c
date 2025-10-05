#include <bits/stdc++.h>
using namespace std;
const int maxn = 123;
int a[maxn], b[maxn];
int vis[maxn];
int n;
struct P {
  int a[101];
  bool operator<(const P &t) const {
    for (int i = 0; i < n; i++) {
      if (a[i] != t.a[i]) return a[i] < t.a[i];
    }
    return false;
  }
};
P t;
map<P, int> m;
int main() {
  cin >> n;
  int tmp = (1 << 15) - 1;
  for (int i = 0; i < n; i++)
    scanf("%d", a + i), b[i] = a[i] >> 15, a[i] = a[i] & tmp;
  for (int i = 0; i <= tmp; i++) {
    int mx = 34;
    for (int j = 0; j < n; j++) {
      t.a[j] = __builtin_popcount(a[j] ^ i);
      mx = min(mx, t.a[j]);
    }
    for (int j = 0; j < n; j++) t.a[j] -= mx;
    m[t] = i;
  }
  for (int i = 0; i <= tmp; i++) {
    int mx = 0;
    for (int j = 0; j < n; j++) {
      t.a[j] = __builtin_popcount(b[j] ^ i);
      mx = max(mx, t.a[j]);
    }
    for (int j = 0; j < n; j++) t.a[j] = mx - t.a[j];
    if (m.count(t) != 0) return 0 * printf("%d", m[t] + (i << 15));
  }
  printf("-1");
}
