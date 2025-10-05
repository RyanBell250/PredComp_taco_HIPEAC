#include <bits/stdc++.h>
long long dx[4] = {0, -1, 0, 1};
long long dy[4] = {1, 0, -1, 0};
using namespace std;
class pa3 {
 public:
  long long x, y, z;
  pa3(long long x = 0, long long y = 0, long long z = 0) : x(x), y(y), z(z) {}
  bool operator<(const pa3 &p) const {
    if (x != p.x) return x < p.x;
    if (y != p.y) return y < p.y;
    return z < p.z;
  }
  bool operator>(const pa3 &p) const {
    if (x != p.x) return x > p.x;
    if (y != p.y) return y > p.y;
    return z > p.z;
  }
  bool operator==(const pa3 &p) const {
    return x == p.x && y == p.y && z == p.z;
  }
  bool operator!=(const pa3 &p) const {
    return !(x == p.x && y == p.y && z == p.z);
  }
};
class pa4 {
 public:
  long long x;
  long long y, z, w;
  pa4(long long x = 0, long long y = 0, long long z = 0, long long w = 0)
      : x(x), y(y), z(z), w(w) {}
  bool operator<(const pa4 &p) const {
    if (x != p.x) return x < p.x;
    if (y != p.y) return y < p.y;
    if (z != p.z) return z < p.z;
    return w < p.w;
  }
  bool operator>(const pa4 &p) const {
    if (x != p.x) return x > p.x;
    if (y != p.y) return y > p.y;
    if (z != p.z) return z > p.z;
    return w > p.w;
  }
  bool operator==(const pa4 &p) const {
    return x == p.x && y == p.y && z == p.z && w == p.w;
  }
  bool operator!=(const pa4 &p) const {
    return !(x == p.x && y == p.y && z == p.z && w == p.w);
  }
};
class pa2 {
 public:
  long long x, y;
  pa2(long long x = 0, long long y = 0) : x(x), y(y) {}
  pa2 operator+(pa2 p) { return pa2(x + p.x, y + p.y); }
  pa2 operator-(pa2 p) { return pa2(x - p.x, y - p.y); }
  bool operator<(const pa2 &p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator>(const pa2 &p) const { return x != p.x ? x > p.x : y > p.y; }
  bool operator==(const pa2 &p) const {
    return abs(x - p.x) == 0 && abs(y - p.y) == 0;
  }
  bool operator!=(const pa2 &p) const {
    return !(abs(x - p.x) == 0 && abs(y - p.y) == 0);
  }
};
class Point {
 public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double a) { return Point(x * a, y * a); }
  Point operator/(double a) { return Point(x / a, y / a); }
  double absv() { return sqrt(norm()); }
  double norm() { return x * x + y * y; }
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==(const Point &p) const {
    return fabs(x - p.x) < (1e-10) && fabs(y - p.y) < (1e-10);
  }
};
struct Segment {
  Point p1, p2;
};
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
bool parareru(Point a, Point b, Point c, Point d) {
  return abs(cross(a - b, d - c)) < (1e-10);
}
double distance_ls_p(Point a, Point b, Point c) {
  if (dot(b - a, c - a) < (1e-10)) return (c - a).absv();
  if (dot(a - b, c - b) < (1e-10)) return (c - b).absv();
  return abs(cross(b - a, c - a)) / (b - a).absv();
}
bool is_intersected_ls(Segment a, Segment b) {
  if (a.p1 == b.p1 || a.p2 == b.p1 || a.p1 == b.p2 || a.p2 == b.p2)
    return false;
  if (parareru((a.p2), (a.p1), (a.p1), (b.p2)) &&
      parareru((a.p2), (a.p1), (a.p1), (b.p1))) {
    if (dot(a.p1 - b.p1, a.p1 - b.p2) < (1e-10)) return true;
    if (dot(a.p2 - b.p1, a.p2 - b.p2) < (1e-10)) return true;
    if (dot(a.p1 - b.p1, a.p2 - b.p1) < (1e-10)) return true;
    if (dot(a.p1 - b.p2, a.p2 - b.p2) < (1e-10)) return true;
    return false;
  } else
    return (cross(a.p2 - a.p1, b.p1 - a.p1) * cross(a.p2 - a.p1, b.p2 - a.p1) <
            (1e-10)) &&
           (cross(b.p2 - b.p1, a.p1 - b.p1) * cross(b.p2 - b.p1, a.p2 - b.p1) <
            (1e-10));
}
double segment_dis(Segment a, Segment b) {
  if (is_intersected_ls(a, b)) return 0;
  double r = distance_ls_p(a.p1, a.p2, b.p1);
  r = min(r, distance_ls_p(a.p1, a.p2, b.p2));
  r = min(r, distance_ls_p(b.p1, b.p2, a.p2));
  r = min(r, distance_ls_p(b.p1, b.p2, a.p1));
  return r;
}
Point intersection_ls(Segment a, Segment b) {
  Point ba = b.p2 - b.p1;
  double d1 = abs(cross(ba, a.p1 - b.p1));
  double d2 = abs(cross(ba, a.p2 - b.p1));
  double t = d1 / (d1 + d2);
  return a.p1 + (a.p2 - a.p1) * t;
}
string itos(long long i) {
  ostringstream s;
  s << i;
  return s.str();
}
long long gcd(long long v, long long b) {
  if (v > b) return gcd(b, v);
  if (v == b) return b;
  if (b % v == 0) return v;
  return gcd(v, b % v);
}
double distans(double x1, double y1, double x2, double y2) {
  double rr = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  return sqrt(rr);
}
long long mod;
long long pr[401000];
long long inv[401000];
long long beki(long long wa, long long rr, long long warukazu) {
  if (rr == 0) return 1 % warukazu;
  if (rr == 1) return wa % warukazu;
  if (rr % 2 == 1) return (beki(wa, rr - 1, warukazu) * wa) % warukazu;
  long long zx = beki(wa, rr / 2, warukazu);
  return (zx * zx) % warukazu;
}
long long comb(long long nn, long long rr) {
  long long r = pr[nn] * inv[rr];
  r %= mod;
  r *= inv[nn - rr];
  r %= mod;
  return r;
}
void gya(long long ert) {
  pr[0] = 1;
  for (long long i = 1; i < ert; i++) {
    pr[i] = (pr[i - 1] * i) % mod;
  }
  for (long long i = 0; i < ert; i++) inv[i] = beki(pr[i], mod - 2, mod);
}
long long par[60], ranks[60], kosuu[60];
void shoki(long long n) {
  for (long long i = 0; i < n; i++) {
    par[i] = i;
    ranks[i] = 0;
    kosuu[i] = 1;
  }
}
long long root(long long x) { return par[x] == x ? x : par[x] = root(par[x]); }
bool same(long long x, long long y) { return root(x) == root(y); }
void unite(long long x, long long y) {
  x = root(x);
  y = root(y);
  long long xx = kosuu[x], yy = kosuu[y];
  if (x == y) return;
  if (ranks[x] < ranks[y]) {
    par[x] = y;
    kosuu[y] = yy + xx;
  } else {
    par[y] = x;
    if (ranks[x] == ranks[y]) ranks[x] = ranks[x] + 1;
    kosuu[x] = yy + xx;
  }
  return;
}
long long ban[10][132020];
class X {
 public:
  long long hi[10];
  long long mi[10];
  long long l, r;
  long long cc;
};
long long n;
struct segsum {
 private:
 public:
  long long cor = (1 << 17);
  vector<X> vec;
  X mrg(X z1, X z2) {
    X zz;
    zz.cc = z1.cc + z2.cc;
    zz.l = z1.l;
    zz.r = z2.r;
    shoki(60);
    for (long long i = 0; i < n; i++)
      if (ban[i][z1.r] == ban[i][z2.l]) {
        if (!same(z1.mi[i], z2.hi[i] + 30)) zz.cc--;
        unite(z1.mi[i], z2.hi[i] + 30);
      }
    long long use[60] = {0};
    for (long long i = 0; i < n; i++) {
      long long rr2 = root(z1.hi[i]);
      zz.hi[i] = rr2;
      long long rr = root(z2.mi[i] + 30);
      use[rr] = 1;
      use[rr2] = 1;
      zz.mi[i] = rr;
    }
    long long cn = 1;
    for (long long i = 1; i < 60; i++) {
      if (use[i]) {
        use[i] = cn;
        cn++;
      }
    }
    for (long long i = 0; i < n; i++) {
      zz.hi[i] = use[zz.hi[i]];
      zz.mi[i] = use[zz.mi[i]];
    }
    return zz;
  }
  void shoki1() { vec.resize(2 * cor + 3); }
  void shoki2() {
    for (long long i = cor - 1; i > 0; i--) {
      vec[i] = mrg(vec[2 * i], vec[2 * i + 1]);
    }
  }
  X sum(long long a, long long b, long long k = 1, long long l = 0,
        long long r = -10) {
    if (r < 0) r = cor;
    if (a == l && r == b) {
      return vec[k];
    }
    if (b <= (l + r) / 2) return sum(a, b, k * 2, l, (l + r) / 2);
    if (a >= (l + r) / 2) return sum(a, b, k * 2 + 1, (l + r) / 2, r);
    X v1 = sum(a, (l + r) / 2, k * 2, l, (l + r) / 2),
      v2 = sum((l + r) / 2, b, k * 2 + 1, (l + r) / 2, r);
    return mrg(v1, v2);
  }
};
segsum ss;
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  long long m, q;
  cin >> n >> m >> q;
  ss.shoki1();
  for (long long i = 0; i < n; i++)
    for (long long j = 132000; j >= 0; j--) ban[i][j] = i + 1;
  for (long long i = 0; i < n; i++)
    for (long long j = 1; j <= m; j++) cin >> ban[i][j];
  for (long long j = 0; j < ss.cor; j++) {
    X z;
    z.hi[0] = 1;
    for (long long i = 1; i < n; i++) {
      if (ban[i][j] == ban[i - 1][j])
        z.hi[i] = z.hi[i - 1];
      else
        z.hi[i] = z.hi[i - 1] + 1;
    }
    for (long long i = 0; i < n; i++) z.mi[i] = z.hi[i];
    z.cc = z.mi[n - 1];
    z.l = j;
    z.r = j;
    ss.vec[ss.cor + j] = z;
  }
  ss.shoki2();
  for (long long i = 0; i < q; i++) {
    long long l, r;
    cin >> l >> r;
    cout << ss.sum(l, r + 1).cc << "\n";
  }
  return 0;
}
