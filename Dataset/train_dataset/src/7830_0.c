#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const long double eps = 1e-6;
long double sign(long double x) { return (x > 0) - (x < 0); }
long long sign(long long x) { return (x > 0) - (x < 0); }
int sign(int x) { return (x > 0) - (x < 0); }
struct pt {
  long double x, y;
  pt() {}
  pt(long double _x, long double _y) : x(_x), y(_y) {}
  bool operator<(pt p) { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(pt p) { return tie(x, y) == tie(p.x, p.y); }
  pt operator+(pt p) { return {x + p.x, y + p.y}; }
  pt operator-(pt p) { return {x - p.x, y - p.y}; }
  pt operator*(long double d) { return {x * d, y * d}; }
  pt operator/(long double d) { return {x / d, y / d}; }
  long double dot(pt p) { return x * p.x + y * p.y; }
  long double det(pt p) { return x * p.y - y * p.x; }
  long double cross(pt p, pt q) { return (p - *this).det(q - *this); }
  long double dist() { return sqrtl(x * x + y * y); }
  pt rot90() { return pt(-y, x); }
  pt unit() { return *this / dist(); }
  long double angle() { return atan2(y, x); }
  pt rot(long double an) {
    return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)};
  }
  void read() { cin >> x >> y; }
  void write() { cout << "(" << x << "," << y << ")" << endl; }
};
struct seg {
  pt fi, sc;
  seg() {}
  seg(pt _fi, pt _sc) : fi(_fi), sc(_sc) {}
  long double dist(pt C) {
    if (fi == sc) return (C - fi).dist();
    long double d = pow((sc - fi).dist(), 2);
    long double t = min(d, max((long double)0.0, (C - fi).dot(sc - fi)));
    return ((C - fi) * d - (sc - fi) * t).dist() / d;
  }
  long double len() { return (fi - sc).dist(); }
  bool on_seg(pt C) {
    return abs(C.cross(fi, sc)) < eps && (fi - C).dot(sc - C) <= eps;
  }
  vector<pt> intersect(seg rhs) {
    long double oa = rhs.fi.cross(rhs.sc, fi);
    long double ob = rhs.fi.cross(rhs.sc, sc);
    long double oc = fi.cross(sc, rhs.fi);
    long double od = fi.cross(sc, rhs.sc);
    if (sign(oa) * sign(ob) < 0 && sign(oc) * sign(od) < 0)
      return {(fi * ob - sc * oa) / (ob - oa)};
    vector<pt> ans;
    if (rhs.on_seg(fi)) ans.push_back(fi);
    if (rhs.on_seg(sc)) ans.push_back(sc);
    if (on_seg(rhs.fi)) ans.push_back(rhs.fi);
    if (on_seg(rhs.sc)) ans.push_back(rhs.sc);
    return ans;
  }
};
struct line {
  long double a, b, c;
  line(pt p1, pt p2) {
    assert(!(p1 == p2));
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = a * p1.x + b * p1.y;
  }
  line() {}
  line(long double _a, long double _b, long double _c) : a(_a), b(_b), c(_c) {}
  long double dist(pt p) {
    return fabs(a * p.x + b * p.y - c) / sqrtl(a * a + b * b);
  }
  pair<int, pt> intersect(line rhs) {
    long double dett = a * rhs.b - b * rhs.a;
    if (fabs(dett) <= eps) {
      long double det2 = c * rhs.a - a * rhs.c;
      if (fabs(det2) <= eps) return {-1, pt()};
      return {0, pt()};
    }
    return {1,
            pt((c * rhs.b - rhs.c * b) / dett, (a * rhs.c - c * rhs.a) / dett)};
  }
};
pt reflect(pt A, line L) {
  line perpendicular(-L.b, L.a, -L.b * A.x + L.a * A.y);
  pt insect = perpendicular.intersect(L).second;
  return insect * (long double)2.0 - A;
}
struct mint {
  int val;
  mint() { val = 0; }
  mint(const long long& v) {
    val = (-mod <= v && v < mod) ? v : v % mod;
    if (val < 0) val += mod;
  }
  friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
  friend bool operator==(const mint& a, const mint& b) {
    return a.val == b.val;
  }
  friend bool operator!=(const mint& a, const mint& b) {
    return a.val != b.val;
  }
  friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }
  friend bool operator>(const mint& a, const mint& b) { return a.val > b.val; }
  friend bool operator<=(const mint& a, const mint& b) {
    return a.val <= b.val;
  }
  friend bool operator>=(const mint& a, const mint& b) {
    return a.val >= b.val;
  }
  mint operator-() { return mint(-val); }
  mint& operator+=(const mint& m) {
    if ((val += m.val) >= mod) val -= mod;
    return *this;
  }
  mint& operator-=(const mint& m) {
    if ((val -= m.val) < mod) val += mod;
    return *this;
  }
  mint& operator*=(const mint& m) {
    val = (val * 1ll * m.val) % mod;
    return *this;
  }
  friend mint pow(mint a, long long p) {
    mint ans = 1;
    for (; p; p /= 2, a *= a)
      if (p % 2 == 1) ans *= a;
    return ans;
  }
  friend mint inv(const mint& a) {
    assert(a.val);
    return pow(a, mod - 2);
  }
  mint& operator/=(const mint& m) { return (*this) *= inv(m); }
  friend mint operator+(mint a, const mint& b) { return a += b; }
  friend mint operator-(mint a, const mint& b) { return a -= b; }
  friend mint operator*(mint a, const mint& b) { return a *= b; }
  friend mint operator/(mint a, const mint& b) { return a /= b; }
};
int solve();
void precomp();
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  if (0) cin >> t;
  if (0) cout << fixed << setprecision(10);
  precomp();
  for (int tc = 1; tc <= t; tc++) {
    if (0 && 0) cout << "Case #" << tc << ": ";
    solve();
  }
}
void precomp() { return; }
int n;
vector<long long> a, b;
bool isinc(vector<long long> x) {
  for (int i = 1; i < x.size(); i++)
    if (x[i] <= x[i - 1]) return false;
  return true;
}
bool isdec(vector<long long> x) {
  for (int i = 1; i < x.size(); i++)
    if (x[i] >= x[i - 1]) return false;
  return true;
}
vector<long long> invpref(vector<long long> x) {
  vector<long long> u(n);
  u[0] = x[0];
  for (int i = 1; i < n; i++) u[i] = x[i] - x[i - 1];
  return u;
}
void rev(vector<long long>& x) { reverse(x.begin(), x.end()); }
int solve() {
  cin >> n;
  a.resize(n);
  b.resize(n);
  long long suma = 0ll, sumb = 0ll;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    suma += a[i];
  }
  for (int j = 0; j < n; j++) {
    cin >> b[j];
    sumb += b[j];
  }
  vector<long long> arev = a;
  rev(arev);
  long long ipc = 0;
  if (n > 2) {
    string ans = "";
    for (;;) {
      if (suma == sumb) {
        if (arev == b) {
          ans += 'R';
          rev(b);
        }
        if (a == b) {
          reverse(ans.begin(), ans.end());
          if (ipc > 2e5)
            cout << "BIG\n" << ipc << endl;
          else
            cout << "SMALL\n" << ans.size() << endl << ans << endl;
        } else
          cout << "IMPOSSIBLE\n";
        return 0;
      } else if (isinc(b)) {
        b = invpref(b);
        sumb = 0ll;
        for (int i = 0; i < n; i++) sumb += b[i];
        ans += 'P';
        ipc++;
      } else if (isdec(b)) {
        rev(b);
        ans += 'R';
      } else {
        cout << "IMPOSSIBLE\n";
        return 0;
      }
    }
  } else if (n == 2) {
    vector<long long> ans;
    long long revcnt = 0;
    bool reved = a[0] > a[1];
    if (reved) swap(a[0], a[1]);
    if (b[0] > b[1]) {
      swap(b[0], b[1]);
      ans.push_back(-1);
      revcnt++;
    }
    for (;;) {
      if (b[0] == 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
      }
      if (suma > sumb) {
        cout << "IMPOSSIBLE\n";
        return 0;
      }
      if (suma == sumb) {
        if (a != b) {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
        if (reved) {
          ans.push_back(-1);
          revcnt++;
        }
        if (ipc > 2e5)
          cout << "BIG\n" << ipc << endl;
        else {
          cout << "SMALL\n" << revcnt + ipc << endl;
          reverse(ans.begin(), ans.end());
          for (long long i : ans) {
            if (i == -1)
              cout << 'R';
            else
              for (int j = 0; j < i; j++) cout << 'P';
          }
          cout << endl;
        }
        return 0;
      }
      if (a[0] == b[0]) {
        if ((b[1] - a[1]) % b[0] == 0) {
          long long nw = (b[1] - a[1]) / b[0];
          ans.push_back(nw);
          ipc += nw;
          b = a;
          sumb = b[0] + b[1];
        } else {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
      } else {
        long long nw = b[1] / b[0];
        ans.push_back(nw);
        ipc += nw;
        ans.push_back(-1);
        revcnt++;
        swap(b[0], b[1]);
        b[0] %= b[1];
        sumb = b[0] + b[1];
      }
    }
  } else if (n == 1) {
    if (a[0] == b[0])
      cout << "SMALL\n0\n\n";
    else
      cout << "IMPOSSIBLE\n";
    return 0;
  }
  return 0;
}
