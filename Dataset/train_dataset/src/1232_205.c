#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using ld = long double;
using db = double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<double, double>;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<double>;
using vs = vector<string>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using F1 = function<void(int)>;
using F2 = function<void(int, int)>;
const int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};
const int di8[8] = {-1, -1, 0, 1, 1, 1, 0, -1},
          dj8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const ld PI = acos((ld)-1);
const ll INF = 1e18;
const double eps = 1e-11;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }
using ul = unsigned long long;
ul modMul(ul a, ul b, const ul mod) {
  ll ret = a * b - mod * (ul)((ld)a * b / mod);
  return ret + ((ret < 0) - (ret >= (ll)mod)) * mod;
}
ul modPow(ul a, ul b, const ul mod) {
  if (b == 0) return 1;
  ul res = modPow(a, b / 2, mod);
  res = modMul(res, res, mod);
  return b & 1 ? modMul(res, a, mod) : res;
}
bool prime(ul n) {
  if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
  ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
     s = __builtin_ctzll(n - 1), d = n >> s;
  for (auto& a : A) {
    ul p = modPow(a, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) p = modMul(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}
template <typename A, typename B>
pair<A, B> operator+(const pair<A, B>& a, const pair<A, B>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}
template <typename A, typename B>
pair<A, B> operator+=(pair<A, B>& a, const pair<A, B>& b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}
template <typename A, typename B>
pair<A, B> operator-(const pair<A, B>& a, const pair<A, B>& b) {
  return make_pair(a.first - b.first, a.second - b.second);
}
template <typename A, typename B>
pair<A, B> operator-(const pair<A, B>& a) {
  return make_pair(-a.first, -a.second);
}
template <typename A, typename B>
pair<A, B>& operator++(pair<A, B>& a) {
  ++a.first;
  ++a.second;
  return a;
}
template <typename A, typename B>
pair<A, B>& operator--(pair<A, B>& a) {
  --a.first;
  --a.second;
  return a;
}
template <typename A>
vector<A>& operator++(vector<A>& a) {
  for (auto it = a.begin(); it != a.end(); ++it) ++*it;
  return a;
}
template <typename A>
vector<A>& operator--(vector<A>& a) {
  for (auto it = a.begin(); it != a.end(); ++it) --*it;
  return a;
}
template <typename A, typename B>
pair<A, B> operator++(pair<A, B>& a, int) {
  pair<A, B> b = a;
  ++a;
  return b;
}
template <typename A, typename B>
pair<A, B> operator--(pair<A, B>& a, int) {
  pair<A, B> b = a;
  --a;
  return b;
}
template <typename A>
vector<A>& operator++(vector<A>& a, int) {
  vector<A> b = a;
  ++a;
  return b;
}
template <typename A>
vector<A>& operator--(vector<A>& a, int) {
  vector<A> b = a;
  --a;
  return b;
}
template <typename A, typename B>
pair<A, B> operator-=(pair<A, B>& a, const pair<A, B>& b) {
  a.first -= b.first;
  a.second -= b.second;
  return a;
}
bool pow2(int i) { return i && (i & -i) == i; }
constexpr int pct(int x) { return __builtin_popcount(x); }
constexpr int bits(int x) { return 31 - __builtin_clz(x); }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
ll half(ll x) { return fdiv(x, 2); }
bool inc(ll a, ll b, ll c) { return a <= b && b <= c; }
template <class t>
int lwb(const vector<t>& v, const t& a) {
  return lower_bound((v).begin(), (v).end(), a) - v.begin();
}
template <class T>
inline T lowbit(T n) {
  return (n ^ (n - 1)) & n;
}
template <typename I>
struct _reversed_struct {
  I& v_;
  explicit _reversed_struct(I& v) : v_{v} {}
  typename I::reverse_iterator begin() const { return v_.rbegin(); }
  typename I::reverse_iterator end() const { return v_.rend(); }
};
template <typename I>
_reversed_struct<I> reversed(I& v) {
  return _reversed_struct<I>(v);
}
template <typename T1, typename T2>
typename vector<pair<T1, T2>>::iterator lower_bound(
    const vector<pair<T1, T2>>& v, const T1& x) {
  return lower_bound(
      (v).begin(), (v).end(), x,
      [](pair<T1, T2> a, pair<T1, T2> b) { return a.first < b.first; });
}
template <typename T1, typename T2>
typename vector<pair<T1, T2>>::iterator upper_bound(
    const vector<pair<T1, T2>>& v, const T1& x) {
  return upper_bound(
      (v).begin(), (v).end(), x,
      [](pair<T1, T2> a, pair<T1, T2> b) { return a.first < b.first; });
}
bool isUpperCase(char c) { return c >= 'A' && c <= 'Z'; }
bool isLowerCase(char c) { return c >= 'a' && c <= 'z'; }
bool isLetter(char c) { return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z'; }
bool isDigit(char c) { return c >= '0' && c <= '9'; }
char toLowerCase(char c) { return (isUpperCase(c)) ? (c + 32) : c; }
char toUpperCase(char c) { return (isLowerCase(c)) ? (c - 32) : c; }
int toInt(string s) {
  int r = 0;
  istringstream sin(s);
  sin >> r;
  return r;
}
ll toInt64(string s) {
  ll r = 0;
  istringstream sin(s);
  sin >> r;
  return r;
}
double toDouble(string s) {
  double r = 0;
  istringstream sin(s);
  sin >> r;
  return r;
}
template <class T>
inline T sqr(T x) {
  return x * x;
}
double dist(double x1, double y1, double x2, double y2) {
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
double distR(double x1, double y1, double x2, double y2) {
  return sqr(x1 - x2) + sqr(y1 - y2);
}
template <class T>
T cross(T x0, T y0, T x1, T y1, T x2, T y2) {
  return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}
int crossOper(double x0, double y0, double x1, double y1, double x2,
              double y2) {
  double t = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
  if (fabs(t) <= eps) return 0;
  return (t < 0) ? -1 : 1;
}
bool isIntersect(double x1, double y1, double x2, double y2, double x3,
                 double y3, double x4, double y4) {
  return crossOper(x1, y1, x2, y2, x3, y3) * crossOper(x1, y1, x2, y2, x4, y4) <
             0 &&
         crossOper(x3, y3, x4, y4, x1, y1) * crossOper(x3, y3, x4, y4, x2, y2) <
             0;
}
bool isMiddle(double s, double m, double t) {
  return fabs(s - m) <= eps || fabs(t - m) <= eps || (s < m) != (t < m);
}
constexpr ll power(ll x, int p) { return p == 0 ? 1 : (x * power(x, p - 1)); }
bool isPower(ll x, ll y) {
  ll res1 = log(y) / log(x);
  double res2 = log(y) / log(x);
  return (res1 == res2);
}
template <class T>
bool chmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool chmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}
void TIME() {}
template <class T>
void remDup(vector<T>& v) {
  sort((v).begin(), (v).end());
  v.erase(unique((v).begin(), (v).end()), end(v));
}
template <class T, class U>
void remAll(vector<T>& v, U a) {
  v.erase(remove((v).begin(), (v).end(), a), v.end());
}
template <class T, class U>
T fstTrue(T lo, T hi, U f) {
  while (lo < hi) {
    T mid = half(lo + hi);
    f(mid) ? hi = mid : lo = mid + 1;
  }
  return lo;
}
template <class T, class U>
T lstTrue(T lo, T hi, U f) {
  while (lo < hi) {
    T mid = half(lo + hi + 1);
    f(mid) ? lo = mid : hi = mid - 1;
  }
  return lo;
}
template <class T, class U, class C>
string to_string(tuple<T, U, C> p);
template <class T, class U, class C, class D>
string to_string(tuple<T, U, C, D> p);
string to_string(char c) { return string(1, c); }
string to_string(bool b) { return to_string((int)b); }
string to_string(const char* s) { return (string)s; }
string to_string(string s) { return s; }
template <class T>
string to_string(complex<T> c) {
  stringstream ss;
  ss << c;
  return ss.str();
}
string to_string(vb v) {
  string res = "{";
  for (int i = (0); i < (((int)(v).size())); ++i) res += char('0' + v[i]);
  res += "}";
  return res;
}
template <size_t SZ>
string to_string(bitset<SZ> b) {
  string res = "";
  for (int i = (0); i < (((int)(b).size())); ++i) res += char('0' + b[i]);
  return res;
}
template <class T, class U>
string to_string(pair<T, U> p);
template <class T>
string to_string(T v) {
  bool fst = 1;
  string res = "";
  for (const auto& x : v) {
    if (!fst) res += " ";
    fst = 0;
    res += to_string(x);
  }
  return res;
}
template <class T, class U>
string to_string(pair<T, U> p) {
  return to_string(p.first) + " " + to_string(p.second);
}
template <class T, class U, class C>
string to_string(tuple<T, U, C> p) {
  return to_string(get<0>(p)) + " " + to_string(get<1>(p)) + " " +
         to_string(get<2>(p));
}
template <class T, class U, class C, class D>
string to_string(tuple<T, U, C, D> p) {
  return to_string(get<0>(p)) + " " + to_string(get<1>(p)) + " " +
         to_string(get<2>(p)) + " " + to_string(get<3>(p));
}
template <class T, class U, class C>
void re(tuple<T, U, C>& p);
template <class T, class U, class C, class D>
void re(tuple<T, U, C, D>& p);
template <class T>
void re(complex<T>& c);
template <class T, class U>
void re(pair<T, U>& p);
template <class T>
void re(vector<T>& v);
template <class T>
void rv(int n, vector<T>& x) {
  x.resize(n);
  re(x);
}
template <class T, size_t SZ>
void re(array<T, SZ>& a);
template <class T>
void re(T& x) {
  cin >> x;
}
void re(double& d) {
  string t;
  re(t);
  d = stod(t);
}
void re(ld& d) {
  string t;
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
void re(array<T, SZ>& x) {
  for (auto& a : x) re(a);
}
template <class T, class U, class C>
void re(tuple<T, U, C>& p) {
  re(get<0>(p), get<1>(p), get<2>(p));
}
template <class T, class U, class C, class D>
void re(tuple<T, U, C, D>& p) {
  re(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
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
struct chash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  template <typename L, typename R>
  size_t operator()(pair<L, R> const& second) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(second.first * 31 + second.second + FIXED_RANDOM);
  }
};
template <class T>
using V = vector<T>;
template <class T, size_t SZ>
using AR = array<T, SZ>;
template <class T>
using mpq = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using pq = priority_queue<T>;
template <class T, class U>
using um = unordered_map<T, U, chash>;
template <class T>
using us = unordered_set<T, chash>;
template <class T>
using PR = pair<T, T>;
const int MOD = 1e9 + 7;
template <int MOD, int RT>
struct mint {
  static const int mod = MOD;
  static constexpr mint rt() { return RT; }
  int v;
  explicit operator int() const { return v; }
  mint() { v = 0; }
  mint(ll _v) {
    v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
    if (v < 0) v += MOD;
  }
  friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
  friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
  friend bool operator<(const mint& a, const mint& b) { return a.v < b.v; }
  friend void re(mint& a) {
    ll x;
    re(x);
    a = mint(x);
  }
  friend string to_string(mint a) { return to_string(a.v); }
  mint& operator+=(const mint& m) {
    if ((v += m.v) >= MOD) v -= MOD;
    return *this;
  }
  mint& operator-=(const mint& m) {
    if ((v -= m.v) < 0) v += MOD;
    return *this;
  }
  mint& operator*=(const mint& m) {
    v = (ll)v * m.v % MOD;
    return *this;
  }
  mint& operator/=(const mint& m) { return (*this) *= inv(m); }
  friend mint pow(mint a, ll p) {
    mint ans = 1;
    assert(p >= 0);
    for (; p; p /= 2, a *= a)
      if (p & 1) ans *= a;
    return ans;
  }
  friend mint inv(const mint& a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }
  mint operator-() const { return mint(-v); }
  mint& operator++() { return *this += 1; }
  mint& operator--() { return *this -= 1; }
  friend mint operator+(mint a, const mint& b) { return a += b; }
  friend mint operator-(mint a, const mint& b) { return a -= b; }
  friend mint operator*(mint a, const mint& b) { return a *= b; }
  friend mint operator/(mint a, const mint& b) { return a /= b; }
};
typedef mint<MOD, 5> mi;
vector<vector<mi>> scmb;
void genComb(int SZ) {
  scmb.assign(SZ, vector<mi>(SZ));
  scmb[0][0] = 1;
  for (int i = (1); i < (SZ); ++i)
    for (int j = (0); j < (i + 1); ++j)
      scmb[i][j] = scmb[i - 1][j] + (j ? scmb[i - 1][j - 1] : 0);
}
vi invs, fac, ifac;
void genFac(int SZ) {
  invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ);
  invs[1] = fac[0] = ifac[0] = 1;
  for (int i = (2); i < (SZ); ++i)
    invs[i] = MOD - (ll)MOD / i * invs[MOD % i] % MOD;
  for (int i = (1); i < (SZ); ++i) {
    fac[i] = (ll)fac[i - 1] * i % MOD;
    ifac[i] = (ll)ifac[i - 1] * invs[i] % MOD;
  }
}
mi comb(int a, int b) {
  if (a < b || b < 0) return 0;
  return (ll)fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll ncr(ll n, ll r) {
  ll p = 1, k = 1;
  if (n - r < r) r = n - r;
  if (r != 0) {
    while (r) {
      p *= n;
      k *= r;
      ll m = gcd(p, k);
      p /= m;
      k /= m;
      n--;
      r--;
    }
  } else
    p = 1;
  return p;
}
void DBG() { cerr << "]" << endl; }
template <class T, class... U>
void DBG(const T& t, const U&... u) {
  cerr << to_string(t);
  if (sizeof...(u)) cerr << ", ";
  DBG(u...);
}
V<vi> readGraph(int n, int m) {
  V<vi> g(n);
  for (int i = (0); i < (m); ++i) {
    int a, b;
    re(a, b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  return g;
}
V<vpi> readwGraph(int n, int m) {
  V<vpi> g(n);
  for (int i = (0); i < (m); ++i) {
    int a, b, w;
    re(a, b, w);
    a--;
    b--;
    g[a].emplace_back(b, w);
    g[b].emplace_back(a, w);
  }
  return g;
}
V<vi> readTree(int n) { return readGraph(n, n - 1); }
V<vpi> readwTree(int n) { return readwGraph(n, n - 1); }
void setPrec() { cout << fixed << setprecision(15); }
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(0); }
void setIO(str s = "") {
  unsyncIO();
  setPrec();
  if (((int)(s).size())) {
    setIn(s + ".in");
    setOut(s + ".out");
  }
}
const int mxN = 2e5 + 5;
ll n, l, r;
mi dp[mxN][3];
void solve() {
  re(n, l, r);
  ll st = 0, st1 = 0, st2 = 0;
  for (int i = (l); i < (r + 1); ++i) {
    if (st && st1 && st2) break;
    if (i % 3 == 0) st2 = i;
    if (i % 3 == 1) st = i;
    if (i % 3 == 2) st1 = i;
  }
  dp[0][0] = (r - (!st2 ? r : st2)) / 3 + min(st2, 1ll);
  dp[0][1] = (r - (!st ? r : st)) / 3 + min(st, 1ll);
  dp[0][2] = (r - (!st1 ? r : st1)) / 3 + min(st1, 1ll);
  0;
  for (int i = (1); i < (n); ++i) {
    dp[i][0] = dp[i - 1][0] * dp[0][0] + dp[i - 1][2] * dp[0][1] +
               dp[i - 1][1] * dp[0][2];
    dp[i][1] = dp[i - 1][0] * dp[0][1] + dp[i - 1][1] * dp[0][0] +
               dp[i - 1][2] * dp[0][2];
    dp[i][2] = dp[i - 1][2] * dp[0][0] + dp[i - 1][1] * dp[0][1] +
               dp[i - 1][0] * dp[0][2];
  }
  ps(dp[n - 1][0]);
}
int main() {
  setIO();
  int T = 1;
  for (int _ = (1); _ < (T + 1); ++_) {
    solve();
  }
}
