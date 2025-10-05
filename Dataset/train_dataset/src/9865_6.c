#include <bits/stdc++.h>
#pragma comment(linker, "/stack:16777216")
namespace Template {
using namespace std;
struct debugger {
  template <typename T>
  debugger &operator,(const T &v) {
    cerr << v << " ";
    return *this;
  }
} dbg;
template <typename T>
void sci(T &t) {
  cin >> t;
}
template <typename T, typename... Ts>
void sci(T &t, Ts &...ts) {
  cin >> t;
  sci(ts...);
}
template <typename T>
inline T gcd(T a, T b) {
  T c;
  while (b) {
    c = b;
    b = a % b;
    a = c;
  }
  return a;
}
template <typename T, typename S>
ostream &operator<<(ostream &os, const pair<T, S> &v) {
  os << "(";
  os << v.first << "," << v.second << ")";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "[";
  int sz = v.size();
  for (int i = 0; i < sz; ++i) {
    os << v[i];
    if (i != sz - 1) os << ",";
  }
  os << "]\n";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) {
  T last = *v.rbegin();
  os << "[";
  for (auto it : v) {
    os << it;
    if (it != last) os << ",";
  }
  os << "]\n";
  return os;
}
template <typename T, typename S>
ostream &operator<<(ostream &os, const map<T, S> &v) {
  for (auto it : v) {
    os << it.first << " : " << it.second << " , ";
  }
  return os;
}
struct _runCode {
  clock_t time;
  int m;
  _runCode(int mode) {
    m = mode;
    if (mode == -1)
      freopen(
          "C:\\Users\\Praveen\\documents\\Visual Studio "
          "2017\\Projects\\comp\\in.txt",
          "w", stdout);
    if (mode >= 1)
      freopen(
          "C:\\Users\\Praveen\\documents\\Visual Studio "
          "2017\\Projects\\comp\\in.txt",
          "r", stdin);
    if (mode == 2)
      freopen(
          "C:\\Users\\Praveen\\documents\\Visual Studio "
          "2017\\Projects\\comp\\out.txt",
          "w", stdout);
    time = clock();
  }
  ~_runCode() {
    cerr << "\nTime: " << ((float)(clock() - time) / CLOCKS_PER_SEC) << '\n';
    if (m == -1 || m == 1) fcloseall();
  }
};
};  
using namespace Template;
bool comp(pair<int, int> i, pair<int, int> j) { return i.second < j.second; }
void solve() {
  long long n, m;
  sci(n, m);
  if (m >= n) {
    cout << n << '\n';
    return;
  }
  long long ans = m + 1;
  long long lans = 0;
  int j = 0;
  long long l = 0LL, r = 1LL << 31;
  while (l < r) {
    long long mid = (l + r) >> 1;
    if (m + ((mid * (mid + 1)) >> 1) < n)
      l = mid + 1;
    else
      r = mid;
  }
  cout << m + l;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ;
  ;
  solve();
  return 0;
}
