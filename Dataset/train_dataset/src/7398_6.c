#include <bits/stdc++.h>
#pragma warning(disable : 4996)
using namespace std;
struct node {
  long long l, r;
  mutable long long v;
  node(long long L, long long R = -1, long long V = 0) : l(L), r(R), v(V) {}
  bool operator<(const node &other) const { return l < other.l; }
};
set<node> s;
vector<pair<long long, long long> > vp;
set<node>::iterator split(long long pos) {
  set<node>::iterator it = s.lower_bound(node(pos));
  if (it != s.end() && it->l == pos) return it;
  --it;
  if (pos > it->r) return s.end();
  long long L = it->l, R = it->r;
  long long V = it->v;
  s.erase(it);
  s.insert(node(L, pos - 1, V));
  return s.insert(node(pos, R, V)).first;
}
void add(long long l, long long r, long long val) {
  split(l);
  set<node>::iterator itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) itl->v += val;
}
void assign(long long l, long long r, long long val) {
  split(l);
  set<node>::iterator itr = split(r + 1), itl = split(l);
  s.erase(itl, itr);
  s.insert(node(l, r, val));
}
long long Rank(long long l, long long r, long long k) {
  split(l);
  set<node>::iterator itr = split(r + 1), itl = split(l);
  vp.clear();
  for (; itl != itr; ++itl) {
    vp.push_back({itl->v, itl->r - itl->l + 1});
  }
  sort(vp.begin(), vp.end());
  for (auto i : vp) {
    k -= i.second;
    if (k <= 0) return i.first;
  }
  return -1;
}
long long qpow(long long x, long long y, long long mod) {
  if (y == 0ll) return 1ll;
  long long ans = qpow(x, y >> 1, mod);
  ans = ans * ans % mod;
  if (y & 1ll) ans = ans * x % mod;
  return ans;
}
long long sum(int l, int r, long long ex, long long mod) {
  split(l);
  set<node>::iterator itr = split(r + 1), itl = split(l);
  long long res = 0;
  for (; itl != itr; ++itl) {
    res =
        (res + (long long)(itl->r - itl->l + 1) * qpow(itl->v % mod, ex, mod)) %
        mod;
  }
  return res;
}
int n, m, seed, vmax;
int rnd() {
  int ret = seed;
  seed = (seed * 7ll + 13) % 1000000007;
  return ret;
}
int main() {
  cin >> n >> m >> seed >> vmax;
  for (int i = 1; i <= n; i++) {
    s.insert(node(i, i, (long long)(rnd() % vmax + 1)));
  }
  for (int i = 1; i <= m; i++) {
    int x, y, op, l, r;
    op = (rnd() % 4) + 1;
    l = (rnd() % n) + 1;
    r = (rnd() % n) + 1;
    if (l > r) swap(l, r);
    if (op == 3)
      x = (rnd() % (r - l + 1)) + 1;
    else {
      x = (rnd() % vmax) + 1;
    }
    if (op == 4) {
      y = (rnd() % vmax) + 1;
    }
    if (op == 1) {
      add(l, r, x);
    } else if (op == 2) {
      assign(l, r, x);
    } else if (op == 3) {
      cout << Rank(l, r, x) << endl;
    } else if (op == 4) {
      cout << sum(l, r, x, y) << endl;
    }
  }
  return 0;
}
