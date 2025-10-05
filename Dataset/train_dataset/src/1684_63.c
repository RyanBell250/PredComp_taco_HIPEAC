#include <bits/stdc++.h>
using namespace std;
const long double pi = 3.1415926535897932384626433832795l;
template <typename T>
inline auto sqr(T x) -> decltype(x * x) {
  return x * x;
}
template <typename T1, typename T2>
inline bool umx(T1 &a, T2 b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <typename T1, typename T2>
inline bool umn(T1 &a, T2 b) {
  if (b < a) {
    a = b;
    return 1;
  }
  return 0;
}
struct Input {
  int n, m;
  vector<int> a, b, d;
  bool read() {
    if (!(cin >> n >> m)) return 0;
    a.resize(m);
    d = b = a;
    for (int i = int(0); i < int(m); ++i) {
      cin >> a[i] >> b[i] >> d[i];
      --a[i], --b[i];
    }
    return 1;
  }
  void init(const Input &input) { *this = input; }
};
struct Data : Input {
  int ans;
  void write() {
    if (ans == -1) {
      cout << "Impossible" << '\n';
    } else {
      cout << ans << '\n';
    }
  }
};
const int BASE = 64;
const int MAXN = 150;
const int MAXK = 30;
struct Matrix {
  uint64_t arr[MAXN][3];
  Matrix() { memset(arr, 0, sizeof(arr)); }
  Matrix(const Matrix &lhs) { memcpy(arr, lhs.arr, sizeof(arr)); }
  void clear() { memset(arr, 0, sizeof(arr)); }
  int get(int i, int j) const { return (arr[i][j / BASE] >> (j % BASE)) & 1; }
  void set(int i, int j) { arr[i][j / BASE] |= (1ull << (j % BASE)); }
};
void transpose(const Matrix &tmp, Matrix &v) {
  v.clear();
  for (int i = int(0); i < int(MAXN); ++i) {
    for (int j = int(0); j < int(MAXN); ++j) {
      if (tmp.get(i, j)) {
        v.set(j, i);
      }
    }
  }
}
struct Vector {
  int arr[MAXN];
  Vector() { memset(arr, 0, sizeof(arr)); }
  Vector(const Vector &lhs) { memcpy(arr, lhs.arr, sizeof(arr)); }
  void clear() { memset(arr, 0, sizeof(arr)); }
};
struct Solution : Data {
  Matrix edges[MAXK][MAXN + 1];
  Matrix wedges[MAXK][MAXN + 1];
  void mult(const Matrix &a, const Matrix &b, Matrix &res) {
    Matrix tp;
    transpose(b, tp);
    res.clear();
    for (int i = int(0); i < int(MAXN); ++i) {
      for (int j = int(0); j < int(MAXN); ++j) {
        if ((a.arr[i][0] & tp.arr[j][0]) | (a.arr[i][1] & tp.arr[j][1]) |
            (a.arr[i][2] & tp.arr[j][2])) {
          res.set(i, j);
        }
      }
    }
  }
  void mult(const Matrix &a, Vector &b, Vector &c) {
    c.clear();
    for (int i = int(0); i < int(n); ++i) {
      c.arr[i] = 0;
      for (int j = 0; j < n && !(c.arr[i]); ++j) {
        c.arr[i] = b.arr[j] && a.get(j, i);
      }
    }
  }
  void propagate(const Vector &from, int id, int diff, Vector &to,
                 bool sparse) {
    to = from;
    for (int it = int(0); it < int(MAXK); ++it) {
      if (diff & (1 << it)) {
        Vector tmp = to;
        if (sparse) {
          mult(edges[it][id], tmp, to);
        } else {
          mult(wedges[it][id], tmp, to);
        }
      }
    }
  }
  void solve() {
    ans = -1;
    vector<tuple<int, int, int> > ev;
    vector<int> un = {0};
    for (int i = int(0); i < int(m); ++i) {
      un.push_back(d[i]);
      ev.push_back(make_tuple(d[i], a[i], b[i]));
    }
    sort((ev).begin(), (ev).end());
    sort((un).begin(), (un).end());
    un.push_back(un.back() + n + 1);
    un.erase(unique((un).begin(), (un).end()), un.end());
    ;
    int cnt = ((int)(un).size());
    for (int i = int(0); i < int(cnt - 1); ++i) {
      for (int j = int(0); j < int(n); ++j) {
        wedges[0][i].set(j, j);
      }
      for (int j = int(0); j < int(m); ++j) {
        int aa, bb, dd;
        tie(dd, aa, bb) = ev[j];
        if (dd <= un[i]) {
          edges[0][i].set(aa, bb);
          wedges[0][i].set(aa, bb);
        }
      }
    }
    for (int it = int(1); it < int(MAXK); ++it) {
      for (int i = int(0); i < int(cnt - 1); ++i) {
        if ((1 << it) <= (un[i + 1] - un[i])) {
          mult(edges[it - 1][i], edges[it - 1][i], edges[it][i]);
          mult(wedges[it - 1][i], wedges[it - 1][i], wedges[it][i]);
        }
      }
    }
    Vector sm;
    sm.arr[0] = 1;
    for (int i = int(1); i < int(cnt); ++i) {
      int diff = un[i] - un[i - 1];
      Vector tp = sm;
      propagate(sm, i - 1, diff, tp, false);
      if (!tp.arr[n - 1]) {
        tp = sm;
        propagate(tp, i - 1, diff, sm, true);
        continue;
      }
      int l = 0, r = diff + 1;
      while (l < r - 1) {
        int mid = (l + r) / 2;
        Vector tp;
        propagate(sm, i - 1, mid, tp, false);
        if (!tp.arr[n - 1]) {
          l = mid;
        } else {
          r = mid;
        }
      }
      ans = un[i - 1] + r;
      break;
    }
  }
  void clear() { *this = Solution(); }
};
Solution sol;
int main() {
  cout.setf(ios::showpoint | ios::fixed);
  cout.precision(20);
  sol.read();
  sol.solve();
  sol.write();
  return 0;
}
