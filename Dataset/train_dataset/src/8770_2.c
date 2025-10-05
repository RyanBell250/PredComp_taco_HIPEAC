#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using db = double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
template <class T>
using V = vector<T>;
template <class T, size_t SZ>
using AR = array<T, SZ>;
template <class T>
using PR = pair<T, T>;
const int MOD = 1e9 + 7;
const int MX = 2e5 + 5;
const ll INF = 1e18;
const ld PI = acos((ld)-1);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
constexpr int pct(int x) { return __builtin_popcount(x); }
constexpr int bits(int x) { return 31 - __builtin_clz(x); }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
template <class T>
bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}
template <class T, class U>
T fstTrue(T lo, T hi, U first) {
  hi++;
  assert(lo <= hi);
  while (lo < hi) {
    T mid = lo + (hi - lo) / 2;
    first(mid) ? hi = mid : lo = mid + 1;
  }
  return lo;
}
template <class T, class U>
T lstTrue(T lo, T hi, U first) {
  lo--;
  assert(lo <= hi);
  while (lo < hi) {
    T mid = lo + (hi - lo + 1) / 2;
    first(mid) ? lo = mid : hi = mid - 1;
  }
  return lo;
}
template <class T>
void remDup(vector<T>& v) {
  sort(begin(v), end(v));
  v.erase(unique(begin(v), end(v)), end(v));
}
template <class T, class U>
void erase(T& t, const U& u) {
  auto it = t.find(u);
  assert(it != end(t));
  t.erase(it);
}
template <class T>
void re(complex<T>& c);
template <class T, class U>
void re(pair<T, U>& p);
template <class T>
void re(vector<T>& v);
template <class T, size_t SZ>
void re(AR<T, SZ>& a);
template <class T>
void re(T& x) {
  cin >> x;
}
void re(db& d) {
  str t;
  re(t);
  d = stod(t);
}
void re(ld& d) {
  str t;
  re(t);
  d = stold(t);
}
template <class T, class... U>
void re(T& t, U&... u) {
  re(t);
  re(u...);
}
template <class T>
void re(complex<T>& c) {
  T a, b;
  re(a, b);
  c = {a, b};
}
template <class T, class U>
void re(pair<T, U>& p) {
  re(p.first, p.second);
}
template <class T>
void re(vector<T>& x) {
  for (auto& a : x) re(a);
}
template <class T, size_t SZ>
void re(AR<T, SZ>& x) {
  for (auto& a : x) re(a);
}
template <class T>
void rv(int& n, vector<T>& x) {
  re(n);
  x.resize(n);
  for (auto& a : x) re(a);
}
str to_string(char c) { return str(1, c); }
str to_string(const char* second) { return (str)second; }
str to_string(str second) { return second; }
str to_string(bool b) { return to_string((int)b); }
template <class T>
str to_string(complex<T> c) {
  stringstream ss;
  ss << c;
  return ss.str();
}
str to_string(vector<bool> v) {
  str res = "{";
  for (int i = (0); i < ((int)(v).size()); ++i) res += char('0' + v[i]);
  res += "}";
  return res;
}
template <size_t SZ>
str to_string(bitset<SZ> b) {
  str res = "";
  for (int i = (0); i < (SZ); ++i) res += char('0' + b[i]);
  return res;
}
template <class T, class U>
str to_string(pair<T, U> p);
template <class T>
str to_string(T v) {
  bool fst = 1;
  str res = "";
  for (const auto& x : v) {
    if (!fst) res += " ";
    fst = 0;
    res += to_string(x);
  }
  return res;
}
template <class T, class U>
str to_string(pair<T, U> p) {
  return to_string(p.first) + " " + to_string(p.second);
}
template <class T>
void pr(T x) {
  cout << to_string(x);
}
template <class T, class... U>
void pr(const T& t, const U&... u) {
  pr(t);
  pr(u...);
}
void ps() { pr("\n"); }
template <class T, class... U>
void ps(const T& t, const U&... u) {
  pr(t);
  if (sizeof...(u)) pr(" ");
  ps(u...);
}
void DBG() { cerr << "]" << endl; }
template <class T, class... U>
void DBG(const T& t, const U&... u) {
  cerr << to_string(t);
  if (sizeof...(u)) cerr << ", ";
  DBG(u...);
}
void setIn(str second) { freopen(second.c_str(), "r", stdin); }
void setOut(str second) { freopen(second.c_str(), "w", stdout); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(0); }
void setIO(str second = "") {
  unsyncIO();
  if ((int)(second).size()) {
    setIn(second + ".in"), setOut(second + ".out");
  }
}
using T = ll;
int sgn(T a) { return (a > 0) - (a < 0); }
T sq(T a) { return a * a; }
T norm(const pair<T, T>& p) { return sq(p.first) + sq(p.second); }
T abs(const pair<T, T>& p) { return sqrt(norm(p)); }
T arg(const pair<T, T>& p) { return atan2(p.second, p.first); }
pair<T, T> conj(const pair<T, T>& p) { return pair<T, T>(p.first, -p.second); }
pair<T, T> perp(const pair<T, T>& p) { return pair<T, T>(-p.second, p.first); }
pair<T, T> dir(T ang) { return pair<T, T>(cos(ang), sin(ang)); }
pair<T, T> operator-(const pair<T, T>& l) {
  return pair<T, T>(-l.first, -l.second);
}
pair<T, T> operator+(const pair<T, T>& l, const pair<T, T>& r) {
  return pair<T, T>(l.first + r.first, l.second + r.second);
}
pair<T, T> operator-(const pair<T, T>& l, const pair<T, T>& r) {
  return pair<T, T>(l.first - r.first, l.second - r.second);
}
pair<T, T> operator*(const pair<T, T>& l, const T& r) {
  return pair<T, T>(l.first * r, l.second * r);
}
pair<T, T> operator*(const T& l, const pair<T, T>& r) { return r * l; }
pair<T, T> operator/(const pair<T, T>& l, const T& r) {
  return pair<T, T>(l.first / r, l.second / r);
}
pair<T, T> operator*(const pair<T, T>& l, const pair<T, T>& r) {
  return pair<T, T>(l.first * r.first - l.second * r.second,
                    l.second * r.first + l.first * r.second);
}
pair<T, T> operator/(const pair<T, T>& l, const pair<T, T>& r) {
  return l * conj(r) / norm(r);
}
pair<T, T>& operator+=(pair<T, T>& l, const pair<T, T>& r) { return l = l + r; }
pair<T, T>& operator-=(pair<T, T>& l, const pair<T, T>& r) { return l = l - r; }
pair<T, T>& operator*=(pair<T, T>& l, const T& r) { return l = l * r; }
pair<T, T>& operator/=(pair<T, T>& l, const T& r) { return l = l / r; }
pair<T, T>& operator*=(pair<T, T>& l, const pair<T, T>& r) { return l = l * r; }
pair<T, T>& operator/=(pair<T, T>& l, const pair<T, T>& r) { return l = l / r; }
pair<T, T> unit(const pair<T, T>& p) { return p / abs(p); }
T dot(const pair<T, T>& a, const pair<T, T>& b) {
  return a.first * b.first + a.second * b.second;
}
T cross(const pair<T, T>& a, const pair<T, T>& b) {
  return a.first * b.second - a.second * b.first;
}
T cross(const pair<T, T>& p, const pair<T, T>& a, const pair<T, T>& b) {
  return cross(a - p, b - p);
}
pair<T, T> reflect(const pair<T, T>& p, const pair<T, T>& a,
                   const pair<T, T>& b) {
  return a + conj((p - a) / (b - a)) * (b - a);
}
pair<T, T> foot(const pair<T, T>& p, const pair<T, T>& a, const pair<T, T>& b) {
  return (p + reflect(p, a, b)) / (T)2;
}
bool onSeg(const pair<T, T>& p, const pair<T, T>& a, const pair<T, T>& b) {
  return cross(a, b, p) == 0 && dot(p - a, p - b) <= 0;
}
template <class T, int... Ns>
struct BIT {
  T val = 0;
  void upd(T v) { val += v; }
  T query() { return val; }
};
template <class T, int N, int... Ns>
struct BIT<T, N, Ns...> {
  BIT<T, Ns...> bit[N + 1];
  template <typename... Args>
  void upd(int pos, Args... args) {
    assert(pos > 0);
    for (; pos <= N; pos += pos & -pos) bit[pos].upd(args...);
  }
  template <typename... Args>
  T sum(int r, Args... args) {
    T res = 0;
    for (; r; r -= r & -r) res += bit[r].query(args...);
    return res;
  }
  template <typename... Args>
  T query(int l, int r, Args... args) {
    return sum(r, args...) - sum(l - 1, args...);
  }
};
BIT<int, 400005> B;
int N;
ll K;
vector<pair<T, T>> v;
db ti = 0, ti2 = 0;
vpi todo[400005];
ll count_gre(db mid) {
  V<pair<pair<db, db>, int>> intervals;
  int cnt = 0;
  for (auto& t : v) {
    db frac = mid / sqrt(norm(t));
    if (frac <= 1) {
      frac = acos(frac);
      db ang = atan2(t.second, t.first);
      pair<db, db> interval = {ang - frac, ang + frac};
      intervals.push_back({interval, cnt});
      interval.first += 2 * PI, interval.second += 2 * PI;
      intervals.push_back({interval, cnt});
    }
    cnt++;
  }
  V<db> compress;
  compress.reserve(4 * N);
  for (auto& t : intervals) {
    compress.push_back(t.first.first);
    compress.push_back(t.first.second);
  }
  remDup(compress);
  auto ind = [&](db d) {
    return lower_bound(begin(compress), end(compress), d) - begin(compress) + 1;
  };
  for (int i = (0); i < (400005); ++i) todo[i].clear();
  for (auto& t : intervals)
    todo[ind(t.first.first)].push_back({ind(t.first.second), t.second});
  B = BIT<int, 400005>();
  vi seen(N);
  ll tot = 0;
  for (int i = (0); i < (400005); ++i)
    for (auto& t : todo[i]) {
      seen[t.second]++;
      if (seen[t.second] == 2) {
        tot += B.query(i, t.first);
      }
      B.upd(t.first, 1);
    }
  return tot;
}
int main() {
  setIO();
  re(N, K);
  clock_t beg = clock();
  v.resize(N);
  re(v);
  db lo = 0, hi = 3e4;
  for (int _ = (0); _ < (50); ++_) {
    0;
    db mid = (lo + hi) / 2;
    ll num = count_gre(mid);
    num = (ll)N * (N - 1) / 2 - num;
    if (num >= K)
      hi = mid;
    else
      lo = mid;
  }
  cout << fixed << setprecision(9) << lo;
}
