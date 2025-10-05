#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int inf = -INF;
const int mod = 1e9 + 7;
const double pi = acos(-1.0);
int a[N];
int b[N];
int main() {
  int n, x;
  scanf("%d%d", &n, &x);
  fill(a, a + 100005, 0);
  fill(b, b + 100005, 0);
  for (int i = 0; i < n; ++i) {
    int p, q;
    scanf("%d", &p);
    q = p & x;
    if (p == q)
      a[p]++;
    else {
      a[p]++;
      b[q]++;
    }
  }
  for (int i = 0; i < 100005; ++i)
    if (a[i] >= 2) {
      cout << 0 << endl;
      return 0;
    }
  for (int i = 0; i < 100005; ++i)
    if (a[i] == 1 && b[i] >= 1) {
      cout << 1 << endl;
      return 0;
    }
  for (int i = 0; i < 100005; ++i)
    if (b[i] >= 2) {
      cout << 2 << endl;
      ;
      return 0;
    }
  cout << -1 << endl;
  return 0;
}
