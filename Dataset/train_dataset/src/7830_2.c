#include <bits/stdc++.h>
using namespace std;
template <class T>
bool umin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}
template <class T>
bool umax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}
template <long long sz>
using tut = array<long long, sz>;
void usaco(string s) {
  freopen((s + ".in").c_str(), "r", stdin);
  freopen((s + ".out").c_str(), "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
const long long N = 2e5 + 5;
const long long mod = (119 << 23) + 1;
const long long inf = 1e18;
const double Pi = acos(-1);
const double eps = 1e-13;
void add(long long& a, long long b, long long mod = ::mod) {
  a = (a + b) % mod;
}
void sub(long long& a, long long b, long long mod = ::mod) {
  a = ((a - b) % mod + mod) % mod;
}
void mul(long long& a, long long b, long long mod = ::mod) {
  a = (a * 1ll * b) % mod;
}
long long n, m, k, t, q, ans, res, a[N];
long long b[N];
void solve(long long t_case) {
  cin >> n;
  for (long long i = 1; i <= n; i++) cin >> a[i];
  for (long long i = 1; i <= n; i++) cin >> b[i];
  if (n == 1) {
    if (a[1] == b[1])
      cout << "SMALL\n" << 0 << "\n";
    else
      cout << "IMPOSSIBLE\n";
    return;
  }
  auto inc = [&]() -> bool {
    for (long long i = 2; i <= n; i++) {
      if (b[i] <= b[i - 1]) return 0;
    }
    return 1;
  };
  if (n == 2) {
    long long cc = 0, ssc = 0;
    string second;
    auto check = [&]() {
      bool ok = 0;
      if (a[1] > a[2]) ok = 1, swap(a[1], a[2]);
      if (b[1] < a[1]) {
        cout << "IMPOSSIBLE\n";
        exit(0);
      }
      if (b[1] == a[1]) {
        if ((b[2] - a[2]) % b[1] == 0) {
          long long cnt = (b[2] - a[2]) / b[1];
          cc += cnt;
          while (cnt-- && ssc <= 2e5) ssc++, second.push_back('P');
          if (ok) second.push_back('R');
          reverse(second.begin(), second.end());
          if (cc <= 2e5) {
            cout << "SMALL\n"
                 << (long long)second.size() << "\n"
                 << second << "\n";
            exit(0);
          } else {
            cout << "BIG\n" << cc << "\n";
            exit(0);
          }
        } else {
          cout << "IMPOSSIBLE\n";
          exit(0);
        }
      }
      if (ok) swap(a[1], a[2]);
    };
    while (1) {
      check();
      reverse(b + 1, b + n + 1), second.push_back('R');
      check();
      if (inc()) {
        long long cnt = b[2] / b[1];
        cc += cnt;
        while (cnt-- && ssc <= 2e5) ssc++, second.push_back('P');
        b[2] = (b[2] % b[1]);
      } else {
        reverse(b + 1, b + n + 1), second.pop_back();
        if (inc()) {
          long long cnt = b[2] / b[1];
          cc += cnt;
          while (cnt-- && ssc <= 2e5) ssc++, second.push_back('P');
          b[2] = (b[2] % b[1]);
        } else {
          cout << "IMPOSSIBLE\n";
          return;
        }
      }
    }
  }
  long long cc = 0;
  string second;
  auto check = [&]() {
    for (long long i = 1; i <= n; i++) {
      if (a[i] != b[i]) return;
    }
    reverse(second.begin(), second.end());
    if (cc <= 2e5) {
      cout << "SMALL\n" << (long long)second.size() << "\n" << second << "\n";
      exit(0);
    } else {
      cout << "BIG\n" << cc << "\n";
      exit(0);
    }
  };
  while (1) {
    check();
    reverse(b + 1, b + n + 1), second.push_back('R');
    check();
    if (inc()) {
      cc++, second.push_back('P');
      for (long long i = n; i > 1; i--) {
        b[i] = b[i] - b[i - 1];
      }
    } else {
      reverse(b + 1, b + n + 1), second.pop_back();
      if (inc()) {
        cc++, second.push_back('P');
        for (long long i = n; i > 1; i--) {
          b[i] = b[i] - b[i - 1];
        }
      } else {
        cout << "IMPOSSIBLE\n";
        return;
      }
    }
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  if (0) {
    long long t;
    cin >> t;
    for (long long t_case = 1; t_case <= t; t_case++) solve(t_case);
  } else
    solve(1);
  return 0;
}
