#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n==0) ? 1 : 10*TEN(n-1); }
template<class T> using V = vector<T>;
template<class T> using VV = V<V<T>>;
using D = double;
using P = complex<D>;
const D PI = acos(D(-1)), EPS = 1e-10;
int sgn(D a) {
    if (abs(a) <= EPS) return 0;
    return (a < 0) ? -1 : 1;
}
bool near(P a, P b) { return !sgn(abs(a-b)); }
D mabs(P p) { return abs(p.real()) + abs(p.imag()); }
bool lessP(P l, P r) {
    if (sgn(r.real()-l.real())) return l.real() < r.real();
    if (sgn(r.imag()-l.imag())) return l.imag() < r.imag();
    return false;
}
D cross(P a, P b) { return a.real()*b.imag() - a.imag()*b.real(); }
D dot(P a, P b) { return a.real()*b.real() + a.imag()*b.imag(); }

int ccw(P b, P c) {
    int s = sgn(cross(b, c) / mabs(b));
    if (s) return s;
    if (!sgn(mabs(c)) || !sgn(mabs(c-b))) return 0;
    if (dot(b, c) < 0) return 2;
    if (dot(-b, c-b) < 0) return -2;
}
int ccw(P a, P b, P c) { return ccw(b-a, c-a); }
struct L {
    P x, y;
    L() {}
    L(P x, P y) :x(x), y(y) {}
    P vec() const { return y-x; }
};
D abs(const L &l) { return abs(l.vec()); }
D distLP(const L &l, const P &p) {
    return abs(cross(l.vec(), p-l.x)/abs(l.vec()));
}
D distSP(const L &s, const P &p) {
    P s2 = s.vec()*P(0, 1);
    if (ccw(s.x, s.x+s2, p) == 1) return abs(s.x-p);
    if (ccw(s.y, s.y+s2, p) == -1) return abs(s.y-p);
    return min(min(abs(s.x-p), abs(s.y-p)), distLP(s, p));
}
using Pol = V<P>;
using Tri = array<P, 3>;
struct C {
    P p; D r;
    C() {}
    C(P p, D r) : p(p), r(r) {}
};
C circumCircle(P a, P b, P c) {
    b -= a; c -= a;
    D s = 2*cross(b, c);
    D x = norm(b-c), y = norm(c), z = norm(b);
    D S = x+y+z;
    P r = (y*(S-2*y)*b+z*(S-2*z)*c)/(s*s);
    return C(r + a, abs(r));
}
C smallestEnclosingCircle(Pol &p, int ps = 0, Tri q = Tri(), int qs = 0) {
    if (ps == p.size()) {
        switch (qs) {
            case 0:
                return C(P(0, 0), -1);
            case 1:
                return C(q[0], 0);
            case 2:
                return C((q[0]+q[1])/D(2.0), abs(q[0]-q[1])/D(2.0));
            case 3:
                return circumCircle(q[0], q[1], q[2]);
        }
        assert(false);
    }
    C c = smallestEnclosingCircle(p, ps+1, q, qs);
    if (sgn(abs(p[ps]-c.p) - c.r) == 1) {
        q[qs] = p[ps];
        return smallestEnclosingCircle(p, ps+1, q, qs+1);
    }
    return c;
}
const int MN = 14;
const int MM = 14;
int n, m;
P p[MN];
D pre[1<<MN];
D dp[MM+1][1<<MN];
bool vis[MM+1][1<<MN];
D solve(int f, int m) {
    if (f == 0) return 0;
    if (m == 0) return 1e100;
    if (vis[m][f]) return dp[m][f];
    vis[m][f] = true;
    D ans = 1e100;
    int g = 0;
    do {
        ans = min(ans, max(pre[g], solve(f^g, m-1)));
        g = ((g|~f)+1) & f;
    } while (g);
    return dp[m][f] = ans;
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << setprecision(20);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        D x, y;
        cin >> x >> y;
        p[i] = P(x, y);
    }
    for (int f = 0; f < (1<<n); f++) {
        V<P> v;
        for (int i = 0; i < n; i++) {
            if (!(f & (1<<i))) continue;
            v.push_back(p[i]);
        }
        pre[f] = smallestEnclosingCircle(v).r;

    }
    cout << solve((1<<n) - 1, m) << endl;
    return 0;
}
