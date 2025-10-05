#include <bits/stdc++.h>
using namespace std;
int pct(int x) { return __builtin_popcount(x); }
int pct(long long x) { return __builtin_popcountll(x); }
int bit(int x) { return 31 - __builtin_clz(x); }
int bit(long long x) { return 63 - __builtin_clzll(x); }
int cdiv(int a, int b) { return a / b + !(a < 0 || a % b == 0); }
long long cdiv(long long a, long long b) {
  return a / b + !(a < 0 || a % b == 0);
}
template <typename T>
void leftShift(vector<T>& v, long long k) {
  k %= (int)v.size();
  if (k < 0) k += (int)v.size();
  rotate(v.begin(), v.begin() + k, v.end());
}
template <typename T>
void rightSift(vector<T>& v, long long k) {
  leftShift(v, (int)v.size() - k);
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rand(long long l, long long r) {
  uniform_int_distribution<long long> uid(l, r);
  return uid(rng);
}
inline int nxt() {
  int x;
  cin >> x;
  return x;
}
inline long long nxtll() {
  long long x;
  cin >> x;
  return x;
}
void pr() {}
void sc() {}
template <typename Head, typename... Tail>
void pr(Head H, Tail... T) {
  cout << H << " ";
  pr(T...);
}
template <typename Head, typename... Tail>
void sc(Head& H, Tail&... T) {
  cin >> H;
  sc(T...);
}
string to_string(__int128 x) {
  string s = "";
  bool neg = 0;
  if (x < 0) {
    s += "-";
    neg = 1;
  }
  if (!x) s += '0';
  while (x) {
    int rem = x % 10;
    s += to_string(rem);
    x /= 10;
  }
  reverse(s.begin() + neg, s.end());
  return s;
}
const int mod = 1e9 + 7;
int pwr(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = (ans * 1LL * a) % mod;
    a = (a * 1LL * a) % mod;
    b >>= 1;
  }
  return ans;
}
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a;
    swap(a, m);
    u -= t * v;
    swap(u, v);
  }
  assert(m == 1);
  return u;
}
template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod())
      v = static_cast<Type>(x);
    else
      v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const {
    return static_cast<U>(value);
  }
  constexpr static Type mod() { return T::value; }
  Modular& operator+=(const Modular& other) {
    if ((value += other.value) >= mod()) value -= mod();
    return *this;
  }
  Modular& operator-=(const Modular& other) {
    if ((value -= other.value) < 0) value += mod();
    return *this;
  }
  template <typename U>
  Modular& operator+=(const U& other) {
    return *this += Modular(other);
  }
  template <typename U>
  Modular& operator-=(const U& other) {
    return *this -= Modular(other);
  }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) {
    Modular result(*this);
    *this += 1;
    return result;
  }
  Modular operator--(int) {
    Modular result(*this);
    *this -= 1;
    return result;
  }
  Modular operator-() const { return Modular(-value); }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value,
                     Modular>::type&
  operator*=(const Modular& rhs) {
    value = normalize(static_cast<int64_t>(value) *
                      static_cast<int64_t>(rhs.value));
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value,
                     Modular>::type&
  operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) *
                                     rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value,
                     Modular>::type&
  operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }
  Modular& operator/=(const Modular& other) {
    return *this *= Modular(inverse(other.value, mod()));
  }
  template <typename U>
  friend const Modular<U>& abs(const Modular<U>& v) {
    return v;
  }
  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);

 private:
  Type value;
};
template <typename T>
bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) {
  return lhs.value == rhs.value;
}
template <typename T, typename U>
bool operator==(const Modular<T>& lhs, U rhs) {
  return lhs == Modular<T>(rhs);
}
template <typename T, typename U>
bool operator==(U lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) == rhs;
}
template <typename T>
bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) {
  return !(lhs == rhs);
}
template <typename T, typename U>
bool operator!=(const Modular<T>& lhs, U rhs) {
  return !(lhs == rhs);
}
template <typename T, typename U>
bool operator!=(U lhs, const Modular<T>& rhs) {
  return !(lhs == rhs);
}
template <typename T>
bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) {
  return lhs.value < rhs.value;
}
template <typename T>
Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(const Modular<T>& lhs, U rhs) {
  return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) += rhs;
}
template <typename T>
Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(const Modular<T>& lhs, U rhs) {
  return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) -= rhs;
}
template <typename T>
Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(const Modular<T>& lhs, U rhs) {
  return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) *= rhs;
}
template <typename T>
Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) /= rhs;
}
template <typename T, typename U>
Modular<T> operator/(const Modular<T>& lhs, U rhs) {
  return Modular<T>(lhs) /= rhs;
}
template <typename T, typename U>
Modular<T> operator/(U lhs, const Modular<T>& rhs) {
  return Modular<T>(lhs) /= rhs;
}
template <typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}
template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}
template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}
template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}
constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
const int N = 1005;
Mint dp[N][N][2][2][2];
void solve() {
  int n, k;
  cin >> n >> k;
  dp[1][0][0][0][1] = 1;
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 0; j <= i; j++) {
      for (int b1 = 0; b1 <= 1; b1++) {
        for (int b2 = 0; b2 <= 1; b2++) {
          for (int b3 = 0; b3 <= 1; b3++) {
            if (!dp[i][j][b1][b2][b3]) continue;
            Mint val = dp[i][j][b1][b2][b3];
            dp[i + 1][j][0][0][1] += val;
            if (!b3) dp[i + 1][j + 1 - b1][0][1][0] += val;
            if (!b3) dp[i + 1][j + 1 - b2][1][0][0] += val;
            if (b3) dp[i + 1][j + 2][1][1][0] += val;
            Mint rem = i - 2 + b3;
            Mint good_pairs = j - b1 - b2;
            dp[i + 1][j - 1][0][0][0] += good_pairs * val;
            dp[i + 1][j][0][0][0] += (rem - good_pairs) * val;
          }
        }
      }
    }
  }
  Mint ans = 0;
  for (int b1 = 0; b1 <= 1; b1++) {
    for (int b2 = 0; b2 <= 1; b2++) {
      for (int b3 = 0; b3 <= 1; b3++) {
        ans += dp[n][k][b1][b2][b3];
      }
    }
  }
  cout << ans;
}
signed main() {
  ios ::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  t = 1;
  for (int tt = 1; tt <= t; tt++) {
    solve();
  }
  return 0;
}
