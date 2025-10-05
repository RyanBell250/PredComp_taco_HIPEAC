#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
namespace {
template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::deque<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::set<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::stack<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::queue<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::priority_queue<T> &);
template <typename T>
std::ostream &operator<<(std::ostream &, const std::unordered_set<T> &);
template <typename T, typename U>
std::ostream &operator<<(std::ostream &, const std::map<T, U> &);
template <typename T, typename U>
std::ostream &operator<<(std::ostream &, const std::unordered_map<T, U> &);
template <typename T, typename U>
std::ostream &operator<<(std::ostream &, const std::pair<T, U> &);
template <typename... T>
std::ostream &operator<<(std::ostream &, const std::tuple<T...> &);
template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &, const std::array<T, N> &);
template <typename Tuple, std::size_t N>
struct __TuplePrinter__ {
  static void print(std::ostream &os, const Tuple &t) {
    __TuplePrinter__<Tuple, N - 1>::print(os, t);
    os << ", " << std::get<N - 1>(t);
  }
};
template <typename Tuple>
struct __TuplePrinter__<Tuple, 1> {
  static void print(std::ostream &os, const Tuple &t) { os << std::get<0>(t); }
};
template <typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &t) {
  os << '(';
  __TuplePrinter__<decltype(t), sizeof...(T)>::print(os, t);
  os << ')';
  return os;
}
template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::stack<T> &c) {
  std::deque<T> v;
  for (auto d = c; !d.empty(); d.pop()) v.push_front(d.top());
  return os << v;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::queue<T> &c) {
  std::deque<T> v;
  for (auto d = c; !d.empty(); d.pop()) v.push_back(d.front());
  return os << v;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::priority_queue<T> &c) {
  std::deque<T> v;
  for (auto d = c; !d.empty(); d.pop()) v.push_front(d.top());
  return os << v;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::map<T, U> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<T, U> &c) {
  os << '[';
  for (auto it = begin(c); it != end(c);) {
    os << *it;
    os << (++it != end(c) ? ", " : "");
  }
  return os << ']';
}
}  
inline long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
inline long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
template <signed M, unsigned T>
struct mod_int {
  constexpr static signed MODULO = M;
  constexpr static unsigned TABLE_SIZE = T;
  signed x;
  mod_int() : x(0) {}
  mod_int(long long y)
      : x(static_cast<signed>(y >= 0 ? y % MODULO : MODULO - (-y) % MODULO)) {}
  mod_int(int y) : x(y >= 0 ? y % MODULO : MODULO - (-y) % MODULO) {}
  mod_int &operator+=(const mod_int &rhs) {
    if ((x += rhs.x) >= MODULO) x -= MODULO;
    return *this;
  }
  mod_int &operator-=(const mod_int &rhs) {
    if ((x += MODULO - rhs.x) >= MODULO) x -= MODULO;
    return *this;
  }
  mod_int &operator*=(const mod_int &rhs) {
    x = static_cast<signed>(1LL * x * rhs.x % MODULO);
    return *this;
  }
  mod_int &operator/=(const mod_int &rhs) {
    x = static_cast<signed>((1LL * x * rhs.inv().x) % MODULO);
    return *this;
  }
  mod_int operator-() const { return mod_int(-x); }
  mod_int operator+(const mod_int &rhs) const { return mod_int(*this) += rhs; }
  mod_int operator-(const mod_int &rhs) const { return mod_int(*this) -= rhs; }
  mod_int operator*(const mod_int &rhs) const { return mod_int(*this) *= rhs; }
  mod_int operator/(const mod_int &rhs) const { return mod_int(*this) /= rhs; }
  bool operator<(const mod_int &rhs) const { return x < rhs.x; }
  mod_int inv() const {
    assert(x != 0);
    if (x <= static_cast<signed>(TABLE_SIZE)) {
      if (_inv[1].x == 0) prepare();
      return _inv[x];
    } else {
      signed a = x, b = MODULO, u = 1, v = 0, t;
      while (b) {
        t = a / b;
        a -= t * b;
        std::swap(a, b);
        u -= t * v;
        std::swap(u, v);
      }
      return mod_int(u);
    }
  }
  mod_int pow(long long t) const {
    assert(!(x == 0 && t == 0));
    mod_int e = *this, res = mod_int(1);
    for (; t; e *= e, t >>= 1)
      if (t & 1) res *= e;
    return res;
  }
  mod_int fact() {
    if (_fact[0].x == 0) prepare();
    return _fact[x];
  }
  mod_int inv_fact() {
    if (_fact[0].x == 0) prepare();
    return _inv_fact[x];
  }
  mod_int choose(mod_int y) {
    assert(y.x <= x);
    return this->fact() * y.inv_fact() * mod_int(x - y.x).inv_fact();
  }
  static mod_int _inv[TABLE_SIZE + 1];
  static mod_int _fact[TABLE_SIZE + 1];
  static mod_int _inv_fact[TABLE_SIZE + 1];
  static void prepare() {
    _inv[1] = 1;
    for (int i = 2; i <= (int)TABLE_SIZE; ++i) {
      _inv[i] = 1LL * _inv[MODULO % i].x * (MODULO - MODULO / i) % MODULO;
    }
    _fact[0] = 1;
    for (unsigned i = 1; i <= TABLE_SIZE; ++i) {
      _fact[i] = _fact[i - 1] * int(i);
    }
    _inv_fact[TABLE_SIZE] = _fact[TABLE_SIZE].inv();
    for (int i = (int)TABLE_SIZE - 1; i >= 0; --i) {
      _inv_fact[i] = _inv_fact[i + 1] * (i + 1);
    }
  }
};
template <int M, unsigned F>
std::ostream &operator<<(std::ostream &os, const mod_int<M, F> &rhs) {
  return os << rhs.x;
}
template <int M, unsigned F>
std::istream &operator>>(std::istream &is, mod_int<M, F> &rhs) {
  long long s;
  is >> s;
  rhs = mod_int<M, F>(s);
  return is;
}
template <int M, unsigned F>
mod_int<M, F> mod_int<M, F>::_inv[TABLE_SIZE + 1];
template <int M, unsigned F>
mod_int<M, F> mod_int<M, F>::_fact[TABLE_SIZE + 1];
template <int M, unsigned F>
mod_int<M, F> mod_int<M, F>::_inv_fact[TABLE_SIZE + 1];
template <int M, unsigned F>
bool operator==(const mod_int<M, F> &lhs, const mod_int<M, F> &rhs) {
  return lhs.x == rhs.x;
}
template <int M, unsigned F>
bool operator!=(const mod_int<M, F> &lhs, const mod_int<M, F> &rhs) {
  return !(lhs == rhs);
}
const int MF = 1000010;
const int MOD = 1000000007;
using mint = mod_int<MOD, MF>;
mint binom(int n, int r) {
  return (r < 0 || r > n || n < 0) ? 0 : mint(n).choose(r);
}
mint fact(int n) { return mint(n).fact(); }
mint inv_fact(int n) { return mint(n).inv_fact(); }
const long long mod = 1000000007;
signed main() {
  long long n;
  cin >> n;
  map<pair<long long, long long>, long long> m;
  long long maxix = 156848486515;
  long long minix = -156848486515;
  long long maxi = 0;
  long long mini = 0;
  long long nowx = 0, nowy = 0, bef = -1;
  long long base;
  long long dx = 1;
  for (long long i = 0; i < n; i++) {
    long long a;
    cin >> a;
    if (i == 0) {
      bef = a;
      base = a;
      m[{nowx, nowy}] = a;
    } else {
      if (a == bef) {
        cout << "NO" << endl;
        return 0;
      }
      if (a - bef == 1) {
        nowx++;
      } else if (bef - a == 1)
        nowx--;
      else if (bef > a) {
        if (dx == 1) {
          dx = abs(bef - a);
          maxix = dx - (base - 1) % dx - 1;
          minix = 1 - (base - 1) % dx - 1;
        }
        nowy--;
        if (bef - a != dx) {
          cout << "NO" << endl;
          return 0;
        }
      } else if (bef < a) {
        if (dx == 1) {
          dx = abs(a - bef);
          maxix = dx - (base - 1) % dx - 1;
          minix = 1 - (base - 1) % dx - 1;
        }
        nowy++;
        if (a - bef != dx) {
          cout << "NO" << endl;
          return 0;
        }
      }
      bef = a;
      if (m.find({nowx, nowy}) != m.end()) {
        if (m[{nowx, nowy}] != a) {
          cout << "NO" << endl;
          return 0;
        }
      } else {
        m[{nowx, nowy}] = a;
      }
    }
    maxi = max(maxi, nowx);
    mini = min(mini, nowx);
  }
  if (maxi > maxix || mini < minix) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;
  cout << 1000000000 << " " << dx << endl;
}
