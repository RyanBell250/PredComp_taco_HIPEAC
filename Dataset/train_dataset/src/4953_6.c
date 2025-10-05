#include <bits/stdc++.h>
using namespace std;
template <typename T, typename U>
std::istream& operator>>(std::istream& i, pair<T, U>& p) {
  i >> p.first >> p.second;
  return i;
}
template <typename T>
std::istream& operator>>(std::istream& i, vector<T>& t) {
  for (auto& v : t) {
    i >> v;
  }
  return i;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& o, const pair<T, U>& p) {
  o << p.first << ' ' << p.second;
  return o;
}
template <typename T>
std::ostream& operator<<(std::ostream& o, const vector<T>& t) {
  if (t.empty()) o << '\n';
  for (size_t i = 0; i < t.size(); ++i) {
    o << t[i] << " \n"[i == t.size() - 1];
  }
  return o;
}
template <typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxheap = priority_queue<T, vector<T>, less<T>>;
template <typename T>
bool in(T a, T b, T c) {
  return a <= b && b < c;
}
unsigned int logceil(int first) {
  return first ? 8 * sizeof(int) - __builtin_clz(first) : 0;
}
namespace std {
template <typename T, typename U>
struct hash<pair<T, U>> {
  hash<T> t;
  hash<U> u;
  size_t operator()(const pair<T, U>& p) const {
    return t(p.first) ^ (u(p.second) << 7);
  }
};
}  
template <typename T, typename F>
T bsh(T l, T h, const F& f) {
  T r = -1, m;
  while (l <= h) {
    m = (l + h) / 2;
    if (f(m)) {
      l = m + 1;
      r = m;
    } else {
      h = m - 1;
    }
  }
  return r;
}
template <typename F>
double bshd(double l, double h, const F& f, double p = 1e-9) {
  unsigned int r = 3 + (unsigned int)log2((h - l) / p);
  while (r--) {
    double m = (l + h) / 2;
    if (f(m)) {
      l = m;
    } else {
      h = m;
    }
  }
  return (l + h) / 2;
}
template <typename T, typename F>
T bsl(T l, T h, const F& f) {
  T r = -1, m;
  while (l <= h) {
    m = (l + h) / 2;
    if (f(m)) {
      h = m - 1;
      r = m;
    } else {
      l = m + 1;
    }
  }
  return r;
}
template <typename F>
double bsld(double l, double h, const F& f, double p = 1e-9) {
  unsigned int r = 3 + (unsigned int)log2((h - l) / p);
  while (r--) {
    double m = (l + h) / 2;
    if (f(m)) {
      h = m;
    } else {
      l = m;
    }
  }
  return (l + h) / 2;
}
template <typename T>
T gcd(T a, T b) {
  if (a < b) swap(a, b);
  return b ? gcd(b, a % b) : a;
}
template <typename T>
class vector2 : public vector<vector<T>> {
 public:
  vector2() {}
  vector2(size_t a, size_t b, T t = T())
      : vector<vector<T>>(a, vector<T>(b, t)) {}
};
template <typename T>
class vector3 : public vector<vector2<T>> {
 public:
  vector3() {}
  vector3(size_t a, size_t b, size_t c, T t = T())
      : vector<vector2<T>>(a, vector2<T>(b, c, t)) {}
};
template <typename T>
class vector4 : public vector<vector3<T>> {
 public:
  vector4() {}
  vector4(size_t a, size_t b, size_t c, size_t d, T t = T())
      : vector<vector3<T>>(a, vector3<T>(b, c, d, t)) {}
};
template <typename T>
class vector5 : public vector<vector4<T>> {
 public:
  vector5() {}
  vector5(size_t a, size_t b, size_t c, size_t d, size_t e, T t = T())
      : vector<vector4<T>>(a, vector4<T>(b, c, d, e, t)) {}
};
class TaskD {
 public:
  vector<int> P;
  void fact(int a, vector<int>& f) {
    while (a != 1) {
      int b = P[a], c = 0;
      while (P[a] == b) {
        c++;
        a /= b;
      }
      f.push_back(c + 1);
    }
    sort(f.begin(), f.end());
    reverse(f.begin(), f.end());
    while (f.size() < Prm.size()) f.push_back(1);
  }
  vector<vector<int>> HH;
  vector<int> Used, CNT;
  map<vector<int>, int> J;
  void genAll(int p, int m, int c, int d, vector<int>& first) {
    if (p == Prm.size()) {
      HH.push_back(first);
      CNT.push_back(d);
      int second = J.size();
      if (c <= 1e6) Used.push_back(second);
      J[first] = second;
    } else {
      first[p] = 1;
      genAll(p + 1, 1, c, d * first[p], first);
      while (true) {
        first[p]++;
        c *= Prm[p];
        if (c > 55050240) return;
        if (first[p] > m) return;
        genAll(p + 1, first[p], c, d * first[p], first);
      }
    }
  }
  vector<int> Prm;
  void solve(istream& cin, ostream& cout) {
    Prm = {2, 3, 5, 7, 11, 13, 17};
    P.assign(1e6 + 5, 0);
    for (int i = 2; i < 1e6 + 3; ++i) {
      if (P[i] == 0) {
        for (int j = i; j < 1e6 + 3; j += i) P[j] = i;
      }
    }
    vector<int> X(Prm.size());
    Used.reserve(289);
    CNT.reserve(706);
    genAll(0, 30, 1, 1, X);
    int N = J.size();
    vector2<int> D(N, N);
    vector2<int> E(N, 673, 100);
    set<int> Q;
    for (int i = 0; i < N; ++i) {
      int c = CNT[i];
      for (int j = i; j < N; ++j) {
        int e = CNT[j];
        int d = 0;
        for (int k = 0; k < Prm.size(); ++k) d += abs(HH[i][k] - HH[j][k]);
        D[j][i] = D[i][j] = d;
        E[i][e] = min(E[i][e], d);
        E[j][c] = min(E[j][c], d);
      }
      Q.insert(c);
    }
    for (int q : Q) {
      for (int a = 0; a < Used.size(); ++a) {
        int i = Used[a];
        for (int b = a + 1; b < Used.size(); ++b) {
          int j = Used[b];
          D[j][i] = D[i][j] = min(D[i][j], E[i][q] + E[j][q]);
        }
      }
    }
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
      int a, b;
      cin >> a >> b;
      vector<int> F, G;
      fact(a, F);
      fact(b, G);
      int i = J[F], j = J[G];
      cout << D[i][j] << '\n';
    }
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  TaskD solver;
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  solver.solve(in, out);
  return 0;
}
