#include <bits/stdc++.h>
using namespace std;
int a[200005];
int main() {
  int n, m, x, f;
  set<int> v;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &x);
    a[x]++;
  }
  for (int i = 0; i <= n; i++) {
    if (a[i]) v.insert(i);
  }
  for (int i = 1; i < n; i++) {
    x = n, f = n;
    if (!a[i]) v.insert(i);
    a[i]++;
    while (x) {
      set<int>::iterator p = v.upper_bound(f);
      if (p == v.begin()) break;
      p--;
      int y = (*p);
      x -= min(x / y, a[y]) * y;
      f = min(y - 1, x);
    }
    if (x) {
      printf("%d\n", i);
      return 0;
    }
    if (!(--a[i])) v.erase(i);
  }
  printf("Greed is good\n");
}
