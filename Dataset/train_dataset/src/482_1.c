#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
const Int MAX = 32;
vector<vector<Int> > X;
vector<Int> Y;
Int dpa[MAX][MAX];
Int dpb[MAX][MAX];
Int dfs(Int l,Int r,Int (*dp)[MAX],vector<Int> &s,Int n){
  Int &res=dp[l%n][r%n];
  if(~res) return res;
  if(l+1==r) return res=1LL<<s[l];
  res=0;
  for(Int i=0;i<(Int)X.size();i++){
    Int k=X[i].size();
    vector<vector<Int> > dp2(MAX*2,vector<Int>(MAX*2,0));
    dp2[l][0]=1;
    for(Int p=l;p<r;p++){
      for(Int j=0;j<k;j++){
	if(!dp2[p][j]||r-p<k-j) continue;
	dp2[p+1][j+1]|=s[p]==X[i][j];	
	for(Int q=p+2;q<=r;q++)
	  dp2[q][j+1]|=(dfs(p,q,dp,s,n)>>X[i][j])&1;
      }
    }
    res|=dp2[r][k]<<Y[i];
  }
  return res;
}
Int n,m;
inline Int ag(Int l,Int r){return dpa[l%n][r%n];};
inline Int bg(Int l,Int r){return dpb[l%m][r%m];};
Int dp[MAX*2][MAX*2];
signed main(){
  Int r;
  while(cin>>n>>m>>r,n){
    vector<Int> A(n),B(m);
    for(Int i=0;i<n;i++) cin>>A[i];
    for(Int i=0;i<m;i++) cin>>B[i];
    vector<vector<Int> > x(r);
    vector<Int> y(r);
    for(Int i=0;i<r;i++){
      Int k;
      cin>>k;
      x[i].resize(k);
      for(Int j=0;j<k;j++) cin>>x[i][j];
      cin>>y[i];
    }
    for(Int i=0;i<n;i++) A.emplace_back(Int(A[i]));
    for(Int i=0;i<m;i++) B.emplace_back(Int(B[i]));
    X=x;Y=y;
    memset(dpa,-1,sizeof(dpa));
    memset(dpb,-1,sizeof(dpb));
    for(Int i=0;i<n;i++)
      for(Int l=1;l<=n;l++)
	dfs(i,i+l,dpa,A,n);
    for(Int i=0;i<m;i++)
      for(Int l=1;l<=m;l++)
	dfs(i,i+l,dpb,B,m);
    memset(dp,-1,sizeof(dp));
    Int ans=-1;
    for(Int i=0;i<n;i++){
      for(Int j=0;j<m;j++){
	dp[i][j]=0;
	for(Int a=0;a<n;a++){
	  for(Int b=0;b<m;b++){
	    if(dp[i+a][j+b]<0) continue;
	    for(Int na=a+1;na<=n;na++)
	      for(Int nb=b+1;nb<=m;nb++)
		if(ag(i+a,i+na)&bg(j+b,j+nb))
		  chmax(dp[i+na][j+nb],dp[i+a][j+b]+1);      
	    dp[i+a][j+b]=-1;
	  }
	}
	chmax(ans,dp[i+n][j+m]);
	for(Int a=0;a<n;a++) dp[i+a][j+m]=-1;
	for(Int b=0;b<m;b++) dp[i+n][j+b]=-1;
      }
    }
    cout<<ans<<endl;
  }
  return 0;
}
