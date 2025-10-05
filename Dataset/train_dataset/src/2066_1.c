#include <bits/stdc++.h>
using namespace std;
const int MaxN = 100500;
vector<vector<int> > g, g1;
vector<int> st;
int sost[MaxN], mark[MaxN], ans[MaxN], mark1[MaxN];
void dfs(int v) {
  int i;
  mark[v] = 1;
  for (i = 0; i < g[v].size(); i++) {
    if ((mark[g[v][i]] == 0)) {
      dfs(g[v][i]);
    }
  }
}
void dfs1(int v) {
  int i;
  mark1[v] = 1;
  if (sost[v] == 1) return;
  for (i = 0; i < g1[v].size(); i++) {
    if ((mark1[g1[v][i]] == 0)) {
      dfs1(g1[v][i]);
    }
  }
}
int main() {
  int i, j, n, m, x, y;
  g.resize(MaxN);
  g1.resize(MaxN);
  for (i = 0; i < MaxN; i++) {
    sost[i] = 0;
    mark[i] = 0;
    mark1[i] = 0;
    ans[i] = 0;
  }
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    scanf("%d", &sost[i]);
  }
  for (i = 0; i < m; i++) {
    scanf("%d %d", &x, &y);
    x--;
    y--;
    g[x].push_back(y);
    g1[y].push_back(x);
  }
  for (i = 0; i < n; i++) {
    if ((mark[i] == 0) && (sost[i] == 1)) {
      dfs(i);
    }
    if ((mark1[i] == 0) && (sost[i] == 2)) {
      dfs1(i);
    }
  }
  for (i = 0; i < n; i++) {
    if ((mark[i] == 1) && (mark1[i] == 1)) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
  cin.get();
  cin.get();
}
