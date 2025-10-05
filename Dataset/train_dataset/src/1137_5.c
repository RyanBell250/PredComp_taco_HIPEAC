#include <bits/stdc++.h>
using namespace std;
const int MAX = 210000;
const int INF = 1000000000;
const int MOD = 1000000007;
int mod(int a, int b, int m) {
  int ret = 1;
  a %= m;
  while (b) {
    if (b & 1) ret = ret * a % m;
    b >>= 1;
    a = a * a % m;
  }
  return ret;
}
int inv(int a) { return mod(a, MOD - 2, MOD); }
int vabs(int x) { return x > 0 ? x : -x; }
int gcd(int a, int b) { return a % b ? gcd(b, a % b) : b; }
int cross(pair<int, int> a, pair<int, int> b) {
  return a.first * b.second - a.second * b.first;
}
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<int> e[MAX];
struct Line {
  int x, l, r;
  Line() {}
  Line(int x_, int l_, int r_, int dx, int dy) {
    x = x_;
    l = l_;
    r = r_;
    dir.first = dx;
    dir.second = dy;
  }
  pair<int, int> dir;
};
vector<Line> h;
vector<Line> v;
void makeLine(int a, int b, int c, int d) {
  if (a == c) {
    v.push_back(Line(a, min(b, d), max(b, d), c - a, d - b));
  } else {
    h.push_back(Line(b, min(a, c), max(a, c), c - a, d - b));
  }
}
bool cmp(Line a, Line b) {
  if (a.x != b.x) return a.x < b.x;
  return a.l < b.l;
}
map<pair<int, int>, int> mp;
int id;
void buildGraph(int x1, int y1, int x2, int y2) {
  if (x1 == x2 && y1 == y2) return;
  if (mp[make_pair(x1, y1)] == 0) mp[make_pair(x1, y1)] = ++id;
  if (mp[make_pair(x2, y2)] == 0) mp[make_pair(x2, y2)] = ++id;
  int a = mp[make_pair(x1, y1)];
  int b = mp[make_pair(x2, y2)];
  e[a].push_back(b);
  e[b].push_back(a);
}
void cutVertical(Line a, int x1, int y1, int x2, int y2) {
  if (a.x <= x1 || a.x >= x2) return;
  if (a.l >= y2 || a.r <= y1) return;
  y1 = max(y1, a.l);
  y2 = min(y2, a.r);
  buildGraph(a.x, y1, a.x, y2);
}
void cutHerizon(Line a, int x1, int y1, int x2, int y2) {
  if (a.x <= y1 || a.x >= y2) return;
  if (a.l >= x2 || a.r <= x1) return;
  x1 = max(x1, a.l);
  x2 = min(x2, a.r);
  buildGraph(x1, a.x, x2, a.x);
}
int dot(pair<int, int> a, pair<int, int> b) {
  return a.first * b.first + a.second * b.second;
}
void build(vector<Line> L, vector<pair<int, int> > p, int x1, int x2, bool rev,
           vector<Line> conf, pair<int, int> dir) {
  int j = 0;
  for (int i = 0; i + 1 < p.size(); i++) {
    int l = max(x1, p[i].first);
    int r = min(x2, p[i + 1].first);
    int y = p[i].second;
    if (l >= r) continue;
    if (j < conf.size() && p[i].first == conf[j].l &&
        p[i + 1].first == conf[j].r) {
      j++;
      if (dot(dir, conf[j - 1].dir) < 0) continue;
    } else {
      if (!rev) {
        if (cross(L[i].dir, make_pair(p[i + 1].first - p[i].first, 0)) >= 0 &&
            cross(L[i + 1].dir, make_pair(p[i].first - p[i + 1].first, 0)) >=
                0) {
        } else {
          continue;
        }
      } else {
        if (cross(L[i].dir, make_pair(0, p[i + 1].first - p[i].first)) >= 0 &&
            cross(L[i + 1].dir, make_pair(0, p[i].first - p[i + 1].first)) >=
                0) {
        } else {
          continue;
        }
      }
    }
    if (!rev) {
      buildGraph(l, y, r, y);
    } else {
      buildGraph(y, l, y, r);
    }
  }
}
vector<Line> L;
vector<pair<int, int> > splitRectangle(vector<Line> v, int y, int x1, int x2) {
  int i;
  L.clear();
  vector<pair<int, int> > p;
  for (i = 0; i < v.size(); i++) {
    if (y >= v[i].l && y <= v[i].r) {
      p.push_back(make_pair(v[i].x, y));
      L.push_back(v[i]);
    }
  }
  return p;
}
bool used[MAX];
bool getPolygon(int start) {
  int tmp = start;
  int cnt = 0;
  while (!used[tmp]) {
    cnt++;
    used[tmp] = true;
    for (int i = 0; i < e[tmp].size(); i++) {
      int v = e[tmp][i];
      if (used[v] == false) {
        tmp = v;
        break;
      }
    }
  }
  for (int i = 0; i < e[tmp].size(); i++) {
    if (e[tmp][i] == start && cnt > 2) return true;
  }
  return false;
}
vector<Line> getConf(int x, vector<Line> l) {
  vector<Line> ret;
  ret.clear();
  for (int i = 0; i < l.size(); i++) {
    if (x == l[i].x) {
      ret.push_back(l[i]);
    }
  }
  return ret;
}
int main() {
  int n, i, j;
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  id = 0;
  for (i = 0; i < MAX; i++) {
    e[i].clear();
  }
  h.clear();
  v.clear();
  int a, b, c, d;
  cin >> n >> a >> b;
  int sx = a;
  int sy = b;
  for (i = 1; i < n; i++) {
    cin >> c >> d;
    makeLine(a, b, c, d);
    a = c;
    b = d;
  }
  makeLine(a, b, sx, sy);
  sort(v.begin(), v.end(), cmp);
  sort(h.begin(), h.end(), cmp);
  mp.clear();
  for (i = 0; i < v.size(); i++) {
    cutVertical(v[i], x1, y1, x2, y2);
  }
  for (i = 0; i < h.size(); i++) {
    cutHerizon(h[i], x1, y1, x2, y2);
  }
  vector<pair<int, int> > p = splitRectangle(v, y1, x1, x2);
  pair<int, int> dir = make_pair(x2 - x1, y1 - y1);
  vector<Line> conf = getConf(y1, h);
  build(L, p, x1, x2, false, conf, dir);
  p = splitRectangle(v, y2, x1, x2);
  dir = make_pair(x1 - x2, y2 - y2);
  conf = getConf(y2, h);
  build(L, p, x1, x2, false, conf, dir);
  p = splitRectangle(h, x1, y1, y2);
  dir = make_pair(x1 - x1, y1 - y2);
  conf = getConf(x1, v);
  build(L, p, y1, y2, true, conf, dir);
  p = splitRectangle(h, x2, y1, y2);
  dir = make_pair(x2 - x2, y2 - y1);
  conf = getConf(x2, v);
  build(L, p, y1, y2, true, conf, dir);
  memset(used, 0, sizeof(bool) * (id + 5));
  int ans = 0;
  for (i = 1; i <= id; i++) {
    if (!used[i]) {
      ans += getPolygon(i);
    }
  }
  cout << ans << endl;
  return 0;
}
