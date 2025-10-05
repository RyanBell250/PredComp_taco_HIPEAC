#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
struct ImplicitKosaraju {
  int n;
  int (*unmarkedadj)(int, bool);
  void (*mark)(int, bool);
  void (*reset)();
  void init(int _n) { n = _n; }
  vector<bool> been;
  vector<int> top;
  int ntop;
  vector<int> comp;
  int ncomp;
  vector<vector<int>> compnodes;
  void dfs1(int at) {
    been[at] = true;
    mark(at, true);
    while (true) {
      int to = unmarkedadj(at, true);
      if (to == -1) break;
      dfs1(to);
    }
    top[ntop++] = at;
  }
  void dfs2(int at, int c) {
    comp[at] = c;
    compnodes[c].push_back(at);
    mark(at, false);
    while (true) {
      int to = unmarkedadj(at, false);
      if (to == -1) break;
      dfs2(to, c);
    }
  }
  void calc() {
    ntop = ncomp = 0;
    been = vector<bool>(n, false), top = vector<int>(n),
    comp = vector<int>(n, -1), compnodes.clear();
    reset();
    for (int i = (0); i < (n); ++i)
      if (!been[i]) dfs1(i);
    reset();
    for (int i = ntop - 1; i >= 0; --i)
      if (comp[top[i]] == -1) {
        compnodes.push_back(vector<int>());
        dfs2(top[i], ncomp++);
      }
  }
};
struct HLD {
  int n;
  vector<vector<int>> adj;
  void init(int _n) {
    n = _n;
    adj = vector<vector<int>>(n);
  }
  vector<int> par;
  vector<int> dep;
  vector<int> sz;
  vector<int> heavy;
  vector<int> psize;
  int np;
  vector<int> hroot;
  vector<int> hpath;
  vector<int> hpos;
  void dfsinit(int at) {
    if (par[at] != -1) dep[at] = dep[par[at]] + 1;
    for (int i = (0); i < (((int)(adj[at]).size())); ++i) {
      int to = adj[at][i];
      if (to == par[at]) continue;
      par[to] = at;
      dfsinit(to);
      sz[at] += sz[to];
      if (heavy[at] == -1 || sz[to] > sz[heavy[at]]) heavy[at] = to;
    }
  }
  void calc() {
    par = vector<int>(n, -1), dep = vector<int>(n, 0), sz = vector<int>(n, 1),
    heavy = vector<int>(n, -1);
    dfsinit(0);
    hroot = hpath = hpos = vector<int>(n, -1), np = 0, psize = vector<int>();
    for (int i = (0); i < (n); ++i)
      if (par[i] == -1 || heavy[par[i]] != i) {
        int p = np++;
        psize.push_back(0);
        for (int at = i; at != -1; at = heavy[at])
          hroot[at] = i, hpath[at] = p, hpos[at] = psize[p]++;
      }
  }
  vector<pair<int, pair<int, int>>> query(int a, int b) {
    vector<pair<int, pair<int, int>>> ret;
    while (hpath[a] != hpath[b]) {
      if (dep[hroot[a]] < dep[hroot[b]]) swap(a, b);
      ret.push_back(make_pair(hpath[a], make_pair(0, hpos[a])));
      a = par[hroot[a]];
    }
    if (dep[a] < dep[b]) swap(a, b);
    if (a != b)
      ret.push_back(make_pair(hpath[a], make_pair(hpos[b] + 1, hpos[a])));
    return ret;
  }
};
struct HLDIntersect {
  bool (*isactive)(int);
  int n, me;
  vector<vector<int>> allbyl;
  vector<vector<int>> prefbyr;
  vector<int> scnt;
  vector<int> sidx;
  vector<vector<int>> slst;
  void init(int _n) {
    n = _n;
    int m = 1;
    while (m < n) m *= 2;
    scnt = sidx = vector<int>(2 * m - 1, 0),
    slst = vector<vector<int>>(2 * m - 1);
  }
  void smod(int x, int l, int r, int L, int R, int ID, int BY) {
    scnt[x] += BY;
    if (L <= l && r <= R) {
      if (BY == +1) slst[x].push_back(ID);
    } else {
      int m = l + (r - l) / 2;
      if (L <= m) smod(2 * x + 1, l, m, L, R, ID, BY);
      if (m + 1 <= R) smod(2 * x + 2, m + 1, r, L, R, ID, BY);
    }
  }
  int sget(int x, int l, int r, int L, int R, int SKIP) {
    if (scnt[x] == 0) return -1;
    while (sidx[x] < ((int)(slst[x]).size())) {
      if (slst[x][sidx[x]] != SKIP) {
        if (isactive(slst[x][sidx[x]])) return slst[x][sidx[x]];
      } else {
        if (sidx[x] + 1 >= ((int)(slst[x]).size())) break;
        assert(slst[x][sidx[x] + 1] != SKIP);
        if (isactive(slst[x][sidx[x] + 1])) return slst[x][sidx[x] + 1];
        slst[x][sidx[x] + 1] = slst[x][sidx[x]];
      }
      ++sidx[x];
    }
    int ret = -1;
    if (l != r) {
      int m = l + (r - l) / 2;
      if (L <= m && ret == -1) ret = sget(2 * x + 1, l, m, L, R, SKIP);
      if (m + 1 <= R && ret == -1) ret = sget(2 * x + 2, m + 1, r, L, R, SKIP);
    }
    return ret;
  }
  void add(int l, int r, int id) {
    smod(0, 0, n - 1, l, r, id, +1);
    return;
    allbyl[l].push_back(id);
    if (l == 0)
      prefbyr[r].push_back(id);
    else
      smod(0, 0, n - 1, l, r, id, +1);
  }
  vector<pair<int, int>> a;
  int aidx;
  vector<pair<int, int>> b;
  int bidx;
  void precalc() {}
  void rem(int l, int r, int id) {
    smod(0, 0, n - 1, l, r, id, -1);
    return;
    if (l != 0) smod(0, 0, n - 1, l, r, id, -1);
  }
  int query(int l, int r, int skip) {
    return sget(0, 0, n - 1, l, r, skip);
    if (l == 0) {
      while (aidx < ((int)(a).size()) && a[aidx].first <= r) {
        if (a[aidx].second != skip) {
          if (isactive(a[aidx].second)) return a[aidx].second;
        } else {
          if (aidx + 1 >= ((int)(a).size()) || a[aidx + 1].first > r) break;
          assert(a[aidx + 1].second != skip);
          if (isactive(a[aidx + 1].second)) return a[aidx + 1].second;
          a[aidx + 1] = a[aidx];
        }
        ++aidx;
      }
      return -1;
    } else {
      while (bidx < ((int)(b).size()) && b[bidx].first >= l) {
        if (b[bidx].second != skip) {
          if (isactive(b[bidx].second)) return b[bidx].second;
        } else {
          if (bidx + 1 >= ((int)(b).size()) || b[bidx + 1].first < l) break;
          assert(b[bidx + 1].second != skip);
          if (isactive(b[bidx + 1].second)) return b[bidx + 1].second;
          b[bidx + 1] = b[bidx];
        }
        ++bidx;
      }
      return sget(0, 0, n - 1, l, r, skip);
    }
  }
};
const int MAXN = 100000;
const int MAXQ = 10000;
int n;
vector<int> adj[MAXN];
int nq;
int q[MAXQ][4];
int ans[MAXQ];
HLD hld;
vector<pair<int, pair<int, int>>> segs[2 * MAXQ];
vector<bool> active;
vector<HLDIntersect> paths;
ImplicitKosaraju impkos;
bool isactive(int id) { return active[id]; }
void reset() {
  active = vector<bool>(2 * nq, true);
  paths = vector<HLDIntersect>(hld.np);
  for (int i = (0); i < (((int)(paths).size())); ++i)
    paths[i].init(hld.psize[i]), paths[i].isactive = isactive, paths[i].me = i;
  for (int at = (0); at < (2 * nq); ++at)
    for (int i = (0); i < (((int)(segs[at]).size())); ++i)
      paths[segs[at][i].first].add(segs[at][i].second.first,
                                   segs[at][i].second.second, at);
  for (int i = (0); i < (((int)(paths).size())); ++i) paths[i].precalc();
}
int unmarkedadj(int at, bool rev) {
  if (rev) at ^= 1;
  for (int i = (0); i < (((int)(segs[at]).size())); ++i) {
    int cur = paths[segs[at][i].first].query(segs[at][i].second.first,
                                             segs[at][i].second.second, at);
    if (cur == -1) continue;
    if (!rev) cur ^= 1;
    return cur;
  }
  return -1;
}
void mark(int at, bool rev) {
  if (!rev) at ^= 1;
  for (int i = (0); i < (((int)(segs[at]).size())); ++i)
    paths[segs[at][i].first].rem(segs[at][i].second.first,
                                 segs[at][i].second.second, at);
  active[at] = false;
}
bool solve() {
  hld.init(n);
  for (int i = (0); i < (n); ++i)
    for (int j = (0); j < (((int)(adj[i]).size())); ++j)
      hld.adj[i].push_back(adj[i][j]);
  hld.calc();
  for (int i = (0); i < (nq); ++i)
    for (int j = (0); j < (2); ++j) {
      int a = q[i][2 * j + 0], b = q[i][2 * j + 1];
      segs[2 * i + j] = hld.query(a, b);
    }
  impkos.init(2 * nq);
  impkos.unmarkedadj = unmarkedadj, impkos.mark = mark, impkos.reset = reset;
  impkos.calc();
  for (int i = (0); i < (nq); ++i)
    if (impkos.comp[2 * i + 0] == impkos.comp[2 * i + 1]) return false;
  for (int i = (0); i < (nq); ++i) ans[i] = -1;
  for (int i = (0); i < (impkos.ncomp); ++i)
    for (int j = (0); j < (((int)(impkos.compnodes[i]).size())); ++j) {
      int at = impkos.compnodes[i][j];
      if (ans[at >> 1] == -1) ans[at >> 1] = at % 2 == 0 ? 1 : 2;
    }
  return true;
}
void run() {
  scanf("%d", &n);
  for (int i = (0); i < (n - 1); ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  scanf("%d", &nq);
  for (int i = (0); i < (nq); ++i)
    for (int j = (0); j < (4); ++j) scanf("%d", &q[i][j]), --q[i][j];
  if (!solve()) {
    printf("NO\n");
    return;
  }
  printf("YES\n");
  for (int i = (0); i < (nq); ++i) printf("%d\n", ans[i]);
}
struct UF {
  vector<int> par, sz;
  UF(int n) {
    par = sz = vector<int>(n);
    for (int i = (0); i < (n); ++i) par[i] = i, sz[i] = 1;
  }
  int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a, sz[a] += sz[b];
    return true;
  }
};
set<pair<int, int>> seen;
bool verifypath(int a, int b, int prev) {
  if (a == b) return true;
  for (int i = (0); i < (((int)(adj[a]).size())); ++i) {
    int c = adj[a][i];
    if (c == prev) continue;
    if (!verifypath(c, b, a)) continue;
    pair<int, int> e = make_pair(a, c);
    if (e.first > e.second) swap(e.first, e.second);
    assert(!seen.count(e));
    seen.insert(e);
    return true;
  }
  return false;
}
void verify() {
  seen.clear();
  for (int i = (0); i < (nq); ++i) {
    int a = q[i][2 * (ans[i] - 1) + 0], b = q[i][2 * (ans[i] - 1) + 1];
    assert(verifypath(a, b, -1));
  }
}
int myrand() { return rand() % 1000 * 1000 + rand() % 1000; }
void stress() {
  for (int rep = (0); rep < (10000); ++rep) {
    n = 20;
    for (int i = (0); i < (n); ++i) adj[i].clear();
    UF uf(n);
    for (int i = (0); i < (n - 1); ++i)
      while (true) {
        int a = myrand() % n, b = myrand() % n;
        if (!uf.unite(a, b)) continue;
        adj[a].push_back(b);
        adj[b].push_back(a);
        break;
      }
    nq = 5;
    for (int i = (0); i < (nq); ++i)
      for (int j = (0); j < (4); ++j) q[i][j] = rand() % n;
    bool have = solve();
    printf("%c", have ? 'V' : 'x');
    if ((rep + 1) % 40 == 0) puts("");
    if (have) verify();
  }
}
int main() {
  run();
  return 0;
}
