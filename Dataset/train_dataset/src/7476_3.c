#include<iostream>
#include<algorithm>
using namespace std;
struct State { int x[5][5]; };
int n, b[6];
pair<State, int>del(State S) {
	bool used[5][5]; for (int i = 0; i < 25; i++)used[i / 5][i % 5] = false;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (S.x[i][j] == S.x[i][j + 1] && S.x[i][j] == S.x[i][j + 2] && S.x[i][j] >= 1) {
				for (int k = j; k < j + 3; k++)used[i][k] = true;
			}
			if (S.x[j][i] == S.x[j + 1][i] && S.x[j][i] == S.x[j + 2][i] && S.x[j][i] >= 1) {
				for (int k = j; k < j + 3; k++)used[k][i] = true;
			}
		}
	}
	int cnt = 0, u = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) { if (used[i][j] == true) { cnt += b[S.x[i][j]]; S.x[i][j] = 0; u++; } }
	}
	if (u == 0)cnt = -1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 5; k++) {
				if (S.x[j][k] >= 1 && S.x[j + 1][k] == 0)swap(S.x[j][k], S.x[j + 1][k]);
			}
		}
	}
	return make_pair(S, cnt);
}
int dfs(State S, int depth, int cx, int cy) {
	if (depth == n) {
		int d = 1, c = 0;
		while (true) {
			pair<State, int>G = del(S);
			if (G.second == -1)return c;
			c += d*G.second; S = G.first; d++;
		}
	}
	int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 }, maxn = 0;
	for (int i = 0; i < 4; i++) {
		int ex = cx + dx[i], ey = cy + dy[i];
		if (ex < 0 || ex >= 5 || ey < 0 || ey >= 5)continue;
		State T = S; swap(T.x[ex][ey], T.x[cx][cy]);
		maxn = max(maxn, dfs(T, depth + 1, ex, ey));
	}
	return maxn;
}
int main() {
	while (true) {
		cin >> n; if (n == -1)break; State V;
		for (int i = 0; i < 25; i++)cin >> V.x[i / 5][i % 5];
		for (int i = 1; i <= 5; i++)cin >> b[i];
		int ret = 0; for (int i = 0; i < 25; i++) { for (int j = 0; j <= n; j++)ret = max(ret, dfs(V, j, i / 5, i % 5)); }
		cout << ret << endl;
	}
	return 0;
}