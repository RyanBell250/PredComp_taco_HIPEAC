#include <bits/stdc++.h>
template <typename T>
void MACRO_VAR_Scan(T& t) {
  std::cin >> t;
}
template <typename First, typename... Rest>
void MACRO_VAR_Scan(First& first, Rest&... rest) {
  std::cin >> first;
  MACRO_VAR_Scan(rest...);
}
template <typename T>
void MACRO_VEC_ROW_Init(int n, T& t) {
  t.resize(n);
}
template <typename First, typename... Rest>
void MACRO_VEC_ROW_Init(int n, First& first, Rest&... rest) {
  first.resize(n);
  MACRO_VEC_ROW_Init(n, rest...);
}
template <typename T>
void MACRO_VEC_ROW_Scan(int p, T& t) {
  std::cin >> t[p];
}
template <typename First, typename... Rest>
void MACRO_VEC_ROW_Scan(int p, First& first, Rest&... rest) {
  std::cin >> first[p];
  MACRO_VEC_ROW_Scan(p, rest...);
}
template <typename T>
inline T CHMAX(T& a, const T b) {
  return a = (a < b) ? b : a;
}
template <typename T>
inline T CHMIN(T& a, const T b) {
  return a = (a > b) ? b : a;
}
void CHECKTIME(std::function<void()> f) {
  auto start = std::chrono::system_clock::now();
  f();
  auto end = std::chrono::system_clock::now();
  auto res = std::chrono::duration_cast<std::chrono::nanoseconds>((end - start))
                 .count();
  std::cerr << "[Time:" << res << "ns  (" << res / (1.0e9) << "s)]\n";
}
template <class T>
std::vector<std::vector<T>> VV(int n, int m, T init = T()) {
  return std::vector<std::vector<T>>(n, std::vector<T>(m, init));
}
template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S, T> p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using PAIR = std::pair<int, int>;
using PAIRLL = std::pair<ll, ll>;
constexpr int INFINT = 1 << 30;
constexpr int INFINT_LIM = (1LL << 31) - 1;
constexpr ll INFLL = 1LL << 60;
constexpr ll INFLL_LIM = (1LL << 62) - 1 + (1LL << 62);
constexpr double EPS = 1e-9;
constexpr int MOD = 1000000007;
constexpr double PI = 3.141592653589793238462643383279;
template <class T, size_t N>
void FILL(T (&a)[N], const T& val) {
  for (auto& x : a) x = val;
}
template <class ARY, size_t N, size_t M, class T>
void FILL(ARY (&a)[N][M], const T& val) {
  for (auto& b : a) FILL(b, val);
}
template <class T>
void FILL(std::vector<T>& a, const T& val) {
  for (auto& x : a) x = val;
}
template <class ARY, class T>
void FILL(std::vector<std::vector<ARY>>& a, const T& val) {
  for (auto& b : a) FILL(b, val);
}
int dp[2003][9][720];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  ;
  std::map<std::multiset<int>, int> map;
  std::vector<std::multiset<int>> inv;
  std::vector<int> cntmap;
  std::multiset<int> base;
  map[base];
  for (int i = 0; i < int(9); ++i) {
    auto t1(base);
    t1.insert(i);
    map[t1];
    for (int j = 0; j < int(9); ++j) {
      auto t2(t1);
      t2.insert(j);
      map[t2];
      for (int k = 0; k < int(9); ++k) {
        auto t3(t2);
        t3.insert(k);
        map[t3];
        for (int l = 0; l < int(9); ++l) {
          auto t4(t3);
          t4.insert(l);
          map[t4];
        }
      }
    }
  }
  inv.resize(map.size());
  cntmap.resize(map.size());
  int sz = 0;
  for (auto& x : map) {
    x.second = sz;
    inv[sz] = x.first;
    cntmap[sz] = x.first.size();
    ++sz;
  }
  int n;
  MACRO_VAR_Scan(n);
  ;
  std::vector<int> a, b;
  MACRO_VEC_ROW_Init(n, a, b);
  for (int i = 0; i < n; ++i) {
    MACRO_VEC_ROW_Scan(i, a, b);
  };
  for (int i = 0; i < int(n); ++i) --a[i], --b[i];
  FILL(dp, INFINT);
  dp[0][0][0] = 0;
  struct D {
    int i, j, k, d;
  };
  std::queue<D> que;
  que.push(D{0, 0, 0, 0});
  while (!que.empty()) {
    D now = que.front();
    que.pop();
    int &i = now.i, &j = now.j, &k = now.k;
    if (dp[i][j][k] < now.d) continue;
    {
      if (i < n && a[i] == j && cntmap[k] < 4) {
        auto mset = inv[k];
        mset.insert(b[i]);
        int kk = map[mset];
        if (dp[i + 1][j][kk] > dp[i][j][k] + 1) {
          dp[i + 1][j][kk] = dp[i][j][k] + 1;
          que.push(D{i + 1, j, kk, dp[i + 1][j][kk]});
        }
      }
    }
    {
      auto mset = inv[k];
      auto it = mset.find(j);
      if (it != mset.end()) {
        mset.erase(it);
        int kk = map[mset];
        if (dp[i][j][kk] > dp[i][j][k] + 1) {
          dp[i][j][kk] = dp[i][j][k] + 1;
          que.push(D{i, j, kk, dp[i][j][kk]});
        }
      }
    }
    {
      if (j + 1 < 9) {
        if (dp[i][j + 1][k] > dp[i][j][k] + 1) {
          dp[i][j + 1][k] = dp[i][j][k] + 1;
          que.push(D{i, j + 1, k, dp[i][j + 1][k]});
        }
      }
    }
    {
      if (j - 1 >= 0) {
        if (dp[i][j - 1][k] > dp[i][j][k] + 1) {
          dp[i][j - 1][k] = dp[i][j][k] + 1;
          que.push(D{i, j - 1, k, dp[i][j - 1][k]});
        }
      }
    }
  }
  int ans = INFINT;
  for (int i = 0; i < int(9); ++i) CHMIN(ans, dp[n][i][0]);
  std::cout << (ans);
  std::cout << "\n";
  ;
  return 0;
}
