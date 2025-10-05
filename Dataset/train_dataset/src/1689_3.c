#include <bits/stdc++.h>
using namespace std;
const int N = 300030;
const int M = 2 * N;
const long long MOD = 1000000007LL;
inline int lowbit(int x) { return x & (-x); }
inline long long addmod(long long x, long long y) {
  x += y;
  if (x >= MOD) x -= MOD;
  return x;
}
struct graph {
  int head[N], next[M], to[M], w[M];
  int tot;
  inline void init(int n) {
    for (int i = 0; i <= n; ++i) head[i] = -1;
    tot = 0;
  }
  inline void addedge(int x, int y, int z) {
    to[tot] = y;
    next[tot] = head[x];
    w[tot] = z;
    head[x] = tot;
    ++tot;
  }
} G;
map<long long, int> mp;
int co[400][400], co1[400][40], sz;
long long pm[400];
void get_state(long long state) {
  if (mp.find(state) != mp.end()) return;
  pm[sz] = state;
  mp[state] = sz++;
  for (int i = 0; i < 32; ++i) {
    if (!((1LL << i) & state)) {
      long long nstate = state;
      for (int j = 0; j < 32; ++j) {
        if ((1LL << j) & state) nstate |= (1LL << (i ^ j));
      }
      get_state(nstate);
      co1[mp[state]][i] = mp[nstate];
    }
  }
}
void init() {
  sz = 1;
  get_state(1);
  for (int i = 1; i < sz; ++i)
    for (int j = i; j < sz; ++j) {
      if (((pm[i] & pm[j]) | 1LL) ^ 1LL) {
      } else {
        int id = i;
        for (int k = 1; k < 32; ++k)
          if ((pm[j] & (1LL << k)) && !(pm[id] & (1LL << k))) id = co1[id][k];
        co[i][j] = co[j][i] = id;
      }
    }
}
int n, m;
int vis[N], w[N], mm[N], dep[N], val[N];
int st[N][3];
long long f[2][400];
vector<int> vec[N];
void dfs(int x, int p, int &state) {
  for (int i = G.head[x]; i != -1; i = G.next[i]) {
    int y = G.to[i];
    if (y == p) continue;
    if (!dep[y]) {
      if (!mm[y]) {
        mm[y] = mm[x];
        vec[mm[y]].push_back(y);
      }
      dep[y] = dep[x] + 1;
      val[y] = val[x] ^ G.w[i];
      dfs(y, x, state);
    } else if (dep[y] <= dep[x] && y != 1) {
      int temp = val[x] ^ val[y] ^ G.w[i];
      state = co1[state][temp];
    }
  }
}
int main() {
  int cases = 1;
  for (int iii = 1; iii <= cases; ++iii) {
    init();
    scanf("%d%d", &n, &m);
    G.init(n);
    for (int i = 0; i < m; ++i) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      G.addedge(x, y, z);
      G.addedge(y, x, z);
    }
    m = 0;
    for (int i = G.head[1]; i != -1; i = G.next[i]) {
      int y = G.to[i];
      vis[y] = 1;
      w[y] = G.w[i];
    }
    dep[1] = 1;
    for (int i = G.head[1]; i != -1; i = G.next[i]) {
      int x = G.to[i], y = -1;
      if (mm[x]) continue;
      mm[x] = ++m;
      vec[m].push_back(x);
      int ww;
      for (int j = G.head[x]; j != -1; j = G.next[j]) {
        int yy = G.to[j];
        if (vis[yy]) {
          mm[yy] = m;
          vec[m].push_back(yy);
          y = yy;
          ww = G.w[j];
          break;
        }
      }
      for (int j = 0; j < 3; ++j) st[m][j] = -1;
      int state = 1;
      val[x] = 0;
      dep[x] = 2;
      dfs(x, 1, state);
      st[m][0] = state;
      if (y != -1) {
        for (auto it : vec[m]) dep[it] = 0;
        state = 1;
        val[y] = 0;
        dep[y] = 2;
        dfs(y, 1, state);
        st[m][1] = state;
        st[m][2] = co1[state][ww ^ w[x] ^ w[y]];
      }
    }
    f[0][1] = 1;
    for (int i = 1; i <= m; ++i) {
      int o = i & 1;
      for (int j = 1; j < sz; ++j) {
        if (!f[o ^ 1][j]) continue;
        for (int k = 0; k < 3; ++k)
          if (st[i][k] != -1) {
            int temp = st[i][k];
            f[o][co[j][temp]] = addmod(f[o][co[j][temp]], f[o ^ 1][j]);
          }
        f[o][j] = addmod(f[o][j], f[o ^ 1][j]);
        f[o ^ 1][j] = 0;
      }
    }
    long long ans = 0;
    for (int i = 1; i < sz; ++i) ans = addmod(ans, f[m & 1][i]);
    printf("%lld\n", ans);
  }
}
