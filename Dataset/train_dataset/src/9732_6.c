#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
const int M = (1 << 20) + 5, mod = 1e9 + 7;
int dep[M];
vector<int> edge[M];
void dfs(int x, int y) {
  for (int to : edge[x]) {
    if (to == y) continue;
    dep[to] = dep[x] + 1;
    dfs(to, x);
  }
}
int main() {
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  for (int j = 1; j < n; j++) {
    int a, b;
    scanf("%d%d", &a, &b);
    edge[a].push_back(b);
    edge[b].push_back(a);
  }
  dfs(1, 0);
  sort(dep + 1, dep + 1 + n);
  int r = 2;
  int ans = 0, cost = 0;
  for (int j = 2; j <= n; j++) {
    while (r <= n && cost + ((dep[r] != dep[r - 1]) ? r - j : 0) <= p) {
      ans = max(ans, r - j + 1);
      if (dep[r] != dep[r - 1]) cost += r - j;
      r++;
    }
    cost -= dep[r - 1] - dep[j];
  }
  printf("%d\n", min(ans, m));
  return 0;
}
