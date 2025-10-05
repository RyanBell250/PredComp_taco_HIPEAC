#include <bits/stdc++.h>
using namespace std;
struct st {
  int v;
  bool mark;
} a[555];
bool cmp(st a, st b) { return a.v < b.v; }
int n;
void idar(int x, int p, int s, int d) {
  if (x == n) {
    int i, rm = 0;
    for (i = 0; i < n; i++)
      if (a[i].mark == true) rm++;
    if (rm == n - 1) {
      printf("YES\n");
      exit(0);
    }
  }
  if (s == a[x].v - 1 && (d >= 2 || d == 0)) {
    idar(x + 1, 0, 0, 0);
  } else {
    if (p == n) return;
    if (a[p].v + s >= a[x].v) return;
    if (!a[p].mark) {
      a[p].mark = true;
      idar(x, p + 1, s + a[p].v, d + 1);
      a[p].mark = false;
    }
    idar(x, p + 1, s, d);
  }
}
int main() {
  int i;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i].v);
    a[i].mark = false;
  }
  sort(a, a + n, cmp);
  idar(0, 0, 0, 0);
  printf("NO\n");
  return 0;
}
