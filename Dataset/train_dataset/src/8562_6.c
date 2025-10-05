#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 100;
const int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int h, w; 
int c_h, d_h, c_w, d_w;
string MP[N];
bool vis[N][N];
int ans = -1;
struct P{
	int x, y;
	int cnt;
};
bool inside(int x, int y) {
	return x >= 0 and x < h and y >= 0 and y < w;
}
bool legal(int x, int y) {
	return inside(x, y) and MP[x][y] == '.';
}
void bfs() {
	deque<P> dque; 
	dque.push_front({c_h, c_w, 0});
	while (!dque.empty()) {
		auto [x, y, cnt] = dque.front();
		dque.pop_front();
		if (x == d_h and y == d_w) {
			ans = cnt;
			break;
		}
		if (vis[x][y]) continue;
		vis[x][y] = true;
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			if (legal(nx, ny))
				dque.push_front({nx, ny, cnt});
		}
		for (int nx = x - 2; nx <= x + 2; nx++) {
			for (int ny = y - 2; ny <= y + 2; ny++) {
				if (legal(nx, ny))
					dque.push_back({nx, ny, cnt + 1});
			}
		}
	}
}
int main() {
	cin >> h >> w;
	cin >> c_h >> c_w >> d_h >> d_w;
	--c_h, --c_w, --d_h, --d_w;
	for (int i = 0; i < h; i++)
		cin >> MP[i];
	bfs();
	cout << ans << "\n";
}
