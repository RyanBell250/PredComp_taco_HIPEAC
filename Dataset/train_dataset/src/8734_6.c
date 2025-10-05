#include <bits/stdc++.h>
using namespace std;
int read() {
  int f = 1;
  int res = 0;
  char ch;
  do {
    ch = getchar();
    if (ch == '-') f = -f;
  } while (ch < '0' || ch > '9');
  do {
    res = res * 10 + ch - '0';
    ch = getchar();
  } while (ch >= '0' && ch <= '9');
  return f == 1 ? res : -res;
}
const int MAXN = 100010;
const int MAXP = MAXN * 51;
const long long INF = 2000000000000LL;
int n, m, D;
int mod = 1000000007;
int X[MAXN], Y[MAXN];
char open[MAXN][52];
int stck[MAXP], in[MAXP], dfsn[MAXP], low[MAXP], idx, top;
int li[MAXN], bak;
bool hv[MAXN];
int head[MAXP], nxt[MAXP], to[MAXP], tot;
int nid[MAXP], dag[MAXP], sz[MAXP];
std::queue<int> q;
int dp[MAXP];
void addEdge(int x, int y) {
  tot++;
  nxt[tot] = head[x];
  head[x] = tot;
  to[tot] = y;
}
int getIndex(int x, int d) { return x + (d % D) * n; }
void append(int x) {
  --x;
  int c = x % n + 1;
  int d = x / n;
  if (c <= 0 || d >= D) cout << "x: " << x << endl;
  if (!hv[c] && (c > 0 && d < D && open[c][d] == '1')) {
    li[++bak] = c;
    hv[c] = true;
  }
}
void clr() {
  for (int i = 1; i <= bak; i++) hv[li[i]] = false;
  bak = 0;
}
void tarjan(int u) {
  dfsn[u] = low[u] = ++idx;
  in[stck[++top] = u] = true;
  for (int i = head[u]; i; i = nxt[i])
    if (!dfsn[to[i]]) {
      tarjan(to[i]);
      low[u] = std::min(low[u], low[to[i]]);
    } else if (in[to[i]])
      low[u] = std::min(low[u], dfsn[to[i]]);
  if (low[u] == dfsn[u]) {
    int v;
    do in[v = stck[top--]] = false, append(v), nid[v] = u;
    while (u != v);
    sz[u] = bak;
    clr();
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &D);
  for (int i = 0; i < m; i++) {
    int u = read();
    int v = read();
    X[i] = u;
    Y[i] = v;
    for (int j = 0; j < D; j++)
      addEdge(getIndex(X[i], j), getIndex(Y[i], j + 1));
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", open[i]);
  }
  tarjan(getIndex(1, 0));
  memset(head, 0, sizeof(head));
  tot = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < D; j++) {
      int u = getIndex(X[i], j);
      int v = getIndex(Y[i], j + 1);
      if (!nid[u] || !nid[v]) continue;
      if (nid[u] == nid[v]) continue;
      addEdge(nid[u], nid[v]);
      dag[nid[v]]++;
    }
  }
  q.push(getIndex(1, 0));
  int ans = 0;
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    ans = std::max(ans, dp[t] += sz[t]);
    for (int i = head[t]; i; i = nxt[i]) {
      dp[to[i]] = std::max(dp[to[i]], dp[t]);
      if (!--dag[to[i]]) q.push(to[i]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
