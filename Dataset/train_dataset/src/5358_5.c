#include <bits/stdc++.h>
using namespace std;
int tr[(1 << 22) + 10][2], cnt = 1, n, m, x, tmp;
void insert(int x) {
  int p = 0;
  for (int i = 20; i >= 0; i--) {
    int idx = (x & (1 << i)) != 0;
    if (!tr[p][idx]) tr[p][idx] = cnt++;
    p = tr[p][idx];
  }
}
int q(int x) {
  int p = 0;
  int ans = 0;
  for (int i = 20; i >= 0; i--) {
    int idx = (x & (1 << i)) != 0;
    if (tr[p][idx]) {
      if (idx) ans |= (1 << i);
      p = tr[p][idx];
    } else {
      if (!idx) ans |= (1 << i);
      p = tr[p][!idx];
    }
  }
  return ans;
}
int main() {
  set<int> s;
  scanf("%d %d", &n, &m);
  while (n--) scanf("%d", &tmp), s.insert(tmp);
  for (int i = 0; i <= (1 << 19); i++)
    if (!s.count(i)) insert(i);
  for (int i = 0; i < m; i++) {
    scanf("%d", &tmp);
    if (i == 0)
      x = tmp;
    else
      x ^= tmp;
    printf("%d\n", x ^ q(x));
  }
  return 0;
}
