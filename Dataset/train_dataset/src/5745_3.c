#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse4")
using namespace std;
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename T, typename V>
void __print(const pair<T, V> &x) {
  cerr << '{';
  __print(x.first);
  cerr << ',';
  __print(x.second);
  cerr << '}';
}
template <typename T>
void __print(const T &x) {
  int f = 0;
  cerr << '{';
  for (auto &i : x) cerr << (f++ ? "," : ""), __print(i);
  cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) {
  __print(t);
  if (sizeof...(v)) cerr << ", ";
  _print(v...);
}
template <typename T, typename TT>
ostream &operator<<(ostream &os, const pair<T, TT> &t) {
  return os << t.first << " " << t.second;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &t) {
  for (auto &i : t) os << i << " ";
  return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &t : v) is >> t;
  return is;
}
template <typename T1, typename T2>
istream &operator>>(istream &is, vector<pair<T1, T2>> &v) {
  for (pair<T1, T2> &t : v) is >> t.first >> t.second;
  return is;
}
const long long mod = 1e9 + 7;
vector<pair<long long, long long>> item;
long long n, m;
vector<long long> v;
bool check(long long mid) {
  vector<long long> cnt = v;
  long long rem = 0;
  vector<long long> c(n, -1);
  for (auto x : item) {
    if (x.first > mid) continue;
    c[x.second - 1] = max(c[x.second - 1], x.first);
  }
  vector<vector<long long>> last(2e5 + 5);
  for (int i = 0; i < n; i++)
    if (c[i] != -1) last[c[i]].push_back(i);
  for (long long i = 1; i <= mid; i++) {
    rem++;
    if (i > 2e5) continue;
    for (auto x : last[i]) {
      if (!rem) break;
      if (cnt[x] >= rem) {
        cnt[x] -= rem;
        rem = 0;
        break;
      } else {
        rem -= cnt[x];
        cnt[x] = 0;
      }
    }
  }
  return accumulate(cnt.begin(), cnt.end(), 0) * 2 <= rem;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  cin >> n >> m;
  v.resize(n);
  item.resize(m);
  cin >> v >> item;
  long long lo = 0, hi = 4e5, ans = hi, mid;
  while (lo <= hi) {
    mid = lo + (hi - lo) / 2;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans << '\n';
  return 0;
}
