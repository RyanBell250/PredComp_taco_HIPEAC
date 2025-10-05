#include <bits/stdc++.h>
using namespace std;
template <typename T>
ostream &operator<<(ostream &out, vector<T> const &a) {
  out << "[";
  for (int i = 0; i < int((a).size()); ++i) {
    if (i != 0) {
      out << ", ";
    }
    out << a[i];
  }
  out << "]";
  return out;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> const &p) {
  out << "(" << p.first << ", " << p.second << ")";
  return out;
}
pair<long long, long long> operator+(const pair<long long, long long> &a,
                                     const pair<long long, long long> &b) {
  return make_pair(a.first + b.first, a.second + b.second);
}
pair<long long, long long> operator-(const pair<long long, long long> &a,
                                     const pair<long long, long long> &b) {
  return make_pair(a.first - b.first, a.second - b.second);
}
long long operator*(const pair<long long, long long> &a,
                    const pair<long long, long long> &b) {
  return a.first * b.first + a.second * b.second;
}
long long operator^(const pair<long long, long long> &a,
                    const pair<long long, long long> &b) {
  return a.first * b.second - a.second * b.first;
}
const int N = 100000;
const int M = 100000;
struct Data {
  int n;
  pair<long long, long long> a[N];
  int m;
  pair<int, int> r[M];
  bool read() {
    if (!(cin >> n)) {
      return 0;
    }
    for (int i = 0; i < int(n); ++i) {
      cin >> a[i].first >> a[i].second;
    }
    cin >> m;
    for (int i = 0; i < int(m); ++i) {
      scanf("%d%d", &r[i].first, &r[i].second);
      --r[i].first;
      --r[i].second;
    }
    return 1;
  }
  int ans[M];
  void write() {
    for (int i = 0; i < int(m); ++i) {
      if (i) {
        printf(" ");
      }
      printf("%d", ans[i] + 1);
    }
    puts("");
  }
  virtual void solve() {}
  virtual void clear() { *this = Data(); }
};
struct Solution : Data {
  static const int D = 20;
  int p[N][D];
  int l[N];
  int lca(int first, int second) {
    if (l[first] < l[second]) {
      swap(first, second);
    }
    int k = l[first] - l[second];
    for (int i = int(D) - 1; i >= 0; --i) {
      if (k & (1 << i)) {
        first = p[first][i];
      }
    }
    if (first == second) {
      return first;
    }
    for (int i = int(D) - 1; i >= 0; --i) {
      if (p[first][i] != p[second][i]) {
        first = p[first][i];
        second = p[second][i];
      }
    }
    return p[first][0];
  }
  void solve() {
    vector<int> q;
    for (int i = int(n) - 1; i >= 0; --i) {
      while (q.size() > 1 &&
             ((a[q[q.size() - 1]] - a[i]) ^ (a[q[q.size() - 2]] - a[i])) > 0) {
        q.pop_back();
      }
      p[i][0] = q.size() ? q.back() : 0;
      l[i] = q.size() ? l[q.back()] + 1 : 0;
      q.push_back(i);
      for (int j = 0; j < int(D - 1); ++j) {
        p[i][j + 1] = p[p[i][j]][j];
      }
    }
    for (int i = 0; i < int(m); ++i) {
      ans[i] = lca(r[i].first, r[i].second);
    }
  }
  Solution(Data d = Data()) : Data(d) {}
  void clear() { *this = Solution(); }
};
Solution sol;
int main() {
  sol.read();
  sol.solve();
  sol.write();
  return 0;
}
