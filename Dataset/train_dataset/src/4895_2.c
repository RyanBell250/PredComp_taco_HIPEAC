#include <bits/stdc++.h>
using namespace std;
vector<int> v[10];
int n, ans, m, tmp;
vector<int> v2;
void recur(int now) {
  if (now == n) {
    int vis[7][7];
    memset(vis, 0, sizeof(vis));
    int ans2 = 0;
    for (int e = 1; e <= n; e++) {
      for (int p = 0; p < v[e].size(); p++) {
        int next = v[e][p];
        int f = v2[e - 1], s = v2[next - 1];
        if (f > s) swap(f, s);
        if (vis[f][s] == 0) {
          vis[f][s] = 1;
          ans2++;
        }
      }
    }
    ans = max(ans, ans2);
  } else {
    for (int p = 1; p <= min(n, 6); p++) {
      v2.push_back(p);
      recur(now + 1);
      v2.pop_back();
    }
  }
}
int main(void) {
  scanf("%d%d", &n, &m);
  for (int e = 0; e < m; e++) {
    int a, b;
    scanf("%d%d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
  }
  recur(0);
  printf("%d", ans);
  return 0;
}
