#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,b) FOR(i,0,b)
#define MP make_pair
#define PB push_back
using ll=long long;
using pii=pair<int,int>;
using vi=vector<int>;
using ld=long double;
int read(){
	int i;
	scanf("%d",&i);
	return i;
}
const int inf=1000000007;
void chmax(int& a,int b){
	if(a<b)
		a=b;
}
void chmin(int& a,int b){
	if(a>b)
		a=b;
}
int c[34][34],d[34];
vi g[34];
int dp[1001][34][34][16];
int main(){
	int n=read(),m=read(),r=read();
	REP(i,n)
		d[i]=read();
	REP(i,n)REP(j,n)c[i][j]=1145;
	REP(i,m){
		int a=read()-1,b=read()-1,_c=read();
		c[a][b]=c[b][a]=_c;
	}
	REP(k,n)REP(i,n)REP(j,n)
		chmin(c[i][j],c[i][k]+c[k][j]);
	REP(t,r+1)REP(i,n)REP(j,n)REP(k,16)
		dp[t][i][j][k]=-inf;
	dp[0][0][0][0]=0;
	REP(t,r){
		REP(i,n)REP(j,n)REP(k,16){
			REP(to,n){
				if(to==i){
					if(t+15<=r)
						chmax(dp[t+15][to][i][15],dp[t][i][j][k]+d[to]);
				}else if(to==j){
					int s=max(0,15-k-c[i][j]);
					if(t+s+c[i][j]<=r)
						chmax(dp[t+s+c[i][j]][to][i][min(15,s+c[i][j])],dp[t][i][j][k]+d[to]);
				}else if(t+c[i][to]<=r)
					chmax(dp[t+c[i][to]][to][i][min(15,c[i][to])],dp[t][i][j][k]+d[to]);
			}
		}
	}
	int ans=0;
	REP(t,r+1)REP(i,n)REP(j,16)
		ans=max(ans,dp[t][n-1][i][j]);
	cout<<ans<<endl;
}
