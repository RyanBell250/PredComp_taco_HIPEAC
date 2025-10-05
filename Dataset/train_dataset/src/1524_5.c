#include <bits/stdc++.h>
using namespace std;
bool flag[20000 + 4];
int G[222][222], S, T, node, par[222], mat[222][222];
bool chk[222];
queue<int> Q;
int bfs() {
  while (!Q.empty()) Q.pop();
  memset(chk, false, sizeof chk);
  Q.push(S);
  par[S] = -1;
  chk[S] = true;
  while (!Q.empty()) {
    int top = Q.front();
    Q.pop();
    int j = 0;
    for (int i = 0; i <= node; i++) {
      if (G[top][i] > 0 && !chk[i]) {
        Q.push(i);
        par[i] = top;
        chk[i] = true;
        if (i == T) {
          j = 1;
          break;
        }
      }
    }
    if (j == 1) break;
  }
  int now = T, cap = 1000000;
  while (par[now] > -1) {
    int parent = par[now];
    cap = min(cap, G[parent][now]);
    now = parent;
  }
  now = T;
  while (par[now] > -1) {
    int parent = par[now];
    G[parent][now] -= cap;
    G[now][parent] += cap;
    now = parent;
  }
  if (cap == 1000000) return 0;
  return cap;
}
int maxflow() {
  int res = 0;
  while (true) {
    int cap = bfs();
    if (cap == 0) break;
    res += cap;
  }
  return res;
}
vector<int> tmp, V[222];
vector<vector<int> > ans;
bool vis[222];
void dfs(int x) {
  tmp.push_back(x);
  vis[x] = true;
  for (int i = 0; i < V[x].size(); i++)
    if (!vis[V[x][i]]) dfs(V[x][i]);
}
void sieve() {
  flag[1] = true;
  for (int i = 4; i <= 20000; i += 2) flag[i] = true;
  for (int i = 3; i <= 20000; i += 2) {
    if (!flag[i]) {
      for (int j = i + i; j <= 20000; j += i) flag[j] = true;
    }
  }
}
int ar[222];
int main() {
  sieve();
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> ar[i];
    if (ar[i] & 1)
      G[0][i] = 2;
    else
      G[i][n + 1] = 2;
  }
  S = 0, T = n + 1;
  node = n + 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (!flag[ar[i] + ar[j]]) {
        if (ar[i] & 1)
          G[i][j] = mat[i][j] = 1;
        else
          G[j][i] = mat[j][i] = 1;
      }
    }
  }
  int get = maxflow();
  if (get != n) {
    cout << "Impossible" << endl;
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (mat[i][j] != G[i][j]) {
        V[i].push_back(j);
        V[j].push_back(i);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      tmp.clear();
      dfs(i);
      ans.push_back(tmp);
    }
  }
  int sz = ans.size();
  cout << sz << endl;
  for (int i = 0; i < sz; i++) {
    cout << ans[i].size();
    for (int j = 0; j < ans[i].size(); j++) cout << " " << ans[i][j];
    cout << endl;
  }
  return 0;
}
