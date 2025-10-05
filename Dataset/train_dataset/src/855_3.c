#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
#define pb push_back
#define fs first
#define sc second
#define show(x) cout << #x << " = " << x << endl
#define chmin(x,y) x=min(x,y)
#define chmax(x,y) x=max(x,y)
using namespace std;
typedef long long ll;
ll mod=1e9+7;
inline void add(ll &x,ll y){
	x+=y;
	x%=mod;
}
int N,K,L[30];
int con[30][31];
vector<int> G[30];
ll way[30][2][2][2][2][9][9][9][9];
bool now=0;
void dfs(int v,int p){
	for(int u:G[v]) if(u!=p) dfs(u,v);
	int I=0,J=0;
	ll dp[2][2][9][9]={},ndp[2][2][9][9]={};
	rep(i,2) rep(j,2) dp[i][j][1][1]=1;
	rep(i,L[v]+1){
		int u=con[v][i];
		if(u>=0&&u!=p){
			rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K){
				if(dp[x][y][X][Y]==0) continue;
				rep(a,2) rep(b,2) rep(c,2) rep(d,2) rep1(A,K) rep1(B,K) rep1(C,K) rep1(D,K){
					if(way[u][a][b][c][d][A][B][C][D]==0) continue;
					int nA,nC;
					{
						nA=A+(x==a?X:0),nC=C+(y==c?Y:0);
						if(a==c&&(i==0||x!=y)){
							if(y==a) nA+=Y;
							if(x==c) nC+=X;
						}
					}
					if(nA>K||nC>K) continue;
					int nB,nD;
					{
						if(a==b) nB=nA;
						else if(b==d&&d==c) nB=nC;
						else nB=B;
						if(c==d) nD=nC;
						else if(d==b&&b==a) nD=nA;
						else nD=D;
					}
					if(nB>K||nD>K) continue;
					add(ndp[b][d][nB][nD],dp[x][y][X][Y]*way[u][a][b][c][d][A][B][C][D]);
				}
			}
			i++;
		}else{
			rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K){
				if(dp[x][y][X][Y]==0) continue;
				rep(a,2) rep(c,2){
					int nA,nC;
					{
						nA=1+(x==a?X:0),nC=1+(y==c?Y:0);
						if(a==c) nA++,nC++;
						if(a==c&&(i==0||x!=y)){
							if(y==a) nA+=Y;
							if(x==c) nC+=X;
						}
					}
					if(nA>K||nC>K) continue;
					add(ndp[a][c][nA][nC],dp[x][y][X][Y]);
				}
			}
		}
		rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K) dp[x][y][X][Y]=ndp[x][y][X][Y],ndp[x][y][X][Y]=0;
		if(u==p) break;
	}
	if(v==0){
		ll ans=0;
		I=L[v]+1;
		rep(a,2) rep(c,2) rep1(A,K) rep1(C,K) rep(b,2) rep(d,2){
			if(dp[a][c][A][C]==0) continue;
			int nA=A+(a==b?1:0),nC=C+(c==d?1:0);
			if(a==c){
				if(a==d) nA++;
				if(c==b) nC++;
			}
			if(nA>K||nC>K) continue;
			add(ans,dp[a][c][A][C]);
		}
		cout<<ans<<endl;
		return;
	}
	ll dq[2][2][9][9]={},ndq[2][2][9][9]={};
	rep(i,2) rep(j,2) dq[i][j][1][1]=1;
	rep(i,L[v]){
		int u=con[v][L[v]-1-i];
		if(u>=0&&u!=p){
			rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K){
				if(dq[x][y][X][Y]==0) continue;
				rep(a,2) rep(b,2) rep(c,2) rep(d,2) rep(A,K+1) rep(B,K+1) rep(C,K+1) rep(D,K+1){
					if(way[u][b][a][d][c][B][A][D][C]==0) continue;
					int nA,nC;
					{
						nA=A+(x==a?X:0),nC=C+(y==c?Y:0);
						if(a==c&&(i==0||x!=y)){
							if(y==a) nA+=Y;
							if(x==c) nC+=X;
						}
					}
					if(nA>K||nC>K) continue;
					int nB,nD;
					{
						if(a==b) nB=nA;
						else if(b==d&&d==c) nB=nC;
						else nB=B;
						if(c==d) nD=nC;
						else if(d==b&&b==a) nD=nA;
						else nD=D;
					}
					if(nB>K||nD>K) continue;
					add(ndq[b][d][nB][nD],dq[x][y][X][Y]*way[u][b][a][d][c][B][A][D][C]);
				}
			}
			i++;
		}else{
			rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K){
				if(dq[x][y][X][Y]==0) continue;
				rep(a,2) rep(c,2){
					int nA,nC;
					{
						nA=1+(x==a?X:0),nC=1+(y==c?Y:0);
						if(a==c) nA++,nC++;
						if(a==c&&(i==0||x!=y)){
							if(y==a) nA+=Y;
							if(x==c) nC+=X;
						}
					}
					if(nA>K||nC>K) continue;
					add(ndq[a][c][nA][nC],dq[x][y][X][Y]);
				}
			}
		}
		rep(x,2) rep(y,2) rep1(X,K) rep1(Y,K) dq[x][y][X][Y]=ndq[x][y][X][Y],ndq[x][y][X][Y]=0;
		if(u==p) break;
	}
	rep(a,2) rep(c,2) rep1(A,K) rep1(C,K) rep(b,2) rep(d,2) rep1(B,K) rep1(D,K){
		if(dp[a][c][A][C]==0) continue;
		if(dq[b][d][B][D]==0) continue;
		int nA,nB,nC,nD;
		{
			if(a==b) nA=A+B;
			else if(a==c&&c==d) nA=A+D;
			else nA=A;
			if(c==d) nC=C+D;
			else if(c==a&&a==b) nC=C+B;
			else nC=C;
			if(b==a) nB=B+A;
			else if(b==d&&d==c) nB=B+C;
			else nB=B;
			if(d==c) nD=D+C;
			else if(d==b&&b==a) nD=D+A;
			else nD=D;
		}
		if(nA>K||nB>K||nC>K||nD>K) continue;
		add(way[v][a][c][b][d][nA][nC][nB][nD],dp[a][c][A][C]*dq[b][d][B][D]);
	}
}
void solve(){
	rep(i,N) cin>>L[i];
	if(now){
		rep(i,N) cout<<L[i]<<" ";
		exit(0);
	}
	rep(i,N) rep(j,L[i]) con[i][j]=-1;
	rep(i,N) G[i].clear();
	rep(i,N) rep(a,2) rep(b,2) rep(c,2) rep(d,2) rep(A,K+1) rep(B,K+1) rep(C,K+1) rep(D,K+1) way[i][a][b][c][d][A][B][C][D]=0;
	rep(i,N-1){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		G[a].pb(c);
		G[c].pb(a);
		con[a][b]=c;
		con[c][d]=a;
	}
	con[0][L[0]]=841;
	dfs(0,841);
}
int main(){
	while(true){
		cin>>N>>K;
		if(N==0) break;
		solve();
	}
}