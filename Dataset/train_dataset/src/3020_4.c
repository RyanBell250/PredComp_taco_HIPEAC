#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,popcnt,avx,mmx,abm,tune=native")
using namespace std;
namespace output {
void __(short x) { cout << x; }
void __(unsigned x) { cout << x; }
void __(int x) { cout << x; }
void __(long long x) { cout << x; }
void __(unsigned long long x) { cout << x; }
void __(double x) { cout << x; }
void __(long double x) { cout << x; }
void __(char x) { cout << x; }
void __(const char* x) { cout << x; }
void __(const string& x) { cout << x; }
void __(bool x) { cout << (x ? "true" : "false"); }
template <class S, class T>
void __(const pair<S, T>& x) {
  __(1 ? "(" : ""), __(x.first), __(1 ? ", " : " "), __(x.second),
      __(1 ? ")" : "");
}
template <class T>
void __(const vector<T>& x) {
  __(1 ? "{" : "");
  bool _ = 0;
  for (const auto& v : x) __(_ ? 1 ? ", " : " " : ""), __(v), _ = 1;
  __(1 ? "}" : "");
}
template <class T>
void __(const set<T>& x) {
  __(1 ? "{" : "");
  bool _ = 0;
  for (const auto& v : x) __(_ ? 1 ? ", " : " " : ""), __(v), _ = 1;
  __(1 ? "}" : "");
}
template <class T>
void __(const multiset<T>& x) {
  __(1 ? "{" : "");
  bool _ = 0;
  for (const auto& v : x) __(_ ? 1 ? ", " : " " : ""), __(v), _ = 1;
  __(1 ? "}" : "");
}
template <class S, class T>
void __(const map<S, T>& x) {
  __(1 ? "{" : "");
  bool _ = 0;
  for (const auto& v : x) __(_ ? 1 ? ", " : " " : ""), __(v), _ = 1;
  __(1 ? "}" : "");
}
void pr() { cout << "\n"; }
template <class S, class... T>
void pr(const S& a, const T&... b) {
  __(a);
  if (sizeof...(b)) __(' ');
  pr(b...);
}
}  
using namespace output;
const int MN = 5e5 + 5;
const long double PI = (long double)4 * atan((long double)1),
                  eps = (long double)5e-19;
int N, R, i, j, x, y, cnt, nxt;
long double st[3 * MN];
map<long double, int> mp;
set<long double> pnt[MN];
long double aa[MN], bb[MN];
pair<int, int> pos[MN];
struct qur {
  int t, x, y;
} q[MN];
long long dot(pair<int, int> i, pair<int, int> j) {
  return 1LL * i.first * j.first + 1LL * i.second * j.second;
}
bool ok(int i, int j) {
  pair<int, int> v1, v2;
  if (aa[i] < aa[j])
    v1 = {pos[i].first + R, pos[i].second};
  else
    v1 = {pos[j].first + R, pos[j].second};
  if (bb[i] < bb[j])
    v2 = {pos[i].first - R, pos[i].second};
  else
    v2 = {pos[j].first - R, pos[j].second};
  return dot(v1, v2) >= 0;
}
void upd(int i, int s, int e, int ind, long double val, bool del = 0) {
  if (s != e) {
    if ((s + e) / 2 < ind)
      upd(2 * i + 1, (s + e) / 2 + 1, e, ind, val, del);
    else
      upd(2 * i, s, (s + e) / 2, ind, val, del);
    st[i] = max(st[2 * i], st[2 * i + 1]);
  } else {
    if (del)
      pnt[s].erase(val);
    else
      pnt[s].insert(val);
    if (pnt[s].empty())
      st[i] = -1;
    else {
      auto it = pnt[s].end();
      it--;
      st[i] = *it;
    }
  }
}
long double qu(int i, int s, int e, int ss, int se) {
  if (s >= ss && e <= se)
    return st[i];
  else if ((s + e) / 2 < ss)
    return qu(2 * i + 1, (s + e) / 2 + 1, e, ss, se);
  else if ((s + e) / 2 >= se)
    return qu(2 * i, s, (s + e) / 2, ss, se);
  else
    return max(qu(2 * i, s, (s + e) / 2, ss, se),
               qu(2 * i + 1, (s + e) / 2 + 1, e, ss, se));
}
int main() {
  scanf("%d%d", &R, &N);
  for (i = 1; i <= N; i++) {
    scanf("%d%d", &q[i].t, &q[i].x);
    if (q[i].t == 1) {
      cnt++;
      scanf("%d", &q[i].y);
      pos[cnt] = {q[i].x, q[i].y};
      aa[cnt] =
          (long double)atan2((long double)q[i].y, (long double)q[i].x + R);
      bb[cnt] =
          PI - (long double)atan2((long double)q[i].y, (long double)q[i].x - R);
      mp[aa[cnt]] = 0;
    } else if (q[i].t == 3)
      scanf("%d", &q[i].y);
  }
  for (auto it = mp.begin(); it != mp.end(); it++) it->second = ++nxt;
  cnt = 0;
  for (i = 1; i <= N; i++) {
    if (q[i].t == 1) {
      cnt++;
      upd(1, 1, nxt, mp[aa[cnt]], bb[cnt], 0);
    } else if (q[i].t == 2) {
      upd(1, 1, nxt, mp[aa[q[i].x]], bb[q[i].x], 1);
    } else {
      x = q[i].x, y = q[i].y;
      if (!ok(x, y))
        printf("NO\n");
      else {
        long double ix = min(aa[x], aa[y]);
        long double iy = min(bb[x], bb[y]);
        int inx = mp[ix];
        upd(1, 1, nxt, mp[aa[x]], bb[x], 1);
        upd(1, 1, nxt, mp[aa[y]], bb[y], 1);
        if (qu(1, 1, nxt, inx, nxt) >= iy)
          printf("NO\n");
        else
          printf("YES\n");
        upd(1, 1, nxt, mp[aa[x]], bb[x], 0);
        upd(1, 1, nxt, mp[aa[y]], bb[y], 0);
      }
    }
  }
  return 0;
}
