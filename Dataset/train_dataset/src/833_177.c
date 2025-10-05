#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
namespace input {
template <class T>
inline void _R(T& x) {
  cin >> x;
}
inline void R() {}
template <class T1, class... T2>
inline void R(T1& x, T2&... y) {
  _R(x);
  R(y...);
}
}  // namespace input
using namespace input;
namespace overload_output {
template <class T1, class T2>
inline ostream& operator<<(ostream& out, pair<T1, T2>& p) {
  return out << p.first << ' ' << p.second;
}
template <class T>
inline ostream& operator<<(ostream& out, vector<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, deque<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, forward_list<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, list<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, set<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, multiset<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, unordered_set<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T>
inline ostream& operator<<(ostream& out, unordered_multiset<T>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T1, class T2>
inline ostream& operator<<(ostream& out, map<T1, T2>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T1, class T2>
inline ostream& operator<<(ostream& out, multimap<T1, T2>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T1, class T2>
inline ostream& operator<<(ostream& out, unordered_map<T1, T2>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
template <class T1, class T2>
inline ostream& operator<<(ostream& out, unordered_multimap<T1, T2>& x) {
  for (auto i : x) out << i << ' ';
  return out;
}
}  // namespace overload_output
using namespace overload_output;
namespace output {
template <class T>
inline void _W(const T& x) {
  cout << x;
}
template <class T1, class T2>
inline void _W(const pair<T1, T2>& p) {
  _W(p.first);
  _W(' ');
  _W(p.second);
}
template <class T>
inline void _W(const vector<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const deque<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const forward_list<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const list<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const set<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const multiset<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const unordered_set<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T>
inline void _W(const unordered_multiset<T>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T1, class T2>
inline void _W(const map<T1, T2>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T1, class T2>
inline void _W(const multimap<T1, T2>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T1, class T2>
inline void _W(const unordered_map<T1, T2>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
template <class T1, class T2>
inline void _W(const unordered_multimap<T1, T2>& x) {
  bool isFirst = 1;
  for (auto i : x) {
    if (!isFirst) cout << ' ';
    isFirst = 0;
    cout << i;
  }
}
inline void W() { cout << '\n'; }
template <class T>
inline void W(const T& x) {
  _W(x);
  W();
}
template <class T1, class... T2>
inline void W(const T1& x, const T2&... y) {
  _W(x);
  _W(' ');
  W(y...);
}
}  // namespace output
using namespace output;
int main() {
  int n, k;
  R(n, k);
  if ((n - 1) / 2 >= k) {
    W(n * k);
    for (int i = 1; i <= n; i++)
      for (int j = i % n + 1, cnt = 0; cnt < k; j %= n, j++, cnt++) W(i, j);
  } else {
    W(-1);
  }
  return 0;
}
static auto _batch_ios = []() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(12);
  return 42;
}();
