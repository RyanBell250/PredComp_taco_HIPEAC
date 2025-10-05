#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
int dx[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[8] = { 0, 1, 0, -1, 1, -1, 1, -1 };
vector<int> G[100000];
int dir[100000];
int vis[100000];
void dfs(int v, int p, int d) {
	dir[v] |= 1 << d;
	vis[v] = 1;
	for(auto c : G[v]) {
		if(c == p || vis[c]) continue;
		dfs(c, v, d);
	}
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int H, W, K;
	cin >> H >> W >> K;
	map<P, int> m;
	vector<P> p(K);
	for(int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		m[{ x, y }] = i;
		p[i] = { x, y };
	}
	for(int i = 0; i < K; i++) {
		for(int k = 0; k < 8; k++) {
			int ny = p[i].first + dy[k], nx = p[i].second + dx[k];
			if(m.count({ ny, nx })) {
				G[i].push_back(m[{ny, nx}]);
			}
		}
	}
	const int U = 0, D = 1, L = 2, R = 3;
	for(int i = 0; i < K; i++) {
		if(p[i].first == 0 && !vis[i]) dfs(i, -1, U);
	}
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < K; i++) {
		if(p[i].first == H - 1 && !vis[i]) dfs(i, -1, D);
	}
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < K; i++) {
		if(p[i].second == 0 && !vis[i]) dfs(i, -1, L);
	}
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < K; i++) {
		if(p[i].second == W - 1 && !vis[i]) dfs(i, -1, R);
	}
	int ok[4] = { 1 << U | 1 << D, 1 << U | 1 << L, 1 << L | 1 << R, 1 << D | 1 << R };
	for(int i = 0; i < K; i++) {
		for(int j = 0; j < 4; j++) {
			if((dir[i] & ok[j]) == ok[j]) {
				cout << 0 << endl;
				return 0;
			}
		}
	}
	for(int i = 0; i < K; i++) {
		int flag = 0;
		if(dir[i] >> U & 1 && p[i].first == H - 2) flag = 1;
		if(dir[i] >> U & 1 && p[i].second == 1) flag = 1;
		if(dir[i] >> D & 1 && p[i].first == 1) flag = 1;
		if(dir[i] >> D & 1 && p[i].second == W - 2) flag = 1;
		if(dir[i] >> L & 1 && p[i].first == 1) flag = 1;
		if(dir[i] >> L & 1 && p[i].second == W - 2) flag = 1;
		if(dir[i] >> R & 1 && p[i].first == H - 2) flag = 1;
		if(dir[i] >> R & 1 && p[i].second == 1) flag = 1;
		if(flag) {
			cout << 1 << endl;
			return 0;
		}
		for(int dx = -2; dx <= 2; dx++) {
			for(int dy = -2; dy <= 2; dy++) {
				if(abs(dx) != 2 && abs(dy) != 2) continue;
				int nx = p[i].second + dx, ny = p[i].first + dy;
				if(m.count({ ny,nx })) {
					int t = m[{ny, nx}];
					int d = dir[i] | dir[t];
					for(int j = 0; j < 4; j++) {
						if((d & ok[j]) == ok[j]) {
							cout << 1 << endl;
							return 0;
						}
					}
				}
			}
		}
	}
	cout << 2 << endl;
}
