#include "bits/stdc++.h"
using namespace std;
#ifdef _DEBUG
#include "dump.hpp"
#else
#define dump(...)
#endif
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define rrep(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define all(c) begin(c),end(c)
const int INF = sizeof(int) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const int MOD = (int)(1e9) + 7;
template<class T> bool chmax(T &a, const T &b) { if (a < b) { a = b; return true; } return false; }
template<class T> bool chmin(T &a, const T &b) { if (b < a) { a = b; return true; } return false; }
const double EPS = 1e-8; 
#define equals(a,b) (fabs((a)-(b)) < EPS)
template<class T> bool chequals(T &a, const T &b) { if (fabs(a - b) < EPS) { a = b; return true; } return false; }
struct Point {
	double x, y, z;
	Point() :x(0.0), y(0.0), z(0.0) {}
	Point(double x, double y, double z) :x(x), y(y), z(z) {}
	Point &operator+=(const Point &p) { x += p.x; y += p.y; z += p.z; return *this; }
	Point &operator-=(const Point &p) { x -= p.x; y -= p.y; z -= p.z; return *this; }
	Point &operator*=(double a) { x *= a; y *= a; z *= a; return *this; }
	Point &operator/=(double a) { x /= a; y /= a; z /= a; return *this; }
	bool operator<(const Point &p)const {
		if (x < p.x)return true;
		if (x > p.x)return false;
		if (y < p.y)return true;
		if (y > p.y)return false;
		if (z < p.z)return true;
		return false;
	}
	bool operator==(const Point &p)const { return equals(x, p.x) && equals(y, p.y) && equals(z, p.z); }
	double abs() { return sqrt(norm()); }
	double norm() { return x*x + y*y + z*z; }
};
Point operator+(const Point &p1, const Point &p2) { return Point(p1) += p2; }
Point operator-(const Point &p1, const Point &p2) { return Point(p1) -= p2; }
Point operator*(const Point &p, double a) { return Point(p) *= a; }
Point operator/(const Point &p, double a) { return Point(p) /= a; }
inline ostream &operator << (ostream &os, const Point &p) { os << p.x << " " << p.y << " " << p.z; return os; }
inline istream &operator >> (istream &is, Point &p) { double x, y, z; is >> x >> y >> z; p = Point(x, y, z); return is; }
struct Vector :public Point {
	using Point::Point;
	Vector() {}
	Vector(const Point &P) { x = P.x; y = P.y; z = P.z; }
	Vector unit() { return *this / abs(); }
};
double dot(Vector a, Vector b) {
	double ret = a.x*b.x + a.y*b.y + a.z*b.z;
	chequals(ret, 0.0);
	return ret;
}
Vector cross(Vector a, Vector b) {
	Vector ret;
	ret.x = a.y*b.z - a.z*b.y; chequals(ret.x, 0.0);
	ret.y = a.z*b.x - a.x*b.z; chequals(ret.y, 0.0);
	ret.z = a.x*b.y - a.y*b.x; chequals(ret.z, 0.0);
	return ret;
}
struct Line {
	Point p1, p2;
	Line() {}
	Line(Point p1, Point p2) :p1(p1), p2(p2) {}
};
struct Segment :public Line {
	using Line::Line;
	Segment() {}
	Segment(const Line &L) { p1 = L.p1; p2 = L.p2; }
	Vector vec() { return p2 - p1; }
};
struct Sphere {
	Point c;
	double r;
	Sphere() {}
	Sphere(const Point &c, double r) :c(c), r(r) {};
};
using Polygon = vector<Point>;
struct Plane {
	double a, b, c, d;
	Plane() {}
	Plane(double a, double b, double c, double d) :a(a), b(b), c(c), d(d) {}
	Plane(const Vector &n, const Point &p) :a(n.x), b(n.y), c(n.z) {
		d = -(a*p.x + b*p.y + c*p.z);
	};
	Vector normal() { return Vector(a, b, c); } 
	Point point() { return Point(a*d, b*d, c*d); }
};
struct Triangle {
	Point p1, p2, p3;
	Triangle() {}
	Triangle(const Point &p1, const Point &p2, const Point &p3) :p1(p1), p2(p2), p3(p3) {}
	Plane plane() {
		Vector OA(p2 - p1), OB(p3 - p1);
		Vector n(cross(OA, OB));
		return Plane(n, p1);
	}
};
double rad(double deg) { return acos(-1)*deg / 180; }
double arg(Vector p) { return atan2(p.y, p.x); }
double angle(Vector a, Vector b) {
	double lena = a.abs(), lenb = b.abs();
	if (lena == 0 || lenb == 0)return 0; 
	double costheta = dot(a, b) / (lena*lenb);
	if (equals(costheta, 1))costheta = 1; 
	return acos(costheta);
}
bool is_orthogonal(Vector a, Vector b) { return equals(dot(a, b), 0.0); }
bool is_orthogonal(Segment s1, Segment s2) { return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0); }
Point project(Segment s, Point p) {
	Vector base = s.p2 - s.p1;
	double r = dot(p - s.p1, base) / base.norm();
	return s.p1 + base*r;
}
Point reflect(Segment s, Point p) { return p + (project(s, p) - p)*2.0; }
double get_distance(Point a, Point b) { return (a - b).abs(); }
double get_distance(Line l, Point p) { return cross(l.p2 - l.p1, p - l.p1).abs() / (l.p2 - l.p1).abs(); }
double get_distance(Segment s, Point p) {
	if (dot(s.p2 - s.p1, p - s.p1) < 0.0)return get_distance(p, s.p1);
	if (dot(s.p1 - s.p2, p - s.p2) < 0.0)return get_distance(p, s.p2);
	return get_distance(Line(s), p);
}
bool intersect(Sphere SP, Segment S) {
	return SP.r + EPS >= get_distance(S, SP.c);
}
pair<Point, Point> get_cross_points(Sphere SP, Line L) {
	assert(intersect(SP, L));
	Vector pr = project(L, SP.c);
	Vector e = (L.p2 - L.p1) / (L.p2 - L.p1).abs();
	double base = sqrt(SP.r*SP.r - (pr - SP.c).norm());
	return make_pair(pr + e*base, pr - e*base);
}
Point center(const Polygon &P) {
	Point ret;
	for (auto &p : P)ret += p;
	ret /= P.size();
	return ret;
}
void boundingSphere() {
	cout << fixed << setprecision(10);
	for (int N; cin >> N&&N;) {
		Polygon p(N);
		vector<double> v(N, 1.0);
		rep(i, 0, N)
			cin >> p[i];
		Point g = center(p);
		vector<double> cost(N);
		double move = 0.5, y = 0.99;
		while (move > EPS) {
			rep(i, 0, N)
				cost[i] = get_distance(g, p[i]) / v[i];
			int maxidx = max_element(all(cost)) - cost.begin();
			g += (p[maxidx] - g) *move;
			move *= y;
		}
		double ans = 0;
		rep(i, 0, N)
			chmax(ans, get_distance(g, p[i]) / v[i]);
		cout << ans << endl;
	}
}
signed main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	boundingSphere();
	return 0;
}