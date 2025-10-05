#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct Dice {
	vector<T> val;
	Dice(){ val.resize(6); }
	Dice(vector<T> &v) { val = v; }
	bool operator == (const Dice &t) const {
		return val == t.val;
	}
	bool operator != (const Dice &t) const {
		return val != t.val;
	}
	bool operator < (const Dice &t) const {
		return val < t.val;
	}
	inline T at(int i){
		return val[i];
	}
	inline void rotate_right(){
		T tmp = val[1];
		val[1] = val[2];
		val[2] = val[4];
		val[4] = val[3];
		val[3] = tmp;
	}
	inline void roll_front(){
		T tmp = val[0];
		val[0] = val[1];
		val[1] = val[5];
		val[5] = val[4];
		val[4] = tmp;
	}
	inline void roll_right(){
		T tmp = val[0];
		val[0] = val[3];
		val[3] = val[5];
		val[5] = val[2];
		val[2] = tmp;
	}
	vector<Dice> all_pattern(){
		vector<Dice> res;
		Dice d = *this;
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 4; j++){
				res.push_back(d);
				d.rotate_right();
			}
			if (i == 0) d.roll_front();
			else if (i < 5) d.roll_right();
			else d.roll_front();
		}
		return res;
	}
};
const int dx[] = {1, 0, 0, 0, 0, -1};
const int dy[] = {0, -1, 0, 0, 1, 0};
const int dz[] = {0, 0, 1, -1, 0, 0};
inline bool ok(int x, int y, int z)
{
	return x >= 0 && y >= 0 && z >= 0 &&
	       x <= 1 && y <= 1 && z <= 1;
}
char must[2][2][2][6];
vector<Dice<char> > ds;
vector<vector<Dice<char> > > D;
bool used[8];
bool check(int n)
{
	if (n == 8) return true;
	for (int now = 0; now < 8; now++){
		int x = !!(n & 4);
		int y = !!(n & 2);
		int z = n & 1;
		if (used[now]) continue;
		used[now] = true;
		for (int i = D[now].size() - 1; i >= 0; i--){	
			Dice<char> &dice = D[now][i];
			bool f = true;
			for (int j = 0; j < 6; j++){
				if (must[x][y][z][j] && must[x][y][z][j] != dice.at(j)){
					f = false;
					break;
				}
			}
			if (!f) continue;
			for (int dir = 0; dir < 6; dir++){
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				int nz = z + dz[dir];
				if (!ok(nx, ny, nz)) continue;
				int to = (nx << 2) + (ny << 1) + nz;
				if (to < n) continue;
				
				must[nx][ny][nz][5 - dir] = dice.at(dir) ^ 32;
			}
			if (check(n + 1)) return true;
		}
		used[now] = false;
	}
	return false;
}
void solve()
{
	memset(used, false, sizeof(used));
	if (check(0)){
		puts("YES");
		return;
	}
	puts("NO");
}
int main()
{	
	while (true){
		ds.clear();
		D.clear();
		for (int i = 0; i < 8; i++){
			vector<char> v(6);
			for (int j = 0; j < 6; j++){
				scanf(" %c", &v[j]);
				if (v[j] == '0') return 0;
			}
			ds.push_back(Dice<char>(v));
			D.push_back(ds[i].all_pattern());
		}
		solve();
	}
}
