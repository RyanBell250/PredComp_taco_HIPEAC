#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 50;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
const long double pi = acos(-1.0L);
inline long long read() {
  long long x = 0, t = 1;
  char ch;
  while (!isdigit(ch = getchar()))
    if (ch == '-') t = -1;
  while (isdigit(ch)) {
    x = 10 * x + ch - '0';
    ch = getchar();
  }
  return x * t;
}
long long fast_pow(long long x, int k, int p) {
  long long ret = 1;
  while (k > 0) {
    if (k & 1) ret = (ret * x) % p;
    k >>= 1;
    x = (x * x) % p;
  }
  return ret % p;
}
int book[N];
vector<int> pic[N], rev[N], path;
int dis[N];
queue<int> q;
void dfs(int u, int s, int t, int mx, int mn) {
  if (s == t) {
    printf("%d %d\n", mn, mx);
    return;
  }
  int m = -1;
  int w = path[u];
  for (int i = 0; i <= pic[s].size() - 1; i++) {
    int v = pic[s][i];
    if (v != w && (m == -1 || dis[v] < dis[m])) m = v;
  }
  if (m == -1) {
    book[w] = 1;
    dfs(u + 1, w, t, mx, mn);
    return;
  } else if (book[m]) {
    if (dis[m] < dis[w]) {
      book[w] = 1;
      dfs(u + 1, w, t, mx + 1, mn + 1);
      return;
    } else if (dis[m] == dis[w]) {
      book[w] = 1;
      dfs(u + 1, w, t, mx + 1, mn);
      return;
    } else {
      book[w] = 1;
      dfs(u + 1, w, t, mx, mn);
      return;
    }
  }
  if (dis[m] == dis[w]) {
    book[w] = 1;
    dfs(u + 1, w, t, mx + 1, mn);
  } else if (dis[m] > dis[w]) {
    book[w] = 1;
    dfs(u + 1, w, t, mx, mn);
  } else {
    book[w] = 1;
    dfs(u + 1, w, t, mx + 1, mn + 1);
  }
}
int mp[50][50];
int main() {
  int T = 1;
  while (T--) {
    int n;
    n = read();
    int m = read();
    for (int i = 1; i <= m; i++) {
      int x = read();
      int y = read();
      pic[x].push_back(y);
      rev[y].push_back(x);
      dis[x] = dis[y] = inf;
    }
    int k = read();
    for (int i = 1; i <= k; i++) {
      path.push_back(read());
    }
    int tot = path.size() - 1;
    int s = path[0];
    int t = path[tot];
    dis[t] = 0;
    q.push(t);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i <= rev[u].size() - 1; i++) {
        int v = rev[u][i];
        if (dis[v] == inf) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      ;
    }
    book[s] = 1;
    dfs(1, s, t, 0, 0);
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= pic[i].size() - 1; j++) {
        ;
      }
    }
  }
  return 0;
}
