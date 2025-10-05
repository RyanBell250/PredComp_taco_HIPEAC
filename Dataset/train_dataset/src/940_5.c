
#include<cmath>
#include<algorithm>
#include<cassert>
const double EPS = 1e-9;                
enum POSITION {ONLINE_FRONT = -2, CLOCKWISE, ON_SEGMENT, COUNTER_CLOCKWISE, ONLINE_BACK};   
struct Point {
  double x, y;
  Point(const double d = 0.0) : x(d), y(d) {}
  Point(const double x, const double y) : x(x), y(y) {}
};
struct Segment {
  Point initial, terminal;
  Segment(const Point& initial, const Point& terminal) : initial(initial), terminal(terminal) {}
  Segment(const double x1, const double y1, const double x2, const double y2) : initial(x1, y1), terminal(x2, y2) {}
};
struct Line {
  Point initial, terminal;
  Line(const Point& initial, const Point& terminal) : initial(initial), terminal(terminal) {}
  Line(const double x1, const double y1, const double x2, const double y2) : initial(x1, y1), terminal(x2, y2) {}
  Line(const Segment& s) : initial(s.initial), terminal(s.terminal) {}
};
bool relative_equal(const double d1, const double d2) {return d1 == 0 ? std::abs(d2) < EPS : std::abs((d1 - d2) / d1) < EPS;}
bool operator==(const Point& lhs, const Point& rhs) {return relative_equal(lhs.x, rhs.x) && relative_equal(lhs.y, rhs.y);}
bool operator<(const Point& lhs, const Point& rhs) {return relative_equal(lhs.x, rhs.x) ? lhs.y < rhs.y : lhs.x < rhs.x;}
bool operator>(const Point& lhs, const Point& rhs) {return relative_equal(lhs.x, rhs.x) ? lhs.y > rhs.y : lhs.x > rhs.x;}
bool operator!=(const Point& lhs, const Point& rhs) {return !(lhs == rhs);}
bool operator<=(const Point& lhs, const Point& rhs) {return !(lhs > rhs);}
bool operator>=(const Point& lhs, const Point& rhs) {return !(lhs < rhs);}
const Point operator+(const Point& lhs, const Point& rhs) {return Point(lhs.x + rhs.x, lhs.y + rhs.y);}
const Point operator-(const Point& lhs, const Point& rhs) {return Point(lhs.x - rhs.x, lhs.y - rhs.y);}
const Point operator*(const Point& lhs, const Point& rhs) {return Point(lhs.x * rhs.x, lhs.y * rhs.y);}
const Point operator/(const Point& lhs, const Point& rhs) {return Point(lhs.x / rhs.x, lhs.y / rhs.y);}
const Point operator-(const Point& p) {return Point(-p.x, -p.y);}
double abs(const Point& p) {return std::hypot(p.x, p.y);}
double norm(const Point& p) {return p.x * p.x + p.y * p.y;}
double dot(const Point& a, const Point& b) {return a.x * b.x + a.y * b.y;}
double cross(const Point& a, const Point& b) {return a.x * b.y - a.y * b.x;}
bool parallel(const Line& l1, const Line& l2) {return relative_equal(0.0, cross(l2.terminal - l2.initial, l1.terminal - l1.initial));}
bool orthogonal(const Line& l1, const Line& l2) {return relative_equal(0.0, dot(l2.terminal - l2.initial, l1.terminal - l1.initial));}
POSITION ccw(const Point& a, const Point& b, const Point& p) {
  Point v1 = b - a;
  Point v2 = p - a;
  if(cross(v1, v2) >= EPS) return COUNTER_CLOCKWISE;
  if(cross(v1, v2) <= -EPS) return CLOCKWISE;
  if(dot(v1, v2) <= -EPS) return ONLINE_BACK;
  if(norm(v1) < norm(v2)) return ONLINE_FRONT;              
  return ON_SEGMENT;
}
bool intersect(const Point& p1, const Point& p2) {return p1 == p2;}
bool intersect(const Point& p, const Segment& s) {return abs(p - s.initial) + abs(p - s.terminal) - abs(s.initial - s.terminal) <= EPS;}
bool intersect(const Segment& s, const Point& p) {return intersect(p, s);}
bool intersect(const Point& p, const Line& l) {return !parallel(Line(p, l.initial), Line(p, l.terminal));}
bool intersect(const Line& l, const Point& p) {return intersect(p, l);}
bool intersect(const Segment& s1, const Segment& s2) {
  return ccw(s1.initial, s1.terminal, s2.initial) * ccw(s1.initial, s1.terminal, s2.terminal) <= 0
      && ccw(s2.initial, s2.terminal, s1.initial) * ccw(s2.initial, s2.terminal, s1.terminal) <= 0;
}
bool intersect(const Segment& s, const Line& l) {
  auto v1 = l.terminal - l.initial;
  auto v2 = s.initial  - l.initial;
  auto v3 = s.terminal - l.initial;
  return cross(v1, v2) * cross(v1, v3) <= EPS;
}
bool intersect(const Line& l, const Segment& s) {return intersect(s, l);}
bool intersect(const Line& l1, const Line& l2) {return !parallel(l1, l2) || intersect(l1.initial, l2);}
Point projection(const Point& p, const Line& l) {
  auto v = l.initial - l.terminal;
  return l.initial + dot(p - l.initial, v) / norm(v) * v;
}
Point projection(const Line& l, const Point& p) {return projection(p, l);}
Point reflection(const Point& p, const Line& l) {return p + 2 * (projection(p, l) - p);}
Point reflection(const Line& l, const Point& p) {return reflection(p, l);}
double distance(const Point& p1, const Point& p2) {
  auto p = p1 - p2;
  return hypot(p.x, p.y);
}
double distance(const Point& p, const Segment& s) {
  auto r = projection(s, p);
  return intersect(r, s) ? distance(p, r) : std::min(distance(p, s.initial), distance(p, s.terminal));
}
double distance(const Segment& s, const Point& p) {return distance(p, s);}
double distance(const Point& p, const Line& l) {return distance(p, projection(p, l));}
double distance(const Line& l, const Point& p) {return distance(p, l);}
double distance(const Segment& s1, const Segment& s2) {
  return intersect(s1, s2) ? 0.0 : std::min({distance(s1, s2.initial), distance(s1, s2.terminal), distance(s2, s1.initial), distance(s2, s1.terminal)});
}
double distance(const Segment& s, const Line& l) {return intersect(s, l) ? 0.0 : std::min(distance(s.initial, l), distance(s.terminal, l));}
double distance(const Line& l,const Segment& s) {return distance(s, l);}
double distance(const Line& l1, const Line& l2) {return intersect(l1, l2) ? 0.0 : distance(l1.initial, l2);}
const Point crosspoint(const Line& l1, const Line& l2) {
  assert(intersect(l1, l2));
  if(parallel(l1, l2)) return l1.initial;                   
  double A = cross(l1.terminal - l1.initial, l2.terminal - l2.initial);
  double B = cross(l1.terminal - l1.initial, l1.terminal - l2.initial);
  return l2.initial + B / A * (l2.terminal - l2.initial);
}
const Point crosspoint(const Segment& s, const Line& l) {
  assert(intersect(s, l));
  if(parallel(s, l)) return s.initial;
  return crosspoint(Line(s), l);
}
const Point crosspoint(const Line& l, const Segment& s) {return crosspoint(s, l);}
const Point crosspoint(const Segment& s1, const Segment& s2) {
  assert(intersect(s1, s2));
  if(parallel(s1, s2)) {                                    
    if(intersect(s1.initial,  s2)) return s1.initial;
    if(intersect(s1.terminal, s2)) return s1.terminal;
    if(intersect(s2.initial,  s1)) return s2.initial;
    if(intersect(s2.terminal, s1)) return s2.terminal;
  }
  return crosspoint(Line(s1), Line(s2));
}
#include<iostream>
std::ostream& operator<<(std::ostream& os, const Point& p) {os<<""; os<<"("<<p.x<<","<<p.y<<")"; return os;}
std::ostream& operator<<(std::ostream& os, const Segment& s) {os<<"segment: "; os<<s.initial<<" - "<<s.terminal; return os;}
std::ostream& operator<<(std::ostream& os, const Line& l) {os<<"line: "; os<<l.initial<<" - "<<l.terminal; return os;}
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<utility>
class Polygon {
public:
  void add(const Point& p);
  void clear();
  int size() const;
  Point vertex(const int n) const;
  Segment edge(const int n) const;
  const std::vector<Point>& vertex() const;
  const std::vector<Segment>& edge() const;
  bool touch(const Point& p) const;
  bool intersect(const Point& p) const;
  double area() const;
  bool convex() const;
  const Polygon convex_hull() const;
  double convex_diameter() const;
  const Polygon convex_cut(const Line& l) const;
private:
  std::vector<Point> vertex_;
  std::vector<Segment> edge_;
};
void Polygon::add(const Point& p) {
  if(!vertex_.empty()) {
    if(!edge_.empty()) edge_.pop_back();
    edge_.push_back(Segment(vertex_.back(), p));
    edge_.push_back(Segment(p, vertex_.front()));
  }
  vertex_.push_back(p);
}
void Polygon::clear() {
  vertex_.clear();
  edge_.clear();
};
int Polygon::size() const {return vertex_.size();}
Point Polygon::vertex(const int n) const {return vertex_.at(n);}
Segment Polygon::edge(const int n) const {return edge_.at(n);}
const std::vector<Point>& Polygon::vertex() const {return vertex_;}
const std::vector<Segment>& Polygon::edge() const {return edge_;}
bool Polygon::touch(const Point& p) const {
  return std::any_of(std::begin(edge()), std::end(edge()), [=](const Segment& s) {return ccw(s.initial, s.terminal, p) == ON_SEGMENT;});
}
bool Polygon::intersect(const Point& p) const {
  bool in = false;                    
  for(const auto& e: edge()) {
    if(::intersect(p, e)) return true;
    Point a = e.initial  - p;
    Point b = e.terminal - p;
    if(a.y > b.y) std::swap(a, b);
    if(a.y < EPS && EPS <= b.y && cross(a, b) < EPS) in = !in;
  }
  return in;
}
double Polygon::area() const {
  return std::abs(std::accumulate(std::begin(edge()), std::end(edge()), 0.0, [=](const double sum, const Segment& e){return sum + cross(e.initial, e.terminal);})) / 2.0;
}
bool Polygon::convex() const {
  bool positive = false;
  bool negative = false;
  for(int i = 0; i < size(); ++i) {
    auto position = ccw(vertex(i), vertex((i + 1) % size()), vertex((i + 2) % size()));
    positive |= position == CLOCKWISE;
    negative |= position == COUNTER_CLOCKWISE;
    if(negative && positive) return false;
  }
  return true;
}
const Polygon Polygon::convex_hull() const {
  auto original = vertex();
  std::sort(std::begin(original), std::end(original));
  original.insert(std::end(original), original.rbegin() + 1, original.rend());
  std::vector<Point> point;
  for(const auto& p: original) {
    while(point.size() >= 2 && ccw(point[point.size() - 2], point.back(), p) == CLOCKWISE) point.pop_back();
    point.push_back(p);
  }
  Polygon convex_hull;
  point.pop_back();
  for(const auto& p: point) convex_hull.add(p);
  return convex_hull;
}
double Polygon::convex_diameter() const {
  auto point = vertex();
  int p, q, start_p, start_q, max_p, max_q;
  p = start_p = max_p = std::min_element(std::begin(point), std::end(point)) - std::begin(point);
  q = start_q = max_q = std::max_element(std::begin(point), std::end(point)) - std::begin(point);
  double max_d = norm(vertex(p) - vertex(q));
  do {
    if(cross(vertex((p + 1) % size()) - vertex(p), vertex((q + 1) % size()) - vertex(q)) >= 0) q = (q + 1) % size();
    else p = (p + 1) % size();
    if(norm(vertex(p) - vertex(q)) > max_d) {
      max_d = norm(vertex(p) - vertex(q));
      max_p = p;
      max_q = q;
    }
  } while(start_p != q || start_q != p);
  return std::sqrt(max_d);
}
const Polygon Polygon::convex_cut(const Line& l) const {
  Polygon result;
  for(const auto& e: edge()) {
    if(ccw(l.initial, l.terminal, e.initial) == COUNTER_CLOCKWISE) result.add(e.initial);
    if(::intersect(e, l)) result.add(crosspoint(e, l));
  }
  return result;
}
#include<bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while(cin >> n, n) {
    Polygon polygon;
    for(int i = 0; i < n; ++i) {
      double x, y;
      cin >> x >> y;
      polygon.add(Point(x, y));
    }
    vector<set<Point>> separator(polygon.size());
    for(int k = 0; k < polygon.size(); ++k) {
      separator[k].insert(polygon.vertex(k));
      separator[k].insert(polygon.vertex((k + 1) % polygon.size()));
    }
    for(int i = 0; i < polygon.size(); ++i) for(int j = i + 1; j < polygon.size(); ++j) {
      Line l(polygon.vertex(i), polygon.vertex(j));
      for(int k = 0; k < polygon.size(); ++k) {
        Segment e(polygon.vertex(k), polygon.vertex((k + 1) % polygon.size()));
        if(intersect(l, e)) separator[k].insert(crosspoint(l, e));
      }
    }
    vector<Segment> edge;
    for(const auto& list: separator)
      for(auto cur = begin(list), pre = cur++; cur != end(list); pre = cur++)
        edge.emplace_back(*pre, *cur);
    vector<vector<bool>> cover(polygon.size(), vector<bool>(edge.size(), false));
    for(int e = 0; e < edge.size(); ++e) for(int v = 0; v < polygon.size(); ++v) {
      Segment s(polygon.vertex(v), (edge[e].initial + edge[e].terminal) / 2.0);
      set<Point> check{s.initial, s.terminal};
      for(const auto& f: polygon.edge()) if(intersect(s, f)) {
        if(parallel(s, f)) {
          check.insert(f.initial);
          check.insert(f.terminal);
        } else {
          check.insert(crosspoint(s, f));
        }
      }
      cover[v][e] = true;
      for(auto cur = begin(check), pre = cur++; cur != end(check); pre = cur++) if(!polygon.intersect((*pre + *cur) / 2.0)) cover[v][e] = false;
    }
    int ans = polygon.size();
    for(int bit = 1; bit < (1 << polygon.size()) - 1; ++bit) {
      bool ok = true;
      for(int e = 0; e < edge.size(); ++e) {
        bool f = false;
        for(int v = 0; v < polygon.size(); ++v) if((bit >> v) & 1) if(cover[v][e]) f = true;
        ok &= f;
        if(!ok) break;
      }
      if(ok) ans = min(ans, __builtin_popcount(bit));
    }
    cout << ans << endl;
  }
}