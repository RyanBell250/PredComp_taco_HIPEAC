#include <bits/stdc++.h>
using namespace std;

template<class T> T &chmax(T &a,const T &b){ return a = max(a,b); }

int n,a[110];
using P = pair<int,int>;
P dp[110][50010];

P operator+(const P &p1,const P &p2){
	return P(p1.first + p2.first,p1.second + p2.second);
}

void solve(){
	const int INF = 1e+9;
	for(int i = 0;i < n;i++) cin >> a[i];
	for(int i = 0;i <= n;i++){
		for(int j = 0;j <= n * 500;j++) dp[i][j] = P(-INF,-INF);
	}
	dp[0][0] = P(0,0);
	for(int i = 0;i < n;i++){
		int b = (a[i] % 1000 ? a[i] % 1000 : 1000);
		for(int j = 0;j <= n * 500;j++){
			chmax(dp[i + 1][j],dp[i][j]);
			if(j + 500 - b >= 0 && j + 500 - b <= n * 500) chmax(dp[i + 1][j + 500 - b],dp[i][j] + P(1,-a[i]));
			if(b > 500 && j + 1000 - b <= n * 500) chmax(dp[i + 1][j + 1000 - b],dp[i][j] + P(0,-a[i]));
		}
	}
	P ans(-INF,-INF);
	for(int i = 0;i <= n * 500;i++){
		chmax(ans,dp[n][i]);
	}
	cout << ans.first << " " << -ans.second << endl;
}

signed main(){
	while(cin >> n,n) solve();
}

