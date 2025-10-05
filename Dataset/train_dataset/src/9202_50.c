#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
using namespace std;
double eps = 1e-12;
double pi = acos(-1);
const bool CHECK_OVERFLOW64 = true;
using dist_t = long double;
struct point {
  int64_t x, y;
  point() : x(0), y(0) {}
  point(int64_t _x, int64_t _y) : x(_x), y(_y) {}
  point &operator+=(const point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  point &operator-=(const point &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  point &operator*=(int64_t mult) {
    x *= mult;
    y *= mult;
    return *this;
  }
  point operator+(const point &other) const { return point(*this) += other; }
  point operator-(const point &other) const { return point(*this) -= other; }
  point operator*(int64_t mult) const { return point(*this) *= mult; }
  bool operator==(const point &other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const point &other) const { return !(*this == other); }
  point operator-() const { return point(-x, -y); }
  point rotate90() const { return point(-y, x); }
  int64_t norm() const { return (int64_t)x * x + (int64_t)y * y; }
  dist_t dist() const { return sqrt(dist_t(norm())); }
  bool top_half() const { return y > 0 || (y == 0 && x > 0); }
  friend ostream &operator<<(ostream &os, const point &p) {
    return os << '(' << p.x << ", " << p.y << ')';
  }
};
int64_t cross(const point &a, const point &b) {
  return (int64_t)a.x * b.y - (int64_t)b.x * a.y;
}
int64_t dot(const point &a, const point &b) {
  return (int64_t)a.x * b.x + (int64_t)a.y * b.y;
}
int cross_sign(const point &a, const point &b) {
  if (CHECK_OVERFLOW64) {
    long double double_value = (long double)a.x * b.y - (long double)b.x * a.y;
    if (abs(double_value) > 1e18) return double_value > 0 ? +1 : -1;
  }
  uint64_t uint64_value = (uint64_t)a.x * b.y - (uint64_t)b.x * a.y;
  int64_t actual = int64_t(uint64_value);
  return (actual > 0) - (actual < 0);
}
bool left_turn_strict(const point &a, const point &b, const point &c) {
  return cross_sign(b - a, c - a) > 0;
}
bool left_turn_lenient(const point &a, const point &b, const point &c) {
  return cross_sign(b - a, c - a) >= 0;
}
bool collinear(const point &a, const point &b, const point &c) {
  return cross_sign(b - a, c - a) == 0;
}
int64_t area_signed_2x(const point &a, const point &b, const point &c) {
  return cross(b - a, c - a);
}
dist_t distance_to_line(const point &p, const point &a, const point &b) {
  assert(a != b);
  return dist_t(abs(area_signed_2x(p, a, b))) / (a - b).dist();
}
int64_t manhattan_dist(const point &a, const point &b) {
  return (int64_t)abs(a.x - b.x) + abs(a.y - b.y);
}
int64_t infinity_norm_dist(const point &a, const point &b) {
  return max(abs(a.x - b.x), abs(a.y - b.y));
}
bool yx_compare(const point &a, const point &b) {
  return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}
bool angle_compare(const point &a, const point &b) {
  if (a.top_half() ^ b.top_half()) return a.top_half();
  return cross_sign(a, b) > 0;
}
template <const int &MOD>
struct _m_int {
  int val;
  _m_int(int64_t v = 0) {
    if (v < 0) v = v % MOD + MOD;
    if (v >= MOD) v %= MOD;
    val = int(v);
  }
  _m_int(uint64_t v) {
    if (v >= MOD) v %= MOD;
    val = int(v);
  }
  _m_int(int v) : _m_int(int64_t(v)) {}
  _m_int(unsigned v) : _m_int(uint64_t(v)) {}
  explicit operator int() const { return val; }
  explicit operator unsigned() const { return val; }
  explicit operator int64_t() const { return val; }
  explicit operator uint64_t() const { return val; }
  explicit operator double() const { return val; }
  explicit operator long double() const { return val; }
  _m_int &operator+=(const _m_int &other) {
    val -= MOD - other.val;
    if (val < 0) val += MOD;
    return *this;
  }
  _m_int &operator-=(const _m_int &other) {
    val -= other.val;
    if (val < 0) val += MOD;
    return *this;
  }
  static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
    return unsigned(x % m);
    unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
    unsigned quot, rem;
    asm("divl %4\n" : "=a"(quot), "=d"(rem) : "d"(x_high), "a"(x_low), "r"(m));
    return rem;
  }
  _m_int &operator*=(const _m_int &other) {
    val = fast_mod(uint64_t(val) * other.val);
    return *this;
  }
  _m_int &operator/=(const _m_int &other) { return *this *= other.inv(); }
  friend _m_int operator+(const _m_int &a, const _m_int &b) {
    return _m_int(a) += b;
  }
  friend _m_int operator-(const _m_int &a, const _m_int &b) {
    return _m_int(a) -= b;
  }
  friend _m_int operator*(const _m_int &a, const _m_int &b) {
    return _m_int(a) *= b;
  }
  friend _m_int operator/(const _m_int &a, const _m_int &b) {
    return _m_int(a) /= b;
  }
  _m_int &operator++() {
    val = val == MOD - 1 ? 0 : val + 1;
    return *this;
  }
  _m_int &operator--() {
    val = val == 0 ? MOD - 1 : val - 1;
    return *this;
  }
  _m_int operator++(int) {
    _m_int before = *this;
    ++*this;
    return before;
  }
  _m_int operator--(int) {
    _m_int before = *this;
    --*this;
    return before;
  }
  _m_int operator-() const { return val == 0 ? 0 : MOD - val; }
  friend bool operator==(const _m_int &a, const _m_int &b) {
    return a.val == b.val;
  }
  friend bool operator!=(const _m_int &a, const _m_int &b) {
    return a.val != b.val;
  }
  friend bool operator<(const _m_int &a, const _m_int &b) {
    return a.val < b.val;
  }
  friend bool operator>(const _m_int &a, const _m_int &b) {
    return a.val > b.val;
  }
  friend bool operator<=(const _m_int &a, const _m_int &b) {
    return a.val <= b.val;
  }
  friend bool operator>=(const _m_int &a, const _m_int &b) {
    return a.val >= b.val;
  }
  static const int SAVE_INV = int(1e6) + 5;
  static _m_int save_inv[SAVE_INV];
  static void prepare_inv() {
    for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1) assert(MOD % p != 0);
    save_inv[0] = 0;
    save_inv[1] = 1;
    for (int i = 2; i < SAVE_INV; i++)
      save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
  }
  _m_int inv() const {
    if (save_inv[1] == 0) prepare_inv();
    if (val < SAVE_INV) return save_inv[val];
    _m_int product = 1;
    int v = val;
    while (v >= SAVE_INV) {
      product *= MOD - MOD / v;
      v = MOD % v;
    }
    return product * save_inv[v];
  }
  _m_int pow(int64_t p) const {
    if (p < 0) return inv().pow(-p);
    _m_int a = *this, result = 1;
    while (p > 0) {
      if (p & 1) result *= a;
      p >>= 1;
      if (p > 0) a *= a;
    }
    return result;
  }
  friend ostream &operator<<(ostream &os, const _m_int &m) {
    return os << m.val;
  }
};
template <const int &MOD>
_m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];
const int MOD = 998244353;
const int mod = 1000000007;
using mod_int = _m_int<MOD>;
vector<mod_int> _factorial = {1, 1}, _inv_factorial = {1, 1};
void prepare_factorials(int64_t maximum) {
  static int64_t prepared_maximum = 1;
  if (maximum <= prepared_maximum) return;
  maximum += maximum / 64;
  _factorial.resize(maximum + 1);
  _inv_factorial.resize(maximum + 1);
  for (int64_t i = prepared_maximum + 1; i <= maximum; i++)
    _factorial[i] = i * _factorial[i - 1];
  _inv_factorial[maximum] = _factorial[maximum].inv();
  for (int64_t i = maximum - 1; i > prepared_maximum; i--)
    _inv_factorial[i] = (i + 1) * _inv_factorial[i + 1];
  prepared_maximum = maximum;
}
mod_int factorial(int64_t n) {
  if (n < 0) return 0;
  prepare_factorials(n);
  return _factorial[n];
}
mod_int inv_factorial(int64_t n) {
  if (n < 0) return 0;
  prepare_factorials(n);
  return _inv_factorial[n];
}
mod_int choose(int64_t n, int64_t r) {
  if (r < 0 || r > n) return 0;
  prepare_factorials(n);
  return _factorial[n] * _inv_factorial[r] * _inv_factorial[n - r];
}
mod_int permute(int64_t n, int64_t r) {
  if (r < 0 || r > n) return 0;
  prepare_factorials(n);
  return _factorial[n] * _inv_factorial[n - r];
}
mod_int inv_choose(int64_t n, int64_t r) {
  assert(0 <= r && r <= n);
  prepare_factorials(n);
  return _inv_factorial[n] * _factorial[r] * _factorial[n - r];
}
mod_int inv_permute(int64_t n, int64_t r) {
  assert(0 <= r && r <= n);
  prepare_factorials(n);
  return _inv_factorial[n] * _factorial[n - r];
}
void solve(int it) {
  long long w, h;
  cin >> w >> h;
  long long n;
  cin >> n;
  long long arrx0[n];
  for (long long i = 0; i < n; i++) {
    cin >> arrx0[i];
  }
  int m;
  cin >> m;
  long long arrx1[m];
  for (long long i = 0; i < m; i++) {
    cin >> arrx1[i];
  }
  int o;
  cin >> o;
  long long arry0[o];
  for (long long i = 0; i < o; i++) {
    cin >> arry0[i];
  }
  int p;
  cin >> p;
  long long arry1[p];
  for (long long i = 0; i < p; i++) {
    cin >> arry1[i];
  }
  cout << max(h * max(arrx0[n - 1] - arrx0[0], arrx1[m - 1] - arrx1[0]),
              w * max(arry0[o - 1] - arry0[0], arry1[p - 1] - arry1[0]))
       << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t;
  cin >> t;
  for (int it = 1; it <= t; it++) {
    solve(it);
  }
  cerr << "time taken : " << (float)clock() * 1000 / CLOCKS_PER_SEC << " ms"
       << endl;
  return 0;
}
