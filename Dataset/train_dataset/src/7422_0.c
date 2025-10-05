#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > ad(200005);
int vis[200005], lev[200005];
void bfs(int s) {
  int i, a, x;
  queue<int> pq;
  pq.push(s);
  vis[s] = 1;
  while (!pq.empty()) {
    s = pq.front();
    pq.pop();
    x = ad[s].size();
    for (i = 0; i < x; i++) {
      a = ad[s][i];
      if (!vis[a]) vis[a] = 1, lev[a] = lev[s] + 1, pq.push(a);
    }
  }
  return;
}
int main() {
  int i, n, m, a, b;
  scanf("%d", &n);
  for (i = 0; i < n; i++) scanf("%d", &a), ad[i].push_back(a - 1);
  for (i = 0; i < n - 1; i++) ad[i].push_back(i + 1);
  for (i = 1; i < n; i++) ad[i].push_back(i - 1);
  bfs(0);
  for (i = 0; i < n; i++) printf("%d ", lev[i]);
  printf("\n");
}
