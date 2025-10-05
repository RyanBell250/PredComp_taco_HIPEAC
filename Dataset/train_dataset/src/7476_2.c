#include<bits/stdc++.h>
#define rep(i,n)for(int i=0;i<(n);i++)
using namespace std;
typedef pair<int, bool>P;

int s[5], dx[]{ 1,-1,0,0, }, dy[]{ 0,0,1,-1 };
vector<vector<int>>a(5, vector<int>(5));
int Max;
void dfs(int x, int y, int c) {
	vector<vector<P>>b(5, vector<P>(5));
	rep(i, 5)rep(j, 5)b[i][j].first = a[i][j];
	bool update = true;
	int p = 0;
	for (int v = 1; update; v++) {
		update = false;
		rep(i, 5) {
			int back = 0, cnt = 0;
			rep(j, b[i].size()) {
				if (back != b[i][j].first) {
					if (cnt >= 3) {
						for (int k = 1; k <= cnt; k++)
							b[i][j - k].second = 1;
					}
					cnt = 0;
				}
				back = b[i][j].first; cnt++;
			}
			if (cnt >= 3) {
				for (int k = 1; k <= cnt; k++)
					b[i][b[i].size() - k].second = 1;
			}
		}
		rep(i, 5) {
			int back = 0, cnt = 0;
			rep(j, 5) {
				if (b[j].size() <= i || back != b[j][i].first) {
					if (cnt >= 3) {
						for (int k = 1; k <= cnt; k++)
							b[j - k][i].second = 1;
					}
					cnt = 0;
				}
				if (i < b[j].size()) {
					back = b[j][i].first; cnt++;
				}
			}
			if (cnt >= 3) {
				for (int k = 1; k <= cnt; k++)b[5 - k][i].second = 1;
			}
		}
		rep(i, 5)rep(j, b[i].size()) {
			if (b[i][j].second == 1) {
				p += v*s[b[i][j].first];
				b[i].erase(b[i].begin() + j); update = true; j--;
			}
		}
	}
	Max = max(Max, p);
	if (c == 0)return;
	rep(i, 4) {
		int nx = x + dx[i], ny = y + dy[i];
		if (0 <= nx&&nx < 5 && 0 <= ny&&ny < 5) {
			swap(a[x][y], a[nx][ny]);
			dfs(nx, ny, c - 1);
			swap(a[x][y], a[nx][ny]);
		}
	}
}
int main() {
	int n;
	while (scanf("%d", &n), ~n) {
		Max = 0;
		rep(i, 5)rep(j, 5)scanf("%d", &a[j][i]), a[j][i]--;
		rep(i, 5)reverse(a[i].begin(), a[i].end());
		rep(i, 5)scanf("%d", &s[i]);
		rep(i, 5)rep(j, 5)dfs(i, j, n);
		printf("%d\n", Max);
	}
}