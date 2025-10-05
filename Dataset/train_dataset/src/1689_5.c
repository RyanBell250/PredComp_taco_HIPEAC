#include <bits/stdc++.h>
using namespace std;
long long read() {
  long long x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch)) f = ch == '-', ch = getchar();
  while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}
const int N = 1e5 + 5, mod = 1e9 + 7;
int Pow(int x, int y) {
  int ans = 1;
  for (; y; y >>= 1, x = (long long)x * x % mod)
    if (y & 1) ans = (long long)ans * x % mod;
  return ans;
}
void Add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}
void Del(int &x, int y) {
  if ((x -= y) < 0) x += mod;
}
int Add(int x) { return x >= mod ? x - mod : x; }
int Del(int x) { return x < 0 ? x + mod : x; }
int n, m;
vector<pair<int, int> > e[N];
vector<pair<int, int> > v;
int a, b;
int Ins(int a, int b) {
  if (a == -1) return -1;
  for (int i = (4); i >= (0); i--) {
    if (b >> i & 1) {
      if (!(a >> (i * 5) & 31)) {
        for (int j = (0); j <= (i - 1); j++)
          if (b >> j & 1) b ^= a >> (j * 5) & 31;
        a ^= b << (i * 5);
        for (int j = (i + 1); j <= (4); j++)
          if (a >> (j * 5) >> i & 1) a ^= b << (j * 5);
        return a;
      } else {
        b ^= a >> (i * 5) & 31;
      }
    }
  }
  return -1;
}
int vis[N];
int ww[N];
void out(int b) {
  for (int i = (0); i <= (4); i++) printf("%d ", b >> (i * 5) & 31);
  puts("");
}
unordered_map<int, int> id;
int st[400], cnt = 0;
int trans[400][35];
void search(int d, int v) {
  if (d < 0) {
    st[++cnt] = v;
    return;
  }
  search(d - 1, v);
  for (int i = (d + 1); i <= (4); i++)
    if (v >> (i * 5) >> d & 1) return;
  for (int i = ((1 << d)); i <= ((1 << (d + 1)) - 1); i++)
    search(d - 1, v | i << (d * 5));
}
void getst() {
  search(4, 0);
  id[-1] = -1;
  for (int i = (1); i <= (cnt); i++) id[st[i]] = i;
  for (int i = (1); i <= (cnt); i++) {
    for (int j = (0); j <= (31); j++) trans[i][j] = id[Ins(st[i], j)];
  }
}
int dep[N];
void dfs(int x, int pre, int w, int d = 1) {
  dep[x] = d;
  vis[x] = 1;
  ww[x] = w;
  for (auto E : e[x]) {
    int y = E.first, v = E.second;
    if (y == pre) continue;
    if (!vis[y])
      dfs(y, x, w ^ v, d + 1);
    else if (y == 1 && pre != 1)
      a = w ^ v;
    else if (dep[y] < dep[x]) {
      if (b != -1) b = trans[b][w ^ v ^ ww[y]];
    }
  }
}
int f[400], g[400];
int main() {
  getst();
  n = read(), m = read();
  for (int i = (1); i <= (m); i++) {
    int x = read(), y = read(), w = read();
    e[x].push_back(make_pair(y, w));
    e[y].push_back(make_pair(x, w));
  }
  vis[1] = 1;
  memset(f, 0, sizeof(f));
  f[id[0]] = 1;
  for (auto E : e[1]) {
    int i = E.first;
    if (vis[i]) continue;
    a = -1, b = id[0];
    dfs(i, 1, E.second);
    if (b != -1) {
      memset(g, 0, sizeof(g));
      int bb = a > 0 && trans[b][a] != -1 ? trans[b][a] : -1;
      for (int s = (1); s <= (cnt); s++) {
        if (!f[s]) continue;
        Add(g[s], f[s]);
        int v = s, t;
        for (int i = (0); i <= (4); i++) {
          t = st[b] >> (i * 5) & 31;
          if (!t) continue;
          if ((v = trans[v][t]) == -1) break;
        }
        if (v != -1) Add(g[v], a != -1 ? Add(f[s] << 1) : f[s]);
        if (bb != -1) {
          int v = s, t;
          for (int i = (0); i <= (4); i++) {
            t = st[bb] >> (i * 5) & 31;
            if (!t) continue;
            if ((v = trans[v][t]) == -1) break;
          }
          if (v != -1) Add(g[v], f[s]);
        }
      }
      swap(f, g);
    }
  }
  int ans = 0;
  for (int i = (1); i <= (cnt); i++) Add(ans, f[i]);
  cout << ans << endl;
  return 0;
}
