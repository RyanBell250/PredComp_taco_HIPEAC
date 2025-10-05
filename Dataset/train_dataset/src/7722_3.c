#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > adj;
int col[100005];
bool posi = true;
void bfs(int s) {
  queue<int> q;
  col[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int c = col[u];
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (col[v] == -1) {
        col[v] = c ^ 1;
        q.push(v);
      } else {
        if (col[v] == c) {
          posi = false;
        }
      }
    }
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  adj.resize(n + 5);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) col[i] = -1;
  for (int i = 1; i <= n; i++)
    if (col[i] == -1) bfs(i);
  if (!posi) {
    cout << -1 << endl;
    return 0;
  }
  int c0 = 0, c1 = 0;
  for (int i = 1; i <= n; i++) {
    if (col[i] == 0)
      c0++;
    else
      c1++;
  }
  printf("%d\n", c0);
  for (int i = 1; i <= n; i++)
    if (col[i] == 0) printf("%d ", i);
  printf("\n");
  printf("%d\n", c1);
  for (int i = 1; i <= n; i++)
    if (col[i] == 1) printf("%d ", i);
  printf("\n");
  return 0;
}
