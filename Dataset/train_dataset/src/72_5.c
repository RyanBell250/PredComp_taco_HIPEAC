#include <bits/stdc++.h>
#define ft first
#define sd second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> tri;
const int MAXN = 100 * 1000 + 123;
unordered_map<int, int> d[MAXN];
unordered_map<int, vector<int>> g[MAXN];
int n, m;
inline void inp();
inline void bfs();
inline bool upd(int&, const int);
int main() {
	inp();
	bfs();
	printf("-1");
	return 0;
}
inline void inp() {
	scanf("%d%d", &n, &m);
	int p, q, c;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &p, &q, &c);
		g[--p][c].push_back(--q), g[q][c].push_back(p);
	}
}
inline bool upd(int &x, const int y) { return ((x == 0 || y < x)? x = y, true: false); }
inline void bfs() {
	deque<tri> deq;
	d[0][0] = 0;
	deq.push_back({{0, 0}, 0});
	while (!deq.empty()) {
		tri v = deq.front();
		deq.pop_front();
		if (v.sd != d[v.ft.ft][abs(v.ft.sd)])
			continue;
		if (v.ft.ft == n - 1) {
			printf("%d", v.sd);
			exit(0);
		}
		if (v.ft.sd) {
			if (upd(d[v.ft.ft][0], v.sd))
				deq.push_front({{v.ft.ft, 0}, v.sd});
			for (auto &u : g[v.ft.ft][v.ft.sd]) {
				auto &tif = d[u][v.ft.sd];
				if (upd(tif, v.sd))
						deq.push_front({{u, v.ft.sd}, tif});
			}
		}
		else {
			for (auto &i : g[v.ft.ft])
				if (upd(d[v.ft.ft][i.ft], v.sd + 1))
					deq.push_back({{v.ft.ft, i.ft}, v.sd + 1});
		}
	}
}