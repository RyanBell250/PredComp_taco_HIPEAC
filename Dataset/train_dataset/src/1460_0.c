#include <bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i, s, n) for (int i = (s); i < (n); i++)
#define RFOR(i, s, n) for (int i = (n) - 1; i >= (s); i--)
#define REP(i, n) FOR(i, 0, n)
#define RREP(i, n) RFOR(i, 0, n)
#define ALL(a) a.begin(), a.end()
#define IN(a, x, b) (a <= x && x < b)
const long long MOD = 1e9+7, INF = 1e18;
template<class T>inline bool CHMAX(T&a,T b){if(a<b){a=b;return true;}return false;}
template<class T>inline bool CHMIN(T&a,T b){if(a>b){a=b;return true;}return false;}



signed main(){
	int N,M;
	cin>>N>>M;
	vector<int>a(N);
	vector<int>cnt(200020,0);
	REP(i,N)cin>>a[i];
	REP(i,M){
		int t;
		cin>>t;
		cnt[t]++;
	}
	
	vector<int>sum(200020,0);
	REP(i,200020){
		if(cnt[i]==0)continue;
		for(int j = 1;j*i<=200020;j++){
			sum[j*i]+=i*cnt[i];
		}
	}
	vector<int>add(200020,0);
	FOR(i,1,200020){
		add[i] = add[i-1] + M - sum[i];
	}
	int ans = 0;
	REP(i,N){
		ans += add[a[i]];
	}
	cout<<ans<<endl;
}
