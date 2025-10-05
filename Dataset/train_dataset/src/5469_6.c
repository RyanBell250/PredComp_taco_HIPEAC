#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<complex>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cassert>
using namespace std;

#define rep(i,n) for(int i=0;i<(int)n;i++)
#define each(i,c) for(__typeof(c.begin()) i=c.begin();i!=c.end();i++)
#define pb push_back
#define mp make_pair
#define all(c) c.begin(),c.end()
#define dbg(x) cerr<<__LINE__<<": "<<#x<<" = "<<(x)<<endl

typedef vector<int> vi;
typedef pair<int,int> pi;
typedef long long ll;
const int inf=(int)1e9;
const double EPS=1e-9, INF=1e12;

const int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
int w, h;
char m[20][20];
int n, g[10], d[10], s[10], e[10];
int dp[2][20][20][1 << 10];

int main(){
	while(cin >> w >> h, h){
		int y, x;
		rep(i, h) rep(j, w){
			cin >> m[i][j];
			if(m[i][j] == 'P') y = i, x = j;
		}
		cin >> n;
		rep(i, n) cin >> g[i] >> d[i] >> s[i] >> e[i];
		
		memset(dp[0], -1, sizeof(dp[0]));
		dp[0][y][x][0] = 0;
		
		int ans = 0;
		int cur = 0, next = 1;
		rep(t, 100){
			memset(dp[next], -1, sizeof(dp[next]));
			
			rep(y, h) rep(x, w) rep(k, 1 << 10) if(dp[cur][y][x][k] >= 0){
				vector<pi> item;
				
				rep(dir, 4){
					int ny = y + dy[dir], nx = x + dx[dir];
					if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
					if(!isdigit(m[ny][nx])) continue;
					
					int mx = 0;
					rep(l, n) if(g[l] == m[ny][nx] - '0' && s[l] <= t && t < e[l])
						mx = max(mx, d[l]);
					if(mx) item.pb(mp(m[ny][nx] - '0', mx));
				}
				rep(b, 1 << item.size()){
					int ncost = dp[cur][y][x][k];
					int nk = k;
					
					rep(l, item.size()) if(b & 1 << l){
						if(nk & 1 << item[l].first) goto FAIL;
						ncost += item[l].second;
						nk |= 1 << item[l].first;
					}
					rep(d, 4){
						int ny = y + dy[d], nx = x + dx[d];
						if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
						if(isdigit(m[ny][nx])) continue;
						if(dp[next][ny][nx][nk] < 0 || dp[next][ny][nx][nk] > ncost){
							dp[next][ny][nx][nk] = ncost;
							ans = max(ans, ncost);
						}
					}
					FAIL:;
				}
			}
			swap(cur, next);
		}
		cout << ans << endl;
	}
	return 0;
}