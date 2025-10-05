#include <bits/stdc++.h>
using namespace std;
inline int sgn(int x) { return (x > 0) ? 1 : -1; }
int addv[100005];
struct SETS {
  int id;
  struct Data {
    int x, v, id;
    Data() {}
    Data(int a, int b, int c) : x(a), v(b), id(c) {}
    bool operator<(const Data &b) const {
      int t1 = x - sgn(v) * addv[id], t2 = b.x - sgn(b.v) * addv[b.id];
      return (t1 != t2) ? t1 < t2 : v < b.v;
    }
  };
  set<Data> st;
  set<pair<int, Data> > dis;
  int getval(int x) {
    set<Data>::iterator it =
        st.lower_bound(Data(x - addv[id], -0x3f3f3f3f, id));
    return (it->x - sgn(it->v) * addv[id] == x) ? it->v : 0;
  }
  void update1(set<Data>::iterator it, bool v) {
    if (it != st.begin()) {
      set<Data>::iterator it2 = it;
      it2--;
      if (it->v > 0 && it2->v < 0) {
        pair<int, Data> t(it->x - it2->x, *it);
        if (v)
          dis.insert(t);
        else
          dis.erase(t);
      }
    }
  }
  void update2(set<Data>::iterator it, bool v) {
    set<Data>::iterator it2 = it;
    it2++;
    if (it2 != st.end()) {
      if (it2->v > 0 && it->v < 0) {
        pair<int, Data> t(it2->x - it->x, *it2);
        if (v)
          dis.insert(t);
        else
          dis.erase(t);
      }
    }
  }
  void add(int x, int v) {
    set<Data>::iterator it =
        st.lower_bound(Data(x - addv[id], -0x3f3f3f3f, id));
    if (it != st.end() && it->x - sgn(it->v) * addv[id] == x) {
      update1(it, 0);
      update2(it, 0);
      v += it->v;
      st.erase(it);
      if (v) {
        it = st.insert(Data(x + sgn(v) * addv[id], v, id)).first;
        update1(it, 1);
        update2(it, 1);
      } else {
        it = st.lower_bound(Data(x + sgn(v) * addv[id], v, id));
        if (it != st.end()) update1(it, 0);
      }
    } else {
      if (it != st.end()) update1(it, 0);
      it = st.insert(Data(x + sgn(v) * addv[id], v, id)).first;
      update1(it, 1);
      update2(it, 1);
    }
  }
  void trans(int d) {
    while (!dis.empty() && (dis.begin())->first - 2 * (addv[id] + d) <= 0) {
      set<Data>::iterator it = st.lower_bound((dis.begin())->second), it2 = it;
      it2--;
      update1(it, 0);
      update2(it, 0);
      update1(it2, 0);
      if (abs(it->v) > abs(it2->v)) {
        Data t = *it;
        t.v += it2->v;
        st.erase(it);
        st.erase(it2);
        it = st.insert(t).first;
        update1(it, 1);
        update2(it, 1);
      } else if (abs(it2->v) > abs(it->v)) {
        Data t = *it2;
        t.v += it->v;
        st.erase(it);
        st.erase(it2);
        it2 = st.insert(t).first;
        update1(it2, 1);
        update2(it2, 1);
      } else {
        set<Data>::iterator it3 = it;
        it3++;
        st.erase(it);
        st.erase(it2);
        if (it3 != st.end()) update1(it3, 1);
      }
    }
    addv[id] += d;
  }
  void merge(SETS &b) {
    if (st.size() < b.st.size()) swap(*this, b);
    for (set<Data>::iterator it = b.st.begin(); it != b.st.end(); it++)
      add(it->x - sgn(it->v) * addv[b.id], it->v);
  }
  int query() {
    int ans = 0, s = 0;
    for (set<Data>::iterator it = st.begin(); it != st.end(); it++) {
      s += it->v;
      ans = max(ans, s);
    }
    return ans;
  }
};
SETS f[100005];
struct Edge {
  int t, v, next;
  Edge() {}
  Edge(int a, int b, int c) : t(a), v(b), next(c) {}
};
Edge e[200005];
int head[100005];
vector<pair<int, int> > vt[100005], vt2[100005];
void dfs(int x, int fa) {
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].t != fa) {
      int u = e[i].t;
      dfs(u, x);
      f[u].trans(e[i].v - 1);
      f[x].merge(f[u]);
    }
  for (int i = 0; i < vt[x].size(); i++) {
    int d = vt[x][i].first, v = vt[x][i].second;
    int nv = max(0, max(-f[x].getval(d), f[x].getval(d + 1)));
    if (nv < v) vt2[x].push_back(pair<int, int>(d, v - nv));
  }
  f[x].trans(1);
  for (int i = 0; i < vt2[x].size(); i++) {
    int d = vt2[x][i].first, v = vt2[x][i].second;
    f[x].add(d, v);
    f[x].add(d + 1, -v);
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    e[2 * i - 1] = Edge(y, 2 * z, head[x]);
    head[x] = 2 * i - 1;
    e[2 * i] = Edge(x, 2 * z, head[y]);
    head[y] = 2 * i;
  }
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    vt[z].push_back(pair<int, int>(2 * x, y));
  }
  for (int i = 1; i <= n; i++) f[i].id = i;
  dfs(1, 0);
  printf("%d\n", f[1].query());
  return 0;
}
