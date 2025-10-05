#include<bits/stdc++.h>

#define rep(i,n) for(int i=0;i<(int)n;i++)
#define all(c) (c).begin(),(c).end()
#define mp make_pair
#define pb push_back
#define each(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define dbg(x) cerr<<__LINE__<<": "<<#x<<" = "<<(x)<<endl

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
const int inf = (int)1e9;
const double INF = 1e12, EPS = 1e-9;

ll days(ll y, int m, int d){
	if(m < 3) y--, m += 12;
	return 365 * (y % 7) + y / 4 - y / 100 + y / 400 + (153 * m + 8) / 5 + d;
}

int main(){
	ll y, m, d, Y, M, D;
	map<pi, ll> memo, prev;
	
	
	cin >> y >> m >> d >> Y >> M >> D;
	if(d > 13){
		d = 1;
		if(++m > 12) m = 1, y++;
	}
	while(d < 13) d++;
	
	if(D < 13){
		D = 31;
		if(--M < 1) M = 12, Y--;
	}
	while(D > 13) D--;
	
	
	ll ans = 0;
	bool flag = 0;
	while(y < Y || y == Y && m <= M){
		
		if(days(y, m, d) % 7 != 5){
			if(++m > 12) m = 1, y++;
			continue;
		}
		ans++;
		if(!flag && memo.count(pi(y % 2800, m))){
			
			ll dy = y - prev[pi(y % 2800, m)];
			ll da = ans - memo[pi(y % 2800, m)];
			
			ll t = (Y - y) / dy;
			t = max(t - 10, 0ll);
			y += dy * t;
			ans += da * t;
			flag = 1;
		}
		
		memo[pi(y % 2800, m)] = ans;
		prev[pi(y % 2800, m)] = y;
		if(++m > 12) m = 1, y++;
	}
	
	cout << ans << endl;
	
	return 0;
}
