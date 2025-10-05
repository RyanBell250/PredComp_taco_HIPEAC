#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
struct state {
	int x, y, tail;
	state(int x_, int y_, int tail_):x(x_), y(y_), tail(tail_) {}
	bool operator<(const state &s) const {
		if(x != s.x) return x < s.x;
		if(y != s.y) return y < s.y;
		return tail < s.tail;
	}
};
typedef pair<int, int> point;
#define X first
#define Y second
point operator-(const point &a, const point &b) {
	return {a.first - b.first, a.second - b.second};
}
constexpr int dx[6] = {0, -1, -1, 0, 1, 1};
constexpr int dy[6] = {-1, 0, 1, 1, 0, -1};
map<point, int> get_d;
int n;
int gx, gy;
set<point> rocks;
constexpr int mask = (1 << 3) - 1;
inline void init() {
	for(int d = 0; d < 6; ++d) {
		get_d[point(dx[d], dy[d])] = d;
	}
}
inline int encode(const vector<point> &hexerpents) {
	int res = 0;
	for(unsigned i = hexerpents.size() - 1; i > 0; --i) {
		res = (res << 3) | get_d[hexerpents[i] - hexerpents[i - 1]];
	}
	return res;
}
inline vector<point> decode(int hx, int hy, int tail) {
	vector<point> res{{hx, hy}};
	res.reserve(n);
	for(int i = 1; i < n; ++i) {
		const int d = tail & mask;
		tail >>= 3;
		hx += dx[d];
		hy += dy[d];
		res.emplace_back(hx, hy);
	}
	return res;
}
inline bool ok(int idx, const vector<point> &hexerpents) {
	if(idx && !get_d.count(hexerpents[idx] - hexerpents[idx - 1])) return false;
	if(idx < n - 1 && !get_d.count(hexerpents[idx] - hexerpents[idx + 1])) return false;
	for(int i = 0; i < idx - 1; ++i) {
		if(get_d.count(hexerpents[i] - hexerpents[idx]) || hexerpents[i] == hexerpents[idx]) return false;
	}
	return true;
}
void update(int idx, vector<point> &hexerpents, int n_dist, queue<state> &que, map<state, int> &dist) {
	if(idx >= n) {
		if(!ok(n - 1, hexerpents)) return;
		const int code = encode(hexerpents);
		const state next(hexerpents[0].X, hexerpents[0].Y, code);
		if(!dist.count(next)) {
			que.push(next);
			dist[next] = n_dist;
		}
		return;
	}
	if(ok(idx, hexerpents)) update(idx + 1, hexerpents, n_dist, que, dist);
	point &p = hexerpents[idx];
	const int tx = p.X;
	const int ty = p.Y;
	for(int d = 0; d < 6; ++d) {
		p.X = tx + dx[d];
		p.Y = ty + dy[d];
		if(rocks.count(p)) continue;
		if(ok(idx, hexerpents)) update(idx + 2, hexerpents, n_dist, que, dist);
	}
	p.X = tx;
	p.Y = ty;
}
int bfs(const state &start) {
	queue<state> que;
	que.push(start);
	map<state, int> dist;
	dist[start] = 0;
	while(!que.empty()) {
		const state current = que.front();
		que.pop();
		const int c_dist = dist[current];
		if(current.x == gx && current.y == gy) return c_dist;
		if(c_dist + max(abs(current.x - gx), abs(current.y - gy)) >= 20) continue;
		auto hexerpents = decode(current.x, current.y, current.tail);
		update(0, hexerpents, c_dist + 1, que, dist);
	}
	return 20;
}
int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	init();
	while(cin >> n && n) {
		vector<point> hexerpents;
		hexerpents.reserve(n);
		for(int i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			hexerpents.emplace_back(x, y);
		}
		const state start(hexerpents[0].X, hexerpents[0].Y, encode(hexerpents));
		int k;
		cin >> k;
		rocks.clear();
		for(int i = 0; i < k; ++i) {
			int u, v;
			cin >> u >> v;
			rocks.insert({u, v});
		}
		cin >> gx >> gy;
		cout << bfs(start) << endl;
	}
	return EXIT_SUCCESS;
}
