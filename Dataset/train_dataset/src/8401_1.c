#include <bits/stdc++.h>
using namespace std;
const int mod = 1000 * 1000 * 1000 + 7;
const int INF = 1e9 + 100;
const long long LINF = 1e18 + 100;
const int MAXN = 50100;
const int MEM = 6 * MAXN;
int n, m;
int ef[MAXN], eto[MAXN], col[MAXN], tim[MAXN];
vector<int> ngb[MAXN];
int gn;
vector<int> adj[MEM], rev[MEM];
int cnum[MEM], cn;
bool mark[MEM], ans[MEM];
vector<int> stk;
void dfs1(int v) {
  mark[v] = true;
  for (int u : adj[v])
    if (!mark[u]) dfs1(u);
  stk.push_back(v);
}
void dfs2(int v) {
  mark[v] = true;
  cnum[v] = cn;
  for (int u : rev[v])
    if (!mark[u]) dfs2(u);
}
inline int NOT(int x) {
  if (x > 2 * m) return (x % 2 ? x + 1 : x - 1);
  return (x > m ? x - m : x + m);
}
inline void addedge(int x, int y) {
  adj[x].push_back(y);
  rev[y].push_back(x);
}
inline void addcond(int x, int y) {
  addedge(NOT(x), y);
  addedge(NOT(y), x);
}
bool check(int x) {
  gn = 2 * m;
  for (int i = (0); i < (int)(MEM); i++) adj[i].clear(), rev[i].clear();
  stk.clear();
  memset(mark, 0, sizeof(mark));
  memset(ans, 0, sizeof(ans));
  memset(cnum, 0, sizeof(cnum));
  cn = 0, gn = 2 * m;
  for (int v = (1); v < (int)(n + 1); v++) {
    if (ngb[v].empty()) continue;
    ;
    ;
    sort((ngb[v]).begin(), (ngb[v]).end(),
         [&](int x, int y) { return col[x] < col[y]; });
    int ind = -1;
    for (int i = 0; i < (int)ngb[v].size();) {
      int j;
      for (j = i; j < (int)ngb[v].size() && col[ngb[v][i]] == col[ngb[v][j]];
           j++)
        ;
      if (j - i > 2 || (j - i == 2 && ind >= 0)) return false;
      if (j - i == 2) ind = i;
      i = j;
    }
    if (ind >= 0) {
      addcond(ngb[v][ind], ngb[v][ind + 1]);
    }
    gn += 2;
    addcond(gn, NOT(ngb[v][0]));
    for (int i = (1); i < (int)((int)ngb[v].size()); i++) {
      gn += 2;
      addcond(NOT(gn - 2), gn);
      addcond(NOT(gn - 2), NOT(ngb[v][i]));
      addcond(gn, NOT(ngb[v][i]));
    };
    ;
  }
  for (int i = (1); i < (int)(m + 1); i++)
    if (tim[i] > x) addcond(NOT(i), NOT(i));
  for (int i = (1); i < (int)(gn + 1); i++)
    if (!mark[i]) dfs1(i);
  memset(mark, 0, sizeof(mark));
  while (!stk.empty()) {
    int v = stk.back();
    stk.pop_back();
    if (!mark[v]) cn++, dfs2(v);
  };
  ;
  for (int i = (1); i < (int)(gn + 1); i++) {
    if (cnum[i] == cnum[NOT(i)])
      return false;
    else if (cnum[i] > cnum[NOT(i)])
      ans[i] = 1;
  }
  return true;
}
int32_t main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ;
  cin >> n >> m;
  for (int i = (1); i < (int)(m + 1); i++) {
    cin >> ef[i] >> eto[i] >> col[i] >> tim[i];
    ngb[ef[i]].push_back(i);
    ngb[eto[i]].push_back(i);
  }
  int l = -1, r = INF;
  while (r - l > 1) {
    int mid = (r + l) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  if (r > 1e9 + 10) return cout << "No\n", 0;
  cout << "Yes\n";
  check(r);
  vector<int> res;
  for (int i = (1); i < (int)(m + 1); i++)
    if (ans[i]) res.push_back(i);
  cout << r << ' ' << res.size() << '\n';
  for (int u : res) cout << u << ' ';
  cout << '\n';
  return 0;
}
